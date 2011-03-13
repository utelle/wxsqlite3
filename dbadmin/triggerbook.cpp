/*---------------------------------------------------------------------------*/
/* Logiciel de gestion de fichier de bases de données SQLite                 */
/*---------------------------------------------------------------------------*/
/* Projet  : wxSQLitePlus                              Version  : 0.2.0.0    */
/* Fichier : triggerbook.cpp                                                 */
/* Auteur  : Fred Cailleau-Lepetit                     Date     : 25/07/2007 */
/* email   : softinthebox@free.fr                      Révision : 27/03/2008 */
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
#pragma implementation "triggerbook.h"
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
#include "triggerbook.h"
#include "sqlite3table.h"
#include "wxsqliteplusapp.h"
#include "sqliteplusframe.h"
/*---------------------------------------------------------------------------*/
#define ID_PAGEDDL 15001
/*---------------------------------------------------------------------------*/
IMPLEMENT_DYNAMIC_CLASS(wxTriggerBook, wxDbBook)

BEGIN_EVENT_TABLE(wxTriggerBook, wxDbBook)
   EVT_MENU(wxID_COPY, wxTriggerBook::OnCopyClick)
   EVT_UPDATE_UI(wxID_COPY, wxTriggerBook::OnCopyUpdate)
   EVT_MENU(ID_CMD_ED_REFRESH, wxTriggerBook::OnEdRefresh)
END_EVENT_TABLE()
/*---------------------------------------------------------------------------*/
wxTriggerBook::wxTriggerBook()
{
   Init();
}
/*---------------------------------------------------------------------------*/
wxTriggerBook::wxTriggerBook(wxWindow* parent, wxWindowID id,
                             const wxPoint& pos, const wxSize& size, long style)
{
   Init();
   Create(parent, id, pos, size, style);
}
/*---------------------------------------------------------------------------*/
bool wxTriggerBook::Create(wxWindow* parent, wxWindowID id, const wxPoint& pos,
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
wxTriggerBook::~wxTriggerBook()
{
}
/*---------------------------------------------------------------------------*/
void wxTriggerBook::Init()
{
   m_PageDdl = NULL;
}
/*---------------------------------------------------------------------------*/
void wxTriggerBook::CreateControls()
{    
   wxBoxSizer* bSizer = new wxBoxSizer(wxHORIZONTAL);
   SetSizer(bSizer);
   
   m_PageDdl = new wxDDLEditor(this, ID_PAGEDDL);
   bSizer->Add(m_PageDdl, 1, wxGROW, 0);
}
/*---------------------------------------------------------------------------*/
bool wxTriggerBook::ShowToolTips(){return true;}
/*---------------------------------------------------------------------------*/
void wxTriggerBook::SetDbObjectName(wxSQLite3Database* db,
                                    const wxString objectname,
                                    const wxString& base)
{
   wxDbBook::SetDbObjectName(db, objectname, base);
   RefreshDbObject();
}
/*---------------------------------------------------------------------------*/
void wxTriggerBook::RefreshDbObject()
{
   if (!m_db || m_DbObjectName.IsEmpty())
      return;

   wxSQLitePlusFrame* frame;
   wxString sql, basename;
   wxSQLite3ResultSet resultSet;

   if (m_Base != wxEmptyString)
      basename = m_Base;
   else
      basename = _T("main");

   frame = (wxSQLitePlusFrame*)wxGetApp().GetTopWindow();
   m_PageDdl->SetValue(frame->GetDbObjectDDL(otTrigger, m_DbObjectName, basename));
}
/*---------------------------------------------------------------------------*/
void wxTriggerBook::OnCopyClick(wxCommandEvent& event)
{
   wxWindow* window = FindFocus();

   if (window && (window == m_PageDdl))
      window->GetEventHandler()->ProcessEvent(event);
}
/*---------------------------------------------------------------------------*/
void wxTriggerBook::OnCopyUpdate(wxUpdateUIEvent& event)
{
   wxWindow* window = FindFocus();

   if (window && (window == m_PageDdl))
      window->GetEventHandler()->ProcessEvent(event);
   else
      event.Enable(false);
}
/*---------------------------------------------------------------------------*/
void wxTriggerBook::OnEdRefresh(wxCommandEvent& event)
{
  wxUnusedVar(event);
   m_PageDdl->InitStyle();
}
/*---------------------------------------------------------------------------*/
