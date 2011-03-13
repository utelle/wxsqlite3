/*---------------------------------------------------------------------------*/
/* Logiciel de gestion de fichier de bases de données SQLite                 */
/*---------------------------------------------------------------------------*/
/* Projet  : wxSQLitePlus                              Version  : 0.2.3.0    */
/* Fichier : addcolumn.cpp                                                   */
/* Auteur  : Fred Cailleau-Lepetit                     Date     : 28/12/2007 */
/* email   : softinthebox@free.fr                      Révision : 09/11/2008 */
/*---------------------------------------------------------------------------*/
/* Copyright (C) Fred Cailleau-Lepetit 2007-2008                             */
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
#pragma implementation "addcolumn.h"
#endif

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <wx/notebook.h>
/*---------------------------------------------------------------------------*/
#include "addcolumn.h"
#include "wxsqliteplusapp.h"
#include "sqliteplusframe.h"
#include "specgrid.h"
/*---------------------------------------------------------------------------*/
#define ID_TABLENAME       15001
#define ID_BOOK            15002
#define ID_PANELBOOK       15003
#define ID_COLUMNS         15004
#define ID_BTN_ADDCOLUMN   15005
#define ID_BTN_DELCOLUMN   15006
#define ID_DDL             15007
/*---------------------------------------------------------------------------*/
wxGridAddColumnsTable::wxGridAddColumnsTable()
{
}
/*---------------------------------------------------------------------------*/
void wxGridAddColumnsTable::SetExistingColumnsName(const wxArrayString& colsname)
{
   m_ExistingColumnsName = colsname;
}
/*---------------------------------------------------------------------------*/
bool wxGridAddColumnsTable::CheckName(const wxString& name, int row)
{
   if (wxGridColumnsTable::CheckName(name, row))
   {
      for (size_t i = 0; i < m_ExistingColumnsName.GetCount(); i++)
         if (m_ExistingColumnsName[i].Upper() == name.Upper())
            return false;
      return true;
   }
   return false;
}
/*---------------------------------------------------------------------------*/
IMPLEMENT_DYNAMIC_CLASS(wxAddColumnDialog, wxDialog)

BEGIN_EVENT_TABLE(wxAddColumnDialog, wxDialog)
   EVT_CHOICE(ID_TABLENAME, wxAddColumnDialog::OnTablenameSelected)
   EVT_NOTEBOOK_PAGE_CHANGING(ID_BOOK, wxAddColumnDialog::OnBookPageChanging)
   EVT_BUTTON(ID_BTN_ADDCOLUMN, wxAddColumnDialog::OnBtnAddcolumnClick)
   EVT_BUTTON(ID_BTN_DELCOLUMN, wxAddColumnDialog::OnBtnDelcolumnClick)
   EVT_UPDATE_UI(ID_BTN_DELCOLUMN, wxAddColumnDialog::OnBtnDelcolumnUpdate)
   EVT_BUTTON(wxID_OK, wxAddColumnDialog::OnOkClick)
