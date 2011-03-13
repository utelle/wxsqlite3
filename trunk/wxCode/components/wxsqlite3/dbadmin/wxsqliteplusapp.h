/*---------------------------------------------------------------------------*/
/* Logiciel de gestion de fichier de base de donnéesSQLite                   */
/*---------------------------------------------------------------------------*/
/* Projet  : wxSQLitePlus                              Version  : 0.2.3.0    */
/* Fichier : wxsqliteplusapp.h                                               */
/* Auteur  : Fred Cailleau-Lepetit                     Date     : 04/07/2007 */
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

#ifndef _WXSQLITEPLUSAPP_H_
#define _WXSQLITEPLUSAPP_H_

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma interface "wxsqliteplusapp.h"
#endif
/*---------------------------------------------------------------------------*/
#include <wx/wxsqlite3.h>
#include "sqliteplusdef.h"
/*---------------------------------------------------------------------------*/
class wxSingleInstanceChecker;
/*---------------------------------------------------------------------------*/
class wxSQLitePlusApp: public wxApp
{
   DECLARE_CLASS(wxSQLitePlusApp)
   DECLARE_EVENT_TABLE()

   public:

      wxSQLitePlusApp();

      void Init();
      virtual bool OnInit();
      virtual int OnExit();

      void AddHistory(const wxString& sql);
      wxSQLite3ResultSet GetStatementHistory();

      void SetParamInt(int param, int value);
      int GetParamInt(int param);
      void SetParamStr(int param, const wxString& value);
      wxString GetParamStr(int param);

      void SetSQLParameter(const wxString& param, const wxString& value);
      wxString GetSQLParameter(const wxString& param);

      wxBitmap GetBmp(int id);
      wxIcon GetIcon(int id);

      wxString GetCompanyName() const;
      wxString GetFileDescription() const;
      wxString GetFileVersion() const;
      wxString GetInternalName() const;
      wxString GetLegalCopyright() const;
      wxString GetOriginalFilename() const;

      void ShowError(const wxString& proc, wxSQLite3Exception& ex) const;

      bool CheckStatementSyntax(wxSQLite3Database* db,
                                const wxString& statement,
                                wxString& error);

      bool GetSavePosition(){return m_SavePosition;}
      bool GetSavePerspective(){return m_SavePerspective;}

      wxString GetStyleFontName(){return m_FontName;}
      int      GetStyleFontSize(){return m_FontSize;}
      bool     GetEdgeLineVisible(){return m_EdgeLineVisible;}
      bool     GetStyleFontBold(int index);
      bool     GetStyleFontItalic(int index);
      bool     GetStyleFontUnderline(int index);
      wxColour GetStyleColourFore(int index);
      wxColour GetStyleColourBack(int index);
      int      GetStyleCase(int index);
      int      GetStyleTabWidth(){return m_StyleTabWidth;}
      bool     GetStyleUseTab(){return m_StyleUseTab;}
      bool     GetStyleTabIndent(){return m_StyleTabIndent;}
      bool     GetStyleBackspaceUnindent(){return m_StyleBackspaceUnindent;}
      int      GetStyleIndentWidth(){return m_StyleIndentWidth;}
      bool     GetStyleShowLineNumber(){return m_StyleShowLineNumber;}
      wxColour GetForeLineNumber(){return m_ForeLineNumber;}
      wxColour GetBackLineNumber(){return m_BackLineNumber;}

      void SetStyleFontName(const wxString& value);
      void SetStyleFontSize(int value);
      void SetEdgeLineVisible(bool value);
      void SetStyleFontBold(int index, bool value);
      void SetStyleFontItalic(int index, bool value);
      void SetStyleFontUnderline(int index, bool value);
      void SetStyleColourFore(int index, wxColour value);
      void SetStyleColourBack(int index, wxColour value);
      void SetStyleCase(int index, int value);

      unsigned short GetService();
      void SetService(unsigned short port);

   private:

      wxSingleInstanceChecker* m_checker;
      wxSQLite3Database m_db;
      bool m_SavePosition;
      bool m_SavePerspective;
      wxString m_FontName;
      int m_FontSize;
      bool m_EdgeLineVisible;
      bool m_FontBold[STYLE_COUNT];
      bool m_FontItalic[STYLE_COUNT];
      bool m_FontUnderline[STYLE_COUNT];
      wxColour m_FontFore[STYLE_COUNT];
      wxColour m_FontBack[STYLE_COUNT];
      int m_StyleCase[STYLE_COUNT];
      int m_StyleTabWidth;
      bool m_StyleUseTab;
      bool m_StyleTabIndent;
      bool m_StyleBackspaceUnindent;
      int m_StyleIndentWidth;
      bool m_StyleShowLineNumber;
      wxColour m_ForeLineNumber;
      wxColour m_BackLineNumber;

      int QueryGetParam(const wxString& param, int defvalue);
      void QuerySetParam(const wxString& param, int value);
      wxString QueryGetParam(const wxString& param, const wxString& defvalue);
      void QuerySetParam(const wxString& param, const wxString& value);

      wxString Normalize(const wxString& str);
      unsigned long CalcCrc32(const void* pData, unsigned long uSize);
      unsigned long CalcCrc32(const wxString& str);

      void InitConfig();

      wxString GetIPCFile();

};
/*---------------------------------------------------------------------------*/
DECLARE_APP(wxSQLitePlusApp)
/*---------------------------------------------------------------------------*/
#endif   // _WXSQLITEPLUSAPP_H_
