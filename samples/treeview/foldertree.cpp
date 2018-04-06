/*
** Name:        foldertree.cpp
** Purpose:     Treeview control for displaying a hierarchical folder structure
** Author:      Ulrich Telle
** Created:     2014-05-11
** Copyright:   (c) 2014-2018 Ulrich Telle
** License:     LGPL-3.0+ WITH WxWindows-exception-3.1
*/

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/artprov.h>
#include <wx/dynarray.h>
#include <wx/hashmap.h>
#include <wx/imaglist.h>
#include <wx/tokenzr.h>

#include "foldertree.h"

#include "folder_blue.xpm"
#include "folder_blue_open.xpm"
#include "folder_violet.xpm"
#include "folder_violet_open.xpm"

// Stack implementation for application tree
WX_DECLARE_OBJARRAY(wxTreeItemId, FolderItemIdArray);

#include <wx/arrimpl.cpp> // this is a magic incantation which must be done!
WX_DEFINE_OBJARRAY(FolderItemIdArray);

// Tree node reference hash map
WX_DECLARE_HASH_MAP(int, wxTreeItemId, wxIntegerHash, wxIntegerEqual, FolderNodeHash);

BEGIN_EVENT_TABLE(FolderTreeCtrl, wxTreeCtrl)
    EVT_KEY_DOWN(FolderTreeCtrl::OnKeyDown)
    EVT_MOTION(FolderTreeCtrl::OnMouseMove)

    EVT_TREE_SEL_CHANGED(wxID_ANY, FolderTreeCtrl::OnSelectionChanged)

    EVT_TREE_BEGIN_LABEL_EDIT(wxID_ANY, FolderTreeCtrl::OnBeginLabelEdit)
    EVT_TREE_END_LABEL_EDIT(wxID_ANY, FolderTreeCtrl::OnEndLabelEdit)

    EVT_TREE_BEGIN_DRAG(wxID_ANY, FolderTreeCtrl::OnBeginDrag)
    EVT_TREE_END_DRAG(wxID_ANY, FolderTreeCtrl::OnEndDrag)
END_EVENT_TABLE()


FolderTreeCtrl::FolderTreeCtrl(wxWindow* parent, wxWindowID id, const wxSize& size)
  : wxTreeCtrl(parent, id, wxDefaultPosition, size, wxTR_HAS_BUTTONS|wxTR_LINES_AT_ROOT|wxTR_SINGLE|wxSUNKEN_BORDER|wxTR_EDIT_LABELS),
  m_parent(parent),
  m_isRecursiveSelfNotify(false),
  m_draggingFolder(false),
  m_draggingProjects(false)
{
  wxBitmap folderClosed = GetBitmapResource(wxT("folder_blue.xpm"));
  wxBitmap folderOpened = GetBitmapResource(wxT("folder_blue_open.xpm"));
  wxBitmap selectedClosed = GetBitmapResource(wxT("folder_violet.xpm"));
  wxBitmap selectedOpened = GetBitmapResource(wxT("folder_violet_open.xpm"));
  wxImageList* il = new wxImageList(16, 16, true);
  il->Add(folderClosed);   // 0 not selected, not expanded
  il->Add(selectedClosed); // 1 selected, not expanded
  il->Add(folderOpened);   // 2 not selected, expanded
  il->Add(selectedOpened); // 3 selected, expanded
  AssignImageList(il);
  SetDropTarget(new ProjectReferencesDropTarget(this));
}

FolderTreeCtrl::~FolderTreeCtrl()
{
}

