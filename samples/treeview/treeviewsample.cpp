/*
** Name:        treeviewsample.cpp
** Purpose:     Treeview sample frame control
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
#include "wx/wx.h"
#endif

#include <wx/aboutdlg.h>
#include <wx/imaglist.h>
#include <wx/textdlg.h>

#include "foldertree.h"
#include "treeviewsample.h"

// XPM images
#include "mondrian.xpm"

#include "folder_delete.xpm"
#include "folder_add.xpm"
#include "folder_edit.xpm"
#include "project_new.xpm"
#include "project_edit.xpm"
#include "project_copy.xpm"
#include "project_delete.xpm"
#include "project_link_delete.xpm"
#include "arrow_up.xpm"
#include "arrow_down.xpm"
#include "arrow_up_down.xpm"

/*
 * TreeviewSample type definition
 */

IMPLEMENT_CLASS( TreeviewSample, wxFrame )

/*
 * TreeviewSample event table definition
 */

BEGIN_EVENT_TABLE( TreeviewSample, wxFrame )

  EVT_LIST_ITEM_RIGHT_CLICK( ID_PROJECT_VIEW, TreeviewSample::OnProjectViewRightClick )

  EVT_MENU( wxID_EXIT, TreeviewSample::OnExitClick )
  EVT_MENU( wxID_ABOUT, TreeviewSample::OnAboutClick )

  EVT_MENU( ID_REFRESH_PROJECTLIST, TreeviewSample::OnRefreshProjectList )

  EVT_MENU( ID_PROJECT_OPEN, TreeviewSample::OnProjectOpenClick )
  EVT_MENU( ID_PROJECT_COPY, TreeviewSample::OnProjectCopyClick )
  EVT_MENU( ID_PROJECT_DELETE, TreeviewSample::OnProjectDeleteClick )

  EVT_BUTTON( ID_FOLDER_REMOVE, TreeviewSample::OnFolderRemoveClick )
  EVT_BUTTON( ID_FOLDER_EDIT_NAME, TreeviewSample::OnFolderEditNameClick )
  EVT_BUTTON( ID_FOLDER_ADD, TreeviewSample::OnFolderAddClick )
  EVT_BUTTON( ID_FOLDER_CHANGED, TreeviewSample::OnFolderChanged )

  EVT_CONTEXT_MENU( TreeviewSample::OnContextMenu )

  EVT_BUTTON( ID_PROJECT_NEW, TreeviewSample::OnProjectNewClick )
  EVT_BUTTON( ID_PROJECT_OPEN, TreeviewSample::OnProjectOpenClick )
  EVT_BUTTON( ID_PROJECT_COPY, TreeviewSample::OnProjectCopyClick )
  EVT_BUTTON( ID_PROJECT_DELETE, TreeviewSample::OnProjectDeleteClick )
  EVT_BUTTON( ID_PROJECT_REMOVE_REFERENCE, TreeviewSample::OnProjectRemoveReferenceClick )

  // Project list view
  EVT_LIST_COL_CLICK( ID_PROJECT_LIST, TreeviewSample::OnProjectViewColLeftClick )
  EVT_LIST_COL_BEGIN_DRAG( ID_PROJECT_LIST, TreeviewSample::OnProjectViewColBeginDrag )
  EVT_LIST_COL_END_DRAG( ID_PROJECT_LIST, TreeviewSample::OnProjectViewColEndDrag )

  EVT_LIST_ITEM_ACTIVATED( ID_PROJECT_LIST, TreeviewSample::OnProjectViewItemActivated )
  EVT_LIST_ITEM_RIGHT_CLICK( ID_PROJECT_LIST, TreeviewSample::OnProjectViewRightClick )
  
  EVT_LIST_BEGIN_DRAG( ID_PROJECT_LIST, TreeviewSample::OnProjectViewBeginDrag )

END_EVENT_TABLE()


/*
 * TreeviewSample constructors
 */

