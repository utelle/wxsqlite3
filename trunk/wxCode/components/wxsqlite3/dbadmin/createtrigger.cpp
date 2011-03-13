/*---------------------------------------------------------------------------*/
/* Logiciel de gestion de fichier de bases de données SQLite                 */
/*---------------------------------------------------------------------------*/
/* Projet  : wxSQLitePlus                              Version  : 0.2.3.0    */
/* Fichier : createtrigger.cpp                                               */
/* Auteur  : Fred Cailleau-Lepetit                     Date     : 24/08/2007 */
/* email   : softinthebox@free.fr                      Révision : 09/11/2008 */
/*---------------------------------------------------------------------------*/
/* Copyright (C) Fred Cailleau-Lepetit 2007-2008                             */
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
#pragma implementation "createtrigger.h"
#endif

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <wx/notebook.h>
#include <wx/valgen.h>
/*---------------------------------------------------------------------------*/
#include "createtrigger.h"
#include "wxsqliteplusapp.h"
#include "sqliteplusframe.h"
/*---------------------------------------------------------------------------*/
#define ID_TRIGGERNAME        15001
#define ID_TEMPTRIGGER        15002
#define ID_NOTEBOOK           15003
#define ID_PANEL              15004
#define ID_TYPE_OBJ           15005
#define ID_OBJ_NAME           15006
#define ID_EVENTTIME          15007
#define ID_TRIGGER_EVENT      15008
#define ID_AVAILABLE_COLUMNS  15009
#define ID_ADDCOLUMN          15010
#define ID_ADDALLCOLUMNS      15011
#define ID_REMOVECOLUMN       15012
#define ID_REMOVEALLCOLUMNS   15013
#define ID_SELECTED_COLUMNS   15014
#define ID_FOR_EACH_ROW       15015
#define ID_WHEN               15016
#define ID_TRIGGER_STATEMENT  15017
#define ID_TEXTCTRL1          15018
/*---------------------------------------------------------------------------*/
IMPLEMENT_DYNAMIC_CLASS(wxCreateTriggerDialog, wxDialog)

BEGIN_EVENT_TABLE(wxCreateTriggerDialog, wxDialog)
   EVT_NOTEBOOK_PAGE_CHANGING(ID_NOTEBOOK, wxCreateTriggerDialog::OnNotebookPageChanging)
   EVT_CHOICE(ID_TYPE_OBJ, wxCreateTriggerDialog::OnTypeObjSelected)
   EVT_CHOICE(ID_OBJ_NAME, wxCreateTriggerDialog::OnObjNameSelected)
   EVT_CHOICE(ID_TRIGGER_EVENT, wxCreateTriggerDialog::OnTriggerEventSelected)
   EVT_BUTTON(ID_ADDCOLUMN, wxCreateTriggerDialog::OnAddcolumnClick)
   EVT_UPDATE_UI(ID_ADDCOLUMN, wxCreateTriggerDialog::OnAddcolumnUpdate)
   EVT_BUTTON(ID_ADDALLCOLUMNS, wxCreateTriggerDialog::OnAddallcolumnsClick)
   EVT_UPDATE_UI(ID_ADDALLCOLUMNS, wxCreateTriggerDialog::OnAddallcolumnsUpdate)
   EVT_BUTTON(ID_REMOVECOLUMN, wxCreateTriggerDialog::OnRemovecolumnClick)
   EVT_UPDATE_UI(ID_REMOVECOLUMN, wxCreateTriggerDialog::OnRemovecolumnUpdate)
   EVT_BUTTON(ID_REMOVEALLCOLUMNS, wxCreateTriggerDialog::OnRemoveallcolumnsClick)
   EVT_UPDATE_UI(ID_REMOVEALLCOLUMNS, wxCreateTriggerDialog::OnRemoveallcolumnsUpdate)
   EVT_BUTTON(wxID_OK, wxCreateTriggerDialog::OnOkClick)
