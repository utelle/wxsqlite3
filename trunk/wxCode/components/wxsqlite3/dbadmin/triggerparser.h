/*---------------------------------------------------------------------------*/
/* Logiciel de gestion de fichier de base de donnéesSQLite                   */
/*---------------------------------------------------------------------------*/
/* Projet  : wxSQLitePlus                              Version  : 0.1.0.0    */
/* Fichier : triggerparser.h                                                 */
/* Auteur  : Fred Cailleau-Lepetit                     Date     : 04/08/2007 */
/* email   : softinthebox@free.fr                      Révision : 17/08/2007 */
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
#ifndef _TRIGGERPARSER_H_
#define _TRIGGERPARSER_H_

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma interface "triggerparser.h"
#endif
/*---------------------------------------------------------------------------*/
class wxCreateTrigerParserMinimal
{
   public:
      
      wxCreateTrigerParserMinimal(const wxString& ddl);

      wxString GetEvent() const {return m_Event;}
      wxString GetColumn() const {return m_Column;}
      
   private:
      
      wxString m_Ddl;
      wxString m_Event;
      wxString m_Column;
      wxString m_CurrentToken;
      size_t m_CharPos;
      
      void Analyze();
      wxString GetNextToken();
      wxChar GetNextChar();
      void ToStartToken();
      bool CurrentCharIsBlank();
};
/*---------------------------------------------------------------------------*/
#endif   // _TRIGGERPARSER_H_