TreeviewSample::TreeviewSample()
{
  Init();
}

TreeviewSample::TreeviewSample( wxSQLite3Database* db, wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
  m_db = db;
  Init();
  Create( parent, id, caption, pos, size, style );
}


/*
 * TreeviewSample creator
 */

bool
TreeviewSample::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
  wxFrame::Create( parent, id, caption, pos, size, style );

  CreateControls();
  SetIcon(wxICON(mondrian));
  SetMinSize(wxSize(500,200));
  if (GetSizer())
  {
    GetSizer()->Fit(this);
    GetSizer()->SetSizeHints(this);
  }
  Centre();

  return true;
}


/*
 * TreeviewSample destructor
 */

TreeviewSample::~TreeviewSample()
{
}


/*
 * Member initialisation
 */

void
TreeviewSample::Init()
{
  m_projectNewButton = NULL;
  m_projectOpenButton = NULL;
  m_projectCopyButton = NULL;
  m_projectDeleteButton = NULL;
  m_projectRemoveReferenceButton = NULL;
  m_projectFolderCtrl = NULL;
  m_statusBar = NULL;

  m_arrowUp     = GetBitmapResource(wxT("arrow_up.xpm"));
  m_arrowDown   = GetBitmapResource(wxT("arrow_down.xpm"));
  m_arrowUpDown = GetBitmapResource(wxT("arrow_up_down.xpm"));
  
  m_activeFolder = 1;
}


/*
 * Control creation for TreeviewSample
 */

