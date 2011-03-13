/*---------------------------------------------------------------------------*/
/* Logiciel de gestion de fichier de bases de données SQLite                 */
/*---------------------------------------------------------------------------*/
/* Projet  : wxSQLitePlus                              Version  : 0.2.0.0    */
/* Fichier : dropobject.cpp                                                  */
/* Auteur  : Fred Cailleau-Lepetit                     Date     : 14/07/2007 */
/* email   : softinthebox@free.fr                      Révision : 28/01/2008 */
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
#pragma implementation "dropobject.h"
#endif

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <wx/valgen.h>
/*---------------------------------------------------------------------------*/
#include "dropobject.h"
#include "wxsqliteplusapp.h"
/*---------------------------------------------------------------------------*/
#define ID_OBJ_TYPE 15001
#define ID_OBJ_NAME 15002
/*---------------------------------------------------------------------------*/
IMPLEMENT_DYNAMIC_CLASS(wxDropObject, wxDialog)

BEGIN_EVENT_TABLE(wxDropObject, wxDialog)
   EVT_CHOICE(ID_OBJ_TYPE, wxDropObject::OnObjTypeSelected)
   EVT_BUTTON(wxID_OK, wxDropObject::OnOkClick)
END_EVENT_TABLE()
/*---------------------------------------------------------------------------*/
wxDropObject::wxDropObject()
{
   Init();
}
/*---------------------------------------------------------------------------*/
wxDropObject::wxDropObject(wxWindow* parent, wxWindowID id,
                           const wxString& caption, const wxPoint& pos,
                           const wxSize& size, long style)
{
   Init();
   Create(parent, id, caption, pos, size, style);
}
/*---------------------------------------------------------------------------*/
bool wxDropObject::Create(wxWindow* parent, wxWindowID id,
                          const wxString& caption, const wxPoint& pos,
                          const wxSize& size, long style)
{
   SetExtraStyle(wxWS_EX_BLOCK_EVENTS);
   wxDialog::Create( parent, id, caption, pos, size, style );
   
   CreateControls();
   Centre();
   return true;
}
/*---------------------------------------------------------------------------*/
wxDropObject::~wxDropObject()
{
}
/*---------------------------------------------------------------------------*/
void wxDropObject::Init()
{
   m_ChoiceObjType = NULL;
   m_TextObjName = NULL;
   m_Db = NULL;
}
/*---------------------------------------------------------------------------*/
void wxDropObject::CreateControls()
{    
   wxBoxSizer* bSizer1 = new wxBoxSizer(wxVERTICAL);
   SetSizer(bSizer1);

   wxStaticText* iStatic1 = new wxStaticText(this, wxID_STATIC,
                                             _("Object Type :"),
                                             wxDefaultPosition, wxDefaultSize, 0);
   bSizer1->Add(iStatic1, 0, wxALIGN_LEFT|wxALL, 5);

   wxArrayString m_ChoiceObjTypeStrings;
   m_ChoiceObjTypeStrings.Add(_("TABLE"));
   m_ChoiceObjTypeStrings.Add(_("VIEW"));
   m_ChoiceObjTypeStrings.Add(_("INDEX"));
   m_ChoiceObjTypeStrings.Add(_("TRIGGER"));
   m_ChoiceObjType = new wxChoice(this, ID_OBJ_TYPE, wxDefaultPosition,
                                  wxSize(200, -1), m_ChoiceObjTypeStrings, 0);
   bSizer1->Add(m_ChoiceObjType, 0, wxGROW|wxALL, 5);

   wxStaticText* iStatic2 = new wxStaticText(this, wxID_STATIC,
                                             _("Object Name :"),
                                             wxDefaultPosition, wxDefaultSize, 0);
   bSizer1->Add(iStatic2, 0, wxALIGN_LEFT|wxALL, 5);

   wxArrayString m_TextObjNameStrings;
   m_TextObjName = new wxChoice(this, ID_OBJ_NAME, wxDefaultPosition,
                                wxSize(200, -1), m_TextObjNameStrings, 0);
   bSizer1->Add(m_TextObjName, 0, wxGROW|wxALL, 5);

   bSizer1->Add(5, 5, 1, wxGROW|wxALL, 5);

   wxStdDialogButtonSizer* dBtnSizer1 = new wxStdDialogButtonSizer;

   bSizer1->Add(dBtnSizer1, 0, wxALIGN_RIGHT|wxALL, 5);
   wxButton* btnOk = new wxButton(this, wxID_OK, _("&OK"), wxDefaultPosition,
                                  wxDefaultSize, 0);
   btnOk->SetDefault();
   dBtnSizer1->AddButton(btnOk);

   wxButton* btnCancel = new wxButton(this, wxID_CANCEL, _("&Cancel"),
                                      wxDefaultPosition, wxDefaultSize, 0);
   dBtnSizer1->AddButton(btnCancel);

   dBtnSizer1->Realize();

   // Set validators
   m_ChoiceObjType->SetValidator(wxGenericValidator(& m_ObjectType));
   m_TextObjName->SetValidator(wxGenericValidator(& m_ObjectName));
}
/*---------------------------------------------------------------------------*/
bool wxDropObject::ShowToolTips()
{
   return true;
}
/*---------------------------------------------------------------------------*/
void wxDropObject::SetDatabase(wxSQLite3Database* db, const wxString& base)
{
   m_Db = db;
   m_Base = base;
}
/*---------------------------------------------------------------------------*/
void wxDropObject::OnOkClick(wxCommandEvent& event)
{
   wxString name;
   wxSQLitePlusFrame* frame;
   wxSQLiteObjectType type;
   
   name = m_TextObjName->GetStringSelection().Lower();
   type = (wxSQLiteObjectType)m_ChoiceObjType->GetSelection();
   if (type == otNone)
   {
      wxMessageBox(_("You have to select an object type."),
                   _("Error"));
      return;
   }
   if (name.IsEmpty())
   {
      wxMessageBox(_("You have to enter an object name."),
                   _("Error"));
      return;
   }
   
   frame = (wxSQLitePlusFrame*)wxGetApp().GetTopWindow();
   
   if (!frame->ExistDbObject(type, name, m_Base))
   {
      wxMessageBox(_("Object of this type with this name don't exist."),
                   _("Error"));
      return;
   }
   event.Skip();
}
/*---------------------------------------------------------------------------*/
void wxDropObject::DisableType()
{
   m_TextObjName->SetFocus();
   m_ChoiceObjType->Enable(false);
}
/*---------------------------------------------------------------------------*/
void wxDropObject::DisableName()
{
   m_TextObjName->Enable(false);
}
/*---------------------------------------------------------------------------*/
void wxDropObject::OnObjTypeSelected( wxCommandEvent& event )
{
   PopulateNameList((wxSQLiteObjectType)m_ChoiceObjType->GetSelection());
   event.Skip();
}
/*---------------------------------------------------------------------------*/
wxSQLiteObjectType wxDropObject::GetObjectType() const
{
   wxSQLitePlusFrame* frame;
   
   frame = (wxSQLitePlusFrame*)wxGetApp().GetTopWindow();
   return frame->GetObjNameType(m_ObjectType);
}
/*---------------------------------------------------------------------------*/
void wxDropObject::SetObjectType(wxSQLiteObjectType value)
{
   wxSQLitePlusFrame* frame;

   frame = (wxSQLitePlusFrame*)wxGetApp().GetTopWindow();

   m_ObjectType = frame->GetObjTypeName(value).Upper();
   PopulateNameList(value);
}
/*---------------------------------------------------------------------------*/
void wxDropObject::PopulateNameList(wxSQLiteObjectType objecttype)
{
   wxString objectname;
   wxSQLite3ResultSet tblQRY;
   wxSQLitePlusFrame* frame;

   m_TextObjName->Clear();
   if (m_Db && (objecttype != otNone))
   {
      try
      {
         frame = (wxSQLitePlusFrame*)wxGetApp().GetTopWindow();
         tblQRY = frame->GetObjNameList(objecttype, m_Base);
         while (tblQRY.NextRow())
         {
            objectname = tblQRY.GetString(0);
            m_TextObjName->Append(objectname);
         }
         tblQRY.Finalize();
      }
      catch(wxSQLite3Exception& ex)
      {
         wxGetApp().ShowError(_T("PopulateNameList"), ex);
      }
   }
}
/*---------------------------------------------------------------------------*/
