/*---------------------------------------------------------------------------*/
/* Logiciel de gestion de fichier de bases de données SQLite                 */
/*---------------------------------------------------------------------------*/
/* Projet  : wxSQLitePlus                              Version  : 0.2.3.0    */
/* Fichier : sqleditor.cpp                                                   */
/* Auteur  : Fred Cailleau-Lepetit                     Date     : 11/09/2007 */
/* email   : softinthebox@free.fr                      Révision : 02/11/2008 */
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
#pragma implementation "sqleditor.h"
#endif

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif
/*---------------------------------------------------------------------------*/
#include "sqleditor.h"
#include "wxsqliteplusapp.h"
/*---------------------------------------------------------------------------*/
wxString SQLWordlist1 =
_T("abort add after all alter analyze and as asc attach autoincrement before begin between blob by cascade case cast check clob collate column commit conflict constraint create cross current_date current_time current_timestamp database default deferrable deferred delete desc detach distinct double drop each else end escape except exclusive explain fail float for foreign from full glob group having if ignore immediate in index initially inner insert instead integer intersect into is isnull join key left like limit match natural not notnull null number numeric of offset on or order outer plan pragma primary query raise real references reindex rename replace restrict right rollback row select set table temp temporary text then to transaction trigger union unique update using vacuum values varchar varchar2 view virtual when where");

wxString SQLWordlist2 =
_T("abs avg coalesce count date datetime glob hex ifnull julianday last_insert_rowid length like load_extension lower ltrim max min nullif quote random randomblob replace round rtrim soundex sqlite_version strftime substr sum time total trim typeof upper zeroblob ");

wxString SQLWordlist3 =
_T("auto_vacuum cache_size case_sensitive_like count_changes database_list default_cache_size default_synchronous empty_result_callbacks encoding foreign_key_list freelist_count full_column_names fullfsync incremental_vacuum index_info index_list integrity_check legacy_file_format locking_mode max_page_count page_size parser_trace read_uncommitted schema_version short_column_names synchronous table_info temp_store temp_store_directory user_version vdbe_listing vdbe_trace");

wxString SQLWordlist4 =
_T("_rowid_ main oid rowid sqlite_master sqlite_sequence sqlite_temp_master temp");
/*---------------------------------------------------------------------------*/
IMPLEMENT_DYNAMIC_CLASS(wxSQLEditorBase, wxStyledTextCtrl)

BEGIN_EVENT_TABLE(wxSQLEditorBase, wxStyledTextCtrl)
   EVT_MENU(wxID_UNDO, wxSQLEditorBase::OnUndoClick)
   EVT_UPDATE_UI(wxID_UNDO, wxSQLEditorBase::OnUndoUpdate)

   EVT_MENU(wxID_REDO, wxSQLEditorBase::OnRedoClick)
   EVT_UPDATE_UI(wxID_REDO, wxSQLEditorBase::OnRedoUpdate)

   EVT_MENU(wxID_CUT, wxSQLEditorBase::OnCutClick)
   EVT_UPDATE_UI(wxID_CUT, wxSQLEditorBase::OnCopyUpdate)

   EVT_MENU(wxID_COPY, wxSQLEditorBase::OnCopyClick)
   EVT_UPDATE_UI(wxID_COPY, wxSQLEditorBase::OnCopyUpdate)

   EVT_MENU(wxID_PASTE, wxSQLEditorBase::OnPasteClick)
   EVT_UPDATE_UI(wxID_PASTE, wxSQLEditorBase::OnPasteUpdate)

   EVT_MENU(wxID_CLEAR, wxSQLEditorBase::OnClearClick)
   EVT_UPDATE_UI(wxID_CLEAR, wxSQLEditorBase::OnCopyUpdate)

   EVT_MENU(wxID_SELECTALL, wxSQLEditorBase::OnSelectAllClick)
   EVT_UPDATE_UI(wxID_SELECTALL, wxSQLEditorBase::OnSelectAllUpdate)
