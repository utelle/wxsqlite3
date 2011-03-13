/*---------------------------------------------------------------------------*/
/* Logiciel de gestion de fichier de base de donnéesSQLite                   */
/*---------------------------------------------------------------------------*/
/* Projet  : wxSQLitePlus                              Version  : 0.2.2.0    */
/* Fichier : sortdlg.h                                                       */
/* Auteur  : Fred Cailleau-Lepetit                     Date     : 23/08/2008 */
/* email   : softinthebox@free.fr                      Révision : 31/08/2008 */
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
#ifndef _SORTDLG_H_
#define _SORTDLG_H_

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma interface "sortdlg.h"
#endif
/*---------------------------------------------------------------------------*/
#include <wx/wxsqlite3.h>
#include <wx/arrstr.h>
/*---------------------------------------------------------------------------*/
class wxSortDialog: public wxDialog
{
   DECLARE_DYNAMIC_CLASS(wxSortDialog)
   DECLARE_EVENT_TABLE()

   public:

      wxSortDialog();
      wxSortDialog(wxWindow* parent, wxWindowID id = -1,
                   const wxString& caption = _("Sort"),
                   const wxPoint& pos = wxDefaultPosition,
                   const wxSize& size = wxDefaultSize,
                   long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER);

      bool Create(wxWindow* parent, wxWindowID id = -1,
                  const wxString& caption = _("Sort"),
                  const wxPoint& pos = wxDefaultPosition,
                  const wxSize& size = wxDefaultSize,
                  long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER);

      ~wxSortDialog();

      wxArrayString GetStringsOrder(){return m_StringsOrder;}
      void SetStringsOrder(wxArrayString& array);

      void SetDatabase(wxSQLite3Database* db,
                       const wxString& base = wxEmptyString);
      void SetTable(const wxString& table);

   protected:

      void Init();
      void CreateControls();

      void OnTorightClick(wxCommandEvent& event);
      void OnTorightUpdate(wxUpdateUIEvent& event);
      void OnAlltorightClick(wxCommandEvent& event);
      void OnAlltorightUpdate(wxUpdateUIEvent& event);
      void OnToleftClick(wxCommandEvent& event);
      void OnToleftUpdate(wxUpdateUIEvent& event);
      void OnAlltoleftClick(wxCommandEvent& event);
      void OnAlltoleftUpdate(wxUpdateUIEvent& event);
      void OnSelectedSelected(wxCommandEvent& event);
      void OnFirstClick(wxCommandEvent& event);
      void OnFirstUpdate(wxUpdateUIEvent& event);
      void OnUpClick(wxCommandEvent& event);
      void OnUpUpdate(wxUpdateUIEvent& event);
      void OnDownClick(wxCommandEvent& event);
      void OnDownUpdate(wxUpdateUIEvent& event);
      void OnLastClick(wxCommandEvent& event);
      void OnLastUpdate(wxUpdateUIEvent& event);
      void OnRbAscSelected(wxCommandEvent& event);
      void OnRbDescSelected(wxCommandEvent& event);
      void OnOkClick(wxCommandEvent& event);

   private:

      wxListBox*           m_Available;
      wxBitmapButton*      m_BtnRight;
      wxBitmapButton*      m_BtnAllRight;
      wxBitmapButton*      m_BtnLeft;
      wxBitmapButton*      m_BtnAllLeft;
      wxListBox*           m_Selected;
      wxBitmapButton*      m_BtnTop;
      wxBitmapButton*      m_BtnUp;
      wxBitmapButton*      m_BtnDown;
      wxBitmapButton*      m_BtnBottom;
      wxRadioButton*       m_Ascending;
      wxRadioButton*       m_Descending;

      wxSQLite3Database*   m_Db;
      wxString             m_Base;
      wxString             m_Table;
      wxArrayString        m_StringsOrder;
};
/*---------------------------------------------------------------------------*/
#endif   // _SORTDLG_H_