void
FolderTreeCtrl::LoadFolderTree(int activeFolder)
{
  FolderItemIdArray folderItemIdStack;
  FolderTreeItem* folderNode;
  int nodeId;
  int parentId;
  int descendant;
  int dDistance;
  int aDistance;
  int nodeLevel;
  int parentLevel;
  wxString folderName;
  wxString folderPath;

  wxString selcmd = wxString(wxT("select fid, fparent, descendant, distd, dista, fname, group_concat(fname,'/') as path from (")) +
                    wxString(wxT("  select f.fid, f.fparent, d.descendant, d.distance as distd, a.distance as dista, f.fname")) +
                    wxString(wxT("    from folderclosure d join folderclosure a on (a.descendant = d.descendant) join folders f on (f.fid = a.ancestor)")) +
                    wxString(wxT("    where d.ancestor = 1 and d.descendant != d.ancestor order by d.descendant, a.distance desc")) +
                    wxString(wxT(") group by descendant order by path;"));

  folderNode = new FolderTreeItem(1, 1, wxT("/"));
  parentLevel = 0;
  wxTreeItemId root = AddRoot(wxT("/"), 0, 1, folderNode);
  SetItemImage(root, 2, wxTreeItemIcon_Expanded);
  SetItemImage(root, 3, wxTreeItemIcon_SelectedExpanded);
  folderItemIdStack.Add(root);
  m_activeFolder = activeFolder;
  m_activeFolderId = root;

  try
  {
    wxSQLite3ResultSet q = m_db->ExecuteQuery(selcmd);
    while (q.NextRow())
    {
      nodeId      = q.GetInt(0);
      parentId    = q.GetInt(1);
      descendant  = q.GetInt(2);
      dDistance   = q.GetInt(3);
      aDistance   = q.GetInt(4);
      folderName  = q.GetString(5);
      nodeLevel   = dDistance;
      if (nodeLevel < parentLevel)
      {
        SortChildren(folderItemIdStack[nodeLevel]);
      }
      parentLevel = nodeLevel;
      folderNode = new FolderTreeItem(nodeId, parentId, folderName);
      if (nodeLevel >= (int) folderItemIdStack.GetCount())
      {
        folderItemIdStack.Add(wxTreeItemId(), nodeLevel+1-folderItemIdStack.GetCount());
      }
      wxTreeItemId newFolder = AppendItem(folderItemIdStack[nodeLevel-1], folderName, 0, 1, folderNode);
      SetItemImage(newFolder, 2, wxTreeItemIcon_Expanded);
      SetItemImage(newFolder, 3, wxTreeItemIcon_SelectedExpanded);
      folderItemIdStack[nodeLevel] = newFolder;
      if (activeFolder == nodeId)
      {
        m_activeFolderId = newFolder;
      }
    }
    for (; parentLevel >= 0; --parentLevel)
    {
      SortChildren(folderItemIdStack[parentLevel]);
    }
    Expand(folderItemIdStack[0]);
    SelectItem(m_activeFolderId);
    EnsureVisible(m_activeFolderId);
  }
  catch (wxSQLite3Exception e)
  {
  }
}

wxString
FolderTreeCtrl::GetFolderPath(int folder)
{
  wxString folderPath;
  wxString sqlFolderPathSelect =
    wxString(wxT("select group_concat(fname,'/') from ")) +
    wxString(wxT("(select f.fname from folders f join folderclosure c on (f.fid=c.ancestor)")) +
    wxString(wxT("  where c.descendant=? order by distance desc);"));
  try
  {
    wxSQLite3Statement selectStatement = m_db->PrepareStatement(sqlFolderPathSelect);
    selectStatement.Bind(1, folder);
    wxSQLite3ResultSet q = selectStatement.ExecuteQuery();
    while (q.NextRow())
    {
      folderPath = q.GetString(0);
    }
    folderPath = folderPath.Mid(4);
    if (folderPath.IsEmpty()) folderPath = wxT("/");
  }
  catch (wxSQLite3Exception e)
  {
  }
  return folderPath;
}

bool
FolderTreeCtrl::HandleDraggedProjects(int sourceFolder, int targetFolder, const wxArrayLong& projectReferences, bool doCopy)
{
  bool ok = true;

  // Prepare collection of references
  wxString references = wxT("(");
  size_t n = projectReferences.Count();
  size_t j;
  for (j = 0; j < n; ++j)
  {
    if (j > 0) references.Append(wxT(","));
    references.Append(wxString::Format(wxT("%ld"), projectReferences[j]));
  }
  references.Append(wxT(")"));

  // Prepare SQL commands
  wxString sqlRemoveTargetReferences = wxString::Format(wxT("delete from folderprojects where fid=%d and pid in "), targetFolder) + references;
  wxString sqlInsertTargetReferences = wxString::Format(wxT("insert into folderprojects (fid,pid) select %d, pid from projects where pid in "), targetFolder) + references;
  wxString sqlRemoveSourceReferences = wxString::Format(wxT("delete from folderprojects where fid=%d and pid in "), sourceFolder) + references;

  // Perform SQL commands in transaction
  try
  {
    m_db->Begin();
    m_db->ExecuteUpdate(sqlRemoveTargetReferences);
    m_db->ExecuteUpdate(sqlInsertTargetReferences);
    if (!doCopy)
    {
      m_db->ExecuteUpdate(sqlRemoveSourceReferences);
    }
    m_db->Commit();
  }
  catch (wxSQLite3Exception e)
  {
    wxLogError(wxString(_("Error: "))+e.GetMessage());
    try
    {
      m_db->Rollback();
    }
    catch (wxSQLite3Exception& e2)
    {
      wxUnusedVar(e2);
    }
    ok = false;
  }
  return ok;
}

