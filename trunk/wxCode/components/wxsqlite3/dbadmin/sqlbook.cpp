/*---------------------------------------------------------------------------*/
/* Logiciel de gestion de fichier de bases de données SQLite                 */
/*---------------------------------------------------------------------------*/
/* Projet  : wxSQLitePlus                              Version  : 0.2.3.0    */
/* Fichier : sqlbook.cpp                                                     */
/* Auteur  : Fred Cailleau-Lepetit                     Date     : 07/07/2007 */
/* email   : softinthebox@free.fr                      Révision : 18/10/2008 */
/*---------------------------------------------------------------------------*/
/* Copyright (C) Fred Cailleau-Lepetit 2007                                  */
/* Licence GNU General Public License  http://www.fsf.org/copyleft/gpl.html  */
/*---------------------------------------------------------------------------*/
/*
This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation (version 3);

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
#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma implementation "sqlbook.h"
#endif

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <wx/aui/framemanager.h>
#include <wx/aui/auibook.h>
/*---------------------------------------------------------------------------*/
#include "sqlbook.h"
#include "sqliteplusframe.h"
#include "wxsqliteplusapp.h"
#include "sqlparameters.h"
#include "sqlhistory.h"
#include "specgrid.h"
#include "describedlg.h"
/*---------------------------------------------------------------------------*/
#define ID_SQLEDIT      15001
#define ID_RESULTBOOK   15002
#define ID_GRIDRESULT   15003
#define ID_LOGRESULT    15004
#define ID_GRIDEXPLAIN  15005
/*---------------------------------------------------------------------------*/
IMPLEMENT_DYNAMIC_CLASS(wxSQLBook, wxPanel)

BEGIN_EVENT_TABLE(wxSQLBook, wxPanel)

   EVT_STC_UPDATEUI(ID_SQLEDIT, wxSQLBook::OnUpdateUI)
   EVT_MENU(ID_MNU_COMPACT, wxSQLBook::OnMnuCompactClick)

   EVT_MENU(wxID_UNDO, wxSQLBook::OnEventClick)
   EVT_UPDATE_UI(wxID_UNDO, wxSQLBook::OnEventUpdate)

   EVT_MENU(wxID_REDO, wxSQLBook::OnEventClick)
   EVT_UPDATE_UI(wxID_REDO, wxSQLBook::OnEventUpdate)

   EVT_MENU(wxID_CUT, wxSQLBook::OnEventClick)
   EVT_UPDATE_UI(wxID_CUT, wxSQLBook::OnEventUpdate)

   EVT_MENU(wxID_COPY, wxSQLBook::OnCopyClick)
   EVT_UPDATE_UI(wxID_COPY, wxSQLBook::OnCopyUpdate)

   EVT_MENU(wxID_PASTE, wxSQLBook::OnEventClick)
   EVT_UPDATE_UI(wxID_PASTE, wxSQLBook::OnEventUpdate)

   EVT_MENU(wxID_CLEAR, wxSQLBook::OnEventClick)
   EVT_UPDATE_UI(wxID_CLEAR, wxSQLBook::OnEventUpdate)

   EVT_MENU(wxID_SELECTALL, wxSQLBook::OnSelectallClick)
   EVT_UPDATE_UI(wxID_SELECTALL, wxSQLBook::OnSelectallUpdate)

   EVT_MENU(ID_MNU_EXECUTESQL, wxSQLBook::OnExecSQLClick)
   EVT_UPDATE_UI(ID_MNU_EXECUTESQL, wxSQLBook::OnQueryUpdate)

   EVT_MENU(ID_MNU_EXECUTESCRIPT, wxSQLBook::OnExecScriptClick)
   EVT_UPDATE_UI(ID_MNU_EXECUTESCRIPT, wxSQLBook::OnQueryUpdate)

   EVT_MENU(ID_MNU_EXPLAIN, wxSQLBook::OnExplainClick)
   EVT_UPDATE_UI(ID_MNU_EXPLAIN, wxSQLBook::OnQueryUpdate)

   EVT_MENU(ID_MNU_DESCRIBE, wxSQLBook::OnDescribeClick)
   EVT_UPDATE_UI(ID_MNU_DESCRIBE, wxSQLBook::OnQueryUpdate)

   EVT_MENU(ID_MNU_BEGINTRANSACT, wxSQLBook::OnBeginTransactionClick)
   EVT_UPDATE_UI(ID_MNU_BEGINTRANSACT, wxSQLBook::OnBeginTransactionUpdate)

   EVT_MENU(ID_MNU_ENDTRANSACT, wxSQLBook::OnEndTransactionClick)
   EVT_UPDATE_UI(ID_MNU_ENDTRANSACT, wxSQLBook::OnEndTransactionUpdate)

   EVT_MENU(ID_MNU_COMMIT, wxSQLBook::OnCommitClick)
   EVT_UPDATE_UI(ID_MNU_COMMIT, wxSQLBook::OnEndTransactionUpdate)

   EVT_MENU(ID_MNU_ROLLBACK, wxSQLBook::OnRollbackClick)
   EVT_UPDATE_UI(ID_MNU_ROLLBACK, wxSQLBook::OnEndTransactionUpdate)

   EVT_MENU(ID_MNU_CLEAR_ALL, wxSQLBook::OnClearAllClick)
   EVT_UPDATE_UI(ID_MNU_CLEAR_ALL, wxSQLBook::OnClearAllUpdate)

   EVT_MENU(ID_MNU_SHOWHISTORY, wxSQLBook::OnMnuShowhistoryClick)
   EVT_UPDATE_UI(ID_MNU_SHOWHISTORY, wxSQLBook::OnMnuShowhistoryUpdate)

   EVT_MENU(ID_CMD_ED_REFRESH, wxSQLBook::OnEdRefresh)
