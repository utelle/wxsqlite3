/*---------------------------------------------------------------------------*/
/* Logiciel de gestion de fichier de bases de données SQLite                 */
/*---------------------------------------------------------------------------*/
/* Projet  : wxSQLitePlus                              Version  : 0.2.3.0    */
/* Fichier : describedlg.cpp                                                 */
/* Auteur  : Fred Cailleau-Lepetit                     Date     : 08/09/2007 */
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
#pragma implementation "describedlg.h"
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
#include "describedlg.h"
#include "wxsqliteplusapp.h"
#include "specgrid.h"
#include "sqlite3table.h"
/*---------------------------------------------------------------------------*/
#define ID_DESCRIBE_GRID 15001
/*---------------------------------------------------------------------------*/
IMPLEMENT_DYNAMIC_CLASS(wxDescribeDlg, wxDialog)

BEGIN_EVENT_TABLE(wxDescribeDlg, wxDialog)
END_EVENT_TABLE()
/*---------------------------------------------------------------------------*/
wxDescribeDlg::wxDescribeDlg()
{
   Init();
}
/*---------------------------------------------------------------------------*/
wxDescribeDlg::wxDescribeDlg(wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style)
{
   Init();
   Create(parent, id, caption, pos, size, style);
}
/*---------------------------------------------------------------------------*/
bool wxDescribeDlg::Create(wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style)
{
   SetExtraStyle(wxWS_EX_BLOCK_EVENTS);
   wxDialog::Create(parent, id, caption, pos, size, style);

   CreateControls();
   SetIcon(wxGetApp().GetIcon(ID_ICO_FIELD2));
   Centre();

   return true;
}
/*---------------------------------------------------------------------------*/
wxDescribeDlg::~wxDescribeDlg()
{
}
/*---------------------------------------------------------------------------*/
void wxDescribeDlg::Init()
{
   m_DescribeName = NULL;
   m_DescribeGrid = NULL;
}
/*---------------------------------------------------------------------------*/
void wxDescribeDlg::CreateControls()
{
   wxBoxSizer* bSizer1 = new wxBoxSizer(wxVERTICAL);
   SetSizer(bSizer1);

   m_DescribeName = new wxStaticText(this, wxID_STATIC, wxEmptyString,
                                     wxDefaultPosition, wxDefaultSize, 0);
   bSizer1->Add(m_DescribeName, 0, wxALIGN_LEFT|wxLEFT|wxTOP, 20);

   bSizer1->Add(5, 5, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 2);

   m_DescribeGrid = new wxSpecGrid(this, ID_DESCRIBE_GRID, wxDefaultPosition,
                                   wxDefaultSize, wxHSCROLL|wxVSCROLL);
   m_DescribeGrid->SetDefaultColSize(50);
   m_DescribeGrid->SetDefaultRowSize(25);
   m_DescribeGrid->SetColLabelSize(25);
   m_DescribeGrid->SetRowLabelSize(0);
   bSizer1->Add(m_DescribeGrid, 1, wxGROW|wxLEFT|wxRIGHT|wxBOTTOM, 20);

   wxButton* btnCancel = new wxButton(this, wxID_CANCEL, _("&Cancel"),
                                      wxDefaultPosition, wxDefaultSize, 0);
   btnCancel->SetDefault();
   bSizer1->Add(btnCancel, 0, wxALIGN_RIGHT|wxRIGHT|wxBOTTOM, 20);
}
/*---------------------------------------------------------------------------*/
bool wxDescribeDlg::ShowToolTips()
{
   return true;
}
/*---------------------------------------------------------------------------*/
void wxDescribeDlg::Describe(wxSQLite3Database* db, const wxString& name,
                             const wxString& base)
{
   wxGridSQLite3TableBase* table;
   wxColour oddColour(wxGetApp().GetParamStr(PARAM_ODDROWCOLOR));

   m_DescribeName->SetLabel(name);
   table = new wxGridTblColumnsTable(db, name, base);
   table->SetAttrProvider(new OddRowsGridCellAttrProvider(oddColour));
   m_DescribeGrid->SetTable((wxGridTableBase*)table, true);
   table->AdaptColumnsSize();
   m_DescribeGrid->SetRowLabelSize(0);
   m_DescribeGrid->SetDefaultSelection();
   m_DescribeGrid->ForceRefresh();
}
/*---------------------------------------------------------------------------*/
