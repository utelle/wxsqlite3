/*---------------------------------------------------------------------------*/
/* Logiciel de gestion de fichier de base de donnéesSQLite                   */
/*---------------------------------------------------------------------------*/
/* Projet  : wxSQLitePlus                              Version  : 0.2.2.0    */
/* Fichier : preferences.h                                                   */
/* Auteur  : Fred Cailleau-Lepetit                     Date     : 02/09/2007 */
/* email   : softinthebox@free.fr                      Révision : 21/08/2008 */
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
#ifndef _PREFERENCES_H_
#define _PREFERENCES_H_

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma interface "preferences.h"
#endif
/*---------------------------------------------------------------------------*/
#include <wx/propdlg.h>
#include <wx/clrpicker.h>
#include <wx/fontpicker.h>
#include "wxsqliteplusapp.h"
/*---------------------------------------------------------------------------*/
class wxColourPickerCtrl;
class wxSpinCtrl;
class wxFontPickerCtrl;
class wxSQLEditorBase;
/*---------------------------------------------------------------------------*/
class wxPrefDlg: public wxPropertySheetDialog
{
   DECLARE_DYNAMIC_CLASS(wxPrefDlg)
   DECLARE_EVENT_TABLE()

   public:

      wxPrefDlg();
      wxPrefDlg(wxWindow* parent, wxWindowID id = -1,
                const wxString& caption = _("Preferences"),
                const wxPoint& pos = wxDefaultPosition,
                const wxSize& size = wxDefaultSize,
                long style = wxDEFAULT_DIALOG_STYLE);

      bool Create(wxWindow* parent, wxWindowID id = -1,
                  const wxString& caption = _("Preferences"),
                  const wxPoint& pos = wxDefaultPosition,
                  const wxSize& size = wxDefaultSize,
                  long style = wxDEFAULT_DIALOG_STYLE);

      ~wxPrefDlg();

      wxString GetValOddColour() const {return m_Val_OddColour;}
      void SetValOddColour(wxString value) {m_Val_OddColour = value;}

      int GetValMaxHistory() const {return m_Val_MaxHistory;}
      void SetValMaxHistory(int value) {m_Val_MaxHistory = value;}

      bool GetValSavePos() const {return m_Val_SavePos;}
      void SetValSavePos(bool value) {m_Val_SavePos = value;}

      bool GetValSavePers() const {return m_Val_SavePers;}
      void SetValSavePers(bool value) {m_Val_SavePers = value;}

      bool GetValShowEdge() const {return m_Val_ShowEdge;}
      void SetValShowEdge(bool value) {m_Val_ShowEdge = value;}

      bool GetValShowLineNumber() const {return m_Val_ShowLineNumber;}
      void SetValShowLineNumber(bool value) {m_Val_ShowLineNumber = value;}

      wxString GetValLineFG() const {return m_Val_LineFG;}
      void SetValLineFG(wxString value) {m_Val_LineFG = value;}

      wxString GetValLineBG() const {return m_Val_LineBG;}
      void SetValLineBG(wxString value) {m_Val_LineBG = value;}

      bool GetValUseTab() const {return m_Val_UseTab;}
      void SetValUseTab(bool value) {m_Val_UseTab = value;}

      bool GetValTabIndent() const {return m_Val_TabIndent;}
      void SetValTabIndent(bool value) {m_Val_TabIndent = value;}

      bool GetValBackUnindent() const {return m_Val_BackUnindent;}
      void SetValBackUnindent(bool value) {m_Val_BackUnindent = value;}

      int GetValTabWidth() const {return m_Val_TabWidth;}
      void SetValTabWidth(int value) {m_Val_TabWidth = value;}

      int GetValIndentWidth() const {return m_Val_IndentWidth;}
      void SetValIndentWidth(int value) {m_Val_IndentWidth = value;}

      wxString GetValFontName() const {return m_Val_FontName;}
      void SetValFontName(wxString value) {m_Val_FontName = value;}

      int GetValFontSize() const {return m_Val_FontSize;}
      void SetValFontSize(int value) {m_Val_FontSize = value;}

