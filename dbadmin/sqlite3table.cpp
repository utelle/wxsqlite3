/*---------------------------------------------------------------------------*/
/* Logiciel de gestion de fichier de bases de données SQLite                 */
/*---------------------------------------------------------------------------*/
/* Projet  : wxSQLitePlus                              Version  : 0.3.0.0    */
/* Fichier : sqlite3table.cpp                                                */
/* Auteur  : Fred Cailleau-Lepetit                     Date     : 29/06/2007 */
/* email   : softinthebox@free.fr                      Révision : 07/03/2009 */
/*---------------------------------------------------------------------------*/
/* Copyright (C) Fred Cailleau-Lepetit 2007-2008                             */
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
#pragma implementation "sqlite3table.h"
#endif

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif
#include <wx/arrimpl.cpp>
/*---------------------------------------------------------------------------*/
#include "sqlite3table.h"
#include "triggerparser.h"
#include "wxsqliteplusapp.h"
#include "specgrid.h"
/*---------------------------------------------------------------------------*/
#define wxGRID_VALUE_BLOB     _T("blob")
/*---------------------------------------------------------------------------*/
wxGridEmptyTable g_EmptyTable;
wxString g_NullValString(_T("(null)"));
/*---------------------------------------------------------------------------*/
// wxSQLite3TableColumn
/*---------------------------------------------------------------------------*/
class wxSQLite3TableColumn
{
   public:

      wxSQLite3TableColumn(){m_ShowNull = true;}
      virtual ~wxSQLite3TableColumn(){}

      virtual void AddValue(wxSQLite3ResultSet& WXUNUSED(resultSet), int WXUNUSED(columnIndex)){}
      virtual void AddValue(const wxString& WXUNUSED(value)){}
      virtual void AddValue(long WXUNUSED(value)){}
      virtual void AddValue(double WXUNUSED(value)){}

      wxString GetLabelValue(){return m_Label;}
      void SetLabelValue(const wxString& value){m_Label = value;}
      int GetSize();

      virtual wxString GetType() const {return wxEmptyString;}

      virtual wxString GetString(int WXUNUSED(row))
      {
         return wxEmptyString;
      }

      virtual bool GetBool(int WXUNUSED(row))
      {
         return false;
      }

      bool IsNull(int row)
      {
         return (m_nullValues.Item(row) == 0);
      }

      bool GetShowNull(){return m_ShowNull;}
      void SetShowNull(bool value){m_ShowNull = value;}

      wxString GetNullString()
      {
         if (m_ShowNull)
            return g_NullValString;
         else
            return wxEmptyString;
      }

   protected:

      wxArrayInt m_nullValues;

   private:

      bool m_ShowNull;
      wxString m_Label;
};
/*---------------------------------------------------------------------------*/
int wxSQLite3TableColumn::GetSize()
{
   int m_Size;

   if (GetType() == wxGRID_VALUE_STRING)
      m_Size = 24;
   else if (GetType() == wxGRID_VALUE_BOOL)
      m_Size = 5;
   else if (GetType() == wxGRID_VALUE_NUMBER)   // 4 000 000 000
      m_Size = 10;
   else if (GetType() == wxGRID_VALUE_FLOAT)
      m_Size = 12;
   else if (GetType() == wxGRID_VALUE_CHOICE)
      m_Size = 28;
   else if (GetType() == wxGRID_VALUE_BLOB)
      m_Size = 8;
   else
      m_Size = 0;
   return m_Size;
}
/*---------------------------------------------------------------------------*/
// wxSQLite3TableStringColumn
/*---------------------------------------------------------------------------*/
class wxSQLite3TableStringColumn : public wxSQLite3TableColumn
{
   public:

      virtual void AddValue(wxSQLite3ResultSet& resultSet, int columnIndex)
      {
         if (resultSet.IsNull(columnIndex))
            m_nullValues.Add(0);
         else
            m_nullValues.Add(1);

         m_Array.Add(resultSet.GetString(columnIndex));
      }
      virtual void AddValue(const wxString& value)
      {
         m_nullValues.Add(1);
         m_Array.Add(value);
      }

      virtual wxString GetType() const {return wxGRID_VALUE_STRING;}

