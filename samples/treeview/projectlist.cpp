/*
** Name:        projectlist.cpp
** Purpose:     Management of a list of projects
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

// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWindows headers
#ifndef WX_PRECOMP
  #include <wx/wx.h>
#endif

#include <wx/dnd.h>
#include <wx/file.h>
#include <wx/clipbrd.h>
#include <wx/fontdlg.h>
#include <wx/imaglist.h>
#include <wx/tokenzr.h>

#include "wx/wxsqlite3.h"

#include "treeviewsample.h"
#include "projectlist.h"

#include <wx/arrimpl.cpp> // this is a magic incantation which must be done!

WX_DEFINE_OBJARRAY(ArrayOfProjectDescriptions);

// ============================================================================

BEGIN_EVENT_TABLE(ProjectListView, wxListView)
  EVT_MENU(ProjectListView::Menu_OpenProject, ProjectListView::OnMenuOpenProject)
  EVT_MENU(ProjectListView::Menu_CopyProject, ProjectListView::OnMenuCopyProject)
  EVT_MENU(ProjectListView::Menu_DeleteProject, ProjectListView::OnMenuDeleteProject)
  EVT_MENU(ProjectListView::Menu_RemoveReference, ProjectListView::OnMenuRemoveReference)
END_EVENT_TABLE()

ProjectListView::ProjectListView(wxWindow* parent, wxWindowID id,
                                 TreeviewSample* mainFrame, wxSQLite3Database* db, wxStatusBar *statusBar)
  : wxListView(parent, id, wxDefaultPosition, wxSize(600, 450), wxLC_REPORT|wxLC_HRULES|wxLC_VRULES /*wxSIMPLE_BORDER|wxHSCROLL|wxVSCROLL)*/)
{
  m_parent = parent;
  m_mainFrame = mainFrame;
  m_db = db;
  m_sortedColumn = -1;
  m_sortedColumnDescending = false;
  m_statusBar = statusBar;
  m_filter = wxT("ALL");
  m_colwidth[0] = PLV_STATUS_COLUMN_WIDTH;
  int j;
  for (j = 1; j < GRID_COLUMN_MAX; ++j)
  {
    m_colwidth[j] = wxLIST_AUTOSIZE_USEHEADER;
  }
  m_imageListSmall = NULL;
}

ProjectListView::~ProjectListView()
{
  if (m_imageListSmall != NULL) delete m_imageListSmall;
}

void
ProjectListView::InitImageList()
{
  m_imageListSmall = new wxImageList(16, 16, true);
  wxBitmap* arrowUp     = m_mainFrame->GetBitmapArrowUp();
  wxBitmap* arrowDown   = m_mainFrame->GetBitmapArrowDown();
  wxBitmap* arrowUpDown = m_mainFrame->GetBitmapArrowUpDown();

  m_imageListSmall->Add(*arrowUp);
  m_imageListSmall->Add(*arrowDown);
  m_imageListSmall->Add(*arrowUpDown);
  SetImageList(m_imageListSmall, wxIMAGE_LIST_SMALL);
}

void
ProjectListView::LoadProjectList()
{
  Freeze();
  ProjectListView::LoadProjectDescriptions(m_sortedColumn, m_sortedColumnDescending);

  ClearAll();
  int idArrow = (!m_sortedColumnDescending) ? 0 : 1;
  int idArrowStd = 2;
  int idImage = -1;
  wxListItem itemCol;
  itemCol.Clear();

  itemCol.SetText(wxT(""));
  itemCol.SetImage(-1);
  itemCol.SetAlign(wxLIST_FORMAT_LEFT);
  InsertColumn(0, itemCol);

  itemCol.SetText(_("Project ID"));
  idImage = (m_sortedColumn == 1) ? idArrow : idArrowStd;
  itemCol.SetImage(idImage);
  itemCol.SetAlign(wxLIST_FORMAT_CENTER);
  InsertColumn(1, itemCol);

  itemCol.SetText(_("Title"));
  idImage = (m_sortedColumn == 2) ? idArrow : idArrowStd;
  itemCol.SetImage(idImage);
  itemCol.SetAlign(wxLIST_FORMAT_LEFT);
  InsertColumn(2, itemCol);

  int row;
  for (row = 0; row < m_projectCount; ++row)
  {
    long tmp = InsertItem(row, wxT(""));
    SetItemData(tmp, row);
    SetItem(tmp, 1, wxString::Format(wxT("%d"), m_data[row].pid));
    SetItem(tmp, 2, m_data[row].title);
  }
  SetColumnWidths();
  Thaw();
}