void
FolderTreeCtrl::EnsureVisibilityActiveFolder()
{
  EnsureVisible(m_activeFolderId);
}

bool 
FolderTreeCtrl::IsSameAsActiveFolder(int folder)
{
  return m_activeFolder == folder;
}

void
FolderTreeCtrl::RemoveSelectedFolder()
{
  wxTreeItemId selectedFolderId = GetSelection();
  if (selectedFolderId.IsOk())
  {
    FolderTreeItem* folderNode = (FolderTreeItem*) GetItemData(selectedFolderId);
    int projectCount = GetProjectCount(selectedFolderId);
    if (projectCount == 0)
    {
      wxString msg = wxString::Format(_("Do you really want to remove folder '%s'?"), folderNode->GetFolderName().c_str());
      wxMessageDialog confirm(this, msg, _("Remove folder"), wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION);
      if (confirm.ShowModal() == wxID_YES)
      {
        // Try to delete the folder
        wxString sqlDeleteFolder = wxString(wxT("delete from folders where fid=?;"));
        try
        {
          wxSQLite3Statement deleteStatement = m_db->PrepareStatement(sqlDeleteFolder);
          deleteStatement.Bind(1, folderNode->GetFolderId());
          deleteStatement.ExecuteUpdate();

          RemoveChildFolders(selectedFolderId);
          Delete(selectedFolderId);
        }
        catch (wxSQLite3Exception e)
        {
          wxLogError(wxString::Format(_("Removing the folder '%s' failed."), folderNode->GetFolderName().c_str()) + wxString(wxT("\n")) +
                     wxString(_("Database error")) + wxString(wxT(": ")) + e.GetMessage());
        }
      }
    }
    else
    {
      wxLogError(wxString::Format(_("The folder '%s' cannot be removed."), folderNode->GetFolderName().c_str()) + wxString(wxT("\n")) +
                 wxString(_("The folder itself or at least one of its subfolders still contains projects.")));
    }
  }
}

void
FolderTreeCtrl::EditSelectedFolderName()
{
  wxArrayTreeItemIds selection;
  unsigned int selectionCount = GetSelections(selection);
  if (selectionCount == 1)
  {
    wxTreeItemId item = selection[0];
    if (item.IsOk()) EditLabel(item);
  }
  else
  {
    if (selectionCount > 0)
    {
      wxLogError(wxString(_("Editing the name of the selected folder failed.")) + wxString(wxT("\n")) +
                 wxString(_("More than 1 folder selected.")) + wxString(wxT("\n")) +
                 wxString(_("Please select a single folder only.")));
      }
      else
      {
        wxLogError(wxString(_("Editing the name of the selected folder failed.")) + wxString(wxT("\n")) +
                   wxString(_("No folder selected.")) + wxString(wxT("\n")) +
                   wxString(_("Please select a folder.")));
      }
  }
}

