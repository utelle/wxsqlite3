/*---------------------------------------------------------------------------*/
/* Logiciel de gestion de fichier de base de donnéesSQLite                   */
/*---------------------------------------------------------------------------*/
/* Projet  : wxSQLitePlus                              Version  : 0.2.0.0    */
/* Fichier : createindex.h                                                   */
/* Auteur  : Fred Cailleau-Lepetit                     Date     : 15/07/2007 */
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
#ifndef _CREATEINDEX_H_
#define _CREATEINDEX_H_

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma interface "createindex.h"
#endif
/*---------------------------------------------------------------------------*/
#include <wx/wxsqlite3.h>
#include <wx/notebook.h>
#include "sqleditor.h"
/*---------------------------------------------------------------------------*/
class wxCreateIndexDlg: public wxDialog
{    
   DECLARE_DYNAMIC_CLASS(wxCreateIndexDlg)
   DECLARE_EVENT_TABLE()

   public:
      
      wxCreateIndexDlg();
      wxCreateIndexDlg(wxWindow* parent, wxWindowID id = -1,
                       const wxString& caption = _("Create Index"),
                       const wxPoint& pos = wxDefaultPosition,
                       const wxSize& size = wxSize(400, 300),
                       long style = wxDEFAULT_DIALOG_STYLE);

      bool Create(wxWindow* parent, wxWindowID id = -1,
                  const wxString& caption = _("Create Index"),
                  const wxPoint& pos = wxDefaultPosition,
                  const wxSize& size = wxSize(400, 300),
                  long style = wxDEFAULT_DIALOG_STYLE);

      ~wxCreateIndexDlg();

      wxString GetCreateIndexDDL();
      
      void SetDatabase(wxSQLite3Database* db,
                       const wxString& base = wxEmptyString);
      void SetTable(const wxString& table);
   
   protected:

      void Init();
      void CreateControls();

      void OnChar(wxKeyEvent& event);
      void OnNotebookPageChanging(wxNotebookEvent& event);
      void OnTablenameSelected(wxCommandEvent& event);
      void OnIndexcolumnsSelected(wxCommandEvent& event);
      void OnAddbtnClick(wxCommandEvent& event);
      void OnRemovebtnClick(wxCommandEvent& event);
      void OnUpbtnClick(wxCommandEvent& event);
      void OnDownbtnClick(wxCommandEvent& event);
      void OnColumnsSelected(wxCommandEvent& event);
      void OnOkClick(wxCommandEvent& event);

      static bool ShowToolTips();

   private:

      wxTextCtrl* m_IndexName;
      wxChoice* m_TableName;
      wxCheckBox* m_UniqueIndex;
      wxListBox* m_IndexColumns;
      wxBitmapButton* m_AddButton;
      wxBitmapButton* m_RemoveButton;
      wxBitmapButton* m_UpButton;
      wxBitmapButton* m_DownButton;
      wxChoice* m_Columns;
      wxChoice* m_Order;
      wxDDLEditor* m_Ddl;

      wxSQLite3Database* m_Db;
      wxString m_Base;

      void DoTablenameSelected();
      void DoIndexcolumnsSelected();
};
/*---------------------------------------------------------------------------*/
#endif   // _CREATEINDEX_H_
