/*---------------------------------------------------------------------------*/
/* Logiciel de gestion de fichier de bases de données SQLite                 */
/*---------------------------------------------------------------------------*/
/* Projet  : wxSQLitePlus                              Version  : 0.3.0.0    */
/* Fichier : specgrid.cpp                                                    */
/* Auteur  : Fred Cailleau-Lepetit                     Date     : 07/09/2007 */
/* email   : softinthebox@free.fr                      Révision : 12/04/2009 */
/*---------------------------------------------------------------------------*/
/* Copyright (C) Fred Cailleau-Lepetit 2007                                  */
/* Licence GNU General Public License  http://www.fsf.org/copyleft/gpl.html  */
/*---------------------------------------------------------------------------*/
/*
This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation (version 3);

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

Ce programme est libre, vous pouvez le redistribuer et/ou le modifier
selon les termes de la Licence Publique Générale GNU publiée par la
Free Software Foundation (version 3).

Ce programme est distribué car potentiellement utile, mais
SANS AUCUNE GARANTIE, ni explicite ni implicite, y compris
les garanties de commercialisation ou d'adaptation dans un but
spécifique. Reportez-vous à la Licence Publique Générale GNU
pour plus de détails.
*/
#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma implementation "specgrid.h"
#endif

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif
/*---------------------------------------------------------------------------*/
#include <wx/dynarray.h>
#include <wx/arrimpl.cpp>
#include <wx/clipbrd.h>
/*---------------------------------------------------------------------------*/
#include "wxsqliteplusapp.h"
#include "sqlite3table.h"
#include "specgrid.h"
#include "filterdlg.h"
#include "sortdlg.h"
#include "blobdlg.h"
/*---------------------------------------------------------------------------*/
WX_DEFINE_OBJARRAY(wxArrayOfCellsBlock);
/*---------------------------------------------------------------------------*/
int wxCompCellsBlock(wxCellsBlock** first, wxCellsBlock** second)
{
   if (**first < **second)
      return -1;
   else if (**first > **second)
      return 1;
   else
      return 0;
}
/*---------------------------------------------------------------------------*/
IMPLEMENT_DYNAMIC_CLASS(wxSpecGrid, wxGrid)

BEGIN_EVENT_TABLE(wxSpecGrid, wxGrid)
   EVT_MENU(wxID_COPY, wxSpecGrid::OnCopy)
   EVT_UPDATE_UI(wxID_COPY, wxSpecGrid::OnCopyUpdate)
   EVT_MENU(wxID_SELECTALL, wxSpecGrid::OnSelectAll)
   EVT_UPDATE_UI(wxID_SELECTALL, wxSpecGrid::OnSelectAllUpdate)
   EVT_GRID_CELL_RIGHT_CLICK(wxSpecGrid::OnRightDown)
   EVT_GRID_SELECT_CELL(wxSpecGrid::OnSelectCell)
   EVT_GRID_BLOBEDIT(wxID_ANY, wxSpecGrid::OnBlodEdit)
