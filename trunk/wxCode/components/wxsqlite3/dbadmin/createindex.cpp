/*---------------------------------------------------------------------------*/
/* Logiciel de gestion de fichier de bases de données SQLite                 */
/*---------------------------------------------------------------------------*/
/* Projet  : wxSQLitePlus                              Version  : 0.2.3.0    */
/* Fichier : createindex.cpp                                                 */
/* Auteur  : Fred Cailleau-Lepetit                     Date     : 15/07/2007 */
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
#pragma implementation "createindex.h"
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
#include "createindex.h"
#include "wxsqliteplusapp.h"
#include "sqliteplusframe.h"
#include "sqleditor.h"
/*---------------------------------------------------------------------------*/
#define ID_TEXTNAME     15001
#define ID_NOTEBOOK     15002
#define ID_PANELPROP    15003
#define ID_TABLENAME    15004
#define ID_UNIQUEINDEX  15005
#define ID_INDEXCOLUMNS 15006
#define ID_ADDBTN       15007
#define ID_REMOVEBTN    15008
#define ID_UPBTN        15009
#define ID_DOWNBTN      15010
#define ID_COLUMNS      15011
#define ID_ORDER        15012
#define ID_TEXTDDL      15013
/*---------------------------------------------------------------------------*/
IMPLEMENT_DYNAMIC_CLASS(wxCreateIndexDlg, wxDialog)

BEGIN_EVENT_TABLE(wxCreateIndexDlg, wxDialog)
   EVT_NOTEBOOK_PAGE_CHANGING(ID_NOTEBOOK, wxCreateIndexDlg::OnNotebookPageChanging)
   EVT_CHOICE(ID_TABLENAME, wxCreateIndexDlg::OnTablenameSelected)
   EVT_LISTBOX(ID_INDEXCOLUMNS, wxCreateIndexDlg::OnIndexcolumnsSelected)
   EVT_BUTTON(ID_ADDBTN, wxCreateIndexDlg::OnAddbtnClick)
   EVT_BUTTON(ID_REMOVEBTN, wxCreateIndexDlg::OnRemovebtnClick)
   EVT_BUTTON(ID_UPBTN, wxCreateIndexDlg::OnUpbtnClick)
   EVT_BUTTON(ID_DOWNBTN, wxCreateIndexDlg::OnDownbtnClick)
   EVT_CHOICE(ID_COLUMNS, wxCreateIndexDlg::OnColumnsSelected)
   EVT_BUTTON(wxID_OK, wxCreateIndexDlg::OnOkClick)
