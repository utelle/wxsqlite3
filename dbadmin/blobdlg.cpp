/*---------------------------------------------------------------------------*/
/* Logiciel de gestion de fichier de bases de données SQLite                 */
/*---------------------------------------------------------------------------*/
/* Projet  : wxSQLitePlus                              Version  : 0.3.0.0    */
/* Fichier : blobdlg.cpp                                                     */
/* Auteur  : Fred Cailleau-Lepetit                     Date     : 08/03/2009 */
/* email   : softinthebox@free.fr                      Révision : 18/04/2009 */
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
#pragma implementation "blobdlg.h"
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
#include <wx/richtext/richtextctrl.h>
#include <wx/buffer.h>
#include <wx/mstream.h>
#include <wx/xpmdecod.h>
/*---------------------------------------------------------------------------*/
#include "blobdlg.h"
/*---------------------------------------------------------------------------*/
#define ID_NOTEBOOK     15110
#define ID_PANEL_INFO   15120
#define ID_TEXTCTRL3    15130
#define ID_BTN_SAVEAS   15140
#define ID_PANE_TEXT    15150
#define ID_VALUE_TEXT   15160
#define ID_PANEL_IMAGE  15170
/*---------------------------------------------------------------------------*/
IMPLEMENT_DYNAMIC_CLASS( wxBlobDialog, wxDialog )

BEGIN_EVENT_TABLE(wxBlobDialog, wxDialog)
   EVT_BUTTON(ID_BTN_SAVEAS, wxBlobDialog::OnBtnSaveasClick)