END_EVENT_TABLE()
/*---------------------------------------------------------------------------*/
wxString wxSpecGrid::GetDataBlock(const wxGridCellCoords& topleft,
                                  const wxGridCellCoords& bottomright)
{
   wxString tmp;
   for (int r = topleft.GetRow(); r < bottomright.GetRow() + 1; r++)
   {
      for (int c = topleft.GetCol(); c < bottomright.GetCol() + 1; c++)
      {
         tmp += GetCellValue(r, c);
         if (c != bottomright.GetCol())
            tmp += _T("\t");
      }
      if (r != bottomright.GetRow())
         tmp += _T("\r\n");
   }
   return tmp;
}
/*---------------------------------------------------------------------------*/
wxString wxSpecGrid::GetDataBlock(const wxArrayOfCellsBlock& array)
{
   wxString tmp;
   size_t count;

   count = array.GetCount();
   for (size_t i =  0; i < count; i++)
   {
      tmp += GetDataBlock(array[i].GetLeftTop(), array[i].GetRightBottom());
      tmp += _T("\r\n");
   }

   return tmp;
}
/*---------------------------------------------------------------------------*/
void wxSpecGrid::OnCopy(wxCommandEvent& event)
{
  wxUnusedVar(event);
   wxString tmp;
   wxArrayOfCellsBlock array;
   wxGridCellCoordsArray coordsArray = GetSelectedCells();
   wxGridCellCoordsArray blocksTopLeft = GetSelectionBlockTopLeft();
   wxGridCellCoordsArray blocksBottomRight = GetSelectionBlockBottomRight();
   wxArrayInt cols = GetSelectedCols();
   wxArrayInt rows = GetSelectedRows();

   for (size_t i = 0; i < cols.GetCount(); i++)
      array.Add(wxCellsBlock(cols[i], 0, cols[i], GetNumberRows() - 1));
   for (size_t i = 0; i < rows.GetCount(); i++)
      array.Add(wxCellsBlock(0, rows[i], GetNumberCols() - 1, rows[i]));
   for (size_t i =  0; i < coordsArray.GetCount(); i++)
      array.Add(wxCellsBlock(coordsArray[i], coordsArray[i]));
   for (size_t i =  0; i < blocksTopLeft.GetCount(); i++)
      array.Add(wxCellsBlock(blocksTopLeft[i], blocksBottomRight[i]));

   array.Sort(wxCompCellsBlock);

   tmp = GetDataBlock(array);

   if (!tmp.IsEmpty())
      if (wxTheClipboard->Open())
      {
         wxTheClipboard->SetData(new wxTextDataObject(tmp));
         wxTheClipboard->Close();
      }
}
/*---------------------------------------------------------------------------*/
void wxSpecGrid::OnCopyUpdate(wxUpdateUIEvent& event)
{
   event.Enable(IsSelection());
}
/*---------------------------------------------------------------------------*/
void wxSpecGrid::OnSelectAll(wxCommandEvent& event)
{
  wxUnusedVar(event);
   SelectAll();
}
/*---------------------------------------------------------------------------*/
void wxSpecGrid::OnSelectAllUpdate(wxUpdateUIEvent& event)
{
   event.Enable(GetNumberRows() > 0);
}
/*---------------------------------------------------------------------------*/
void wxSpecGrid::OnRightDown(wxGridEvent& event)
{
  wxUnusedVar(event);
   wxMenu* popMenu = CreateRightMenu();
   if (popMenu)
   {
      PopupMenu(popMenu);
      delete popMenu;
   }
}
/*---------------------------------------------------------------------------*/
wxMenu* wxSpecGrid::CreateRightMenu()
{
   wxMenu* menu = new wxMenu;
   menu->Append(wxID_COPY, _("C&opy"), _("Copy the selected text"), wxITEM_NORMAL);
   menu->AppendSeparator();
   menu->Append(wxID_SELECTALL, _("Select &All"), _T(""), wxITEM_NORMAL);
   return menu;
}
/*---------------------------------------------------------------------------*/
void wxSpecGrid::OnSelectCell(wxGridEvent& event)
{
   SetDefaultSelection(event.GetRow(), event.GetCol());
   event.Skip();
}
/*---------------------------------------------------------------------------*/
void wxSpecGrid::OnBlodEdit(wxGridCellBlobEditorEvent& event)
{
   wxGridSQLite3Table* pGridSQLite3Table;
   wxMemoryBuffer* buffer;

   pGridSQLite3Table = wxDynamicCast(GetTable(), wxGridSQLite3Table);
   if (pGridSQLite3Table &&
       pGridSQLite3Table->GetBlob(event.GetRow(), event.GetCol(), buffer))
   {
      if (buffer)
      {
         wxBlobDialog BlobDlg(wxGetApp().GetTopWindow());

         BlobDlg.SetBlob(buffer);
         BlobDlg.ShowModal();
      }
      else
         wxMessageBox(_T("The value is NULL!"), _T("Blob"));
   }
}
/*---------------------------------------------------------------------------*/
void wxSpecGrid::SetDefaultSelection(int row, int col)
{
   if (!IsSelection())
   {
      int c1, c2;

      if (row == -1)
      {
         row = GetGridCursorRow();
         if ((row == -1)&&(GetNumberRows() > 0))
            row = 0;
      }
      if (col == -1)
      {
         col = GetGridCursorCol();
         if ((col == -1)&&(GetNumberCols() > 0))
            col = 0;
      }

      if (GetSelectionMode() == wxGrid::wxGridSelectCells)
         c1 = c2 = col;
      else
      {
         c1 = 0;
         c2 = GetNumberCols() - 1;
      }
      SelectBlock(row, c1, row, c2);
   }
}
/*---------------------------------------------------------------------------*/
bool wxSpecGrid::HasFocus()
{
   wxWindow* window = FindFocus();

   return (window && ((window == this)||(window == GetGridWindow())||
           (window == GetGridRowLabelWindow())||(window == GetGridColLabelWindow())||
           (window == GetGridCornerLabelWindow())));
}
/*---------------------------------------------------------------------------*/
IMPLEMENT_DYNAMIC_CLASS(wxDataGrid, wxSpecGrid)