void
ProjectListView::LoadProjectDescriptions(int sortColumn, bool descending)
{
  wxString direction = (descending) ? wxT(" desc") : wxT("");
  wxBusyCursor cr;
  int activeFolder = m_mainFrame->GetActiveFolder();

  wxString selcmd = wxString(wxT("select p.pid, p.prjtitle")) +
                    wxString(wxT("  from projects p where p.pid in (select pid from folderprojects where fid=?)"));
  switch (sortColumn)
  {
    case GRID_COLUMN_PRJID: // Project id
      selcmd += wxT(" order by p.pid");
      selcmd += direction;
      selcmd += wxT(", p.prjtitle");
      break;
    case GRID_COLUMN_TITLE: // Project title
      selcmd += wxT(" order by p.prjtitle");
      selcmd += direction;
      selcmd += wxT(", p.pid desc");
      break;
    default:
      selcmd += wxT(" order by p.pid desc");
      break;
  }

  m_data.Empty();
  try
  {
    wxSQLite3Statement stmt = m_db->PrepareStatement(selcmd);
    stmt.Bind(1, activeFolder);
    wxSQLite3ResultSet q = stmt.ExecuteQuery();
    m_projectCount = 0;
    while (q.NextRow())
    {
      ProjectDescription s;
      s.pid      = q.GetInt(0);
      s.title    = q.GetString(1);
      m_data.Add(s);
      ++m_projectCount;
    }
  }
  catch (wxSQLite3Exception e)
  {
  }

  if (m_statusBar)
  {
    m_statusBar->SetStatusText(wxString::Format(_("%d project(s) found."), m_projectCount), 0);
  }
}

int
ProjectListView::GetSelectedProjectRow()
{
  long row = GetFirstSelected();
  long next = (row < 0) ? -1 : GetNextSelected(row);
  while (next >= 0)
  {
    Select(next, false);
    next = GetNextSelected(next);
  }
  return row;
}

const ProjectDescription&
ProjectListView::GetProjectDescription(int selectedRow)
{
  int row = selectedRow;
  if (row < 0) row = 0;
  return m_data[row];
}

void
ProjectListView::SaveColumnWidth(int column, int width)
{
  if (column > 0 && column < GRID_COLUMN_MAX)
  {
    m_colwidth[column] = width;
  }
}

void
ProjectListView::SetColumnWidths()
{
  int j;
  for (j = 0; j < GRID_COLUMN_MAX; ++j)
  {
    SetColumnWidth(j, m_colwidth[j]);
    m_colwidth[j] = GetColumnWidth(j);
  }
}

void
ProjectListView::SetColumnWidths(const wxString& plWidths)
{
  if (!plWidths.IsEmpty())
  {
    wxStringTokenizer tkz(plWidths, wxT("/"));
    wxString token;
    long width;
    int j;
    for (j = 0; j < GRID_COLUMN_MAX; ++j)
    {
      if (tkz.HasMoreTokens())
      {
        token = tkz.GetNextToken();
        if (token.ToLong(&width))
        {
          if (j == 0) width = PLV_STATUS_COLUMN_WIDTH;
          m_colwidth[j] = (int) width;
          SetColumnWidth(j, m_colwidth[j]);
        }
      }
    }
  }
}

wxString
ProjectListView::GetColumnWidths()
{
  wxString plWidths;
  int j;
  for (j = 0; j < GRID_COLUMN_MAX; ++j)
  {
    m_colwidth[j] = GetColumnWidth(j);
    plWidths += wxString::Format(wxT("%d/"), m_colwidth[j]);
  }
  return plWidths;
}

void
ProjectListView::OnItemRightClick(wxListEvent &event)
{
  long selectedRow = event.GetIndex();
  long next = GetFirstSelected();
  while (next >= 0)
  {
    if (next != selectedRow) Select(next, false);
    next = GetNextSelected(next);
  }
  Select(selectedRow);

  wxMenu myMenu((long) 0);
  myMenu.Append(Menu_OpenProject, _("Open"));
  myMenu.Append(Menu_CopyProject, _("Copy"));
  myMenu.Append(Menu_DeleteProject, _("Delete"));
  myMenu.AppendSeparator();
  myMenu.Append(Menu_RemoveReference, _("Remove reference"));
  int pid = m_data[selectedRow].pid;
  int refCount = m_mainFrame->GetProjectReferenceCount(pid);
  if (refCount < 2)
  {
    myMenu.Enable(Menu_RemoveReference, false);
  }
  PopupMenu(&myMenu);
}

