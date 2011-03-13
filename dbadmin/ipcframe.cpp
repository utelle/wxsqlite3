/*---------------------------------------------------------------------------*/
/* Logiciel de gestion de fichier de bases de données SQLite                 */
/*---------------------------------------------------------------------------*/
/* Projet  : wxSQLitePlus                              Version  : 0.2.1.0    */
/* Fichier : ipcframe.cpp                                                    */
/* Auteur  : Fred Cailleau-Lepetit                     Date     : 02/05/2008 */
/* email   : softinthebox@free.fr                      Révision : 04/05/2008 */
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
#pragma implementation "ipcframe.h"
#endif

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <wx/frame.h>
#include <wx/socket.h>
/*---------------------------------------------------------------------------*/
#include "ipcframe.h"
#include "wxsqliteplusapp.h"
/*---------------------------------------------------------------------------*/
IMPLEMENT_DYNAMIC_CLASS(wxIPCFrame, wxFrame)

BEGIN_EVENT_TABLE(wxIPCFrame, wxFrame)
   EVT_MENU(ID_CMD_LAUNCH_CLT, wxIPCFrame::OnLaunchClt)
END_EVENT_TABLE()
/*---------------------------------------------------------------------------*/
wxIPCFrame::wxIPCFrame() : wxFrame()
{
}
/*---------------------------------------------------------------------------*/
void wxIPCFrame::OnLaunchClt(wxCommandEvent& event)
{
  wxUnusedVar(event);
   LaunchClient();
   Close(true);
}
/*---------------------------------------------------------------------------*/
void wxIPCFrame::LaunchClient()
{
   const wxChar *msg1;
   size_t len;
   wxString message;
   wxSocketClient Client;
   wxIPV4address addr;

   // Création du client
   addr.Hostname(_T("127.0.0.1"));
   addr.Service(wxGetApp().GetService());

   Client.Connect(addr, false);
   Client.WaitOnConnect(10);

   if (Client.IsConnected())
   {
      for (int i = 1; i < wxGetApp().argc; i++)
      {
         message.Printf(_("%s %s"), IPC_VERB_OPEN, wxGetApp().argv[i]);
         msg1 = message.c_str();
         len  = (wxStrlen(msg1) + 1) * sizeof(wxChar);
         Client.WriteMsg(msg1, len);
         // wxLogMessage(_T("%s %u"), msg1, len);
      }
      message = IPC_VERB_SHOW;
      msg1 = message.c_str();
      len  = (wxStrlen(msg1) + 1) * sizeof(wxChar);

      Client.WriteMsg(msg1, len);
   }
   Client.Close();
}
/*---------------------------------------------------------------------------*/