END_EVENT_TABLE()
/*---------------------------------------------------------------------------*/
wxSQLEditorBase::wxSQLEditorBase(wxWindow *parent, wxWindowID id,
                                 const wxPoint& pos, const wxSize& size,
                                 long style, const wxString& name) :
                 wxStyledTextCtrl(parent, id, pos, size, style, name)
{
   Init();
}
/*---------------------------------------------------------------------------*/
wxSQLEditorBase::wxSQLEditorBase() : wxStyledTextCtrl(){}
/*---------------------------------------------------------------------------*/
wxSQLEditorBase::~wxSQLEditorBase(){}
/*---------------------------------------------------------------------------*/
bool wxSQLEditorBase::Create(wxWindow *parent, wxWindowID id,
                             const wxPoint& pos, const wxSize& size, long style,
                             const wxString& name)
{
   if (!wxStyledTextCtrl::Create(parent, id, pos, size, style, name))
      return false;

   Init();

   return true;
}
/*---------------------------------------------------------------------------*/
void wxSQLEditorBase::Init()
{
   m_FontName = _T("Courier New");
   m_FontSize = 10;

   SetWrapMode(wxSTC_WRAP_NONE);  // wxSTC_WRAP_WORD wxSTC_WRAP_NONE
   SetLexer(wxSTC_LEX_SQL);
   SetTabWidth(2);
   SetUseTabs(false);
   SetTabIndents (true);
   SetBackSpaceUnIndents (true);
   SetIndent(2);
   SetViewEOL(false);
   SetIndentationGuides(true);
   SetEOLMode(wxSTC_EOL_LF);

   SetEdgeColumn(200);
   SetEdgeMode(wxSTC_EDGE_LINE);   // wxSTC_EDGE_NONE wxSTC_EDGE_LINE
   SetViewWhiteSpace(wxSTC_WS_INVISIBLE);   // wxSTC_WS_VISIBLEALWAYS

   SetMarginType(1, wxSTC_MARGIN_SYMBOL);
   SetMarginWidth(1, 0);

   SetKeyWords(0, SQLWordlist1);
   SetKeyWords(1, SQLWordlist2);
   SetKeyWords(4, SQLWordlist3);
   SetKeyWords(5, SQLWordlist4);

   ReInitAllStyle();
}
/*---------------------------------------------------------------------------*/
void wxSQLEditorBase::SetDefaultFont(const wxString& name, int size)
{
   m_FontName = name;
   m_FontSize = size;
}
/*---------------------------------------------------------------------------*/
void wxSQLEditorBase::ReInitAllStyle()
{
   SetMarginType(0, wxSTC_MARGIN_NUMBER);
   StyleSetForeground(wxSTC_STYLE_LINENUMBER, wxColour(_T("BLACK")));
   StyleSetBackground(wxSTC_STYLE_LINENUMBER, wxColour(_T("GREY")));
   SetMarginWidth(0, 25);
   // default fonts for all styles!
   for (int i = wxSTC_SQL_DEFAULT; i <= wxSTC_SQL_QUOTEDIDENTIFIER; i++)
   {
      SetTypeStyle(i, false, false, false, wxSTC_CASE_MIXED,
                   wxColour(_T("BLACK")), wxColour(_T("WHITE")));
   }
}
/*---------------------------------------------------------------------------*/
void wxSQLEditorBase::SetLineNumberMarginStyle(bool show, wxColour fore,
                                               wxColour back)
{
   SetMarginType(0, wxSTC_MARGIN_NUMBER);
   if (fore != wxNullColour)
      StyleSetForeground(wxSTC_STYLE_LINENUMBER, fore);
   if (back != wxNullColour)
      StyleSetBackground(wxSTC_STYLE_LINENUMBER, back);
   SetMarginWidth(0, show ? 25 : 0);
}
/*---------------------------------------------------------------------------*/
void wxSQLEditorBase::SetDefaultStyle(bool bold, bool italic, bool underline,
                                      int lettercase, wxColour fore,
                                      wxColour back)
{
   SetTypeStyle(wxSTC_SQL_DEFAULT, bold, italic, underline, lettercase, fore, back);
}
/*---------------------------------------------------------------------------*/
void wxSQLEditorBase::SetCommentStyle(bool bold, bool italic, bool underline,
                                      int lettercase, wxColour fore,
                                      wxColour back)
{
   SetTypeStyle(wxSTC_SQL_COMMENT, bold, italic, underline, lettercase, fore, back);
   SetTypeStyle(wxSTC_SQL_COMMENTDOC, bold, italic, underline, lettercase, fore, back);
   SetTypeStyle(wxSTC_SQL_SQLPLUS_COMMENT, bold, italic, underline, lettercase, fore, back);
   SetTypeStyle(wxSTC_SQL_COMMENTDOCKEYWORD, bold, italic, underline, lettercase, fore, back);
   SetTypeStyle(wxSTC_SQL_COMMENTDOCKEYWORDERROR, bold, italic, underline, lettercase, fore, back);
}
/*---------------------------------------------------------------------------*/
void wxSQLEditorBase::SetCommentLineStyle(bool bold, bool italic, bool underline,
                                          int lettercase, wxColour fore,
                                          wxColour back)
{
   SetTypeStyle(wxSTC_SQL_COMMENTLINE, bold, italic, underline, lettercase, fore, back);
   SetTypeStyle(wxSTC_SQL_COMMENTLINEDOC, bold, italic, underline, lettercase, fore, back);
}
/*---------------------------------------------------------------------------*/
void wxSQLEditorBase::SetNumberStyle(bool bold, bool italic, bool underline,
                                     int lettercase, wxColour fore,
                                     wxColour back)
{
   SetTypeStyle(wxSTC_SQL_NUMBER, bold, italic, underline, lettercase, fore, back);
}
/*---------------------------------------------------------------------------*/
void wxSQLEditorBase::SetStringStyle(bool bold, bool italic, bool underline,
                                     int lettercase, wxColour fore,
                                     wxColour back)
{
   SetTypeStyle(wxSTC_SQL_STRING, bold, italic, underline, lettercase, fore, back);
}
/*---------------------------------------------------------------------------*/
void wxSQLEditorBase::SetCharacterStyle(bool bold, bool italic, bool underline,
                                        int lettercase, wxColour fore,
                                        wxColour back)
{
   SetTypeStyle(wxSTC_SQL_CHARACTER, bold, italic, underline, lettercase, fore, back);
}
/*---------------------------------------------------------------------------*/
void wxSQLEditorBase::SetOperatorStyle(bool bold, bool italic, bool underline,
                                       int lettercase, wxColour fore,
                                       wxColour back)
{
   SetTypeStyle(wxSTC_SQL_OPERATOR, bold, italic, underline, lettercase, fore, back);
}
/*---------------------------------------------------------------------------*/
void wxSQLEditorBase::SetIdentifierStyle(bool bold, bool italic, bool underline,
                                         int lettercase, wxColour fore,
                                         wxColour back)
{
   SetTypeStyle(wxSTC_SQL_IDENTIFIER, bold, italic, underline, lettercase, fore, back);
}
/*---------------------------------------------------------------------------*/
void wxSQLEditorBase::SetKeyWordStyle(int index, bool bold, bool italic,
                                      bool underline, int lettercase,
                                      wxColour fore, wxColour back)
{
   int kw;
   switch (index)
   {
      case 1  : kw = wxSTC_SQL_WORD;  break;
      case 2  : kw = wxSTC_SQL_WORD2; break;
      case 3  : kw = wxSTC_SQL_USER1; break;
      case 4  : kw = wxSTC_SQL_USER2; break;
      default : return;
   }
   SetTypeStyle(kw, bold, italic, underline, lettercase, fore, back);
}
/*---------------------------------------------------------------------------*/
void wxSQLEditorBase::SetTypeStyle(int type, bool bold, bool italic,
                                   bool underline, int lettercase,
                                   wxColour fore, wxColour back)
{
   if (type < wxSTC_SQL_DEFAULT || type > wxSTC_SQL_QUOTEDIDENTIFIER)
      return;

   StyleSetFontAttr(type, m_FontSize, m_FontName, bold, italic, underline);

   if (fore != wxNullColour)
      StyleSetForeground(type, fore);
   if (back != wxNullColour)
      StyleSetBackground(type, back);
   StyleSetBold(type, bold); // true / false
   StyleSetItalic(type, italic);
   StyleSetUnderline(type, underline);
   // wxSTC_CASE_MIXED wxSTC_CASE_UPPER wxSTC_CASE_LOWER (0 1 2)
   if (lettercase < 0 || lettercase > 2)
      lettercase = 0;
   StyleSetCase(type, lettercase);
}
/*---------------------------------------------------------------------------*/
void wxSQLEditorBase::OnUndoClick(wxCommandEvent& event)
{
  wxUnusedVar(event);
  Undo();
}
/*---------------------------------------------------------------------------*/
void wxSQLEditorBase::OnUndoUpdate(wxUpdateUIEvent& event)
{
   event.Enable(CanUndo());
}
/*---------------------------------------------------------------------------*/
void wxSQLEditorBase::OnRedoClick(wxCommandEvent& event)
{
  wxUnusedVar(event);
  Redo();
}
/*---------------------------------------------------------------------------*/
void wxSQLEditorBase::OnRedoUpdate(wxUpdateUIEvent& event)
{
   event.Enable(CanRedo());
}
/*---------------------------------------------------------------------------*/
void wxSQLEditorBase::OnCutClick(wxCommandEvent& event)
{
  wxUnusedVar(event);
  Cut();
}
/*---------------------------------------------------------------------------*/
void wxSQLEditorBase::OnPasteClick(wxCommandEvent& event)
{
  wxUnusedVar(event);
  Paste();
}
/*---------------------------------------------------------------------------*/
void wxSQLEditorBase::OnClearClick(wxCommandEvent& event)
{
  wxUnusedVar(event);
  Clear();
}
/*---------------------------------------------------------------------------*/
void wxSQLEditorBase::OnPasteUpdate(wxUpdateUIEvent& event)
{
   event.Enable(CanPaste());
}
/*---------------------------------------------------------------------------*/
void wxSQLEditorBase::OnCopyClick(wxCommandEvent& event)
{
  wxUnusedVar(event);
  Copy();
}
/*---------------------------------------------------------------------------*/
void wxSQLEditorBase::OnSelectAllUpdate(wxUpdateUIEvent& event)
{
   event.Enable(GetLength() > 0);
}
/*---------------------------------------------------------------------------*/
void wxSQLEditorBase::OnSelectAllClick(wxCommandEvent& event)
{
  wxUnusedVar(event);
  SelectAll();
}
/*---------------------------------------------------------------------------*/
void wxSQLEditorBase::OnCopyUpdate(wxUpdateUIEvent& event)
{
   event.Enable(GetSelectionStart() != GetSelectionEnd());
}
/*---------------------------------------------------------------------------*/
bool wxSQLEditorBase::EndLineIsComment(int lineindex)
{
   int pos, style;

   pos = PositionFromLine(lineindex) + GetLine(lineindex).Length() - 1;
   style = GetStyleAt(pos);
   if ((style == wxSTC_SQL_COMMENT)||(style == wxSTC_SQL_COMMENTDOC)||
       (style == wxSTC_SQL_SQLPLUS_COMMENT)||(style == wxSTC_SQL_COMMENTDOCKEYWORD)||
       (style == wxSTC_SQL_COMMENTDOCKEYWORDERROR)||(style == wxSTC_SQL_COMMENTLINE)||
       (style == wxSTC_SQL_COMMENTLINEDOC))
      return true;
   return false;
}
/*---------------------------------------------------------------------------*/
IMPLEMENT_DYNAMIC_CLASS(wxSQLEditor, wxSQLEditorBase)
/*---------------------------------------------------------------------------*/
wxSQLEditor::wxSQLEditor(wxWindow *parent, wxWindowID id, const wxPoint& pos,
                         const wxSize& size, long style, const wxString& name) :
             wxSQLEditorBase(parent, id, pos, size, style, name)
{
   InitStyle();
}
/*---------------------------------------------------------------------------*/
wxSQLEditor::wxSQLEditor() : wxSQLEditorBase(){}
/*---------------------------------------------------------------------------*/
wxSQLEditor::~wxSQLEditor(){}
/*---------------------------------------------------------------------------*/
bool wxSQLEditor::Create(wxWindow *parent, wxWindowID id, const wxPoint& pos,
                         const wxSize& size, long style, const wxString& name)
{
   if (!wxSQLEditorBase::Create(parent, id, pos, size, style, name))
      return false;

   InitStyle();

   return true;
}
/*---------------------------------------------------------------------------*/
void wxSQLEditor::InitStyle()
{
   SetDefaultFont(wxGetApp().GetStyleFontName(), wxGetApp().GetStyleFontSize());
   SetEdgeMode(wxGetApp().GetEdgeLineVisible() ? wxSTC_EDGE_LINE : wxSTC_EDGE_NONE);

   SetDefaultStyle(wxGetApp().GetStyleFontBold(STYLE_DEFAULT),
                   wxGetApp().GetStyleFontItalic(STYLE_DEFAULT),
                   wxGetApp().GetStyleFontUnderline(STYLE_DEFAULT),
                   wxGetApp().GetStyleCase(STYLE_DEFAULT),
                   wxGetApp().GetStyleColourFore(STYLE_DEFAULT),
                   wxGetApp().GetStyleColourBack(STYLE_DEFAULT));

   SetCommentStyle(wxGetApp().GetStyleFontBold(STYLE_COMMENT),
                   wxGetApp().GetStyleFontItalic(STYLE_COMMENT),
                   wxGetApp().GetStyleFontUnderline(STYLE_COMMENT),
                   wxGetApp().GetStyleCase(STYLE_COMMENT),
                   wxGetApp().GetStyleColourFore(STYLE_COMMENT),
                   wxGetApp().GetStyleColourBack(STYLE_COMMENT));

   SetCommentLineStyle(wxGetApp().GetStyleFontBold(STYLE_COMMENTLINE),
                       wxGetApp().GetStyleFontItalic(STYLE_COMMENTLINE),
                       wxGetApp().GetStyleFontUnderline(STYLE_COMMENTLINE),
                       wxGetApp().GetStyleCase(STYLE_COMMENTLINE),
                       wxGetApp().GetStyleColourFore(STYLE_COMMENTLINE),
                       wxGetApp().GetStyleColourBack(STYLE_COMMENTLINE));

   SetNumberStyle(wxGetApp().GetStyleFontBold(STYLE_NUMBER),
                  wxGetApp().GetStyleFontItalic(STYLE_NUMBER),
                  wxGetApp().GetStyleFontUnderline(STYLE_NUMBER),
                  wxGetApp().GetStyleCase(STYLE_NUMBER),
                  wxGetApp().GetStyleColourFore(STYLE_NUMBER),
                  wxGetApp().GetStyleColourBack(STYLE_NUMBER));

   SetKeyWordStyle(1, wxGetApp().GetStyleFontBold(STYLE_WORD1),
                   wxGetApp().GetStyleFontItalic(STYLE_WORD1),
                   wxGetApp().GetStyleFontUnderline(STYLE_WORD1),
                   wxGetApp().GetStyleCase(STYLE_WORD1),
                   wxGetApp().GetStyleColourFore(STYLE_WORD1),
                   wxGetApp().GetStyleColourBack(STYLE_WORD1));

   SetStringStyle(wxGetApp().GetStyleFontBold(STYLE_STRING),
                  wxGetApp().GetStyleFontItalic(STYLE_STRING),
                  wxGetApp().GetStyleFontUnderline(STYLE_STRING),
                  wxGetApp().GetStyleCase(STYLE_STRING),
                  wxGetApp().GetStyleColourFore(STYLE_STRING),
                  wxGetApp().GetStyleColourBack(STYLE_STRING));

   SetCharacterStyle(wxGetApp().GetStyleFontBold(STYLE_CHARACTER),
                     wxGetApp().GetStyleFontItalic(STYLE_CHARACTER),
                     wxGetApp().GetStyleFontUnderline(STYLE_CHARACTER),
                     wxGetApp().GetStyleCase(STYLE_CHARACTER),
                     wxGetApp().GetStyleColourFore(STYLE_CHARACTER),
                     wxGetApp().GetStyleColourBack(STYLE_CHARACTER));

   SetOperatorStyle(wxGetApp().GetStyleFontBold(STYLE_OPERATOR),
                    wxGetApp().GetStyleFontItalic(STYLE_OPERATOR),
                    wxGetApp().GetStyleFontUnderline(STYLE_OPERATOR),
                    wxGetApp().GetStyleCase(STYLE_OPERATOR),
                    wxGetApp().GetStyleColourFore(STYLE_OPERATOR),
                    wxGetApp().GetStyleColourBack(STYLE_OPERATOR));

   SetIdentifierStyle(wxGetApp().GetStyleFontBold(STYLE_IDENTIFIER),
                      wxGetApp().GetStyleFontItalic(STYLE_IDENTIFIER),
                      wxGetApp().GetStyleFontUnderline(STYLE_IDENTIFIER),
                      wxGetApp().GetStyleCase(STYLE_IDENTIFIER),
                      wxGetApp().GetStyleColourFore(STYLE_IDENTIFIER),
                      wxGetApp().GetStyleColourBack(STYLE_IDENTIFIER));

   SetKeyWordStyle(2, wxGetApp().GetStyleFontBold(STYLE_WORD2),
                   wxGetApp().GetStyleFontItalic(STYLE_WORD2),
                   wxGetApp().GetStyleFontUnderline(STYLE_WORD2),
                   wxGetApp().GetStyleCase(STYLE_WORD2),
                   wxGetApp().GetStyleColourFore(STYLE_WORD2),
                   wxGetApp().GetStyleColourBack(STYLE_WORD2));

   SetKeyWordStyle(3, wxGetApp().GetStyleFontBold(STYLE_WORD3),
                   wxGetApp().GetStyleFontItalic(STYLE_WORD3),
                   wxGetApp().GetStyleFontUnderline(STYLE_WORD3),
                   wxGetApp().GetStyleCase(STYLE_WORD3),
                   wxGetApp().GetStyleColourFore(STYLE_WORD3),
                   wxGetApp().GetStyleColourBack(STYLE_WORD3));

   SetKeyWordStyle(4, wxGetApp().GetStyleFontBold(STYLE_WORD4),
                   wxGetApp().GetStyleFontItalic(STYLE_WORD4),
                   wxGetApp().GetStyleFontUnderline(STYLE_WORD4),
                   wxGetApp().GetStyleCase(STYLE_WORD4),
                   wxGetApp().GetStyleColourFore(STYLE_WORD4),
                   wxGetApp().GetStyleColourBack(STYLE_WORD4));


   SetTabWidth(wxGetApp().GetStyleTabWidth());
   SetUseTabs(wxGetApp().GetStyleUseTab());
   SetTabIndents(wxGetApp().GetStyleTabIndent());
   SetBackSpaceUnIndents(wxGetApp().GetStyleBackspaceUnindent());
   SetIndent(wxGetApp().GetStyleIndentWidth());

   SetLineNumberMarginStyle(wxGetApp().GetStyleShowLineNumber(),
                            wxGetApp().GetForeLineNumber(),
                            wxGetApp().GetBackLineNumber());
}
/*---------------------------------------------------------------------------*/
IMPLEMENT_DYNAMIC_CLASS(wxDDLEditor, wxSQLEditor)
/*---------------------------------------------------------------------------*/
wxDDLEditor::wxDDLEditor(wxWindow *parent, wxWindowID id, const wxPoint& pos,
                         const wxSize& size, long style, const wxString& name) :
             wxSQLEditor(parent, id, pos, size, style, name)
{
   DisableLine();
}
/*---------------------------------------------------------------------------*/
wxDDLEditor::wxDDLEditor() : wxSQLEditor(){}
/*---------------------------------------------------------------------------*/
wxDDLEditor::~wxDDLEditor(){}
/*---------------------------------------------------------------------------*/
bool wxDDLEditor::Create(wxWindow *parent, wxWindowID id, const wxPoint& pos,
                         const wxSize& size, long style, const wxString& name)
{
   if (!wxSQLEditor::Create(parent, id, pos, size, style, name))
      return false;

   DisableLine();

   return true;
}
/*---------------------------------------------------------------------------*/
void wxDDLEditor::DisableLine()
{
   SetLineNumberMarginStyle(false);
   SetReadOnly(true);
}
/*---------------------------------------------------------------------------*/
void wxDDLEditor::SetValue(const wxString& value)
{
   bool ro = GetReadOnly();

   SetReadOnly(false);
   SetText(value);
   SetReadOnly(ro);
}
/*---------------------------------------------------------------------------*/
