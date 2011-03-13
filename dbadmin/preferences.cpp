/*---------------------------------------------------------------------------*/
/* Logiciel de gestion de fichier de bases de données SQLite                 */
/*---------------------------------------------------------------------------*/
/* Projet  : wxSQLitePlus                              Version  : 0.2.2.0    */
/* Fichier : preferences.cpp                                                 */
/* Auteur  : Fred Cailleau-Lepetit                     Date     : 02/09/2007 */
/* email   : softinthebox@free.fr                      Révision : 21/08/2008 */
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
#pragma implementation "preferences.h"
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
#include <wx/bookctrl.h>
#include <wx/valgen.h>
#include <wx/spinctrl.h>
/*---------------------------------------------------------------------------*/
#include "preferences.h"
#include "sqleditor.h"
/*---------------------------------------------------------------------------*/
#define ID_PANEL_GENERAL      15001
#define ID_ODDLINECOLOUR      15002
#define ID_MAX_HISTORY        15003
#define ID_SAVE_POS           15004
#define ID_SAVE_PERS          15005
#define ID_PANEL_EDITOR       15006
#define ID_SHOWEDGELINE       15007
#define ID_SHOW_LINE_NUMBER   15008
#define ID_LINEFORE           15009
#define ID_LINEBACK           15010
#define ID_USE_TAB            15011
#define ID_TAB_INDENT         15012
#define ID_BACK_UNINDENT      15013
#define ID_TABWIDTH           15014
#define ID_IDENTWIDTH         15015
#define ID_PANEL_SYNTAX       15016
#define ID_FONT               15017
#define ID_ITEMS              15018
#define ID_BOLD               15019
#define ID_ITALIC             15020
#define ID_UNDERLINE          15021
#define ID_ITEMFORE           15022
#define ID_ITEMBACK           15023
#define ID_CASEMIXED          15024
#define ID_CASEUPPER          15025
#define ID_CASELOWER          15026
#define ID_EDITSAMPLE         15027
#define ID_DEFAULT_GENERAL    15028
#define ID_DEFAULT_EDITOR     15029
#define ID_DEFAULTSYNTAX      15030
/*---------------------------------------------------------------------------*/
IMPLEMENT_DYNAMIC_CLASS(wxPrefDlg, wxPropertySheetDialog)

BEGIN_EVENT_TABLE(wxPrefDlg, wxPropertySheetDialog)
   EVT_INIT_DIALOG(wxPrefDlg::OnInitDialog)
   EVT_COLOURPICKER_CHANGED(ID_ODDLINECOLOUR, wxPrefDlg::OnOddlinecolourColourChanged)
   EVT_COLOURPICKER_CHANGED(ID_LINEFORE, wxPrefDlg::OnLineforeColourChanged)
   EVT_COLOURPICKER_CHANGED(ID_LINEBACK, wxPrefDlg::OnLinebackColourChanged)
   EVT_FONTPICKER_CHANGED(ID_FONT, wxPrefDlg::OnFontChanged)
   EVT_CHOICE(ID_ITEMS, wxPrefDlg::OnItemsSelected)
   EVT_CHECKBOX(ID_BOLD, wxPrefDlg::OnBoldClick)
   EVT_CHECKBOX(ID_ITALIC, wxPrefDlg::OnItalicClick)
   EVT_CHECKBOX(ID_UNDERLINE, wxPrefDlg::OnUnderlineClick)
   EVT_COLOURPICKER_CHANGED(ID_ITEMFORE, wxPrefDlg::OnItemforeColourChanged)
   EVT_COLOURPICKER_CHANGED(ID_ITEMBACK, wxPrefDlg::OnItembackColourChanged)
   EVT_RADIOBUTTON(ID_CASEMIXED, wxPrefDlg::OnCaseSelected)
   EVT_RADIOBUTTON(ID_CASEUPPER, wxPrefDlg::OnCaseSelected)
   EVT_RADIOBUTTON(ID_CASELOWER, wxPrefDlg::OnCaseSelected)
   EVT_BUTTON(ID_DEFAULT_GENERAL, wxPrefDlg::OnBtnDefGenClick)
   EVT_BUTTON(ID_DEFAULT_EDITOR, wxPrefDlg::OnBtnDefEditClick)
   EVT_BUTTON(ID_DEFAULTSYNTAX, wxPrefDlg::OnBtnDefSyntaxClick)
