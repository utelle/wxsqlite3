/*---------------------------------------------------------------------------*/
/* Logiciel de gestion de fichier de base de donnéesSQLite                   */
/*---------------------------------------------------------------------------*/
/* Projet  : wxSQLitePlus                              Version  : 0.2.0.0    */
/* Fichier : createtable.h                                                   */
/* Auteur  : Fred Cailleau-Lepetit                     Date     : 14/07/2007 */
/* email   : softinthebox@free.fr                      Révision : 12/01/2008 */
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
#ifndef _CREATETABLE_H_
#define _CREATETABLE_H_

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma interface "createtable.h"
#endif
/*---------------------------------------------------------------------------*/
#include <wx/wxsqlite3.h>
#include <wx/grid.h>
#include <wx/dynarray.h>
#include "sqlite3table.h"
#include "sqleditor.h"
/*---------------------------------------------------------------------------*/
class wxSpecGrid;
/*---------------------------------------------------------------------------*/
enum wxColTblType {cttInteger, cttIntegerAutoinc, cttReal, cttText, cttBlob};
/*---------------------------------------------------------------------------*/
class wxColumnCtrTable
{
   public:

      wxColumnCtrTable();

      void SetName(const wxString& name) {m_Name = name;}
      void SetType(wxColTblType type) {m_Type = type;}
      void SetNotNull(bool notnull) {m_NotNull = notnull;}
      void SetPrimaryKey(bool primarykey) {m_PrimaryKey = primarykey;}
      void SetDefault(const wxString& def) {m_Default = def;}

      wxString GetName() const {return m_Name;}
      wxColTblType GetType() const {return m_Type;}
      bool GetNotNull() const {return m_NotNull;}
      bool GetPrimaryKey() const {return m_PrimaryKey;}
      wxString GetDefault() const {return m_Default;}

   private:
        
      wxString m_Name;
      wxColTblType m_Type;
      bool m_NotNull;
      bool m_PrimaryKey;
      wxString m_Default;
};
/*---------------------------------------------------------------------------*/
WX_DEFINE_ARRAY(wxColumnCtrTable*, wxArrayColumnCtrTable);
/*---------------------------------------------------------------------------*/
class wxGridColumnsTable : public wxGridTableBase
{
   public:
        
      wxGridColumnsTable();

      virtual ~wxGridColumnsTable();
        
      virtual int GetNumberRows();
      virtual int GetNumberCols() {return 5;}
      virtual bool IsEmptyCell(int row, int col);

      virtual wxString GetValue(int row, int col);
      virtual bool GetValueAsBool(int row, int col);

      virtual void SetValue(int row, int col, const wxString& value);
      virtual void SetValueAsBool(int row, int col, bool value);

      virtual wxString GetColLabelValue(int col);
      
      virtual wxString GetTypeName(int row, int col);
      virtual bool CanGetValueAs(int row, int col, const wxString& typeName);
      virtual bool CanSetValueAs(int row, int col, const wxString& typeName);

      virtual bool InsertRows(size_t pos = 0, size_t numRows = 1);
      virtual bool AppendRows(size_t numRows = 1);
      virtual bool DeleteRows(size_t pos = 0, size_t numRows = 1);

      wxColumnCtrTable* GetColumnCtrTable(size_t index);
      
   protected:

      virtual bool CheckName(const wxString& name, int row = -1);

   private:

      wxArrayColumnCtrTable m_Columns;

      bool CheckAutoInc(int row = -1);
      wxString GetUniqueName();
};
/*---------------------------------------------------------------------------*/
class wxCreateTableDialog: public wxDialog
{    
   DECLARE_DYNAMIC_CLASS(wxCreateTableDialog)
   DECLARE_EVENT_TABLE()

   public:

      wxCreateTableDialog();
      wxCreateTableDialog(wxWindow* parent, wxWindowID id = -1,
                          const wxString& caption = _("Create Table"),
                          const wxPoint& pos = wxDefaultPosition,
                          const wxSize& size = wxSize(400, 300),
                          long style = wxDEFAULT_DIALOG_STYLE);

      bool Create(wxWindow* parent, wxWindowID id = -1,
                  const wxString& caption = _("Create Table"),
                  const wxPoint& pos = wxDefaultPosition,
                  const wxSize& size = wxSize(400, 300),
                  long style = wxDEFAULT_DIALOG_STYLE);

      ~wxCreateTableDialog();

      wxString GetCreateTableDDL();
      
      void SetDatabase(wxSQLite3Database* db,
                       const wxString& base = wxEmptyString);

      bool GetTemporary() const {return m_Temporary;}
      
   protected:

      void Init();
      void CreateControls();

      void OnChar(wxKeyEvent& event);
      void OnBookPageChanging(wxNotebookEvent& event);
      void OnGridChar(wxKeyEvent& event);
      void OnBtnAddcolumnClick(wxCommandEvent& event);
      void OnBtnDelcolumnClick(wxCommandEvent& event);
      void OnBtnDelcolumnUpdate(wxUpdateUIEvent& event);
      void OnOkClick(wxCommandEvent& event);

      static bool ShowToolTips();

   private:

      wxTextCtrl* m_TextTableName;
      wxCheckBox* m_TempTable;
      wxSpecGrid* m_GridColumns;
      wxDDLEditor* m_TextDdl;
      wxButton* m_BtnAddColumn;

      wxSQLite3Database* m_Db;
      wxString m_Base;
      wxGridColumnsTable m_TableColumns;
      bool m_Temporary;

};
/*---------------------------------------------------------------------------*/
#endif   // _CREATETABLE_H_
