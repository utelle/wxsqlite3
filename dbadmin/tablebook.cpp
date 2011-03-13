/*---------------------------------------------------------------------------*/
/* Logiciel de gestion de fichier de bases de données SQLite                 */
/*---------------------------------------------------------------------------*/
/* Projet  : wxSQLitePlus                              Version  : 0.2.2.0    */
/* Fichier : tablebook.cpp                                                   */
/* Auteur  : Fred Cailleau-Lepetit                     Date     : 23/07/2007 */
/* email   : softinthebox@free.fr                      Révision : 07/09/2008 */
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
#pragma implementation "tablebook.h"
#endif

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <wx/aui/auibook.h>
/*---------------------------------------------------------------------------*/
#include "tablebook.h"
#include "wxsqliteplusapp.h"
#include "sqliteplusframe.h"
#include "sqlite3table.h"
#include "paneldata.h"
#include "specgrid.h"
/*---------------------------------------------------------------------------*/
#define ID_TABLEBOOK       12001
#define ID_PAGECOLUMNS     12002
#define ID_PAGEDATA        12003
#define ID_PAGEFORIEGNKEY  12004
#define ID_PAGETRIGGERS    12005
#define ID_PAGEINDEXES     12006
#define ID_PAGEDDL         12007
/*---------------------------------------------------------------------------*/
IMPLEMENT_DYNAMIC_CLASS(wxTableBook, wxDbBook)

BEGIN_EVENT_TABLE(wxTableBook, wxDbBook)
   EVT_AUINOTEBOOK_PAGE_CHANGING(ID_TABLEBOOK, wxTableBook::OnTablebookPageChanging)
   EVT_MENU(wxID_COPY, wxTableBook::OnCopyClick)
   EVT_UPDATE_UI(wxID_COPY, wxTableBook::OnCopyUpdate)
   EVT_MENU(ID_CMD_ED_REFRESH, wxTableBook::OnEdRefresh)