BEGIN_EVENT_TABLE(wxDataGrid, wxSpecGrid)
   EVT_MENU(ID_MNU_FILTER, wxDataGrid::OnFilter)
   EVT_UPDATE_UI(ID_MNU_FILTER, wxDataGrid::OnFilterSortUpdate)
   EVT_MENU(ID_MNU_SORT, wxDataGrid::OnSort)
   EVT_UPDATE_UI(ID_MNU_SORT, wxDataGrid::OnFilterSortUpdate)
   EVT_MENU(ID_MNU_REFRESH, wxDataGrid::OnRefresh)
END_EVENT_TABLE()
/*---------------------------------------------------------------------------*/
void wxDataGrid::SetDbTableViewName(wxSQLite3Database* db,
                                    const wxString objectname,
                                    const wxString& base)
{
   m_db = db;
   m_Base = base;
   m_TableViewName = objectname;
}
/*---------------------------------------------------------------------------*/
void wxDataGrid::DoRefresh(bool usefilter)
{
   if (!m_db || m_TableViewName.IsEmpty())
      return;

   wxString sql, basename;
   wxSQLite3ResultSet resultSet;
   wxGridSQLite3TableBase* table;
   wxColour oddColour(wxGetApp().GetParamStr(PARAM_ODDROWCOLOR));

   if (m_Base != wxEmptyString)
      basename = m_Base;
   else
      basename = _T("main");
   try
   {  // remplissage de la grille des données
      sql = wxString::Format(_T("SELECT * FROM %s.%s"), basename.c_str(),
                             m_TableViewName.c_str());
      m_IsFiltered = m_IsSorted = false;
      if (usefilter)
      {
         if (!m_StringWhere.IsEmpty())
         {
            m_IsFiltered = true;
            sql += _T(" WHERE ") + m_StringWhere;
         }
         for (size_t i = 0; i < m_StringsOrder.Count(); i++)
         {
            if (i == 0)
            {
               m_IsSorted = true;
               sql += _T(" ORDER BY ");
            }
            else
               sql += _T(", ");
            sql += m_StringsOrder[i];
         }
      }
      sql += _T(";");
      resultSet = m_db->ExecuteQuery(ToUTF8(sql));
      SetTable(&g_EmptyTable);
      ForceRefresh();
      table = new wxGridSQLite3Table(&resultSet);
      table->SetAttrProvider(new OddRowsGridCellAttrProvider(oddColour));
      SetTable((wxGridTableBase*)table, true);
      table->AdaptColumnsSize();
      SetDefaultSelection();
      ForceRefresh();
      resultSet.Finalize();
   }
   catch(wxSQLite3Exception& ex)
   {
      wxGetApp().ShowError(_T("Refresh"), ex);
   }
}
/*---------------------------------------------------------------------------*/
void wxDataGrid::DoSort()
{
   wxSortDialog dlgSort(this);

   dlgSort.SetDatabase(m_db, m_Base);
   dlgSort.SetTable(m_TableViewName);
   dlgSort.SetStringsOrder(m_StringsOrder);

   if (dlgSort.ShowModal() == wxID_OK)
   {
      m_StringsOrder = dlgSort.GetStringsOrder();
      DoRefresh(true);
   }
}
/*---------------------------------------------------------------------------*/
void wxDataGrid::DoFilter()
{
   wxFilterDialog dlgFilter(this);

   dlgFilter.SetDatabase(m_db, m_Base);
   dlgFilter.SetTable(m_TableViewName);
   dlgFilter.SetStatement(m_StringWhere);

   if (dlgFilter.ShowModal() == wxID_OK)
   {
      m_StringWhere = dlgFilter.GetStatement();
      DoRefresh(true);
   }
}
/*---------------------------------------------------------------------------*/
void wxDataGrid::OnFilter(wxCommandEvent& event)
{
  wxUnusedVar(event);
   DoFilter();
}
/*---------------------------------------------------------------------------*/
void wxDataGrid::OnSort(wxCommandEvent& event)
{
  wxUnusedVar(event);
   DoSort();
}
/*---------------------------------------------------------------------------*/
void wxDataGrid::OnRefresh(wxCommandEvent& event)
{
  wxUnusedVar(event);
   DoRefresh(true);
}
/*---------------------------------------------------------------------------*/
void wxDataGrid::OnFilterSortUpdate(wxUpdateUIEvent& event)
{
   event.Skip();
}
/*---------------------------------------------------------------------------*/
wxMenu* wxDataGrid::CreateRightMenu()
{
   wxMenu* menu = wxSpecGrid::CreateRightMenu();

   menu->AppendSeparator();
   menu->Append(ID_MNU_FILTER, _("&Filter..."), wxEmptyString, wxITEM_NORMAL);
   menu->Append(ID_MNU_SORT, _("&Sort..."), wxEmptyString, wxITEM_NORMAL);
   menu->AppendSeparator();
   menu->Append(ID_MNU_REFRESH, _("&Refresh"), wxEmptyString, wxITEM_NORMAL);
   return menu;
}
/*---------------------------------------------------------------------------*/
wxGridCellBlobRenderer::wxGridCellBlobRenderer(bool displaynullvalue,
                                               const wxString& defaultstring)
{
   m_IsNullValueDisplayed = displaynullvalue;
   m_DefaultString = defaultstring;
   if (defaultstring == wxEmptyString)
      m_DefaultString = _T("(blob)");
}
/*---------------------------------------------------------------------------*/
wxString wxGridCellBlobRenderer::GetString(const wxGrid& grid, int row, int col)
{
   wxString text;

   text = m_DefaultString;
   if (grid.GetTable()->IsEmptyCell(row, col))
   {
      if (m_IsNullValueDisplayed)
         text = _T("(null)");
      else
         text = wxEmptyString;
   }
   return text;
}
/*---------------------------------------------------------------------------*/
void wxGridCellBlobRenderer::Draw(wxGrid& grid, wxGridCellAttr& attr, wxDC& dc,
                             const wxRect& rect, int row, int col,
                             bool isSelected)
{
   int hAlign, vAlign;
   wxRect l_rect;

   // wxGridCellStringRenderer::Draw(grid, attr, dc, rect, row, col, isSelected);
   wxGridCellRenderer::Draw(grid, attr, dc, rect, row, col, isSelected);

   SetTextColoursAndFont(grid, attr, dc, isSelected);

   // draw the text right aligned by default
   attr.GetAlignment(&hAlign, &vAlign);
   hAlign = wxALIGN_LEFT;

   l_rect = rect;
   l_rect.Inflate(-1);


   grid.DrawTextRectangle(dc, GetString(grid, row, col), l_rect, hAlign, vAlign);

}
/*---------------------------------------------------------------------------*/
wxSize wxGridCellBlobRenderer::GetBestSize(wxGrid& grid, wxGridCellAttr& attr,
                                           wxDC& dc, int row, int col)
{
    return DoGetBestSize(attr, dc, GetString(grid, row, col));
}
/*---------------------------------------------------------------------------*/
BEGIN_EVENT_TABLE(wxGridCellBlobEditor, wxEvtHandler)
   EVT_BUTTON(wxID_ANY, wxGridCellBlobEditor::OnBtnClick)
