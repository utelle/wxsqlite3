/*---------------------------------------------------------------------------*/
/* Logiciel de gestion de fichier de base de donnéesSQLite                   */
/*---------------------------------------------------------------------------*/
/* Projet  : wxSQLitePlus                              Version  : 0.2.0.0    */
/* Fichier : createview.h                                                    */
/* Auteur  : Fred Cailleau-Lepetit                     Date     : 23/08/2007 */
/* email   : softinthebox@free.fr                      Révision : 02/01/2008 */
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
#ifndef _CREATEVIEW_H_
#define _CREATEVIEW_H_

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma interface "createview.h"
#endif

/*---------------------------------------------------------------------------*/
#include <wx/wxsqlite3.h>
#include <wx/notebook.h>
#include "sqleditor.h"
/*---------------------------------------------------------------------------*/
class wxCreateViewDialog: public wxDialog
{    
   DECLARE_DYNAMIC_CLASS(wxCreateViewDialog)
   DECLARE_EVENT_TABLE()

   public:

      wxCreateViewDialog();
      wxCreateViewDialog(wxWindow* parent, wxWindowID id = -1,
                         const wxString& caption = _("Create View"),
                         const wxPoint& pos = wxDefaultPosition,
                         const wxSize& size = wxDefaultSize,
                         long style = wxDEFAULT_DIALOG_STYLE);

      bool Create(wxWindow* parent, wxWindowID id = -1,
                  const wxString& caption = _("Create View"),
                  const wxPoint& pos = wxDefaultPosition,
                  const wxSize& size = wxDefaultSize,
                  long style = wxDEFAULT_DIALOG_STYLE);

      ~wxCreateViewDialog();

      wxString GetCreateViewDDL();

      void SetDatabase(wxSQLite3Database* db,
                       const wxString& base = wxEmptyString);

      bool GetTemporary() const {return m_Temporary;}
      
   protected:

      void Init();
      void CreateControls();

      void OnChar(wxKeyEvent& event);
      void OnNotebookPageChanging(wxNotebookEvent& event);
      void OnBtnTestClick(wxCommandEvent& event);
      void OnBtnTestUpdate(wxUpdateUIEvent& event);
      void OnOkClick(wxCommandEvent& event);

      static bool ShowToolTips();

   private:

      wxTextCtrl* m_ViewName;
      wxCheckBox* m_TempView;
      wxSQLEditor* m_ViewQuery;
      wxTextCtrl* m_ParseResults;
      wxDDLEditor* m_TextDdl;

      wxSQLite3Database* m_Db;
      wxString m_Base;
      wxString m_QueryError;
      bool m_Temporary;

      bool CheckViewQuery(const wxString& query);
};
/*---------------------------------------------------------------------------*/
#endif   // _CREATEVIEW_H_
