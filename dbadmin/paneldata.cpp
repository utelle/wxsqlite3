/*---------------------------------------------------------------------------*/
/* Logiciel de gestion de fichier de bases de données SQLite                 */
/*---------------------------------------------------------------------------*/
/* Projet  : wxSQLitePlus                              Version  : 0.3.0.0    */
/* Fichier : paneldata.cpp                                                   */
/* Auteur  : Fred Cailleau-Lepetit                     Date     : 07/09/2008 */
/* email   : softinthebox@free.fr                      Révision : 01/02/2009 */
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
#pragma implementation "paneldata.h"
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
#include "wxsqliteplusapp.h"
#include "specgrid.h"
#include "paneldata.h"
/*---------------------------------------------------------------------------*/
#define ID_DATATOOLBAR  15001
#define ID_DATAGRID     15002
/*---------------------------------------------------------------------------*/
IMPLEMENT_DYNAMIC_CLASS(wxPanelData, wxPanel)

BEGIN_EVENT_TABLE(wxPanelData, wxPanel)
   EVT_MENU(ID_MNU_FILTER, wxPanelData::OnMnuFilterClick)
   EVT_MENU(ID_MNU_SORT, wxPanelData::OnMnuSortClick)
   EVT_MENU(ID_MNU_REFRESH, wxPanelData::OnMnuRefreshClick)
   EVT_UPDATE_UI(wxID_STATIC, wxPanelData::OnStaticUpdate)
END_EVENT_TABLE()
/*---------------------------------------------------------------------------*/
wxPanelData::wxPanelData()
{
   Init();
}
/*---------------------------------------------------------------------------*/
wxPanelData::wxPanelData(wxWindow* parent, wxWindowID id, const wxPoint& pos,
                         const wxSize& size, long style)
{
   Init();
   Create(parent, id, pos, size, style);
}
/*---------------------------------------------------------------------------*/
bool wxPanelData::Create(wxWindow* parent, wxWindowID id, const wxPoint& pos,
                         const wxSize& size, long style)
{
   wxPanel::Create(parent, id, pos, size, style);

   CreateControls();
   return true;
}
/*---------------------------------------------------------------------------*/
wxPanelData::~wxPanelData()
{
}
/*---------------------------------------------------------------------------*/
void wxPanelData::SetDbTableViewName(wxSQLite3Database* db,
                                     const wxString objectname,
                                     const wxString& base)
{
   if (m_DataGrid)
      m_DataGrid->SetDbTableViewName(db, objectname, base);
}
/*---------------------------------------------------------------------------*/
void wxPanelData::Init()
{
   m_active = NULL;
   m_DataGrid = NULL;
}
/*---------------------------------------------------------------------------*/
void wxPanelData::CreateControls()
{
   wxBitmap BitmapDisabled;

   wxBoxSizer* bSizer1 = new wxBoxSizer(wxVERTICAL);
   SetSizer(bSizer1);

   wxToolBar* iToolBar1 = new wxToolBar(this, ID_DATATOOLBAR, wxDefaultPosition,
                                        wxDefaultSize,
                                        wxTB_FLAT|wxTB_HORIZONTAL|wxTB_NODIVIDER);
   wxBitmap filterBmp(wxGetApp().GetBmp(ID_BMP_FILTER));
   iToolBar1->AddTool(ID_MNU_FILTER, _("Filter"), filterBmp, BitmapDisabled,
                      wxITEM_NORMAL, _("Filter"), _("Filter"));
   wxBitmap sortBmp(wxGetApp().GetBmp(ID_BMP_SORT));
   iToolBar1->AddTool(ID_MNU_SORT, _("Sort"), sortBmp, BitmapDisabled,
                      wxITEM_NORMAL, _("Sort"), _("Sort"));
   wxBitmap refreshBmp(wxGetApp().GetBmp(ID_BMP_REFRESH));
   iToolBar1->AddTool(ID_MNU_REFRESH, _("Refresh"), refreshBmp, BitmapDisabled,
                      wxITEM_NORMAL, _("Refresh"), _("Refresh"));
   iToolBar1->AddSeparator();
   m_active = new wxStaticText(iToolBar1, wxID_STATIC, wxEmptyString,
                               wxDefaultPosition, wxSize(-1, 20), 0);
   iToolBar1->AddControl(m_active);
   iToolBar1->Realize();
   bSizer1->Add(iToolBar1, 0, wxGROW, 0);

   m_DataGrid = new wxDataGrid(this, ID_DATAGRID, wxDefaultPosition, wxDefaultSize);
   m_DataGrid->SetDefaultColSize(50);
   m_DataGrid->SetDefaultRowSize(25);
   m_DataGrid->SetColLabelSize(25);
   m_DataGrid->SetRowLabelSize(50);

   bSizer1->Add(m_DataGrid, 1, wxGROW, 0);
}
/*---------------------------------------------------------------------------*/
void wxPanelData::OnStaticUpdate(wxUpdateUIEvent& event)
{
  wxUnusedVar(event);
   wxString tmp;

   if (m_DataGrid->IsFiltered())
      tmp = _("Filtered");
   if (m_DataGrid->IsSorted())
   {
      if (!tmp.IsEmpty())
         tmp += _T(", ");
      tmp += _("Sorted");
   }
   if (tmp != m_active->GetLabel())
   {
      m_active->SetLabel(tmp);
   }
}
/*---------------------------------------------------------------------------*/
void wxPanelData::OnMnuFilterClick(wxCommandEvent& event)
{
  wxUnusedVar(event);
   if (m_DataGrid)
      m_DataGrid->DoFilter();
}
/*---------------------------------------------------------------------------*/
void wxPanelData::OnMnuSortClick(wxCommandEvent& event)
{
  wxUnusedVar(event);
   if (m_DataGrid)
      m_DataGrid->DoSort();
}
/*---------------------------------------------------------------------------*/
void wxPanelData::OnMnuRefreshClick(wxCommandEvent& event)
{
  wxUnusedVar(event);
   DoRefresh(true);
}
/*---------------------------------------------------------------------------*/
void wxPanelData::DoRefresh(bool usefilter)
{
   if (m_DataGrid)
      m_DataGrid->DoRefresh(usefilter);
}
/*---------------------------------------------------------------------------*/
bool wxPanelData::HasFocus()
{
   if (m_DataGrid)
      return m_DataGrid->HasFocus();
   return false;
}
/*---------------------------------------------------------------------------*/