bool
FolderTreeCtrl::AddSubfolder(const wxString& newFolderName)
{
  bool ok = false;
  if (!newFolderName.IsEmpty())
  {
    wxArrayTreeItemIds selection;
    unsigned int selectionCount = GetSelections(selection);
    if (selectionCount == 1)
    {
      wxTreeItemId idParent = selection[0];
      if (idParent.IsOk())
      {
        FolderTreeItem* folderNode = (FolderTreeItem*) GetItemData(idParent);
        // Try to update the folder name
        wxString sqlInsertFolder = wxString(wxT("insert into folders (fid, fparent, fname) values (?,?,?);"));
        try
        {
          m_db->Begin();
          int newFolderId = m_db->ExecuteScalar("select max(fid)+1 from folders");
          wxSQLite3Statement insertStatement = m_db->PrepareStatement(sqlInsertFolder);
          insertStatement.Bind(1, newFolderId);
          insertStatement.Bind(2, folderNode->GetFolderId());
          insertStatement.Bind(3, newFolderName);
          insertStatement.ExecuteUpdate();
          m_db->Commit();

          FolderTreeItem* newFolderNode = new FolderTreeItem(newFolderId, folderNode->GetFolderId(), newFolderName);
          wxTreeItemId newFolder = AppendItem(idParent, newFolderName, 0, 1, newFolderNode); 
          SetItemImage(newFolder, 2, wxTreeItemIcon_Expanded);
          SetItemImage(newFolder, 3, wxTreeItemIcon_SelectedExpanded);
          SortChildren(idParent);
          Expand(idParent);
          ok = true;
        }
        catch (wxSQLite3Exception e)
        {
          try
          {
            m_db->Rollback();
          }
          catch (wxSQLite3Exception& e2)
          {
            wxUnusedVar(e2);
          }
          wxLogError(wxString::Format(_("Insert of new folder '%s' failed."), newFolderName.c_str()) + wxString(wxT("\n")) +
                     wxString(_("Folder name is not unique. Please change the folder name.")));
        }
      }
    }
    else
    {
      if (selectionCount > 0)
      {
        wxLogError(wxString(_("Adding a new subfolder failed.")) + wxString(wxT("\n")) +
                   wxString(_("More than one folder is selected.")) + wxString(wxT("\n")) +
                   wxString(_("Please select a single folder only.")));
      }
      else
      {
        wxLogError(wxString(_("Adding a new subfolder failed.")) + wxString(wxT("\n")) +
                   wxString(_("No folder selected.")) + wxString(wxT("\n")) +
                   wxString(_("Please select a folder.")));
      }
    }
  }
  else
  {
    wxLogError(wxString(_("Please enter a non-empty name for the new folder.")));
  }
  return ok;
}

bool
FolderTreeCtrl::IsTargetInSubtree(const wxTreeItemId& startFolder, const wxTreeItemId& targetFolder)
{
  bool found = false;
  if (startFolder.IsOk())
  {
    found = (startFolder == targetFolder);
    if (!found)
    {
      wxTreeItemIdValue cookie; // This cookie is needed for iteration over a trees children.
      wxTreeItemId childFolder = GetFirstChild(startFolder, cookie);
      while (!found && childFolder.IsOk())
      {
        found = IsTargetInSubtree(childFolder, targetFolder);
        childFolder = GetNextChild(startFolder, cookie);
      }
    }
  }
  return found;
}

void
FolderTreeCtrl::OnKeyDown(wxKeyEvent& keyEvent)
{
  switch (keyEvent.GetKeyCode())
  {
    case WXK_F2:
    {
      wxTreeItemId item = GetSelection();
      if (item.IsOk()) EditLabel(item);
      break;
    }
    case WXK_DELETE:
    {
      wxTreeItemId item = GetSelection();
      if (item.IsOk()) RemoveSelectedFolder();
      break;
    }
    default:
      keyEvent.Skip();
      break;
  }
}

void
FolderTreeCtrl::OnSelectionChanged(wxTreeEvent& treeEvent)
{
  wxUnusedVar(treeEvent);
  wxTreeItemId selectedFolder = GetSelection();
  if (selectedFolder.IsOk())
  {
    FolderTreeItem* folderNode = (FolderTreeItem*) GetItemData(selectedFolder);
    long fid = folderNode->GetFolderId();
    m_activeFolderId = selectedFolder;
    m_activeFolder = fid;
    wxCommandEvent doFolderChanged(wxEVT_COMMAND_BUTTON_CLICKED, m_folderChangedEventId);
    doFolderChanged.SetExtraLong(fid);
    GetEventHandler()->ProcessEvent(doFolderChanged);
  }
  treeEvent.Skip();
}

void
FolderTreeCtrl::OnBeginLabelEdit(wxTreeEvent& treeEvent)
{
  wxTreeItemId idFolder = treeEvent.GetItem();
  FolderTreeItem* folderNode = (FolderTreeItem*) GetItemData(idFolder);
  if (folderNode->GetFolderId() == 1)
  {
    treeEvent.Veto();
  }
}

