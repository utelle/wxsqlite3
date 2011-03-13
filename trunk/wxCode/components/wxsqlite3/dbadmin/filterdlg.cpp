/*---------------------------------------------------------------------------*/
/* Logiciel de gestion de fichier de bases de données SQLite                 */
/*---------------------------------------------------------------------------*/
/* Projet  : wxSQLitePlus                              Version  : 0.2.3.0    */
/* Fichier : filterdlg.cpp                                                   */
/* Auteur  : Fred Cailleau-Lepetit                     Date     : 24/08/2008 */
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
#pragma implementation "filterdlg.h"
#endif

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "wxsqliteplusapp.h"
#include "filterdlg.h"
/*---------------------------------------------------------------------------*/
#define ID_FILTER_PANEL 15001
#define ID_FIELDS       15002
#define ID_OPERATORS    15003
#define ID_VALUE        15004
#define ID_BTN_AND      15005
#define ID_BTN_OR       15006
#define ID_BTN_OPAR     15007
#define ID_BTN_CPAR     15008
#define ID_BTN_ADD      15009
#define ID_STATEMENT    15010
/*---------------------------------------------------------------------------*/
IMPLEMENT_DYNAMIC_CLASS(wxFilterDialog, wxDialog)

BEGIN_EVENT_TABLE(wxFilterDialog, wxDialog)
   EVT_CHOICE(ID_FIELDS, wxFilterDialog::OnFieldsSelected)
   EVT_UPDATE_UI(ID_VALUE, wxFilterDialog::OnValueUpdate)
   EVT_BUTTON(ID_BTN_AND, wxFilterDialog::OnBtnAndClick)
   EVT_BUTTON(ID_BTN_OR, wxFilterDialog::OnBtnOrClick)
   EVT_BUTTON(ID_BTN_OPAR, wxFilterDialog::OnBtnOparClick)
   EVT_BUTTON(ID_BTN_CPAR, wxFilterDialog::OnBtnCparClick)
   EVT_BUTTON(wxID_CLEAR, wxFilterDialog::OnClearClick)
   EVT_UPDATE_UI(wxID_CLEAR, wxFilterDialog::OnClearUpdate)
   EVT_BUTTON(ID_BTN_ADD, wxFilterDialog::OnBtnAddClick)
   EVT_BUTTON(wxID_OK, wxFilterDialog::OnOkClick)
