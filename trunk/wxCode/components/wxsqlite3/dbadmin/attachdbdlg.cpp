/*---------------------------------------------------------------------------*/
/* Logiciel de gestion de fichier de bases de données SQLite                 */
/*---------------------------------------------------------------------------*/
/* Projet  : wxSQLitePlus                              Version  : 0.2.3.0    */
/* Fichier : attachdbdlg.cpp                                                 */
/* Auteur  : Fred Cailleau-Lepetit                     Date     : 03/02/2008 */
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
#pragma implementation "attachdbdlg.h"
#endif

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <wx/valtext.h>
#include <wx/filedlg.h>
/*---------------------------------------------------------------------------*/
#include "attachdbdlg.h"
#include "wxsqliteplusapp.h"
/*---------------------------------------------------------------------------*/
#define ID_FILENAME  15001
#define ID_ATTACHBTN 15002
#define ID_ALIAS     15003
#define ID_KEY       15004
/*---------------------------------------------------------------------------*/
IMPLEMENT_DYNAMIC_CLASS(wxAttachDbDlg, wxDialog)

BEGIN_EVENT_TABLE(wxAttachDbDlg, wxDialog)
   EVT_BUTTON(ID_ATTACHBTN, wxAttachDbDlg::OnAttachbtnClick)
   EVT_BUTTON(wxID_OK, wxAttachDbDlg::OnOkClick)