      virtual wxString GetString(int row)
      {
         if (row >= 0)
         {
            if (m_nullValues.Item(row) == 0)
               return GetNullString();
            return m_Array.Item(row);
         }
         return wxEmptyString;
      }

   private:

      wxArrayString m_Array;
};
/*---------------------------------------------------------------------------*/
// wxSQLite3TableLongColumn
/*---------------------------------------------------------------------------*/
class wxSQLite3TableLongColumn : public wxSQLite3TableColumn
{
   public:

      virtual void AddValue(wxSQLite3ResultSet& resultSet, int columnIndex)
      {
         if (resultSet.IsNull(columnIndex))
            m_nullValues.Add(0);
         else
            m_nullValues.Add(1);

         m_Array.Add(resultSet.GetInt(columnIndex));
      }
      virtual void AddValue(long value)
      {
         m_nullValues.Add(1);
         m_Array.Add(value);
      }

      virtual wxString GetType(){return wxGRID_VALUE_NUMBER;}

      virtual wxString GetString(int row)
      {
         if (row >= 0)
         {
            if (m_nullValues.Item(row) == 0)
               return GetNullString();
            return wxString::Format(_("%li"), m_Array.Item(row));
         }
         return wxEmptyString;
      }

      virtual bool GetBool(int row)
      {
         if (row >= 0)
            return m_Array.Item(row) != 0;
         return false;
      }

   private:

      wxArrayLong m_Array;
};
/*---------------------------------------------------------------------------*/
// wxSQLite3TableDoubleColumn
/*---------------------------------------------------------------------------*/
class wxSQLite3TableDoubleColumn : public wxSQLite3TableColumn
{
   public:

      virtual void AddValue(wxSQLite3ResultSet& resultSet, int columnIndex)
      {
         if (resultSet.IsNull(columnIndex))
            m_nullValues.Add(0);
         else
            m_nullValues.Add(1);

         m_Array.Add(resultSet.GetDouble(columnIndex));
      }
      virtual void AddValue(double value)
      {
         m_nullValues.Add(1);
         m_Array.Add(value);
      }

      virtual wxString GetString(int row)
      {
         if (row >= 0)
         {
            if (m_nullValues.Item(row) == 0)
               return GetNullString();
            return wxString::Format(_("%g"), m_Array.Item(row));
         }
         return wxEmptyString;
      }
      virtual wxString GetType()const {return wxGRID_VALUE_FLOAT;}

      virtual bool GetBool(int row)
      {
         if (row >= 0)
            return m_Array.Item(row) != 0;
         return false;
      }

   private:

      wxArrayDouble m_Array;
};
/*---------------------------------------------------------------------------*/
// wxSQLite3TableBlobColumn
/*---------------------------------------------------------------------------*/
WX_DECLARE_OBJARRAY(wxMemoryBuffer, wxArrayOfBlob);
WX_DEFINE_OBJARRAY(wxArrayOfBlob);
/*---------------------------------------------------------------------------*/
class wxSQLite3TableBlobColumn : public wxSQLite3TableColumn
{
   public:

      ~wxSQLite3TableBlobColumn()
      {
         m_BlobArray.Clear();
      }

      virtual void AddValue(wxSQLite3ResultSet& resultSet, int columnIndex)
      {
         if (resultSet.IsNull(columnIndex))
         {
            m_nullValues.Add(0);
            m_BlobArray.Add(NULL);
         }
         else
         {
            wxMemoryBuffer* memBuf = new  wxMemoryBuffer;
            m_nullValues.Add(1);
            resultSet.GetBlob(columnIndex, *memBuf);
            m_BlobArray.Add(memBuf);
         }
     }
      virtual void AddValue(const wxString& value)
      {
         size_t sizeUsed;
         wxMemoryBuffer* memBuf = new wxMemoryBuffer;

#if wxCHECK_VERSION(2,9,0)
         const wxScopedCharBuffer utf8value = value.utf8_str();
         sizeUsed = value.Len() * utf8value.length();
         memBuf->SetBufSize(sizeUsed + 1);
         memBuf->AppendData((const char*)utf8value, sizeUsed);
#else
         sizeUsed = value.Len() * sizeof(wxChar);
         memBuf->SetBufSize(sizeUsed + 1);
         memBuf->AppendData((void*)value.GetData(), sizeUsed);
#endif
         memBuf->AppendByte(0);

         m_nullValues.Add(1);
         m_BlobArray.Add(memBuf);
      }