END_EVENT_TABLE()
/*---------------------------------------------------------------------------*/
wxFilterDialog::wxFilterDialog()
{
   Init();
}
/*---------------------------------------------------------------------------*/
wxFilterDialog::wxFilterDialog(wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style)
{
   Init();
   Create(parent, id, caption, pos, size, style);
}
/*---------------------------------------------------------------------------*/
bool wxFilterDialog::Create(wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style)
{
   SetExtraStyle(wxWS_EX_BLOCK_EVENTS);
   wxDialog::Create(parent, id, caption, pos, size, style);

   CreateControls();
   SetIcon(wxGetApp().GetIcon(ID_ICO_FILTER));
   if (GetSizer())
   {
      GetSizer()->SetSizeHints(this);
   }
   Centre();
   return true;
}
/*---------------------------------------------------------------------------*/
wxFilterDialog::~wxFilterDialog()
{
}
/*---------------------------------------------------------------------------*/
void wxFilterDialog::Init()
{
   m_fields = NULL;
   m_operators = NULL;
   m_Value = NULL;
   m_filter = NULL;
}
/*---------------------------------------------------------------------------*/
void wxFilterDialog::CreateControls()
{
   wxBoxSizer* bSizer1 = new wxBoxSizer(wxVERTICAL);
   SetSizer(bSizer1);

   wxPanel* iPanel1 = new wxPanel(this, ID_FILTER_PANEL, wxDefaultPosition,
                                  wxDefaultSize, wxSUNKEN_BORDER|wxTAB_TRAVERSAL);
   bSizer1->Add(iPanel1, 0, wxGROW, 0);

   wxBoxSizer* bSizer2 = new wxBoxSizer(wxVERTICAL);
   iPanel1->SetSizer(bSizer2);

   wxBoxSizer* bSizer3 = new wxBoxSizer(wxHORIZONTAL);
   bSizer2->Add(bSizer3, 0, wxGROW, 0);

   m_fields = new wxChoice(iPanel1, ID_FIELDS, wxDefaultPosition,
                           wxDefaultSize, 0, NULL, 0);
   bSizer3->Add(m_fields, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5);

   wxArrayString m_operatorsStrings;
   m_operatorsStrings.Add(_(">"));
   m_operatorsStrings.Add(_(">="));
   m_operatorsStrings.Add(_("<"));
   m_operatorsStrings.Add(_("<="));
   m_operatorsStrings.Add(_("="));
   m_operatorsStrings.Add(_("<>"));
   m_operatorsStrings.Add(_("LIKE"));
   m_operatorsStrings.Add(_("NOT LIKE"));
   m_operatorsStrings.Add(_("GLOB"));
   m_operatorsStrings.Add(_("NOT GLOB"));
   m_operatorsStrings.Add(_("ISNULL"));
   m_operatorsStrings.Add(_("NOTNULL"));
   m_operators = new wxChoice(iPanel1, ID_OPERATORS, wxDefaultPosition,
                              wxDefaultSize, m_operatorsStrings, 0);
   m_operators->SetStringSelection(_(">"));
   bSizer3->Add(m_operators, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

   m_Value = new wxTextCtrl(iPanel1, ID_VALUE, _T(""), wxDefaultPosition,
                            wxDefaultSize, 0);
   bSizer3->Add(m_Value, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5);

   wxBoxSizer* bSizer4 = new wxBoxSizer(wxHORIZONTAL);
   bSizer2->Add(bSizer4, 0, wxALIGN_LEFT, 0);

   wxButton* btnAnd = new wxButton(iPanel1, ID_BTN_AND, _("AND"),
                                   wxDefaultPosition, wxSize(50, -1), 0);
   bSizer4->Add(btnAnd, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

   wxButton* btnOr = new wxButton(iPanel1, ID_BTN_OR, _("OR"),
                                  wxDefaultPosition, wxSize(50, -1), 0);
   bSizer4->Add(btnOr, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

   wxButton* btnOpenPar = new wxButton(iPanel1, ID_BTN_OPAR, _("("),
                                       wxDefaultPosition, wxSize(50, -1), 0);
   bSizer4->Add(btnOpenPar, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

   wxButton* btnClosePar = new wxButton(iPanel1, ID_BTN_CPAR, _(")"),
                                        wxDefaultPosition, wxSize(50, -1), 0);
   bSizer4->Add(btnClosePar, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

   wxButton* btnClear = new wxButton(iPanel1, wxID_CLEAR, _("&Clear"),
                                     wxDefaultPosition, wxDefaultSize, 0);
   bSizer4->Add(btnClear, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

   bSizer4->Add(5, 5, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

   wxButton* btnAdd = new wxButton(iPanel1, ID_BTN_ADD, _("Add"),
                                   wxDefaultPosition, wxDefaultSize, 0);
   bSizer4->Add(btnAdd, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

   m_filter = new wxSQLEditor(this, ID_STATEMENT, wxDefaultPosition, wxSize(-1, 100));
   m_filter->SetLineNumberMarginStyle(false);

   bSizer1->Add(m_filter, 1, wxGROW|wxLEFT, 0);

   wxStdDialogButtonSizer* dlgButtonSizer1 = new wxStdDialogButtonSizer;

   bSizer1->Add(dlgButtonSizer1, 0, wxALIGN_RIGHT|wxALL, 5);
   wxButton* btnOk = new wxButton(this, wxID_OK, _("&OK"),
                                  wxDefaultPosition, wxDefaultSize, 0);
   btnOk->SetDefault();
   dlgButtonSizer1->AddButton(btnOk);

   wxButton* btnCancel = new wxButton(this, wxID_CANCEL, _("&Cancel"),
                                      wxDefaultPosition, wxDefaultSize, 0);
   dlgButtonSizer1->AddButton(btnCancel);

   dlgButtonSizer1->Realize();
}
/*---------------------------------------------------------------------------*/
void wxFilterDialog::OnBtnAddClick(wxCommandEvent& event)
{
  wxUnusedVar(event);
   wxString tmp1, tmp2;
   int idxfield, idxoper;

   idxfield = m_fields->GetSelection();
   idxoper = m_operators->GetSelection();

   tmp1 = wxString::Format(_T("\"%s\" %s"),
                           m_fields->GetString(idxfield).c_str(),
                           m_operators->GetString(idxoper).c_str());
   if (idxoper < 10)
   {
      tmp2 = m_Value-> GetValue();
      if (m_fields->GetClientData(idxfield) == (void*)1)
         tmp2 = wxString::Format(_T("'%s'"), tmp2.c_str());
      tmp1 = wxString::Format(_T("%s %s"), tmp1.c_str(), tmp2.c_str());
   }
   m_filter->AddText(tmp1);
}
/*---------------------------------------------------------------------------*/
void wxFilterDialog::OnBtnAndClick(wxCommandEvent& event)
{
  wxUnusedVar(event);
   m_filter->AddText(_T("\nAND "));
}
/*---------------------------------------------------------------------------*/
void wxFilterDialog::OnBtnOrClick(wxCommandEvent& event)
{
  wxUnusedVar(event);
   m_filter->AddText(_T("\nOR "));
}
/*---------------------------------------------------------------------------*/
void wxFilterDialog::OnBtnOparClick(wxCommandEvent& event)
{
  wxUnusedVar(event);
   m_filter->AddText(_T("("));
}
/*---------------------------------------------------------------------------*/
void wxFilterDialog::OnBtnCparClick(wxCommandEvent& event)
{
  wxUnusedVar(event);
   m_filter->AddText(_T(")"));
}
/*---------------------------------------------------------------------------*/
void wxFilterDialog::OnClearClick(wxCommandEvent& event)
{
  wxUnusedVar(event);
   m_filter->ClearAll();
}
/*---------------------------------------------------------------------------*/
void wxFilterDialog::OnClearUpdate(wxUpdateUIEvent& event)
{
   event.Enable(m_filter->GetLength() > 0);
}
/*---------------------------------------------------------------------------*/
void wxFilterDialog::OnOkClick(wxCommandEvent& event)
{
   wxString sql, base;

   try
   {
      m_Statement = m_filter->GetText();
      if (!m_Statement.IsEmpty())
      {
         if (m_Base.IsEmpty())
            base = _T("main");
         else
            base = m_Base;
         sql = _T("EXPLAIN SELECT *\r");
         sql += _T("FROM ") + base + _T(".") + m_Table + _T("\r");
         sql += _T("WHERE ") + m_Statement + _T(";");
         wxSQLite3ResultSet resultSet = m_Db->ExecuteQuery(ToUTF8(sql));
         resultSet.Finalize();
      }
      event.Skip();
   }
   catch(wxSQLite3Exception& ex)
   {
      wxMessageBox(ex.GetMessage(), _("Error"));
   }
}
/*---------------------------------------------------------------------------*/
void wxFilterDialog::OnFieldsSelected(wxCommandEvent& event)
{
   m_Value->Clear();
   event.Skip();
}
/*---------------------------------------------------------------------------*/
void wxFilterDialog::OnValueUpdate(wxUpdateUIEvent& event)
{
   event.Enable(m_operators->GetSelection() < 10);
}
/*---------------------------------------------------------------------------*/
void wxFilterDialog::SetDatabase(wxSQLite3Database* db, const wxString& base)
{
   m_Db = db;
   m_Base = base;
   if (!m_Db||!m_Db->IsOpen())
      return;
   m_fields->Clear();
   m_Table = wxEmptyString;
}
/*---------------------------------------------------------------------------*/
void wxFilterDialog::SetTable(const wxString& table)
{
   if (!m_Db||!m_Db->IsOpen())
      return;

   m_Table = table;
   m_fields->Clear();

   try
   {
      wxSQLite3ResultSet clmnQRY;
      wxString sql, basename;
      int numberCols;

      if (m_Base != wxEmptyString)
         basename = m_Base;
      else
         basename = _T("main");

      // limiter à 1 car si limite à 0 ça ne fonctionne pas
      // les informations sur le type de colonnes n'est pas retourné
      sql = wxString::Format(_T("SELECT * FROM %s.%s LIMIT 1;"),
                             basename.c_str(), m_Table.c_str());
      clmnQRY = m_Db->ExecuteQuery(ToUTF8(sql));

      numberCols = clmnQRY.GetColumnCount();
      int colt;
      for (int i = 0; i < numberCols; i++)
      {
         colt = clmnQRY.GetColumnType(i);
         switch (colt)
         {
            case WXSQLITE_INTEGER :
            case WXSQLITE_FLOAT   :
               m_fields->Append(clmnQRY.GetColumnName(i), (void*)0);
               break;
            default : ; // WXSQLITE_TEXT WXSQLITE_BLOB WXSQLITE_NULL
               m_fields->Append(clmnQRY.GetColumnName(i), (void*)1);
         }
      }

      clmnQRY.Finalize();
      m_fields->SetSelection(0);
   }
   catch(wxSQLite3Exception& ex)
   {
      wxGetApp().ShowError(_T("SetTable"), ex);
   }

}
/*---------------------------------------------------------------------------*/
void wxFilterDialog::SetStatement(const wxString& value)
{
   m_Statement = value;
   m_filter->SetText(m_Statement);
}
/*---------------------------------------------------------------------------*/