END_EVENT_TABLE()
/*---------------------------------------------------------------------------*/
wxCreateIndexDlg::wxCreateIndexDlg()
{
   Init();
}
/*---------------------------------------------------------------------------*/
wxCreateIndexDlg::wxCreateIndexDlg(wxWindow* parent, wxWindowID id,
                                   const wxString& caption, const wxPoint& pos,
                                   const wxSize& size, long style)
{
   Init();
   Create(parent, id, caption, pos, size, style);
}
/*---------------------------------------------------------------------------*/
bool wxCreateIndexDlg::Create(wxWindow* parent, wxWindowID id,
                              const wxString& caption, const wxPoint& pos,
                              const wxSize& size, long style)
{
   SetExtraStyle(wxWS_EX_BLOCK_EVENTS);
   wxDialog::Create(parent, id, caption, pos, size, style);

   CreateControls();
   SetIcon(wxGetApp().GetIcon(ID_ICO_INDEXE));
   if (GetSizer())
   {
      GetSizer()->SetSizeHints(this);
   }
   Centre();
   return true;
}
/*---------------------------------------------------------------------------*/
wxCreateIndexDlg::~wxCreateIndexDlg()
{
}
/*---------------------------------------------------------------------------*/
void wxCreateIndexDlg::Init()
{
   m_IndexName = NULL;
   m_TableName = NULL;
   m_UniqueIndex = NULL;
   m_IndexColumns = NULL;
   m_AddButton = NULL;
   m_RemoveButton = NULL;
   m_UpButton = NULL;
   m_DownButton = NULL;
   m_Columns = NULL;
   m_Order = NULL;
   m_Ddl = NULL;
   m_Db = NULL;
}
/*---------------------------------------------------------------------------*/
void wxCreateIndexDlg::CreateControls()
{
   wxBoxSizer* bSizer1 = new wxBoxSizer(wxVERTICAL);
   SetSizer(bSizer1);

   wxBoxSizer* bSizer2 = new wxBoxSizer(wxHORIZONTAL);
   bSizer1->Add(bSizer2, 0, wxGROW|wxALL, 5);

   wxStaticText* iStatic1 = new wxStaticText(this, wxID_STATIC, _("&Name : "),
                                             wxDefaultPosition, wxDefaultSize, 0);
   bSizer2->Add(iStatic1, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

   m_IndexName = new wxTextCtrl(this, ID_TEXTNAME, _T(""), wxDefaultPosition,
                                wxDefaultSize, 0);
   bSizer2->Add(m_IndexName, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5);

   wxNotebook* nBook1 = new wxNotebook(this, ID_NOTEBOOK, wxDefaultPosition,
                                       wxDefaultSize, wxBK_DEFAULT);

   wxPanel* panel1 = new wxPanel(nBook1, ID_PANELPROP, wxDefaultPosition,
                                 wxDefaultSize, wxTAB_TRAVERSAL);
   wxBoxSizer* bSizer3 = new wxBoxSizer(wxVERTICAL);
   panel1->SetSizer(bSizer3);

   wxBoxSizer* bSizer4 = new wxBoxSizer(wxHORIZONTAL);
   bSizer3->Add(bSizer4, 0, wxGROW, 0);
   wxStaticText* iStatic2 = new wxStaticText(panel1, wxID_STATIC,
                                             _("&Table : "), wxDefaultPosition,
                                             wxDefaultSize, 0);
   bSizer4->Add(iStatic2, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

   wxArrayString m_TableNameStrings;
   m_TableName = new wxChoice(panel1, ID_TABLENAME, wxDefaultPosition,
                              wxDefaultSize, m_TableNameStrings, 0);
   bSizer4->Add(m_TableName, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5);

   m_UniqueIndex = new wxCheckBox(panel1, ID_UNIQUEINDEX, _("&Unique"),
                                  wxDefaultPosition, wxDefaultSize, 0);
   m_UniqueIndex->SetValue(false);
   bSizer3->Add(m_UniqueIndex, 0, wxALIGN_LEFT|wxALL, 5);

   wxStaticText* iStatic3 = new wxStaticText(panel1, wxID_STATIC, _("&Index :"),
                                             wxDefaultPosition, wxDefaultSize, 0);
   bSizer3->Add(iStatic3, 0, wxALIGN_LEFT|wxALL, 5);

   wxBoxSizer* bSizer5 = new wxBoxSizer(wxHORIZONTAL);
   bSizer3->Add(bSizer5, 0, wxGROW, 0);
   m_IndexColumns = new wxListBox(panel1, ID_INDEXCOLUMNS, wxDefaultPosition,
                                  wxDefaultSize, 0, NULL, wxLB_SINGLE);
   bSizer5->Add(m_IndexColumns, 1, wxGROW|wxALL, 5);

   wxBoxSizer* bSizer6 = new wxBoxSizer(wxVERTICAL);
   bSizer5->Add(bSizer6, 0, wxGROW|wxALL, 5);
   m_AddButton = new wxBitmapButton(panel1, ID_ADDBTN,
                                    wxGetApp().GetBmp(ID_BMP_ADD),
                                    wxDefaultPosition, wxDefaultSize,
                                    wxBU_AUTODRAW|wxBU_EXACTFIT);
   m_AddButton->Enable(false);
   bSizer6->Add(m_AddButton, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

   m_RemoveButton = new wxBitmapButton(panel1, ID_REMOVEBTN,
                                       wxGetApp().GetBmp(ID_BMP_REMOVE),
                                       wxDefaultPosition, wxDefaultSize,
                                       wxBU_AUTODRAW|wxBU_EXACTFIT);
   m_RemoveButton->Enable(false);
   bSizer6->Add(m_RemoveButton, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

   m_UpButton = new wxBitmapButton(panel1, ID_UPBTN,
                                   wxGetApp().GetBmp(ID_BMP_COLUP),
                                   wxDefaultPosition, wxDefaultSize,
                                   wxBU_AUTODRAW|wxBU_EXACTFIT);
   m_UpButton->Enable(false);
   bSizer6->Add(m_UpButton, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

   m_DownButton = new wxBitmapButton(panel1, ID_DOWNBTN,
                                     wxGetApp().GetBmp(ID_BMP_COLDOWN),
                                     wxDefaultPosition, wxDefaultSize,
                                     wxBU_AUTODRAW|wxBU_EXACTFIT);
   m_DownButton->Enable(false);
   bSizer6->Add(m_DownButton, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

   wxBoxSizer* bSizer7 = new wxBoxSizer(wxHORIZONTAL);
   bSizer3->Add(bSizer7, 0, wxGROW, 0);
   wxBoxSizer* bSizer8 = new wxBoxSizer(wxVERTICAL);
   bSizer7->Add(bSizer8, 0, wxALIGN_CENTER_VERTICAL, 0);
   wxStaticText* iStatic4 = new wxStaticText(panel1, wxID_STATIC,
                                             _("&Column name :"),
                                             wxDefaultPosition, wxDefaultSize, 0);
   bSizer8->Add(iStatic4, 0, wxALIGN_LEFT|wxALL, 5);

   m_Columns = new wxChoice(panel1, ID_COLUMNS, wxDefaultPosition,
                            wxSize(200, -1), 0, NULL, 0);
   bSizer8->Add(m_Columns, 0, wxALIGN_LEFT|wxALL, 5);

   wxBoxSizer* bSizer9 = new wxBoxSizer(wxVERTICAL);
   bSizer7->Add(bSizer9, 0, wxALIGN_CENTER_VERTICAL, 0);
   wxStaticText* bSizer10 = new wxStaticText(panel1, wxID_STATIC, _("&Order :"),
                                             wxDefaultPosition, wxDefaultSize, 0);
   bSizer9->Add(bSizer10, 0, wxALIGN_LEFT|wxALL, 5);

   wxArrayString m_OrderStrings;
   m_OrderStrings.Add(_("ASC"));
   m_OrderStrings.Add(_("DESC"));
   m_Order = new wxChoice(panel1, ID_ORDER, wxDefaultPosition, wxSize(70, -1),
                          m_OrderStrings, 0);
   m_Order->SetStringSelection(_("ASC"));
   bSizer9->Add(m_Order, 0, wxALIGN_LEFT|wxALL, 5);

   nBook1->AddPage(panel1, _("Properties"));

   m_Ddl = new wxDDLEditor(nBook1, ID_TEXTDDL);

   nBook1->AddPage(m_Ddl, _("DDL"));

   bSizer1->Add(nBook1, 0, wxGROW|wxALL, 5);

   wxStdDialogButtonSizer* dBtnSizer1 = new wxStdDialogButtonSizer;

   bSizer1->Add(dBtnSizer1, 0, wxALIGN_RIGHT|wxALL, 5);
   wxButton* btnOk = new wxButton(this, wxID_OK, _("&OK"), wxDefaultPosition,
                                  wxDefaultSize, 0);
   btnOk->SetDefault();
   dBtnSizer1->AddButton(btnOk);

   wxButton* btnCancel = new wxButton(this, wxID_CANCEL, _("&Cancel"),
                                      wxDefaultPosition, wxDefaultSize, 0);
   dBtnSizer1->AddButton(btnCancel);

   dBtnSizer1->Realize();

   // Connect events and objects
   m_IndexName->Connect(ID_TEXTNAME, wxEVT_CHAR,
                        wxKeyEventHandler(wxCreateIndexDlg::OnChar), NULL, this);
}
/*---------------------------------------------------------------------------*/
void wxCreateIndexDlg::SetDatabase(wxSQLite3Database* db, const wxString& base)
{
   m_Db = db;
   m_Base = base;
   if (!m_Db||!m_Db->IsOpen())
      return;
   m_TableName->Clear();
   try
   {
      wxSQLite3ResultSet tblQRY;
      wxSQLitePlusFrame* frame;

      frame = (wxSQLitePlusFrame*)wxGetApp().GetTopWindow();

      tblQRY = frame->GetObjNameList(otTable, m_Base);

      while (tblQRY.NextRow())
         m_TableName->Append(tblQRY.GetString(0).Lower());
      tblQRY.Finalize();
   }
   catch(wxSQLite3Exception& ex)
   {
      wxGetApp().ShowError(_T("SetDatabase"), ex);
   }
}
/*---------------------------------------------------------------------------*/
void wxCreateIndexDlg::SetTable(const wxString& table)
{
   if (!m_Db||!m_Db->IsOpen())
      return;
   if (m_TableName->SetStringSelection(table))
   {
      DoTablenameSelected();
      m_TableName->Enable(false);
   }
}
/*---------------------------------------------------------------------------*/
void wxCreateIndexDlg::OnChar(wxKeyEvent& event)
{
   int c = event.GetKeyCode();
   if ((!wxIsalnum(c) && c != _T('_') && c != _T(' ') && c != WXK_BACK && c != WXK_DELETE)&&
      // Ctrl+C Ctrl+V Ctrl+X
       !(event.ControlDown() && (c == 3 || c == 22 || c == 24)))
      return;
   event.Skip();
}
/*---------------------------------------------------------------------------*/
void wxCreateIndexDlg::OnNotebookPageChanging(wxNotebookEvent& event)
{
   if (event.GetOldSelection() == 0)
   {
      wxString ddl = GetCreateIndexDDL();

      if (ddl.IsEmpty())
         event.Veto();
      else
         m_Ddl->SetValue(ddl);
   }
}
/*---------------------------------------------------------------------------*/
void wxCreateIndexDlg::OnTablenameSelected(wxCommandEvent& event)
{
   DoTablenameSelected();
   event.Skip();
}
/*---------------------------------------------------------------------------*/
void wxCreateIndexDlg::OnAddbtnClick(wxCommandEvent& event)
{
   wxString column, order;
   column = m_Columns->GetStringSelection();
   order = m_Order->GetStringSelection();
   if (!column.IsEmpty() && !order.IsEmpty())
   {
      m_IndexColumns->Append(_T("\"") + column + _T("\" ") + order);
      DoIndexcolumnsSelected();
   }
   event.Skip();
}
/*---------------------------------------------------------------------------*/
void wxCreateIndexDlg::OnRemovebtnClick(wxCommandEvent& event)
{
   int index = m_IndexColumns->GetSelection();
   if (index != wxNOT_FOUND)
   {
      m_IndexColumns->Delete((size_t)index);
      DoIndexcolumnsSelected();
   }
   event.Skip();
}
/*---------------------------------------------------------------------------*/
void wxCreateIndexDlg::OnUpbtnClick(wxCommandEvent& event)
{
   int index = m_IndexColumns->GetSelection();
   if (index != wxNOT_FOUND)
   {
      wxString selection = m_IndexColumns->GetStringSelection();
      m_IndexColumns->Delete(index);
      m_IndexColumns->Insert(selection, index - 1);
      m_IndexColumns->SetSelection(index - 1);
      DoIndexcolumnsSelected();
   }
   event.Skip();
}
/*---------------------------------------------------------------------------*/
void wxCreateIndexDlg::OnDownbtnClick(wxCommandEvent& event)
{
   int index = m_IndexColumns->GetSelection();
   if (index != wxNOT_FOUND)
   {
      wxString selection = m_IndexColumns->GetStringSelection();
      m_IndexColumns->Delete(index);
      m_IndexColumns->Insert(selection, index + 1);
      m_IndexColumns->SetSelection(index + 1);
      DoIndexcolumnsSelected();
   }
   event.Skip();
}
/*---------------------------------------------------------------------------*/
void wxCreateIndexDlg::OnOkClick(wxCommandEvent& event)
{
   if (GetCreateIndexDDL().IsEmpty())
      return;
   event.Skip();
}
/*---------------------------------------------------------------------------*/
bool wxCreateIndexDlg::ShowToolTips()
{
    return true;
}
/*---------------------------------------------------------------------------*/
wxString wxCreateIndexDlg::GetCreateIndexDDL()
{
   wxString ddl, indexname, tablename;
   wxSQLitePlusFrame* frame;

   if (!m_Db||!m_Db->IsOpen())
      return wxEmptyString;

   indexname = m_IndexName->GetValue();
   if (indexname.IsEmpty())
   {
      wxMessageBox(_("You have to enter an index name."),
                   _("Error"));
      m_IndexName->SetFocus();
      return wxEmptyString;
   }
   tablename = m_TableName->GetStringSelection();
   if (tablename.IsEmpty())
   {
      wxMessageBox(_("You have to select an table name."),
                   _("Error"));
      m_TableName->SetFocus();
      return wxEmptyString;
   }
   if (m_IndexColumns->GetCount() == 0)
   {
      wxMessageBox(_("You have to choose column(s) for the index."),
                   _("Error"));
      m_Columns->SetFocus();
      return wxEmptyString;
   }

   frame = (wxSQLitePlusFrame*)wxGetApp().GetTopWindow();

   if (frame->ExistDbObject(otIndex, indexname, m_Base))
   {
      wxMessageBox(_("Index with this name already exist."),
                   _("Error"));
      m_IndexName->SetFocus();
      return wxEmptyString;
   }

   ddl = _T("CREATE ");
   if (m_UniqueIndex-> IsChecked())
      ddl += _T("UNIQUE ");
   ddl += _T("INDEX ");
   if (m_Base != wxEmptyString)
      ddl += m_Base + _T(".");
   ddl += _T("\"") + indexname.Lower();
   ddl += _T("\" ON \"") + tablename + _T("\"\n(");
   for (size_t i = 0; i < m_IndexColumns->GetCount(); i++)
   {
      ddl += _T("\n   ") + m_IndexColumns->GetString(i);
      if (i != m_IndexColumns->GetCount() - 1)
         ddl += _T(",");
   }
   ddl += _T("\n);");
   return ddl;
}
/*---------------------------------------------------------------------------*/
void wxCreateIndexDlg::DoTablenameSelected()
{
   if (!m_Db||!m_Db->IsOpen())
      return;
   m_Columns->Clear();
   try
   {
      wxSQLite3ResultSet clmnQRY;
      wxString tablename, sql, basename;
      tablename = m_TableName->GetStringSelection();
      if (m_Base != wxEmptyString)
         basename = m_Base;
      else
         basename = _T("main");
      sql = wxString::Format(_T("PRAGMA %s.table_info(\"%s\");"),
                             basename.c_str(), tablename.c_str());
      clmnQRY = m_Db->ExecuteQuery(ToUTF8(sql));
      while (clmnQRY.NextRow())
         m_Columns->Append(clmnQRY.GetString(1).Lower());
      clmnQRY.Finalize();
   }
   catch(wxSQLite3Exception& ex)
   {
      wxGetApp().ShowError(_T("DoTablenameSelected"), ex);
   }
}
/*---------------------------------------------------------------------------*/
void wxCreateIndexDlg::OnIndexcolumnsSelected(wxCommandEvent& event)
{
  wxUnusedVar(event);
   DoIndexcolumnsSelected();
}
/*---------------------------------------------------------------------------*/
void wxCreateIndexDlg::OnColumnsSelected(wxCommandEvent& event)
{
  wxUnusedVar(event);
   bool b_enable = false;
   if (m_Columns->GetSelection() != wxNOT_FOUND)
      b_enable = true;
   m_AddButton->Enable(b_enable);
}
/*---------------------------------------------------------------------------*/
void wxCreateIndexDlg::DoIndexcolumnsSelected()
{
   bool b_enableRem = false;
   bool b_enableUp = false;
   bool b_enableDown = false;
   if (m_IndexColumns->GetSelection() != wxNOT_FOUND)
      b_enableRem = true;
   m_RemoveButton->Enable(b_enableRem);
   if (m_IndexColumns->GetSelection() > 0)
      b_enableUp = true;
   m_UpButton->Enable(b_enableUp);
   int c = m_IndexColumns->GetCount();
   if (c > 1 && m_IndexColumns->GetSelection() < c - 1)
      b_enableDown = true;
   m_DownButton->Enable(b_enableDown);
}
/*---------------------------------------------------------------------------*/
