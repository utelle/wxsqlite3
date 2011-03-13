/*---------------------------------------------------------------------------*/
/* Logiciel de gestion de fichier de base de donnéesSQLite                   */
/*---------------------------------------------------------------------------*/
/* Projet  : wxSQLitePlus                              Version  : 0.3.0.0    */
/* Fichier : backrestdlg.h                                                   */
/* Auteur  : Fred Cailleau-Lepetit                     Date     : 26/04/2009 */
/* email   : softinthebox@free.fr                      Révision : 16/05/2009 */
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
#ifndef _BACKRESTDLG_H_
#define _BACKRESTDLG_H_

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma interface "backrestdlg.h"
#endif
/*---------------------------------------------------------------------------*/
#include <wx/wxsqlite3.h>
/*---------------------------------------------------------------------------*/
class wxBackupRestoreDbDlg: public wxDialog
{
   DECLARE_DYNAMIC_CLASS(wxBackupRestoreDbDlg)
   DECLARE_EVENT_TABLE()

   public:

      wxBackupRestoreDbDlg();
      wxBackupRestoreDbDlg(wxWindow* parent, bool backup,
                           wxWindowID id = -1,
                           const wxPoint& pos = wxDefaultPosition,
                           const wxSize& size = wxDefaultSize,
                           long style = wxDEFAULT_DIALOG_STYLE);

      bool Create(wxWindow* parent, bool backup, wxWindowID id = -1,
                  const wxPoint& pos = wxDefaultPosition,
                  const wxSize& size = wxDefaultSize,
                  long style = wxDEFAULT_DIALOG_STYLE);

      ~wxBackupRestoreDbDlg();

      wxString GetFileName() const {return m_FileName;}
      void SetFileName(wxString value) {m_FileName = value;}

      wxString GetAlias() const {return m_Alias;}
      void SetAlias(wxString value) {m_Alias = value;}

      wxString GetKey() const {return m_Key;}
      void SetKey(wxString value) {m_Key = value;}

      void SetDatabase(wxSQLite3Database* db,
                       const wxString& base = wxEmptyString);

   protected:

      void Init();
      void CreateControls();
      void OnGetfilebtnClick(wxCommandEvent& event);
      void OnOkClick(wxCommandEvent& event);

      static bool ShowToolTips();

   private:

      wxTextCtrl* m_EdFilename;
      wxTextCtrl* m_EdKey;
      wxChoice* m_Database;

      wxString m_Key;
      wxString m_FileName;
      wxString m_Alias;

      wxSQLite3Database* m_Db;
      bool m_BackUp;
};
/*---------------------------------------------------------------------------*/
#endif   // _BACKRESTDLG_H_
