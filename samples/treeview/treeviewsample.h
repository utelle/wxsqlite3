/*
** Name:        treeviewsample.h
** Purpose:     Treeview sample frame control
** Author:      Ulrich Telle
** Created:     2014-05-11
** Copyright:   (c) 2014-2018 Ulrich Telle
** License:     LGPL-3.0+ WITH WxWindows-exception-3.1
*/

#ifndef _TREEVIEWSAMPLE_H_
#define _TREEVIEWSAMPLE_H_

/*!
 * Includes
 */

#include <wx/frame.h>
#include <wx/splitter.h>
#include <wx/treectrl.h>
#include <wx/listctrl.h>

#include "projectlist.h"
#include "wx/wxsqlite3.h"

/*!
 * Forward declarations
 */

class FolderTreeCtrl;
class ProjectListView;

/*!
 * Control identifiers
 */

#define ID_TREEVIEWSAMPLE           10000
#define ID_STATUSBAR1               10001

#define ID_PANEL                    10101
#define ID_SPLITTER_PROJECT_LIST    10102
#define ID_EDIT_FOLDERNAME          10103
#define ID_NEW_FOLDER_NAME          10104

#define ID_PROJECT_LIST             10105
#define ID_PROJECT_NEW              10106
#define ID_PROJECT_OPEN             10107
#define ID_PROJECT_COPY             10108
#define ID_PROJECT_DELETE           10109
#define ID_PROJECT_REMOVE_REFERENCE 10110
#define ID_PROJECT_FOLDER           10111
#define ID_PROJECT_VIEW             10112
#define ID_REFRESH_PROJECTLIST      10113

#define ID_FOLDER_TREECTRL          10030
#define ID_FOLDER_REMOVE            10031
#define ID_FOLDER_EDIT_NAME         10032
#define ID_FOLDER_NEW_NAME          10033
#define ID_FOLDER_ADD               10034

#define ID_FOLDER_CHANGED           10039

#define SYMBOL_TREEVIEWSAMPLE_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX
#define SYMBOL_TREEVIEWSAMPLE_TITLE _("wxSQLite3 Treeview Sample")
#define SYMBOL_TREEVIEWSAMPLE_IDNAME ID_TREEVIEWSAMPLE
#define SYMBOL_TREEVIEWSAMPLE_SIZE wxSize(700, 300)
#define SYMBOL_TREEVIEWSAMPLE_POSITION wxDefaultPosition


/*!
 * TreeviewSample class declaration
 */

class TreeviewSample: public wxFrame
{    
  DECLARE_CLASS( TreeviewSample )
  DECLARE_EVENT_TABLE()

public:
  /// Constructors
  TreeviewSample();
  TreeviewSample( wxSQLite3Database* db, wxWindow* parent, wxWindowID id = SYMBOL_TREEVIEWSAMPLE_IDNAME, const wxString& caption = SYMBOL_TREEVIEWSAMPLE_TITLE, const wxPoint& pos = SYMBOL_TREEVIEWSAMPLE_POSITION, const wxSize& size = SYMBOL_TREEVIEWSAMPLE_SIZE, long style = SYMBOL_TREEVIEWSAMPLE_STYLE );

  bool Create( wxWindow* parent, wxWindowID id = SYMBOL_TREEVIEWSAMPLE_IDNAME, const wxString& caption = SYMBOL_TREEVIEWSAMPLE_TITLE, const wxPoint& pos = SYMBOL_TREEVIEWSAMPLE_POSITION, const wxSize& size = SYMBOL_TREEVIEWSAMPLE_SIZE, long style = SYMBOL_TREEVIEWSAMPLE_STYLE );

  /// Destructor
  ~TreeviewSample();

  /// Initialises member variables
  void Init();

  wxBitmap* GetBitmapArrowUp()     { return &m_arrowUp; }
  wxBitmap* GetBitmapArrowDown()   { return &m_arrowDown; }
  wxBitmap* GetBitmapArrowUpDown() { return &m_arrowUpDown; }

  /// Creates the controls and sizers
  void CreateControls();

  /// Delete selected project
  void DeleteSelectedProject(int selectedRow);

  /// Delete project from database
  bool DeleteFromDatabase(int projectId);

  /// Open selected project
  void OpenSelectedProject(int selectedRow, bool copy = false);

  /// Insert project into database
  int InsertIntoDatabase(const wxString& projectTitle);

  /// Get number of references for a project
  int GetProjectReferenceCount(int projectId);

  /// Remove a reference to a project
  bool RemoveProjectReference(int projectId);

