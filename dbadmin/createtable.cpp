/*---------------------------------------------------------------------------*/
/* Logiciel de gestion de fichier de bases de données SQLite                 */
/*---------------------------------------------------------------------------*/
/* Projet  : wxSQLitePlus                              Version  : 0.2.3.0    */
/* Fichier : createtable.cpp                                                 */
/* Auteur  : Fred Cailleau-Lepetit                     Date     : 14/07/2007 */
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
#pragma implementation "createtable.h"
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
#include <wx/valgen.h>
/*---------------------------------------------------------------------------*/
#include "createtable.h"
#include "wxsqliteplusapp.h"
#include "sqliteplusframe.h"
#include "specgrid.h"
/*---------------------------------------------------------------------------*/
#define ID_TABLENAME       15001
#define ID_CB_TEMP         15002
#define ID_BOOK            15003
#define ID_PANELBOOK       15004
#define ID_COLUMNS         15005
#define ID_BTN_ADDCOLUMN   15006
#define ID_BTN_DELCOLUMN   15007
#define ID_DDL             15008
/*---------------------------------------------------------------------------*/
wxColumnCtrTable::wxColumnCtrTable()
{
   m_Name = _T("col");
   m_Type = cttText;
   m_NotNull = false;
   m_PrimaryKey = false;
}
/*---------------------------------------------------------------------------*/
wxGridColumnsTable::wxGridColumnsTable()
{
}
/*---------------------------------------------------------------------------*/
wxGridColumnsTable::~wxGridColumnsTable()
{
   WX_CLEAR_ARRAY(m_Columns)
}
/*---------------------------------------------------------------------------*/
int wxGridColumnsTable::GetNumberRows()
{
   return (int)m_Columns.GetCount();
}
/*---------------------------------------------------------------------------*/
bool wxGridColumnsTable::IsEmptyCell(int row, int col)
{
   if (col == 0)
      if (m_Columns[row]->GetName() == wxEmptyString)
         return true;
   return false;
}
/*---------------------------------------------------------------------------*/
wxString wxGridColumnsTable::GetValue(int row, int col)
{
   switch (col)
   {
      case 0 : return m_Columns[row]->GetName();
      case 1 :
         switch (m_Columns[row]->GetType())
         {
            case cttInteger : return _T("INTEGER");
            case cttIntegerAutoinc : return _T("INTEGER AUTOINCREMENT");
            case cttReal : return _T("REAL");
            case cttText : return _T("TEXT");
            case cttBlob : return _T("BLOB");
         }
         return wxEmptyString;
      case 2 :
         if (m_Columns[row]->GetNotNull())
            return _T("1");
         return _T("0");
      case 3 :
         if (m_Columns[row]->GetPrimaryKey())
            return _T("1");
         return _T("0");
      case 4 : return m_Columns[row]->GetDefault();
   }
   return wxEmptyString;
}
/*---------------------------------------------------------------------------*/
bool wxGridColumnsTable::GetValueAsBool(int row, int col)
{
   if (col == 2)
      return m_Columns[row]->GetNotNull();
   else if (col == 3)
      return m_Columns[row]->GetPrimaryKey();
   else
      return false;
}
/*---------------------------------------------------------------------------*/
void wxGridColumnsTable::SetValue(int row, int col, const wxString& value)
{
   if (col == 0)
   {
      if (CheckName(value, row))
         m_Columns[row]->SetName(value.Upper());
   }
   else if (col == 1)
   {
      if (value == _T("INTEGER"))
      {
         long l_Long;
         wxString val;

         m_Columns[row]->SetType(cttInteger);
         val = m_Columns[row]->GetDefault();
         if ((val != wxEmptyString) && !val.ToLong(&l_Long))
            SetValue(row, 4, wxEmptyString);
      }
      else if (value == _T("INTEGER AUTOINCREMENT"))
      {
         if (CheckAutoInc())
            return;
         m_Columns[row]->SetType(cttIntegerAutoinc);
         SetValueAsBool(row, 3, true);
         SetValue(row, 4, wxEmptyString);
         // Oblige la grille à prendre en compte le changement
         GetView()->SetCellValue(row, 3, _T("1"));
      }
      else if (value == _T("REAL"))
      {
         double l_Double;
         wxString val;

         m_Columns[row]->SetType(cttReal);
         val = m_Columns[row]->GetDefault();
         if ((val != wxEmptyString) && !val.ToDouble(&l_Double))
            SetValue(row, 4, wxEmptyString);
      }
      else if (value == _T("TEXT"))
         m_Columns[row]->SetType(cttText);
      else if (value == _T("BLOB"))
         m_Columns[row]->SetType(cttBlob);
   }
   else if (col == 4)
   {
      if (value != wxEmptyString)
      {
         long l_Long;
         double l_Double;

         switch (m_Columns[row]->GetType())
         {
            case cttInteger :
               if (value.ToLong(&l_Long))
                  m_Columns[row]->SetDefault(wxString::Format(_T("%li"), l_Long));
               break;
            case cttIntegerAutoinc : return;
            case cttReal :
               if (value.ToDouble(&l_Double))
                  m_Columns[row]->SetDefault(wxString::Format(_T("%f"), l_Double));
               break;
            case cttText :
            case cttBlob :
               if ((value.Upper() == _T("CURRENT_TIME"))||
                  (value.Upper() == _T("CURRENT_DATE"))||
                  (value.Upper() == _T("CURRENT_TIMESTAMP")))
                  m_Columns[row]->SetDefault(value.Upper());
               else
                  m_Columns[row]->SetDefault(value);
         }
      }
      else
         m_Columns[row]->SetDefault(wxEmptyString);
   }
}
/*---------------------------------------------------------------------------*/
void wxGridColumnsTable::SetValueAsBool(int row, int col, bool value)
{

   if (col == 2)
      m_Columns[row]->SetNotNull(value);
   else if (col == 3)
   {
      if (value != 0)   // Si primary key
      {
         if (CheckAutoInc(row))
            return;

         // alors retirer le flag au autres
         for (size_t i = 0; i < m_Columns.GetCount(); i++)
         {
            m_Columns[i]->SetPrimaryKey(false);
            // Oblige la grille à prendre en compte le changement
            GetView()->SetCellValue(i, 3, _T("0"));
         }
      }
      else
      {  // Si la colonne est autoincrement ne pas supprimer le primary key
         if (m_Columns[row]->GetType() == cttIntegerAutoinc)
            return;
      }
      m_Columns[row]->SetPrimaryKey(value);
   }
}
/*---------------------------------------------------------------------------*/
wxString wxGridColumnsTable::GetColLabelValue(int col)
{
   switch (col)
   {
      case 0 : return _("Name");
      case 1 : return _("Type");
      case 2 : return _("Not Null");
      case 3 : return _("Primay Key");
      case 4 : return _("Default");
   }
   return wxEmptyString;
}
/*---------------------------------------------------------------------------*/
wxString wxGridColumnsTable::GetTypeName(int row, int col)
{
  wxUnusedVar(row);
  wxUnusedVar(col);
   if (col == 0 || col == 4)
      return wxGRID_VALUE_STRING;
   else if (col == 1)
      return wxString::Format(_T("%s:INTEGER,INTEGER AUTOINCREMENT,REAL,TEXT,BLOB"), wxGRID_VALUE_CHOICE);
   else if (col == 2 || col == 3)
      return wxGRID_VALUE_BOOL;
   return wxEmptyString;
}
/*---------------------------------------------------------------------------*/
bool wxGridColumnsTable::CanGetValueAs(int row, int col, const wxString& typeName)
{
  wxUnusedVar(row);
   if (typeName == wxGRID_VALUE_STRING)
      return (col == 0 || col == 1 || col == 4);
   else if (typeName == wxGRID_VALUE_BOOL)
      return (col == 2 || col == 3);
   else
      return false;
}
/*---------------------------------------------------------------------------*/
bool wxGridColumnsTable::CanSetValueAs(int row, int col, const wxString& typeName)
{
   return CanGetValueAs(row, col, typeName);
}
/*---------------------------------------------------------------------------*/
bool wxGridColumnsTable::InsertRows(size_t pos, size_t numRows)
{
   for (size_t i = 0; i < numRows; i ++)
   {
      wxColumnCtrTable* item = new wxColumnCtrTable;
      item->SetName(GetUniqueName());
      m_Columns.Insert(item, pos + i);
   }
   if (GetView())
   {
      wxGridTableMessage msg(this, wxGRIDTABLE_NOTIFY_ROWS_INSERTED, pos, numRows);
      GetView()->ProcessTableMessage( msg );
   }
   return true;
}
/*---------------------------------------------------------------------------*/
bool wxGridColumnsTable::AppendRows(size_t numRows)
{
   for (size_t i = 0; i < numRows; i ++)
   {
      wxColumnCtrTable* item = new wxColumnCtrTable;
      item->SetName(GetUniqueName());
      m_Columns.Add(item);
   }
   if (GetView())
   {
      wxGridTableMessage msg(this, wxGRIDTABLE_NOTIFY_ROWS_APPENDED, numRows);
      GetView()->ProcessTableMessage(msg);
   }
   return true;
}
/*---------------------------------------------------------------------------*/
bool wxGridColumnsTable::DeleteRows(size_t pos, size_t numRows)
{
   for (size_t i = pos; i < pos + numRows && i < m_Columns.GetCount(); i++)
   {
      wxColumnCtrTable* item = m_Columns[i];
      m_Columns.Remove(item);
      delete item;
   }
   if (GetView())
   {
      wxGridTableMessage msg(this, wxGRIDTABLE_NOTIFY_ROWS_DELETED, pos, numRows);
      GetView()->ProcessTableMessage(msg);
    }
   return true;
}
/*---------------------------------------------------------------------------*/
bool wxGridColumnsTable::CheckName(const wxString& name, int row)
{
   wxChar c;
   // Vérification du nom
   for (size_t i = 0; i < name.Len(); i++)
   {
      c = name.GetChar(i);
      if (!wxIsalnum(c) && c != _T('_') && c != _T(' '))
         return false;
   }
   // Vérifie que le nom est unique
   for (size_t i = 0; i < m_Columns.GetCount(); i++)
      if ((int)i != row)
         if (m_Columns[i]->GetName().Upper() == name.Upper())
            return false;

   return true;
}
/*---------------------------------------------------------------------------*/
wxString wxGridColumnsTable::GetUniqueName()
{
   wxString name;
   size_t i = m_Columns.GetCount();

   do
   {
      name = wxString::Format(_T("COLUMN%u"), i++);
   }
   while (!CheckName(name));
   return name;
}
/*---------------------------------------------------------------------------*/
wxColumnCtrTable* wxGridColumnsTable::GetColumnCtrTable(size_t index)
{
   if (index < m_Columns.GetCount())
      return m_Columns[index];
   return NULL;
}
/*---------------------------------------------------------------------------*/
bool wxGridColumnsTable::CheckAutoInc(int row)
{
   // Vérifier si une ligne est AUTOINCREMENT
   for (size_t i = 0; i < m_Columns.GetCount(); i++)
      if (((int)i != row) && (m_Columns[i]->GetType() == cttIntegerAutoinc))
         return true;
   return false;
}
/*---------------------------------------------------------------------------*/
IMPLEMENT_DYNAMIC_CLASS(wxCreateTableDialog, wxDialog)