void
TreeviewSample::CreateControls()
{    
  TreeviewSample* mainFrame = this;

  wxMenuBar* menuBar = new wxMenuBar;

  wxMenu* itemMenuExit = new wxMenu;
  itemMenuExit->Append(wxID_EXIT, _("&Exit"), wxEmptyString, wxITEM_NORMAL);
  menuBar->Append(itemMenuExit, _("&Project"));

  wxMenu* itemHelpMenu = new wxMenu;
  itemHelpMenu->Append(wxID_ABOUT, _("&About"), wxEmptyString, wxITEM_NORMAL);
  menuBar->Append(itemHelpMenu, _("&Help"));

  mainFrame->SetMenuBar(menuBar);

  m_statusBar = new wxStatusBar( mainFrame, ID_STATUSBAR1, wxST_SIZEGRIP|wxNO_BORDER );
  m_statusBar->SetFieldsCount(2);
  mainFrame->SetStatusBar(m_statusBar);

  wxPanel* mainPanel = new wxPanel( mainFrame, ID_PANEL, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxTAB_TRAVERSAL );

  wxBoxSizer* itemBoxSizer6 = new wxBoxSizer(wxVERTICAL);
  mainPanel->SetSizer(itemBoxSizer6);

  wxBoxSizer* itemBoxSizer7 = new wxBoxSizer(wxHORIZONTAL);
  itemBoxSizer6->Add(itemBoxSizer7, 1, wxGROW|wxLEFT|wxRIGHT|wxBOTTOM, 3);

  wxSplitterWindow* splitterWindow = new wxSplitterWindow( mainPanel, ID_SPLITTER_PROJECT_LIST, wxDefaultPosition, wxSize(500, 100), wxSP_3DBORDER|wxSP_3DSASH|wxNO_BORDER );
  splitterWindow->SetMinimumPaneSize(175);

  m_projectFolderPanel = new wxPanel( splitterWindow, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNO_BORDER|wxTAB_TRAVERSAL );
  wxBoxSizer* itemBoxSizer10 = new wxBoxSizer(wxVERTICAL);
  m_projectFolderPanel->SetSizer(itemBoxSizer10);

  wxBoxSizer* folderControlBoxSizer = new wxBoxSizer(wxHORIZONTAL);
  itemBoxSizer10->Add(folderControlBoxSizer, 0, wxGROW, 3);

  wxBitmapButton* folderDeleteBitmapButton = new wxBitmapButton( m_projectFolderPanel, ID_FOLDER_REMOVE, mainFrame->GetBitmapResource(wxT("folder_delete.xpm")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
  if (TreeviewSample::ShowToolTips())
    folderDeleteBitmapButton->SetToolTip(_("Remove folder"));
  folderControlBoxSizer->Add(folderDeleteBitmapButton, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3);

  wxBitmapButton* folderEditBitmapButton = new wxBitmapButton( m_projectFolderPanel, ID_FOLDER_EDIT_NAME, mainFrame->GetBitmapResource(wxT("folder_edit.xpm")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
  if (TreeviewSample::ShowToolTips())
    folderEditBitmapButton->SetToolTip(_("Edit folder name"));
  folderControlBoxSizer->Add(folderEditBitmapButton, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3);

  folderControlBoxSizer->Add(5, 5, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3);

  m_folderNameCtrl = new wxTextCtrl( m_projectFolderPanel, ID_FOLDER_NEW_NAME, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
  if (TreeviewSample::ShowToolTips())
    m_folderNameCtrl->SetToolTip(_("Enter name for new subfolder"));
  folderControlBoxSizer->Add(m_folderNameCtrl, 1, wxALIGN_CENTER_VERTICAL|wxLEFT|wxTOP|wxBOTTOM, 3);

  wxBitmapButton* folderAddBitmapButton = new wxBitmapButton( m_projectFolderPanel, ID_FOLDER_ADD, mainFrame->GetBitmapResource(wxT("folder_add.xpm")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
  if (TreeviewSample::ShowToolTips())
    folderAddBitmapButton->SetToolTip(_("Add new subfolder"));
  folderControlBoxSizer->Add(folderAddBitmapButton, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3);

  m_projectFolderTreeCtrl = new FolderTreeCtrl( m_projectFolderPanel, ID_FOLDER_TREECTRL, wxDefaultSize);
  m_projectFolderTreeCtrl->SetFolderChangedEventId(ID_FOLDER_CHANGED);
  itemBoxSizer10->Add(m_projectFolderTreeCtrl, 1, wxGROW, 3);

  m_projectListPanel = new wxPanel( splitterWindow, wxID_ANY, wxDefaultPosition, wxSize(800, -1), wxNO_BORDER|wxTAB_TRAVERSAL );
  wxBoxSizer* itemBoxSizer19 = new wxBoxSizer(wxVERTICAL);
  m_projectListPanel->SetSizer(itemBoxSizer19);

  wxBoxSizer* itemBoxSizer20 = new wxBoxSizer(wxHORIZONTAL);
  itemBoxSizer19->Add(itemBoxSizer20, 0, wxGROW|wxLEFT|wxRIGHT, 3);
  m_projectNewButton = new wxBitmapButton( m_projectListPanel, ID_PROJECT_NEW, mainFrame->GetBitmapResource(wxT("project_new.xpm")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
  if (TreeviewSample::ShowToolTips())
    m_projectNewButton->SetToolTip(_("Create new project"));
  itemBoxSizer20->Add(m_projectNewButton, 0, wxALIGN_CENTER_VERTICAL|wxLEFT|wxTOP|wxBOTTOM, 3);

  itemBoxSizer20->Add(5, 5, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM, 3);

  m_projectOpenButton = new wxBitmapButton( m_projectListPanel, ID_PROJECT_OPEN, mainFrame->GetBitmapResource(wxT("project_edit.xpm")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
  if (TreeviewSample::ShowToolTips())
    m_projectOpenButton->SetToolTip(_("Open selected project"));
  itemBoxSizer20->Add(m_projectOpenButton, 0, wxALIGN_CENTER_VERTICAL|wxLEFT|wxTOP|wxBOTTOM, 3);

  m_projectCopyButton = new wxBitmapButton( m_projectListPanel, ID_PROJECT_COPY, mainFrame->GetBitmapResource(wxT("project_copy.xpm")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
  if (TreeviewSample::ShowToolTips())
    m_projectCopyButton->SetToolTip(_("Copy selected project"));
  itemBoxSizer20->Add(m_projectCopyButton, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3);

  itemBoxSizer20->Add(5, 5, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM, 3);

  m_projectDeleteButton = new wxBitmapButton( m_projectListPanel, ID_PROJECT_DELETE, mainFrame->GetBitmapResource(wxT("project_delete.xpm")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
  if (TreeviewSample::ShowToolTips())
    m_projectDeleteButton->SetToolTip(_("Delete selected project"));
  itemBoxSizer20->Add(m_projectDeleteButton, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3);

  itemBoxSizer20->Add(5, 5, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM, 3);

  m_projectRemoveReferenceButton = new wxBitmapButton( m_projectListPanel, ID_PROJECT_REMOVE_REFERENCE, mainFrame->GetBitmapResource(wxT("project_link_delete.xpm")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
  if (TreeviewSample::ShowToolTips())
    m_projectRemoveReferenceButton->SetToolTip(_("Remove selected project reference from current folder"));
  itemBoxSizer20->Add(m_projectRemoveReferenceButton, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3);

  itemBoxSizer20->Add(5, 5, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM, 3);

  m_projectFolderCtrl = new wxTextCtrl( m_projectListPanel, ID_PROJECT_FOLDER, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
  itemBoxSizer20->Add(m_projectFolderCtrl, 1, wxALIGN_CENTER_VERTICAL|wxLEFT|wxTOP|wxBOTTOM, 3);

  m_projectView = new ProjectListView( m_projectListPanel, ID_PROJECT_LIST, this, m_db, NULL);
  m_projectView->InitImageList();
  itemBoxSizer19->Add(m_projectView, 1, wxGROW|wxLEFT|wxRIGHT, 3);

  splitterWindow->SplitVertically(m_projectFolderPanel, m_projectListPanel, 250);
  itemBoxSizer7->Add(splitterWindow, 1, wxGROW|wxLEFT|wxTOP, 3);

  m_projectFolderTreeCtrl->SetDatabase(m_db);
  m_projectFolderTreeCtrl->LoadFolderTree(1);
  
  RefreshProjectList();
}

void
TreeviewSample::DeleteSelectedProject(int selectedRow)
{
  if (selectedRow >= 0)
  {
    const ProjectDescription& pd = m_projectView->GetProjectDescription(selectedRow);
    int      projectId     = pd.pid;
    wxString projectTitle  = pd.title;
    wxString msg = wxString(_("Do you really want to delete the project?")) + wxT("\n\n")
                 + wxString::Format(wxT("%d"), projectId) + wxString(wxT(" / ")) + projectTitle;
    wxMessageDialog confirm(this, msg, _("Delete project"), wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION);
    if (confirm.ShowModal() == wxID_YES)
    {
      if (DeleteFromDatabase(projectId))
      {
        RefreshProjectList();
        wxString msg = wxString(_("Project has been successfully deleted:")) + wxT("\n")
                     + wxString::Format(wxT("%d"), projectId) + wxString(wxT(" / ")) + projectTitle;
        wxMessageBox(msg, _("Delete project"), wxOK, this );
      }
      else
      {
        wxLogError(wxString(_("Unable to delete project:")) + wxT("\n") + wxString::Format(wxT("%d"), projectId) + wxString(wxT(" / ")) + projectTitle);
      }
    }
  }
  else
  {
    wxMessageBox(_("No project selected."), _("Delete project"), wxOK, this );
  }
}

bool
TreeviewSample::DeleteFromDatabase(int projectId)
{
  bool ok = true;
  try
  {
    m_db->Begin();
    wxSQLite3Statement stmt1 = m_db->PrepareStatement("delete from projects where pid=?;");
    stmt1.Bind(1, projectId);
    stmt1.ExecuteUpdate();
    wxSQLite3Statement stmt2 = m_db->PrepareStatement("delete from folderprojects where pid=?;");
    stmt2.Bind(1, projectId);
    stmt2.ExecuteUpdate();
    m_db->Commit();
  }
  catch (wxSQLite3Exception& e)
  {
    wxUnusedVar(e);
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
TreeviewSample::OpenSelectedProject(int selectedRow, bool copy)
{
  wxString msg;
  if (selectedRow >= 0)
  {
    const ProjectDescription& pd = m_projectView->GetProjectDescription(selectedRow);
    int      projectId    = pd.pid;
    wxString projectTitle = pd.title;

    if (copy)
    {
      projectTitle += wxString::Format(_(" (Copy of %d)"), projectId);
      projectId = InsertIntoDatabase(projectTitle);
    }
    wxMessageBox(wxString(_("The project to be opened")) + wxT(":\n") + 
      wxString::Format(wxT("%d"), projectId) + wxT(" / ") + projectTitle,
                 _("Open project"), wxOK, this );
  }
  else
  {
    msg = _("No project selected.");
    wxMessageBox(msg, _("Open project"), wxOK, this );
  }
}

int
TreeviewSample::InsertIntoDatabase(const wxString& projectTitle)
{
  int projectId = -1;
  int projectIdMax = 0;
  wxString sqlMaxProjectId = wxString(wxT("select max(pid) from projects"));
  wxString sqlInsertProject = wxString(wxT("insert into projects values (?,?)"));
  wxString sqlInsertReference = wxString(wxT("insert into folderprojects values (?,?)"));
  try
  {
    m_db->Begin();
    projectIdMax = m_db->ExecuteScalar(sqlMaxProjectId);
    projectId = projectIdMax + 1;
    wxSQLite3Statement stmtInsertProject = m_db->PrepareStatement(sqlInsertProject);
    stmtInsertProject.Bind(1, projectId);
    stmtInsertProject.Bind(2, projectTitle);
    stmtInsertProject.ExecuteUpdate();
    wxSQLite3Statement stmtInsertReference = m_db->PrepareStatement(sqlInsertReference);
    stmtInsertReference.Bind(1, m_activeFolder);
    stmtInsertReference.Bind(2, projectId);
    stmtInsertReference.ExecuteUpdate();
    m_db->Commit();
    RefreshProjectList();
  }
  catch (wxSQLite3Exception& e)
  {
    wxUnusedVar(e);
    projectId = -1;
    try
    {
      m_db->Rollback();
    }
    catch (wxSQLite3Exception& e2)
    {
      wxUnusedVar(e2);
    }
  }
  return projectId;
}

int
TreeviewSample::GetProjectReferenceCount(int projectId)
{
  int refCount = 0;
  wxString sqlRefCount = wxString::Format(wxT("select count(*) from folderprojects where pid=%d"), projectId);
  try
  {
    refCount = m_db->ExecuteScalar(sqlRefCount);
  }
  catch (wxSQLite3Exception& e)
  {
    wxUnusedVar(e);
    refCount = 0;
  }
  return refCount;
}

bool
TreeviewSample::RemoveProjectReference(int projectId)
{
  bool ok = true;
  wxString sqlRemoveRef = wxString::Format(wxT("delete from folderprojects where fid=%d and pid=%d"), m_activeFolder, projectId);
  try
  {
    m_db->ExecuteUpdate(sqlRemoveRef);
    RefreshProjectList();
  }
  catch (wxSQLite3Exception& e)
  {
    wxUnusedVar(e);
    ok = false;
  }
  return ok;
}

void
TreeviewSample::RefreshProjectList()
{
  m_projectView->Fill();
  m_projectView->Refresh();
  wxString folderPath = m_projectFolderTreeCtrl->GetFolderPath(m_activeFolder);
  m_projectFolderCtrl->SetValue(folderPath);
}

void
TreeviewSample::OnRefreshProjectList( wxCommandEvent& event )
{
  wxUnusedVar(event);
  RefreshProjectList();
}

/*
 * wxEVT_COMMAND_MENU_SELECTED event handler for ID_PROJECT_OPEN
 */

void
TreeviewSample::OnProjectOpenClick( wxCommandEvent& event )
{
  wxUnusedVar(event);
  int selectedRow = m_projectView->GetSelectedProjectRow();
  OpenSelectedProject(selectedRow);
}


/*
 * wxEVT_COMMAND_MENU_SELECTED event handler for ID_PROJECT_COPY
 */

void
TreeviewSample::OnProjectCopyClick( wxCommandEvent& event )
{
  wxUnusedVar(event);
  int selectedRow = m_projectView->GetSelectedProjectRow();
  OpenSelectedProject(selectedRow, true);
}


/*
 * wxEVT_COMMAND_MENU_SELECTED event handler for ID_PROJECT_DELETE
 */

void
TreeviewSample::OnProjectDeleteClick( wxCommandEvent& event )
{
  wxUnusedVar(event);
  int selectedRow = m_projectView->GetSelectedProjectRow();
  DeleteSelectedProject(selectedRow);
}


void
TreeviewSample::OnProjectRemoveReferenceClick( wxCommandEvent& event )
{
  m_projectView->OnMenuRemoveReference(event);
}

/*
 * wxEVT_COMMAND_MENU_SELECTED event handler for wxID_EXIT
 */

void
TreeviewSample::OnExitClick( wxCommandEvent& event )
{
  wxUnusedVar(event);
  Close(true);
}

/*
 * wxEVT_COMMAND_MENU_SELECTED event handler for wxID_ABOUT
 */

void
TreeviewSample::OnAboutClick( wxCommandEvent& event )
{
  wxUnusedVar(event);
  wxAboutDialogInfo info;
  info.SetName(_("wxSQLite3 Treeview Sample"));
  info.SetVersion(wxT("1.0.0"));
  info.SetDescription(_("\nThis sample program demonstrates the use of\n\n- SQLite in a wxWidgets based GUI application\n- Persisting a tree structure in a SQLite database\n- Drag and drop of folders within a treeview\n- Move or copy of project references via drag & drop "));
  info.SetCopyright(_T("(C) 2014 Ulrich Telle <ulrich.telle@gmx.de>"));
  wxAboutBox(info);
}


/*
 * wxEVT_COMMAND_MENU_SELECTED event handler for ID_PRJ_NEW
 */

void
TreeviewSample::OnProjectNewClick( wxCommandEvent& event )
{
  wxUnusedVar(event);
  wxTextEntryDialog askProjectTitle(this, _("Please enter the title of the new project"), _("New Project Title"));
  int returnValue = askProjectTitle.ShowModal();
  if (returnValue == wxID_OK)
  {
    InsertIntoDatabase(askProjectTitle.GetValue());
  }
}

/*
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_FOLDER_REMOVE
 */

void
TreeviewSample::OnFolderRemoveClick( wxCommandEvent& event )
{
  wxUnusedVar(event);
  m_projectFolderTreeCtrl->RemoveSelectedFolder();
}


/*
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_FOLDER_EDIT_NAME
 */

void
TreeviewSample::OnFolderEditNameClick( wxCommandEvent& event )
{
  wxUnusedVar(event);
  m_projectFolderTreeCtrl->EditSelectedFolderName();
}


/*
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_FOLDER_ADD
 */

void
TreeviewSample::OnFolderAddClick( wxCommandEvent& event )
{
  wxUnusedVar(event);
  wxString newFolderName = m_folderNameCtrl->GetValue().Trim();
  if (m_projectFolderTreeCtrl->AddSubfolder(newFolderName))
  {
    m_folderNameCtrl->SetValue(wxEmptyString);
  }
}

/*
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_FOLDER_ADD
 */

void
TreeviewSample::OnFolderChanged( wxCommandEvent& event )
{
  m_activeFolder = (int) event.GetExtraLong();
  RefreshProjectList();
}

void
TreeviewSample::OnProjectViewItemActivated( wxListEvent& event )
{
  int row = event.GetIndex();
  if (row >= 0)
  {
    OpenSelectedProject(row);
  }
  else
  {
    event.Skip();
  }
}

void
TreeviewSample::OnProjectViewRightClick( wxListEvent& event )
{
  m_projectView->OnItemRightClick(event);
}

void
TreeviewSample::OnProjectViewColLeftClick( wxListEvent& event )
{
  m_projectView->OnLabelLeftClick(event);
}

void
TreeviewSample::OnProjectViewColBeginDrag( wxListEvent& event )
{
  int column = event.GetColumn();
  if (column == 0)
  {
    event.Veto();
  }
}

void
TreeviewSample::OnProjectViewColEndDrag( wxListEvent& event )
{
  int column = event.GetColumn();
  int width = m_projectView->GetColumnWidth(column);
  if (width < 2)
  {
    m_projectView->SetColumnWidth(column, wxLIST_AUTOSIZE_USEHEADER);
    width = m_projectView->GetColumnWidth(column);
  }
  m_projectView->SaveColumnWidth(column, width);
}

void
TreeviewSample::OnProjectViewBeginDrag( wxListEvent& event )
{
  m_projectView->OnBeginDrag(event);
}

/*!
 * wxEVT_CONTEXT_MENU event handler for ID_PROJECTLIST
 */

void
TreeviewSample::OnContextMenu( wxContextMenuEvent& event )
{
  event.Skip();
}

/*
 * Should we show tooltips?
 */

bool
TreeviewSample::ShowToolTips()
{
    return true;
}

/*
 * Get bitmap resources
 */

wxBitmap
TreeviewSample::GetBitmapResource( const wxString& name )
{
  // Bitmap retrieval
  wxUnusedVar(name);
  if (name == wxT("folder_delete.xpm"))
  {
    wxBitmap bitmap(folder_delete_xpm);
    return bitmap;
  }
  else if (name == wxT("folder_add.xpm"))
  {
    wxBitmap bitmap(folder_add_xpm);
    return bitmap;
  }
  else if (name == wxT("folder_edit.xpm"))
  {
    wxBitmap bitmap(folder_edit_xpm);
    return bitmap;
  }
  else if (name == wxT("project_new.xpm"))
  {
    wxBitmap bitmap(project_new_xpm);
    return bitmap;
  }
  else if (name == wxT("project_edit.xpm"))
  {
    wxBitmap bitmap(project_edit_xpm);
    return bitmap;
  }
  else if (name == wxT("project_copy.xpm"))
  {
    wxBitmap bitmap(project_copy_xpm);
    return bitmap;
  }
  else if (name == wxT("project_delete.xpm"))
  {
    wxBitmap bitmap(project_delete_xpm);
    return bitmap;
  }
  else if (name == wxT("project_link_delete.xpm"))
  {
    wxBitmap bitmap(project_link_delete_xpm);
    return bitmap;
  }
  else if (name == wxT("arrow_up.xpm"))
  {
    wxBitmap bitmap(arrow_up_xpm);
    return bitmap;
  }
  else if (name == wxT("arrow_down.xpm"))
  {
    wxBitmap bitmap(arrow_down_xpm);
    return bitmap;
  }
  else if (name == wxT("arrow_up_down.xpm"))
  {
    wxBitmap bitmap(arrow_up_down_xpm);
    return bitmap;
  }
  return wxNullBitmap;
}

/*
 * Get icon resources
 */

wxIcon
TreeviewSample::GetIconResource( const wxString& name )
{
  // Icon retrieval
  wxUnusedVar(name);
  return wxNullIcon;
}