void
FolderTreeCtrl::OnEndLabelEdit(wxTreeEvent& treeEvent)
{
  if (!treeEvent.IsEditCancelled())
  {
    wxTreeItemId idFolder = treeEvent.GetItem();
    FolderTreeItem* folderNode = (FolderTreeItem*) GetItemData(idFolder);
    wxString newName = treeEvent.GetLabel();
    newName = newName.Trim();
    if (!newName.IsEmpty())
    {
      // Try to update the folder name
      wxString sqlUpdateFolderName = wxString(wxT("update folders set fname=? where fid=?;"));
      try
      {
        wxSQLite3Statement updateStatement = m_db->PrepareStatement(sqlUpdateFolderName);
        updateStatement.Bind(1, newName);
        updateStatement.Bind(2, folderNode->GetFolderId());
        updateStatement.ExecuteUpdate();
        SetItemText(idFolder, newName);
        folderNode->SetFolderName(newName);
        wxTreeItemId idParent = GetItemParent(idFolder);
        SortChildren(idParent);
      }
      catch (wxSQLite3Exception e)
      {
        treeEvent.Veto();
      }
    }
    else
    {
      //wxLogError(wxString(_("A folder name can't be empty.")));
      treeEvent.Veto();
    }
  }
}

void
FolderTreeCtrl::OnBeginDrag(wxTreeEvent& treeEvent)
{
  if (!treeEvent.GetItem().IsOk())   // Should never happen.
  {
    wxLogError(_("Sorry, this folder cannot be dragged."));
    return;
  }

  if (treeEvent.GetItem() == GetRootItem())
  {
    wxLogError(_("Sorry, the root folder cannot be dragged."));
    return;
  }

  m_draggedFolderId = treeEvent.GetItem();
  m_draggingFolder = true;
  treeEvent.Allow();
}

void
FolderTreeCtrl::OnEndDrag(wxTreeEvent& treeEvent)
{
  if (m_draggingFolder && m_draggedFolderId.IsOk())
  {
    wxTreeItemId sourceFolderId = m_draggedFolderId;
    m_draggingFolder = false;

    if (treeEvent.GetItem().IsOk())
    {
      wxTreeItemId targetFolderId = treeEvent.GetItem();

      // If sourceFolder is already an immediate child of targetFolder, do nothing.
      if (GetItemParent(sourceFolderId) != targetFolderId)
      {
        // Make sure that targetFolder is not in the subtree of sourceFolder (or else the reparenting would create invalid cycles).
        // Note that the targetFolder can still be a child in a different subtree of the parent of the sourceFolder.
        bool targetInSubtree = IsTargetInSubtree(sourceFolderId, targetFolderId);
        if (!targetInSubtree)
        {
          FolderTreeItem* sourceFolderNode = (FolderTreeItem*) GetItemData(sourceFolderId);
          FolderTreeItem* targetFolderNode = (FolderTreeItem*) GetItemData(targetFolderId);
          wxString sqlUpdateFolder = wxString(wxT("update folders set fparent=? where fid=?;"));
          try
          {
            wxSQLite3Statement updateStatement = m_db->PrepareStatement(sqlUpdateFolder);
            updateStatement.Bind(1, targetFolderNode->GetFolderId());
            updateStatement.Bind(2, sourceFolderNode->GetFolderId());
            updateStatement.ExecuteUpdate();

            MoveFolder(sourceFolderId, targetFolderId);
            RemoveChildFolders(sourceFolderId);
            Delete(sourceFolderId);
            SortChildren(targetFolderId);
          }
          catch (wxSQLite3Exception e)
          {
            wxLogError(wxString::Format(_("Moving folder '%s' failed."), sourceFolderNode->GetFolderName().c_str()) + wxString(wxT("\n")) +
                       wxString(_("Subfolder with same name already exists in target folder.")));
          }
        }
      }
    }
  }
}

