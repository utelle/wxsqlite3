/*---------------------------------------------------------------------------*/
/* Logiciel de gestion de fichier de base de donnéesSQLite                   */
/*---------------------------------------------------------------------------*/
/* Projet  : wxSQLitePlus                              Version  : 0.2.0.0    */
/* Fichier : addcolumn.h                                                     */
/* Auteur  : Fred Cailleau-Lepetit                     Date     : 28/12/2007 */
/* email   : softinthebox@free.fr                      Révision : 09/01/2008 */
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
#ifndef _ADDCOLUMN_H_
#define _ADDCOLUMN_H_

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma interface "addcolumn.h"
#endif
/*---------------------------------------------------------------------------*/
#include "createtable.h"
/*---------------------------------------------------------------------------*/
class wxGridAddColumnsTable : public wxGridColumnsTable
{
   public:

      wxGridAddColumnsTable();
      
      void SetExistingColumnsName(const wxArrayString& colsname);
      
   protected:

      virtual bool CheckName(const wxString& name, int row = -1);

   private:

      wxArrayString m_ExistingColumnsName;

};
/*---------------------------------------------------------------------------*/
class wxAddColumnDialog: public wxDialog
{    
   DECLARE_DYNAMIC_CLASS(wxAddColumnDialog)
   DECLARE_EVENT_TABLE()

   public:

      wxAddColumnDialog();
      wxAddColumnDialog(wxWindow* parent, wxWindowID id = -1,
                        const wxString& caption = _("Add Column"),
                        const wxPoint& pos = wxDefaultPosition,
                        const wxSize& size = wxSize(400, 300),
                        long style = wxDEFAULT_DIALOG_STYLE);

      bool Create(wxWindow* parent, wxWindowID id = -1,
                  const wxString& caption = _("Add Column"),
                  const wxPoint& pos = wxDefaultPosition,
                  const wxSize& size = wxSize(400, 300),
                  long style = wxDEFAULT_DIALOG_STYLE);

      ~wxAddColumnDialog();

      wxString GetAddColumnsDDL();
      wxArrayString GetAddColumnsScript();
      
      void SetDatabase(wxSQLite3Database* db,
                       const wxString& base = wxEmptyString);
      void SetTable(const wxString& table);
      
   protected:

      void Init();
      void CreateControls();

      void OnTablenameSelected(wxCommandEvent& event);
      void OnBookPageChanging(wxNotebookEvent& event);
      void OnGridChar(wxKeyEvent& event);
      void OnBtnAddcolumnClick(wxCommandEvent& event);
      void OnBtnDelcolumnClick(wxCommandEvent& event);
      void OnBtnDelcolumnUpdate(wxUpdateUIEvent& event);
      void OnOkClick(wxCommandEvent& event);

      static bool ShowToolTips();

   private:

      wxChoice* m_ChoiceTableName;
      wxGrid* m_GridColumns;
      wxDDLEditor* m_TextDdl;
      wxButton* m_BtnAddColumn;

      wxSQLite3Database* m_Db;
      wxString m_Base;
      wxGridAddColumnsTable m_TableColumns;

      void DoTablenameSelected();
};
/*---------------------------------------------------------------------------*/
#endif   // _ADDCOLUMN_H_
