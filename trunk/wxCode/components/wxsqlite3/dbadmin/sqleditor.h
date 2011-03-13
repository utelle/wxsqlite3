/*---------------------------------------------------------------------------*/
/* Logiciel de gestion de fichier de base de donnéesSQLite                   */
/*---------------------------------------------------------------------------*/
/* Projet  : wxSQLitePlus                              Version  : 0.2.2.0    */
/* Fichier : sqleditor.h                                                     */
/* Auteur  : Fred Cailleau-Lepetit                     Date     : 11/09/2007 */
/* email   : softinthebox@free.fr                      Révision : 24/08/2008 */
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
#ifndef _SQLEDITOR_H_
#define _SQLEDITOR_H_

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma interface "sqleditor.h"
#endif
/*---------------------------------------------------------------------------*/
#include <wx/stc/stc.h>
/*---------------------------------------------------------------------------*/
class wxSQLEditorBase : public wxStyledTextCtrl
{
   DECLARE_DYNAMIC_CLASS(wxSQLEditorBase)
   DECLARE_EVENT_TABLE()

   public:

      wxSQLEditorBase(wxWindow *parent, wxWindowID id = wxID_ANY,
                      const wxPoint& pos = wxDefaultPosition,
                      const wxSize& size = wxDefaultSize, long style = 0,
                      const wxString& name = wxSTCNameStr);

      wxSQLEditorBase();

      ~wxSQLEditorBase();


      bool Create(wxWindow *parent, wxWindowID id = wxID_ANY,
                  const wxPoint& pos = wxDefaultPosition,
                  const wxSize& size = wxDefaultSize, long style = 0,
                  const wxString& name = wxSTCNameStr);

      void SetDefaultFont(const wxString& name, int size);
      wxString GetDefaultFontName(){return m_FontName;}
      int GetDefaultFontSize(){return m_FontSize;}

      void ReInitAllStyle();

      void SetLineNumberMarginStyle(bool show = true,
                                    wxColour fore = wxNullColour,
                                    wxColour back = wxNullColour);
      void SetDefaultStyle(bool bold = false, bool italic = false,
                           bool underline = false,
                           int lettercase = wxSTC_CASE_MIXED,
                           wxColour fore = wxNullColour,
                           wxColour back = wxNullColour);
      void SetCommentStyle(bool bold = false, bool italic = true,
                           bool underline = false,
                           int lettercase = wxSTC_CASE_MIXED,
                           wxColour fore = wxNullColour,
                           wxColour back = wxNullColour);
      void SetCommentLineStyle(bool bold = false, bool italic = true,
                               bool underline = false,
                               int lettercase = wxSTC_CASE_MIXED,
                               wxColour fore = wxNullColour,
                               wxColour back = wxNullColour);
      void SetNumberStyle(bool bold = false, bool italic = false,
                          bool underline = false,
                          int lettercase = wxSTC_CASE_MIXED,
                          wxColour fore = wxNullColour,
                          wxColour back = wxNullColour);
      void SetStringStyle(bool bold = false, bool italic = false,
                          bool underline = false,
                          int lettercase = wxSTC_CASE_MIXED,
                          wxColour fore = wxNullColour,
                          wxColour back = wxNullColour);
      void SetCharacterStyle(bool bold = false, bool italic = false,
                             bool underline = false,
                             int lettercase = wxSTC_CASE_MIXED,
                             wxColour fore = wxNullColour,
                             wxColour back = wxNullColour);
      void SetOperatorStyle(bool bold = false, bool italic = false,
                            bool underline = false,
                            int lettercase = wxSTC_CASE_MIXED,
                            wxColour fore = wxNullColour,
                            wxColour back = wxNullColour);
      void SetIdentifierStyle(bool bold = false, bool italic = false,
                              bool underline = false,
                              int lettercase = wxSTC_CASE_MIXED,
                              wxColour fore = wxNullColour,
                              wxColour back = wxNullColour);
      void SetKeyWordStyle(int index, bool bold = true, bool italic = false,
                           bool underline = false,
                           int lettercase = wxSTC_CASE_UPPER,
                           wxColour fore = wxNullColour,
                           wxColour back = wxNullColour);

      bool EndLineIsComment(int lineindex);

   protected:

      void Init();

      void SetTypeStyle(int type, bool bold, bool italic, bool underline,
                        int lettercase, wxColour fore, wxColour back);

      void OnUndoClick(wxCommandEvent& event);
      void OnUndoUpdate(wxUpdateUIEvent& event);
      void OnRedoClick(wxCommandEvent& event);
      void OnRedoUpdate(wxUpdateUIEvent& event);
      void OnCutClick(wxCommandEvent& event);
      void OnCopyClick(wxCommandEvent& event);
      void OnCopyUpdate(wxUpdateUIEvent& event);
      void OnPasteClick(wxCommandEvent& event);
      void OnPasteUpdate(wxUpdateUIEvent& event);
      void OnClearClick(wxCommandEvent& event);
      void OnSelectAllUpdate(wxUpdateUIEvent& event);
      void OnSelectAllClick(wxCommandEvent& event);

   private:

      wxString m_FontName;
      int      m_FontSize;
};
/*---------------------------------------------------------------------------*/
class wxSQLEditor : public wxSQLEditorBase
{
   DECLARE_DYNAMIC_CLASS(wxSQLEditor)

   public:

      wxSQLEditor(wxWindow *parent, wxWindowID id = wxID_ANY,
                  const wxPoint& pos = wxDefaultPosition,
                  const wxSize& size = wxDefaultSize, long style = 0,
                  const wxString& name = wxSTCNameStr);

      wxSQLEditor();

      ~wxSQLEditor();


      bool Create(wxWindow *parent, wxWindowID id = wxID_ANY,
                  const wxPoint& pos = wxDefaultPosition,
                  const wxSize& size = wxDefaultSize, long style = 0,
                  const wxString& name = wxSTCNameStr);

      void InitStyle();

};
/*---------------------------------------------------------------------------*/
class wxDDLEditor : public wxSQLEditor
{
   DECLARE_DYNAMIC_CLASS(wxDDLEditor)

   public:

      wxDDLEditor(wxWindow *parent, wxWindowID id = wxID_ANY,
                  const wxPoint& pos = wxDefaultPosition,
                  const wxSize& size = wxDefaultSize, long style = 0,
                  const wxString& name = wxSTCNameStr);

      wxDDLEditor();

      ~wxDDLEditor();


      bool Create(wxWindow *parent, wxWindowID id = wxID_ANY,
                  const wxPoint& pos = wxDefaultPosition,
                  const wxSize& size = wxDefaultSize, long style = 0,
                  const wxString& name = wxSTCNameStr);

      void SetValue(const wxString& value);

   protected:

      void DisableLine();

};
/*---------------------------------------------------------------------------*/
#endif // _SQLEDITOR_H_