void
FolderTreeCtrl::MoveFolder(const wxTreeItemId& sourceFolderId, const wxTreeItemId& targetFolderId)
{
  if (sourceFolderId.IsOk())
  {
    // Append sourceFolder to targetFolder
    FolderTreeItem* sourceNode = (FolderTreeItem*) GetItemData(sourceFolderId);
    FolderTreeItem* targetNode = (FolderTreeItem*) GetItemData(targetFolderId);
    FolderTreeItem* folderNode = new FolderTreeItem(sourceNode->GetFolderId(), targetNode->GetFolderId(), sourceNode->GetFolderName());
    wxTreeItemId sourceFolderCopy = AppendItem(targetFolderId, sourceNode->GetFolderName(), 0, 1, folderNode);
    SetItemImage(sourceFolderCopy, 2, wxTreeItemIcon_Expanded);
    SetItemImage(sourceFolderCopy, 3, wxTreeItemIcon_SelectedExpanded);

    wxTreeItemIdValue cookie;
    wxTreeItemId childFolderId = GetFirstChild(sourceFolderId, cookie);
    while (childFolderId.IsOk())
    {
      MoveFolder(childFolderId, sourceFolderCopy);
      childFolderId = GetNextChild(sourceFolderId, cookie);
    }
  }
}

void
FolderTreeCtrl::RemoveChildFolders(const wxTreeItemId& sourceFolderId)
{
  int childCount = 0;
  wxTreeItemIdValue cookie;
  wxTreeItemId childFolderId = GetFirstChild(sourceFolderId, cookie);
  while (childFolderId.IsOk())
  {
    ++childCount;
    RemoveChildFolders(childFolderId);
    childFolderId = GetNextChild(sourceFolderId, cookie);
  }
  if (childCount > 0)
  {
    DeleteChildren(sourceFolderId);
  }
}

int
FolderTreeCtrl::GetProjectCount(const wxTreeItemId& folderId)
{
  int projectCount = 0;
  FolderTreeItem* folderNode = (FolderTreeItem*) GetItemData(folderId);
  wxString sqlProjectCount = wxString(wxT("select count(*) from folderprojects where fid in (select descendant from folderclosure where ancestor=?);"));
  try
  {
    wxSQLite3Statement projectCountStatement = m_db->PrepareStatement(sqlProjectCount);
    projectCountStatement.Bind(1,folderNode->GetFolderId());
    projectCount = projectCountStatement.ExecuteScalar();
  }
  catch (wxSQLite3Exception e)
  {
  }
  return projectCount;
}

// Called by EVT_MOTION
void
FolderTreeCtrl::OnMouseMove(wxMouseEvent& event)
{
  if (m_draggingFolder || m_draggingProjects)
  {
    int width = 0;
    int height = 0;
    // Get the width and height of the tree control
    GetSize(&width, &height);
    // Find where the mouse is in relation to the (exited) pane
    wxPoint mousePos = ScreenToClient(wxGetMousePosition());
    if( mousePos.x < 0 || mousePos.x > width )
      return;

    if (mousePos.y <= 0)
    {
      Scroll(true); // Scroll Up
    }
    else if (mousePos.y >= height)
    {
      Scroll(false); // Scroll Down
    }
  }
  event.Skip();
}

void
FolderTreeCtrl::Scroll(bool doScrollUp)
{
  if (doScrollUp)
  {
    LineUp();
  }
  else
  {
    LineDown();
  }
  Refresh(true);
}

wxBitmap
FolderTreeCtrl::GetBitmapResource(const wxString& name)
{
  // Bitmap retrieval

  if (name == wxT("folder_blue.xpm"))
  {
    wxBitmap bitmap(folder_blue_xpm);
    return bitmap;
  }
  else if (name == wxT("folder_blue_open.xpm"))
  {
    wxBitmap bitmap(folder_blue_open_xpm);
    return bitmap;
  }
  else if (name == wxT("folder_violet.xpm"))
  {
    wxBitmap bitmap(folder_violet_xpm);
    return bitmap;
  }
  else if (name == wxT("folder_violet_open.xpm"))
  {
    wxBitmap bitmap(folder_violet_open_xpm);
    return bitmap;
  }

  return wxNullBitmap;
}

// --- Project references drop target ---

ProjectReferencesDropTarget::ProjectReferencesDropTarget(FolderTreeCtrl* owner)
{
 m_owner = owner;
 SetDataObject(new wxTextDataObject);
}

