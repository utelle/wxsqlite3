/*---------------------------------------------------------------------------*/
/* Logiciel de gestion de fichier de base de donn�esSQLite                   */
/*---------------------------------------------------------------------------*/
/* Projet  : wxSQLitePlus                              Version  : 0.2.1.0    */
/* Fichier : dbbook.h                                                        */
/* Auteur  : Fred Cailleau-Lepetit                     Date     : 29/07/2007 */
/* email   : softinthebox@free.fr                      R�vision : 04/05/2008 */
/*---------------------------------------------------------------------------*/
/* Copyright (C) Fred Cailleau-Lepetit 2007-2008                             */
/* Licence GNU General Public License  http://www.fsf.org/copyleft/gpl.html  */
/*---------------------------------------------------------------------------*/
/*
This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation (version 3).

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

Ce programme est libre, vous pouvez le redistribuer et/ou le modifier
selon les termes de la Licence Publique G�n�rale GNU publi�e par la
Free Software Foundation (version 3).

Ce programme est distribu� car potentiellement utile, mais
SANS AUCUNE GARANTIE, ni explicite ni implicite, y compris
les garanties de commercialisation ou d'adaptation dans un but
sp�cifique. Reportez-vous � la Licence Publique G�n�rale GNU
pour plus de d�tails.
*/
#ifndef _DBBOOK_H_
#define _DBBOOK_H_

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma interface "dbbook.h"
#endif
/*---------------------------------------------------------------------------*/
class wxSQLite3Database;
/*---------------------------------------------------------------------------*/
class wxDbBook : public wxPanel
{
   DECLARE_CLASS(wxDbBook)
   
   public:
      
      wxDbBook();
      wxDbBook(wxWindow* parent, wxWindowID id = -1,
               const wxPoint& pos = wxDefaultPosition,
               const wxSize& size = wxDefaultSize,
               long style = wxTAB_TRAVERSAL);

      bool Create(wxWindow* parent, wxWindowID id = -1,
                  const wxPoint& pos = wxDefaultPosition,
                  const wxSize& size = wxDefaultSize,
                  long style = wxTAB_TRAVERSAL);

      virtual ~wxDbBook();

      virtual void SetDbObjectName(wxSQLite3Database* db,
                                   const wxString objectname,
                                   const wxString& base = wxEmptyString);


      virtual void RefreshDbObject() = 0;
      
      wxString GetObjectName() const {return m_DbObjectName;}
      wxString GetBaseName() const {return m_Base;}
      
   protected:
      
      void Init();

      wxSQLite3Database* m_db;
      wxString m_Base;
      wxString m_DbObjectName;
};
/*---------------------------------------------------------------------------*/
#endif   // _DBBOOK_H_