END_EVENT_TABLE()
/*---------------------------------------------------------------------------*/
wxPrefDlg::wxPrefDlg()
{
   Init();
}
/*---------------------------------------------------------------------------*/
wxPrefDlg::wxPrefDlg(wxWindow* parent, wxWindowID id, const wxString& caption,
                     const wxPoint& pos, const wxSize& size, long style)
{
   Init();
   Create(parent, id, caption, pos, size, style);
}
/*---------------------------------------------------------------------------*/
bool wxPrefDlg::Create(wxWindow* parent, wxWindowID id, const wxString& caption,
                       const wxPoint& pos, const wxSize& size, long style)
{
   SetExtraStyle(wxWS_EX_VALIDATE_RECURSIVELY|wxWS_EX_BLOCK_EVENTS);
   wxPropertySheetDialog::Create(parent, id, caption, pos, size, style);
   SetIcon(wxGetApp().GetIcon(ID_ICO_LOGO32));

   SetSheetStyle(wxPROPSHEET_TREEBOOK);
   CreateButtons(wxOK|wxCANCEL);
   CreateControls();

   ChangeFont();
   for (int i = STYLE_DEFAULT; i < STYLE_COUNT; i++)
      ChangeStyle(i);

   LayoutDialog();
   Centre();

   return true;
}
/*---------------------------------------------------------------------------*/
wxPrefDlg::~wxPrefDlg()
{
}
/*---------------------------------------------------------------------------*/
void wxPrefDlg::Init()
{
   m_OddLineColour = NULL;
   m_MaxHistory = NULL;
   m_SaveWinPos = NULL;
   m_SaveWinPers = NULL;
   m_ShowEdgeLine = NULL;
   m_ShowLineNumber = NULL;
   m_LineNumberFG = NULL;
   m_LineNumberBG = NULL;
   m_UseTab = NULL;
   m_TabIndent = NULL;
   m_BackspaceUnindent = NULL;
   m_TabWidth = NULL;
   m_IdentWidth = NULL;
   m_Font = NULL;
   m_EdItems = NULL;
   m_Bold = NULL;
   m_Italic = NULL;
   m_Underline = NULL;
   m_ItemFG = NULL;
   m_ItemBG = NULL;
   m_CaseMixed = NULL;
   m_CaseUpper = NULL;
   m_CaseLower = NULL;
   m_EdSample = NULL;

   ResetDefaultDataGeneral();
   ResetDefaultDataEditor();
   ResetDefaultDataSyntax();
}
/*---------------------------------------------------------------------------*/
void wxPrefDlg::CreateControls()
{
   CreatePanelGeneral();
   CreatePanelEditor();
   CreatePanelSyntax();
   // Set validators
   m_MaxHistory->SetValidator(wxGenericValidator(& m_Val_MaxHistory));
   m_SaveWinPos->SetValidator(wxGenericValidator(& m_Val_SavePos));
   m_SaveWinPers->SetValidator(wxGenericValidator(& m_Val_SavePers));
   m_ShowEdgeLine->SetValidator(wxGenericValidator(& m_Val_ShowEdge));
   m_ShowLineNumber->SetValidator(wxGenericValidator(& m_Val_ShowLineNumber));
   m_UseTab->SetValidator(wxGenericValidator(& m_Val_UseTab));
   m_TabIndent->SetValidator(wxGenericValidator(& m_Val_TabIndent));
   m_BackspaceUnindent->SetValidator(wxGenericValidator(& m_Val_BackUnindent));
   m_TabWidth->SetValidator(wxGenericValidator(& m_Val_TabWidth));
   m_IdentWidth->SetValidator(wxGenericValidator(& m_Val_IndentWidth));
}
/*---------------------------------------------------------------------------*/
void wxPrefDlg::CreatePanelGeneral()
{
   wxPanel* panelGen = new wxPanel(GetBookCtrl(), ID_PANEL_GENERAL,
                                   wxDefaultPosition, wxDefaultSize,
                                   wxSUNKEN_BORDER|wxTAB_TRAVERSAL );
   wxBoxSizer* bSizer1 = new wxBoxSizer(wxVERTICAL);
   panelGen->SetSizer(bSizer1);

   wxFlexGridSizer* flexSizer1 = new wxFlexGridSizer(2, 2, 0, 0);
   bSizer1->Add(flexSizer1, 0, wxALIGN_LEFT, 0);
   wxStaticText* sText1 = new wxStaticText(panelGen, wxID_STATIC,
                                           _("Odd Line Colour : "),
                                           wxDefaultPosition, wxDefaultSize, 0);
   flexSizer1->Add(sText1, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

   m_OddLineColour = new wxColourPickerCtrl(panelGen, ID_ODDLINECOLOUR,
                                            wxColour(255, 255, 128),
                                            wxDefaultPosition, wxDefaultSize,
                                            wxCLRP_DEFAULT_STYLE|wxCLRP_SHOW_LABEL);
   flexSizer1->Add(m_OddLineColour, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

   wxStaticText* sText2 = new wxStaticText(panelGen, wxID_STATIC,
                                           _("Max. SQL History : "),
                                           wxDefaultPosition, wxDefaultSize, 0);
   flexSizer1->Add(sText2, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

   m_MaxHistory = new wxSpinCtrl(panelGen, ID_MAX_HISTORY, _T("100"),
                                 wxDefaultPosition, wxSize(70, -1),
                                 wxSP_ARROW_KEYS, 0, 100, 100);
   flexSizer1->Add(m_MaxHistory, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

   bSizer1->Add(5, 5, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

   m_SaveWinPos = new wxCheckBox(panelGen, ID_SAVE_POS,
                                 _("Save window position"), wxDefaultPosition,
                                 wxDefaultSize, 0 );
   m_SaveWinPos->SetValue(true);
   bSizer1->Add(m_SaveWinPos, 0, wxALIGN_LEFT|wxALL, 5);

   m_SaveWinPers = new wxCheckBox(panelGen, ID_SAVE_PERS,
                                  _("Save window perspective"),
                                  wxDefaultPosition, wxDefaultSize, 0);
   m_SaveWinPers->SetValue(true);
   bSizer1->Add(m_SaveWinPers, 0, wxALIGN_LEFT|wxALL, 5);

   bSizer1->Add(5, 5, 1, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

   wxButton* resetBtn = new wxButton(panelGen, ID_DEFAULT_GENERAL,
                                     _("Reset Default"), wxDefaultPosition,
                                     wxDefaultSize, 0);
   bSizer1->Add(resetBtn, 0, wxALIGN_RIGHT|wxALL, 5);

   GetBookCtrl()->AddPage(panelGen, _("General"));
}
/*---------------------------------------------------------------------------*/
void wxPrefDlg::CreatePanelEditor()
{
   wxPanel* panelEdit = new wxPanel(GetBookCtrl(), ID_PANEL_EDITOR,
                                    wxDefaultPosition, wxDefaultSize,
                                    wxSUNKEN_BORDER|wxTAB_TRAVERSAL);
   wxBoxSizer* bSizer1 = new wxBoxSizer(wxVERTICAL);
   panelEdit->SetSizer(bSizer1);

   m_ShowEdgeLine = new wxCheckBox(panelEdit, ID_SHOWEDGELINE,
                                   _("Show Edge Line"), wxDefaultPosition,
                                   wxDefaultSize, 0);
   m_ShowEdgeLine->SetValue(false);
   bSizer1->Add(m_ShowEdgeLine, 0, wxALIGN_LEFT|wxALL, 5);

   bSizer1->Add(5, 5, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

   m_ShowLineNumber = new wxCheckBox(panelEdit, ID_SHOW_LINE_NUMBER,
                                     _("Show Line Number"), wxDefaultPosition,
                                     wxDefaultSize, 0);
   m_ShowLineNumber->SetValue(true);
   bSizer1->Add(m_ShowLineNumber, 0, wxALIGN_LEFT|wxALL, 5);

   wxBoxSizer* bSizer2 = new wxBoxSizer(wxHORIZONTAL);
   bSizer1->Add(bSizer2, 0, wxALIGN_LEFT, 0);
   wxStaticText* sText1 = new wxStaticText(panelEdit, wxID_STATIC,
                                           _("Foreground :"), wxDefaultPosition,
                                           wxDefaultSize, 0);
   bSizer2->Add(sText1, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

   m_LineNumberFG = new wxColourPickerCtrl(panelEdit, ID_LINEFORE,
                                           wxColour(0, 0, 0), wxDefaultPosition,
                                           wxDefaultSize,
                                           wxCLRP_DEFAULT_STYLE|wxCLRP_SHOW_LABEL);
   bSizer2->Add(m_LineNumberFG, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

   wxStaticText* sText2 = new wxStaticText(panelEdit, wxID_STATIC,
                                           _("Background  :"),
                                           wxDefaultPosition, wxDefaultSize, 0);
   bSizer2->Add(sText2, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

   m_LineNumberBG = new wxColourPickerCtrl(panelEdit, ID_LINEBACK,
                                           wxColour(128, 128, 128),
                                           wxDefaultPosition, wxDefaultSize,
                                           wxCLRP_DEFAULT_STYLE|wxCLRP_SHOW_LABEL);
   bSizer2->Add(m_LineNumberBG, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

   bSizer1->Add(5, 5, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

   m_UseTab = new wxCheckBox(panelEdit, ID_USE_TAB, _("Use Tab"),
                             wxDefaultPosition, wxDefaultSize, 0);
   m_UseTab->SetValue(false);
   bSizer1->Add(m_UseTab, 0, wxALIGN_LEFT|wxALL, 5);

   m_TabIndent = new wxCheckBox(panelEdit, ID_TAB_INDENT, _("Tab Indent"),
                                wxDefaultPosition, wxDefaultSize, 0);
   m_TabIndent->SetValue(true);
   bSizer1->Add(m_TabIndent, 0, wxALIGN_LEFT|wxALL, 5);

   m_BackspaceUnindent = new wxCheckBox(panelEdit, ID_BACK_UNINDENT,
                                        _("Backspace Unindent"),
                                        wxDefaultPosition, wxDefaultSize, 0);
   m_BackspaceUnindent->SetValue(true);
   bSizer1->Add(m_BackspaceUnindent, 0, wxALIGN_LEFT|wxALL, 5);

   wxBoxSizer* bSizer3 = new wxBoxSizer(wxHORIZONTAL);
   bSizer1->Add(bSizer3, 0, wxALIGN_LEFT, 0);

   wxBoxSizer* bSizer4 = new wxBoxSizer(wxHORIZONTAL);
   bSizer1->Add(bSizer4, 0, wxALIGN_LEFT, 0);

   wxFlexGridSizer* flexSizer1 = new wxFlexGridSizer(2, 2, 0, 0);
   bSizer1->Add(flexSizer1, 0, wxALIGN_LEFT, 0);
   wxStaticText* sText3 = new wxStaticText(panelEdit, wxID_STATIC,
                                           _("Tab Width : "), wxDefaultPosition,
                                           wxDefaultSize, 0);
   flexSizer1->Add(sText3, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

   m_TabWidth = new wxSpinCtrl(panelEdit, ID_TABWIDTH, _T("2"),
                               wxDefaultPosition, wxDefaultSize,
                               wxSP_ARROW_KEYS, 1, 20, 2);
   flexSizer1->Add(m_TabWidth, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

   wxStaticText* sText4 = new wxStaticText(panelEdit, wxID_STATIC,
                                           _("Indent Width : "),
                                           wxDefaultPosition, wxDefaultSize, 0);
   flexSizer1->Add(sText4, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

   m_IdentWidth = new wxSpinCtrl(panelEdit, ID_IDENTWIDTH, _T("2"),
                                 wxDefaultPosition, wxDefaultSize,
                                 wxSP_ARROW_KEYS, 1, 20, 2);
   flexSizer1->Add(m_IdentWidth, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

   bSizer1->Add(5, 5, 1, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

   wxButton* resetBtn = new wxButton(panelEdit, ID_DEFAULT_EDITOR,
                                     _("Reset Default"), wxDefaultPosition,
                                     wxDefaultSize, 0);
   bSizer1->Add(resetBtn, 0, wxALIGN_RIGHT|wxALL, 5);

   GetBookCtrl()->AddPage(panelEdit, _("Editor"));
}
/*---------------------------------------------------------------------------*/
void wxPrefDlg::CreatePanelSyntax()
{
   wxPanel* panelSyntax = new wxPanel(GetBookCtrl(), ID_PANEL_SYNTAX,
                                      wxDefaultPosition, wxDefaultSize,
                                      wxSUNKEN_BORDER|wxTAB_TRAVERSAL);
   wxBoxSizer* bSizer1 = new wxBoxSizer(wxVERTICAL);
   panelSyntax->SetSizer(bSizer1);

   wxBoxSizer* bSizer2 = new wxBoxSizer(wxHORIZONTAL);
   bSizer1->Add(bSizer2, 0, wxGROW, 0);
   wxStaticText* sText1 = new wxStaticText(panelSyntax, wxID_STATIC,
                                           _("Font : "), wxDefaultPosition,
                                           wxDefaultSize, 0);
   bSizer2->Add(sText1, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

   m_Font = new wxFontPickerCtrl(panelSyntax, ID_FONT,
                                 wxFont(8, wxSWISS, wxNORMAL, wxNORMAL,
                                        false, wxT("Courier New")),
                                 wxDefaultPosition, wxDefaultSize,
                                 wxFNTP_DEFAULT_STYLE);
   bSizer2->Add(m_Font, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5);

   // bSizer2->Add(5, 5, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

   wxBoxSizer* bSizer3 = new wxBoxSizer(wxHORIZONTAL);
   bSizer1->Add(bSizer3, 0, wxALIGN_LEFT, 0);
   wxStaticText* sText2 = new wxStaticText(panelSyntax, wxID_STATIC,
                                           _("Items : "), wxDefaultPosition,
                                           wxDefaultSize, 0);
   bSizer3->Add(sText2, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

   wxArrayString m_EdItemsStrings;
   m_EdItemsStrings.Add(_("Default"));
   m_EdItemsStrings.Add(_("Comment"));
   m_EdItemsStrings.Add(_("Comment One Line"));
   m_EdItemsStrings.Add(_("Number"));
   m_EdItemsStrings.Add(_("Key Word 1"));
   m_EdItemsStrings.Add(_("String"));
   m_EdItemsStrings.Add(_("Characters"));
   m_EdItemsStrings.Add(_("Operator"));
   m_EdItemsStrings.Add(_("Identifier"));
   m_EdItemsStrings.Add(_("Key Word 2"));
   m_EdItemsStrings.Add(_("Key Word 3"));
   m_EdItemsStrings.Add(_("Key Word 4"));
   m_EdItems = new wxChoice(panelSyntax, ID_ITEMS, wxDefaultPosition,
                            wxDefaultSize, m_EdItemsStrings, 0);
   m_EdItems->SetStringSelection(_("Default"));
   bSizer3->Add(m_EdItems, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

   wxBoxSizer* bSizer4 = new wxBoxSizer(wxHORIZONTAL);
   bSizer1->Add(bSizer4, 0, wxGROW, 0);
   m_Bold = new wxCheckBox(panelSyntax, ID_BOLD, _("Bold"), wxDefaultPosition,
                           wxDefaultSize, 0);
   m_Bold->SetValue(false);
   bSizer4->Add(m_Bold, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5);

   m_Italic = new wxCheckBox(panelSyntax, ID_ITALIC, _("Italic"),
                             wxDefaultPosition, wxDefaultSize, 0);
   m_Italic->SetValue(false);
   bSizer4->Add(m_Italic, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5);

   m_Underline = new wxCheckBox(panelSyntax, ID_UNDERLINE, _("Underline"),
                                wxDefaultPosition, wxDefaultSize, 0);
   m_Underline->SetValue(false);
   bSizer4->Add(m_Underline, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5);

   //bSizer4->Add(5, 5, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

   wxBoxSizer* bSizer5 = new wxBoxSizer(wxHORIZONTAL);
   bSizer1->Add(bSizer5, 0, wxALIGN_LEFT, 0);
   wxStaticText* sText3 = new wxStaticText(panelSyntax, wxID_STATIC,
                                           _("Foreground :"), wxDefaultPosition,
                                           wxDefaultSize, 0);
   bSizer5->Add(sText3, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

   m_ItemFG = new wxColourPickerCtrl(panelSyntax, ID_ITEMFORE,
                                     wxColour(0, 0, 0), wxDefaultPosition,
                                     wxDefaultSize,
                                     wxCLRP_DEFAULT_STYLE|wxCLRP_SHOW_LABEL);
   bSizer5->Add(m_ItemFG, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

   wxStaticText* sText4 = new wxStaticText(panelSyntax, wxID_STATIC,
                                           _("Background  :"),
                                           wxDefaultPosition, wxDefaultSize, 0);
   bSizer5->Add(sText4, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

   m_ItemBG = new wxColourPickerCtrl(panelSyntax, ID_ITEMBACK,
                                     wxColour(255, 255, 255), wxDefaultPosition,
                                     wxDefaultSize,
                                     wxCLRP_DEFAULT_STYLE|wxCLRP_SHOW_LABEL);
   bSizer5->Add(m_ItemBG, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

   wxBoxSizer* bSizer6 = new wxBoxSizer(wxHORIZONTAL);
   bSizer1->Add(bSizer6, 0, wxALIGN_LEFT, 0);
   m_CaseMixed = new wxRadioButton(panelSyntax, ID_CASEMIXED, _("Case Mixed"),
                                   wxDefaultPosition, wxDefaultSize, wxRB_GROUP);
   m_CaseMixed->SetValue(true);
   bSizer6->Add(m_CaseMixed, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

   m_CaseUpper = new wxRadioButton(panelSyntax, ID_CASEUPPER, _("Case Upper"),
                                   wxDefaultPosition, wxDefaultSize, 0);
   m_CaseUpper->SetValue(false);
   bSizer6->Add(m_CaseUpper, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

   m_CaseLower = new wxRadioButton(panelSyntax, ID_CASELOWER, _("Case Lower"),
                                   wxDefaultPosition, wxDefaultSize, 0);
   m_CaseLower->SetValue(false);
   bSizer6->Add(m_CaseLower, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

   wxBoxSizer* bSizer7 = new wxBoxSizer(wxHORIZONTAL);
   bSizer1->Add(bSizer7, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);
   m_EdSample = new wxSQLEditorBase(panelSyntax, ID_EDITSAMPLE,
                                    wxDefaultPosition, wxSize(350, 200));

   m_EdSample->SetText(_T("-- comment\nPRAGMA short_column_names = 1; \n/* comment */\nselect rowid, e.name, max(salary)\nfrom \"emp\" e\nwhere dept in (2, 4)\n\tand e.name <> 'Smith'\ngroup by dept;"));
   m_EdSample->SetReadOnly(true);
   bSizer7->Add(m_EdSample, 1, wxGROW|wxRIGHT, 0);

   // bSizer7->Add(5, 5, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

   bSizer1->Add(5, 5, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

   wxBoxSizer* bSizer8 = new wxBoxSizer(wxHORIZONTAL);
   bSizer1->Add(bSizer8, 0, wxALIGN_RIGHT|wxALL, 5);
   wxButton* resetBtn = new wxButton(panelSyntax, ID_DEFAULTSYNTAX,
                                     _("Reset Default"), wxDefaultPosition,
                                     wxDefaultSize, 0);
   bSizer8->Add(resetBtn, 0, wxALIGN_CENTER_VERTICAL, 0);

   // bSizer8->Add(5, 5, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

   GetBookCtrl()->AddPage(panelSyntax, _("Syntax Highlight"));
}
/*---------------------------------------------------------------------------*/
bool wxPrefDlg::ShowToolTips()
{
   return true;
}
/*---------------------------------------------------------------------------*/
void wxPrefDlg::OnInitDialog(wxInitDialogEvent& event)
{
   m_OddLineColour->SetColour(m_Val_OddColour);
   m_LineNumberFG->SetColour(m_Val_LineFG);
   m_LineNumberBG->SetColour(m_Val_LineBG);

   m_ItemFG->SetColour(m_Val_ItemFG[0]);
   m_ItemBG->SetColour(m_Val_ItemBG[0]);

   event.Skip();
}
/*---------------------------------------------------------------------------*/
void wxPrefDlg::OnFontChanged(wxFontPickerEvent& event)
{
   wxFont font = event.GetFont();
   if (font.IsFixedWidth())
   {
      m_Val_FontName = font.GetFaceName();
      m_Val_FontSize = font.GetPointSize();
      ChangeFont();
   }
   event.Skip();
}
/*---------------------------------------------------------------------------*/
void wxPrefDlg::OnItemsSelected(wxCommandEvent& event)
{
   int index = m_EdItems->GetSelection();
   if (index != wxNOT_FOUND)
      DisplayStyle(index);
   event.Skip();
}
/*---------------------------------------------------------------------------*/
void wxPrefDlg::OnBoldClick(wxCommandEvent& event)
{
   int index = m_EdItems->GetSelection();
   if (index != wxNOT_FOUND)
   {
      m_Val_Bold[index] = m_Bold->IsChecked();
      ChangeStyle(index);
   }
   event.Skip();
}
/*---------------------------------------------------------------------------*/
void wxPrefDlg::OnItalicClick(wxCommandEvent& event)
{
   int index = m_EdItems->GetSelection();
   if (index != wxNOT_FOUND)
   {
      m_Val_Italic[index] = m_Italic->IsChecked();
      ChangeStyle(index);
   }
   event.Skip();
}
/*---------------------------------------------------------------------------*/
void wxPrefDlg::OnUnderlineClick(wxCommandEvent& event)
{
   int index = m_EdItems->GetSelection();
   if (index != wxNOT_FOUND)
   {
      m_Val_Underline[index] = m_Underline->IsChecked();
      ChangeStyle(index);
   }
   event.Skip();
}
/*---------------------------------------------------------------------------*/
void wxPrefDlg::OnItemforeColourChanged(wxColourPickerEvent& event)
{
   int index = m_EdItems->GetSelection();
   if (index != wxNOT_FOUND)
   {
      m_Val_ItemFG[index] = m_ItemFG->GetColour().GetAsString(wxC2S_HTML_SYNTAX);
      ChangeStyle(index);
   }
   event.Skip();
}
/*---------------------------------------------------------------------------*/
void wxPrefDlg::OnItembackColourChanged(wxColourPickerEvent& event)
{
   int index = m_EdItems->GetSelection();
   if (index != wxNOT_FOUND)
   {
      m_Val_ItemBG[index] = m_ItemBG->GetColour().GetAsString(wxC2S_HTML_SYNTAX);
      ChangeStyle(index);
   }
   event.Skip();
}
/*---------------------------------------------------------------------------*/
void wxPrefDlg::OnLineforeColourChanged(wxColourPickerEvent& event)
{
   m_Val_LineFG = m_LineNumberFG->GetColour().GetAsString(wxC2S_HTML_SYNTAX);
   event.Skip();
}
/*---------------------------------------------------------------------------*/
void wxPrefDlg::OnOddlinecolourColourChanged(wxColourPickerEvent& event)
{
   m_Val_OddColour = m_OddLineColour->GetColour().GetAsString(wxC2S_HTML_SYNTAX);
   event.Skip();
}
/*---------------------------------------------------------------------------*/
void wxPrefDlg::OnLinebackColourChanged(wxColourPickerEvent& event)
{
   m_Val_LineBG = m_LineNumberBG->GetColour().GetAsString(wxC2S_HTML_SYNTAX);
   event.Skip();
}
/*---------------------------------------------------------------------------*/
void wxPrefDlg::OnCaseSelected(wxCommandEvent& event)
{
   int index = m_EdItems->GetSelection();
   if (index != wxNOT_FOUND)
   {
      int val = 0;
      if (m_CaseMixed->GetValue())
         val = 0;
      else if (m_CaseUpper->GetValue())
         val = 1;
      else if (m_CaseLower->GetValue())
         val = 2;

      m_Val_Case[index] = val; // 0 Mixed 1 Upper 2 Lower
      ChangeStyle(index);
   }
   event.Skip();
}
/*---------------------------------------------------------------------------*/
void wxPrefDlg::OnBtnDefGenClick(wxCommandEvent& event)
{
  wxUnusedVar(event);
  ResetDefaultDataGeneral();
   ResetDisplayGeneral();
}
/*---------------------------------------------------------------------------*/
void wxPrefDlg::OnBtnDefEditClick(wxCommandEvent& event)
{
  wxUnusedVar(event);
   ResetDefaultDataEditor();
   ResetDisplayEditor();
}
/*---------------------------------------------------------------------------*/
void wxPrefDlg::OnBtnDefSyntaxClick(wxCommandEvent& event)
{
  wxUnusedVar(event);
   ResetDefaultDataSyntax();
   ResetDisplaySyntax();
}
/*---------------------------------------------------------------------------*/
bool wxPrefDlg::GetValBold(int index)
{
   if (index < 0 || index >= STYLE_COUNT)
      return false;
   return m_Val_Bold[index];
}
/*---------------------------------------------------------------------------*/
void wxPrefDlg::SetValBold(int index, bool value)
{
   if (index < 0 || index >= STYLE_COUNT)
      return;
   m_Val_Bold[index] = value;
}
/*---------------------------------------------------------------------------*/
bool wxPrefDlg::GetValItalic(int index)
{
   if (index < 0 || index >= STYLE_COUNT)
      return false;
   return m_Val_Italic[index];
}
/*---------------------------------------------------------------------------*/
void wxPrefDlg::SetValItalic(int index, bool value)
{
   if (index < 0 || index >= STYLE_COUNT)
      return;
   m_Val_Italic[index] = value;
}
/*---------------------------------------------------------------------------*/
bool wxPrefDlg::GetValUnderline(int index)
{
   if (index < 0 || index >= STYLE_COUNT)
      return false;
   return m_Val_Underline[index];
}
/*---------------------------------------------------------------------------*/
void wxPrefDlg::SetValUnderline(int index, bool value)
{
   if (index < 0 || index >= STYLE_COUNT)
      return;
   m_Val_Underline[index] = value;
}
/*---------------------------------------------------------------------------*/
wxString wxPrefDlg::GetValItemFG(int index)
{
   if (index < 0 || index >= STYLE_COUNT)
      return _T("#FFFFFF");
   return m_Val_ItemFG[index];
}
/*---------------------------------------------------------------------------*/
void wxPrefDlg::SetValItemFG(int index, const wxString& value)
{
   if (index < 0 || index >= STYLE_COUNT)
      return;
   m_Val_ItemFG[index] = value;
}
/*---------------------------------------------------------------------------*/
wxString wxPrefDlg::GetValItemBG(int index)
{
   if (index < 0 || index >= STYLE_COUNT)
      return _T("#000000");
   return m_Val_ItemBG[index];
}
/*---------------------------------------------------------------------------*/
void wxPrefDlg::SetValItemBG(int index, const wxString& value)
{
   if (index < 0 || index >= STYLE_COUNT)
      return;
   m_Val_ItemBG[index] = value;
}
/*---------------------------------------------------------------------------*/
int wxPrefDlg::GetValCase(int index)
{
   if (index < 0 || index >= STYLE_COUNT)
      return 0;
   return m_Val_Case[index]; // 0 Mixed 1 Upper 2 Lower
}
/*---------------------------------------------------------------------------*/
void wxPrefDlg::SetValCase(int index, int value)
{
   if (index < 0 || index >= STYLE_COUNT || value < 0 || value > 2)
      return;
   m_Val_Case[index] = value; // 0 Mixed 1 Upper 2 Lower
}
/*---------------------------------------------------------------------------*/
void wxPrefDlg::ChangeFont()
{
   m_EdSample->SetDefaultFont(m_Val_FontName, m_Val_FontSize);
   for (int i = STYLE_DEFAULT; i < STYLE_COUNT; i++)
      ChangeStyle(i);
}
/*---------------------------------------------------------------------------*/
void wxPrefDlg::ChangeStyle(int style)
{
   switch (style)
   {
      case STYLE_DEFAULT :
         m_EdSample->SetDefaultStyle(m_Val_Bold[style], m_Val_Italic[style],
                                     m_Val_Underline[style], m_Val_Case[style],
                                     wxColour(m_Val_ItemFG[style]),
                                     wxColour(m_Val_ItemBG[style]));
         break;
      case STYLE_COMMENT :
         m_EdSample->SetCommentStyle(m_Val_Bold[style], m_Val_Italic[style],
                                     m_Val_Underline[style], m_Val_Case[style],
                                     wxColour(m_Val_ItemFG[style]),
                                     wxColour(m_Val_ItemBG[style]));
         break;
      case STYLE_COMMENTLINE :
         m_EdSample->SetCommentLineStyle(m_Val_Bold[style], m_Val_Italic[style],
                                         m_Val_Underline[style], m_Val_Case[style],
                                         wxColour(m_Val_ItemFG[style]),
                                         wxColour(m_Val_ItemBG[style]));
         break;
      case STYLE_NUMBER :
         m_EdSample->SetNumberStyle(m_Val_Bold[style], m_Val_Italic[style],
                                    m_Val_Underline[style], m_Val_Case[style],
                                    wxColour(m_Val_ItemFG[style]),
                                    wxColour(m_Val_ItemBG[style]));
         break;
      case STYLE_WORD1 :
         m_EdSample->SetKeyWordStyle(1, m_Val_Bold[style], m_Val_Italic[style],
                                     m_Val_Underline[style], m_Val_Case[style],
                                     wxColour(m_Val_ItemFG[style]),
                                     wxColour(m_Val_ItemBG[style]));
         break;
      case STYLE_STRING :
         m_EdSample->SetStringStyle(m_Val_Bold[style], m_Val_Italic[style],
                                    m_Val_Underline[style], m_Val_Case[style],
                                    wxColour(m_Val_ItemFG[style]),
                                    wxColour(m_Val_ItemBG[style]));
         break;
      case STYLE_CHARACTER :
         m_EdSample->SetCharacterStyle(m_Val_Bold[style], m_Val_Italic[style],
                                       m_Val_Underline[style], m_Val_Case[style],
                                       wxColour(m_Val_ItemFG[style]),
                                       wxColour(m_Val_ItemBG[style]));
         break;
      case STYLE_OPERATOR :
         m_EdSample->SetOperatorStyle(m_Val_Bold[style], m_Val_Italic[style],
                                      m_Val_Underline[style], m_Val_Case[style],
                                      wxColour(m_Val_ItemFG[style]),
                                      wxColour(m_Val_ItemBG[style]));
         break;
      case STYLE_IDENTIFIER :
         m_EdSample->SetIdentifierStyle(m_Val_Bold[style], m_Val_Italic[style],
                                        m_Val_Underline[style], m_Val_Case[style],
                                        wxColour(m_Val_ItemFG[style]),
                                        wxColour(m_Val_ItemBG[style]));
         break;
      case STYLE_WORD2 :
         m_EdSample->SetKeyWordStyle(2, m_Val_Bold[style], m_Val_Italic[style],
                                     m_Val_Underline[style], m_Val_Case[style],
                                     wxColour(m_Val_ItemFG[style]),
                                     wxColour(m_Val_ItemBG[style]));
         break;
      case STYLE_WORD3 :
         m_EdSample->SetKeyWordStyle(3, m_Val_Bold[style], m_Val_Italic[style],
                                     m_Val_Underline[style], m_Val_Case[style],
                                     wxColour(m_Val_ItemFG[style]),
                                     wxColour(m_Val_ItemBG[style]));
         break;
      case STYLE_WORD4 :
         m_EdSample->SetKeyWordStyle(4, m_Val_Bold[style], m_Val_Italic[style],
                                     m_Val_Underline[style], m_Val_Case[style],
                                     wxColour(m_Val_ItemFG[style]),
                                     wxColour(m_Val_ItemBG[style]));
         break;
   };
}
/*---------------------------------------------------------------------------*/
void wxPrefDlg::DisplayStyle(int style)
{
   m_Bold->SetValue(m_Val_Bold[style]);
   m_Italic->SetValue(m_Val_Italic[style]);
   m_Underline->SetValue(m_Val_Underline[style]);
   m_ItemFG->SetColour(m_Val_ItemFG[style]);
   m_ItemBG->SetColour(m_Val_ItemBG[style]);

   switch (m_Val_Case[style]) // 0 Mixed 1 Upper 2 Lower
   {
      case 0 :
         m_CaseMixed->SetValue(true);
         break;
      case 1 :
         m_CaseUpper->SetValue(true);
         break;
      case 2 :
         m_CaseLower->SetValue(true);
         break;
   };
}
/*---------------------------------------------------------------------------*/
void wxPrefDlg::ResetDefaultDataGeneral()
{
   m_Val_OddColour = _T("#FFFFAF");
   m_Val_MaxHistory = 100;
   m_Val_SavePos = true;
   m_Val_SavePers = true;
}
/*---------------------------------------------------------------------------*/
void wxPrefDlg::ResetDefaultDataEditor()
{
   m_Val_ShowEdge = true;
   m_Val_ShowLineNumber = true;
   m_Val_LineFG = _T("#000000");
   m_Val_LineBG = _T("#808080");
   m_Val_UseTab = false;
   m_Val_TabIndent = true;
   m_Val_BackUnindent = true;
   m_Val_TabWidth = 2;
   m_Val_IndentWidth = 2;
}
/*---------------------------------------------------------------------------*/
void wxPrefDlg::ResetDefaultDataSyntax()
{
   m_Val_FontName = _T("Courier");
   m_Val_FontSize = 10;

   for (int i = STYLE_DEFAULT; i < STYLE_COUNT; i++)
   {
      m_Val_Bold[i] = false;
      m_Val_Italic[i] = false;
      m_Val_Underline[i] = false;
      m_Val_ItemFG[i] = _T("#000000");
      m_Val_ItemBG[i] = _T("#FFFFFF");
      m_Val_Case[i] = 0; // 0 Mixed 1 Upper 2 Lower
   }

   m_Val_Italic[STYLE_COMMENT] = true;
   m_Val_Italic[STYLE_COMMENTLINE] = true;
   m_Val_Bold[STYLE_WORD1] = true;
   m_Val_Case[STYLE_WORD1] = 1; // 0 Mixed 1 Upper 2 Lower
   m_Val_Bold[STYLE_WORD2] = true;
   m_Val_Bold[STYLE_WORD3] = true;
   m_Val_Bold[STYLE_WORD4] = true;
   m_Val_ItemFG[STYLE_COMMENT] = _T("#C0C0C0");
   m_Val_ItemFG[STYLE_COMMENTLINE] = _T("#808080");
   m_Val_ItemFG[STYLE_NUMBER] = _T("#B000FF");
   m_Val_ItemFG[STYLE_WORD1] = _T("#238E23");
   m_Val_ItemFG[STYLE_STRING] = _T("#0000FF");
   m_Val_ItemFG[STYLE_CHARACTER] = _T("#5F9F9F");
   m_Val_ItemFG[STYLE_OPERATOR] = _T("#9F9F5F");
   m_Val_ItemFG[STYLE_IDENTIFIER] = _T("#0000FF");
   m_Val_ItemFG[STYLE_WORD2] = _T("#238E23");
   m_Val_ItemFG[STYLE_WORD3] = _T("#238E23");
   m_Val_ItemFG[STYLE_WORD4] = _T("#238E23");
}
/*---------------------------------------------------------------------------*/
void wxPrefDlg::ResetDisplayGeneral()
{
   m_OddLineColour->SetColour(m_Val_OddColour);
   m_MaxHistory->SetValue(m_Val_MaxHistory);
   m_SaveWinPos->SetValue(m_Val_SavePos);
   m_SaveWinPers->SetValue(m_Val_SavePers);
}
/*---------------------------------------------------------------------------*/
void wxPrefDlg::ResetDisplayEditor()
{
   m_ShowEdgeLine->SetValue(m_Val_ShowEdge);
   m_ShowLineNumber->SetValue(m_Val_ShowLineNumber);
   m_LineNumberFG->SetColour(m_Val_LineFG);
   m_LineNumberBG->SetColour(m_Val_LineBG);
   m_UseTab->SetValue(m_Val_UseTab);
   m_TabIndent->SetValue(m_Val_TabIndent);
   m_BackspaceUnindent->SetValue(m_Val_BackUnindent);
   m_TabWidth->SetValue(m_Val_TabWidth);
   m_IdentWidth->SetValue(m_Val_IndentWidth);
}
/*---------------------------------------------------------------------------*/
void wxPrefDlg::ResetDisplaySyntax()
{
   wxFont font(m_Val_FontSize, wxFONTFAMILY_DEFAULT, wxNORMAL, wxNORMAL,
               false, m_Val_FontName);
   m_Font->SetSelectedFont(font);
   int index = m_EdItems->GetSelection();
   if (index != wxNOT_FOUND)
      DisplayStyle(index);
   ChangeFont();
   for (int i = STYLE_DEFAULT; i < STYLE_COUNT; i++)
      ChangeStyle(i);
}
/*---------------------------------------------------------------------------*/
