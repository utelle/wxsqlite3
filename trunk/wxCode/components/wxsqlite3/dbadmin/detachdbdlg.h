/*---------------------------------------------------------------------------*/
/* Logiciel de gestion de fichier de base de donnéesSQLite                   */
/*---------------------------------------------------------------------------*/
/* Projet  : wxSQLitePlus                              Version  : 0.2.2.0    */
/* Fichier : detachdbdlg.h                                                   */
/* Auteur  : Fred Cailleau-Lepetit                     Date     : 03/02/2008 */
/* email   : softinthebox@free.fr                      Révision : 20/08/2008 */
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
#ifndef _DETACHDBDLG_H_
#define _DETACHDBDLG_H_

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma interface "detachdbdlg.h"
#endif
/*---------------------------------------------------------------------------*/
#include <wx/wxsqlite3.h>
/*---------------------------------------------------------------------------*/
class wxDetachDbDlg: public wxDialog
{
   DECLARE_DYNAMIC_CLASS(wxDetachDbDlg)
   DECLARE_EVENT_TABLE()

   public:

      wxDetachDbDlg();
      wxDetachDbDlg(wxWindow* parent, wxWindowID id = -1,
                    const wxString& caption = _("Detach Database"),
                    const wxPoint& pos = wxDefaultPosition,
                    const wxSize& size = wxDefaultSize,
                    long style = wxDEFAULT_DIALOG_STYLE);

      bool Create(wxWindow* parent, wxWindowID id = -1,
                  const wxString& caption = _("Detach Database"),
                  const wxPoint& pos = wxDefaultPosition,
                  const wxSize& size = wxDefaultSize,
                  long style = wxDEFAULT_DIALOG_STYLE);

      ~wxDetachDbDlg();

      void SetDatabase(wxSQLite3Database* db,
                       const wxString& base = wxEmptyString);

       int GetAliasList(wxArrayString& aliaslist);

   protected:

      void Init();
      void CreateControls();

      void OnOkClick(wxCommandEvent& event);

      static bool ShowToolTips();

   private:

      wxListBox* m_DataBasesList;

      wxSQLite3Database* m_Db;
};
/*---------------------------------------------------------------------------*/
#endif   // _DETACHDBDLG_H_
