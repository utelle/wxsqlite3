/*---------------------------------------------------------------------------*/
/* Logiciel de gestion de fichier de bases de données SQLite                 */
/*---------------------------------------------------------------------------*/
/* Projet  : wxSQLitePlus                              Version  : 0.2.3.0    */
/* Fichier : sortdlg.cpp                                                     */
/* Auteur  : Fred Cailleau-Lepetit                     Date     : 23/08/2008 */
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
#pragma implementation "sortdlg.h"
#endif

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "wxsqliteplusapp.h"
#include "sortdlg.h"
/*---------------------------------------------------------------------------*/
#define ID_AVAILABLE    15001
#define ID_TORIGHT      15002
#define ID_ALLTORIGHT   15003
#define ID_TOLEFT       15004
#define ID_ALLTOLEFT    15005
#define ID_SELECTED     15006
#define ID_FIRST        15007
#define ID_UP           15008
#define ID_DOWN         15009
#define ID_LAST         15010
#define ID_RB_ASC       15011
#define ID_RB_DESC      15012
/*---------------------------------------------------------------------------*/
IMPLEMENT_DYNAMIC_CLASS(wxSortDialog, wxDialog)
BEGIN_EVENT_TABLE(wxSortDialog, wxDialog)
   EVT_BUTTON(ID_TORIGHT, wxSortDialog::OnTorightClick)
   EVT_UPDATE_UI(ID_TORIGHT, wxSortDialog::OnTorightUpdate)
   EVT_BUTTON(ID_ALLTORIGHT, wxSortDialog::OnAlltorightClick)
   EVT_UPDATE_UI(ID_ALLTORIGHT, wxSortDialog::OnAlltorightUpdate)
   EVT_BUTTON(ID_TOLEFT, wxSortDialog::OnToleftClick)
   EVT_UPDATE_UI(ID_TOLEFT, wxSortDialog::OnToleftUpdate)
   EVT_BUTTON(ID_ALLTOLEFT, wxSortDialog::OnAlltoleftClick)
   EVT_UPDATE_UI(ID_ALLTOLEFT, wxSortDialog::OnAlltoleftUpdate)
   EVT_LISTBOX(ID_SELECTED, wxSortDialog::OnSelectedSelected)
   EVT_BUTTON(ID_FIRST, wxSortDialog::OnFirstClick)
   EVT_UPDATE_UI(ID_FIRST, wxSortDialog::OnFirstUpdate)
   EVT_BUTTON(ID_UP, wxSortDialog::OnUpClick)
   EVT_UPDATE_UI(ID_UP, wxSortDialog::OnUpUpdate)
   EVT_BUTTON(ID_DOWN, wxSortDialog::OnDownClick)
   EVT_UPDATE_UI(ID_DOWN, wxSortDialog::OnDownUpdate)
   EVT_BUTTON(ID_LAST, wxSortDialog::OnLastClick)
   EVT_UPDATE_UI(ID_LAST, wxSortDialog::OnLastUpdate)
   EVT_RADIOBUTTON(ID_RB_ASC, wxSortDialog::OnRbAscSelected)
   EVT_RADIOBUTTON(ID_RB_DESC, wxSortDialog::OnRbDescSelected)
   EVT_BUTTON(wxID_OK, wxSortDialog::OnOkClick)
