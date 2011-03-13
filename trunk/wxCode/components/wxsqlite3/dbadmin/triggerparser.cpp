/*---------------------------------------------------------------------------*/
/* Logiciel de gestion de fichier de bases de données SQLite                 */
/*---------------------------------------------------------------------------*/
/* Projet  : wxSQLitePlus                              Version  : 0.1.0.0    */
/* Fichier : triggerparser.cpp                                               */
/* Auteur  : Fred Cailleau-Lepetit                     Date     : 04/08/2007 */
/* email   : softinthebox@free.fr                      Révision : 17/08/2007 */
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
#pragma implementation "triggerparser.h"
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
#include "triggerparser.h"
/*---------------------------------------------------------------------------*/
wxCreateTrigerParserMinimal::wxCreateTrigerParserMinimal(const wxString& ddl)
{
   m_Ddl = ddl;
   m_CharPos = 0;
   Analyze();
}
/*---------------------------------------------------------------------------*/
void wxCreateTrigerParserMinimal::Analyze()
{
   wxString token, afterbefore;
   
   token = GetNextToken().Upper();

   if (token == _T("CREATE"))
   {
      token = GetNextToken().Upper();
      if (token == _T("TEMP")||token == _T("TEMPORARY"))
         token = GetNextToken().Upper();
      if (token == _T("TRIGGER"))
      {
         token = GetNextToken().Upper();
         if (token == _T("IF"))
         {
            token = GetNextToken().Upper();
            if (token == _T("NOT"))
            {
               token = GetNextToken().Upper();
               if (token == _T("EXISTS"))
                  token = GetNextToken().Upper();
               else
                  return;
            }
            else
               return;
            // Get The Trigger Name
            token = GetNextToken();
         }
         token = GetNextToken().Upper();
         if (token == _T("BEFORE")||token == _T("AFTER"))
         {
            m_Event = token + _T(" ");
            token = GetNextToken().Upper();
         }
         m_Event += token;
         if (token == _T("UPDATE"))
         {
            token = GetNextToken().Upper();
            if (token == _T("OF"))
            {
               m_Event += _T(" OF");
               m_Column = GetNextToken();
            }
         }
         else if (token == _T("INSTEAD"))
         {
            token = GetNextToken().Upper();
            if (token == _T("OF"))
            {
               m_Event = _T("INSTEAD OF");
               token = GetNextToken().Upper();
               m_Column = token;
               if (token == _T("UPDATE"))
               {
                  token = GetNextToken().Upper();
                  if (token == _T("OF"))
                  {
                     m_Column += _T(" OF ");
                     m_Column += GetNextToken();
                  }
               }
            }
         }
      }
   }
/*
sql-statement ::= CREATE [TEMP | TEMPORARY] TRIGGER [IF NOT EXISTS] trigger-name [ BEFORE | AFTER ]
database-event ON [database-name .] table-name
trigger-action
sql-statement ::= CREATE [TEMP | TEMPORARY] TRIGGER [IF NOT EXISTS] trigger-name INSTEAD OF
database-event ON [database-name .] view-name
trigger-action
database-event ::= DELETE | INSERT | UPDATE | UPDATE OF column-list
*/
}
/*---------------------------------------------------------------------------*/
wxString wxCreateTrigerParserMinimal::GetNextToken()
{
   wxChar c, cm;
   
   m_CurrentToken = wxEmptyString;
   ToStartToken();

   c = m_Ddl[m_CharPos];
   if (c == _T('\'')||c == _T('\"'))
   {
      cm = c;
      m_CurrentToken += GetNextChar();
      c = m_Ddl[m_CharPos];
      while (c != cm)
      {
         m_CurrentToken += GetNextChar();
         c = m_Ddl[m_CharPos];
      }
      m_CurrentToken += GetNextChar();
   }
   else
   {
      while (!CurrentCharIsBlank())
         m_CurrentToken += GetNextChar();
   }
   return m_CurrentToken;
}
/*---------------------------------------------------------------------------*/
wxChar wxCreateTrigerParserMinimal::GetNextChar()
{
   if (m_CharPos < m_Ddl.Length())
      return m_Ddl[m_CharPos++];
   return wxChar(0);
}
/*---------------------------------------------------------------------------*/
void wxCreateTrigerParserMinimal::ToStartToken()
{
   wxChar c;
   size_t l;
   
   l = m_Ddl.Length();
   c = m_Ddl[m_CharPos];
   while (CurrentCharIsBlank() && m_CharPos < l)
      c = m_Ddl[++m_CharPos];
}
/*---------------------------------------------------------------------------*/
bool wxCreateTrigerParserMinimal::CurrentCharIsBlank()
{
   wxChar c;
   c = m_Ddl[m_CharPos];

   return (c == _T(' ') || c == _T('\t') || c == _T('\r') || c == _T('\n'));
}
/*---------------------------------------------------------------------------*/
