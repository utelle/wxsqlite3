/*---------------------------------------------------------------------------*/
/* Logiciel de gestion de fichier de bases de données SQLite                 */
/*---------------------------------------------------------------------------*/
/* Projet  : wxSQLitePlus                              Version  : 0.3.0.0    */
/* Fichier : backrestdlg.cpp                                                 */
/* Auteur  : Fred Cailleau-Lepetit                     Date     : 26/04/2009 */
/* email   : softinthebox@free.fr                      Révision : 16/05/2009 */
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
#pragma implementation "backrestdlg.h"
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
#include <wx/filename.h>
/*---------------------------------------------------------------------------*/
#include "backrestdlg.h"
#include "wxsqliteplusapp.h"
/*---------------------------------------------------------------------------*/
#define ID_FILENAME     15001
#define ID_GETFILEBTN   15002
#define ID_KEY          15003
#define ID_CHOICE       15004
/*---------------------------------------------------------------------------*/
IMPLEMENT_DYNAMIC_CLASS(wxBackupRestoreDbDlg, wxDialog)

BEGIN_EVENT_TABLE(wxBackupRestoreDbDlg, wxDialog )
   EVT_BUTTON(ID_GETFILEBTN, wxBackupRestoreDbDlg::OnGetfilebtnClick)
   EVT_BUTTON(wxID_OK, wxBackupRestoreDbDlg::OnOkClick)
