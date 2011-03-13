/*---------------------------------------------------------------------------*/
/* Logiciel de gestion de fichier de bases de données SQLite                 */
/*---------------------------------------------------------------------------*/
/* Projet  : wxSQLitePlus                              Version  : 0.2.3.0    */
/* Fichier : encrypkeydlg.cpp                                                 */
/* Auteur  : Fred Cailleau-Lepetit                     Date     : 08/11/2008 */
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
#pragma implementation "encrypkeydlg.h"
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
#include "encrypkeydlg.h"
/*---------------------------------------------------------------------------*/
#define ID_KEY       15001
/*---------------------------------------------------------------------------*/
IMPLEMENT_DYNAMIC_CLASS(wxDbEncryptionKeyDlg, wxDialog)

BEGIN_EVENT_TABLE(wxDbEncryptionKeyDlg, wxDialog)
END_EVENT_TABLE()
/*---------------------------------------------------------------------------*/
wxDbEncryptionKeyDlg::wxDbEncryptionKeyDlg()
{
   Init();
}
/*---------------------------------------------------------------------------*/
wxDbEncryptionKeyDlg::wxDbEncryptionKeyDlg(wxWindow* parent, wxWindowID id,
                                           const wxString& caption,
                                           const wxPoint& pos,
                                           const wxSize& size, long style)
{
   Init();
   Create(parent, id, caption, pos, size, style);
}
/*---------------------------------------------------------------------------*/
bool wxDbEncryptionKeyDlg::Create(wxWindow* parent, wxWindowID id,
                                  const wxString& caption, const wxPoint& pos,
                                  const wxSize& size, long style)
{
   SetExtraStyle(wxWS_EX_BLOCK_EVENTS);
   wxDialog::Create(parent, id, caption, pos, size, style);

   CreateControls();
   if (GetSizer())
      GetSizer()->SetSizeHints(this);
   Centre();
   return true;
}
/*---------------------------------------------------------------------------*/
wxDbEncryptionKeyDlg::~wxDbEncryptionKeyDlg()
{
}
/*---------------------------------------------------------------------------*/
void wxDbEncryptionKeyDlg::Init()
{
   m_EdKey = NULL;
}
/*---------------------------------------------------------------------------*/
void wxDbEncryptionKeyDlg::CreateControls()
{
   wxBoxSizer* bSizer1 = new wxBoxSizer(wxVERTICAL);
   SetSizer(bSizer1);

   wxStaticText* sText1 = new wxStaticText(this, wxID_STATIC,
                                           _("Enter encryption key (let empty for no encryption)"),
                                           wxDefaultPosition, wxDefaultSize, 0);
   bSizer1->Add(sText1, 0, wxALIGN_LEFT|wxALL, 5);

   m_EdKey = new wxTextCtrl(this, ID_KEY, wxEmptyString, wxDefaultPosition,
                          wxSize(250, -1), wxTE_PASSWORD);
   bSizer1->Add(m_EdKey, 0, wxGROW|wxALL, 5);

   wxStdDialogButtonSizer* dlgBtnSizer1 = new wxStdDialogButtonSizer;

   bSizer1->Add(dlgBtnSizer1, 0, wxALIGN_RIGHT|wxALL, 5);
   wxButton* btnOk = new wxButton(this, wxID_OK, _("&OK"),
                                  wxDefaultPosition, wxDefaultSize, 0);
   btnOk->SetDefault();
   dlgBtnSizer1->AddButton(btnOk);

   wxButton* btnCancel = new wxButton(this, wxID_CANCEL, _("&Cancel"),
                                      wxDefaultPosition, wxDefaultSize, 0);
   dlgBtnSizer1->AddButton(btnCancel);

   dlgBtnSizer1->Realize();

   // Set validators
   m_EdKey->SetValidator(wxTextValidator(wxFILTER_NONE, &m_Key));

   m_EdKey->SetFocus();
}
/*---------------------------------------------------------------------------*/
bool wxDbEncryptionKeyDlg::ShowToolTips()
{
   return true;
}
/*---------------------------------------------------------------------------*/
