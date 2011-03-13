/*---------------------------------------------------------------------------*/
/* Logiciel de gestion de fichier de bases de données SQLite                 */
/*---------------------------------------------------------------------------*/
/* Projet  : wxSQLitePlus                              Version  : 0.2.1.0    */
/* Fichier : dbbook.cpp                                                      */
/* Auteur  : Fred Cailleau-Lepetit                     Date     : 29/07/2007 */
/* email   : softinthebox@free.fr                      Révision : 04/05/2008 */
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
#pragma implementation "dbbook.h"
#endif

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "dbbook.h"
#include "sqlite3table.h"
/*---------------------------------------------------------------------------*/
IMPLEMENT_CLASS(wxDbBook, wxPanel)
/*---------------------------------------------------------------------------*/
wxDbBook::wxDbBook()
{
   Init();
}
/*---------------------------------------------------------------------------*/
wxDbBook::wxDbBook(wxWindow* parent, wxWindowID id, const wxPoint& pos,
                   const wxSize& size, long style)
{
   Init();
   Create(parent, id, pos, size, style);
}
/*---------------------------------------------------------------------------*/
bool wxDbBook::Create(wxWindow* parent, wxWindowID id, const wxPoint& pos,
                      const wxSize& size, long style)
{
   wxPanel::Create( parent, id, pos, size, style );
   return true;
}
/*---------------------------------------------------------------------------*/
wxDbBook::~wxDbBook()
{
}
/*---------------------------------------------------------------------------*/
void wxDbBook::Init()
{
   m_db = NULL;
}
/*---------------------------------------------------------------------------*/
void wxDbBook::SetDbObjectName(wxSQLite3Database* db,
                               const wxString objectname, const wxString& base)
{
   m_db = db;
   m_Base = base;
   m_DbObjectName = objectname;
}                               
/*---------------------------------------------------------------------------*/