END_EVENT_TABLE()
/*---------------------------------------------------------------------------*/
wxGridCellBlobEditor::wxGridCellBlobEditor() : wxGridCellEditor(), wxEvtHandler()
{
   m_Row = m_Col = 0;
   m_Grid = NULL;
}
/*---------------------------------------------------------------------------*/
void wxGridCellBlobEditor::Create(wxWindow* parent, wxWindowID id,
                          wxEvtHandler* evtHandler)
{
   m_control = new wxButton(parent, id, _T("..."), wxDefaultPosition,
                            wxDefaultSize, wxBU_EXACTFIT);

   wxGridCellEditor::Create(parent, id, evtHandler);
}
/*---------------------------------------------------------------------------*/
void wxGridCellBlobEditor::PaintBackground(const wxRect& rectCell, wxGridCellAttr *attr)
{
   // erase the background because we might not fill the cell
   wxClientDC dc(m_control->GetParent());
   wxWindow* gridWindow = wxDynamicCast(m_control->GetParent(), wxWindow);
   if (gridWindow)
   {
      wxGrid* grid = wxDynamicCast(gridWindow->GetParent(), wxGrid);
      if (grid)
      {
         grid->PrepareDC(dc);

#if wxCHECK_VERSION(2, 9, 5)
         wxGridCellEditor::PaintBackground(dc, rectCell, *attr);
#else
         wxGridCellEditor::PaintBackground(rectCell, attr);
#endif // wxCHECK_VERSION(2, 9, 5)

         wxGridCellRenderer *renderer = attr->GetRenderer(grid, m_Row, m_Col);
         renderer->Draw(*grid, *attr, dc, rectCell, m_Row, m_Col, false);
         renderer->DecRef();
      }
   }
   else
   {
#if wxCHECK_VERSION(2, 9, 5)
      wxGridCellEditor::PaintBackground(dc, rectCell, *attr);
#else
      wxGridCellEditor::PaintBackground(rectCell, attr);
#endif // wxCHECK_VERSION(2, 9, 5)
   }
   // redraw the control we just painted over
   m_control->Refresh();
}
/*---------------------------------------------------------------------------*/
void wxGridCellBlobEditor::BeginEdit(int row, int col, wxGrid* grid)
{
   wxASSERT_MSG(m_control,
                wxT("The wxGridCellBlobEditor must be created first!"));

   m_Row = row;
   m_Col = col;
   m_Grid = grid;

   m_control->PushEventHandler(this);

   m_control->SetFocus();

}
/*---------------------------------------------------------------------------*/
#if wxCHECK_VERSION(2,9,0)
bool wxGridCellBlobEditor::EndEdit(int row, int col, const wxGrid* grid,
                                   const wxString& oldval, wxString* newval)
{
  wxUnusedVar(row);
  wxUnusedVar(col);
  wxUnusedVar(grid);
  wxUnusedVar(oldval);
  wxUnusedVar(newval);
  m_control->PopEventHandler();

   m_Row = m_Col = 0;
   m_Grid = NULL;

   return false;
}