  /// Refresh the project list
  void RefreshProjectList();

  /// Set the active folder
  void SetActiveFolder(int activeFolder) { m_activeFolder = activeFolder; }

  /// Get the active folder
  int GetActiveFolder() { return m_activeFolder; }

  /// Event handler for 
  void OnRefreshProjectList( wxCommandEvent& event );

  /// wxEVT_COMMAND_MENU_SELECTED event handler for ID_PROJECT_NEW
  void OnProjectNewClick( wxCommandEvent& event );

  /// wxEVT_COMMAND_MENU_SELECTED event handler for ID_PROJECT_OPEN
  void OnProjectOpenClick( wxCommandEvent& event );

  /// wxEVT_COMMAND_MENU_SELECTED event handler for ID_PROJECT_COPY
  void OnProjectCopyClick( wxCommandEvent& event );

  /// wxEVT_COMMAND_MENU_SELECTED event handler for ID_PROJECT_DELETE
  void OnProjectDeleteClick( wxCommandEvent& event );

  /// wxEVT_COMMAND_MENU_SELECTED event handler for ID_PROJECT_REMOVE_REFERENCE
  void OnProjectRemoveReferenceClick( wxCommandEvent& event );

  /// wxEVT_COMMAND_MENU_SELECTED event handler for wxID_EXIT
  void OnExitClick( wxCommandEvent& event );

  /// wxEVT_COMMAND_MENU_SELECTED event handler for wxID_ABOUT
  void OnAboutClick( wxCommandEvent& event );

  /// wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_REMOVE
  void OnFolderRemoveClick( wxCommandEvent& event );

  /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_EDIT_FOLDERNAME
  void OnFolderEditNameClick( wxCommandEvent& event );

  /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_FOLDER_ADD
  void OnFolderAddClick( wxCommandEvent& event );

  /// wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_FOLDER_CHANGED
  void OnFolderChanged( wxCommandEvent& event );

  void OnContextMenu( wxContextMenuEvent& event );

  /// wxEVT_COMMAND_LIST_ITEM_ACTIVATED event handler for ID_PROJECT_LIST
  void OnProjectViewItemActivated( wxListEvent& event );

  /// wxEVT_COMMAND_LIST_ITEM_RIGHT_CLICK event handler for ID_PROJECT_LIST
  void OnProjectViewRightClick( wxListEvent& event );

  /// wxEVT_COMMAND_LIST_COL_CLICK event handler for ID_PROJECT_LIST
  void OnProjectViewColLeftClick( wxListEvent& event );

  /// wxEVT_COMMAND_LIST_COL_BEGIN_DRAG event handler for ID_PROJECT_LIST
  void OnProjectViewColBeginDrag( wxListEvent& event );

  /// wxEVT_COMMAND_LIST_COL_END_DRAG event handler for ID_PROJECT_LIST
  void OnProjectViewColEndDrag( wxListEvent& event );
  
    /// wxEVT_COMMAND_LIST_COL_CLICK event handler for ID_LISTCTRL
  void OnListctrlColLeftClick( wxListEvent& event );

  /// wxEVT_COMMAND_LIST_COL_BEGIN_DRAG event handler for ID_PROJECT_LIST
  void OnProjectViewBeginDrag( wxListEvent& event );

  /// Retrieves bitmap resources
  wxBitmap GetBitmapResource( const wxString& name );

  /// Retrieves icon resources
  wxIcon GetIconResource( const wxString& name );

  /// Should we show tooltips?
  static bool ShowToolTips();

  wxBitmap         m_arrowUp;
  wxBitmap         m_arrowDown;
  wxBitmap         m_arrowUpDown;

  wxStatusBar*     m_statusBar;

  wxBitmapButton*  m_projectNewButton;
  wxBitmapButton*  m_projectOpenButton;
  wxBitmapButton*  m_projectCopyButton;
  wxBitmapButton*  m_projectDeleteButton;
  wxBitmapButton*  m_projectRemoveReferenceButton;
  wxTextCtrl*      m_projectFolderCtrl;

  wxPanel*         m_projectFolderPanel;
  FolderTreeCtrl*  m_projectFolderTreeCtrl;
  wxBitmapButton*  m_folderRemoveButton;
  wxBitmapButton*  m_folderEditNameButton;
  wxTextCtrl*      m_folderNameCtrl;
  wxBitmapButton*  m_folderAddButton;

  wxPanel*         m_projectListPanel;
  ProjectListView* m_projectView;
  int              m_activeFolder;

  wxSQLite3Database* m_db;
};

#endif
    // _TREEVIEWSAMPLE_H_
