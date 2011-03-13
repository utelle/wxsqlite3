/*---------------------------------------------------------------------------*/
/* Logiciel de gestion de fichier de base de donnéesSQLite                   */
/*---------------------------------------------------------------------------*/
/* Projet  : wxSQLitePlus                              Version  : 0.2.0.0    */
/* Fichier : createtrigger.h                                                 */
/* Auteur  : Fred Cailleau-Lepetit                     Date     : 24/08/2007 */
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
#ifndef _CREATETRIGGER_H_
#define _CREATETRIGGER_H_

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma interface "createtrigger.h"
#endif
/*---------------------------------------------------------------------------*/
#include <wx/wxsqlite3.h>
#include "sqleditor.h"
/*---------------------------------------------------------------------------*/
class wxCreateTriggerDialog: public wxDialog
{    
   DECLARE_DYNAMIC_CLASS(wxCreateTriggerDialog)
   DECLARE_EVENT_TABLE()

   public:

      wxCreateTriggerDialog();
      wxCreateTriggerDialog(wxWindow* parent, wxWindowID id = -1,
                            const wxString& caption = _("Create Trigger"),
                            const wxPoint& pos = wxDefaultPosition,
                            const wxSize& size = wxDefaultSize,
                            long style = wxDEFAULT_DIALOG_STYLE);

      bool Create(wxWindow* parent, wxWindowID id = -1,
                  const wxString& caption = _("Create Trigger"),
                  const wxPoint& pos = wxDefaultPosition,
                  const wxSize& size = wxDefaultSize,
                  long style = wxDEFAULT_DIALOG_STYLE);

      ~wxCreateTriggerDialog();

      wxString GetCreateTriggerDDL();

      void SetDatabase(wxSQLite3Database* db,
                       const wxString& base = wxEmptyString);
      void SetObject(const wxString& objname, bool table = true);

      bool GetTemporary() const {return m_Temporary;}

   protected:

      void Init();
      void CreateControls();

      void OnChar(wxKeyEvent& event);
      void OnNotebookPageChanging(wxNotebookEvent& event);
      void OnTypeObjSelected(wxCommandEvent& event);
      void OnObjNameSelected(wxCommandEvent& event);
      void OnTriggerEventSelected(wxCommandEvent& event);
      void OnAddcolumnClick(wxCommandEvent& event);
      void OnAddcolumnUpdate(wxUpdateUIEvent& event);
      void OnAddallcolumnsClick(wxCommandEvent& event);
      void OnAddallcolumnsUpdate(wxUpdateUIEvent& event);
      void OnRemovecolumnClick(wxCommandEvent& event);
      void OnRemovecolumnUpdate(wxUpdateUIEvent& event);
      void OnRemoveallcolumnsClick(wxCommandEvent& event);
      void OnRemoveallcolumnsUpdate(wxUpdateUIEvent& event);
      void OnOkClick(wxCommandEvent& event);

      static bool ShowToolTips();

   private:

      wxTextCtrl* m_TriggerName;
      wxCheckBox* m_TempTrigger;
      wxChoice* m_TypeObj;
      wxChoice* m_ObjName;
      wxChoice* m_TriggerTime;
      wxChoice* m_TriggerEvent;
      wxListBox* m_AvailableColumns;
      wxBitmapButton* m_BtnAddColumn;
      wxBitmapButton* m_BtnAddAllColumns;
      wxBitmapButton* m_BtnRemoveColumn;
      wxBitmapButton* m_BtnRemoveAllColumns;
      wxListBox* m_SelectedColumns;
      wxCheckBox* m_ForEachRow;
      wxTextCtrl* m_When;
      // wxTextCtrl* m_Statement;
      wxSQLEditor* m_Statement;
      wxDDLEditor* m_TextDdl;

      wxSQLite3Database* m_Db;
      wxString m_Base;
      bool m_Temporary;

      void PopulateObjName();
      void PopulateColumns();
      void DoEnableColumns();
};
/*---------------------------------------------------------------------------*/
#endif   // _CREATETRIGGER_H_
