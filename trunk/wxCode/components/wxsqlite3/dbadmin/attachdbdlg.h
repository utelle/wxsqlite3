/*---------------------------------------------------------------------------*/
/* Logiciel de gestion de fichier de base de donn�esSQLite                   */
/*---------------------------------------------------------------------------*/
/* Projet  : wxSQLitePlus                              Version  : 0.2.3.0    */
/* Fichier : attachdbdlg.h                                                   */
/* Auteur  : Fred Cailleau-Lepetit                     Date     : 03/02/2008 */
/* email   : softinthebox@free.fr                      R�vision : 08/11/2008 */
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
#ifndef _ATTACHDBDLG_H_
#define _ATTACHDBDLG_H_

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma interface "attachdbdlg.h"
#endif
/*---------------------------------------------------------------------------*/
#include <wx/wxsqlite3.h>
/*---------------------------------------------------------------------------*/
class wxAttachDbDlg: public wxDialog
{
   DECLARE_DYNAMIC_CLASS(wxAttachDbDlg)
   DECLARE_EVENT_TABLE()

   public:

      wxAttachDbDlg();
      wxAttachDbDlg(wxWindow* parent, wxWindowID id = -1,
                    const wxString& caption = _("Attach Database"),
                    const wxPoint& pos = wxDefaultPosition,
                    const wxSize& size = wxDefaultSize,
                    long style = wxDEFAULT_DIALOG_STYLE);

      bool Create(wxWindow* parent, wxWindowID id = -1,
                  const wxString& caption = _("Attach Database"),
                  const wxPoint& pos = wxDefaultPosition,
                  const wxSize& size = wxDefaultSize,
                  long style = wxDEFAULT_DIALOG_STYLE);

      ~wxAttachDbDlg();

      void SetDatabase(wxSQLite3Database* db);

      wxString GetFileName() const {return m_FileName;}
      void SetFileName(wxString value) {m_FileName = value;}

      wxString GetAlias() const {return m_Alias;}
      void SetAlias(wxString value) {m_Alias = value;}

      wxString GetKey() const {return m_Key;}
      void SetKey(wxString value) {m_Key = value;}

      void OnlyKey();

   protected:

      void Init();
      void CreateControls();

      void OnAttachbtnClick(wxCommandEvent& event);
      void OnOkClick(wxCommandEvent& event);
      void OnChar(wxKeyEvent& event);


      static bool ShowToolTips();

   private:

      wxBitmapButton*   m_BtnAttach;
      wxTextCtrl*       m_EdFilename;
      wxTextCtrl*       m_EdAlias;
      wxTextCtrl*       m_EdKey;

      wxString m_FileName;
      wxString m_Alias;
      wxString m_Key;

      wxSQLite3Database* m_Db;
};
/*---------------------------------------------------------------------------*/
#endif   // _ATTACHDBDLG_H_
