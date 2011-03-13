/*---------------------------------------------------------------------------*/
/* Logiciel de gestion de fichier de bases de données SQLite                 */
/*---------------------------------------------------------------------------*/
/* Projet  : wxSQLitePlus                              Version  : 0.3.0.0    */
/* Fichier : wxsqliteplusapp.cpp                                             */
/* Auteur  : Fred Cailleau-Lepetit                     Date     : 04/07/2007 */
/* email   : softinthebox@free.fr                      Révision : 03/05/2009 */
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
#pragma implementation "wxsqliteplusapp.h"
#endif

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif
#include <wx/log.h>
#include <wx/filename.h>
#include <wx/image.h>
#include <wx/snglinst.h>
#include <wx/stdpaths.h>
#include <wx/fileconf.h>
/*---------------------------------------------------------------------------*/
#include "wxsqliteplusapp.h"
#include "sqliteplusframe.h"
#include "ipcframe.h"
/*---------------------------------------------------------------------------*/
#include "images/field2.xpm"
#include "images/sqlicon.xpm"
#include "images/log.xpm"
#include "images/add.xpm"
#include "images/remove.xpm"
#include "images/colup.xpm"
#include "images/coldown.xpm"
#include "images/dbnew.xpm"
#include "images/opendb.xpm"
#include "images/attachdb.xpm"
#include "images/compactdb.xpm"
#include "images/refresh.xpm"
#include "images/undo.xpm"
#include "images/redo.xpm"
#include "images/cut.xpm"
#include "images/copy.xpm"
#include "images/paste.xpm"
#include "images/clear.xpm"
#include "images/runsql.xpm"
#include "images/runscript.xpm"
#include "images/explain.xpm"
#include "images/starttransact.xpm"
#include "images/stoptransact.xpm"
#include "images/commit.xpm"
#include "images/rollback.xpm"
#include "images/autotransact.xpm"
#include "images/tablecreate.xpm"
#include "images/tabledrop.xpm"
#include "images/viewcreate.xpm"
#include "images/viewdrop.xpm"
#include "images/indexecreate.xpm"
#include "images/indexedrop.xpm"
#include "images/triggercreate.xpm"
#include "images/triggerdrop.xpm"
#include "images/database.xpm"
#include "images/field.xpm"
#include "images/indexe.xpm"
#include "images/indexe_tmp.xpm"
#include "images/indexes.xpm"
#include "images/table.xpm"
#include "images/table_tmp.xpm"
#include "images/tables.xpm"
#include "images/trigger2.xpm"
#include "images/trigger2_tmp.xpm"
#include "images/triggers2.xpm"
#include "images/view.xpm"
#include "images/view_tmp.xpm"
#include "images/views.xpm"
#include "images/rightarrow1.xpm"
#include "images/rightarrow2.xpm"
#include "images/leftarrow1.xpm"
#include "images/leftarrow2.xpm"
#include "images/logo32.xpm"
#include "images/logo128.xpm"
#include "images/power_sqlite.xpm"
#include "images/sqlhisto.xpm"

#include "images/alltoleft.xpm"
#include "images/alltoright.xpm"
#include "images/left.xpm"
#include "images/right.xpm"
#include "images/first.xpm"
#include "images/last.xpm"
#include "images/up.xpm"
#include "images/down.xpm"
#include "images/sort.xpm"
#include "images/filter.xpm"
/*---------------------------------------------------------------------------*/
unsigned long  crc32_table[256] =
{
   0x00000000, 0x77073096, 0xEE0E612C, 0x990951BA, 0x076DC419, 0x706AF48F, 0xE963A535, 0x9E6495A3,
   0x0EDB8832, 0x79DCB8A4, 0xE0D5E91E, 0x97D2D988, 0x09B64C2B, 0x7EB17CBD, 0xE7B82D07, 0x90BF1D91,
   0x1DB71064, 0x6AB020F2, 0xF3B97148, 0x84BE41DE, 0x1ADAD47D, 0x6DDDE4EB, 0xF4D4B551, 0x83D385C7,
   0x136C9856, 0x646BA8C0, 0xFD62F97A, 0x8A65C9EC, 0x14015C4F, 0x63066CD9, 0xFA0F3D63, 0x8D080DF5,
   0x3B6E20C8, 0x4C69105E, 0xD56041E4, 0xA2677172, 0x3C03E4D1, 0x4B04D447, 0xD20D85FD, 0xA50AB56B,
   0x35B5A8FA, 0x42B2986C, 0xDBBBC9D6, 0xACBCF940, 0x32D86CE3, 0x45DF5C75, 0xDCD60DCF, 0xABD13D59,
   0x26D930AC, 0x51DE003A, 0xC8D75180, 0xBFD06116, 0x21B4F4B5, 0x56B3C423, 0xCFBA9599, 0xB8BDA50F,
   0x2802B89E, 0x5F058808, 0xC60CD9B2, 0xB10BE924, 0x2F6F7C87, 0x58684C11, 0xC1611DAB, 0xB6662D3D,
   0x76DC4190, 0x01DB7106, 0x98D220BC, 0xEFD5102A, 0x71B18589, 0x06B6B51F, 0x9FBFE4A5, 0xE8B8D433,
   0x7807C9A2, 0x0F00F934, 0x9609A88E, 0xE10E9818, 0x7F6A0DBB, 0x086D3D2D, 0x91646C97, 0xE6635C01,
   0x6B6B51F4, 0x1C6C6162, 0x856530D8, 0xF262004E, 0x6C0695ED, 0x1B01A57B, 0x8208F4C1, 0xF50FC457,
   0x65B0D9C6, 0x12B7E950, 0x8BBEB8EA, 0xFCB9887C, 0x62DD1DDF, 0x15DA2D49, 0x8CD37CF3, 0xFBD44C65,
   0x4DB26158, 0x3AB551CE, 0xA3BC0074, 0xD4BB30E2, 0x4ADFA541, 0x3DD895D7, 0xA4D1C46D, 0xD3D6F4FB,
   0x4369E96A, 0x346ED9FC, 0xAD678846, 0xDA60B8D0, 0x44042D73, 0x33031DE5, 0xAA0A4C5F, 0xDD0D7CC9,
   0x5005713C, 0x270241AA, 0xBE0B1010, 0xC90C2086, 0x5768B525, 0x206F85B3, 0xB966D409, 0xCE61E49F,
   0x5EDEF90E, 0x29D9C998, 0xB0D09822, 0xC7D7A8B4, 0x59B33D17, 0x2EB40D81, 0xB7BD5C3B, 0xC0BA6CAD,
   0xEDB88320, 0x9ABFB3B6, 0x03B6E20C, 0x74B1D29A, 0xEAD54739, 0x9DD277AF, 0x04DB2615, 0x73DC1683,
   0xE3630B12, 0x94643B84, 0x0D6D6A3E, 0x7A6A5AA8, 0xE40ECF0B, 0x9309FF9D, 0x0A00AE27, 0x7D079EB1,
   0xF00F9344, 0x8708A3D2, 0x1E01F268, 0x6906C2FE, 0xF762575D, 0x806567CB, 0x196C3671, 0x6E6B06E7,
   0xFED41B76, 0x89D32BE0, 0x10DA7A5A, 0x67DD4ACC, 0xF9B9DF6F, 0x8EBEEFF9, 0x17B7BE43, 0x60B08ED5,
   0xD6D6A3E8, 0xA1D1937E, 0x38D8C2C4, 0x4FDFF252, 0xD1BB67F1, 0xA6BC5767, 0x3FB506DD, 0x48B2364B,
   0xD80D2BDA, 0xAF0A1B4C, 0x36034AF6, 0x41047A60, 0xDF60EFC3, 0xA867DF55, 0x316E8EEF, 0x4669BE79,
   0xCB61B38C, 0xBC66831A, 0x256FD2A0, 0x5268E236, 0xCC0C7795, 0xBB0B4703, 0x220216B9, 0x5505262F,
   0xC5BA3BBE, 0xB2BD0B28, 0x2BB45A92, 0x5CB36A04, 0xC2D7FFA7, 0xB5D0CF31, 0x2CD99E8B, 0x5BDEAE1D,
   0x9B64C2B0, 0xEC63F226, 0x756AA39C, 0x026D930A, 0x9C0906A9, 0xEB0E363F, 0x72076785, 0x05005713,
   0x95BF4A82, 0xE2B87A14, 0x7BB12BAE, 0x0CB61B38, 0x92D28E9B, 0xE5D5BE0D, 0x7CDCEFB7, 0x0BDBDF21,
   0x86D3D2D4, 0xF1D4E242, 0x68DDB3F8, 0x1FDA836E, 0x81BE16CD, 0xF6B9265B, 0x6FB077E1, 0x18B74777,
   0x88085AE6, 0xFF0F6A70, 0x66063BCA, 0x11010B5C, 0x8F659EFF, 0xF862AE69, 0x616BFFD3, 0x166CCF45,
   0xA00AE278, 0xD70DD2EE, 0x4E048354, 0x3903B3C2, 0xA7672661, 0xD06016F7, 0x4969474D, 0x3E6E77DB,
   0xAED16A4A, 0xD9D65ADC, 0x40DF0B66, 0x37D83BF0, 0xA9BCAE53, 0xDEBB9EC5, 0x47B2CF7F, 0x30B5FFE9,
   0xBDBDF21C, 0xCABAC28A, 0x53B39330, 0x24B4A3A6, 0xBAD03605, 0xCDD70693, 0x54DE5729, 0x23D967BF,
   0xB3667A2E, 0xC4614AB8, 0x5D681B02, 0x2A6F2B94, 0xB40BBE37, 0xC30C8EA1, 0x5A05DF1B, 0x2D02EF8D
};
/*---------------------------------------------------------------------------*/
IMPLEMENT_APP(wxSQLitePlusApp)

