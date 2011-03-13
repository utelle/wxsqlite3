/*---------------------------------------------------------------------------*/
/* Logiciel de gestion de fichier de bases de données SQLite                 */
/*---------------------------------------------------------------------------*/
/* Projet  : wxSQLitePlus                              Version  : 0.2.3.0    */
/* Fichier : sqlhistory.cpp                                                  */
/* Auteur  : Fred Cailleau-Lepetit                     Date     : 26/08/2007 */
/* email   : softinthebox@free.fr                      Révision : 09/11/2008 */
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
#pragma implementation "sqlhistory.h"
#endif

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <wx/wxsqlite3.h>
/*---------------------------------------------------------------------------*/
#include "sqlhistory.h"
#include "sqlite3table.h"
#include "wxsqliteplusapp.h"
/*---------------------------------------------------------------------------*/
#define ID_HITORYGRID 15001
/*---------------------------------------------------------------------------*/
IMPLEMENT_DYNAMIC_CLASS(wxSQLHistory, wxDialog)

BEGIN_EVENT_TABLE(wxSQLHistory, wxDialog)
   EVT_GRID_CELL_LEFT_DCLICK(wxSQLHistory::OnCellLeftDClick)
   EVT_BUTTON(wxID_OK, wxSQLHistory::OnOkClick)
END_EVENT_TABLE()
/*---------------------------------------------------------------------------*/
wxSQLHistory::wxSQLHistory()
{
   Init();
}
/*---------------------------------------------------------------------------*/
wxSQLHistory::wxSQLHistory(wxWindow* parent, wxWindowID id,
                           const wxString& caption, const wxPoint& pos,
                           const wxSize& size, long style)
{
   Init();
   Create(parent, id, caption, pos, size, style);
}
/*---------------------------------------------------------------------------*/
bool wxSQLHistory::Create(wxWindow* parent, wxWindowID id,
                          const wxString& caption, const wxPoint& pos,
                          const wxSize& size, long style)
{
   SetExtraStyle(wxWS_EX_BLOCK_EVENTS);
   wxDialog::Create(parent, id, caption, pos, size, style);

   CreateControls();
   SetIcon(wxGetApp().GetIcon(ID_ICO_SQLHISTO));

   if (GetSizer())
   {
      GetSizer()->SetSizeHints(this);
   }
   Centre();
   return true;
}
/*---------------------------------------------------------------------------*/
wxSQLHistory::~wxSQLHistory()
{
}
/*---------------------------------------------------------------------------*/
void wxSQLHistory::SetResultSet(wxSQLite3ResultSet& resultSet)
{
   wxColour oddColour(wxGetApp().GetParamStr(PARAM_ODDROWCOLOR));
   wxGridSQLite3Table* table = new wxGridSQLite3Table(&resultSet);
   table->SetAttrProvider(new OddRowsGridCellAttrProvider(oddColour));
   m_HistoryGrid->SetTable((wxGridTableBase*)table, true);
   table->AdaptColumnsSize();
   m_HistoryGrid->SetSelectionMode(wxGrid::wxGridSelectRows);
   m_HistoryGrid->SetDefaultColSize(50);
   m_HistoryGrid->SetDefaultRowSize(50);
   m_HistoryGrid->SetColLabelSize(25);
   m_HistoryGrid->SetRowLabelSize(0);
   m_HistoryGrid->SetColSize(0, 75);
   m_HistoryGrid->SetColSize(1, 430);
   m_HistoryGrid->SetColSize(2, 50);
   m_HistoryGrid->SetDefaultSelection();
   m_HistoryGrid->ForceRefresh();
   resultSet.Finalize();
}
/*---------------------------------------------------------------------------*/
void wxSQLHistory::Init()
{
    m_HistoryGrid = NULL;
}
/*---------------------------------------------------------------------------*/
void wxSQLHistory::CreateControls()
{
   wxBoxSizer* bSizer1 = new wxBoxSizer(wxVERTICAL);
   SetSizer(bSizer1);

   m_HistoryGrid = new wxSpecGrid(this, ID_HITORYGRID, wxDefaultPosition,
                                  wxSize(600, 400),
                                  wxNO_BORDER|wxHSCROLL|wxVSCROLL);
   bSizer1->Add(m_HistoryGrid, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

   wxStdDialogButtonSizer* dlgBtnSizer1 = new wxStdDialogButtonSizer;

   bSizer1->Add(dlgBtnSizer1, 0, wxALIGN_RIGHT|wxALL, 5);
   wxButton* btnOk = new wxButton(this, wxID_OK, _("&OK"), wxDefaultPosition, wxDefaultSize, 0);
   btnOk->SetDefault();
   dlgBtnSizer1->AddButton(btnOk);

   wxButton* btnCancel = new wxButton(this, wxID_CANCEL, _("&Cancel"), wxDefaultPosition, wxDefaultSize, 0);
   dlgBtnSizer1->AddButton(btnCancel);

   dlgBtnSizer1->Realize();

   m_HistoryGrid->EnableEditing(true);
}
/*---------------------------------------------------------------------------*/
bool wxSQLHistory::ShowToolTips()
{
    return true;
}
/*---------------------------------------------------------------------------*/
void wxSQLHistory::OnCellLeftDClick(wxGridEvent& event)
{
  wxUnusedVar(event);
   if (PopulateStement())
      EndModal(wxID_OK);
}
/*---------------------------------------------------------------------------*/
void wxSQLHistory::OnOkClick(wxCommandEvent& event)
{
   if (PopulateStement())
      event.Skip();
}
/*---------------------------------------------------------------------------*/
bool wxSQLHistory::PopulateStement()
{
   m_SqlStatement = m_HistoryGrid->GetCellValue(m_HistoryGrid->GetGridCursorRow(), 1);
   return !m_SqlStatement.IsEmpty();
}
/*---------------------------------------------------------------------------*/
