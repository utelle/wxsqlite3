/*---------------------------------------------------------------------------*/
/* Logiciel de gestion de fichier de base de donn�esSQLite                   */
/*---------------------------------------------------------------------------*/
/* Projet  : wxSQLitePlus                              Version  : 0.1.0.0    */
/* Fichier : indexbook.h                                                     */
/* Auteur  : Fred Cailleau-Lepetit                     Date     : 25/07/2007 */
/* email   : softinthebox@free.fr                      R�vision : 27/03/2008 */
/*---------------------------------------------------------------------------*/
/* Copyright (C) Fred Cailleau-Lepetit 2007                                  */
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
#ifndef _INDEXBOOK_H_
#define _INDEXBOOK_H_

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma interface "indexbook.h"
#endif
/*---------------------------------------------------------------------------*/
#include "dbbook.h"
#include "sqleditor.h"
/*---------------------------------------------------------------------------*/
class wxSpecGrid;
class wxSQLite3Database;
/*---------------------------------------------------------------------------*/
class wxIndexBook: public wxDbBook
{    
   DECLARE_DYNAMIC_CLASS(wxIndexBook)
   DECLARE_EVENT_TABLE()

   public:

      wxIndexBook();
      wxIndexBook(wxWindow* parent, wxWindowID id = -1,
                  const wxPoint& pos = wxDefaultPosition,
                  const wxSize& size = wxDefaultSize,
                  long style = wxTAB_TRAVERSAL);

      bool Create(wxWindow* parent, wxWindowID id = -1,
                  const wxPoint& pos = wxDefaultPosition,
                  const wxSize& size = wxDefaultSize,
                  long style = wxTAB_TRAVERSAL);

      ~wxIndexBook();

      virtual void SetDbObjectName(wxSQLite3Database* db,
                                   const wxString objectname,
                                   const wxString& base);

      virtual void RefreshDbObject();

   protected:
      
      void Init();
      void CreateControls();
      static bool ShowToolTips();

      void OnCopyClick(wxCommandEvent& event);
      void OnCopyUpdate(wxUpdateUIEvent& event);
      void OnEdRefresh(wxCommandEvent& event);
      
   private:
      
      wxSpecGrid* m_PageColumns;
      wxDDLEditor* m_PageDdl;

};
/*---------------------------------------------------------------------------*/
#endif   // _INDEXBOOK_H_