IMPLEMENT_CLASS(wxSQLitePlusApp, wxApp)

BEGIN_EVENT_TABLE( wxSQLitePlusApp, wxApp )

END_EVENT_TABLE()
/*---------------------------------------------------------------------------*/
wxSQLitePlusApp::wxSQLitePlusApp()
{
}
/*---------------------------------------------------------------------------*/
bool wxSQLitePlusApp::OnInit()
{
   int XPos, YPos, F_Width, F_Height, F_Maximized;

   const wxString name = wxString::Format(_T("wxSQLitePlus-%s"), wxGetUserId().c_str());
   m_checker = new wxSingleInstanceChecker(name);
   if (m_checker->IsAnotherRunning())
   {
      wxIPCFrame* frame = new wxIPCFrame;
      frame->Show(false);
      wxCommandEvent postevent(wxEVT_COMMAND_MENU_SELECTED, ID_CMD_LAUNCH_CLT);
      wxPostEvent(frame, postevent);

      return true;
   }

   Init();

   wxInitAllImageHandlers();

   if (m_SavePosition)
   {
      XPos = GetParamInt(PARAM_FRAME_XPOS);
      YPos = GetParamInt(PARAM_FRAME_YPOS);
      F_Width = GetParamInt(PARAM_FRAME_WIDTH);
      F_Height = GetParamInt(PARAM_FRAME_HEIGHT);
      F_Maximized = GetParamInt(PARAM_FRAME_MAXIMIZED);
   }
   else
   {
      XPos = YPos = F_Width = F_Height = -1;
      F_Maximized = false;
   }

   wxPoint pos(XPos, YPos);
   wxSize size(F_Width, F_Height);

   wxSQLitePlusFrame* mainWindow = new wxSQLitePlusFrame(NULL, -1,
                                                         _T("wxSQLite+"),
                                                         pos, size);
   SetTopWindow(mainWindow);
   if (F_Maximized)
      mainWindow->Maximize(true);
   mainWindow->Show(true);

   for (int i = 1; i < argc; i++)
      mainWindow->CmdOpen(argv[i]);

#ifdef DEBUG
    new wxLogWindow(mainWindow, _T("Debug"));
#endif

   return true;
}
/*---------------------------------------------------------------------------*/
int wxSQLitePlusApp::OnExit()
{
   delete m_checker;
   return wxApp::OnExit();
}
/*---------------------------------------------------------------------------*/
void wxSQLitePlusApp::AddHistory(const wxString& sql)
{
   try
   {
      wxSQLite3ResultSet hisQRY;
      unsigned long sqlCRC32;
      int sql_count;
      wxString sql1;
      wxString statement = sql;

      if (statement.Last() != _T(';'))
         statement += _T(';');
      sqlCRC32 = CalcCrc32(Normalize(statement));
      sql1 = wxString::Format(_T("SELECT id, count_use FROM history WHERE user = '%s' AND code = %lu;"),
                              wxGetUserId().c_str(), sqlCRC32);
      hisQRY = m_db.ExecuteQuery(ToUTF8(sql1));
      if (hisQRY.NextRow())
      {
         int id = hisQRY.GetInt(0);
         int count = hisQRY.GetInt(1) + 1;
         sql1 = wxString::Format(_T("UPDATE history SET count_use = %i, last_modif_date = CURRENT_TIMESTAMP WHERE id = %i;"),
                                 count, id);
      }
      else
      {
         statement.Replace(_T("'"), _T("/'/"), true);
         statement.Replace(_T("/'/"), _T("''"), true);
         sql1 = wxString::Format(_T("INSERT INTO history (user, sql, code, count_use) VALUES ('%s', '%s', %lu, 1);"),
                                 wxGetUserId().c_str(), statement.c_str(), sqlCRC32);
      }
      hisQRY.Finalize();
      m_db.ExecuteUpdate(sql1);

      sql_count = wxGetApp().GetParamInt(PARAM_SQLHISTOCOUNT);

      sql1 = _T("SELECT COUNT(*) FROM history;");
      if (m_db.ExecuteScalar(sql1) > sql_count)
      {
         sql1 = wxString::Format(_T("DELETE FROM history WHERE last_modif_date < ( SELECT MIN(last_modif_date) FROM ( SELECT last_modif_date FROM history WHERE user = '%s' ORDER BY last_modif_date DESC LIMIT 0,%i ) ) AND user = '%s';"),
                                 wxGetUserId().c_str(), sql_count, wxGetUserId().c_str());

         m_db.ExecuteUpdate(sql1);
      }
   }
   catch(wxSQLite3Exception& ex)
   {
      ShowError(_T("AddHistory"), ex);
   }
}
/*---------------------------------------------------------------------------*/
wxSQLite3ResultSet wxSQLitePlusApp::GetStatementHistory()
{
   wxSQLite3ResultSet hisQRY;
   wxString sql1;

   try
   {
      sql1 = wxString::Format(_T("SELECT  last_modif_date AS \"Date\", sql AS \"Statement\", count_use AS \"Count\" FROM history WHERE user = '%s' ORDER BY last_modif_date DESC;"),
                              wxGetUserId().c_str());
      hisQRY = m_db.ExecuteQuery(ToUTF8(sql1));
   }
   catch(wxSQLite3Exception& ex)
   {
      ShowError(_T("GetStatementHistory"), ex);
   }
   return hisQRY;
}
/*---------------------------------------------------------------------------*/
void wxSQLitePlusApp::SetParamInt(int param, int value)
{
   wxString paramname;

   switch (param)
   {
      case PARAM_FRAME_XPOS   :
         paramname = _T("Frame_XPos");
         break;
      case PARAM_FRAME_YPOS   :
         paramname = _T("Frame_YPos");
         break;
      case PARAM_FRAME_WIDTH  :
         paramname = _T("Frame_Width");
         break;
      case PARAM_FRAME_HEIGHT :
         paramname = _T("Frame_Height");
         break;
      case PARAM_FRAME_MAXIMIZED :
         paramname = _T("Frame_Maximized");
         break;
      case PARAM_AUTOTRANSACT :
         paramname = _T("Auto_Transaction");
         break;
      case PARAM_SQLHISTOCOUNT :
         paramname = _T("Sql_History_Count");
         break;
      case PARAM_SAVEWINPOSITION :
         paramname = _T("Save_Window_position");
         m_SavePosition = value != 0;
         break;
      case PARAM_SAVEWINPERSPECTIVE :
         paramname = _T("Save_Window_Perspective");
         m_SavePerspective = value != 0;
         break;
      case PARAM_STYLE_FONTSIZE :
         paramname = _T("Style Font Size");
         m_FontSize = value;
         break;
      case PARAM_STYLE_EDGELINE :
         paramname = _T("Style Edge Line");
         m_EdgeLineVisible = value != 0;
         break;
      case PARAM_ST_BOLD_DEF :
         paramname = _T("Style Font Bold Default");
         m_FontBold[STYLE_DEFAULT] = value != 0;
         break;
      case PARAM_ST_ITALIC_DEF :
         paramname = _T("Style Font Italic Default");
         m_FontItalic[STYLE_DEFAULT] = value != 0;
         break;
      case PARAM_ST_UNDER_DEF :
         paramname = _T("Style Font Underline Default");
         m_FontUnderline[STYLE_DEFAULT] = value != 0;
         break;
      case PARAM_ST_CASE_DEF :
         paramname = _T("Style Font Case Default");
         m_StyleCase[STYLE_DEFAULT] = value;
         break;
      case PARAM_ST_BOLD_COM :
         paramname = _T("Style Font Bold Comment");
         m_FontBold[STYLE_COMMENT] = value != 0;
         break;
      case PARAM_ST_ITALIC_COM :
         paramname = _T("Style Font Italic Comment");
         m_FontItalic[STYLE_COMMENT] = value != 0;
         break;
      case PARAM_ST_UNDER_COM :
         paramname = _T("Style Font Underline Comment");
         m_FontUnderline[STYLE_COMMENT] = value != 0;
         break;
      case PARAM_ST_CASE_COM :
         paramname = _T("Style Font Case Comment");
         m_StyleCase[STYLE_COMMENT] = value;
         break;
      case PARAM_ST_BOLD_COML :
         paramname = _T("Style Font Bold Comment Line");
         m_FontBold[STYLE_COMMENTLINE] = value != 0;
         break;
      case PARAM_ST_ITALIC_COML :
         paramname = _T("Style Font Italic Comment Line");
         m_FontItalic[STYLE_COMMENTLINE] = value != 0;
         break;
      case PARAM_ST_UNDER_COML :
         paramname = _T("Style Font Underline Comment Line");
         m_FontUnderline[STYLE_COMMENTLINE] = value != 0;
         break;
      case PARAM_ST_CASE_COML :
         paramname = _T("Style Font Case Comment Line");
         m_StyleCase[STYLE_COMMENTLINE] = value;
         break;
      case PARAM_ST_BOLD_NUM :
         paramname = _T("Style Font Bold Number");
         m_FontBold[STYLE_NUMBER] = value != 0;
         break;
      case PARAM_ST_ITALIC_NUM :
         paramname = _T("Style Font Italic Number");
         m_FontItalic[STYLE_NUMBER] = value != 0;
         break;
      case PARAM_ST_UNDER_NUM :
         paramname = _T("Style Font Underline Number");
         m_FontUnderline[STYLE_NUMBER] = value != 0;
         break;
      case PARAM_ST_CASE_NUM :
         paramname = _T("Style Font Case Number");
         m_StyleCase[STYLE_NUMBER] = value;
         break;
      case PARAM_ST_BOLD_KEY1 :
         paramname = _T("Style Font Bold Key 1");
         m_FontBold[STYLE_WORD1] = value != 0;
         break;
      case PARAM_ST_ITALIC_KEY1 :
         paramname = _T("Style Font Italic Key 1");
         m_FontItalic[STYLE_WORD1] = value != 0;
         break;
      case PARAM_ST_UNDER_KEY1 :
         paramname = _T("Style Font Underline Key 1");
         m_FontUnderline[STYLE_WORD1] = value != 0;
         break;
      case PARAM_ST_CASE_KEY1 :
         paramname = _T("Style Font Case Key 1");
         m_StyleCase[STYLE_WORD1] = value;
         break;
      case PARAM_ST_BOLD_STR :
         paramname = _T("Style Font Bold String");
         m_FontBold[STYLE_STRING] = value != 0;
         break;
      case PARAM_ST_ITALIC_STR :
         paramname = _T("Style Font Italic String");
         m_FontItalic[STYLE_STRING] = value != 0;
         break;
      case PARAM_ST_UNDER_STR :
         paramname = _T("Style Font Underline String");
         m_FontUnderline[STYLE_STRING] = value != 0;
         break;
      case PARAM_ST_CASE_STR :
         paramname = _T("Style Font Case String");
         m_StyleCase[STYLE_STRING] = value;
         break;
      case PARAM_ST_BOLD_CHAR :
         paramname = _T("Style Font Bold Characters");
         m_FontBold[STYLE_CHARACTER] = value != 0;
         break;
      case PARAM_ST_ITALIC_CHAR :
         paramname = _T("Style Font Italic Characters");
         m_FontItalic[STYLE_CHARACTER] = value != 0;
         break;
      case PARAM_ST_UNDER_CHAR :
         paramname = _T("Style Font Underline Characters");
         m_FontUnderline[STYLE_CHARACTER] = value != 0;
         break;
      case PARAM_ST_CASE_CHAR :
         paramname = _T("Style Font Case Characters");
         m_StyleCase[STYLE_CHARACTER] = value;
         break;
      case PARAM_ST_BOLD_OPE :
         paramname = _T("Style Font Bold Operator");
         m_FontBold[STYLE_OPERATOR] = value != 0;
         break;
      case PARAM_ST_ITALIC_OPE :
         paramname = _T("Style Font Italic Operator");
         m_FontItalic[STYLE_OPERATOR] = value != 0;
         break;
      case PARAM_ST_UNDER_OPE :
         paramname = _T("Style Font Underline Operator");
         m_FontUnderline[STYLE_OPERATOR] = value != 0;
         break;
      case PARAM_ST_CASE_OPE :
         paramname = _T("Style Font Case Operator");
         m_StyleCase[STYLE_OPERATOR] = value;
         break;
      case PARAM_ST_BOLD_IDE :
         paramname = _T("Style Font Bold Identifier");
         m_FontBold[STYLE_IDENTIFIER] = value != 0;
         break;
      case PARAM_ST_ITALIC_IDE :
         paramname = _T("Style Font Italic Identifier");
         m_FontItalic[STYLE_IDENTIFIER] = value != 0;
         break;
      case PARAM_ST_UNDER_IDE :
         paramname = _T("Style Font Underline Identifier");
         m_FontUnderline[STYLE_IDENTIFIER] = value != 0;
         break;
      case PARAM_ST_CASE_IDE :
         paramname = _T("Style Font Case Identifier");
         m_StyleCase[STYLE_IDENTIFIER] = value;
         break;
      case PARAM_ST_BOLD_KEY2 :
         paramname = _T("Style Font Bold Key 2");
         m_FontBold[STYLE_WORD2] = value != 0;
         break;
      case PARAM_ST_ITALIC_KEY2 :
         paramname = _T("Style Font Italic Key 2");
         m_FontItalic[STYLE_WORD2] = value != 0;
         break;
      case PARAM_ST_UNDER_KEY2 :
         paramname = _T("Style Font Underline Key 2");
         m_FontUnderline[STYLE_WORD2] = value != 0;
         break;
      case PARAM_ST_CASE_KEY2 :
         paramname = _T("Style Font Case Key 2");
         m_StyleCase[STYLE_WORD2] = value;
         break;
      case PARAM_ST_BOLD_KEY3 :
         paramname = _T("Style Font Bold Key 3");
         m_FontBold[STYLE_WORD3] = value != 0;
         break;
      case PARAM_ST_ITALIC_KEY3 :
         paramname = _T("Style Font Italic Key 3");
         m_FontItalic[STYLE_WORD3] = value != 0;
         break;
      case PARAM_ST_UNDER_KEY3 :
         paramname = _T("Style Font Underline Key 3");
         m_FontUnderline[STYLE_WORD3] = value != 0;
         break;
      case PARAM_ST_CASE_KEY3 :
         paramname = _T("Style Font Case Key 3");
         m_StyleCase[STYLE_WORD3] = value;
         break;
      case PARAM_ST_BOLD_KEY4 :
         paramname = _T("Style Font Bold Key 4");
         m_FontBold[STYLE_WORD4] = value != 0;
         break;
      case PARAM_ST_ITALIC_KEY4 :
         paramname = _T("Style Font Italic Key 4");
         m_FontItalic[STYLE_WORD4] = value != 0;
         break;
      case PARAM_ST_UNDER_KEY4 :
         paramname = _T("Style Font Underline Key 4");
         m_FontUnderline[STYLE_WORD4] = value != 0;
         break;
      case PARAM_ST_CASE_KEY4 :
         paramname = _T("Style Font Case Key 4");
         m_StyleCase[STYLE_WORD4] = value;
         break;
      case PARAM_ST_TAB_WIDTH :
         paramname = _T("Style Tab Width");
         m_StyleTabWidth = value;
         break;
      case PARAM_ST_USE_TAB :
         paramname = _T("Style Use Tab");
         m_StyleUseTab = value != 0;
         break;
      case PARAM_ST_TAB_INDENT :
         paramname = _T("Style Tab Indent");
         m_StyleTabIndent = value != 0;
         break;
      case PARAM_ST_BACKSP_UNINDT :
         paramname = _T("Style Backspace Unindent");
         m_StyleBackspaceUnindent = value != 0;
         break;
      case PARAM_ST_INDENT_WIDTH :
         paramname = _T("Style Indent Width");
         m_StyleIndentWidth = value;
         break;
      case PARAM_ST_SHOW_LINENUM :
         paramname = _T("Style Show Line Number");
         m_StyleShowLineNumber = value != 0;
         break;
      default : return;
   }
   QuerySetParam(paramname, value);
}
/*---------------------------------------------------------------------------*/
int wxSQLitePlusApp::GetParamInt(int param)
{
   int defvalue;
   wxString paramname;

   switch (param)
   {
      case PARAM_FRAME_XPOS   :
         paramname = _T("Frame_XPos");
         defvalue = -1;
         break;
      case PARAM_FRAME_YPOS   :
         paramname = _T("Frame_YPos");
         defvalue = -1;
         break;
      case PARAM_FRAME_WIDTH  :
         paramname = _T("Frame_Width");
         defvalue = 725;
         break;
      case PARAM_FRAME_HEIGHT :
         paramname = _T("Frame_Height");
         defvalue = 550;
         break;
      case PARAM_FRAME_MAXIMIZED :
         paramname = _T("Frame_Maximized");
         defvalue = 0;
         break;
      case PARAM_AUTOTRANSACT :
         paramname = _T("Auto_Transaction");
         defvalue = 1;
         break;
      case PARAM_SQLHISTOCOUNT :
         paramname = _T("Sql_History_Count");
         defvalue = 100;
         break;
      case PARAM_SAVEWINPOSITION :
         paramname = _T("Save_Window_position");
         defvalue = 1;
         break;
      case PARAM_SAVEWINPERSPECTIVE :
         paramname = _T("Save_Window_Perspective");
         defvalue = 1;
         break;
      case PARAM_STYLE_FONTSIZE :
         paramname = _T("Style Font Size");
         defvalue = 10;
         break;
      case PARAM_STYLE_EDGELINE :
         paramname = _T("Style Edge Line");
         defvalue = 1;
         break;
      case PARAM_ST_BOLD_DEF :
         paramname = _T("Style Font Bold Default");
         defvalue = 0;
         break;
      case PARAM_ST_ITALIC_DEF :
         paramname = _T("Style Font Italic Default");
         defvalue = 0;
         break;
      case PARAM_ST_UNDER_DEF :
         paramname = _T("Style Font Underline Default");
         defvalue = 0;
         break;
      case PARAM_ST_CASE_DEF :
         paramname = _T("Style Font Case Default");
         defvalue = 0;
         break;
      case PARAM_ST_BOLD_COM :
         paramname = _T("Style Font Bold Comment");
         defvalue = 0;
         break;
      case PARAM_ST_ITALIC_COM :
         paramname = _T("Style Font Italic Comment");
         defvalue = 1;
         break;
      case PARAM_ST_UNDER_COM :
         paramname = _T("Style Font Underline Comment");
         defvalue = 0;
         break;
      case PARAM_ST_CASE_COM :
         paramname = _T("Style Font Case Comment");
         defvalue = 0;
         break;
      case PARAM_ST_BOLD_COML :
         paramname = _T("Style Font Bold Comment Line");
         defvalue = 0;
         break;
      case PARAM_ST_ITALIC_COML :
         paramname = _T("Style Font Italic Comment Line");
         defvalue = 1;
         break;
      case PARAM_ST_UNDER_COML :
         paramname = _T("Style Font Underline Comment Line");
         defvalue = 0;
         break;
      case PARAM_ST_CASE_COML :
         paramname = _T("Style Font Case Comment Line");
         defvalue = 0;
         break;
      case PARAM_ST_BOLD_NUM :
         paramname = _T("Style Font Bold Number");
         defvalue = 0;
         break;
      case PARAM_ST_ITALIC_NUM :
         paramname = _T("Style Font Italic Number");
         defvalue = 0;
         break;
      case PARAM_ST_UNDER_NUM :
         paramname = _T("Style Font Underline Number");
         defvalue = 0;
         break;
      case PARAM_ST_CASE_NUM :
         paramname = _T("Style Font Case Number");
         defvalue = 0;
         break;
      case PARAM_ST_BOLD_KEY1 :
         paramname = _T("Style Font Bold Key 1");
         defvalue = 1;
         break;
      case PARAM_ST_ITALIC_KEY1 :
         paramname = _T("Style Font Italic Key 1");
         defvalue = 0;
         break;
      case PARAM_ST_UNDER_KEY1 :
         paramname = _T("Style Font Underline Key 1");
         defvalue = 0;
         break;
      case PARAM_ST_CASE_KEY1 :
         paramname = _T("Style Font Case Key 1");
         defvalue = 1;  // wxSTC_CASE_UPPER
         break;
      case PARAM_ST_BOLD_STR :
         paramname = _T("Style Font Bold String");
         defvalue = 0;
         break;
      case PARAM_ST_ITALIC_STR :
         paramname = _T("Style Font Italic String");
         defvalue = 0;
         break;
      case PARAM_ST_UNDER_STR :
         paramname = _T("Style Font Underline String");
         defvalue = 0;
         break;
      case PARAM_ST_CASE_STR :
         paramname = _T("Style Font Case String");
         defvalue = 0;
         break;
      case PARAM_ST_BOLD_CHAR :
         paramname = _T("Style Font Bold Characters");
         defvalue = 0;
         break;
      case PARAM_ST_ITALIC_CHAR :
         paramname = _T("Style Font Italic Characters");
         defvalue = 0;
         break;
      case PARAM_ST_UNDER_CHAR :
         paramname = _T("Style Font Underline Characters");
         defvalue = 0;
         break;
      case PARAM_ST_CASE_CHAR :
         paramname = _T("Style Font Case Characters");
         defvalue = 0;
         break;
      case PARAM_ST_BOLD_OPE :
         paramname = _T("Style Font Bold Operator");
         defvalue = 0;
         break;
      case PARAM_ST_ITALIC_OPE :
         paramname = _T("Style Font Italic Operator");
         defvalue = 0;
         break;
      case PARAM_ST_UNDER_OPE :
         paramname = _T("Style Font Underline Operator");
         defvalue = 0;
         break;
      case PARAM_ST_CASE_OPE :
         paramname = _T("Style Font Case Operator");
         defvalue = 0;
         break;
      case PARAM_ST_BOLD_IDE :
         paramname = _T("Style Font Bold Identifier");
         defvalue = 0;
         break;
      case PARAM_ST_ITALIC_IDE :
         paramname = _T("Style Font Italic Identifier");
         defvalue = 0;
         break;
      case PARAM_ST_UNDER_IDE :
         paramname = _T("Style Font Underline Identifier");
         defvalue = 0;
         break;
      case PARAM_ST_CASE_IDE :
         paramname = _T("Style Font Case Identifier");
         defvalue = 0;
         break;
      case PARAM_ST_BOLD_KEY2 :
         paramname = _T("Style Font Bold Key 2");
         defvalue = 1;
         break;
      case PARAM_ST_ITALIC_KEY2 :
         paramname = _T("Style Font Italic Key 2");
         defvalue = 0;
         break;
      case PARAM_ST_UNDER_KEY2 :
         paramname = _T("Style Font Underline Key 2");
         defvalue = 0;
         break;
      case PARAM_ST_CASE_KEY2 :
         paramname = _T("Style Font Case Key 2");
         defvalue = 0;  // wxSTC_CASE_MIXED
         break;
      case PARAM_ST_BOLD_KEY3 :
         paramname = _T("Style Font Bold Key 3");
         defvalue = 1;
         break;
      case PARAM_ST_ITALIC_KEY3 :
         paramname = _T("Style Font Italic Key 3");
         defvalue = 0;
         break;
      case PARAM_ST_UNDER_KEY3 :
         paramname = _T("Style Font Underline Key 3");
         defvalue = 0;
         break;
      case PARAM_ST_CASE_KEY3 :
         paramname = _T("Style Font Case Key 3");
         defvalue = 0;  // wxSTC_CASE_MIXED
         break;
      case PARAM_ST_BOLD_KEY4 :
         paramname = _T("Style Font Bold Key 4");
         defvalue = 1;
         break;
      case PARAM_ST_ITALIC_KEY4 :
         paramname = _T("Style Font Italic Key 4");
         defvalue = 0;
         break;
      case PARAM_ST_UNDER_KEY4 :
         paramname = _T("Style Font Underline Key 4");
         defvalue = 0;
         break;
      case PARAM_ST_CASE_KEY4 :
         paramname = _T("Style Font Case Key 4");
         defvalue = 0;  // wxSTC_CASE_MIXED
         break;
      case PARAM_ST_TAB_WIDTH :
         paramname = _T("Style Tab Width");
         defvalue = 2;
         break;
      case PARAM_ST_USE_TAB :
         paramname = _T("Style Use Tab");
         defvalue = 0;
         break;
      case PARAM_ST_TAB_INDENT :
         paramname = _T("Style Tab Indent");
         defvalue = 1;
         break;
      case PARAM_ST_BACKSP_UNINDT :
         paramname = _T("Style Backspace Unindent");
         defvalue = 1;
         break;
      case PARAM_ST_INDENT_WIDTH :
         paramname = _T("Style Indent Width");
         defvalue = 2;
         break;
      case PARAM_ST_SHOW_LINENUM :
         paramname = _T("Style Show Line Number");
         defvalue = 1;
         break;
      default : return 0;
   }
   return QueryGetParam(paramname, defvalue);
}
/*---------------------------------------------------------------------------*/
void wxSQLitePlusApp::SetParamStr(int param, const wxString& value)
{
   wxString paramname;

   switch (param)
   {
      case PARAM_FRAME_PERSPECTIVE :
         paramname = _T("Frame_Perspective");
         break;
      case PARAM_SQL_PERSPECTIVE :
         paramname = _T("Sql_Perspective");
         break;
      case PARAM_ODDROWCOLOR :
         paramname = _T("Odd_Row_Color");
         break;
      case PARAM_STYLE_FONTNAME :
         paramname = _T("Style Font Name");
         m_FontName = value;
         break;
      case PARAM_ST_FORE_DEF :
         paramname = _T("Style Foreground Default");
         m_FontFore[STYLE_DEFAULT] = value;
         break;
      case PARAM_ST_FORE_COM :
         paramname = _T("Style Foreground Comment");
         m_FontFore[STYLE_COMMENT] = value;
         break;
      case PARAM_ST_FORE_COML :
         paramname = _T("Style Foreground Comment Line");
         m_FontFore[STYLE_COMMENTLINE] = value;
         break;
      case PARAM_ST_FORE_NUM :
         paramname = _T("Style Foreground Number");
         m_FontFore[STYLE_NUMBER] = value;
         break;
      case PARAM_ST_FORE_KEY1 :
         paramname = _T("Style Foreground Key 1");
         m_FontFore[STYLE_WORD1] = value;
         break;
      case PARAM_ST_FORE_STR :
         paramname = _T("Style Foreground String");
         m_FontFore[STYLE_STRING] = value;
         break;
      case PARAM_ST_FORE_CHAR :
         paramname = _T("Style Foreground Characters");
         m_FontFore[STYLE_CHARACTER] = value;
         break;
      case PARAM_ST_FORE_OPE :
         paramname = _T("Style Foreground Operator");
         m_FontFore[STYLE_OPERATOR] = value;
         break;
      case PARAM_ST_FORE_IDE :
         paramname = _T("Style Foreground Identifier");
         m_FontFore[STYLE_IDENTIFIER] = value;
         break;
      case PARAM_ST_FORE_KEY2 :
         paramname = _T("Style Foreground Key 2");
         m_FontFore[STYLE_WORD2] = value;
         break;
      case PARAM_ST_FORE_KEY3 :
         paramname = _T("Style Foreground Key 3");
         m_FontFore[STYLE_WORD3] = value;
         break;
      case PARAM_ST_FORE_KEY4 :
         paramname = _T("Style Foreground Key 4");
         m_FontFore[STYLE_WORD4] = value;
         break;
      case PARAM_ST_BACK_DEF :
         paramname = _T("Style Background Default");
         m_FontBack[STYLE_DEFAULT] = value;
         break;
      case PARAM_ST_BACK_COM :
         paramname = _T("Style Background Comment");
         m_FontBack[STYLE_COMMENT] = value;
         break;
      case PARAM_ST_BACK_COML :
         paramname = _T("Style Background Comment Line");
         m_FontBack[STYLE_COMMENTLINE] = value;
         break;
      case PARAM_ST_BACK_NUM :
         paramname = _T("Style Background Number");
         m_FontBack[STYLE_NUMBER] = value;
         break;
      case PARAM_ST_BACK_KEY1 :
         paramname = _T("Style Background Key 1");
         m_FontBack[STYLE_WORD1] = value;
         break;
      case PARAM_ST_BACK_STR :
         paramname = _T("Style Background String");
         m_FontBack[STYLE_STRING] = value;
         break;
      case PARAM_ST_BACK_CHAR :
         paramname = _T("Style Background Characters");
         m_FontBack[STYLE_CHARACTER] = value;
         break;
      case PARAM_ST_BACK_OPE :
         paramname = _T("Style Background Operator");
         m_FontBack[STYLE_OPERATOR] = value;
         break;
      case PARAM_ST_BACK_IDE :
         paramname = _T("Style Background Identifier");
         m_FontBack[STYLE_IDENTIFIER] = value;
         break;
      case PARAM_ST_BACK_KEY2 :
         paramname = _T("Style Background Key 2");
         m_FontBack[STYLE_WORD2] = value;
         break;
      case PARAM_ST_BACK_KEY3 :
         paramname = _T("Style Background Key 3");
         m_FontBack[STYLE_WORD3] = value;
         break;
      case PARAM_ST_BACK_KEY4 :
         paramname = _T("Style Background Key 4");
         m_FontBack[STYLE_WORD4] = value;
         break;
      case PARAM_ST_FORE_LINENUM :
         paramname = _T("Style Foreground Line Number");
         m_ForeLineNumber = value;
         break;
      case PARAM_ST_BACK_LINENUM :
         paramname = _T("Style Background Line Number");
         m_BackLineNumber = value;
         break;
      default : return;
   }
   QuerySetParam(paramname, value);
}
/*---------------------------------------------------------------------------*/
wxString wxSQLitePlusApp::GetParamStr(int param)
{
   wxString paramname, defvalue;

   switch (param)
   {
      case PARAM_FRAME_PERSPECTIVE  :
         paramname = _T("Frame_Perspective");
         defvalue = wxEmptyString;
         break;
      case PARAM_SQL_PERSPECTIVE    :
         paramname = _T("Sql_Perspective");
         defvalue = wxEmptyString;
         break;
      case PARAM_ODDROWCOLOR :
         paramname = _T("Odd_Row_Color");
         defvalue = _T("#FFFFAF");
         break;
      case PARAM_STYLE_FONTNAME :
         paramname = _T("Style Font Name");
         defvalue = _T("Courier");
         break;
      case PARAM_ST_FORE_DEF :
         paramname = _T("Style Foreground Default");
         defvalue = _T("#000000");
         break;
      case PARAM_ST_FORE_COM :
         paramname = _T("Style Foreground Comment");
         defvalue = _T("#C0C0C0");
         break;
      case PARAM_ST_FORE_COML :
         paramname = _T("Style Foreground Comment Line");
         defvalue = _T("#808080");
         break;
      case PARAM_ST_FORE_NUM :
         paramname = _T("Style Foreground Number");
         defvalue = _T("#B000FF");
         break;
      case PARAM_ST_FORE_KEY1 :
         paramname = _T("Style Foreground Key 1");
         defvalue = _T("#238E23");
         break;
      case PARAM_ST_FORE_STR :
         paramname = _T("Style Foreground String");
         defvalue = _T("#0000FF");
         break;
      case PARAM_ST_FORE_CHAR :
         paramname = _T("Style Foreground Characters");
         defvalue = _T("#5F9F9F");
         break;
      case PARAM_ST_FORE_OPE :
         paramname = _T("Style Foreground Operator");
         defvalue = _T("#9F9F5F");
         break;
      case PARAM_ST_FORE_IDE :
         paramname = _T("Style Foreground Identifier");
         defvalue = _T("#0000FF");
         break;
      case PARAM_ST_FORE_KEY2 :
         paramname = _T("Style Foreground Key 2");
         defvalue = _T("#238E23");
         break;
      case PARAM_ST_FORE_KEY3 :
         paramname = _T("Style Foreground Key 3");
         defvalue = _T("#238E23");
         break;
      case PARAM_ST_FORE_KEY4 :
         paramname = _T("Style Foreground Key 4");
         defvalue = _T("#238E23");
         break;
      case PARAM_ST_BACK_DEF :
         paramname = _T("Style Background Default");
         defvalue = _T("#FFFFFF");
         break;
      case PARAM_ST_BACK_COM :
         paramname = _T("Style Background Comment");
         defvalue = _T("#FFFFFF");
         break;
      case PARAM_ST_BACK_COML :
         paramname = _T("Style Background Comment Line");
         defvalue = _T("#FFFFFF");
         break;
      case PARAM_ST_BACK_NUM :
         paramname = _T("Style Background Number");
         defvalue = _T("#FFFFFF");
         break;
      case PARAM_ST_BACK_KEY1 :
         paramname = _T("Style Background Key 1");
         defvalue = _T("#FFFFFF");
         break;
      case PARAM_ST_BACK_STR :
         paramname = _T("Style Background String");
         defvalue = _T("#FFFFFF");
         break;
      case PARAM_ST_BACK_CHAR :
         paramname = _T("Style Background Characters");
         defvalue = _T("#FFFFFF");
         break;
      case PARAM_ST_BACK_OPE :
         paramname = _T("Style Background Operator");
         defvalue = _T("#FFFFFF");
         break;
      case PARAM_ST_BACK_IDE :
         paramname = _T("Style Background Identifier");
         defvalue = _T("#FFFFFF");
         break;
      case PARAM_ST_BACK_KEY2 :
         paramname = _T("Style Background Key 2");
         defvalue = _T("#FFFFFF");
         break;
      case PARAM_ST_BACK_KEY3 :
         paramname = _T("Style Background Key 3");
         defvalue = _T("#FFFFFF");
         break;
      case PARAM_ST_BACK_KEY4 :
         paramname = _T("Style Background Key 4");
         defvalue = _T("#FFFFFF");
         break;
      case PARAM_ST_FORE_LINENUM :
         paramname = _T("Style Foreground Line Number");
         defvalue = _T("#000000");
         break;
      case PARAM_ST_BACK_LINENUM :
         paramname = _T("Style Background Line Number");
         defvalue = _T("#808080");
         break;
      default : return wxEmptyString;
   }

   return QueryGetParam(paramname, defvalue);
}
/*---------------------------------------------------------------------------*/
void wxSQLitePlusApp::SetSQLParameter(const wxString& param,
                                      const wxString& value)
{
   wxString paramname;

   paramname = _T("SQLPARAM-") + param.Mid(1).Upper();

   QuerySetParam(paramname, value);
}
/*---------------------------------------------------------------------------*/
wxString wxSQLitePlusApp::GetSQLParameter(const wxString& param)
{
   wxString paramname;

   paramname = _T("SQLPARAM-") + param.Mid(1).Upper();
   return QueryGetParam(paramname, wxEmptyString);
}
/*---------------------------------------------------------------------------*/
wxBitmap wxSQLitePlusApp::GetBmp(int id)
{
   switch (id)
   {
      case ID_BMP_ADD :
         return wxBitmap(add_xpm);
      case ID_BMP_REMOVE :
         return wxBitmap(remove_xpm);
      case ID_BMP_COLUP :
         return wxBitmap(colup_xpm);
      case ID_BMP_COLDOWN :
         return wxBitmap(coldown_xpm);
      case ID_BMP_DBNEW :
         return wxBitmap(dbnew_xpm);
      case ID_BMP_OPENDB :
         return wxBitmap(opendb_xpm);
      case ID_BMP_ATTACH :
         return wxBitmap(attachdb_xpm);
      case ID_BMP_COMPACTDB :
         return wxBitmap(compactdb_xpm);
      case ID_BMP_REFRESH :
         return wxBitmap(refresh_xpm);
      case ID_BMP_UNDO :
         return wxBitmap(undo_xpm);
      case ID_BMP_REDO :
         return wxBitmap(redo_xpm);
      case ID_BMP_CUT :
         return wxBitmap(cut_xpm);
      case ID_BMP_COPY :
         return wxBitmap(copy_xpm);
      case ID_BMP_PASTE :
         return wxBitmap(paste_xpm);
      case ID_BMP_CLEAR :
         return wxBitmap(clear_xpm);
      case ID_BMP_RUNSQL :
         return wxBitmap(runsql_xpm);
      case ID_BMP_RUNSCRIPT :
         return wxBitmap(runscript_xpm);
      case ID_BMP_EXPLAIN :
         return wxBitmap(explain_xpm);
      case ID_BMP_STARTTRANSACT :
         return wxBitmap(starttransact_xpm);
      case ID_BMP_STOPTRANSACT :
         return wxBitmap(stoptransact_xpm);
      case ID_BMP_COMMIT :
         return wxBitmap(commit_xpm);
      case ID_BMP_ROLLBACK :
         return wxBitmap(rollback_xpm);
      case ID_BMP_AUTOTRANSACT :
         return wxBitmap(autotransact_xpm);
      case ID_BMP_TABLECREATE :
         return wxBitmap(tablecreate_xpm);
      case ID_BMP_TABLEDROP :
         return wxBitmap(tabledrop_xpm);
      case ID_BMP_VIEWCREATE :
         return wxBitmap(viewcreate_xpm);
      case ID_BMP_VIEWDROP :
         return wxBitmap(viewdrop_xpm);
      case ID_BMP_INDEXECREATE :
         return wxBitmap(indexecreate_xpm);
      case ID_BMP_INDEXEDROP :
         return wxBitmap(indexedrop_xpm);
      case ID_BMP_TRIGGERCREATE :
         return wxBitmap(triggercreate_xpm);
      case ID_BMP_TRIGGERDROP :
         return wxBitmap(triggerdrop_xpm);
      case ID_BMP_INDEXE :
         return wxBitmap(indexe_xpm);
      case ID_BMP_INDEXE_TMP :
         return wxBitmap(indexe_tmp_xpm);
      case ID_BMP_INDEXES :
         return wxBitmap(indexes_xpm);
      case ID_BMP_TABLE :
         return wxBitmap(table_xpm);
      case ID_BMP_TABLE_TMP :
         return wxBitmap(table_tmp_xpm);
      case ID_BMP_TABLES :
         return wxBitmap(tables_xpm);
      case ID_BMP_TRIGGER2 :
         return wxBitmap(trigger2_xpm);
      case ID_BMP_TRIGGER2_TMP :
         return wxBitmap(trigger2_tmp_xpm);
      case ID_BMP_TRIGGERS2 :
         return wxBitmap(triggers2_xpm);
      case ID_BMP_VIEW :
         return wxBitmap(view_xpm);
      case ID_BMP_VIEW_TMP :
         return wxBitmap(view_tmp_xpm);
      case ID_BMP_VIEWS :
         return wxBitmap(views_xpm);
      case ID_BMP_LOG :
         return wxBitmap(log_xpm);
      case ID_BMP_DATABASE :
         return wxBitmap(database_xpm);
      case ID_BMP_FIELD :
         return wxBitmap(field_xpm);
      case ID_BMP_FIELD2 :
         return wxBitmap(field2_xpm);
      case ID_BMP_RIGHTARROW1 :
         return wxBitmap(rightarrow1_xpm);
      case ID_BMP_RIGHTARROW2 :
         return wxBitmap(rightarrow2_xpm);
      case ID_BMP_LEFTARROW1 :
         return wxBitmap(leftarrow1_xpm);
      case ID_BMP_LEFTARROW2 :
         return wxBitmap(leftarrow2_xpm);
      case ID_BMP_ALLTOLEFT :
         return wxBitmap(alltoleft_xpm);
      case ID_BMP_ALLTORIGHT :
         return wxBitmap(alltoright_xpm);
      case ID_BMP_LEFT :
         return wxBitmap(left_xpm);
      case ID_BMP_RIGHT :
         return wxBitmap(right_xpm);
      case ID_BMP_FIRST :
         return wxBitmap(first_xpm);
      case ID_BMP_LAST :
         return wxBitmap(last_xpm);
      case ID_BMP_UP :
         return wxBitmap(up_xpm);
      case ID_BMP_DOWN :
         return wxBitmap(down_xpm);
      case ID_BMP_FILTER :
         return wxBitmap(filter_xpm);
      case ID_BMP_SORT :
         return wxBitmap(sort_xpm);

      case ID_BMP_LOGO32 :
         return wxBitmap(logo128_xpm);
      case ID_BMP_POWEREDBYSQLITE :
         return wxBitmap(power_sqlite_xpm);
      default:
         return wxNullBitmap;
   }
}
/*---------------------------------------------------------------------------*/
wxIcon wxSQLitePlusApp::GetIcon(int id)
{
   switch (id)
   {
      case ID_ICO_INDEXE   : return wxIcon(indexe_xpm);
      case ID_ICO_SQLICON  : return wxIcon(sqlicon_xpm);
      case ID_ICO_TABLE    : return wxIcon(table_xpm);
      case ID_ICO_VIEW     : return wxIcon(view_xpm);
      case ID_ICO_TRIGGER2 : return wxIcon(trigger2_xpm);
      case ID_ICO_LOGO32   : return wxIcon(logo32_xpm);
      case ID_ICO_SQLHISTO : return wxIcon(sqlhisto_xpm);
      case ID_ICO_FIELD2   : return wxIcon(field2_xpm);
      case ID_ICO_DATABASE : return wxIcon(database_xpm);
      case ID_ICO_FILTER   : return wxIcon(filter_xpm);
      case ID_ICO_SORT     : return wxIcon(sort_xpm);

      default : return wxNullIcon;
   }
}
/*---------------------------------------------------------------------------*/
wxString wxSQLitePlusApp::GetCompanyName() const
{
   return _T("Soft In The Box");
}
/*---------------------------------------------------------------------------*/
wxString wxSQLitePlusApp::GetFileDescription() const
{
   return  _("A simple SQLite database browser.");
}
/*---------------------------------------------------------------------------*/
wxString wxSQLitePlusApp::GetFileVersion() const
{
   return  _T("0.3.0");
}
/*---------------------------------------------------------------------------*/
wxString wxSQLitePlusApp::GetInternalName() const
{
   return  _T("wxSQLite+");
}
/*---------------------------------------------------------------------------*/
wxString wxSQLitePlusApp::GetLegalCopyright() const
{
   wxString tmp;

   tmp = _T("Copyright (c) 2007-2009, Fred Cailleau-Lepetit");
#if WXSQLITE3_HAVE_CODEC
   tmp += _T("\nPart of encryption code:\nCopyright (c) 1990, RSA Data Security");
#endif
   return tmp;
}
/*---------------------------------------------------------------------------*/
wxString wxSQLitePlusApp::GetOriginalFilename() const
{
   return  _T("wxSQLitePlus.exe");
}
/*---------------------------------------------------------------------------*/
void wxSQLitePlusApp::ShowError(const wxString& proc, wxSQLite3Exception& ex) const
{
   wxString ErrStr = wxString::Format(_("Error %i-%i in %s:\n%s\n"),
                                         ex.GetErrorCode(),
                                         ex.GetExtendedErrorCode(),
                                         proc.c_str(),
                                         ex.GetMessage().c_str());
   wxMessageBox(ErrStr, _("Internal Error"));
}
/*---------------------------------------------------------------------------*/
int wxSQLitePlusApp::QueryGetParam(const wxString& param, int defvalue)
{
   wxSQLite3ResultSet paramQRY;
   wxString sql1;
   int value  = defvalue;

   try
   {
      sql1 = wxString::Format(_T("SELECT param_value FROM paramint WHERE param_name = '%s' AND user = '%s';"),
                              param.c_str(), wxGetUserId().c_str());
      paramQRY = m_db.ExecuteQuery(ToUTF8(sql1));
      if (paramQRY.NextRow())
         value = paramQRY.GetInt(0);
      paramQRY.Finalize();
   }
   catch(wxSQLite3Exception& ex)
   {
      ShowError(_T("QueryGetParam"), ex);
   }
   return value;
}
/*---------------------------------------------------------------------------*/
void wxSQLitePlusApp::QuerySetParam(const wxString& param, int value)
{
   wxString sql1;

   try
   {
      sql1 = wxString::Format(_T("SELECT COUNT(*) FROM paramint WHERE param_name = '%s' AND user = '%s';"),
                              param.c_str(), wxGetUserId().c_str());
      if (m_db.ExecuteScalar(sql1) > 0)
      {
         sql1 = wxString::Format(_T("UPDATE paramint SET param_value = %i WHERE param_name = '%s' AND user = '%s';"),
                                 value, param.c_str(), wxGetUserId().c_str());
      }
      else
      {
         sql1 = wxString::Format(_T("INSERT INTO paramint (user, param_name, param_value) VALUES ('%s', '%s', %i);"),
                                    wxGetUserId().c_str(), param.c_str(), value);
      }
      m_db.ExecuteUpdate(sql1);
   }
   catch(wxSQLite3Exception& ex)
   {
      ShowError(_T("QuerySetParam"), ex);
   }
}
/*---------------------------------------------------------------------------*/
wxString wxSQLitePlusApp::QueryGetParam(const wxString& param,
                                        const wxString& defvalue)
{
   wxSQLite3ResultSet paramQRY;
   wxString sql1;
   wxString value;

   try
   {
      sql1 = wxString::Format(_T("SELECT param_value FROM paramtext WHERE param_name = '%s' AND user = '%s';"),
                              param.c_str(), wxGetUserId().c_str());
      paramQRY = m_db.ExecuteQuery(ToUTF8(sql1));
      if (paramQRY.NextRow())
         value = paramQRY.GetString(0);
      else
         value = defvalue;
      paramQRY.Finalize();
   }
   catch(wxSQLite3Exception& ex)
   {
      ShowError(_T("QueryGetParam"), ex);
   }
   return value;
}
/*---------------------------------------------------------------------------*/
void wxSQLitePlusApp::QuerySetParam(const wxString& param,
                                    const wxString& value)
{
   wxString sql1;

   try
   {
      sql1 = wxString::Format(_T("SELECT COUNT(*) FROM paramtext WHERE param_name = '%s' AND user = '%s';"),
                              param.c_str(), wxGetUserId().c_str());
      if (m_db.ExecuteScalar(sql1) > 0)
      {
         sql1 = wxString::Format(_T("UPDATE paramtext SET param_value = '%s' WHERE param_name = '%s' AND user = '%s';"),
                                  value.c_str(), param.c_str(), wxGetUserId().c_str());
      }
      else
      {
         sql1 = wxString::Format(_T("INSERT INTO paramtext (user, param_name, param_value) VALUES ('%s', '%s', '%s');"),
                                    wxGetUserId().c_str(), param.c_str(), value.c_str());
      }
      m_db.ExecuteUpdate(sql1);
   }
   catch(wxSQLite3Exception& ex)
   {
      ShowError(_T("QuerySetParam"), ex);
   }
}
/*---------------------------------------------------------------------------*/
bool wxSQLitePlusApp::CheckStatementSyntax(wxSQLite3Database* db,
                                           const wxString& statement,
                                           wxString& error)
{
   if (!db||!db->IsOpen())
   {
      error = _("No database or database is not open.");
      return false;
   }
   // La fonction CheckSyntax utilise la fonction sqlite3_complete
   // d'après la documentation celle-ci ne vérifie pas vraiment la syntaxe
   // mais juste si l'expression est bien terminée.
   // L'utilisation de EXPLAIN permet de passer par l'analyseur
   // syntaxique et de vérifier les paramètres (nom de tables et colonnes, etc...)
   wxString tmp = _T("EXPLAIN ") + statement.Strip(wxString::both);

   try
   {
      wxSQLite3ResultSet resultSet = db->ExecuteQuery(ToUTF8(tmp));
      resultSet.Finalize();

      return true;
   }
   catch(wxSQLite3Exception& ex)
   {
      error = ex.GetMessage();
   }
   return false;
}
/*---------------------------------------------------------------------------*/
wxString wxSQLitePlusApp::Normalize(const wxString& str)
{
   wxString ret;
   wxChar c, p;

   // Cette fonction transforme les sauts de lignes en espace
   // Supprime les espaces superflus
   // Et transforme en majuscules le code SQL
   p = 0;
   for (size_t i = 0; i < str.Len(); i++)
   {
      c = str[i];
      if ((c == p)&&(c == _T(' ')))
      {  // Ne rien faire
         // le caractère précédent est un espace
         // l'espace courant est donc superflu
      }
      else if (c == _T(' ')&&(p == 0))
      {  // Le caractère courant est un espace
         // mais le caractère précédent n'était pas un espace
         ret += c;      // Ajouter l'espace
         p = _T(' ');   // Marqué comme premier espace
      }
      else if (c == _T('\n'))
      {  // Le caractère courant est un saut de ligne
         if (p != _T(' ')) // Si le caractère précédent n'est pas un espace
         {
            p = _T(' ');   // Marquer ce caractère comme un espace
            ret += p;      // Et l'ajouter
         }  // Sinon considérer comme espace superflu
      }
      else if (c == p)  // Cas ou le caractère courant est " ou '
      {  // Et " ou ' est déjà apparu (fermeture de la chaine)
         ret += c;   // Ajouter le caractère
         p = 0;      // Fermer la chaine en supprimant le flag
      }
      else if ((c == _T('\''))||(c == _T('"')))
      {  // Début de chaine par ' ou "
         ret += c;   // Ajouter le caractère courant
         p = c;      // Mettre le flag de début de chaine
      }
      else
      {  // Autre cas
         if (((p == _T(' '))&&(c != _T(' ')))||((p != _T('\''))&&(p != _T('"'))))
         {  // si un espace précédent existe mais le caractère courant
            // n'est pas un espace ou
            // le flag n'est pas marqué comme ' ni comme "
            p = 0;   // Annulation du flag espace
            c = wxToupper(c); // Mise en majuscule du caractère courant
         }
         else if (p == _T('"'))  // c'est une chaine de nom d'objet sql
            c = wxToupper(c);    // Mise en majuscule du caractère courant
         ret += c;   // Ajout du caractère courant
      }
   }
   if (ret.Last() != _T(';'))
      ret += _T(';');
   return ret;
}
/*---------------------------------------------------------------------------*/
unsigned long wxSQLitePlusApp::CalcCrc32(const void* pData, unsigned long uSize)
{
  if (!pData) return 0;
  if (uSize == 0) return 0;

  unsigned long crc32 = 0xFFFFFFFF;
  unsigned long i = 0;
  unsigned char* pChar = NULL;

  pChar = (unsigned char*)pData;

  while (i < uSize)
  {
    crc32 = (crc32 >> 8) ^ crc32_table[(crc32 & 0xFF) ^ pChar[i]];
    i++;
  }

  return (crc32 ^ 0xFFFFFFFF);
}
/*---------------------------------------------------------------------------*/
unsigned long wxSQLitePlusApp::CalcCrc32(const wxString& str)
{
   // On multiplie par la taille de wxChar pour gérer l'unicode
   return CalcCrc32(str.c_str(), str.Len() * sizeof(wxChar));
}
/*---------------------------------------------------------------------------*/
void wxSQLitePlusApp::Init()
{
   InitConfig();

   m_SavePosition = wxGetApp().GetParamInt(PARAM_SAVEWINPOSITION) != 0;
   m_SavePerspective = wxGetApp().GetParamInt(PARAM_SAVEWINPERSPECTIVE) != 0;

   // Initialiser les styles pour les editeurs
   m_FontName = wxGetApp().GetParamStr(PARAM_STYLE_FONTNAME);
   m_FontSize = wxGetApp().GetParamInt(PARAM_STYLE_FONTSIZE);
   m_EdgeLineVisible = wxGetApp().GetParamInt(PARAM_STYLE_EDGELINE) != 0;
   for (int i = STYLE_DEFAULT; i < STYLE_COUNT; i++)
   {
      m_FontBold[i] = wxGetApp().GetParamInt(PARAM_ST_BOLD_DEF + (i * 6)) != 0;
      m_FontItalic[i] = wxGetApp().GetParamInt(PARAM_ST_ITALIC_DEF + (i * 6)) != 0;
      m_FontUnderline[i] = wxGetApp().GetParamInt(PARAM_ST_UNDER_DEF + (i * 6)) != 0;
      m_FontFore[i] = wxColour(wxGetApp().GetParamStr(PARAM_ST_FORE_DEF + (i * 6)));
      m_FontBack[i] = wxColour(wxGetApp().GetParamStr(PARAM_ST_BACK_DEF + (i * 6)));
      m_StyleCase[i] = wxGetApp().GetParamInt(PARAM_ST_CASE_DEF + (i * 6));
   }

   m_StyleTabWidth = wxGetApp().GetParamInt(PARAM_ST_TAB_WIDTH);
   m_StyleUseTab = wxGetApp().GetParamInt(PARAM_ST_USE_TAB) != 0;
   m_StyleTabIndent = wxGetApp().GetParamInt(PARAM_ST_TAB_INDENT) != 0;
   m_StyleBackspaceUnindent = wxGetApp().GetParamInt(PARAM_ST_BACKSP_UNINDT) != 0;
   m_StyleIndentWidth = wxGetApp().GetParamInt(PARAM_ST_INDENT_WIDTH);
   m_StyleShowLineNumber = wxGetApp().GetParamInt(PARAM_ST_SHOW_LINENUM) != 0;
   m_ForeLineNumber = wxColour(wxGetApp().GetParamStr(PARAM_ST_FORE_LINENUM));
   m_BackLineNumber = wxColour(wxGetApp().GetParamStr(PARAM_ST_BACK_LINENUM));
}
/*---------------------------------------------------------------------------*/
void wxSQLitePlusApp::InitConfig()
{
   wxString cfgdb;
   try
   {
#ifdef __WXMSW__
      wxFileName fname(argv[0]);
      cfgdb = fname.GetPath(wxPATH_GET_VOLUME);
      cfgdb += _T("\\config.par");
#else
      cfgdb = wxFileName::GetHomeDir() + _T("/.SoftInTheBox");
      // Vérifier l'existance du chemin, sinon le créer
      if (!wxDirExists(cfgdb))
         wxMkdir(cfgdb);
      cfgdb += _T("/wxSQLitePlus");
      // Vérifier l'existance du chemin, sinon le créer
      if (!wxDirExists(cfgdb))
         wxMkdir(cfgdb);
      cfgdb += _T("/config.db");
#endif
      m_db.Open(cfgdb);
      if (!m_db.TableExists(_T("history")))
      {
         wxString sql = _T("CREATE TABLE history (id INTEGER PRIMARY KEY AUTOINCREMENT, last_modif_date DATE DEFAULT CURRENT_TIMESTAMP, user TEXT, sql TEXT, code NUMBER, count_use NUMBER);");
         m_db.ExecuteUpdate(sql);

         sql = _T("CREATE INDEX idx_hist_user_sql ON history (user ASC, sql ASC );");
         m_db.ExecuteUpdate(sql);

         sql = _T("CREATE INDEX idx_hist_user_date ON history ( user ASC, last_modif_date DESC );");
         m_db.ExecuteUpdate(sql);

      }
      if (!m_db.TableExists(_T("paramint")))
      {
         wxString sql = _T("CREATE TABLE paramint ( id INTEGER PRIMARY KEY AUTOINCREMENT, user TEXT, param_name TEXT, param_value INTEGER );");
         m_db.ExecuteUpdate(sql);

         sql = _T("CREATE UNIQUE INDEX idx_pint_user_name ON paramint ( user ASC, param_name ASC );");
         m_db.ExecuteUpdate(sql);
      }
      if (!m_db.TableExists(_T("paramtext")))
      {
         wxString sql = _T("CREATE TABLE paramtext ( id INTEGER PRIMARY KEY AUTOINCREMENT, user TEXT, param_name TEXT, param_value TEXT );");
         m_db.ExecuteUpdate(sql);

         sql = _T("CREATE UNIQUE INDEX idx_ptext_user_name ON paramtext ( user ASC, param_name ASC );");
         m_db.ExecuteUpdate(sql);

         QuerySetParam(_T("Version"), GetFileVersion());
      }
   }
   catch(wxSQLite3Exception& ex)
   {
      ShowError(_T("InitConfig"), ex);
   }
}
/*---------------------------------------------------------------------------*/
bool wxSQLitePlusApp::GetStyleFontBold(int index)
{
   if (index >= 0 && index < STYLE_COUNT)
      return m_FontBold[index];
   return false;
}
/*---------------------------------------------------------------------------*/
bool wxSQLitePlusApp::GetStyleFontItalic(int index)
{
   if (index >= 0 && index < STYLE_COUNT)
      return m_FontItalic[index];
   return false;
}
/*---------------------------------------------------------------------------*/
bool wxSQLitePlusApp::GetStyleFontUnderline(int index)
{
   if (index >= 0 && index < STYLE_COUNT)
      return m_FontUnderline[index];
   return false;
}
/*---------------------------------------------------------------------------*/
wxColour wxSQLitePlusApp::GetStyleColourFore(int index)
{
   if (index >= 0 && index < STYLE_COUNT)
      return m_FontFore[index];
   return wxColour(_T("BLACK"));
}
/*---------------------------------------------------------------------------*/
wxColour wxSQLitePlusApp::GetStyleColourBack(int index)
{
   if (index >= 0 && index < STYLE_COUNT)
      return m_FontBack[index];
   return wxColour(_T("WHITE"));
}
/*---------------------------------------------------------------------------*/
int wxSQLitePlusApp::GetStyleCase(int index)
{
   if (index >= 0 && index < STYLE_COUNT)
      return m_StyleCase[index];
   return 0; // wxSTC_CASE_MIXED
}
/*---------------------------------------------------------------------------*/
void wxSQLitePlusApp::SetStyleFontName(const wxString& value)
{
   SetParamStr(PARAM_STYLE_FONTNAME, value);
}
/*---------------------------------------------------------------------------*/
void wxSQLitePlusApp::SetStyleFontSize(int value)
{
   SetParamInt(PARAM_STYLE_FONTSIZE, value);
}
/*---------------------------------------------------------------------------*/
void wxSQLitePlusApp::SetEdgeLineVisible(bool value)
{
   SetParamInt(PARAM_STYLE_EDGELINE, (int)value);
}
/*---------------------------------------------------------------------------*/
void wxSQLitePlusApp::SetStyleFontBold(int index, bool value)
{
   int param;
   switch (index)
   {
      case STYLE_DEFAULT      : param = PARAM_ST_BOLD_DEF; break;
      case STYLE_COMMENT      : param = PARAM_ST_BOLD_COM; break;
      case STYLE_COMMENTLINE  : param = PARAM_ST_BOLD_COML; break;
      case STYLE_NUMBER       : param = PARAM_ST_BOLD_NUM; break;
      case STYLE_WORD1        : param = PARAM_ST_BOLD_KEY1; break;
      case STYLE_STRING       : param = PARAM_ST_BOLD_STR; break;
      case STYLE_CHARACTER    : param = PARAM_ST_BOLD_CHAR; break;
      case STYLE_OPERATOR     : param = PARAM_ST_BOLD_OPE; break;
      case STYLE_IDENTIFIER   : param = PARAM_ST_BOLD_IDE; break;
      case STYLE_WORD2        : param = PARAM_ST_BOLD_KEY2; break;
      case STYLE_WORD3        : param = PARAM_ST_BOLD_KEY3; break;
      case STYLE_WORD4        : param = PARAM_ST_BOLD_KEY4; break;
      default : return;
   }
   SetParamInt(param, (int)value);
}
/*---------------------------------------------------------------------------*/
void wxSQLitePlusApp::SetStyleFontItalic(int index, bool value)
{
   int param;
   switch (index)
   {
      case STYLE_DEFAULT      : param = PARAM_ST_ITALIC_DEF; break;
      case STYLE_COMMENT      : param = PARAM_ST_ITALIC_COM; break;
      case STYLE_COMMENTLINE  : param = PARAM_ST_ITALIC_COML; break;
      case STYLE_NUMBER       : param = PARAM_ST_ITALIC_NUM; break;
      case STYLE_WORD1        : param = PARAM_ST_ITALIC_KEY1; break;
      case STYLE_STRING       : param = PARAM_ST_ITALIC_STR; break;
      case STYLE_CHARACTER    : param = PARAM_ST_ITALIC_CHAR; break;
      case STYLE_OPERATOR     : param = PARAM_ST_ITALIC_OPE; break;
      case STYLE_IDENTIFIER   : param = PARAM_ST_ITALIC_IDE; break;
      case STYLE_WORD2        : param = PARAM_ST_ITALIC_KEY2; break;
      case STYLE_WORD3        : param = PARAM_ST_ITALIC_KEY3; break;
      case STYLE_WORD4        : param = PARAM_ST_ITALIC_KEY4; break;
      default : return;
   }
   SetParamInt(param, (int)value);
}
/*---------------------------------------------------------------------------*/
void wxSQLitePlusApp::SetStyleFontUnderline(int index, bool value)
{
   int param;
   switch (index)
   {
      case STYLE_DEFAULT      : param = PARAM_ST_UNDER_DEF; break;
      case STYLE_COMMENT      : param = PARAM_ST_UNDER_COM; break;
      case STYLE_COMMENTLINE  : param = PARAM_ST_UNDER_COML; break;
      case STYLE_NUMBER       : param = PARAM_ST_UNDER_NUM; break;
      case STYLE_WORD1        : param = PARAM_ST_UNDER_KEY1; break;
      case STYLE_STRING       : param = PARAM_ST_UNDER_STR; break;
      case STYLE_CHARACTER    : param = PARAM_ST_UNDER_CHAR; break;
      case STYLE_OPERATOR     : param = PARAM_ST_UNDER_OPE; break;
      case STYLE_IDENTIFIER   : param = PARAM_ST_UNDER_IDE; break;
      case STYLE_WORD2        : param = PARAM_ST_UNDER_KEY2; break;
      case STYLE_WORD3        : param = PARAM_ST_UNDER_KEY3; break;
      case STYLE_WORD4        : param = PARAM_ST_UNDER_KEY4; break;
      default : return;
   }
   SetParamInt(param, (int)value);
}
/*---------------------------------------------------------------------------*/
void wxSQLitePlusApp::SetStyleColourFore(int index, wxColour value)
{
   int param;
   switch (index)
   {
      case STYLE_DEFAULT      : param = PARAM_ST_FORE_DEF; break;
      case STYLE_COMMENT      : param = PARAM_ST_FORE_COM; break;
      case STYLE_COMMENTLINE  : param = PARAM_ST_FORE_COML; break;
      case STYLE_NUMBER       : param = PARAM_ST_FORE_NUM; break;
      case STYLE_WORD1        : param = PARAM_ST_FORE_KEY1; break;
      case STYLE_STRING       : param = PARAM_ST_FORE_STR; break;
      case STYLE_CHARACTER    : param = PARAM_ST_FORE_CHAR; break;
      case STYLE_OPERATOR     : param = PARAM_ST_FORE_OPE; break;
      case STYLE_IDENTIFIER   : param = PARAM_ST_FORE_IDE; break;
      case STYLE_WORD2        : param = PARAM_ST_FORE_KEY2; break;
      case STYLE_WORD3        : param = PARAM_ST_FORE_KEY3; break;
      case STYLE_WORD4        : param = PARAM_ST_FORE_KEY4; break;
      default : return;
   }
   SetParamStr(param, value.GetAsString(wxC2S_HTML_SYNTAX));
}
/*---------------------------------------------------------------------------*/
void wxSQLitePlusApp::SetStyleColourBack(int index, wxColour value)
{
   int param;
   switch (index)
   {
      case STYLE_DEFAULT      : param = PARAM_ST_BACK_DEF; break;
      case STYLE_COMMENT      : param = PARAM_ST_BACK_COM; break;
      case STYLE_COMMENTLINE  : param = PARAM_ST_BACK_COML; break;
      case STYLE_NUMBER       : param = PARAM_ST_BACK_NUM; break;
      case STYLE_WORD1        : param = PARAM_ST_BACK_KEY1; break;
      case STYLE_STRING       : param = PARAM_ST_BACK_STR; break;
      case STYLE_CHARACTER    : param = PARAM_ST_BACK_CHAR; break;
      case STYLE_OPERATOR     : param = PARAM_ST_BACK_OPE; break;
      case STYLE_IDENTIFIER   : param = PARAM_ST_BACK_IDE; break;
      case STYLE_WORD2        : param = PARAM_ST_BACK_KEY2; break;
      case STYLE_WORD3        : param = PARAM_ST_BACK_KEY3; break;
      case STYLE_WORD4        : param = PARAM_ST_BACK_KEY4; break;
      default : return;
   }
   SetParamStr(param, value.GetAsString(wxC2S_HTML_SYNTAX));
}
/*---------------------------------------------------------------------------*/
void wxSQLitePlusApp::SetStyleCase(int index, int value)
{
   int param;
   switch (index)
   {
      case STYLE_DEFAULT      : param = PARAM_ST_CASE_DEF; break;
      case STYLE_COMMENT      : param = PARAM_ST_CASE_COM; break;
      case STYLE_COMMENTLINE  : param = PARAM_ST_CASE_COML; break;
      case STYLE_NUMBER       : param = PARAM_ST_CASE_NUM; break;
      case STYLE_WORD1        : param = PARAM_ST_CASE_KEY1; break;
      case STYLE_STRING       : param = PARAM_ST_CASE_STR; break;
      case STYLE_CHARACTER    : param = PARAM_ST_CASE_CHAR; break;
      case STYLE_OPERATOR     : param = PARAM_ST_CASE_OPE; break;
      case STYLE_IDENTIFIER   : param = PARAM_ST_CASE_IDE; break;
      case STYLE_WORD2        : param = PARAM_ST_CASE_KEY2; break;
      case STYLE_WORD3        : param = PARAM_ST_CASE_KEY3; break;
      case STYLE_WORD4        : param = PARAM_ST_CASE_KEY4; break;
      default : return;
   }
   SetParamInt(param, value);
}
/*---------------------------------------------------------------------------*/
unsigned short wxSQLitePlusApp::GetService()
{
   long Service;

   wxFileConfig IPCConfigFile(wxEmptyString, wxEmptyString, GetIPCFile());

   IPCConfigFile.Read(_T("Service"), &Service, 0);

   return (unsigned short)Service;
}
/*---------------------------------------------------------------------------*/
void wxSQLitePlusApp::SetService(unsigned short port)
{
   wxFileConfig IPCConfigFile(wxEmptyString, wxEmptyString, GetIPCFile());

   IPCConfigFile.Write(_T("Service"), (long)port);
}
/*---------------------------------------------------------------------------*/
wxString wxSQLitePlusApp::GetIPCFile()
{
   wxStandardPathsBase& stdp = wxStandardPaths::Get();

   if (!wxDirExists(stdp.GetUserLocalDataDir()))
   {
      if (!wxMkdir(stdp.GetUserLocalDataDir()))
         return wxEmptyString;
   }
   return stdp.GetUserLocalDataDir() + wxFileName::GetPathSeparator() + _T("ipc.cfg");
}
/*---------------------------------------------------------------------------*/
