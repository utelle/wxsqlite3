/*---------------------------------------------------------------------------*/
/* Logiciel de gestion de fichier de base de donnéesSQLite                   */
/*---------------------------------------------------------------------------*/
/* Projet  : wxSQLitePlus                              Version  : 0.2.0.0    */
/* Fichier : describedlg.h                                                   */
/* Auteur  : Fred Cailleau-Lepetit                     Date     : 08/09/2007 */
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
#ifndef _DESCRIBEDLG_H_
#define _DESCRIBEDLG_H_

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma interface "describedlg.h"
#endif
/*---------------------------------------------------------------------------*/
#include <wx/wxsqlite3.h>
/*---------------------------------------------------------------------------*/
class wxSpecGrid;
/*---------------------------------------------------------------------------*/
class wxDescribeDlg: public wxDialog
{    
   DECLARE_DYNAMIC_CLASS(wxDescribeDlg)
   DECLARE_EVENT_TABLE()

   public:

      wxDescribeDlg();
      wxDescribeDlg(wxWindow* parent, wxWindowID id = -1,
                    const wxString& caption = _("Describe"),
                    const wxPoint& pos = wxDefaultPosition,
                    const wxSize& size = wxSize(600, 500),
                    long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER);

      bool Create(wxWindow* parent, wxWindowID id = -1,
                  const wxString& caption = _("Describe"),
                  const wxPoint& pos = wxDefaultPosition,
                  const wxSize& size = wxSize(600, 500),
                  long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER);

      ~wxDescribeDlg();

      void Describe(wxSQLite3Database* db, const wxString& name,
                    const wxString& base);

   protected:

      void Init();
      void CreateControls();
      static bool ShowToolTips();

   private:

      wxStaticText* m_DescribeName;
      wxSpecGrid* m_DescribeGrid;
};
/*---------------------------------------------------------------------------*/
#endif   // _DESCRIBEDLG_H_
