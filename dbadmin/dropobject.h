/*---------------------------------------------------------------------------*/
/* Logiciel de gestion de fichier de base de donnéesSQLite                   */
/*---------------------------------------------------------------------------*/
/* Projet  : wxSQLitePlus                              Version  : 0.2.0.0    */
/* Fichier : dropobject.h                                                    */
/* Auteur  : Fred Cailleau-Lepetit                     Date     : 14/07/2007 */
/* email   : softinthebox@free.fr                      Révision : 28/01/2008 */
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
#ifndef _DROPOBJECT_H_
#define _DROPOBJECT_H_

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma interface "dropobject.h"
#endif
/*---------------------------------------------------------------------------*/
#include <wx/wxsqlite3.h>
#include "sqliteplusframe.h"
/*---------------------------------------------------------------------------*/
#define WXDROPOBJECT_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX
/*---------------------------------------------------------------------------*/
class wxDropObject: public wxDialog
{    
   DECLARE_DYNAMIC_CLASS(wxDropObject)
   DECLARE_EVENT_TABLE()

   public:

      wxDropObject();
      wxDropObject(wxWindow* parent, wxWindowID id = -1,
                   const wxString& caption = _("DROP Object"),
                   const wxPoint& pos = wxDefaultPosition,
                   const wxSize& size = wxSize(250, 200),
                   long style = WXDROPOBJECT_STYLE);

      bool Create(wxWindow* parent, wxWindowID id = -1,
                  const wxString& caption = _("DROP Object"),
                  const wxPoint& pos = wxDefaultPosition,
                  const wxSize& size = wxSize(250, 200),
                  long style = WXDROPOBJECT_STYLE);

      void SetDatabase(wxSQLite3Database* db,
                       const wxString& base = wxEmptyString);
   
      void DisableType();
      void DisableName();
   
      ~wxDropObject();

      wxSQLiteObjectType GetObjectType() const;
      void SetObjectType(wxSQLiteObjectType value);
      
      wxString GetObjectName() const {return m_ObjectName;}
      void SetObjectName(wxString value) {m_ObjectName = value;}

   protected:

      void Init();
      void CreateControls();

      void OnObjTypeSelected( wxCommandEvent& event );
      void OnOkClick( wxCommandEvent& event );

      static bool ShowToolTips();

   private:
      
      wxChoice* m_ChoiceObjType;
      wxChoice* m_TextObjName;
      wxString m_ObjectType;
      wxString m_ObjectName;
      
      wxSQLite3Database* m_Db;
      wxString m_Base;
      
      void PopulateNameList(wxSQLiteObjectType objecttype);
};
/*---------------------------------------------------------------------------*/
#endif   // _DROPOBJECT_H_
