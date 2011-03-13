/*---------------------------------------------------------------------------*/
/* Logiciel de gestion de fichier de base de donnéesSQLite                   */
/*---------------------------------------------------------------------------*/
/* Projet  : wxSQLitePlus                              Version  : 0.2.2.0    */
/* Fichier : filterdlg.h                                                     */
/* Auteur  : Fred Cailleau-Lepetit                     Date     : 24/08/2008 */
/* email   : softinthebox@free.fr                      Révision : 24/08/2008 */
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
selon les termes de la Licence Publique Générale GNU publiée par la
Free Software Foundation (version 3).

Ce programme est distribué car potentiellement utile, mais
SANS AUCUNE GARANTIE, ni explicite ni implicite, y compris
les garanties de commercialisation ou d'adaptation dans un but
spécifique. Reportez-vous à la Licence Publique Générale GNU
pour plus de détails.
*/

#ifndef _FILTERDLG_H_
#define _FILTERDLG_H_

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma interface "filterdlg.h"
#endif
/*---------------------------------------------------------------------------*/
#include <wx/wxsqlite3.h>
#include "sqleditor.h"
/*---------------------------------------------------------------------------*/
class wxFilterDialog: public wxDialog
{
   DECLARE_DYNAMIC_CLASS(wxFilterDialog)
   DECLARE_EVENT_TABLE()

   public:

      wxFilterDialog();
      wxFilterDialog(wxWindow* parent, wxWindowID id = -1,
                     const wxString& caption = _("Filter"),
                     const wxPoint& pos = wxDefaultPosition,
                     const wxSize& size = wxDefaultSize,
                     long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER);

      bool Create(wxWindow* parent, wxWindowID id = -1,
                  const wxString& caption = _("Filter"),
                  const wxPoint& pos = wxDefaultPosition,
                  const wxSize& size = wxDefaultSize,
                  long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER);

      ~wxFilterDialog();

      void SetDatabase(wxSQLite3Database* db,
                       const wxString& base = wxEmptyString);
      void SetTable(const wxString& table);

      wxString GetStatement(){return m_Statement;}
      void SetStatement(const wxString& value);

   protected:

      void Init();
      void CreateControls();

      void OnFieldsSelected(wxCommandEvent& event);
      void OnValueUpdate(wxUpdateUIEvent& event);
      void OnBtnAndClick(wxCommandEvent& event);
      void OnBtnOrClick(wxCommandEvent& event);
      void OnBtnOparClick(wxCommandEvent& event);
      void OnBtnCparClick(wxCommandEvent& event);
      void OnClearClick(wxCommandEvent& event);
      void OnClearUpdate(wxUpdateUIEvent& event);
      void OnBtnAddClick(wxCommandEvent& event);
      void OnOkClick(wxCommandEvent& event);

   private:

      wxChoice* m_fields;
      wxChoice* m_operators;
      wxTextCtrl* m_Value;
      wxSQLEditor* m_filter;

      wxSQLite3Database* m_Db;
      wxString m_Base;
      wxString m_Table;
      wxString m_Statement;

};
/*---------------------------------------------------------------------------*/
#endif   // _FILTERDLG_H_
