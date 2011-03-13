/*---------------------------------------------------------------------------*/
/* Logiciel de gestion de fichier de base de donnéesSQLite                   */
/*---------------------------------------------------------------------------*/
/* Projet  : wxSQLitePlus                              Version  : 0.2.2.0    */
/* Fichier : tablebook.h                                                     */
/* Auteur  : Fred Cailleau-Lepetit                     Date     : 23/07/2007 */
/* email   : softinthebox@free.fr                      Révision : 31/08/2008 */
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
selon les termes de la Licence Publique Générale GNU publiée par la
Free Software Foundation (version 3).

Ce programme est distribué car potentiellement utile, mais
SANS AUCUNE GARANTIE, ni explicite ni implicite, y compris
les garanties de commercialisation ou d'adaptation dans un but
spécifique. Reportez-vous à la Licence Publique Générale GNU
pour plus de détails.
*/
#ifndef _TABLEBOOK_H_
#define _TABLEBOOK_H_

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma interface "tablebook.h"
#endif
/*---------------------------------------------------------------------------*/
#include "dbbook.h"
#include "sqleditor.h"
/*---------------------------------------------------------------------------*/
class wxAuiNotebook;
class wxSpecGrid;
class wxPanelData;
class wxSQLite3Database;
/*---------------------------------------------------------------------------*/
class wxTableBook: public wxDbBook
{
   DECLARE_DYNAMIC_CLASS(wxTableBook)
   DECLARE_EVENT_TABLE()

   public:

      wxTableBook();
      wxTableBook(wxWindow* parent, wxWindowID id = -1,
                  const wxPoint& pos = wxDefaultPosition,
                  const wxSize& size = wxDefaultSize,
                  long style = wxTAB_TRAVERSAL);

    /// Creation
      bool Create(wxWindow* parent, wxWindowID id = -1,
                  const wxPoint& pos = wxDefaultPosition,
                  const wxSize& size = wxDefaultSize,
                  long style = wxTAB_TRAVERSAL);

      ~wxTableBook();

      virtual void SetDbObjectName(wxSQLite3Database* db,
                                   const wxString objectname,
                                   const wxString& base = wxEmptyString);

      virtual void RefreshDbObject();

   protected:

      void Init();
      void CreateControls();
      static bool ShowToolTips();

      void OnTablebookPageChanging( wxAuiNotebookEvent& event );
      void OnCopyClick(wxCommandEvent& event);
      void OnCopyUpdate(wxUpdateUIEvent& event);
      void OnEdRefresh(wxCommandEvent& event);

   private:

      wxAuiNotebook* m_Book;
      wxSpecGrid* m_PageColumns;
      wxPanelData* m_PageData;
      wxSpecGrid* m_PageForeignKey;
      wxSpecGrid* m_PageTriggers;
      wxSpecGrid* m_PageIndexes;
      wxDDLEditor* m_PageDdl;
      bool m_InitData;

      void RefreshStruct();
      void RefreshData();
};
/*---------------------------------------------------------------------------*/
#endif   // _TABLEBOOK_H_