END_EVENT_TABLE()
/*---------------------------------------------------------------------------*/
wxBlobDialog::wxBlobDialog()
{
   Init();
}
/*---------------------------------------------------------------------------*/
wxBlobDialog::wxBlobDialog(wxWindow* parent, wxWindowID id,
                           const wxString& caption, const wxPoint& pos,
                           const wxSize& size, long style)
{
   Init();
   Create(parent, id, caption, pos, size, style);
}
/*---------------------------------------------------------------------------*/
bool wxBlobDialog::Create(wxWindow* parent, wxWindowID id,
                          const wxString& caption, const wxPoint& pos,
                          const wxSize& size, long style)
{
   SetExtraStyle(wxWS_EX_BLOCK_EVENTS);
   wxDialog::Create(parent, id, caption, pos, size, style);

   CreateControls();
   Centre();
   return true;
}
/*---------------------------------------------------------------------------*/
wxBlobDialog::~wxBlobDialog()
{
}
/*---------------------------------------------------------------------------*/
void wxBlobDialog::Init()
{
   m_Notebook = NULL;
   m_BlobLen = NULL;
   m_EditHexa = NULL;
   m_EditText = NULL;
   m_Image = NULL;
   m_RealSize = NULL;
   m_FlagBin = m_FlagBmp = false;
}
/*---------------------------------------------------------------------------*/
void wxBlobDialog::CreateControls()
{
   wxBoxSizer* bSizer1 = new wxBoxSizer(wxVERTICAL);
   SetSizer(bSizer1);

   m_Notebook = new wxNotebook(this, ID_NOTEBOOK, wxDefaultPosition,
                               wxDefaultSize, wxBK_BOTTOM);

   wxPanel* pnInfo = new wxPanel(m_Notebook, ID_PANEL_INFO, wxDefaultPosition,
                                 wxDefaultSize, wxSUNKEN_BORDER|wxTAB_TRAVERSAL);
   wxBoxSizer* bSizer2 = new wxBoxSizer(wxVERTICAL);
   pnInfo->SetSizer(bSizer2);

   wxBoxSizer* bSizer3 = new wxBoxSizer(wxHORIZONTAL);
   bSizer2->Add(bSizer3, 0, wxALIGN_LEFT|wxALL, 5);
   wxStaticText* sText1 = new wxStaticText(pnInfo, wxID_STATIC, _("Length: "),
                                           wxDefaultPosition, wxDefaultSize, 0);
   bSizer3->Add(sText1, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

   m_BlobLen = new wxStaticText(pnInfo, wxID_STATIC, wxEmptyString,
                                wxDefaultPosition, wxDefaultSize, 0 );
   bSizer3->Add(m_BlobLen, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

   bSizer2->Add(5, 5, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

   wxStaticText* sText2 = new wxStaticText(pnInfo, wxID_STATIC,
                                           _("First 32 bytes"),
                                           wxDefaultPosition, wxDefaultSize, 0);
   bSizer2->Add(sText2, 0, wxALIGN_LEFT|wxALL, 5);

   m_EditHexa = new wxTextCtrl(pnInfo, ID_TEXTCTRL3, wxEmptyString,
                               wxDefaultPosition, wxDefaultSize,
                               wxTE_MULTILINE|wxTE_READONLY|wxHSCROLL);
   m_EditHexa->SetFont(wxFont(10, wxTELETYPE, wxNORMAL, wxNORMAL, false,
                              wxT("Liberation Mono")));
   bSizer2->Add(m_EditHexa, 1, wxGROW|wxALL, 5);

   wxButton* btnSaveAs = new wxButton(pnInfo, ID_BTN_SAVEAS, _("Save As..."),
                                      wxDefaultPosition, wxDefaultSize, 0);
   btnSaveAs->SetName(_T("m_BtnSaveAs"));
   bSizer2->Add(btnSaveAs, 0, wxALIGN_LEFT|wxALL, 5);

   m_Notebook->AddPage(pnInfo, _("Information"));

   m_EditText = new wxRichTextCtrl(m_Notebook, ID_VALUE_TEXT, wxEmptyString,
                                   wxDefaultPosition, wxSize(100, 100),
                                   wxTE_READONLY|wxWANTS_CHARS);
   m_Notebook->AddPage(m_EditText, _("Text"));

   wxPanel* pnImage = new wxPanel(m_Notebook, ID_PANEL_IMAGE, wxDefaultPosition,
                                  wxDefaultSize, wxSUNKEN_BORDER|wxTAB_TRAVERSAL);
   wxBoxSizer* bSizer6 = new wxBoxSizer(wxVERTICAL);
   pnImage->SetSizer(bSizer6);

   bSizer6->Add(5, 5, 1, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

   m_Image = new wxStaticBitmap(pnImage, wxID_STATIC, wxNullBitmap,
                                wxDefaultPosition, wxSize(400, 250), 0);
   bSizer6->Add(m_Image, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

   bSizer6->Add(5, 5, 1, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

   m_RealSize = new wxStaticText(pnImage, wxID_STATIC, wxEmptyString,
                                 wxDefaultPosition, wxDefaultSize, 0);
   bSizer6->Add(m_RealSize, 0, wxALIGN_LEFT|wxALL, 5);

   m_Notebook->AddPage(pnImage, _("Image"));

   bSizer1->Add(m_Notebook, 1, wxGROW|wxALL, 5);

   wxStdDialogButtonSizer* btnSizer1 = new wxStdDialogButtonSizer;

   bSizer1->Add(btnSizer1, 0, wxALIGN_RIGHT|wxALL, 5);
   wxButton* btnCancel = new wxButton(this, wxID_CANCEL, _("&Cancel"),
                                      wxDefaultPosition, wxDefaultSize, 0);
   btnSizer1->AddButton(btnCancel);

   btnSizer1->Realize();
}
/*---------------------------------------------------------------------------*/
bool wxBlobDialog::ShowToolTips()
{
   return true;
}
/*---------------------------------------------------------------------------*/
void wxBlobDialog::SetBlob(wxMemoryBuffer* buffer)
{
   if (buffer)
   {
      wxImage image;
      size_t BufLen = buffer->GetDataLen();

      m_BlobLen->SetLabel(wxString::Format(_T("%u"), BufLen));
      m_EditHexa->SetValue(GetHexaString(buffer));
      wxMemoryInputStream inputStream((const char*)buffer->GetData(), BufLen);
      if (m_FlagBin == false)
      {
         m_EditText->SetValue(wxString::From8BitData((const char*)buffer->GetData(), BufLen));
         wxXPMDecoder XpmDecoder;
         if (XpmDecoder.CanRead(inputStream))
            image = XpmDecoder.ReadFile(inputStream);
      }
      else
      {
         image.LoadFile(inputStream);
      }
      if (image.IsOk())
      {
         wxSize newSize;

         m_FlagBmp = true;
         m_RealSize->SetLabel(wxString::Format(_("Real Size: %i x %i"),
                                               image.GetWidth(),
                                               image.GetHeight()));
         newSize = RescaleImage(image.GetWidth(), image.GetHeight());
         m_Image->SetBitmap(wxBitmap(image.Rescale(newSize.GetWidth(),
                                                   newSize.GetHeight())));
      }
   }
   if (!m_FlagBmp)
      m_Notebook->RemovePage(2);
   if (m_FlagBin)
      m_Notebook->RemovePage(1);
}
/*---------------------------------------------------------------------------*/
void wxBlobDialog::OnBtnSaveasClick(wxCommandEvent& event)
{
// A FINIR
   event.Skip();
}
/*---------------------------------------------------------------------------*/
wxString wxBlobDialog::GetHexaString(wxMemoryBuffer* buffer)
{
   wxString retStr, HexStr, carStr;
   size_t bLen, strLen;
   char c;

   bLen = buffer->GetDataLen();
   bLen = (bLen < 32 ? bLen : 32);
   for (size_t i = 0, count = 0; i < 4; i++)
   {
      if (count >= bLen)
         break;
      HexStr = carStr = wxEmptyString;
      for (size_t j = 0; j < 8; j++, count++)
      {
         if (count >= bLen)
            break;
         c = ((char*)buffer->GetData())[count];
         if (c < 32)
         {
            if (c == 7 || c == _T('\r') || c == _T('\n'))
               carStr += _T(" ");
            else
            {
               m_FlagBin = true;
               carStr += _T("?");
            }
         }
         else
            carStr += wxChar(c);
         HexStr += wxString::Format(_T("0x%02X "), (int)c);
      }
      // _("0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 | xxxxxxxx\n")
      strLen = HexStr.Len();
      HexStr += wxString(_T(' '), 40 - strLen);
      retStr += HexStr + _T("| ") + carStr + _T("\n");
   }

   return retStr;
}
/*---------------------------------------------------------------------------*/
wxSize wxBlobDialog::RescaleImage(int width, int height)
{
   wxSize retSize;
   const int maxWidth = 400;
   const int maxHeight = 250;
   float r1;

   if (width <= maxWidth && height <= maxHeight)
      retSize.Set(width, height);
   else
   {
      r1 = float(height) / float(width);  // Calcul du ratio de l'image
      // le ratio appliqué sur la hauteur de la fenêtre
      // rentre t'il dans la largeur ? Si oui appliquer
      if (maxWidth >= int(float(maxHeight) / r1))
         retSize.Set(int(float(maxHeight) / r1), maxHeight);
      else // Si non appliquer le ratio sur la hauteur
         retSize.Set(maxWidth, int(float(maxWidth) * r1));
   }
   return retSize;
}
/*---------------------------------------------------------------------------*/