END_EVENT_TABLE()
/*---------------------------------------------------------------------------*/
wxTableBook::wxTableBook()
{
   Init();
}
/*---------------------------------------------------------------------------*/
wxTableBook::wxTableBook(wxWindow* parent, wxWindowID id, const wxPoint& pos,
                         const wxSize& size, long style)
{
   Init();
   Create(parent, id, pos, size, style);
}
/*---------------------------------------------------------------------------*/
bool wxTableBook::Create(wxWindow* parent, wxWindowID id, const wxPoint& pos,
                         const wxSize& size, long style)
{
   wxDbBook::Create( parent, id, pos, size, style );

   CreateControls();
   if (GetSizer())
   {
      GetSizer()->SetSizeHints(this);
   }
   return true;
}
/*---------------------------------------------------------------------------*/
wxTableBook::~wxTableBook()
{
}
/*---------------------------------------------------------------------------*/
void wxTableBook::Init()
{
   m_Book = NULL;
   m_PageColumns = NULL;
   m_PageData = NULL;
   m_PageForeignKey = NULL;
   m_PageTriggers = NULL;
   m_PageIndexes = NULL;
   m_PageDdl = NULL;
   m_InitData = true;
}
/*---------------------------------------------------------------------------*/
void wxTableBook::CreateControls()
{
   wxBoxSizer* bSizer = new wxBoxSizer(wxHORIZONTAL);
   SetSizer(bSizer);

   m_Book = new wxAuiNotebook(this, ID_TABLEBOOK, wxDefaultPosition,
                              wxDefaultSize,
                              wxAUI_NB_TOP|wxAUI_NB_TAB_SPLIT|wxAUI_NB_TAB_MOVE);

   m_PageColumns = new wxSpecGrid(m_Book, ID_PAGECOLUMNS, wxDefaultPosition,
                                  wxDefaultSize, wxHSCROLL|wxVSCROLL);
   m_PageColumns->SetDefaultColSize(50);
   m_PageColumns->SetDefaultRowSize(25);
   m_PageColumns->SetColLabelSize(25);

   wxBitmap m_PageColumnsBitmap(wxGetApp().GetBmp(ID_BMP_FIELD));
   m_Book->AddPage(m_PageColumns, _("Columns"), false, m_PageColumnsBitmap);

   m_PageData = new wxPanelData(m_Book, ID_PAGEDATA, wxDefaultPosition, wxDefaultSize);

   wxBitmap m_PageDataBitmap(wxGetApp().GetBmp(ID_BMP_TABLE));
   m_Book->AddPage(m_PageData, _("Data"), false, m_PageDataBitmap);

   m_PageForeignKey = new wxSpecGrid(m_Book, ID_PAGEFORIEGNKEY,
                                     wxDefaultPosition, wxDefaultSize,
                                     wxHSCROLL|wxVSCROLL );
   m_PageForeignKey->SetDefaultColSize(50);
   m_PageForeignKey->SetDefaultRowSize(25);
   m_PageForeignKey->SetColLabelSize(25);

   wxBitmap m_PageForeignKeyBitmap(wxGetApp().GetBmp(ID_BMP_FIELD2));
   m_Book->AddPage(m_PageForeignKey, _("Foreign key"), false, m_PageForeignKeyBitmap);

   m_PageTriggers = new wxSpecGrid(m_Book, ID_PAGETRIGGERS, wxDefaultPosition,
                                   wxDefaultSize, wxHSCROLL|wxVSCROLL);
   m_PageTriggers->SetDefaultColSize(50);
   m_PageTriggers->SetDefaultRowSize(25);
   m_PageTriggers->SetColLabelSize(25);

   wxBitmap m_PageTriggersBitmap(wxGetApp().GetBmp(ID_BMP_TRIGGER2));
   m_Book->AddPage(m_PageTriggers, _("Triggers"), false, m_PageTriggersBitmap);

   m_PageIndexes = new wxSpecGrid(m_Book, ID_PAGEINDEXES, wxDefaultPosition,
                                  wxDefaultSize, wxHSCROLL|wxVSCROLL);
   m_PageIndexes->SetDefaultColSize(50);
   m_PageIndexes->SetDefaultRowSize(25);
   m_PageIndexes->SetColLabelSize(25);

   wxBitmap m_PageIndexesBitmap(wxGetApp().GetBmp(ID_BMP_INDEXE));
   m_Book->AddPage(m_PageIndexes, _("Indexes"), false, m_PageIndexesBitmap);

   m_PageDdl = new wxDDLEditor(m_Book, ID_PAGEDDL);

   wxBitmap m_PageDdlBitmap(wxGetApp().GetBmp(ID_BMP_RUNSCRIPT));
   m_Book->AddPage(m_PageDdl, _("DDL"), false, m_PageDdlBitmap);

   bSizer->Add(m_Book, 1, wxGROW, 0);
}
/*---------------------------------------------------------------------------*/
bool wxTableBook::ShowToolTips(){return true;}
/*---------------------------------------------------------------------------*/
void wxTableBook::OnTablebookPageChanging( wxAuiNotebookEvent& event )
{
   if (m_InitData)
   {  // Vérifier si c'est l'onglet Data qui doit être affiché
      if (_T("Data") == m_Book->GetPageText(event.GetSelection()))
      {  // Si oui lancer la sélection des données de la table
         m_InitData = false;
         RefreshData();
      }
   }
   event.Skip();
}
/*---------------------------------------------------------------------------*/
void wxTableBook::SetDbObjectName(wxSQLite3Database* db,
                                 const wxString objectname, const wxString& base)
{
   wxDbBook::SetDbObjectName(db, objectname, base);
   m_PageData->SetDbTableViewName(db, objectname, base);
   RefreshStruct();
}
/*---------------------------------------------------------------------------*/
void wxTableBook::RefreshDbObject()
{
   RefreshStruct();
   if (_T("Data") == m_Book->GetPageText(m_Book->GetSelection()))
      RefreshData();
   else
      m_InitData = true;
}
/*---------------------------------------------------------------------------*/
void wxTableBook::RefreshStruct()
{
   if (!m_db || m_DbObjectName.IsEmpty())
      return;
   // Remplir les wxGrid avec les paramètres de la table
   wxSQLitePlusFrame* frame;
   wxString sql, basename;
   wxSQLite3ResultSet resultSet;
   wxGridSQLite3TableBase* table;
   wxColour oddColour(wxGetApp().GetParamStr(PARAM_ODDROWCOLOR));

   if (m_Base != wxEmptyString)
      basename = m_Base;
   else
      basename = _T("main");
   try
   {
      // remplissage de la grille des colonnes
      m_PageColumns->SetTable(&g_EmptyTable);
      m_PageColumns->ForceRefresh();
      table = new wxGridTblColumnsTable(m_db, m_DbObjectName, basename);
      table->SetAttrProvider(new OddRowsGridCellAttrProvider(oddColour));
      m_PageColumns->SetTable((wxGridTableBase*)table, true);
      table->AdaptColumnsSize();
      m_PageColumns->SetRowLabelSize(0);
      m_PageColumns->SetDefaultSelection();
      m_PageColumns-> ForceRefresh();
   }
   catch(wxSQLite3Exception& ex)
   {
      wxGetApp().ShowError(_T("RefreshStruct"), ex);
   }

   try
   {
      // remplissage de la grille des clés étrangères
      sql = wxString::Format(_T("PRAGMA %s.foreign_key_list(\"%s\");"),
                             basename.c_str(), m_DbObjectName.c_str());
      resultSet = m_db->ExecuteQuery(ToUTF8(sql));
      m_PageForeignKey->SetTable(&g_EmptyTable);
      m_PageForeignKey->ForceRefresh();
      table = new wxGridSQLite3Table(&resultSet);
      table->SetAttrProvider(new OddRowsGridCellAttrProvider(oddColour));
      m_PageForeignKey->SetTable((wxGridTableBase*)table, true);
      table->AdaptColumnsSize();
      m_PageForeignKey->SetRowLabelSize(0);
      m_PageForeignKey->SetDefaultSelection();
      m_PageForeignKey-> ForceRefresh();
      resultSet.Finalize();
   }
   catch(wxSQLite3Exception& ex)
   {
      wxGetApp().ShowError(_T("RefreshStruct"), ex);
   }

   try
   {
      // remplissage de la grille des triggers
      m_PageTriggers->SetTable(&g_EmptyTable);
      m_PageTriggers->ForceRefresh();
      table = new wxGridTriggerTable(m_db, m_DbObjectName, basename);
      table->SetAttrProvider(new OddRowsGridCellAttrProvider(oddColour));
      m_PageTriggers->SetTable((wxGridTableBase*)table, true);
      table->AdaptColumnsSize();
      m_PageTriggers->SetRowLabelSize(0);
      m_PageTriggers->SetDefaultSelection();
      m_PageTriggers-> ForceRefresh();
   }
   catch(wxSQLite3Exception& ex)
   {
      wxGetApp().ShowError(_T("RefreshStruct"), ex);
   }

   try
   {
      // remplissage de la grille des indexes
      m_PageIndexes->SetTable(&g_EmptyTable);
      m_PageIndexes->ForceRefresh();
      table = new wxGridTblIndexesTable(m_db, m_DbObjectName, basename);
      table->SetAttrProvider(new OddRowsGridCellAttrProvider(oddColour));
      m_PageIndexes->SetTable((wxGridTableBase*)table, true);
      table->AdaptColumnsSize();
      m_PageIndexes->SetRowLabelSize(0);
      m_PageIndexes->SetDefaultSelection();
      m_PageIndexes-> ForceRefresh();
   }
   catch(wxSQLite3Exception& ex)
   {
      wxGetApp().ShowError(_T("RefreshStruct"), ex);
   }

   frame = (wxSQLitePlusFrame*)wxGetApp().GetTopWindow();
   m_PageDdl->SetValue(frame->GetDbObjectDDL(otTable, m_DbObjectName, basename));

}
/*---------------------------------------------------------------------------*/
void wxTableBook::RefreshData()
{
   m_PageData->DoRefresh();
}
/*---------------------------------------------------------------------------*/
void wxTableBook::OnCopyClick(wxCommandEvent& event)
{
   wxWindow* window = FindFocus();

   if (window && ((window == m_PageDdl)||
       (m_PageColumns && m_PageColumns->HasFocus())||
       (m_PageData && m_PageData->HasFocus())||
       (m_PageForeignKey && m_PageForeignKey->HasFocus())||
       (m_PageTriggers && m_PageTriggers->HasFocus())||
       (m_PageIndexes && m_PageIndexes->HasFocus())))
      window->GetEventHandler()->ProcessEvent(event);
}
/*---------------------------------------------------------------------------*/
void wxTableBook::OnCopyUpdate(wxUpdateUIEvent& event)
{
   wxWindow* window = FindFocus();

   if (window && ((window == m_PageDdl)||
       (m_PageColumns && m_PageColumns->HasFocus())||
       (m_PageData && m_PageData->HasFocus())||
       (m_PageForeignKey && m_PageForeignKey->HasFocus())||
       (m_PageTriggers && m_PageTriggers->HasFocus())||
       (m_PageIndexes && m_PageIndexes->HasFocus())))
      window->GetEventHandler()->ProcessEvent(event);
   else
      event.Enable(false);
}
/*---------------------------------------------------------------------------*/
void wxTableBook::OnEdRefresh(wxCommandEvent& event)
{
  wxUnusedVar(event);
   m_PageDdl->InitStyle();
}
/*---------------------------------------------------------------------------*/
