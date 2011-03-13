/*---------------------------------------------------------------------------*/
/* Logiciel de gestion de fichier de bases de données SQLite                 */
/*---------------------------------------------------------------------------*/
/* Projet  : wxSQLitePlus                              Version  : 0.2.3.0    */
/* Fichier : aboutdlg.cpp                                                    */
/* Auteur  : Fred Cailleau-Lepetit                     Date     : 09/09/2007 */
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
#pragma implementation "aboutdlg.h"
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
#define ID_TEXTPANEL 15001
/*---------------------------------------------------------------------------*/
#include "aboutdlg.h"
#include "wxsqliteplusapp.h"
/*---------------------------------------------------------------------------*/
IMPLEMENT_DYNAMIC_CLASS( wxAboutDlg, wxDialog )

BEGIN_EVENT_TABLE( wxAboutDlg, wxDialog )

END_EVENT_TABLE()
/*---------------------------------------------------------------------------*/
wxAboutDlg::wxAboutDlg()
{
   Init();
}
/*---------------------------------------------------------------------------*/
wxAboutDlg::wxAboutDlg(wxWindow* parent, wxWindowID id, const wxString& caption,
                       const wxPoint& pos, const wxSize& size, long style)
{
   Init();
   Create(parent, id, caption, pos, size, style);
}
/*---------------------------------------------------------------------------*/
bool wxAboutDlg::Create(wxWindow* parent, wxWindowID id, const wxString& caption,
                        const wxPoint& pos, const wxSize& size, long style)
{
   SetExtraStyle(wxWS_EX_BLOCK_EVENTS);
   wxDialog::Create( parent, id, caption, pos, size, style );

   CreateControls();
   SetIcon(wxGetApp().GetIcon(ID_ICO_LOGO32));
   SetTitle(wxString::Format(_("About %s"), wxGetApp().GetInternalName().c_str()));
   if (GetSizer())
   {
      GetSizer()->SetSizeHints(this);
   }
   Centre();

   return true;
}
/*---------------------------------------------------------------------------*/
wxAboutDlg::~wxAboutDlg()
{
}
/*---------------------------------------------------------------------------*/
void wxAboutDlg::Init()
{
   m_AppName = NULL;
   m_AppDescription = NULL;
   m_AppCopyright = NULL;
}
/*---------------------------------------------------------------------------*/
void wxAboutDlg::CreateControls()
{
   wxString tmp;

   wxBoxSizer* bSizer1 = new wxBoxSizer(wxVERTICAL);
   SetSizer(bSizer1);

   wxBoxSizer* bSizer2 = new wxBoxSizer(wxHORIZONTAL);
   bSizer1->Add(bSizer2, 1, wxGROW|wxALL, 5);

   wxBoxSizer* bSizer3 = new wxBoxSizer(wxVERTICAL);
   bSizer2->Add(bSizer3, 0, wxGROW, 0);

   wxStaticBitmap* bmpLogo = new wxStaticBitmap(this, wxID_STATIC,
                                                wxGetApp().GetBmp(ID_BMP_LOGO32),
                                                wxDefaultPosition,
                                                wxSize(128, 128), 0);
   bSizer3->Add(bmpLogo, 0, wxALIGN_LEFT, 0);

   bSizer3->Add(5, 5, 1, wxALIGN_LEFT, 0);

   wxPanel* panelText = new wxPanel(this, ID_TEXTPANEL, wxDefaultPosition,
                                    wxDefaultSize,
                                    wxSUNKEN_BORDER|wxTAB_TRAVERSAL);
   bSizer2->Add(panelText, 1, wxGROW|wxALL, 5);

   wxBoxSizer* bSizer4 = new wxBoxSizer(wxVERTICAL);
   panelText->SetSizer(bSizer4);

   tmp = wxGetApp().GetInternalName() + _T(" v") + wxGetApp().GetFileVersion();
   m_AppName = new wxStaticText(panelText, wxID_STATIC, tmp, wxDefaultPosition,
                                wxDefaultSize, 0);
   bSizer4->Add(m_AppName, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

   tmp = wxGetApp().GetFileDescription();
   m_AppDescription = new wxStaticText(panelText, wxID_STATIC, tmp,
                                       wxDefaultPosition, wxDefaultSize, 0);
   bSizer4->Add(m_AppDescription, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

   bSizer4->Add(5, 100, 1, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

   tmp = wxGetApp().GetLegalCopyright();
   m_AppCopyright = new wxStaticText(panelText, wxID_STATIC, tmp,
                                     wxDefaultPosition, wxDefaultSize, 0);
   bSizer4->Add(m_AppCopyright, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

   bSizer4->Add(5, 5, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

   tmp = wxString::Format(_("%s comes with ABSOLUTELY NO WARRANTY.\nThis is free software, and you are welcome to redistribute it\nunder certain conditions. For details read the file gpl.txt.\n"),
                          wxGetApp().GetInternalName().c_str());
   wxStaticText* sText1 = new wxStaticText(panelText, wxID_STATIC, tmp,
                                           wxDefaultPosition, wxDefaultSize, 0);
   bSizer4->Add(sText1, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

   wxBoxSizer* bSizer5 = new wxBoxSizer(wxHORIZONTAL);
   bSizer1->Add(bSizer5, 0, wxGROW, 0);

   wxStaticBitmap* bmpPowered = new wxStaticBitmap(this, wxID_STATIC,
                                                   wxGetApp().GetBmp(ID_BMP_POWEREDBYSQLITE),
                                                   wxDefaultPosition,
                                                   wxSize(140, 53), 0);
   bSizer5->Add(bmpPowered, 0, wxALIGN_BOTTOM, 0);

   bSizer5->Add(5, 5, 1, wxALIGN_CENTER_VERTICAL, 0);

   wxButton* btnCancel = new wxButton(this, wxID_OK, _("&OK"),
                                      wxDefaultPosition, wxDefaultSize, 0);
   btnCancel->SetDefault();
   bSizer5->Add(btnCancel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);
}
/*---------------------------------------------------------------------------*/
bool wxAboutDlg::ShowToolTips()
{
   return true;
}
/*---------------------------------------------------------------------------*/
