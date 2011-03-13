/*---------------------------------------------------------------------------*/
/* Logiciel de gestion de fichier de base de donnéesSQLite                   */
/*---------------------------------------------------------------------------*/
/* Projet  : wxSQLitePlus                              Version  : 0.1.0.0    */
/* Fichier : sqlhistory.h                                                    */
/* Auteur  : Fred Cailleau-Lepetit                     Date     : 26/08/2007 */
/* email   : softinthebox@free.fr                      Révision : 10/09/2007 */
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
#ifndef _SQLHISTORY_H_
#define _SQLHISTORY_H_

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma interface "sqlhistory.h"
#endif
/*---------------------------------------------------------------------------*/
#include "specgrid.h"
/*---------------------------------------------------------------------------*/
class wxSpecGrid;
class wxSQLite3ResultSet;
/*---------------------------------------------------------------------------*/
class wxSQLHistory: public wxDialog
{    
   DECLARE_DYNAMIC_CLASS(wxSQLHistory)
   DECLARE_EVENT_TABLE()

   public:

      wxSQLHistory();
      wxSQLHistory(wxWindow* parent, wxWindowID id = -1,
                   const wxString& caption = _("SQL History"),
                   const wxPoint& pos = wxDefaultPosition,
                   const wxSize& size = wxDefaultSize,
                   long style = wxDEFAULT_DIALOG_STYLE);

      bool Create(wxWindow* parent, wxWindowID id = -1,
                  const wxString& caption = _("SQL History"),
                  const wxPoint& pos = wxDefaultPosition,
                  const wxSize& size = wxDefaultSize,
                  long style = wxDEFAULT_DIALOG_STYLE);

      ~wxSQLHistory();

      void SetResultSet(wxSQLite3ResultSet& resultSet);
      
      wxString GetSQLStatement(){return m_SqlStatement;}
      
   protected:

      void Init();
      void CreateControls();

      void OnCellLeftDClick(wxGridEvent& event);
      void OnOkClick(wxCommandEvent& event);

      static bool ShowToolTips();

   private:

      wxSpecGrid* m_HistoryGrid;
      wxString m_SqlStatement;
      
      bool PopulateStement();
};
/*---------------------------------------------------------------------------*/
#endif   // _SQLHISTORY_H_