END_EVENT_TABLE()
/*---------------------------------------------------------------------------*/
wxBackupRestoreDbDlg::wxBackupRestoreDbDlg()
{
   Init();
}
/*---------------------------------------------------------------------------*/
wxBackupRestoreDbDlg::wxBackupRestoreDbDlg(wxWindow* parent, bool backup,
                                           wxWindowID id, const wxPoint& pos,
                                           const wxSize& size, long style)
{
   Init();
   Create(parent, backup, id, pos, size, style);
}
/*---------------------------------------------------------------------------*/
bool wxBackupRestoreDbDlg::Create(wxWindow* parent, bool backup, wxWindowID id,
                                  const wxPoint& pos, const wxSize& size,
                                  long style)
{
   m_BackUp  = backup;
   SetExtraStyle(wxWS_EX_BLOCK_EVENTS);
   wxDialog::Create(parent, id, (m_BackUp ? _("Backup Database") :
                                           _("Restore Database")),
                    pos, size, style);
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
wxBackupRestoreDbDlg::~wxBackupRestoreDbDlg()
{
}
/*---------------------------------------------------------------------------*/
void wxBackupRestoreDbDlg::Init()
{
   m_EdFilename = NULL;
   m_EdKey = NULL;
   m_Database = NULL;
   m_BackUp = true;
}
/*---------------------------------------------------------------------------*/
void wxBackupRestoreDbDlg::CreateControls()
{
   wxString FileName;
   wxString DatabaseName;

   if (m_BackUp)
   {
      FileName = _("File name (target):");
      DatabaseName = _("Database (source):");
   }
   else
   {
      FileName = _("File name (source):");
      DatabaseName = _("Database (target):");
   }

   wxBoxSizer* bSizer1 = new wxBoxSizer(wxVERTICAL);
   SetSizer(bSizer1);

   wxStaticText* sText1 = new wxStaticText(this, wxID_STATIC, FileName,
                                           wxDefaultPosition, wxDefaultSize, 0);
   bSizer1->Add(sText1, 0, wxALIGN_LEFT|wxALL, 5);

   wxBoxSizer* bSizer2 = new wxBoxSizer(wxHORIZONTAL);
   bSizer1->Add(bSizer2, 0, wxGROW|wxALL, 0);

   m_EdFilename = new wxTextCtrl(this, ID_FILENAME, wxEmptyString,
                                 wxDefaultPosition, wxSize(250, -1), 0);
   bSizer2->Add(m_EdFilename, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5);

   wxBitmapButton* btnOpenDb = new wxBitmapButton(this, ID_GETFILEBTN,
                                                  wxGetApp().GetBmp(ID_BMP_OPENDB),
                                                  wxDefaultPosition, wxDefaultSize,
                                                  wxBU_AUTODRAW);
   bSizer2->Add(btnOpenDb, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

   wxStaticText* sText2 = new wxStaticText(this, wxID_STATIC,
                                           _("Enter encryption key: (let empty for no encryption)"),
                                           wxDefaultPosition, wxDefaultSize, 0);
   bSizer1->Add(sText2, 0, wxALIGN_LEFT|wxALL, 5);

   m_EdKey = new wxTextCtrl(this, ID_KEY, wxEmptyString, wxDefaultPosition,
                            wxDefaultSize, wxTE_PASSWORD);
   bSizer1->Add(m_EdKey, 0, wxGROW|wxALL, 5);

   wxStaticText* sText3 = new wxStaticText(this, wxID_STATIC, DatabaseName,
                                           wxDefaultPosition, wxDefaultSize, 0);
   bSizer1->Add(sText3, 0, wxALIGN_LEFT|wxALL, 5);

   wxArrayString m_DatabaseStrings;
   m_Database = new wxChoice(this, ID_CHOICE, wxDefaultPosition, wxDefaultSize,
                             m_DatabaseStrings, 0);
   bSizer1->Add(m_Database, 0, wxGROW|wxALL, 5);

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

   m_EdFilename->SetValidator(wxTextValidator(wxFILTER_NONE, & m_FileName));
   m_EdKey->SetValidator(wxTextValidator(wxFILTER_NONE, & m_Key));
}
/*---------------------------------------------------------------------------*/
void wxBackupRestoreDbDlg::OnGetfilebtnClick(wxCommandEvent& event)
{
  wxUnusedVar(event);
   wxString dlgtitle;
   int style;

   if (m_BackUp)
   {
      dlgtitle = _("Target database");
      style = wxFD_OPEN;
   }
   else
   {
      dlgtitle = _("Source database");
      style = wxFD_OPEN|wxFD_FILE_MUST_EXIST;
   }

   wxFileDialog fileDialog(this, dlgtitle, wxEmptyString,
                           wxEmptyString,
                           _("SQLite files (*.db)|*.db|All files (*.*)|*.*"),
                           style);
   if (fileDialog.ShowModal() == wxID_OK)
   {
      m_EdFilename->SetValue(fileDialog.GetPath());
   }
}
/*---------------------------------------------------------------------------*/
void wxBackupRestoreDbDlg::OnOkClick(wxCommandEvent& event)
{
   wxString filename;

   filename = m_EdFilename->GetValue();
   if (filename.IsEmpty())
   {
      wxMessageBox(_("You have to enter a file name."), _("Error"));
      m_EdFilename->SetFocus();
      return;
   }
   if (m_BackUp)
   {
      wxFileName FileNameObject(filename);
      // Check if the file could be created
      if (!wxDirExists(FileNameObject.GetPath()))
      {
         wxMessageBox(_("Please choose an existing directory."), _("Error"));
         m_EdFilename->SetFocus();
         return;
      }
      if (!FileNameObject.IsOk())
      {
         wxMessageBox(_("Please choose a correct file name."), _("Error"));
         m_EdFilename->SetFocus();
         return;
      }
   }
   else
   {
      // Check if the file exists
      if (!wxFileExists(filename))
      {
         wxMessageBox(_("Please choose an existing file."), _("Error"));
         m_EdFilename->SetFocus();
         return;
      }
   }
   event.Skip();
}
/*---------------------------------------------------------------------------*/
void wxBackupRestoreDbDlg::SetDatabase(wxSQLite3Database* db, const wxString& base)
{
   wxSQLite3ResultSet dbQRY;
   wxString alias;

   m_Db = db;
   if (!m_Db||!m_Db->IsOpen())
      m_Db = NULL;
   else
   {
      try
      {
         dbQRY = m_Db->ExecuteQuery(ToUTF8(_T("PRAGMA database_list;")));
         while (dbQRY.NextRow())
         {
            alias = dbQRY.GetString(1);
            m_Database->Append(alias);
         }
         m_Database->SetStringSelection(base);
      }
      catch(wxSQLite3Exception& ex)
      {
         wxGetApp().ShowError(_T("SetDatabase"), ex);
      }
      dbQRY.Finalize();
   }
}
/*---------------------------------------------------------------------------*/
bool wxBackupRestoreDbDlg::ShowToolTips()
{
   return true;
}
/*---------------------------------------------------------------------------*/