END_EVENT_TABLE()
/*---------------------------------------------------------------------------*/
wxAddColumnDialog::wxAddColumnDialog()
{
   Init();
}
/*---------------------------------------------------------------------------*/
wxAddColumnDialog::wxAddColumnDialog(wxWindow* parent, wxWindowID id,
                                     const wxString& caption, const wxPoint& pos,
                                     const wxSize& size, long style)
{
    Init();
    Create(parent, id, caption, pos, size, style);
}
/*---------------------------------------------------------------------------*/
bool wxAddColumnDialog::Create(wxWindow* parent, wxWindowID id,
                               const wxString& caption, const wxPoint& pos,
                               const wxSize& size, long style)
{
   SetExtraStyle(wxWS_EX_BLOCK_EVENTS);
   wxDialog::Create(parent, id, caption, pos, size, style);

   CreateControls();
   SetIcon(wxGetApp().GetIcon(ID_ICO_TABLE));
   if (GetSizer())
   {
      GetSizer()->SetSizeHints(this);
   }
   Centre();
   return true;
}
/*---------------------------------------------------------------------------*/
wxAddColumnDialog::~wxAddColumnDialog()
{
   // if this line does not exist the program crash on GTK2
   m_GridColumns->SetTable(NULL);
}
/*---------------------------------------------------------------------------*/
void wxAddColumnDialog::SetDatabase(wxSQLite3Database* db, const wxString& base)
{
   m_Db = db;
   m_Base = base;
   if (!m_Db||!m_Db->IsOpen())
      return;
   m_ChoiceTableName->Clear();
   try
   {
      wxSQLite3ResultSet tblQRY;
      wxSQLitePlusFrame* frame;

      frame = (wxSQLitePlusFrame*)wxGetApp().GetTopWindow();

      tblQRY = frame->GetObjNameList(otTable, m_Base);

      while (tblQRY.NextRow())
         m_ChoiceTableName->Append(tblQRY.GetString(0).Lower());
      tblQRY.Finalize();
   }
   catch(wxSQLite3Exception& ex)
   {
      wxGetApp().ShowError(_T("SetDatabase"), ex);
   }
}
/*---------------------------------------------------------------------------*/
void wxAddColumnDialog::Init()
{
   m_ChoiceTableName = NULL;
   m_GridColumns = NULL;
   m_TextDdl = NULL;
   m_BtnAddColumn = NULL;
}
/*---------------------------------------------------------------------------*/
void wxAddColumnDialog::CreateControls()
{
   wxBoxSizer* bSizer1 = new wxBoxSizer(wxVERTICAL);
   SetSizer(bSizer1);

   wxBoxSizer* bSizer2 = new wxBoxSizer(wxHORIZONTAL);
   bSizer1->Add(bSizer2, 0, wxALIGN_LEFT|wxALL, 5);

   wxStaticText* sText1 = new wxStaticText(this, wxID_STATIC, _("&Table :"),
                                           wxDefaultPosition, wxDefaultSize, 0);
   bSizer2->Add(sText1, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

   wxArrayString m_ChoiceTableNameStrings;
   m_ChoiceTableName = new wxChoice(this, ID_TABLENAME, wxDefaultPosition,
                                    wxSize(200, -1),
                                    m_ChoiceTableNameStrings, 0);
   bSizer2->Add(m_ChoiceTableName, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

   wxNotebook* noteBook1 = new wxNotebook(this, ID_BOOK, wxDefaultPosition,
                                          wxDefaultSize, wxBK_DEFAULT);

   wxPanel* panel1 = new wxPanel(noteBook1, ID_PANELBOOK, wxDefaultPosition,
                                 wxDefaultSize, wxTAB_TRAVERSAL);
   wxBoxSizer* bSizer3 = new wxBoxSizer(wxVERTICAL);
   panel1->SetSizer(bSizer3);

   m_GridColumns = new wxGrid(panel1, ID_COLUMNS, wxDefaultPosition,
                              wxSize(700, 250), wxHSCROLL|wxVSCROLL);
   m_GridColumns->SetDefaultColSize(50);
   m_GridColumns->SetDefaultRowSize(25);
   m_GridColumns->SetColLabelSize(25);
   m_GridColumns->SetRowLabelSize(35);
   m_GridColumns->CreateGrid(0, 5, wxGrid::wxGridSelectCells);
   bSizer3->Add(m_GridColumns, 1, wxGROW|wxALL, 5);

   wxBoxSizer* bSizer4 = new wxBoxSizer(wxHORIZONTAL);
   bSizer3->Add(bSizer4, 0, wxALIGN_LEFT|wxALL, 5);
   m_BtnAddColumn = new wxButton(panel1, ID_BTN_ADDCOLUMN, _("Add Column"),
                                 wxDefaultPosition, wxDefaultSize, 0);
   bSizer4->Add(m_BtnAddColumn, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

   wxButton* btnDel = new wxButton(panel1, ID_BTN_DELCOLUMN, _("Remove Column"),
                                   wxDefaultPosition, wxDefaultSize, 0);
   bSizer4->Add(btnDel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

   noteBook1->AddPage(panel1, _("Columns"));

   m_TextDdl = new wxDDLEditor(noteBook1, ID_DDL);

   noteBook1->AddPage(m_TextDdl, _("DDL"));

   bSizer1->Add(noteBook1, 0, wxGROW|wxALL, 5);

   wxStdDialogButtonSizer* dlgBtnSizer1 = new wxStdDialogButtonSizer;

   bSizer1->Add(dlgBtnSizer1, 0, wxALIGN_RIGHT|wxALL, 5);
   wxButton* btnOk = new wxButton(this, wxID_OK, _("&OK"), wxDefaultPosition,
                                  wxDefaultSize, 0);
   btnOk->SetDefault();
   dlgBtnSizer1->AddButton(btnOk);

   wxButton* btnCancel = new wxButton(this, wxID_CANCEL, _("&Cancel"),
                                      wxDefaultPosition, wxDefaultSize, 0);
   dlgBtnSizer1->AddButton(btnCancel);

   dlgBtnSizer1->Realize();

   m_GridColumns->Connect(ID_COLUMNS, wxEVT_CHAR,
                          wxKeyEventHandler(wxAddColumnDialog::OnGridChar),
                          NULL, this);

   m_GridColumns->SetTable(&m_TableColumns);
   m_GridColumns->SetColSize(0, 190);
   m_GridColumns->SetColSize(1, 185);
   m_GridColumns->SetColSize(2, 70);
   m_GridColumns->SetColSize(3, 90);
   m_GridColumns->SetColSize(4, 120);
}
/*---------------------------------------------------------------------------*/
void wxAddColumnDialog::SetTable(const wxString& table)
{
   if (!m_Db||!m_Db->IsOpen())
      return;
   if (m_ChoiceTableName->SetStringSelection(table))
   {
      DoTablenameSelected();
      m_ChoiceTableName->Enable(false);
   }
}
/*---------------------------------------------------------------------------*/
void wxAddColumnDialog::OnBookPageChanging(wxNotebookEvent& event)
{
   if (event.GetOldSelection() == 0)
   {
      wxString ddl = GetAddColumnsDDL();

      if (ddl.IsEmpty())
         event.Veto();
      else
         m_TextDdl->SetValue(ddl);
   }
}
/*---------------------------------------------------------------------------*/
void wxAddColumnDialog::OnGridChar(wxKeyEvent& event)
{
   event.Skip();
}
/*---------------------------------------------------------------------------*/
void wxAddColumnDialog::OnBtnAddcolumnClick(wxCommandEvent& event)
{
  wxUnusedVar(event);
   m_GridColumns->AppendRows(1);
}
/*---------------------------------------------------------------------------*/
void wxAddColumnDialog::OnBtnDelcolumnClick(wxCommandEvent& event)
{
  wxUnusedVar(event);
   wxArrayInt rowsArray = m_GridColumns->GetSelectedRows();
   for (size_t i = rowsArray.GetCount(); i > 0; i--)
      m_GridColumns->DeleteRows(rowsArray[i - 1]);
}
/*---------------------------------------------------------------------------*/
void wxAddColumnDialog::OnBtnDelcolumnUpdate(wxUpdateUIEvent& event)
{
   event.Enable(m_GridColumns->GetSelectedRows().GetCount() > 0);
}
/*---------------------------------------------------------------------------*/
void wxAddColumnDialog::OnOkClick(wxCommandEvent& event)
{
   if (GetAddColumnsDDL().IsEmpty())
      return;
   event.Skip();
}
/*---------------------------------------------------------------------------*/
bool wxAddColumnDialog::ShowToolTips()
{
    return true;
}
/*---------------------------------------------------------------------------*/
void wxAddColumnDialog::OnTablenameSelected(wxCommandEvent& event)
{
   DoTablenameSelected();
   event.Skip();
}
/*---------------------------------------------------------------------------*/
wxString wxAddColumnDialog::GetAddColumnsDDL()
{
   wxString ddl;
   wxArrayString arrayString;

   arrayString = GetAddColumnsScript();

   for (size_t i = 0; i < arrayString.GetCount(); i++)
   {
      ddl += arrayString.Item(i);
      if ((int)i != m_TableColumns.GetNumberRows() - 1)
         ddl += _T("\n");
   }

   return ddl;
}
/*---------------------------------------------------------------------------*/
wxArrayString wxAddColumnDialog::GetAddColumnsScript()
{
   wxString ddl, tablename, sql, def;
   wxColumnCtrTable* column;
   wxArrayString arrayString, emptyArray;

   if (!m_Db||!m_Db->IsOpen())
      return emptyArray;

   tablename = m_ChoiceTableName->GetStringSelection();
   if (tablename.IsEmpty())
   {
      wxMessageBox(_("You have to select a table."),
                   _("Error"));
      m_ChoiceTableName->SetFocus();
      return emptyArray;
   }
   if (m_GridColumns->GetNumberRows() == 0)
   {
      wxMessageBox(_("You have to add column(s) for the table."),
                   _("Error"));
      m_BtnAddColumn->SetFocus();
      return emptyArray;
   }

   // Création du DDL
   sql = _T("ALTER TABLE \"");
   if (m_Base != wxEmptyString)
      sql += m_Base + _T(".");
   sql += tablename + _T("\" ADD COLUMN ");
   for (int i = 0; i < m_TableColumns.GetNumberRows(); i++)
   {
      ddl = sql;
      column = m_TableColumns.GetColumnCtrTable(i);
      ddl += _T("\"") + column->GetName() + _T("\" ");
      switch (column->GetType())
      {
         case cttIntegerAutoinc :
            if (!column->GetPrimaryKey())
            {
               wxMessageBox(_("A column with AUTOINCREMENT must be a primary key."),
                            _("Error"));
               return emptyArray;
            }
         case cttInteger :
            ddl += _T("INTEGER"); break;
         case cttReal :
            ddl += _T("REAL"); break;
         case cttText :
            ddl += _T("TEXT"); break;
         case cttBlob :
            ddl += _T("BLOB"); break;
      }

      if (column->GetNotNull())
      {
         if (column->GetDefault() == wxEmptyString)
         {
            wxMessageBox(_("Cannot add a NOT NULL column with default value NULL."),
                         _("Error"));
            return emptyArray;
         }
         ddl += _T(" NOT NULL");
      }

      if (column->GetDefault() != wxEmptyString)
      {
         ddl += _T(" DEFAULT ");
         if ((column->GetType() == cttText || column->GetType() == cttBlob)&&
             (column->GetDefault() != _T("CURRENT_TIME")||
              column->GetDefault() != _T("CURRENT_DATE")||
              column->GetDefault() != _T("CURRENT_TIMESTAMP")))
         {
            def = column->GetDefault();
            if (!def.StartsWith(_T("'"))||!def.EndsWith(_T("'")))
            {
               def.Replace(_T("'"), _T("''"));
               ddl += _T("'") + def + _T("'");
            }
         }
         else if (column->GetDefault() == _T("CURRENT_TIME")||
                  column->GetDefault() == _T("CURRENT_DATE")||
                  column->GetDefault() == _T("CURRENT_TIMESTAMP"))
         {
            wxMessageBox(_("The column may not have a default value of CURRENT_TIME, CURRENT_DATE or CURRENT_TIMESTAMP."),
                         _("Error"));
            return emptyArray;
         }
         else
            ddl += column->GetDefault();
      }
      if (column->GetPrimaryKey())
      {
         wxMessageBox(_("Adding a primary key column is forbidden."),
                      _("Error"));
         return emptyArray;
      }
      ddl += _T(";");
      arrayString.Add(ddl);
   }
   return arrayString;
}
/*---------------------------------------------------------------------------*/
void wxAddColumnDialog::DoTablenameSelected()
{
   wxArrayString arrayString;
   wxString sql, tablename, basename;
   wxSQLite3ResultSet tblQRY;

   if (!m_Db||!m_Db->IsOpen())
      return;
   // Vider la grille
   for (size_t i = m_GridColumns->GetNumberRows(); i > 0; i--)
      m_GridColumns->DeleteRows(i - 1);

   // Récupérer les noms des colonnes de la table
   tablename = m_ChoiceTableName->GetStringSelection();
   if (m_Base != wxEmptyString)
      basename = m_Base;
   else
      basename = _T("main");

   sql = wxString::Format(_T("PRAGMA %s.table_info(\"%s\");"),
                          basename.c_str(), tablename.c_str());
   try
   {
      tblQRY = m_Db->ExecuteQuery(ToUTF8(sql));
      while (tblQRY.NextRow())
         arrayString.Add(tblQRY.GetString(1));
   }
   catch(wxSQLite3Exception& ex)
   {
      wxGetApp().ShowError(_T("OnTablenameSelected"), ex);
   }
   tblQRY.Finalize();

   // Mettre dans un tableau de chaine tous les noms des colonnes existante
   m_TableColumns.SetExistingColumnsName(arrayString);
}
/*---------------------------------------------------------------------------*/