      bool GetValBold(int index);
      void SetValBold(int index, bool value);
      bool GetValItalic(int index);
      void SetValItalic(int index, bool value);
      bool GetValUnderline(int index);
      void SetValUnderline(int index, bool value);
      wxString GetValItemFG(int index);
      void SetValItemFG(int index, const wxString& value);
      wxString GetValItemBG(int index);
      void SetValItemBG(int index, const wxString& value);
      int GetValCase(int index);
      void SetValCase(int index, int value);

   protected:

      void Init();
      void CreateControls();
      void CreatePanelGeneral();
      void CreatePanelEditor();
      void CreatePanelSyntax();

      void OnInitDialog(wxInitDialogEvent& event);
      void OnOddlinecolourColourChanged(wxColourPickerEvent& event);
      void OnLineforeColourChanged(wxColourPickerEvent& event);
      void OnLinebackColourChanged(wxColourPickerEvent& event);
      void OnFontChanged(wxFontPickerEvent& event);
      void OnItemsSelected(wxCommandEvent& event);
      void OnBoldClick(wxCommandEvent& event);
      void OnItalicClick(wxCommandEvent& event);
      void OnUnderlineClick(wxCommandEvent& event);
      void OnItemforeColourChanged(wxColourPickerEvent& event);
      void OnItembackColourChanged(wxColourPickerEvent& event);
      void OnCaseSelected(wxCommandEvent& event);
      void OnBtnDefGenClick(wxCommandEvent& event);
      void OnBtnDefEditClick(wxCommandEvent& event);
      void OnBtnDefSyntaxClick(wxCommandEvent& event);

      static bool ShowToolTips();

   private:

      wxColourPickerCtrl* m_OddLineColour;
      wxSpinCtrl* m_MaxHistory;
      wxCheckBox* m_SaveWinPos;
      wxCheckBox* m_SaveWinPers;
      wxCheckBox* m_ShowEdgeLine;
      wxCheckBox* m_ShowLineNumber;
      wxColourPickerCtrl* m_LineNumberFG;
      wxColourPickerCtrl* m_LineNumberBG;
      wxCheckBox* m_UseTab;
      wxCheckBox* m_TabIndent;
      wxCheckBox* m_BackspaceUnindent;
      wxSpinCtrl* m_TabWidth;
      wxSpinCtrl* m_IdentWidth;
      wxFontPickerCtrl* m_Font;
      wxChoice* m_EdItems;
      wxCheckBox* m_Bold;
      wxCheckBox* m_Italic;
      wxCheckBox* m_Underline;
      wxColourPickerCtrl* m_ItemFG;
      wxColourPickerCtrl* m_ItemBG;
      wxRadioButton* m_CaseMixed;
      wxRadioButton* m_CaseUpper;
      wxRadioButton* m_CaseLower;
      wxSQLEditorBase* m_EdSample;

      wxString m_Val_OddColour;
      int m_Val_MaxHistory;
      bool m_Val_SavePos;
      bool m_Val_SavePers;
      bool m_Val_ShowEdge;
      bool m_Val_ShowLineNumber;
      wxString m_Val_LineFG;
      wxString m_Val_LineBG;
      bool m_Val_UseTab;
      bool m_Val_TabIndent;
      bool m_Val_BackUnindent;
      int m_Val_TabWidth;
      int m_Val_IndentWidth;
      wxString m_Val_FontName;
      int m_Val_FontSize;

      bool m_Val_Bold[STYLE_COUNT];
      bool m_Val_Italic[STYLE_COUNT];
      bool m_Val_Underline[STYLE_COUNT];
      wxString m_Val_ItemFG[STYLE_COUNT];
      wxString m_Val_ItemBG[STYLE_COUNT];
      int m_Val_Case[STYLE_COUNT]; // 0 Mixed 1 Upper 2 Lower

      void ChangeFont();
      void ChangeStyle(int style);
      void DisplayStyle(int style);
      void ResetDefaultDataGeneral();
      void ResetDefaultDataEditor();
      void ResetDefaultDataSyntax();
      void ResetDisplayGeneral();
      void ResetDisplayEditor();
      void ResetDisplaySyntax();

};
/*---------------------------------------------------------------------------*/
#endif   // _PREFERENCES_H_
