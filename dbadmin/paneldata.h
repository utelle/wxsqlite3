/*---------------------------------------------------------------------------*/
/* Logiciel de gestion de fichier de base de donnéesSQLite                   */
/*---------------------------------------------------------------------------*/
/* Projet  : wxSQLitePlus                              Version  : 0.2.2.0    */
/* Fichier : paneldata.h                                                     */
/* Auteur  : Fred Cailleau-Lepetit                     Date     : 07/09/2008 */
/* email   : softinthebox@free.fr                      Révision : 07/09/2008 */
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
#ifndef _PANELDATA_H_
#define _PANELDATA_H_

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma interface "paneldata.h"
#endif
/*---------------------------------------------------------------------------*/
#include "dbbook.h"
/*---------------------------------------------------------------------------*/
class wxDataGrid;
/*---------------------------------------------------------------------------*/
class wxPanelData : public wxPanel
{
   DECLARE_DYNAMIC_CLASS(wxPanelData)
   DECLARE_EVENT_TABLE()

   public:

      wxPanelData();
      wxPanelData(wxWindow* parent, wxWindowID id = -1,
                  const wxPoint& pos = wxDefaultPosition,
                  const wxSize& size = wxDefaultSize,
                  long style = wxTAB_TRAVERSAL);

      bool Create(wxWindow* parent, wxWindowID id = -1,
                  const wxPoint& pos = wxDefaultPosition,
                  const wxSize& size = wxDefaultSize,
                  long style = wxTAB_TRAVERSAL);

      ~wxPanelData();

      void SetDbTableViewName(wxSQLite3Database* db,
                              const wxString objectname,
                              const wxString& base = wxEmptyString);

      bool HasFocus();

      void DoRefresh(bool usefilter = false);

   protected:

      void Init();
      void CreateControls();

      void OnMnuFilterClick(wxCommandEvent& event);
      void OnMnuSortClick(wxCommandEvent& event);
      void OnMnuRefreshClick(wxCommandEvent& event);
      void OnStaticUpdate(wxUpdateUIEvent& event);

   private:

      wxStaticText* m_active;
      wxDataGrid* m_DataGrid;
};

#endif   // _PANELDATA_H_