void wxGridCellBlobEditor::ApplyEdit(int row, int col, wxGrid* grid)
{
  wxUnusedVar(row);
  wxUnusedVar(col);
  wxUnusedVar(grid);
}
#else
bool wxGridCellBlobEditor::EndEdit(int row, int col, wxGrid* grid)
{
  wxUnusedVar(row);
  wxUnusedVar(col);
  wxUnusedVar(grid);
  m_control->PopEventHandler();

  m_Row = m_Col = 0;
  m_Grid = NULL;

  return false;
}
#endif

/*---------------------------------------------------------------------------*/
void wxGridCellBlobEditor::Reset()
{
   // do nothing
}
/*---------------------------------------------------------------------------*/
wxGridCellEditor* wxGridCellBlobEditor::Clone() const
{
   wxGridCellBlobEditor* editor = new wxGridCellBlobEditor;

   return editor;
}
/*---------------------------------------------------------------------------*/
wxString wxGridCellBlobEditor::GetValue() const
{
   return wxEmptyString;
}
/*---------------------------------------------------------------------------*/
void wxGridCellBlobEditor::SetSize(const wxRect& rectOrig)
{
   wxRect rect(rectOrig);

   // Make the edit control large enough to allow for internal margins
   //
   // TODO: remove this if the text ctrl sizing is improved esp. for unix
   //
#if defined(__WXGTK__)
   if (rect.x != 0)
   {
      rect.x += 1;
      rect.y += 1;
      rect.width -= 1;
      rect.height -= 1;
   }
#elif defined(__WXMSW__)
   if (rect.x == 0)
      rect.x += 2;
   else
      rect.x += 3;

   if (rect.y == 0)
      rect.y += 2;
   else
      rect.y += 3;

   rect.width -= 2;
   rect.height -= 2;
#else
   int extra_x = (rect.x > 2) ? 2 : 1;
   int extra_y = (rect.y > 2) ? 2 : 1;

   #if defined(__WXMOTIF__)
   extra_x *= 2;
   extra_y *= 2;
   #endif

   rect.SetLeft(wxMax(0, rect.x - extra_x));
   rect.SetTop(wxMax(0, rect.y - extra_y));
   rect.SetRight(rect.GetRight() + 2 * extra_x);
   rect.SetBottom(rect.GetBottom() + 2 * extra_y);
#endif
   wxSize size = m_control->GetBestSize();

   if (rect.width > size.GetWidth())
   {
      rect.x += rect.width - size.GetWidth();
      rect.width = size.GetWidth();
   }
   wxGridCellEditor::SetSize(rect);
}
/*---------------------------------------------------------------------------*/
void wxGridCellBlobEditor::OnBtnClick(wxCommandEvent& event)
{
  wxUnusedVar(event);
   if (m_Grid)
   {
      wxGridCellBlobEditorEvent evt;
      evt.SetEventType(wxEVT_GRID_BLOBEDIT);
      evt.SetId(m_Grid->GetId());
      evt.SetRow(m_Row);
      evt.SetCol(m_Col);
      evt.SetGrid(m_Grid);

      m_Grid->GetEventHandler()->ProcessEvent(evt);
   }

}
/*---------------------------------------------------------------------------*/
DEFINE_EVENT_TYPE(wxEVT_GRID_BLOBEDIT)

IMPLEMENT_DYNAMIC_CLASS(wxGridCellBlobEditorEvent, wxNotifyEvent)
/*---------------------------------------------------------------------------*/
wxGridCellBlobEditorEvent::wxGridCellBlobEditorEvent(wxEventType commandType,
                                                     int id) :
                           wxNotifyEvent(commandType, id)
{
   m_Row = m_Col = 0;
   m_Grid = NULL;
}
/*---------------------------------------------------------------------------*/
wxGridCellBlobEditorEvent::wxGridCellBlobEditorEvent(const wxGridCellBlobEditorEvent& event)
{
   m_Row = event.m_Row;
   m_Col = event.m_Col;
   m_Grid = event.m_Grid;
}
/*---------------------------------------------------------------------------*/
