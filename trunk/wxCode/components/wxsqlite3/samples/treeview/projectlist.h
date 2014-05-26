/////////////////////////////////////////////////////////////////////////////
// Name:        projectlist.h
// Purpose:     
// Author:      Ulrich Telle
// Modified by: 
// Created:     2014-05-11
// Copyright:   (c) Ulrich Telle
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef _PROJECT_LIST_H
#define _PROJECT_LIST_H

#include <wx/wx.h>
#include <wx/datetime.h>
#include <wx/dynarray.h>
#include <wx/grid.h>
#include <wx/listctrl.h>

#include "wx/wxsqlite3.h"

class ProjectDescription
{
public:
  int        pid;
  wxString   title;
};

// Define column numbers starting with 0 in the order to be used on display
#define GRID_COLUMN_DUMMY    0
#define GRID_COLUMN_PRJID    1
#define GRID_COLUMN_TITLE    2
#define GRID_COLUMN_MAX      3

WX_DECLARE_OBJARRAY(ProjectDescription, ArrayOfProjectDescriptions);

class TreeviewSample;

//----------------------------------------------------------------------

const int PLV_STATUS_COLUMN_WIDTH = 0;

class ProjectListView : public wxListView {
private:
  enum {
    Menu_OpenProject, 
    Menu_CopyProject, 
    Menu_DeleteProject,
    Menu_RemoveReference
  };

public:
  ProjectListView(wxWindow* parent, wxWindowID id, TreeviewSample* mainFrame, wxSQLite3Database* db, wxStatusBar *statusBar = 0);
  virtual ~ProjectListView();

  void SetProjectListFrame(TreeviewSample* projectListFrame) { m_mainFrame = projectListFrame; }

  void InitImageList();

  void LoadProjectList();
  void LoadProjectDescriptions(int sortColumn, bool descending);

  void Fill();
  void SetFilter(wxString filter) { m_filter = filter; }
  
  int GetSelectedProjectRow();

  const ProjectDescription& GetProjectDescription(int selectedRow);

  void SaveColumnWidth(int column, int width);
  void SetColumnWidths();
  void SetColumnWidths(const wxString& plWidths);
  wxString GetColumnWidths();

  void OnLabelLeftClick(wxListEvent& event);
  void OnItemRightClick(wxListEvent &event);
  
  void OnBeginDrag(wxListEvent& event);

  void OnMenuOpenProject(wxCommandEvent& event);
  void OnMenuCopyProject(wxCommandEvent& event);
  void OnMenuDeleteProject(wxCommandEvent& event);
  void OnMenuRemoveReference(wxCommandEvent& event);

protected:
  void ProcessSort(int columnIndex);

  int  m_colwidth[GRID_COLUMN_MAX];
  int  m_sortedColumn;
  bool m_sortedColumnDescending;

  wxWindow*          m_parent;
  TreeviewSample*    m_mainFrame;
  wxSQLite3Database* m_db;

  ArrayOfProjectDescriptions m_data;
  wxString                   m_filter;
  int                        m_projectCount;
  wxStatusBar*               m_statusBar;
  wxImageList*               m_imageListSmall;

  DECLARE_EVENT_TABLE()
};

#endif