END_EVENT_TABLE()
/*---------------------------------------------------------------------------*/
wxSortDialog::wxSortDialog()
{
   Init();
}
/*---------------------------------------------------------------------------*/
wxSortDialog::wxSortDialog(wxWindow* parent, wxWindowID id,
                           const wxString& caption, const wxPoint& pos,
                           const wxSize& size, long style)
{
   Init();
   Create(parent, id, caption, pos, size, style);
}
/*---------------------------------------------------------------------------*/
bool wxSortDialog::Create(wxWindow* parent, wxWindowID id,
                          const wxString& caption, const wxPoint& pos,
                          const wxSize& size, long style)
{
   SetExtraStyle(wxWS_EX_BLOCK_EVENTS);
   wxDialog::Create(parent, id, caption, pos, size, style);

   CreateControls();
   SetIcon(wxGetApp().GetIcon(ID_ICO_SORT));
   if (GetSizer())
   {
      GetSizer()->SetSizeHints(this);
   }
   Centre();
   return true;
}
/*---------------------------------------------------------------------------*/
wxSortDialog::~wxSortDialog()
{
}
/*---------------------------------------------------------------------------*/
void wxSortDialog::Init()
{
   m_Available = NULL;
   m_BtnRight = NULL;
   m_BtnAllRight = NULL;
   m_BtnLeft = NULL;
   m_BtnAllLeft = NULL;
   m_Selected = NULL;
   m_BtnTop = NULL;
   m_BtnUp = NULL;
   m_BtnDown = NULL;
   m_BtnBottom = NULL;
   m_Ascending = NULL;
   m_Descending = NULL;
}
/*---------------------------------------------------------------------------*/
void wxSortDialog::CreateControls()
{
   wxBoxSizer* bSizer1 = new wxBoxSizer(wxVERTICAL);
   SetSizer(bSizer1);

   wxBoxSizer* bSizer2 = new wxBoxSizer(wxHORIZONTAL);
   bSizer1->Add(bSizer2, 1, wxGROW, 0);

   wxBoxSizer* bSizer3 = new wxBoxSizer(wxVERTICAL);
   bSizer2->Add(bSizer3, 1, wxGROW|wxALL, 5);

   wxStaticText* sText1 = new wxStaticText(this, wxID_STATIC,
                                           _("&Available Columns"),
                                           wxDefaultPosition, wxDefaultSize, 0);
   bSizer3->Add(sText1, 0, wxALIGN_LEFT, 0);

   m_Available = new wxListBox(this, ID_AVAILABLE, wxDefaultPosition,
                               wxSize(150, 200), 0, NULL, wxLB_MULTIPLE|wxLB_SORT);
   bSizer3->Add(m_Available, 1, wxGROW, 0);

   wxBoxSizer* bSizer4 = new wxBoxSizer(wxVERTICAL);
   bSizer2->Add(bSizer4, 0, wxALIGN_CENTER_VERTICAL, 0);

   m_BtnRight = new wxBitmapButton(this, ID_TORIGHT,
                                   wxGetApp().GetBmp(ID_BMP_RIGHT),
                                   wxDefaultPosition, wxDefaultSize,
                                   wxBU_AUTODRAW);
   bSizer4->Add(m_BtnRight, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

   m_BtnAllRight = new wxBitmapButton(this, ID_ALLTORIGHT,
                                      wxGetApp().GetBmp(ID_BMP_ALLTORIGHT),
                                      wxDefaultPosition, wxDefaultSize,
                                      wxBU_AUTODRAW);
   bSizer4->Add(m_BtnAllRight, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

   m_BtnLeft = new wxBitmapButton(this, ID_TOLEFT,
                                  wxGetApp().GetBmp(ID_BMP_LEFT),
                                  wxDefaultPosition, wxDefaultSize,
                                  wxBU_AUTODRAW);
   bSizer4->Add(m_BtnLeft, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

   m_BtnAllLeft = new wxBitmapButton(this, ID_ALLTOLEFT,
                                     wxGetApp().GetBmp(ID_BMP_ALLTOLEFT),
                                     wxDefaultPosition, wxDefaultSize,
                                     wxBU_AUTODRAW);
   bSizer4->Add(m_BtnAllLeft, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

   wxBoxSizer* bSizer5 = new wxBoxSizer(wxVERTICAL);
   bSizer2->Add(bSizer5, 1, wxGROW|wxALL, 5);

   wxStaticText* sText2 = new wxStaticText(this, wxID_STATIC,
                                           _("&Selected Columns"),
                                           wxDefaultPosition, wxDefaultSize, 0);
   bSizer5->Add(sText2, 0, wxALIGN_LEFT, 0);

   m_Selected = new wxListBox(this, ID_SELECTED, wxDefaultPosition,
                              wxSize(150, 200), 0, NULL, wxLB_SINGLE);
   bSizer5->Add(m_Selected, 1, wxGROW, 0);

   wxBoxSizer* bSizer6 = new wxBoxSizer(wxVERTICAL);
   bSizer2->Add(bSizer6, 0, wxALIGN_CENTER_VERTICAL|wxLEFT, 0);

   m_BtnTop = new wxBitmapButton(this, ID_FIRST,
                                 wxGetApp().GetBmp(ID_BMP_FIRST),
                                 wxDefaultPosition, wxDefaultSize,
                                 wxBU_AUTODRAW);
   bSizer6->Add(m_BtnTop, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

   m_BtnUp = new wxBitmapButton(this, ID_UP,
                                wxGetApp().GetBmp(ID_BMP_UP),
                                wxDefaultPosition, wxDefaultSize,
                                wxBU_AUTODRAW);
   bSizer6->Add(m_BtnUp, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

   m_BtnDown = new wxBitmapButton(this, ID_DOWN,
                                  wxGetApp().GetBmp(ID_BMP_DOWN),
                                  wxDefaultPosition, wxDefaultSize,
                                  wxBU_AUTODRAW);
   bSizer6->Add(m_BtnDown, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

   m_BtnBottom = new wxBitmapButton(this, ID_LAST,
                                    wxGetApp().GetBmp(ID_BMP_LAST),
                                    wxDefaultPosition, wxDefaultSize,
                                    wxBU_AUTODRAW);
   bSizer6->Add(m_BtnBottom, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

   wxBoxSizer* bSizer7 = new wxBoxSizer(wxVERTICAL);
   bSizer2->Add(bSizer7, 0, wxALIGN_TOP, 0);

   m_Ascending = new wxRadioButton(this, ID_RB_ASC, _("&Ascending"),
                                   wxDefaultPosition, wxDefaultSize,
                                   wxRB_GROUP);
   m_Ascending->SetValue(true);
   bSizer7->Add(m_Ascending, 0, wxALIGN_LEFT, 0);

   m_Descending = new wxRadioButton(this, ID_RB_DESC, _("D&escending"),
                                    wxDefaultPosition, wxDefaultSize, 0);
   m_Descending->SetValue(false);
   bSizer7->Add(m_Descending, 0, wxALIGN_LEFT, 0);

   wxStdDialogButtonSizer* dlgBtnSizer1 = new wxStdDialogButtonSizer;

   bSizer1->Add(dlgBtnSizer1, 0, wxALIGN_RIGHT|wxALL, 5);
   wxButton* btnOk = new wxButton(this, wxID_OK, _("&OK"),
                                  wxDefaultPosition, wxDefaultSize, 0);
   btnOk->SetDefault();
   dlgBtnSizer1->AddButton(btnOk);

   wxButton* btnCancel = new wxButton(this, wxID_CANCEL, _("&Cancel"),
                                      wxDefaultPosition, wxDefaultSize, 0);
   dlgBtnSizer1->AddButton(btnCancel);

   dlgBtnSizer1->Realize();
}
/*---------------------------------------------------------------------------*/
void wxSortDialog::OnTorightClick(wxCommandEvent& event)
{
   int count;
   wxArrayInt selections;

   count = m_Available->GetSelections(selections);
   if (count > 0)
   {
      for (int i = 0; i < count; i++)
         m_Selected->Append(m_Available->GetString(selections[i]));

      for (int i = count - 1; i >= 0; i--)
         m_Available->Delete(selections[i]);
   }
   event.Skip();
}
/*---------------------------------------------------------------------------*/
void wxSortDialog::OnTorightUpdate(wxUpdateUIEvent& event)
{
   wxArrayInt selections;

   event.Enable(m_Available->GetSelections(selections) > 0);
}
/*---------------------------------------------------------------------------*/
void wxSortDialog::OnAlltorightClick(wxCommandEvent& event)
{
   int count;

   count = m_Available->GetCount();
   if (count > 0)
   {
      for (int i = 0; i < count; i++)
         m_Selected->Append(m_Available->GetString(i));

      m_Available->Clear();
   }
   event.Skip();
}
/*---------------------------------------------------------------------------*/
void wxSortDialog::OnAlltorightUpdate(wxUpdateUIEvent& event)
{
   event.Enable(m_Available->GetCount() > 0);
}
/*---------------------------------------------------------------------------*/
void wxSortDialog::OnAlltoleftClick(wxCommandEvent& event)
{
   int count;
   wxString tmp;

   count = m_Selected->GetCount();
   if (count > 0)
   {
      for (int i = 0; i < count; i++)
      {
         tmp = m_Selected->GetString(i).BeforeLast(_T(' ')) + _T(" ASC");
         m_Available->Append(tmp);
      }
      m_Selected->Clear();
   }
   event.Skip();
}
/*---------------------------------------------------------------------------*/
void wxSortDialog::OnAlltoleftUpdate(wxUpdateUIEvent& event)
{
   event.Enable(m_Selected->GetCount() > 0);
}
/*---------------------------------------------------------------------------*/
void wxSortDialog::OnToleftClick(wxCommandEvent& event)
{
   int count;
   wxString tmp;
   wxArrayInt selections;

   count = m_Selected->GetSelections(selections);
   if (count > 0)
   {
      for (int i = 0; i < count; i++)
      {
         tmp = m_Selected->GetString(selections[i]).BeforeLast(_T(' ')) + _T(" ASC");
         m_Available->Append(tmp);
      }

      for (int i = count - 1; i >= 0; i--)
         m_Selected->Delete(selections[i]);
   }
   event.Skip();
}
/*---------------------------------------------------------------------------*/
void wxSortDialog::OnToleftUpdate(wxUpdateUIEvent& event)
{
   wxArrayInt selections;

   event.Enable(m_Selected->GetSelections(selections) > 0);
}
/*---------------------------------------------------------------------------*/
void wxSortDialog::OnFirstClick(wxCommandEvent& event)
{
   int index;
   wxString tmp;

   index = m_Selected->GetSelection();
   if (index != wxNOT_FOUND)
   {
      tmp = m_Selected->GetString(index);
      m_Selected->Delete(index);
      m_Selected->Insert(tmp, 0);
      m_Selected->SetSelection(0);
   }
   event.Skip();
}
/*---------------------------------------------------------------------------*/
void wxSortDialog::OnFirstUpdate(wxUpdateUIEvent& event)
{
   event.Enable(m_Selected->GetSelection() > 0);
}
/*---------------------------------------------------------------------------*/
void wxSortDialog::OnUpClick(wxCommandEvent& event)
{
   int index;
   wxString tmp;

   index = m_Selected->GetSelection();
   tmp = m_Selected->GetString(index);
   m_Selected->Delete(index);
   index--;
   m_Selected->Insert(tmp, index);
   m_Selected->SetSelection(index);
   event.Skip();
}
/*---------------------------------------------------------------------------*/
void wxSortDialog::OnUpUpdate(wxUpdateUIEvent& event)
{
   int index;

   index = m_Selected->GetSelection();
   event.Enable(index > 0);
}
/*---------------------------------------------------------------------------*/
void wxSortDialog::OnDownClick(wxCommandEvent& event)
{
   int index;
   wxString tmp;

   index = m_Selected->GetSelection();
   tmp = m_Selected->GetString(index);
   m_Selected->Delete(index);
   index++;
   m_Selected->Insert(tmp, index);
   m_Selected->SetSelection(index);
   event.Skip();
}
/*---------------------------------------------------------------------------*/
void wxSortDialog::OnDownUpdate(wxUpdateUIEvent& event)
{
   int index;

   index = m_Selected->GetSelection();
   event.Enable((index != wxNOT_FOUND) &&
                ((unsigned int)index < m_Selected->GetCount() - 1));
}
/*---------------------------------------------------------------------------*/
void wxSortDialog::OnLastClick(wxCommandEvent& event)
{
   int index;
   wxString tmp;

   index = m_Selected->GetSelection();
   if (index != wxNOT_FOUND)
   {
      tmp = m_Selected->GetString(index);
      m_Selected->Delete(index);
      index = m_Selected->Append(tmp);
      m_Selected->SetSelection(index);
   }
   event.Skip();
}
/*---------------------------------------------------------------------------*/
void wxSortDialog::OnLastUpdate(wxUpdateUIEvent& event)
{
   int count, index;

   index = m_Selected->GetSelection();
   count = m_Selected->GetCount() - 1;
   event.Enable((index != wxNOT_FOUND)&&(index < count));
}
/*---------------------------------------------------------------------------*/
void wxSortDialog::OnRbAscSelected(wxCommandEvent& event)
{
   wxString tmp;
   int index;

   index = m_Selected->GetSelection();
   tmp = m_Selected->GetString(index).BeforeLast(_T(' '));
   m_Selected->SetString(index, tmp + _T(" ASC"));
   event.Skip();
}
/*---------------------------------------------------------------------------*/
void wxSortDialog::OnRbDescSelected(wxCommandEvent& event)
{
   wxString tmp;
   int index;

   index = m_Selected->GetSelection();
   tmp = m_Selected->GetString(index).BeforeLast(_T(' '));
   m_Selected->SetString(index, tmp + _T(" DESC"));
   event.Skip();
}
/*---------------------------------------------------------------------------*/
void wxSortDialog::OnSelectedSelected(wxCommandEvent& event)
{
   wxString tmp;

   tmp = m_Selected->GetStringSelection().AfterLast(_T(' '));

   if (tmp == _T("ASC"))
      m_Ascending->SetValue(true);
   else
      m_Descending->SetValue(true);
   event.Skip();
}
/*---------------------------------------------------------------------------*/
void wxSortDialog::OnOkClick(wxCommandEvent& event)
{
   m_StringsOrder = m_Selected->GetStrings();
   event.Skip();
}
/*---------------------------------------------------------------------------*/
void wxSortDialog::SetDatabase(wxSQLite3Database* db, const wxString& base)
{
   m_Db = db;
   m_Base = base;
}
/*---------------------------------------------------------------------------*/
void wxSortDialog::SetTable(const wxString& table)
{
   m_Table = table;
}
/*---------------------------------------------------------------------------*/
void wxSortDialog::SetStringsOrder(wxArrayString& array)
{
   if (!m_Db||!m_Db->IsOpen())
      return;

   try
   {
      wxSQLite3ResultSet tblQRY;
      wxString sql, tmp;
      int index;

      sql = wxString::Format(_T("PRAGMA %s.table_info(\"%s\");"),
                             m_Base.c_str(), m_Table.c_str());
      tblQRY = m_Db->ExecuteQuery(ToUTF8(sql));
      while (tblQRY.NextRow())
         m_Available->Append(tblQRY.GetString(1) + _T(" ASC"));

      tblQRY.Finalize();

      m_StringsOrder = array;
      for (size_t i = 0; i < m_StringsOrder.Count(); i++)
      {
         tmp = m_StringsOrder[i].BeforeLast(_T(' ')) + _T(" ASC");
         index = m_Available->FindString(tmp);
         if (index != wxNOT_FOUND)
         {
            m_Available->Delete(index);
            m_Selected->Append(m_StringsOrder[i]);
         }
      }
   }
   catch(wxSQLite3Exception& ex)
   {
      wxGetApp().ShowError(_T("SetStringsOrder"), ex);
   }
}
/*---------------------------------------------------------------------------*/
