/*---------------------------------------------------------------------------*/
/* Logiciel de gestion de fichier de base de donnéesSQLite                   */
/*---------------------------------------------------------------------------*/
/* Projet  : wxSQLitePlus                              Version  : 0.2.3.0    */
/* Fichier : sqlparameters.h                                                 */
/* Auteur  : Fred Cailleau-Lepetit                     Date     : 14/07/2007 */
/* email   : softinthebox@free.fr                      Révision : 18/10/2008 */
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
#ifndef _SQLPARAMETERS_H_
#define _SQLPARAMETERS_H_

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma interface "sqlparameters.h"
#endif

/*---------------------------------------------------------------------------*/
#include <wx/dynarray.h>
/*---------------------------------------------------------------------------*/
#define WXSQLPARAMETERSDIALOG_STYLE wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER
/*---------------------------------------------------------------------------*/
class wxSQLParametersDialog: public wxDialog
{
   DECLARE_DYNAMIC_CLASS(wxSQLParametersDialog)

   public:

      wxSQLParametersDialog();
      wxSQLParametersDialog(wxWindow* parent, wxWindowID id = -1,
                            const wxString& caption = _("SQL Parameters"),
                            const wxPoint& pos = wxDefaultPosition,
                            const wxSize& size = wxSize(400, 250),
                            long style = WXSQLPARAMETERSDIALOG_STYLE);

      bool Create(wxWindow* parent, wxWindowID id = -1,
                  const wxString& caption = _("SQL Parameters"),
                  const wxPoint& pos = wxDefaultPosition,
                  const wxSize& size = wxSize(400, 250),
                  long style = WXSQLPARAMETERSDIALOG_STYLE);

      ~wxSQLParametersDialog();

      void AddParameter(const wxString& name, const wxString& value = wxEmptyString);
      wxString GetParameter(size_t index);

   protected:

      void Init();
      void CreateControls();

      static bool ShowToolTips();

   private:

      wxScrolledWindow* m_ScrolledWindow;
      wxFlexGridSizer* m_FlexSizer;
      wxArrayPtrVoid m_PtrArray;
};
/*---------------------------------------------------------------------------*/
#endif   // _SQLPARAMETERS_H_
