/*---------------------------------------------------------------------------*/
/* Logiciel de gestion de fichier de base de donnéesSQLite                   */
/*---------------------------------------------------------------------------*/
/* Projet  : wxSQLitePlus                              Version  : 0.2.2.0    */
/* Fichier : sqlbook.h                                                       */
/* Auteur  : Fred Cailleau-Lepetit                     Date     : 07/07/2007 */
/* email   : softinthebox@free.fr                      Révision : 19/08/2008 */
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
#ifndef _SQLBOOK_H_
#define _SQLBOOK_H_

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma interface "sqlbook.h"
#endif
/*---------------------------------------------------------------------------*/
#include "sqleditor.h"
/*---------------------------------------------------------------------------*/
class wxAuiNotebook;
class wxGrid;
class wxSpecGrid;
class wxSQLite3Database;
class SQLite3HookForCount;
/*---------------------------------------------------------------------------*/
class wxSQLBook: public wxPanel
{
   DECLARE_DYNAMIC_CLASS(wxSQLBook)
   DECLARE_EVENT_TABLE()

   public:

      wxSQLBook();
      wxSQLBook(wxWindow* parent, wxWindowID id = -1,
                const wxPoint& pos = wxDefaultPosition,
                const wxSize& size = wxDefaultSize, long style = 0);

      bool Create(wxWindow* parent, wxWindowID id = -1,
                  const wxPoint& pos = wxDefaultPosition,
                  const wxSize& size = wxDefaultSize, long style = 0);

      ~wxSQLBook();

      wxSQLEditor* GetSQLEdit(){return m_SQLEdit;}
      wxGrid* GetDataResult(){return (wxGrid*)m_DataResult;}
      wxTextCtrl* GetLogResult(){return m_LogResult;}

      void ShowLog(bool showend = true);
      void ShowData();
      void ShowExplain();
      void WriteText(const wxString&  text);
      void SetAutoClose(bool value){m_AutoClose = value;}

      void SetDatabaseAndHook(wxSQLite3Database* db, SQLite3HookForCount* hook)
      {
         m_db = db;
         m_Hook = hook;
      }
      void SetAutoTransact(bool autotransact){m_AutoTransact = autotransact;}

      void ExecQuery(const wxString sql, bool explain = false,
                     bool history = true);
      void ExecScript(const wxArrayString& arrayString);

      bool DoClose();

   protected:

      void Init();
      void CreateControls();

      void OnUpdateUI(wxStyledTextEvent& event);
      void OnSQLRightDown(wxMouseEvent& event);
      void OnSQLSetFocus(wxFocusEvent& event);
      void OnSQLKillFocus(wxFocusEvent& event);

      void OnMnuCompactClick(wxCommandEvent& event);
      void OnCopyClick(wxCommandEvent& event);
      void OnCopyUpdate(wxUpdateUIEvent& event);
      void OnClearAllClick(wxCommandEvent& event);
      void OnClearAllUpdate(wxUpdateUIEvent& event);
      void OnSelectallClick(wxCommandEvent& event);
      void OnSelectallUpdate(wxUpdateUIEvent& event);
      void OnEventClick(wxCommandEvent& event);
      void OnEventUpdate(wxUpdateUIEvent& event);
      void OnMnuShowhistoryClick(wxCommandEvent& event);
      void OnMnuShowhistoryUpdate(wxUpdateUIEvent& event);

      void OnExecSQLClick(wxCommandEvent& event);
      void OnExecScriptClick(wxCommandEvent& event);
      void OnExplainClick(wxCommandEvent& event);
      void OnDescribeClick(wxCommandEvent& event);
      void OnQueryUpdate(wxUpdateUIEvent& event);

      void OnBeginTransactionClick(wxCommandEvent& event);
      void OnEndTransactionClick(wxCommandEvent& event);
      void OnCommitClick(wxCommandEvent& event);
      void OnRollbackClick(wxCommandEvent& event);
      void OnBeginTransactionUpdate(wxUpdateUIEvent& event);
      void OnEndTransactionUpdate(wxUpdateUIEvent& event);

      void OnEdRefresh(wxCommandEvent& event);

      wxAuiManager& GetAuiManager() { return m_auiManager; }

      static bool ShowToolTips();

   private:

      wxAuiManager m_auiManager;

      wxSQLEditor* m_SQLEdit;
      wxAuiNotebook* m_ResultBook;
      wxSpecGrid* m_DataResult;
      wxTextCtrl* m_LogResult;
      wxSpecGrid* m_Explain;

      wxSQLite3Database* m_db;
      SQLite3HookForCount* m_Hook;
      bool m_AutoTransact;
      bool m_AutoClose;

      wxString GetCurrentSQLStatement();
      void GetScripSQL(wxArrayString& array);
      wxString GetSQLStatementAt(long start, long& end);
      wxString GetCurrentItem();
      void DisplayHookValues();
      wxMenu* CreateMenuSQLEditor();
      void ShowEditorPos();
      void SetStatusText(const wxString& text);
      void Describe(const wxString& name);

};
/*---------------------------------------------------------------------------*/
#endif   // _SQLBOOK_H_
