/*---------------------------------------------------------------------------*/
/* Logiciel de gestion de fichier de base de donnéesSQLite                   */
/*---------------------------------------------------------------------------*/
/* Projet  : wxSQLitePlus                              Version  : 0.1.0.0    */
/* Fichier : triggerbook.h                                                   */
/* Auteur  : Fred Cailleau-Lepetit                     Date     : 25/07/2007 */
/* email   : softinthebox@free.fr                      Révision : 27/03/2008 */
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
#ifndef _TRIGGERBOOK_H_
#define _TRIGGERBOOK_H_

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma interface "triggerbook.h"
#endif
/*---------------------------------------------------------------------------*/
#include "dbbook.h"
#include "sqleditor.h"
/*---------------------------------------------------------------------------*/
class wxTriggerBook : public wxDbBook
{    
   DECLARE_DYNAMIC_CLASS(wxTriggerBook)
   DECLARE_EVENT_TABLE()

   public:
      
      wxTriggerBook();
      wxTriggerBook(wxWindow* parent, wxWindowID id = -1,
                    const wxPoint& pos = wxDefaultPosition,
                    const wxSize& size = wxDefaultSize,
                    long style = wxTAB_TRAVERSAL);

      bool Create(wxWindow* parent, wxWindowID id = -1,
                  const wxPoint& pos = wxDefaultPosition,
                  const wxSize& size = wxDefaultSize,
                  long style = wxTAB_TRAVERSAL);

      ~wxTriggerBook();

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
      
      wxDDLEditor* m_PageDdl;

};
/*---------------------------------------------------------------------------*/
#endif   // _TRIGGERBOOK_H_
