/*---------------------------------------------------------------------------*/
/* Logiciel de gestion de fichier de base de donn�esSQLite                   */
/*---------------------------------------------------------------------------*/
/* Projet  : wxSQLitePlus                              Version  : 0.2.1.0    */
/* Fichier : sqliteplusframe.h                                               */
/* Auteur  : Fred Cailleau-Lepetit                     Date     : 04/07/2007 */
/* email   : softinthebox@free.fr                      R�vision : 04/05/2008 */
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
selon les termes de la Licence Publique G�n�rale GNU publi�e par la
Free Software Foundation (version 3).

Ce programme est distribu� car potentiellement utile, mais
SANS AUCUNE GARANTIE, ni explicite ni implicite, y compris
les garanties de commercialisation ou d'adaptation dans un but
sp�cifique. Reportez-vous � la Licence Publique G�n�rale GNU
pour plus de d�tails.
*/
#ifndef _IPCFRAME_H_
#define _IPCFRAME_H_

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma interface "ipcframe.h"
#endif
/*---------------------------------------------------------------------------*/
class wxIPCFrame : public wxFrame
{
   DECLARE_DYNAMIC_CLASS(wxIPCFrame)
   DECLARE_EVENT_TABLE()

   public:

      wxIPCFrame();
      
   protected:

      // event handlers (these functions should _not_ be virtual)
      void OnLaunchClt(wxCommandEvent& event);
      
   private:

      void LaunchClient();

};
/*---------------------------------------------------------------------------*/
#endif   // _IPCFRAME_H_