BEGIN_EVENT_TABLE(wxCreateTableDialog, wxDialog)
   EVT_NOTEBOOK_PAGE_CHANGING(ID_BOOK, wxCreateTableDialog::OnBookPageChanging)
   EVT_BUTTON(ID_BTN_ADDCOLUMN, wxCreateTableDialog::OnBtnAddcolumnClick)
   EVT_BUTTON(ID_BTN_DELCOLUMN, wxCreateTableDialog::OnBtnDelcolumnClick)
   EVT_UPDATE_UI(ID_BTN_DELCOLUMN, wxCreateTableDialog::OnBtnDelcolumnUpdate)
   EVT_BUTTON(wxID_OK, wxCreateTableDialog::OnOkClick)
END_EVENT_TABLE()
/*---------------------------------------------------------------------------*/
wxCreateTableDialog::wxCreateTableDialog()
{
   Init();
}
/*---------------------------------------------------------------------------*/
wxCreateTableDialog::wxCreateTableDialog(wxWindow* parent, wxWindowID id,
                                         const wxString& caption,
                                         const wxPoint& pos, const wxSize& size,
                                         long style)
{
   Init();
   Create(parent, id, caption, pos, size, style);
}
/*---------------------------------------------------------------------------*/
bool wxCreateTableDialog::Create(wxWindow* parent, wxWindowID id,
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
wxCreateTableDialog::~wxCreateTableDialog()
{
   // if this line does not exist the program crash on GTK2
   m_GridColumns->SetTable(NULL);
}
/*---------------------------------------------------------------------------*/
void wxCreateTableDialog::SetDatabase(wxSQLite3Database* db,
                                      const wxString& base)
{
   m_Db = db;
   m_Base = base;
   if (!m_Db||!m_Db->IsOpen())
      m_Db = NULL;
}
/*---------------------------------------------------------------------------*/
void wxCreateTableDialog::Init()
{
   m_TextTableName = NULL;
   m_TempTable = NULL;
   m_GridColumns = NULL;
   m_TextDdl = NULL;
   m_Db = NULL;
   m_Temporary = false;
}
/*---------------------------------------------------------------------------*/
void wxCreateTableDialog::CreateControls()
{
   wxBoxSizer* bSizer1 = new wxBoxSizer(wxVERTICAL);
   SetSizer(bSizer1);

   wxBoxSizer* bSizer2 = new wxBoxSizer(wxHORIZONTAL);
   bSizer1->Add(bSizer2, 0, wxALIGN_LEFT|wxALL, 5);

   wxStaticText* iStatic1 = new wxStaticText(this, wxID_STATIC, _("&Name : "),
                                             wxDefaultPosition, wxDefaultSize, 0);
   bSizer2->Add(iStatic1, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

   m_TextTableName = new wxTextCtrl(this, ID_TABLENAME, wxEmptyString,
                                    wxDefaultPosition, wxSize(200, -1), 0);
   bSizer2->Add(m_TextTableName, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

   m_TempTable = new wxCheckBox(this, ID_CB_TEMP, _("&Temporary Table"),
                                wxDefaultPosition, wxDefaultSize, 0);
   m_TempTable->SetValue(false);
   bSizer2->Add(m_TempTable, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

   wxNotebook* noteBook1 = new wxNotebook(this, ID_BOOK, wxDefaultPosition,
                                          wxDefaultSize, wxBK_DEFAULT);

   wxPanel* panel1 = new wxPanel(noteBook1, ID_PANELBOOK, wxDefaultPosition,
                                 wxDefaultSize, wxTAB_TRAVERSAL);
   wxBoxSizer* bSizer3 = new wxBoxSizer(wxVERTICAL);
   panel1->SetSizer(bSizer3);

   m_GridColumns = new wxSpecGrid(panel1, ID_COLUMNS, wxDefaultPosition,
                                  wxSize(700, 250), wxHSCROLL|wxVSCROLL);
   m_GridColumns->SetDefaultColSize(50);
   m_GridColumns->SetDefaultRowSize(25);
   m_GridColumns->SetColLabelSize(25);
   m_GridColumns->SetRowLabelSize(50);
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

   noteBook1->AddPage(panel1, _("Table"));

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

   // Connect events and objects
   m_TextTableName->Connect(ID_TABLENAME, wxEVT_CHAR,
                            wxKeyEventHandler(wxCreateTableDialog::OnChar),
                            NULL, this);
   m_GridColumns->Connect(ID_COLUMNS, wxEVT_CHAR,
                          wxKeyEventHandler(wxCreateTableDialog::OnGridChar),
                          NULL, this);
   m_GridColumns->SetTable(&m_TableColumns);
   m_GridColumns->SetColSize(0, 190);
   m_GridColumns->SetColSize(1, 185);
   m_GridColumns->SetColSize(2, 70);
   m_GridColumns->SetColSize(3, 90);
   m_GridColumns->SetColSize(4, 120);

   // Set validators
   m_TempTable->SetValidator(wxGenericValidator(&m_Temporary));
}
/*---------------------------------------------------------------------------*/
bool wxCreateTableDialog::ShowToolTips()
{
   return true;
}
/*---------------------------------------------------------------------------*/
void wxCreateTableDialog::OnBtnAddcolumnClick(wxCommandEvent& event)
{
  wxUnusedVar(event);
   m_GridColumns->AppendRows(1);
}
/*---------------------------------------------------------------------------*/
void wxCreateTableDialog::OnBtnDelcolumnClick(wxCommandEvent& event)
{
  wxUnusedVar(event);
   wxArrayInt rowsArray = m_GridColumns->GetSelectedRows();
   for (size_t i = rowsArray.GetCount(); i > 0; i--)
      m_GridColumns->DeleteRows(rowsArray[i - 1]);
}
/*---------------------------------------------------------------------------*/
void wxCreateTableDialog::OnBtnDelcolumnUpdate(wxUpdateUIEvent& event)
{
   event.Enable(m_GridColumns->GetSelectedRows().GetCount() > 0);
}
/*---------------------------------------------------------------------------*/
void wxCreateTableDialog::OnOkClick(wxCommandEvent& event)
{
   if (GetCreateTableDDL().IsEmpty())
      return;
   event.Skip();
}
/*---------------------------------------------------------------------------*/
void wxCreateTableDialog::OnGridChar(wxKeyEvent& event)
{
   event.Skip();
}
/*---------------------------------------------------------------------------*/
void wxCreateTableDialog::OnChar(wxKeyEvent& event)
{
   int c = event.GetKeyCode();
   if ((!wxIsalnum(c) && c != _T('_') && c != _T(' ') && c != WXK_BACK && c != WXK_DELETE)&&
      // Ctrl+C Ctrl+V Ctrl+X
       !(event.ControlDown() && (c == 3 || c == 22 || c == 24)))
      return;
   event.Skip();
}
/*---------------------------------------------------------------------------*/
void wxCreateTableDialog::OnBookPageChanging(wxNotebookEvent& event)
{
   if (event.GetOldSelection() == 0)
   {
      wxString ddl = GetCreateTableDDL();

      if (ddl.IsEmpty())
         event.Veto();
      else
         m_TextDdl->SetValue(ddl);
   }
}
/*---------------------------------------------------------------------------*/
wxString wxCreateTableDialog::GetCreateTableDDL()
{
   wxString ddl, tablename, def;
   wxColumnCtrTable* column;
   wxSQLitePlusFrame* frame;

   if (!m_Db||!m_Db->IsOpen())
      return wxEmptyString;

   tablename = m_TextTableName->GetValue();
   if (tablename.IsEmpty())
   {
      wxMessageBox(_("You have to enter a table name."),
                   _("Error"));
      m_TextTableName->SetFocus();
      return wxEmptyString;
   }
   if (m_GridColumns->GetNumberRows() == 0)
   {
      wxMessageBox(_("You have to create column(s) for the table."),
                   _("Error"));
      m_BtnAddColumn->SetFocus();
      return wxEmptyString;
   }

   frame = (wxSQLitePlusFrame*)wxGetApp().GetTopWindow();

   if (frame->ExistDbObject(otTable, tablename, m_Base))
   {
      wxMessageBox(_("Table or view with this name already exist."),
                   _("Error"));
      m_TextTableName->SetFocus();
      return wxEmptyString;
   }

   // Création du DDL
   ddl = _T("CREATE ");
   if (m_TempTable->IsChecked())
      ddl += _T("TEMPORARY ");
   ddl += _T("TABLE ");
   if (!m_TempTable->IsChecked() && m_Base != wxEmptyString)
      ddl += m_Base + _T(".");
   ddl += _T("\"") + tablename.Lower() + _T("\"\n");
   ddl += _T("(");
   for (int i = 0; i < m_TableColumns.GetNumberRows(); i++)
   {
      column = m_TableColumns.GetColumnCtrTable(i);
      ddl += _T("\n  \"") + column->GetName() + _T("\" ");
      switch (column->GetType())
      {
         case cttIntegerAutoinc :
            if (!column->GetPrimaryKey())
            {
               wxMessageBox(_("A column with AUTOINCREMENT must be a primary key."),
                            _("Error"));
               return wxEmptyString;
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
         ddl += _T(" NOT NULL");
      if (column->GetPrimaryKey())
      {
         ddl += _T(" PRIMARY KEY");
         if (column->GetType() == cttIntegerAutoinc)
            ddl += _T(" AUTOINCREMENT");
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
         else
            ddl += column->GetDefault();
      }
      if (i != m_TableColumns.GetNumberRows() - 1)
         ddl += _T(",");
   }
   ddl += _T("\n);");
   return ddl;
}
/*---------------------------------------------------------------------------*/