      virtual wxString GetType() const {return wxGRID_VALUE_BLOB;}

      virtual wxString GetString(int row)
      {
         if (row >= 0)
         {
            if (m_nullValues.Item(row) == 0)
               return GetNullString();
            return _T("(blob)");
         }
         return wxEmptyString;
      }

      wxMemoryBuffer* GetBuffer(size_t index)
      {
         if (index < m_BlobArray.Count())
            return &m_BlobArray[index];
         return NULL;
      }

   private:

      wxArrayOfBlob m_BlobArray;

};
/*---------------------------------------------------------------------------*/
// OddRowsGridCellAttrProvider
/*---------------------------------------------------------------------------*/
OddRowsGridCellAttrProvider::OddRowsGridCellAttrProvider(wxColour colour)
{
   m_attrForOddRows = new wxGridCellAttr;
   m_OddColour = colour;
   m_attrForOddRows->SetBackgroundColour(m_OddColour);
}
/*---------------------------------------------------------------------------*/
OddRowsGridCellAttrProvider::~OddRowsGridCellAttrProvider()
{
   m_attrForOddRows->DecRef();
}
/*---------------------------------------------------------------------------*/
wxGridCellAttr* OddRowsGridCellAttrProvider::GetAttr(int row, int col,
                                                     wxGridCellAttr::wxAttrKind  kind) const
{
   wxGridCellAttr *attr = wxGridCellAttrProvider::GetAttr(row, col, kind);

   if (row % 2)
   {
      if ( !attr )
      {
         attr = m_attrForOddRows;
         attr->IncRef();
      }
      else
      {
         if (!attr->HasBackgroundColour())
         {
            wxGridCellAttr *attrNew = attr->Clone();
            attr->DecRef();
            attr = attrNew;
            attr->SetBackgroundColour(m_OddColour);
         }
      }
   }

   return attr;
}
/*---------------------------------------------------------------------------*/
// wxGridSQLite3TableBase
/*---------------------------------------------------------------------------*/
wxGridSQLite3TableBase::wxGridSQLite3TableBase()
{
   Init();
}
/*---------------------------------------------------------------------------*/
wxGridSQLite3TableBase::~wxGridSQLite3TableBase()
{
   WX_CLEAR_ARRAY(m_ArrayColumn)
}
/*---------------------------------------------------------------------------*/
bool wxGridSQLite3TableBase::IsEmptyCell(int row, int col)
{
   if (m_ArrayColumn[col]->IsNull(row))
      return true;
   return false;
}
/*---------------------------------------------------------------------------*/
wxString wxGridSQLite3TableBase::GetValue(int row, int col)
{
   return m_ArrayColumn[col]->GetString(row);
}
/*---------------------------------------------------------------------------*/
void wxGridSQLite3TableBase::SetValue(int row, int col, const wxString& value)
{
  wxUnusedVar(row);
  wxUnusedVar(col);
  wxUnusedVar(value);
   // rien pour l'instant
}
/*---------------------------------------------------------------------------*/
wxString wxGridSQLite3TableBase::GetColLabelValue(int col)
{
   return m_ArrayColumn[col]->GetLabelValue();
}
/*---------------------------------------------------------------------------*/
wxString wxGridSQLite3TableBase::GetTypeName(int row, int col)
{
  wxUnusedVar(row);
  wxUnusedVar(col);
   return m_ArrayColumn[col]->GetType();
}
/*---------------------------------------------------------------------------*/
void wxGridSQLite3TableBase::SetView(wxGrid* grid)
{
   if (grid)
   {
      m_CharWidth = grid->GetCharWidth();

      wxString tmp = wxString::Format(_(" %i "), GetNumberRows());

      grid->SetRowLabelSize(tmp.Length() * m_CharWidth);
   }

   wxGridTableBase::SetView(grid);
}
/*---------------------------------------------------------------------------*/
void wxGridSQLite3TableBase::AdaptColumnsSize()
{
   if (GetView())
   {
      for (int i = 0; i < m_NumberCols; i++)
      {
         GetView()->SetColSize(i, m_ArrayColumn[i]->GetSize() * m_CharWidth);
         if (m_ArrayColumn[i]->GetType() == wxGRID_VALUE_FLOAT)
            GetView()->SetColFormatFloat(i, m_FloatWidth, m_FloatPrecision);
         else if (m_ArrayColumn[i]->GetType() == wxGRID_VALUE_STRING)
         {
            wxGridCellAttr* textAttr = new wxGridCellAttr;

            textAttr->SetEditor(new wxGridCellAutoWrapStringEditor);
            textAttr->SetRenderer(new wxGridCellAutoWrapStringRenderer);
            GetView()->SetColAttr(i, textAttr);
         }
         else if (m_ArrayColumn[i]->GetType() == wxGRID_VALUE_BLOB)
         {
            wxGridCellAttr* textAttr = new wxGridCellAttr;

            textAttr->SetRenderer(new wxGridCellBlobRenderer);
            textAttr->SetEditor(new wxGridCellBlobEditor);
            GetView()->SetColAttr(i, textAttr);
         }
      }
   }
}
/*---------------------------------------------------------------------------*/
void wxGridSQLite3TableBase::Init()
{
   m_CharWidth = 10; // par défaut
   m_NumberRows = m_NumberCols = 0;
   m_FloatWidth = -1;
   m_FloatPrecision = 2;
}
/*---------------------------------------------------------------------------*/
void wxGridSQLite3TableBase::PopulateArray(wxSQLite3ResultSet* resultSet)
{
   wxSQLite3TableColumn* p_Column;
   wxString colType;

   if (resultSet == NULL)
      return;
   m_NumberCols = resultSet->GetColumnCount();
   // Création des colonnes
   for (int i = 0; i < m_NumberCols; i++)
   {
      colType = resultSet->GetDeclaredColumnType(i).Upper();
      switch (resultSet->GetColumnType(i))
      {
         case WXSQLITE_INTEGER :
            p_Column = (wxSQLite3TableColumn*)new wxSQLite3TableLongColumn;
            break;
         case WXSQLITE_FLOAT   :
            p_Column = (wxSQLite3TableColumn*)new wxSQLite3TableDoubleColumn;
            break;
         case WXSQLITE_BLOB    :
            p_Column = (wxSQLite3TableColumn*)new wxSQLite3TableBlobColumn;
            break;
         default : // WXSQLITE_TEXT WXSQLITE_NULL
            if (colType == _T("BLOB") || colType == _T("CLOB") ||
                colType == _T("GLOB"))
               p_Column = (wxSQLite3TableColumn*)new wxSQLite3TableBlobColumn;
            else
               p_Column = (wxSQLite3TableColumn*)new wxSQLite3TableStringColumn;
      }
      // Nommer les colonnes
      p_Column->SetLabelValue(resultSet->GetColumnName(i));
      // Ajouter la colonne
      m_ArrayColumn.Add(p_Column);
   }
   // boucler et incrémenter
   while (resultSet->NextRow())
   {
      m_NumberRows++;
      for (int i = 0; i < m_NumberCols; i++)
         m_ArrayColumn[i]->AddValue(*resultSet, i);
   }
}
/*---------------------------------------------------------------------------*/
// wxGridSQLite3Table
/*---------------------------------------------------------------------------*/
wxGridSQLite3Table::wxGridSQLite3Table(wxSQLite3ResultSet* resultSet) :
                    wxGridSQLite3TableBase()
{
   PopulateArray(resultSet);
}
/*---------------------------------------------------------------------------*/
wxGridSQLite3Table::wxGridSQLite3Table(wxSQLite3Database* db,
                                       const wxString& tablename,
                                       const wxString& base) :
                    wxGridSQLite3TableBase()
{
   if (db == NULL)
      return;
   if (db->TableExists(tablename))
   {
      m_TableName = tablename;
      wxSQLite3ResultSet resultSet = GetResultSet(db, base);
      PopulateArray(&resultSet);
      resultSet.Finalize();
   }
}
/*---------------------------------------------------------------------------*/
bool wxGridSQLite3Table::GetBlob(size_t row, size_t col, wxMemoryBuffer*& buffer)
{
   if (row < (size_t)GetNumberRows() && col < (size_t)GetNumberCols())
      if (m_ArrayColumn[col]->GetType() == wxGRID_VALUE_BLOB)
      {
         buffer =  ((wxSQLite3TableBlobColumn*)m_ArrayColumn[col])->GetBuffer(row);
         return true;
      }
   return false;
}
/*---------------------------------------------------------------------------*/
wxSQLite3ResultSet wxGridSQLite3Table::GetResultSet(wxSQLite3Database* db,
                                                    const wxString& base)
{
   wxSQLite3ResultSet resultSet;
   wxString sql;
   sql = _("SELECT * FROM ");
   if (base != wxEmptyString)
      sql += base + _T(".");
   sql += m_TableName + _(";");
   try
   {
      resultSet = db->ExecuteQuery(ToUTF8(sql));
   }
   catch(wxSQLite3Exception& ex)
   {
      wxGetApp().ShowError(_T("GetResultSet"), ex);
   }
   return resultSet;
}
/*---------------------------------------------------------------------------*/
wxGridTblIndexesTable::wxGridTblIndexesTable(wxSQLite3Database* db,
                                             const wxString& tablename,
                                             const wxString& base) :
                    wxGridSQLite3TableBase()
{
   if (db == NULL)
      return;
   if (db->TableExists(tablename))
   {
      wxSQLite3ResultSet resultSet = GetResultSet(db, tablename, base);
      PopulateArray(&resultSet);
      resultSet.Finalize();
      for (int i = 0; i < m_NumberCols; i++)
         m_ArrayColumn[i]->SetShowNull(false);
   }
}
/*---------------------------------------------------------------------------*/
wxString wxGridTblIndexesTable::GetTypeName(int row, int col)
{
   if (col == 2)
         return wxGRID_VALUE_BOOL;
   else
      return wxGridSQLite3TableBase::GetTypeName(row, col);
}
/*---------------------------------------------------------------------------*/
wxString wxGridTblIndexesTable::GetValue(int row, int col)
{
   // dans certain cas au lieu de 1 la colonne est égale à 99
   // les coches sont alors mal gérées
   if (col == 2)
      return m_ArrayColumn[col]->GetBool(row) ? _T("1") : _T("0");
   else
      return m_ArrayColumn[col]->GetString(row);
}
/*---------------------------------------------------------------------------*/
wxSQLite3ResultSet wxGridTblIndexesTable::GetResultSet(wxSQLite3Database* db,
                                                       const wxString& tablename,
                                                       const wxString& base)
{
   wxSQLite3ResultSet resultSet;
   wxString sql, basename;

   if (base != wxEmptyString)
      basename = base;
   else
      basename = _T("main");
   sql = wxString::Format(_T("PRAGMA %s.index_list(\"%s\");"), basename.c_str(),
                          tablename.c_str());
   try
   {
      resultSet = db->ExecuteQuery(ToUTF8(sql));
   }
   catch(wxSQLite3Exception& ex)
   {
      wxGetApp().ShowError(_T("GetResultSet"), ex);
   }
   return resultSet;
}
/*---------------------------------------------------------------------------*/
wxGridTblColumnsTable::wxGridTblColumnsTable(wxSQLite3Database* db,
                                             const wxString& tablename,
                                             const wxString& base) :
                    wxGridSQLite3TableBase()
{
   if (db == NULL)
      return;
   wxSQLite3ResultSet resultSet = GetResultSet(db, tablename, base);
   PopulateArray(&resultSet);
   resultSet.Finalize();
   for (int i = 0; i < m_NumberCols; i++)
      m_ArrayColumn[i]->SetShowNull(false);
}
/*---------------------------------------------------------------------------*/
wxString wxGridTblColumnsTable::GetTypeName(int row, int col)
{
   if ((col == 3)||(col == 5))
         return wxGRID_VALUE_BOOL;
   else
      return wxGridSQLite3TableBase::GetTypeName(row, col);
}
/*---------------------------------------------------------------------------*/
wxString wxGridTblColumnsTable::GetValue(int row, int col)
{
   // dans certain cas au lieu de 1 la colonne est égale à 99
   // les coches sont alors mal gérées
   if ((col == 3)||(col == 5))
      return m_ArrayColumn[col]->GetBool(row) ? _T("1") : _T("0");
   else
      return m_ArrayColumn[col]->GetString(row);
}
/*---------------------------------------------------------------------------*/
wxSQLite3ResultSet wxGridTblColumnsTable::GetResultSet(wxSQLite3Database* db,
                                                       const wxString& tablename,
                                                       const wxString& base)
{
   wxSQLite3ResultSet resultSet;
   wxString sql, basename;

   if (base != wxEmptyString)
      basename = base;
   else
      basename = _T("main");
   sql = wxString::Format(_T("PRAGMA %s.table_info(\"%s\");"), basename.c_str(),
                          tablename.c_str());
   try
   {
      resultSet = db->ExecuteQuery(ToUTF8(sql));
   }
   catch(wxSQLite3Exception& ex)
   {
      wxGetApp().ShowError(_T("GetResultSet"), ex);
   }
   return resultSet;
}
/*---------------------------------------------------------------------------*/
wxGridTriggerTable::wxGridTriggerTable(wxSQLite3Database* db,
                                       const wxString& tablename,
                                       const wxString& base) :
                    wxGridSQLite3TableBase()
{
   if (db == NULL)
      return;
   if (db->TableExists(tablename))
   {
      wxSQLite3ResultSet resultSet = GetResultSet(db, tablename, base);
      PopulateArray(&resultSet);
      resultSet.Finalize();
   }
}
/*---------------------------------------------------------------------------*/
void wxGridTriggerTable::PopulateArray(wxSQLite3ResultSet* resultSet)
{
   wxSQLite3TableColumn* p_Column;
   wxString sql;

   if (resultSet == NULL||resultSet->GetColumnCount() == 0)
      return;
   m_NumberCols = 3;
   p_Column = (wxSQLite3TableColumn*)new wxSQLite3TableStringColumn;
   p_Column->SetLabelValue(_T("name"));
   p_Column->SetShowNull(false);
   m_ArrayColumn.Add(p_Column);
   p_Column = (wxSQLite3TableColumn*)new wxSQLite3TableStringColumn;
   p_Column->SetLabelValue(_T("type"));
   p_Column->SetShowNull(false);
   m_ArrayColumn.Add(p_Column);
   p_Column = (wxSQLite3TableColumn*)new wxSQLite3TableStringColumn;
   p_Column->SetLabelValue(_T("column/Event"));
   p_Column->SetShowNull(false);
   m_ArrayColumn.Add(p_Column);
   // boucler et incrémenter
   while (resultSet->NextRow())
   {
      m_NumberRows++;
      m_ArrayColumn[0]->AddValue(*resultSet, 0);
      sql = resultSet->GetString(1);
      wxCreateTrigerParserMinimal parser(sql);
      m_ArrayColumn[1]->AddValue(parser.GetEvent());
      m_ArrayColumn[2]->AddValue(parser.GetColumn());
   }
}
/*---------------------------------------------------------------------------*/
wxSQLite3ResultSet wxGridTriggerTable::GetResultSet(wxSQLite3Database* db,
                                                    const wxString& tablename,
                                                    const wxString& base)
{
   wxSQLite3ResultSet resultSet;
   wxString sql;

   if ((base == wxEmptyString)||(base == _T("main")))
   {
      sql = _T("SELECT name, sql FROM  sqlite_master WHERE type = 'trigger' AND tbl_name = '");
      sql += tablename + _T("' UNION SELECT name, sql FROM sqlite_temp_master WHERE type = 'trigger' AND tbl_name = '");
      sql += tablename + _T("';");
   }
   else
   {
      sql = _T("SELECT name, sql FROM ");
      sql += base + _T(".");
      sql += _T("sqlite_master WHERE type = 'trigger' AND tbl_name = '");
      sql += tablename + _T("';");
   }
   try
   {
      resultSet = db->ExecuteQuery(ToUTF8(sql));
   }
   catch(wxSQLite3Exception& ex)
   {
      wxGetApp().ShowError(_T("GetResultSet"), ex);
   }
   return resultSet;
}
/*---------------------------------------------------------------------------*/
