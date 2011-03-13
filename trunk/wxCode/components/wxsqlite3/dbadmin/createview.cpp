/*---------------------------------------------------------------------------*/
/* Logiciel de gestion de fichier de bases de données SQLite                 */
/*---------------------------------------------------------------------------*/
/* Projet  : wxSQLitePlus                              Version  : 0.2.0.0    */
/* Fichier : createview.cpp                                                  */
/* Auteur  : Fred Cailleau-Lepetit                     Date     : 23/08/2007 */
/* email   : softinthebox@free.fr                      Révision : 01/02/2008 */
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
#pragma implementation "createview.h"
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
#include "createview.h"
#include "wxsqliteplusapp.h"
#include "sqliteplusframe.h"
/*---------------------------------------------------------------------------*/
#define ID_VIEWNAME     15001
#define ID_TEMPVIEW     15002
#define ID_NOTEBOOK     15003
#define ID_PANEL        15004
#define ID_VIEWQUERY    15005
#define ID_PARSERESULTS 15006
#define ID_BTN_TEST     15007
#define ID_DDL          15008
/*---------------------------------------------------------------------------*/
IMPLEMENT_DYNAMIC_CLASS(wxCreateViewDialog, wxDialog)

BEGIN_EVENT_TABLE(wxCreateViewDialog, wxDialog)
   EVT_NOTEBOOK_PAGE_CHANGING(ID_NOTEBOOK, wxCreateViewDialog::OnNotebookPageChanging)
   EVT_BUTTON(ID_BTN_TEST, wxCreateViewDialog::OnBtnTestClick)
   EVT_UPDATE_UI(ID_BTN_TEST, wxCreateViewDialog::OnBtnTestUpdate)
   EVT_BUTTON(wxID_OK, wxCreateViewDialog::OnOkClick)
