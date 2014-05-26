/////////////////////////////////////////////////////////////////////////////
// Name:        foldertree.h
// Purpose:     
// Author:      Ulrich Telle
// Modified by: 
// Created:     2014-05-11
// Copyright:   (c) Ulrich Telle
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef _FOLDER_TREE_H_
#define _FOLDER_TREE_H_

#include <wx/dnd.h>
#include <wx/treectrl.h>

#include "wx/wxsqlite3.h"

class FolderTreeItem : public wxTreeItemData
{
public:
  FolderTreeItem(int idFolder, int idParent, const wxString& folderName) : m_idFolder(idFolder), m_idParent(idParent), m_folderName(folderName) {};

  int GetFolderId() const { return m_idFolder; }
  int GetParentId() const { return m_idParent; }
  void SetFolderName(const wxString& folderName) { m_folderName = folderName; }
  wxString GetFolderName() const { return m_folderName; }

private:
  int      m_idFolder;
  int      m_idParent;
  wxString m_folderName;
};

class FolderTreeCtrl : public wxTreeCtrl /*, public ObserverT*/
{
public:
  FolderTreeCtrl(wxWindow* parent, wxWindowID id, const wxSize& size);
  virtual ~FolderTreeCtrl();

  void SetDatabase(wxSQLite3Database* database) { m_db = database; }

  void SetFolderChangedEventId(wxWindowID folderChangedEventId ) { m_folderChangedEventId = folderChangedEventId; }
  void LoadFolderTree(int activeFolder);
  wxString GetFolderPath(int folder);
  void EnsureVisibilityActiveFolder();
  bool IsSameAsActiveFolder(int folder);

  void RemoveSelectedFolder();
  void EditSelectedFolderName();
  bool AddSubfolder(const wxString& newFolderName);

  bool IsDraggingFolder() { return m_draggingFolder; }
  void SetDraggingFolderState(bool dragging) { m_draggingProjects = dragging; }

  bool IsDraggingProjects() { return m_draggingProjects; }
  void SetDraggingProjectsState(bool dragging) { m_draggingProjects = dragging; }
  bool HandleDraggedProjects(int sourceFolder, int targetFolder, const wxArrayLong& projectReferences, bool doCopy);

  wxBitmap GetBitmapResource(const wxString& name);

  void Scroll(bool doScrollUp = true);

private:
  void MoveFolder(const wxTreeItemId& sourceFolderId, const wxTreeItemId& targetFolderId);
  void RemoveChildFolders(const wxTreeItemId& sourceFolderId);

  int GetProjectCount(const wxTreeItemId& folderId);
  bool IsTargetInSubtree(const wxTreeItemId& startFolder, const wxTreeItemId& targetFolder);
  
  void OnMouseMove(wxMouseEvent& event);

  void OnKeyDown(wxKeyEvent& keyEvent);
  void OnSelectionChanged(wxTreeEvent& treeEvent);

  void OnBeginLabelEdit(wxTreeEvent& treeEvent);
  void OnEndLabelEdit(wxTreeEvent& treeEvent);

  void OnBeginDrag(wxTreeEvent& treeEvent);
  void OnEndDrag(wxTreeEvent& treeEvent);

  wxWindow*       m_parent;
  bool            m_isRecursiveSelfNotify;
  wxTreeItemId    m_draggedFolderId;
  bool            m_draggingFolder;
  int             m_activeFolder;
  wxTreeItemId    m_activeFolderId;

  wxWindowID      m_folderChangedEventId;

  bool            m_draggingProjects;

  wxSQLite3Database* m_db;

  DECLARE_EVENT_TABLE()
};

class ProjectReferencesDropTarget : public wxDropTarget
{
public:
  ProjectReferencesDropTarget(FolderTreeCtrl* owner);
  virtual ~ProjectReferencesDropTarget() {}

  virtual wxDragResult OnEnter(wxCoord x, wxCoord y, wxDragResult def);
  virtual wxDragResult OnDragOver(wxCoord x, wxCoord y, wxDragResult def);
  virtual void OnLeave();

  virtual wxDragResult OnData(wxCoord x, wxCoord y, wxDragResult def);

  wxTreeItemId GetHit(const wxPoint& point);
  void ClearDropHighlight();
  void DisplayDropHighlight(wxTreeItemId targetId);

  bool OnDropText(wxCoord x, wxCoord y, const wxString& projectReferences);

private:
  FolderTreeCtrl* m_owner;
  wxTreeItemId    m_dropHighlight;
  int             m_targetFolderId;
  bool            m_copyProjects;

  DECLARE_NO_COPY_CLASS(ProjectReferencesDropTarget)
};

#endif