wxDragResult
ProjectReferencesDropTarget::OnData(wxCoord x, wxCoord y, wxDragResult def)
{
  if (!GetData())
  {
    return wxDragNone;
  }
  m_copyProjects = (def == wxDragCopy);
  wxTextDataObject* dataObj = (wxTextDataObject*) m_dataObject;
  return OnDropText(x, y, dataObj->GetText()) ? def : wxDragNone;
}

bool
ProjectReferencesDropTarget::OnDropText(wxCoord x, wxCoord y, const wxString& projectReferences)
{
  wxUnusedVar(x);
  wxUnusedVar(y);
  bool accepted = false;
  if (m_dropHighlight.IsOk() && projectReferences.StartsWith(wxT("projects.source=")))
  {
    FolderTreeItem* targetFolder = (FolderTreeItem*) m_owner->GetItemData(m_dropHighlight);

    int pos = projectReferences.Find(wxT(':'));
    wxString strSourceFolder = projectReferences.Mid(16, pos-16);
    long sourceFolder;
    if (!strSourceFolder.ToLong(&sourceFolder))
    {
      sourceFolder = 1;
    }
    if (targetFolder->GetFolderId() != sourceFolder)
    {
      wxString strReferences = projectReferences.AfterFirst(wxT(':'));
      long reference;
      wxArrayLong references;
      wxStringTokenizer tkz(strReferences, wxT(":"));
      while (tkz.HasMoreTokens())
      {
        wxString token = tkz.GetNextToken();
        if (token.ToLong(&reference))
        {
          references.Add(reference);
        }
      }
      accepted = m_owner->HandleDraggedProjects(sourceFolder, targetFolder->GetFolderId(), references, m_copyProjects);
      m_targetFolderId = -1;
      ClearDropHighlight();
    }
  }
  return accepted;
}

wxTreeItemId
ProjectReferencesDropTarget::GetHit(const wxPoint& point)
{
  int flags = 0;
  wxTreeItemId hitId = m_owner->HitTest(point, flags);
  if (flags & (wxTREE_HITTEST_ABOVE | wxTREE_HITTEST_BELOW | wxTREE_HITTEST_NOWHERE | wxTREE_HITTEST_TOLEFT | wxTREE_HITTEST_TORIGHT))
  {
    hitId = wxTreeItemId(); 
  }
  return hitId;
}


wxDragResult
ProjectReferencesDropTarget::OnDragOver(wxCoord x, wxCoord y, wxDragResult def)
{
  if (def == wxDragError ||
      def == wxDragNone ||
      def == wxDragCancel)
  {
    ClearDropHighlight();
    return def;
  }

  wxTreeItemId hitId = GetHit(wxPoint(x, y));
  if (!hitId.IsOk())
  {
    ClearDropHighlight();
    return wxDragNone;
  }

  FolderTreeItem* targetFolder = (FolderTreeItem*) m_owner->GetItemData(hitId);
  if (m_owner->IsSameAsActiveFolder(targetFolder->GetFolderId()))
  {
    ClearDropHighlight();
    return wxDragNone;
  }

  m_owner->SetDraggingProjectsState(true);
  m_targetFolderId = targetFolder->GetFolderId();
  DisplayDropHighlight(hitId);

  return def;
}

void
ProjectReferencesDropTarget::OnLeave()
{
  m_owner->SetDraggingProjectsState(false);
//  ClearDropHighlight();
}

wxDragResult
ProjectReferencesDropTarget::OnEnter(wxCoord x, wxCoord y, wxDragResult def)
{
  return OnDragOver(x, y, def);
}

void
ProjectReferencesDropTarget::ClearDropHighlight()
{
  if (m_dropHighlight.IsOk())
  {
    m_owner->SetItemDropHighlight(m_dropHighlight, false);
    m_dropHighlight = wxTreeItemId();
  }
}

void
ProjectReferencesDropTarget::DisplayDropHighlight(wxTreeItemId targetId)
{
  ClearDropHighlight();
  m_owner->EnsureVisible(targetId);
  m_owner->SetItemDropHighlight(targetId, true);
  m_dropHighlight = targetId;
  wxTreeItemId firstVisibleId = m_owner->GetFirstVisibleItem();
  if (m_dropHighlight == firstVisibleId)
  {
    m_owner->Scroll(true);
  }
}