END_EVENT_TABLE()
/*---------------------------------------------------------------------------*/
wxCreateTriggerDialog::wxCreateTriggerDialog()
{
   Init();
}
/*---------------------------------------------------------------------------*/
wxCreateTriggerDialog::wxCreateTriggerDialog(wxWindow* parent, wxWindowID id,
                                             const wxString& caption,
                                             const wxPoint& pos,
                                             const wxSize& size, long style)
{
   Init();
   Create(parent, id, caption, pos, size, style);
}
/*---------------------------------------------------------------------------*/
bool wxCreateTriggerDialog::Create(wxWindow* parent, wxWindowID id,
                                   const wxString& caption, const wxPoint& pos,
                                   const wxSize& size, long style)
{
   SetExtraStyle(wxWS_EX_BLOCK_EVENTS);
   wxDialog::Create(parent, id, caption, pos, size, style);

   CreateControls();
   SetIcon(wxGetApp().GetIcon(ID_ICO_TRIGGER2));
   if (GetSizer())
   {
      GetSizer()->SetSizeHints(this);
   }
   Centre();
   return true;
}
/*---------------------------------------------------------------------------*/
wxCreateTriggerDialog::~wxCreateTriggerDialog()
{
}
/*---------------------------------------------------------------------------*/
void wxCreateTriggerDialog::SetDatabase(wxSQLite3Database* db,
                                        const wxString& base)
{
   m_Db = db;
   m_Base = base;
   if (!m_Db||!m_Db->IsOpen())
      m_Db = NULL;
   PopulateObjName();
   DoEnableColumns();
}
/*---------------------------------------------------------------------------*/
void wxCreateTriggerDialog::SetObject(const wxString& objname, bool table)
{
   int index;

   if (!m_Db||!m_Db->IsOpen())
      return;
   if (table)
      m_TypeObj->SetStringSelection(_("TABLE"));
   else
      m_TypeObj->SetStringSelection(_("VIEW"));
   m_TypeObj->Enable(false);
   PopulateObjName();
   if ((index = m_ObjName->FindString(objname)) != wxNOT_FOUND)
   {
      m_ObjName->SetSelection(index);
      m_ObjName->Enable(false);
      PopulateColumns();
      DoEnableColumns();
   }
}
/*---------------------------------------------------------------------------*/
void wxCreateTriggerDialog::Init()
{
   m_TriggerName = NULL;
   m_TempTrigger = NULL;
   m_TypeObj = NULL;
   m_ObjName = NULL;
   m_TriggerTime = NULL;
   m_TriggerEvent = NULL;
   m_AvailableColumns = NULL;
   m_BtnAddColumn = NULL;
   m_BtnAddAllColumns = NULL;
   m_BtnRemoveColumn = NULL;
   m_BtnRemoveAllColumns = NULL;
   m_SelectedColumns = NULL;
   m_ForEachRow = NULL;
   m_When = NULL;
   m_Statement = NULL;
   m_TextDdl = NULL;
   m_Db = NULL;
   m_Temporary = false;
}
/*---------------------------------------------------------------------------*/
void wxCreateTriggerDialog::CreateControls()
{
   wxBoxSizer* bSizer1 = new wxBoxSizer(wxVERTICAL);
   SetSizer(bSizer1);

   wxBoxSizer* bSizer2 = new wxBoxSizer(wxHORIZONTAL);
   bSizer1->Add(bSizer2, 0, wxALIGN_LEFT|wxALL, 5);

   wxStaticText* sText1 = new wxStaticText(this, wxID_STATIC, _("Na&me :"),
                                           wxDefaultPosition, wxDefaultSize, 0);
   bSizer2->Add(sText1, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

   m_TriggerName = new wxTextCtrl(this, ID_TRIGGERNAME, wxEmptyString,
                                  wxDefaultPosition, wxSize(200, -1), 0);
   bSizer2->Add(m_TriggerName, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

   bSizer2->Add(20, 5, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

   m_TempTrigger = new wxCheckBox(this, ID_TEMPTRIGGER, _("&Temporary Trigger"),
                                  wxDefaultPosition, wxDefaultSize, 0);
   m_TempTrigger->SetValue(false);
   bSizer2->Add(m_TempTrigger, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

   wxNotebook* nBook1 = new wxNotebook(this, ID_NOTEBOOK, wxDefaultPosition,
                                       wxDefaultSize, wxBK_DEFAULT);

   wxPanel* panel1 = new wxPanel(nBook1, ID_PANEL, wxDefaultPosition,
                                 wxDefaultSize, wxTAB_TRAVERSAL);
   wxBoxSizer* bSizer3 = new wxBoxSizer(wxVERTICAL);
   panel1->SetSizer(bSizer3);

   wxBoxSizer* bSizer4 = new wxBoxSizer(wxHORIZONTAL);
   bSizer3->Add(bSizer4, 0, wxGROW, 0);
   wxStaticText* sText2 = new wxStaticText(panel1, wxID_STATIC,
                                           _("Object : "),
                                           wxDefaultPosition, wxSize(80, -1), 0);
   bSizer4->Add(sText2, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

   wxArrayString m_TypeObjStrings;
   m_TypeObjStrings.Add(_("TABLE"));
   m_TypeObjStrings.Add(_("VIEW"));
   m_TypeObj = new wxChoice(panel1, ID_TYPE_OBJ, wxDefaultPosition,
                            wxSize(110, -1), m_TypeObjStrings, 0);
   m_TypeObj->SetStringSelection(_("TABLE"));
   bSizer4->Add(m_TypeObj, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

   wxArrayString m_ObjNameStrings;
   m_ObjName = new wxChoice(panel1, ID_OBJ_NAME, wxDefaultPosition,
                            wxDefaultSize, m_ObjNameStrings, 0);
   bSizer4->Add(m_ObjName, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5);

   wxBoxSizer* bSizer5 = new wxBoxSizer(wxHORIZONTAL);
   bSizer3->Add(bSizer5, 0, wxGROW, 0);
   wxStaticText* sText3 = new wxStaticText(panel1, wxID_STATIC, _("Type : "),
                                           wxDefaultPosition, wxSize(80, -1), 0);
   bSizer5->Add(sText3, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

   wxArrayString m_TriggerTimeStrings;
   m_TriggerTimeStrings.Add(_("AFTER"));
   m_TriggerTimeStrings.Add(_("BEFORE"));
   m_TriggerTime = new wxChoice(panel1, ID_EVENTTIME, wxDefaultPosition,
                                wxSize(110, -1), m_TriggerTimeStrings, 0);
   m_TriggerTime->SetStringSelection(_("BEFORE"));
   bSizer5->Add(m_TriggerTime, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

   wxArrayString m_TriggerEventStrings;
   m_TriggerEventStrings.Add(_("DELETE"));
   m_TriggerEventStrings.Add(_("INSERT"));
   m_TriggerEventStrings.Add(_("UPDATE"));
   m_TriggerEventStrings.Add(_("UPDATE OF"));
   m_TriggerEvent = new wxChoice(panel1, ID_TRIGGER_EVENT, wxDefaultPosition,
                                 wxDefaultSize, m_TriggerEventStrings, 0);
   m_TriggerEvent->SetStringSelection(_("DELETE"));
   bSizer5->Add(m_TriggerEvent, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

   wxFlexGridSizer* fgSizer1 = new wxFlexGridSizer(2, 3, 0, 0);
   fgSizer1->AddGrowableCol(0);
   fgSizer1->AddGrowableCol(2);
   bSizer3->Add(fgSizer1, 0, wxGROW|wxALL, 0);
   wxStaticText* sText4 = new wxStaticText(panel1, wxID_STATIC,
                                           _("Available Columns"),
                                           wxDefaultPosition, wxDefaultSize, 0);
   fgSizer1->Add(sText4, 0,
                 wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxTOP, 5);

   fgSizer1->Add(5, 5, 0,
                 wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|
                 wxLEFT|wxRIGHT|wxTOP, 5);

   wxStaticText* sText5 = new wxStaticText(panel1, wxID_STATIC,
                                           _("Selected Columns"),
                                           wxDefaultPosition, wxDefaultSize, 0);
   fgSizer1->Add(sText5, 0,
                 wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxTOP, 5);

   wxArrayString m_AvailableColumnsStrings;
   m_AvailableColumns = new wxListBox(panel1, ID_AVAILABLE_COLUMNS,
                                      wxDefaultPosition, wxDefaultSize,
                                      m_AvailableColumnsStrings,
                                      wxLB_EXTENDED/*wxLB_MULTIPLE*/|wxLB_SORT);
   fgSizer1->Add(m_AvailableColumns, 1, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

   wxGridSizer* gSizer1 = new wxGridSizer(4, 1, 0, 0);
   fgSizer1->Add(gSizer1, 0, wxALIGN_CENTER_HORIZONTAL|wxGROW, 0);
   m_BtnAddColumn = new wxBitmapButton(panel1, ID_ADDCOLUMN,
                                       wxGetApp().GetBmp(ID_BMP_RIGHTARROW1),
                                       wxDefaultPosition, wxDefaultSize,
                                       wxBU_AUTODRAW);
   gSizer1->Add(m_BtnAddColumn, 0,
                wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 0);

   m_BtnAddAllColumns = new wxBitmapButton(panel1, ID_ADDALLCOLUMNS,
                                           wxGetApp().GetBmp(ID_BMP_RIGHTARROW2),
                                           wxDefaultPosition, wxDefaultSize,
                                           wxBU_AUTODRAW);
   gSizer1->Add(m_BtnAddAllColumns, 0,
                wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 0);

   m_BtnRemoveColumn = new wxBitmapButton(panel1, ID_REMOVECOLUMN,
                                          wxGetApp().GetBmp(ID_BMP_LEFTARROW1),
                                          wxDefaultPosition, wxDefaultSize,
                                          wxBU_AUTODRAW);
   gSizer1->Add(m_BtnRemoveColumn, 0,
                wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 0);

   m_BtnRemoveAllColumns = new wxBitmapButton(panel1, ID_REMOVEALLCOLUMNS,
                                              wxGetApp().GetBmp(ID_BMP_LEFTARROW2),
                                              wxDefaultPosition, wxDefaultSize,
                                              wxBU_AUTODRAW);
   gSizer1->Add(m_BtnRemoveAllColumns, 0,
                wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 0);

   wxArrayString m_SelectedColumnsStrings;
   m_SelectedColumns = new wxListBox(panel1, ID_SELECTED_COLUMNS,
                                     wxDefaultPosition, wxDefaultSize,
                                     m_SelectedColumnsStrings,
                                     wxLB_EXTENDED/*wxLB_MULTIPLE*/|wxLB_SORT);
   fgSizer1->Add(m_SelectedColumns, 1, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

   m_ForEachRow = new wxCheckBox(panel1, ID_FOR_EACH_ROW, _("For Each Row"),
                                 wxDefaultPosition, wxDefaultSize, 0);
   m_ForEachRow->SetValue(false);
   bSizer3->Add(m_ForEachRow, 0, wxALIGN_LEFT|wxALL, 5);

   wxBoxSizer* bSizer6 = new wxBoxSizer(wxHORIZONTAL);
   bSizer3->Add(bSizer6, 0, wxGROW, 0);
   wxStaticText* sText6 = new wxStaticText(panel1, wxID_STATIC, _("When : "),
                                           wxDefaultPosition, wxDefaultSize, 0);
   bSizer6->Add(sText6, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

   m_When = new wxTextCtrl(panel1, ID_WHEN, wxEmptyString, wxDefaultPosition,
                           wxDefaultSize, 0);
   bSizer6->Add(m_When, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5);

   wxStaticText* sText7 = new wxStaticText(panel1, wxID_STATIC,
                                           _("Trigger Statement"),
                                           wxDefaultPosition, wxDefaultSize, 0);
   bSizer3->Add(sText7, 0, wxALIGN_LEFT|wxLEFT|wxRIGHT|wxTOP, 5);

   m_Statement = new wxSQLEditor(panel1, ID_TRIGGER_STATEMENT, wxDefaultPosition,
                                 wxSize(500, 150));
   m_Statement->SetLineNumberMarginStyle(false);

   bSizer3->Add(m_Statement, 0, wxGROW|wxALL, 5);

   nBook1->AddPage(panel1, _("Trigger"));

   m_TextDdl = new wxDDLEditor(nBook1, ID_TEXTCTRL1);

   nBook1->AddPage(m_TextDdl, _("DDL"));

   bSizer1->Add(nBook1, 0, wxGROW|wxALL, 5);

   wxStdDialogButtonSizer* dlgBtnSizer1 = new wxStdDialogButtonSizer;

   bSizer1->Add(dlgBtnSizer1, 0, wxALIGN_RIGHT|wxALL, 5);
   wxButton* btnOk = new wxButton(this, wxID_OK, _("&OK"), wxDefaultPosition,
                                  wxDefaultSize, 0);
   btnOk->SetDefault();
   dlgBtnSizer1->AddButton(btnOk);

   wxButton* btnCancel = new wxButton(this, wxID_CANCEL, _("&Cancel"),
                                      wxDefaultPosition, wxDefaultSize, 0);
   dlgBtnSizer1->AddButton(btnCancel);

   dlgBtnSizer1->Realize();
   // Ajout d'un spacer en fin de dialogue pour que les boutons
   // ne soient pas tronqués lorsque les listes de définition de l'objet
   // de ratacchement au trigger sont désactivées
   bSizer1->Add(20, 2, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

   // Connect events and objects
   m_TriggerName->Connect(ID_TRIGGERNAME, wxEVT_CHAR,
                          wxKeyEventHandler(wxCreateTriggerDialog::OnChar),
                          NULL, this);
   // Set validators
   m_TempTrigger->SetValidator(wxGenericValidator(&m_Temporary));
}
/*---------------------------------------------------------------------------*/
bool wxCreateTriggerDialog::ShowToolTips()
{
    return true;
}
/*---------------------------------------------------------------------------*/
void wxCreateTriggerDialog::OnChar(wxKeyEvent& event)
{
   int c = event.GetKeyCode();
   if ((!wxIsalnum(c) && c != _T('_') && c != _T(' ') && c != WXK_BACK && c != WXK_DELETE)&&
      // Ctrl+C Ctrl+V Ctrl+X
       !(event.ControlDown() && (c == 3 || c == 22 || c == 24)))
      return;
   event.Skip();
}
/*---------------------------------------------------------------------------*/
void wxCreateTriggerDialog::OnNotebookPageChanging(wxNotebookEvent& event)
{
   if (event.GetOldSelection() == 0)
   {
      wxString ddl = GetCreateTriggerDDL();

      if (ddl.IsEmpty())
         event.Veto();
      else
         m_TextDdl->SetValue(ddl);
   }
}
/*---------------------------------------------------------------------------*/
void wxCreateTriggerDialog::OnOkClick(wxCommandEvent& event)
{
   if (GetCreateTriggerDDL().IsEmpty())
      return;
   event.Skip();
}
/*---------------------------------------------------------------------------*/
void wxCreateTriggerDialog::OnTypeObjSelected(wxCommandEvent& event)
{
   PopulateObjName();
   DoEnableColumns();
   event.Skip();
}
/*---------------------------------------------------------------------------*/
void wxCreateTriggerDialog::OnObjNameSelected(wxCommandEvent& event)
{
   PopulateColumns();
   event.Skip();
}
/*---------------------------------------------------------------------------*/
void wxCreateTriggerDialog::OnTriggerEventSelected(wxCommandEvent& event)
{
   DoEnableColumns();
   event.Skip();
}
/*---------------------------------------------------------------------------*/
void wxCreateTriggerDialog::OnAddcolumnClick(wxCommandEvent& event)
{
   wxArrayInt selections;
   wxArrayString items;

   m_AvailableColumns->GetSelections(selections);
   for (size_t i = selections.GetCount(); i > 0; i--)
   {
      items.Add(m_AvailableColumns->GetString(selections[i - 1]));
      m_AvailableColumns->Delete(selections[i - 1]);
   }
   m_SelectedColumns->Append(items);
   event.Skip();
}
/*---------------------------------------------------------------------------*/
void wxCreateTriggerDialog::OnAddcolumnUpdate(wxUpdateUIEvent& event)
{
   bool enable = false;

   if (m_TriggerEvent->GetCurrentSelection() == 3)
   {
      wxArrayInt selections;

      m_AvailableColumns->GetSelections(selections);
      enable = (selections.GetCount() > 0);
   }
   event.Enable(enable);
}
/*---------------------------------------------------------------------------*/
void wxCreateTriggerDialog::OnAddallcolumnsClick(wxCommandEvent& event)
{
   wxArrayString items;

   items = m_AvailableColumns->GetStrings();
   m_AvailableColumns->Clear();
   m_SelectedColumns->Append(items);
   event.Skip();
}
/*---------------------------------------------------------------------------*/
void wxCreateTriggerDialog::OnAddallcolumnsUpdate(wxUpdateUIEvent& event)
{
   bool enable = false;

   if (m_TriggerEvent->GetCurrentSelection() == 3)
      enable = (m_AvailableColumns->GetCount() > 0);
   event.Enable(enable);
}
/*---------------------------------------------------------------------------*/
void wxCreateTriggerDialog::OnRemovecolumnClick(wxCommandEvent& event)
{
   wxArrayInt selections;
   wxArrayString items;

   m_SelectedColumns->GetSelections(selections);
   for (size_t i = selections.GetCount(); i > 0; i--)
   {
      items.Add(m_SelectedColumns->GetString(selections[i - 1]));
      m_SelectedColumns->Delete(selections[i - 1]);
   }
   m_AvailableColumns->Append(items);
   event.Skip();
}
/*---------------------------------------------------------------------------*/
void wxCreateTriggerDialog::OnRemovecolumnUpdate(wxUpdateUIEvent& event)
{
   bool enable = false;
   if (m_TriggerEvent->GetCurrentSelection() == 3)
   {
      wxArrayInt selections;

      m_SelectedColumns->GetSelections(selections);
      enable = (selections.GetCount() > 0);
   }
   event.Enable(enable);
}
/*---------------------------------------------------------------------------*/
void wxCreateTriggerDialog::OnRemoveallcolumnsClick(wxCommandEvent& event)
{
   wxArrayString items;

   items = m_SelectedColumns->GetStrings();
   m_SelectedColumns->Clear();
   m_AvailableColumns->Append(items);
   event.Skip();
}
/*---------------------------------------------------------------------------*/
void wxCreateTriggerDialog::OnRemoveallcolumnsUpdate(wxUpdateUIEvent& event)
{
   bool enable = false;

   if (m_TriggerEvent->GetCurrentSelection() == 3)
      enable = (m_SelectedColumns->GetCount() > 0);
   event.Enable(enable);
}
/*---------------------------------------------------------------------------*/
void wxCreateTriggerDialog::PopulateObjName()
{
   wxSQLite3ResultSet tblQRY;
   wxArrayString m_TriggerTimeStrings;
   wxSQLitePlusFrame* frame;
   wxSQLiteObjectType objtype;

   if (m_Db == NULL)
      return;

   m_TriggerTime->Clear();
   if (m_TypeObj->GetCurrentSelection() == 0)
   {
      objtype = otTable;
      m_TriggerTime->Enable(true);
      m_TriggerTimeStrings.Add(_("AFTER"));
      m_TriggerTimeStrings.Add(_("BEFORE"));
      m_TriggerTime->Append(m_TriggerTimeStrings);
      m_TriggerTime->SetStringSelection(_("BEFORE"));
   }
   else
   {
      objtype = otView;
      m_TriggerTimeStrings.Add(_("INSTEAD OF"));
      m_TriggerTime->Append(m_TriggerTimeStrings);
      m_TriggerTime->SetStringSelection(_("INSTEAD OF"));
   }

   m_ObjName->Clear();
   m_AvailableColumns->Clear();
   m_SelectedColumns->Clear();

   try
   {
      frame = (wxSQLitePlusFrame*)wxGetApp().GetTopWindow();
      tblQRY = frame->GetObjNameList(objtype, m_Base);
      while (tblQRY.NextRow())
         m_ObjName->Append(tblQRY.GetString(0));
   }
   catch(wxSQLite3Exception& ex)
   {
      wxGetApp().ShowError(_T("PopulateObjName"), ex);
   }
   tblQRY.Finalize();
}
/*---------------------------------------------------------------------------*/
void wxCreateTriggerDialog::PopulateColumns()
{
   wxString tablename, sql, basename;
   wxSQLite3ResultSet clmnQRY;

   if (m_Db == NULL)
      return;

   tablename = m_ObjName->GetStringSelection();
   if (m_Base != wxEmptyString)
      basename = m_Base;
   else
      basename = _T("main");
   sql = wxString::Format(_T("PRAGMA %s.table_info(\"%s\");"),
                          basename.c_str(), tablename.c_str());

   m_AvailableColumns->Clear();
   m_SelectedColumns->Clear();

   try
   {
      clmnQRY = m_Db->ExecuteQuery(ToUTF8(sql));
      while (clmnQRY.NextRow())
         m_AvailableColumns->Append(clmnQRY.GetString(1));
   }
   catch(wxSQLite3Exception& ex)
   {
      wxGetApp().ShowError(_T("PopulateColumns"), ex);
   }
   clmnQRY.Finalize();
}
/*---------------------------------------------------------------------------*/
wxString wxCreateTriggerDialog::GetCreateTriggerDDL()
{
   wxString ddl, triggername, objname, when, statement, ddlerror, basename;
   wxSQLitePlusFrame* frame;

   if (!m_Db||!m_Db->IsOpen())
      return wxEmptyString;

   triggername = m_TriggerName->GetValue();
   if (triggername.IsEmpty())
   {
      wxMessageBox(_("You have to enter a trigger name."),
                   _("Error"));
      m_TriggerName->SetFocus();
      return wxEmptyString;
   }
   objname = m_ObjName->GetStringSelection();
   if (objname.IsEmpty())
   {
      wxMessageBox(_("You have to select an table or view name."),
                   _("Error"));
      m_ObjName->SetFocus();
      return wxEmptyString;
   }
   if ((m_TriggerEvent->GetSelection() == 3)&&
       (m_SelectedColumns->GetCount() == 0))
   {
      wxMessageBox(_("You have to select column(s) for the trigger."),
                   _("Error"));
      m_AvailableColumns->SetFocus();
      return wxEmptyString;
   }
   statement = m_Statement->GetText();
   if (statement.IsEmpty())
   {
      wxMessageBox(_("The trigger statement is a mandatory value."),
                   _("Error"));
      m_Statement->SetFocus();
      return wxEmptyString;
   }

   frame = (wxSQLitePlusFrame*)wxGetApp().GetTopWindow();
   if (frame->ExistDbObject(otTrigger, triggername, m_Base))
   {
      wxMessageBox(_("Trigger with this name already exist."),
                   _("Error"));
      m_TriggerName->SetFocus();
      return wxEmptyString;
   }

   // Création du DDL
   ddl = _T("CREATE ");
   if (m_TempTrigger->IsChecked())
      ddl += _T("TEMPORARY ");
   ddl += _T("TRIGGER ");
   if (!m_TempTrigger->IsChecked() && m_Base != wxEmptyString)
      ddl += m_Base + _T(".");
   ddl += _T("\"") + triggername.Lower() + _T("\"\n");
   ddl += m_TriggerTime->GetStringSelection() + _T(" ");
   ddl += m_TriggerEvent->GetStringSelection();
   if (m_TriggerEvent->GetSelection() == 3)
   {
      for (size_t i = 0; i < m_SelectedColumns->GetCount(); i++)
      {
         ddl += _T(" ") + m_SelectedColumns->GetString(i);
         if (i != m_SelectedColumns->GetCount() - 1)
            ddl += _T(",");
      }
   }
   ddl += _T("\n");
   ddl += _T("ON \"") + objname + _T("\"\n");
   if (m_ForEachRow->IsChecked())
      ddl += _T("FOR EACH ROW\n");
   when = m_When->GetValue();
   if (!when.IsEmpty())
      ddl += _T("WHEN ") + when + _T("\n");
   ddl += _T("BEGIN\n");
   ddl += statement;
   if (statement.Last() != _T('\n'))
      ddl += _T("\n");
   ddl += _T("END;");

   if (!wxGetApp().CheckStatementSyntax(m_Db, ddl, ddlerror))
   {
      wxMessageBox(ddlerror, _("Error"));
      m_Statement->SetFocus();
      return wxEmptyString;
   }

   return ddl;
}
/*---------------------------------------------------------------------------*/
void wxCreateTriggerDialog::DoEnableColumns()
{
   bool enable = false;

   if (m_TriggerEvent->GetCurrentSelection() == 3)
      enable = true;
   m_AvailableColumns->Enable(enable);
   m_SelectedColumns->Enable(enable);
}
/*---------------------------------------------------------------------------*/