END_EVENT_TABLE()
/*---------------------------------------------------------------------------*/
wxCreateViewDialog::wxCreateViewDialog()
{
   Init();
}
/*---------------------------------------------------------------------------*/
wxCreateViewDialog::wxCreateViewDialog(wxWindow* parent, wxWindowID id,
                                       const wxString& caption,
                                       const wxPoint& pos,
                                       const wxSize& size, long style)
{
   Init();
   Create(parent, id, caption, pos, size, style);
}
/*---------------------------------------------------------------------------*/
bool wxCreateViewDialog::Create(wxWindow* parent, wxWindowID id,
                                const wxString& caption, const wxPoint& pos,
                                const wxSize& size, long style)
{
   SetExtraStyle(wxWS_EX_BLOCK_EVENTS);
   wxDialog::Create(parent, id, caption, pos, size, style);

   CreateControls();
   SetIcon(wxGetApp().GetIcon(ID_ICO_VIEW));
   if (GetSizer())
   {
      GetSizer()->SetSizeHints(this);
   }
   Centre();
   return true;
}
/*---------------------------------------------------------------------------*/
wxCreateViewDialog::~wxCreateViewDialog()
{
}
/*---------------------------------------------------------------------------*/
void wxCreateViewDialog::SetDatabase(wxSQLite3Database* db,
                                     const wxString& base)
{
   m_Db = db;
   m_Base = base;
   if (!m_Db||!m_Db->IsOpen())
      m_Db = NULL;
}
/*---------------------------------------------------------------------------*/
void wxCreateViewDialog::Init()
{
   m_ViewName = NULL;
   m_TempView = NULL;
   m_ViewQuery = NULL;
   m_ParseResults = NULL;
   m_TextDdl = NULL;
   m_Db = NULL;
   m_Temporary = false;
}
/*---------------------------------------------------------------------------*/
void wxCreateViewDialog::CreateControls()
{    
   wxBoxSizer* bSizer1 = new wxBoxSizer(wxVERTICAL);
   SetSizer(bSizer1);

   wxBoxSizer* bSizer2 = new wxBoxSizer(wxHORIZONTAL);
   bSizer1->Add(bSizer2, 0, wxALIGN_LEFT|wxALL, 5);

   wxStaticText* sText1 = new wxStaticText(this, wxID_STATIC, _("Na&me :"),
                                           wxDefaultPosition, wxDefaultSize, 0);
   bSizer2->Add(sText1, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

   m_ViewName = new wxTextCtrl(this, ID_VIEWNAME, wxEmptyString,
                               wxDefaultPosition, wxSize(200, -1), 0);
   bSizer2->Add(m_ViewName, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

   bSizer2->Add(20, 5, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

   m_TempView = new wxCheckBox(this, ID_TEMPVIEW, _("&Temporary View"),
                               wxDefaultPosition, wxDefaultSize, 0);
   m_TempView->SetValue(false);
   bSizer2->Add(m_TempView, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

   wxNotebook* nBook1 = new wxNotebook(this, ID_NOTEBOOK, wxDefaultPosition,
                                       wxDefaultSize, wxBK_DEFAULT);

   wxPanel* panel1 = new wxPanel(nBook1, ID_PANEL, wxDefaultPosition,
                                 wxDefaultSize, wxTAB_TRAVERSAL);
   wxBoxSizer* bSizer3 = new wxBoxSizer(wxVERTICAL);
   panel1->SetSizer(bSizer3);

   wxStaticText* sText2 = new wxStaticText(panel1, wxID_STATIC,
                                           _("SQL &Query :"), wxDefaultPosition,
                                           wxDefaultSize, 0);
   bSizer3->Add(sText2, 0, wxALIGN_LEFT|wxALL, 5);

   m_ViewQuery = new wxSQLEditor(panel1, ID_VIEWQUERY, wxDefaultPosition,
                                 wxSize(600, 170));
   m_ViewQuery->SetLineNumberMarginStyle(false);
   bSizer3->Add(m_ViewQuery, 1, wxGROW|wxALL, 5);

   wxBoxSizer* bSizer4 = new wxBoxSizer(wxHORIZONTAL);
   bSizer3->Add(bSizer4, 0, wxGROW, 0);
   wxBoxSizer* bSizer5 = new wxBoxSizer(wxVERTICAL);
   bSizer4->Add(bSizer5, 1, wxGROW, 0);
   wxStaticText* sText3 = new wxStaticText(panel1, wxID_STATIC,
                                           _("SQL &Parse Results :"),
                                           wxDefaultPosition, wxDefaultSize, 0);
   bSizer5->Add(sText3, 0, wxALIGN_LEFT|wxALL, 5);

   m_ParseResults = new wxTextCtrl(panel1, ID_PARSERESULTS, wxEmptyString,
                                   wxDefaultPosition, wxSize(-1, 80),
                                   wxTE_MULTILINE|wxTE_READONLY|
                                   wxTE_WORDWRAP|wxSIMPLE_BORDER);
   bSizer5->Add(m_ParseResults, 1, wxGROW|wxALL, 5);

   wxButton* btnTextSyntax = new wxButton(panel1, ID_BTN_TEST,
                                          _("Test &Syntax"), wxDefaultPosition,
                                          wxDefaultSize, 0);
   bSizer4->Add(btnTextSyntax, 0, wxALIGN_TOP|wxALL, 5);

   nBook1->AddPage(panel1, _("SQL Query"));

   m_TextDdl = new wxDDLEditor(nBook1, ID_DDL);

   nBook1->AddPage(m_TextDdl, _("DDL"));

   bSizer1->Add(nBook1, 0, wxGROW|wxALL, 5);

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
   m_ViewName->Connect(ID_VIEWNAME, wxEVT_CHAR,
                       wxKeyEventHandler(wxCreateViewDialog::OnChar),
                       NULL, this);
   // Set validators
   m_TempView->SetValidator(wxGenericValidator(&m_Temporary));
}
/*---------------------------------------------------------------------------*/
bool wxCreateViewDialog::ShowToolTips()
{
   return true;
}
/*---------------------------------------------------------------------------*/
void wxCreateViewDialog::OnChar(wxKeyEvent& event)
{
   int c = event.GetKeyCode();
   if ((!wxIsalnum(c) && c != _T('_') && c != _T(' ') && c != WXK_BACK && c != WXK_DELETE)&&
      // Ctrl+C Ctrl+V Ctrl+X
       !(event.ControlDown() && (c == 3 || c == 22 || c == 24)))
      return;
   event.Skip();
}
/*---------------------------------------------------------------------------*/
void wxCreateViewDialog::OnNotebookPageChanging(wxNotebookEvent& event)
{
   if (event.GetOldSelection() == 0)
   {
      wxString ddl = GetCreateViewDDL();

      if (ddl.IsEmpty())
         event.Veto();
      else
         m_TextDdl->SetValue(ddl);
   }
}
/*---------------------------------------------------------------------------*/
void wxCreateViewDialog::OnOkClick(wxCommandEvent& event)
{
   if (GetCreateViewDDL().IsEmpty())
      return;
   event.Skip();
}
/*---------------------------------------------------------------------------*/
void wxCreateViewDialog::OnBtnTestClick(wxCommandEvent& event)
{
   if (!CheckViewQuery(m_ViewQuery->GetText()))
      m_ParseResults->SetValue(m_QueryError);
   else
      m_ParseResults->SetValue(_("No errors found in SQL."));
   event.Skip();
}
/*---------------------------------------------------------------------------*/
void wxCreateViewDialog::OnBtnTestUpdate(wxUpdateUIEvent& event)
{
   event.Enable(!m_ViewQuery->GetText().IsEmpty());
}
/*---------------------------------------------------------------------------*/
bool wxCreateViewDialog::CheckViewQuery(const wxString& query)
{
   if (!query.IsEmpty())
   {
      /*
      wxString tmp;
      // Ce test n'est pas bon ni performant
      tmp = query.Strip(wxString::both).BeforeFirst(_T(' ')).Upper();
      if (tmp != _T("SELECT"))
      {
         m_QueryError = _("You must enter a SELECT sql statement.");
      }
      else
      {
         return wxGetApp().CheckStatementSyntax(m_Db, query, m_QueryError);
      }
      */
      return wxGetApp().CheckStatementSyntax(m_Db, query, m_QueryError);
   }
   else
      m_QueryError = _("You must enter a SELECT sql statement.");
   return false;
}
/*---------------------------------------------------------------------------*/
wxString wxCreateViewDialog::GetCreateViewDDL()
{
   wxString ddl, query, viewname;
   wxSQLitePlusFrame* frame;

   if (!m_Db||!m_Db->IsOpen())
      return wxEmptyString;

   viewname = m_ViewName->GetValue();
   if (viewname.IsEmpty())
   {
      wxMessageBox(_("You have to enter a view name."),
                   _("Error"));
      m_ViewName->SetFocus();
      return wxEmptyString;
   }

   query = m_ViewQuery->GetText();
   if (!CheckViewQuery(query))
   {
      wxMessageBox(m_QueryError, _("Error"));
      m_ViewQuery->SetFocus();
      return wxEmptyString;
   }

   frame = (wxSQLitePlusFrame*)wxGetApp().GetTopWindow();

   if (frame->ExistDbObject(otView, viewname, m_Base))
   {
      wxMessageBox(_("View or table with this name already exist."),
                   _("Error"));
      m_ViewName->SetFocus();
      return wxEmptyString;
   }

   // Création du DDL
   ddl = _T("CREATE ");
   if (m_TempView->IsChecked())
      ddl += _T("TEMPORARY ");
   ddl += _T("VIEW ");
   if (!m_TempView->IsChecked() && m_Base != wxEmptyString)
      ddl += m_Base + _T(".");
   ddl += _T("\"") + viewname.Lower() + _T("\" AS\n");
   ddl += query;
   if (query.Last() != _T(';'))
      ddl += _T(';');
/*
CREATE [TEMP | TEMPORARY] VIEW [IF NOT EXISTS] [database-name.] view-name AS select-statement
*/
   return ddl;
}
/*---------------------------------------------------------------------------*/
