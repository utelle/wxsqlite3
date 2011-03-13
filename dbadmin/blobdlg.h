/*---------------------------------------------------------------------------*/
/* Logiciel de gestion de fichier de base de donnéesSQLite                   */
/*---------------------------------------------------------------------------*/
/* Projet  : wxSQLitePlus                              Version  : 0.3.0.0    */
/* Fichier : blobdlg.h                                                       */
/* Auteur  : Fred Cailleau-Lepetit                     Date     : 08/03/2009 */
/* email   : softinthebox@free.fr                      Révision : 18/04/2009 */
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
#ifndef _BLOBDLG_H_
#define _BLOBDLG_H_

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma interface "blobdlg.h"
#endif
/*---------------------------------------------------------------------------*/
#include <wx/notebook.h>
/*---------------------------------------------------------------------------*/
class wxRichTextCtrl;
class wxMemoryBuffer;
/*---------------------------------------------------------------------------*/
class wxBlobDialog : public wxDialog
{
   DECLARE_DYNAMIC_CLASS(wxBlobDialog)
   DECLARE_EVENT_TABLE()

   public:

      wxBlobDialog();
      wxBlobDialog(wxWindow* parent, wxWindowID id = -1,
                   const wxString& caption = _("Blob"),
                   const wxPoint& pos = wxDefaultPosition,
                   const wxSize& size = wxSize(450, 400),
                   long style = wxDEFAULT_DIALOG_STYLE|
                                wxRESIZE_BORDER|wxTAB_TRAVERSAL);

      bool Create(wxWindow* parent, wxWindowID id = -1,
                  const wxString& caption = _("Blob"),
                  const wxPoint& pos = wxDefaultPosition,
                  const wxSize& size = wxSize(450, 400),
                  long style = wxDEFAULT_DIALOG_STYLE|
                               wxRESIZE_BORDER|wxTAB_TRAVERSAL);

      ~wxBlobDialog();

      void SetBlob(wxMemoryBuffer* buffer);

   protected:

      void Init();
      void CreateControls();

      void OnBtnSaveasClick(wxCommandEvent& event);

      static bool ShowToolTips();

   private:

      wxNotebook* m_Notebook;
      wxStaticText* m_BlobLen;
      wxTextCtrl* m_EditHexa;
      wxRichTextCtrl* m_EditText;
      wxStaticBitmap* m_Image;
      wxStaticText* m_RealSize;
      bool m_FlagBin;
      bool m_FlagBmp;

      wxString GetHexaString(wxMemoryBuffer* buffer);
      wxSize RescaleImage(int width, int height);
};
/*---------------------------------------------------------------------------*/
#endif   // _BLOBDLG_H_