void
ProjectListView::OnLabelLeftClick( wxListEvent& event )
{
  int column = event.GetColumn();
  if (column >= 0)
  {
    ProcessSort(column);
  }
  else
  {
    event.Skip();
  }
}

void
ProjectListView::OnBeginDrag(wxListEvent& event)
{
  wxUnusedVar(event);
  int rowCount = 0;
  int activeFolder = m_mainFrame->GetActiveFolder();
  wxString dragMessage = wxString::Format(wxT("projects.source=%d"), activeFolder);
  long selectedRow = GetFirstSelected();
  while (selectedRow >= 0)
  {
    ++rowCount;
    dragMessage += wxString::Format(wxT(":%d"), m_data[selectedRow].pid);
    selectedRow = GetNextSelected(selectedRow);
  }

  if (rowCount > 0)
  {
    // Start drag operation
    wxTextDataObject textData(dragMessage);
    wxDropSource source(textData, this /*, wxDROP_ICON(dnd_copy), wxDROP_ICON(dnd_move), wxDROP_ICON(dnd_none) */ );
    int flags = wxDrag_DefaultMove;
    wxDragResult result = source.DoDragDrop(flags);
    wxString dragStatusMessage;
    switch (result)
    {
      case wxDragError:   dragStatusMessage = wxString(_("Error on dragging projects references!"));            break;
      case wxDragNone:    dragStatusMessage = wxString(_("No project references moved or copied."));            break;
      case wxDragCopy:    dragStatusMessage = wxString::Format(_("%d project reference(s) copied."), rowCount); break;
      case wxDragMove:    dragStatusMessage = wxString::Format(_("%d project reference(s) moved."), rowCount);  break;
      case wxDragCancel:  dragStatusMessage = wxString(_("Dragging of project references cancelled."));         break;
      default:            dragStatusMessage = wxString(_("Unknown drag status."));                              break;
    }
    m_mainFrame->RefreshProjectList();
    m_mainFrame->SetStatusText(dragStatusMessage, 0);
  }
}

void
ProjectListView::OnMenuOpenProject(wxCommandEvent& event)
{
  wxUnusedVar(event);
  wxCommandEvent menuevent(wxEVT_COMMAND_MENU_SELECTED, ID_PROJECT_OPEN);
  m_mainFrame->GetEventHandler()->ProcessEvent( menuevent );
}

void
ProjectListView::OnMenuCopyProject(wxCommandEvent& WXUNUSED(event))
{
  wxCommandEvent menuevent(wxEVT_COMMAND_MENU_SELECTED, ID_PROJECT_COPY);
  m_mainFrame->GetEventHandler()->ProcessEvent( menuevent );
}

void
ProjectListView::OnMenuDeleteProject(wxCommandEvent& WXUNUSED(event))
{
  wxCommandEvent menuevent(wxEVT_COMMAND_MENU_SELECTED, ID_PROJECT_DELETE);
  m_mainFrame->GetEventHandler()->ProcessEvent( menuevent );
}

void
ProjectListView::OnMenuRemoveReference(wxCommandEvent& event)
{
  wxUnusedVar(event);
  long row = GetFirstSelected();
  if (row >= 0)
  {
    int projectId = m_data[row].pid;
    int refCount = m_mainFrame->GetProjectReferenceCount(projectId);
    if (refCount > 1)
    {
      wxString projectTitle  = m_data[row].title;

      wxString msg = wxString(_("Do you really want to remove the project reference from this folder?")) + wxT("\n\n")
        + wxString::Format(wxT("%d"), projectId) + wxString(wxT(" / ")) + projectTitle;
      wxMessageDialog confirm(this, msg, _("Remove project reference"), wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION);
      if (confirm.ShowModal() == wxID_YES)
      {
        m_mainFrame->RemoveProjectReference(projectId);
      }
    }
  }
}

void
ProjectListView::Fill()
{
  LoadProjectList();
}

void
ProjectListView::ProcessSort(int columnIndex)
{
  if (columnIndex >= 0)
  {
    m_sortedColumnDescending = (columnIndex == m_sortedColumn) && !m_sortedColumnDescending;
    SetColumnImage(columnIndex, (m_sortedColumnDescending) ? 0 : 1);
    m_sortedColumn = columnIndex;
    Fill();
    Refresh();
  }
}