END_EVENT_TABLE()
/*---------------------------------------------------------------------------*/
wxSQLBook::wxSQLBook()
{
   Init();
}
/*---------------------------------------------------------------------------*/
wxSQLBook::wxSQLBook(wxWindow* parent, wxWindowID id, const wxPoint& pos,
                     const wxSize& size, long style)
{
   Init();
   Create(parent, id, pos, size, style);
}
/*---------------------------------------------------------------------------*/
bool wxSQLBook::Create(wxWindow* parent, wxWindowID id, const wxPoint& pos,
                       const wxSize& size, long style)
{
   wxPanel::Create(parent, id, pos, size, style);

   CreateControls();

   if (wxGetApp().GetSavePerspective())
   {
      wxString perspective;
      perspective = wxGetApp().GetParamStr(PARAM_SQL_PERSPECTIVE);
      if (!perspective.IsEmpty())
         GetAuiManager().LoadPerspective(perspective);
   }
   return true;
}
/*---------------------------------------------------------------------------*/
wxSQLBook::~wxSQLBook()
{
   if (wxGetApp().GetSavePerspective())
   {
      wxString perspective = GetAuiManager().SavePerspective();
      wxGetApp().SetParamStr(PARAM_SQL_PERSPECTIVE, perspective);
   }

   GetAuiManager().UnInit();
   if (m_AutoClose)
   {
      wxCommandEvent postevent(wxEVT_COMMAND_MENU_SELECTED, ID_MNU_CLOSE_DB);
      wxPostEvent(wxGetApp().GetTopWindow(), postevent);
   }
}
/*---------------------------------------------------------------------------*/
void wxSQLBook::Init()
{
   m_SQLEdit = NULL;
   m_ResultBook = NULL;
   m_DataResult = NULL;
   m_LogResult = NULL;
   m_Explain = NULL;
   m_AutoTransact = false;
   m_AutoClose = true;
}
/*---------------------------------------------------------------------------*/
void wxSQLBook::CreateControls()
{
   GetAuiManager().SetManagedWindow(this);

   m_SQLEdit = new wxSQLEditor(this, ID_SQLEDIT);

   GetAuiManager().AddPane(m_SQLEdit,
                           wxAuiPaneInfo().Name(_T("SQLEdit"))
                                          .Caption(_T("Enter SQL Statement :"))
                                          .Top().MinSize(wxSize(-1, 200))
                                          .CloseButton(false)
                                          .DestroyOnClose(false)
                                          .Resizable(true)
                                          .Floatable(false));

   m_ResultBook = new wxAuiNotebook(this, ID_RESULTBOOK, wxDefaultPosition,
                                    wxDefaultSize,
                                    wxAUI_NB_TOP|wxAUI_NB_TAB_SPLIT|wxAUI_NB_TAB_MOVE);

   m_DataResult = new wxSpecGrid(m_ResultBook, ID_GRIDRESULT, wxDefaultPosition,
                                 wxDefaultSize, wxHSCROLL|wxVSCROLL);
   m_DataResult->SetDefaultColSize(50);
   m_DataResult->SetDefaultRowSize(25);
   m_DataResult->SetColLabelSize(25);
   m_DataResult->SetRowLabelSize(50);

   wxBitmap m_DataResultBitmap(wxGetApp().GetBmp(ID_BMP_RUNSQL));
   m_ResultBook->AddPage(m_DataResult, _("Results"), false, m_DataResultBitmap);

   m_LogResult = new wxTextCtrl(m_ResultBook, ID_LOGRESULT, wxEmptyString,
                                wxDefaultPosition, wxDefaultSize,
                                wxTE_MULTILINE|wxTE_READONLY|wxTE_WORDWRAP);

   wxBitmap m_LogResultBitmap(wxGetApp().GetBmp(ID_BMP_LOG));
   m_ResultBook->AddPage(m_LogResult, _("Output"), false, m_LogResultBitmap);

   m_Explain = new wxSpecGrid(m_ResultBook, ID_GRIDEXPLAIN, wxDefaultPosition,
                              wxSize(200, 150),
                              wxSUNKEN_BORDER|wxHSCROLL|wxVSCROLL);
   m_Explain->SetDefaultColSize(50);
   m_Explain->SetDefaultRowSize(25);
   m_Explain->SetColLabelSize(25);
   m_Explain->SetRowLabelSize(50);

   wxBitmap m_ExplainBitmap(wxGetApp().GetBmp(ID_BMP_EXPLAIN));
   m_ResultBook->AddPage(m_Explain, _("Explain"), false, m_ExplainBitmap);

   GetAuiManager().AddPane(m_ResultBook,
                           wxAuiPaneInfo().Name(_T("ResultBook"))
                                          .Centre()
                                          .CaptionVisible(false)
                                          .CloseButton(false)
                                          .DestroyOnClose(false)
                                          .Resizable(true));

   GetAuiManager().Update();

   m_SQLEdit->Connect(ID_SQLEDIT, wxEVT_SET_FOCUS,
                      wxFocusEventHandler(wxSQLBook::OnSQLSetFocus), NULL, this);
   m_SQLEdit->Connect(ID_SQLEDIT, wxEVT_KILL_FOCUS,
                      wxFocusEventHandler(wxSQLBook::OnSQLKillFocus), NULL, this);

   m_SQLEdit->SetFocus();
}
/*---------------------------------------------------------------------------*/
bool wxSQLBook::ShowToolTips()
{
    return true;
}
/*---------------------------------------------------------------------------*/
void wxSQLBook::ShowLog(bool showend)
{
   m_ResultBook->SetSelection(m_ResultBook->GetPageIndex(m_LogResult));
   if (showend)
      m_LogResult->ShowPosition(m_LogResult->GetLastPosition());
}
/*---------------------------------------------------------------------------*/
void wxSQLBook::ShowData()
{
   m_ResultBook->SetSelection(m_ResultBook->GetPageIndex(m_DataResult));
}
/*---------------------------------------------------------------------------*/
void wxSQLBook::ShowExplain()
{
   m_ResultBook->SetSelection(m_ResultBook->GetPageIndex(m_Explain));
}
/*---------------------------------------------------------------------------*/
void wxSQLBook::WriteText(const wxString& text)
{
   m_SQLEdit->AddText(text);
   m_SQLEdit->SetFocus();
}
/*---------------------------------------------------------------------------*/
void wxSQLBook::OnEventClick(wxCommandEvent& event)
{
   wxWindow* window = FindFocus();
   if (window && (window == m_SQLEdit))
      window->GetEventHandler()->ProcessEvent(event);
}
/*---------------------------------------------------------------------------*/
void wxSQLBook::OnEventUpdate(wxUpdateUIEvent& event)
{
   wxWindow* window = FindFocus();
   if (window && (window == m_SQLEdit))
      window->GetEventHandler()->ProcessEvent(event);
   else
      event.Enable(false);
}
/*---------------------------------------------------------------------------*/
void wxSQLBook::OnCopyClick(wxCommandEvent& event)
{
   wxWindow* window = FindFocus();

   if (window && ((window == m_SQLEdit)||/*(window == m_LogResult)||*/
                  (m_Explain && m_Explain->HasFocus())||(m_DataResult && m_DataResult->HasFocus())))
         window->GetEventHandler()->ProcessEvent(event);
}
/*---------------------------------------------------------------------------*/
void wxSQLBook::OnCopyUpdate(wxUpdateUIEvent& event)
{
   wxWindow* window = FindFocus();

   if (window && ((window == m_SQLEdit)||/*(window == m_LogResult)||*/
                  (m_Explain && m_Explain->HasFocus())||(m_DataResult && m_DataResult->HasFocus())))
         window->GetEventHandler()->ProcessEvent(event);
   else
      event.Enable(false);
}
/*---------------------------------------------------------------------------*/
void wxSQLBook::OnExecSQLClick(wxCommandEvent& event)
{
  wxUnusedVar(event);
   wxString SQL = GetCurrentSQLStatement();
   if (!SQL.IsEmpty())
      ExecQuery(SQL);
}
/*---------------------------------------------------------------------------*/
void wxSQLBook::OnExecScriptClick(wxCommandEvent& event)
{
  wxUnusedVar(event);
   wxArrayString array;

   GetScripSQL(array);
   ExecScript(array);
}
/*---------------------------------------------------------------------------*/
void wxSQLBook::OnExplainClick(wxCommandEvent& event)
{
  wxUnusedVar(event);
   wxString SQL = GetCurrentSQLStatement();
   if (!SQL.IsEmpty())
   {
      SQL = _T("EXPLAIN ") + SQL;
      ExecQuery(SQL, true);
   }
}
/*---------------------------------------------------------------------------*/
void wxSQLBook::OnDescribeClick(wxCommandEvent& event)
{
  wxUnusedVar(event);
   wxString item = GetCurrentItem();

   if (!item.IsEmpty())
      Describe(item);
}
/*---------------------------------------------------------------------------*/
void wxSQLBook::OnQueryUpdate(wxUpdateUIEvent& event)
{
   if (m_SQLEdit)
      event.Enable(m_SQLEdit->GetLength() > 0);
   else
      event.Enable(false);
}
/*---------------------------------------------------------------------------*/
void wxSQLBook::ExecQuery(const wxString sql, bool explain, bool history)
{
   try
   {
      try
      {
         if (m_db->GetAutoCommit() && m_AutoTransact)
         {
            m_db->ExecuteUpdate(_T("BEGIN TRANSACTION;"));
            m_LogResult->AppendText(_("Started transaction.\n"));
         }
      }
      catch(wxSQLite3Exception& ex)
      {
         m_LogResult->AppendText(wxString::Format(_("Error %i-%i : %s\n"),
                                          ex.GetErrorCode(),
                                          ex.GetExtendedErrorCode(),
                                          ex.GetMessage().c_str()));
         ShowLog();
      }

      int countrows = 0;
      m_Hook->Clear();
      wxSQLite3ResultSet resultSet;
      wxSQLite3Statement statement = m_db->PrepareStatement(sql);
      if (statement.GetParamCount())
      {
         wxString param, value;
         int count = statement.GetParamCount();
         wxSQLParametersDialog paramsdlg(this);

         for (int i = 0; i < count; i++)
         {
            param = statement.GetParamName(i + 1);
            value = wxGetApp().GetSQLParameter(param);
            paramsdlg.AddParameter(param, value);
         }
         if (paramsdlg.ShowModal() == wxID_OK)
         {
            for (int i = 0; i < count; i++)
            {
               param = statement.GetParamName(i + 1);
               value = paramsdlg.GetParameter(i);
               wxGetApp().SetSQLParameter(param, value);
               statement.Bind(i + 1, value);
            }
         }
         else
         {
            statement.Finalize();
            return;
         }
         resultSet = statement.ExecuteQuery();
      }
      else
         resultSet = m_db->ExecuteQuery(ToUTF8(sql));
      DisplayHookValues();
      countrows = resultSet.GetColumnCount();

      wxSpecGrid* grid;
      if (explain)
         grid = m_Explain;
      else
         grid = m_DataResult;
      if (countrows)
      {
         grid->SetTable(&g_EmptyTable);
         grid->ForceRefresh();
         wxGridSQLite3Table* table = new wxGridSQLite3Table(&resultSet);
         wxColour oddColour(wxGetApp().GetParamStr(PARAM_ODDROWCOLOR));
         table->SetAttrProvider(new OddRowsGridCellAttrProvider(oddColour));
         grid->SetTable((wxGridTableBase*)table, true);
         table->AdaptColumnsSize();
         grid->SetDefaultSelection();

         //grid->SetSelectionMode(wxGrid::wxGridSelectRows);
         grid->ForceRefresh();
         if (explain)
            ShowExplain();
         else
            ShowData();
      }
      else if (m_Hook->GetNbRowDeleted() || m_Hook->GetNbRowInserted() ||
         m_Hook->GetNbRowUpdated())
         ShowLog();

      resultSet.Finalize();
      statement.Finalize();
      if (history)
         wxGetApp().AddHistory(sql);
   }
   catch(wxSQLite3Exception& ex)
   {
      m_LogResult->AppendText(wxString::Format(_("Error %i in : \n%s\n%i : %s\n"),
                                               ex.GetErrorCode(),
                                               sql.c_str(),
                                               ex.GetExtendedErrorCode(),
                                               ex.GetMessage().c_str()));
      ShowLog();
   }
}
/*---------------------------------------------------------------------------*/
void wxSQLBook::ExecScript(const wxArrayString& arrayString)
{
   for (size_t i = 0; i < arrayString.Count(); i++)
      if (!arrayString.Item(i).IsEmpty())
         ExecQuery(arrayString.Item(i));
}
/*---------------------------------------------------------------------------*/
bool wxSQLBook::DoClose()
{
   wxSQLitePlusFrame* frame;

   frame = (wxSQLitePlusFrame*)wxGetApp().GetTopWindow();

   return frame->DoFinishTransaction();
}
/*---------------------------------------------------------------------------*/
wxString wxSQLBook::GetCurrentSQLStatement()
{
   long x, y, start;
   wxString temp;

   temp = m_SQLEdit->GetSelectedText();
   if (!temp.IsEmpty())
      return temp;

   y = m_SQLEdit->LineFromPosition(m_SQLEdit->GetCurrentPos());
   x = m_SQLEdit->GetColumn(m_SQLEdit->GetCurrentPos());
   if (y <= 0)
      start = 0;
   else
   {
      temp = m_SQLEdit->GetLine(y).Trim();

      if (temp.IsEmpty())
         start = y + 1;
      else
      {
         start = 0;
         do
         {
            y--;
            temp = m_SQLEdit->GetLine(y).Trim();

            if ((temp.IsEmpty()||(temp.Last() == _T(';')))&&!m_SQLEdit->EndLineIsComment(y))
            {
               start = y + 1;
               break;
            }
         }
         while (y != 0);
      }
   }
   return GetSQLStatementAt(start, x);
}
/*---------------------------------------------------------------------------*/
wxString wxSQLBook::GetCurrentItem()
{
   long x, y, start;
   wxChar c, s;
   wxString temp, str;

   temp = m_SQLEdit->GetSelectedText();

   if (!temp.IsEmpty())
      return temp.BeforeFirst(_T('\n'));

   y = m_SQLEdit->LineFromPosition(m_SQLEdit->GetCurrentPos());
   x = m_SQLEdit->GetColumn(m_SQLEdit->GetCurrentPos());

   str = m_SQLEdit->GetLine(y);

   s = _T(' ');
   for (start = x; start >= 0; start--)
   {
      c = str.GetChar(start);

      if (c == _T(' ')||c == _T('"'))
      {
         s = c;
         break;
      }
   }

   for (start = start + 1; start < (long)str.Len(); start++)
   {
      c = str.GetChar(start);

      if (c == s)
         break;
      temp += c;
   }

   return temp;
}
/*---------------------------------------------------------------------------*/
void wxSQLBook::GetScripSQL(wxArrayString& array)
{
   long start, end, count;
   wxString str;
   array.Clear();
   start = end = 0;

   count = m_SQLEdit->GetLineCount();

   while (start < count && end != -1)
   {
      str = GetSQLStatementAt(start, end);
      if (!str.IsEmpty())
        array.Add(str);
      start = end + 1;
   }
}
/*---------------------------------------------------------------------------*/
wxString wxSQLBook::GetSQLStatementAt(long start, long& end)
{
   wxString Str, temp;
   bool first = true;
   long count = m_SQLEdit->GetLineCount();

   end = -1;

   for (long i = start; i < count; i++)
   {
      if (!first)
         Str += _T("\n");
      else
         first = false;

      temp = m_SQLEdit->GetLine(i).Trim();
      if ((temp.Last() == _T(';')) && !m_SQLEdit->EndLineIsComment(i)) // Arrêt au point virgule de fin de commande
      // if (temp.IsEmpty())  // Arrêt à la première ligne vide
      {
         end = i;
         Str += temp;
         break;
      }
      Str += temp;
   }
   return ToUTF8(Str);
}
/*---------------------------------------------------------------------------*/
void wxSQLBook::OnBeginTransactionClick(wxCommandEvent& event)
{
  wxUnusedVar(event);
   try
   {
      if (m_db->GetAutoCommit())
      {
         m_db->ExecuteUpdate(_T("BEGIN TRANSACTION;"));
         m_LogResult->AppendText(_("Started transaction.\n"));
      }
   }
   catch(wxSQLite3Exception& ex)
   {
      m_LogResult->AppendText(wxString::Format(_("Error %i-%i : %s\n"),
                                       ex.GetErrorCode(),
                                       ex.GetExtendedErrorCode(),
                                       ex.GetMessage().c_str()));
      ShowLog();
   }
}
/*---------------------------------------------------------------------------*/
void wxSQLBook::OnEndTransactionClick(wxCommandEvent& event)
{
  wxUnusedVar(event);
   try
   {
      if (!m_db->GetAutoCommit())
      {
         m_db->ExecuteUpdate(_T("END TRANSACTION;"));
         m_LogResult->AppendText(_("Transaction completed.\n"));
      }
   }
   catch(wxSQLite3Exception& ex)
   {
      m_LogResult->AppendText(wxString::Format(_("Error %i-%i : %s\n"),
                                       ex.GetErrorCode(),
                                       ex.GetExtendedErrorCode(),
                                       ex.GetMessage().c_str()));
      ShowLog();
   }
}
/*---------------------------------------------------------------------------*/
void wxSQLBook::OnCommitClick(wxCommandEvent& event)
{
  wxUnusedVar(event);
   try
   {
      if (!m_db->GetAutoCommit())
      {
         m_db->ExecuteUpdate(_T("COMMIT;"));
         m_LogResult->AppendText(_("Transaction completed.\n"));
      }
   }
   catch(wxSQLite3Exception& ex)
   {
      m_LogResult->AppendText(wxString::Format(_("Error %i-%i : %s\n"),
                                       ex.GetErrorCode(),
                                       ex.GetExtendedErrorCode(),
                                       ex.GetMessage().c_str()));
      ShowLog();
   }
}
/*---------------------------------------------------------------------------*/
void wxSQLBook::OnRollbackClick(wxCommandEvent& event)
{
  wxUnusedVar(event);
   try
   {
      if (!m_db->GetAutoCommit())
      {
         m_db->ExecuteUpdate(_T("ROLLBACK;"));
         m_LogResult->AppendText(_("Transaction cancelled.\n"));
      }
   }
   catch(wxSQLite3Exception& ex)
   {
      m_LogResult->AppendText(wxString::Format(_("Error %i-%i : %s\n"),
                                       ex.GetErrorCode(),
                                       ex.GetExtendedErrorCode(),
                                       ex.GetMessage().c_str()));
      ShowLog();
   }
}
/*---------------------------------------------------------------------------*/
void wxSQLBook::OnBeginTransactionUpdate(wxUpdateUIEvent& event)
{
   event.Enable(m_db->GetAutoCommit());
}
/*---------------------------------------------------------------------------*/
void wxSQLBook::OnEndTransactionUpdate(wxUpdateUIEvent& event)
{
   event.Enable(!m_db->GetAutoCommit());
}
/*---------------------------------------------------------------------------*/
void wxSQLBook::DisplayHookValues()
{
   if (m_Hook->GetNbRowDeleted() > 0)
   {
      if (m_Hook->GetNbRowDeleted() > 1)
         m_LogResult->AppendText(wxString::Format(_("%i rows where deleted.\n"),
                                                  m_Hook->GetNbRowDeleted()));
      else
         m_LogResult->AppendText(wxString::Format(_("%i row was deleted.\n"),
                                                  m_Hook->GetNbRowDeleted()));
   }
   if (m_Hook->GetNbRowInserted() > 0)
   {
      if (m_Hook->GetNbRowInserted() > 1)
         m_LogResult->AppendText(wxString::Format(_("%i rows where inserted.\n"),
                                                  m_Hook->GetNbRowInserted()));
      else
         m_LogResult->AppendText(wxString::Format(_("%i row was inserted.\n"),
                                                  m_Hook->GetNbRowInserted()));
   }
   if (m_Hook->GetNbRowUpdated() > 0)
   {
      if (m_Hook->GetNbRowUpdated() > 1)
         m_LogResult->AppendText(wxString::Format(_("%i rows where updated.\n"),
                                                  m_Hook->GetNbRowUpdated()));
      else
         m_LogResult->AppendText(wxString::Format(_("%i row was updated.\n"),
                                                  m_Hook->GetNbRowUpdated()));
   }
}
/*---------------------------------------------------------------------------*/
void wxSQLBook::OnMnuCompactClick(wxCommandEvent& event)
{
  wxUnusedVar(event);
   try
   {
      if (m_db->GetAutoCommit())
      {
         m_Hook->Clear();
         m_db->ExecuteUpdate(_T("VACUUM;"));
         DisplayHookValues();
         m_LogResult->AppendText(_("Operation completed.\n"));
      }
      else
      {
         wxMessageBox(_("A transaction is running.\nYou have to execute COMMIT or ROLLBACK before compacting the database."),
                        _("Warning"));
      }
   }
   catch(wxSQLite3Exception& ex)
   {
      m_LogResult->AppendText(wxString::Format(_("Error %i-%i : %s\n"),
                                       ex.GetErrorCode(),
                                       ex.GetExtendedErrorCode(),
                                       ex.GetMessage().c_str()));
      ShowLog();
   }
}
/*---------------------------------------------------------------------------*/
void wxSQLBook::OnClearAllClick(wxCommandEvent& event)
{
  wxUnusedVar(event);
   wxWindow* window = FindFocus();
   if (window)
   {
      if (window == m_SQLEdit)
         m_SQLEdit->ClearAll();
      else if (window == m_LogResult)
         m_LogResult->SetValue(wxEmptyString);
   }
}
/*---------------------------------------------------------------------------*/
void wxSQLBook::OnClearAllUpdate(wxUpdateUIEvent& event)
{
   wxWindow* window = FindFocus();
   if (window)
   {
      if (window == m_SQLEdit)
         event.Enable(m_SQLEdit->GetLength() > 0);
      else if (window == m_LogResult)
         event.Enable(m_LogResult->GetLastPosition() > 0);
   }
   else
      event.Enable(false);
}
/*---------------------------------------------------------------------------*/
void wxSQLBook::OnSelectallClick(wxCommandEvent& event)
{
   /*
   wxWindow* window = FindFocus();
   if (window && ((window == m_SQLEdit)||(window == m_LogResult)))
      window->GetEventHandler()->ProcessEvent(event);
   */

   wxWindow* window = FindFocus();

   if (window && ((window == m_SQLEdit)||/*(window == m_LogResult)||*/
                  (m_Explain && m_Explain->HasFocus())||(m_DataResult && m_DataResult->HasFocus())))
         window->GetEventHandler()->ProcessEvent(event);

}
/*---------------------------------------------------------------------------*/
void wxSQLBook::OnSelectallUpdate(wxUpdateUIEvent& event)
{
   /*
   wxWindow* window = FindFocus();
   if (window)
   {
      // log message erreur fatale
      if (window == m_SQLEdit)
         m_SQLEdit->GetEventHandler()->ProcessEvent(event);
      else if (window == m_LogResult)
      {
      //m_LogResult->GetEventHandler()->ProcessEvent(event);
      }
   }
   else
      event.Enable(false);
   */
   wxWindow* window = FindFocus();

   if (window && ((window == m_SQLEdit)||/*(window == m_LogResult)||*/
                  (m_Explain && m_Explain->HasFocus())||(m_DataResult && m_DataResult->HasFocus())))
         window->GetEventHandler()->ProcessEvent(event);
   else
      event.Enable(false);

}
/*---------------------------------------------------------------------------*/
wxMenu* wxSQLBook::CreateMenuSQLEditor()
{
   wxMenu* menu = new wxMenu;
   menu->Append(ID_MNU_EXECUTESQL, _("E&xecute Statement\tF9"), _("Execute the current SQL statement"), wxITEM_NORMAL);
   menu->Append(ID_MNU_EXECUTESCRIPT, _("Run &Script\tF5"), _("Execute the SQL script"), wxITEM_NORMAL);
   menu->AppendSeparator();
   menu->Append(ID_MNU_EXPLAIN, _("Execute &Explain Plan\tF6"), _("Explain the current SQL statement"), wxITEM_NORMAL);
   menu->Append(ID_MNU_DESCRIBE, _("&Describe\tF4"), _T(""), wxITEM_NORMAL);
   menu->AppendSeparator();
   menu->Append(wxID_UNDO, _("&undo\tCtrl+Z"), _("Undo the last editor action"), wxITEM_NORMAL);
   menu->Append(wxID_REDO, _("&Redo\tShift+Ctrl+Z"), _("Redo the last editor action"), wxITEM_NORMAL);
   menu->AppendSeparator();
   menu->Append(wxID_CUT, _("&Cut\tCtrl+X"), _("Cut the selected text"), wxITEM_NORMAL);
   menu->Append(wxID_COPY, _("C&opy\tCtrl+C"), _("Copy the selected text"), wxITEM_NORMAL);
   menu->Append(wxID_PASTE, _("&Paste\tCtrl+V"), _("Paste in the editor the text in the clipboard"), wxITEM_NORMAL);
   menu->AppendSeparator();
   menu->Append(wxID_CLEAR, _("C&lear"), _("Delete the selected text"), wxITEM_NORMAL);
   menu->Append(ID_MNU_CLEAR_ALL, _("Clear A&ll"), _("Clear editor"), wxITEM_NORMAL);
   menu->Append(wxID_SELECTALL, _("Select &All\tCtrl+A"), _("Select all the content of the editor"), wxITEM_NORMAL);
   return menu;
}
/*---------------------------------------------------------------------------*/
void wxSQLBook::OnSQLRightDown(wxMouseEvent& event)
{
  wxUnusedVar(event);
   wxMenu* popMenu = CreateMenuSQLEditor();
   if (popMenu)
   {
      PopupMenu(popMenu);
      delete popMenu;
   }
}
/*---------------------------------------------------------------------------*/
void wxSQLBook::OnUpdateUI(wxStyledTextEvent& event)
{
   ShowEditorPos();
   event.Skip();
}
/*---------------------------------------------------------------------------*/
void wxSQLBook::ShowEditorPos()
{
   long x, y, p;

   p = m_SQLEdit->GetCurrentPos();
   x = m_SQLEdit->GetColumn(p);
   y = m_SQLEdit->LineFromPosition(p);

   SetStatusText(wxString::Format(_T("%li/%li"), x + 1, y + 1));
}
/*---------------------------------------------------------------------------*/
void wxSQLBook::SetStatusText(const wxString& text)
{
   ((wxFrame*)wxGetApp().GetTopWindow())->SetStatusText(text, 1);
}
/*---------------------------------------------------------------------------*/
void wxSQLBook::OnSQLSetFocus(wxFocusEvent& event)
{
   ShowEditorPos();
   event.Skip();
}
/*---------------------------------------------------------------------------*/
void wxSQLBook::OnSQLKillFocus(wxFocusEvent& event)
{
   SetStatusText(wxEmptyString);
   event.Skip();
}
/*---------------------------------------------------------------------------*/
void wxSQLBook::OnMnuShowhistoryClick(wxCommandEvent& event)
{
  wxUnusedVar(event);
   wxSQLite3ResultSet resultSet;
   wxSQLHistory sqlHistory(wxGetApp().GetTopWindow());
   wxString sql;
   wxChar c;

   resultSet = wxGetApp().GetStatementHistory();
   sqlHistory.SetResultSet(resultSet);

   if (sqlHistory.ShowModal() == wxID_OK)
   {
      sql = sqlHistory.GetSQLStatement();

      if (!sql.IsEmpty())
      {
         // Me demandez pas pourquoi la chaine contient des doubles interlignes
         // Je n'en sais rien, mais c'est génant.
         sql.Replace(_T("\n\n"), _T("\n"));
         c = m_SQLEdit->GetCharAt(m_SQLEdit->GetLength());

         if ((c != _T('\n'))&&(c != 0))
            m_SQLEdit->AppendText(_T("\n\n"));
         m_SQLEdit->AppendText(sql);
      }
   }
}
/*---------------------------------------------------------------------------*/
void wxSQLBook::OnMnuShowhistoryUpdate(wxUpdateUIEvent& event)
{
   event.Enable(true);
}
/*---------------------------------------------------------------------------*/
void wxSQLBook::OnEdRefresh(wxCommandEvent& event)
{
  wxUnusedVar(event);
   m_SQLEdit->InitStyle();
}
/*---------------------------------------------------------------------------*/
void wxSQLBook::Describe(const wxString& name)
{
   wxSQLitePlusFrame* frame;
   wxString base, tempname;

   if (!name.IsEmpty())
   {
      tempname = name.AfterLast(_T('.'));
      base = name.BeforeLast(_T('.'));

      frame = (wxSQLitePlusFrame*)wxGetApp().GetTopWindow();
      if (frame->ExistDbObject(otTableAndView, tempname, base))
      {
         wxDescribeDlg describeDlg(wxGetApp().GetTopWindow());
         describeDlg.Describe(m_db, tempname, base);
         describeDlg.ShowModal();
      }
      else
      {
         wxString msg = wxString::Format(_("Table or view \"%s\" not found."),
                                         name.c_str());
         wxMessageBox(msg, _("Error"));
      }
   }
}
/*---------------------------------------------------------------------------*/