END_EVENT_TABLE()
/*---------------------------------------------------------------------------*/
wxAttachDbDlg::wxAttachDbDlg()
{
   Init();
}
/*---------------------------------------------------------------------------*/
wxAttachDbDlg::wxAttachDbDlg(wxWindow* parent, wxWindowID id,
                             const wxString& caption, const wxPoint& pos,
                             const wxSize& size, long style)
{
   Init();
   Create(parent, id, caption, pos, size, style);
}
/*---------------------------------------------------------------------------*/
bool wxAttachDbDlg::Create(wxWindow* parent, wxWindowID id,
                           const wxString& caption, const wxPoint& pos,
                           const wxSize& size, long style)
{
   SetExtraStyle(wxWS_EX_BLOCK_EVENTS);
   wxDialog::Create(parent, id, caption, pos, size, style);

   CreateControls();
   SetIcon(wxGetApp().GetIcon(ID_ICO_DATABASE));
   if (GetSizer())
   {
      GetSizer()->SetSizeHints(this);
   }
   Centre();
   return true;
}
/*---------------------------------------------------------------------------*/
wxAttachDbDlg::~wxAttachDbDlg()
{
}
/*---------------------------------------------------------------------------*/
void wxAttachDbDlg::SetDatabase(wxSQLite3Database* db)
{
   m_Db = db;
   if (!m_Db||!m_Db->IsOpen())
      m_Db = NULL;
}
/*---------------------------------------------------------------------------*/
void wxAttachDbDlg::Init()
{
   m_BtnAttach = NULL;
   m_EdFilename = NULL;
   m_EdAlias = NULL;
   m_EdKey = NULL;
   m_Db = NULL;
}
/*---------------------------------------------------------------------------*/
void wxAttachDbDlg::CreateControls()
{
   wxBoxSizer* bSizer1 = new wxBoxSizer(wxVERTICAL);
   SetSizer(bSizer1);

   wxStaticText* sText1 = new wxStaticText(this, wxID_STATIC, _("File name :"),
                                           wxDefaultPosition, wxDefaultSize, 0);
   bSizer1->Add(sText1, 0, wxALIGN_LEFT|wxALL, 5);

   wxBoxSizer* bSizer2 = new wxBoxSizer(wxHORIZONTAL);
   bSizer1->Add(bSizer2, 0, wxGROW|wxALL, 0);

   m_EdFilename = new wxTextCtrl(this, ID_FILENAME, wxEmptyString,
                                 wxDefaultPosition, wxSize(250, -1), 0);
   bSizer2->Add(m_EdFilename, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5);

   m_BtnAttach = new wxBitmapButton(this, ID_ATTACHBTN,
                                    wxGetApp().GetBmp(ID_BMP_OPENDB),
                                    wxDefaultPosition,
                                    wxDefaultSize, wxBU_AUTODRAW);
   bSizer2->Add(m_BtnAttach, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

   wxStaticText* sText2 = new wxStaticText(this, wxID_STATIC, _("Alias :"),
                                           wxDefaultPosition, wxDefaultSize, 0);
   bSizer1->Add(sText2, 0, wxALIGN_LEFT|wxALL, 5);

   m_EdAlias = new wxTextCtrl(this, ID_ALIAS, wxEmptyString, wxDefaultPosition,
                              wxDefaultSize, 0);
   bSizer1->Add(m_EdAlias, 0, wxGROW|wxALL, 5);

   wxStaticText* sText3 = new wxStaticText(this, wxID_STATIC,
                                           _("Enter encryption key: (let empty for no encryption)"),
                                           wxDefaultPosition, wxDefaultSize, 0);
   bSizer1->Add(sText3, 0, wxALIGN_LEFT|wxALL, 5);

   m_EdKey = new wxTextCtrl(this, ID_KEY, wxEmptyString, wxDefaultPosition,
                          wxDefaultSize, wxTE_PASSWORD);
   bSizer1->Add(m_EdKey, 0, wxGROW|wxALL, 5);

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

   // Set validators
   m_EdFilename->SetValidator(wxTextValidator(wxFILTER_NONE, &m_FileName));
   m_EdAlias->SetValidator(wxTextValidator(wxFILTER_NONE, &m_Alias));
   m_EdKey->SetValidator(wxTextValidator(wxFILTER_NONE, &m_Key));

   // Connect events and objects
   m_EdAlias->Connect(ID_ALIAS, wxEVT_CHAR,
                      wxKeyEventHandler(wxAttachDbDlg::OnChar), NULL, this);

   m_EdFilename->SetFocus();
}
/*---------------------------------------------------------------------------*/
bool wxAttachDbDlg::ShowToolTips()
{
   return true;
}
/*---------------------------------------------------------------------------*/
void wxAttachDbDlg::OnlyKey()
{
   m_BtnAttach->Enable (false);
   m_EdFilename->Enable (false);
   m_EdAlias->Enable (false);
   m_EdKey->SetFocus();
}
/*---------------------------------------------------------------------------*/
void wxAttachDbDlg::OnAttachbtnClick(wxCommandEvent& event)
{
  wxUnusedVar(event);
   wxFileDialog fileDialog(this, _("Attach database"), wxEmptyString,
                           wxEmptyString,
                           _("SQLite files (*.db)|*.db|All files (*.*)|*.*"),
                           wxFD_OPEN/*|wxFILE_MUST_EXIST*/);
   if (fileDialog.ShowModal() == wxID_OK)
   {
      m_EdFilename->SetValue(fileDialog.GetPath());
   }
}
/*---------------------------------------------------------------------------*/
void wxAttachDbDlg::OnOkClick(wxCommandEvent& event)
{
   wxSQLite3ResultSet dbQRY;
   wxString alias;

   if (!m_Db||!m_Db->IsOpen())
      return;

   if (m_EdFilename->GetValue().IsEmpty())
   {
      wxMessageBox(_("You have to enter a file name."),
                   _("Error"));
      m_EdFilename->SetFocus();
      return;
   }
   if (m_EdAlias->GetValue().IsEmpty())
   {
      wxMessageBox(_("You have to enter an alias name."),
                   _("Error"));
      m_EdAlias->SetFocus();
      return;
   }

   alias = m_EdAlias->GetValue().Lower();
   try
   {
      dbQRY = m_Db->ExecuteQuery(ToUTF8(_T("PRAGMA database_list;")));
      while (dbQRY.NextRow())
      {
         if (dbQRY.GetString(1) == alias)
         {
            wxMessageBox(_("This alias already exist."),
                         _("Error"));
            m_EdAlias->SetFocus();
            dbQRY.Finalize();
            return;
         }
      }
   }
   catch(wxSQLite3Exception& ex)
   {
      wxGetApp().ShowError(_T("OnOkClick"), ex);
   }
   dbQRY.Finalize();
   event.Skip();
}
/*---------------------------------------------------------------------------*/
void wxAttachDbDlg::OnChar(wxKeyEvent& event)
{
   int c = event.GetKeyCode();
   if ((!wxIsalnum(c) && c != _T('_') && c != WXK_BACK &&
        c != WXK_DELETE && c != WXK_TAB)&&
      // Ctrl+C Ctrl+V Ctrl+X
       !(event.ControlDown() && (c == 3 || c == 22 || c == 24)))
      return;
   event.Skip();
}
/*---------------------------------------------------------------------------*/
