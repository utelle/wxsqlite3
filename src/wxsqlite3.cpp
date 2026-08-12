/*
** Name:        wxsqlite3.cpp
** Purpose:     Implementation of wxSQLite3 classes
** Author:      Ulrich Telle
** Created:     2005-07-06
** Copyright:   (c) 2005-2026 Ulrich Telle and the wxSQLite3 contributors
** SPDX-License-Identifier: LGPL-3.0+ WITH WxWindows-exception-3.1
*/

/// \file wxsqlite3.cpp Implementation of the wxSQLite3 class

#if defined(__GNUG__) && !defined(__APPLE__)
#pragma implementation "wxsqlite3.h"
#endif

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

//#include <vld.h>

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "wx/dynarray.h"
#include "wx/regex.h"
#include "wx/thread.h"

#include "wx/wxsqlite3.h"
#include "wx/wxsqlite3opt.h"

// Suppress some Visual C++ warnings regarding the default constructor
// for a C struct used only in SQLite modules
#ifdef __VISUALC__
#pragma warning (disable:4510)
#pragma warning (disable:4610)
#endif

#include "sqlite3mc_config.h"

#ifdef SQLITE_CORE
#undef SQLITE_CORE
#endif

#include "sqlite3mc_amalgamation.h"

namespace wxSQLite3 {

// Check for minimal required SQLite version
#if SQLITE_VERSION_NUMBER < 3032000
#error SQLite version 3.32.0 or higher required.
#endif

using sqlite3_xauth = int (*)(void*, int, const char*, const char*, const char*, const char*);

// Local declaration of the ExecAuthorizer function
// to avoid dependency on user authentication enabled or not
static int FunctionContextExecAuthorizer(void* func, int type,
                                         const char* arg1, const char* arg2,
                                         const char* arg3, const char* arg4
                                        );

// Error messages

#if wxCHECK_VERSION(2,9,0)
using err_char_t = char;
#else
using err_char_t = wxChar;
#endif

const err_char_t* wxERRMSG_NODB = wxTRANSLATE("No Database opened");
const err_char_t* wxERRMSG_NOSTMT = wxTRANSLATE("Statement not accessible");
const err_char_t* wxERRMSG_NOMEM = wxTRANSLATE("Out of memory");
const err_char_t* wxERRMSG_INVALID_INDEX = wxTRANSLATE("Invalid field index");
const err_char_t* wxERRMSG_INVALID_NAME = wxTRANSLATE("Invalid field name");
const err_char_t* wxERRMSG_INVALID_ROW = wxTRANSLATE("Invalid row index");
const err_char_t* wxERRMSG_INVALID_QUERY = wxTRANSLATE("Invalid scalar query");
const err_char_t* wxERRMSG_INVALID_BLOB = wxTRANSLATE("Invalid BLOB handle");

const err_char_t* wxERRMSG_NORESULT = wxTRANSLATE("Null Results pointer");
const err_char_t* wxERRMSG_BIND_STR = wxTRANSLATE("Error binding string param");
const err_char_t* wxERRMSG_BIND_INT = wxTRANSLATE("Error binding int param");
const err_char_t* wxERRMSG_BIND_INT64 = wxTRANSLATE("Error binding int64 param");
const err_char_t* wxERRMSG_BIND_DBL = wxTRANSLATE("Error binding double param");
const err_char_t* wxERRMSG_BIND_BLOB = wxTRANSLATE("Error binding blob param");
const err_char_t* wxERRMSG_BIND_DATETIME = wxTRANSLATE("Error binding date/time param");
const err_char_t* wxERRMSG_BIND_NULL = wxTRANSLATE("Error binding NULL param");
const err_char_t* wxERRMSG_BIND_ZEROBLOB = wxTRANSLATE("Error binding zero blob param");
const err_char_t* wxERRMSG_BIND_POINTER = wxTRANSLATE("Error binding pointer param");
const err_char_t* wxERRMSG_BIND_CLEAR = wxTRANSLATE("Error clearing bindings");

const err_char_t* wxERRMSG_NOMETADATA = wxTRANSLATE("Meta data support not available");
const err_char_t* wxERRMSG_NOLOADEXT = wxTRANSLATE("Loadable extension support not available");
const err_char_t* wxERRMSG_NOCOLLECTIONS = wxTRANSLATE("Named collection support not available");

const err_char_t* wxERRMSG_SHARED_CACHE = wxTRANSLATE("Setting SQLite shared cache mode failed");

const err_char_t* wxERRMSG_INITIALIZE = wxTRANSLATE("Initialization of SQLite failed");
const err_char_t* wxERRMSG_SHUTDOWN = wxTRANSLATE("Shutdown of SQLite failed");

const err_char_t* wxERRMSG_SOURCEDB_BUSY = wxTRANSLATE("Source database is busy");
const err_char_t* wxERRMSG_DBOPEN_FAILED = wxTRANSLATE("Database open failed");
const err_char_t* wxERRMSG_DBASSIGN_FAILED = wxTRANSLATE("Database assignment failed");
const err_char_t* wxERRMSG_FINALIZE_FAILED = wxTRANSLATE("Finalize failed");

const err_char_t* wxERRMSG_CIPHER_APPLY_FAILED = wxTRANSLATE("Application of cipher failed");
const err_char_t* wxERRMSG_CIPHER_NOT_SUPPORTED = wxTRANSLATE("Cipher not supported");

const err_char_t* wxERRMSG_INVALID_COLLECTION = wxTRANSLATE("Collection instance not properly initialized");

const err_char_t* wxERRMSG_SCHEMANAME_UNKNOWN = wxTRANSLATE("Schema name unknown");

const err_char_t* wxERRMSG_DBCONFIG_OPTION_UNKNOWN = wxTRANSLATE("Database configuration option unknown");

static const char* LocalMakePointerTypeCopy(wxArrayPtrVoid& ptrTypes, const wxString& pointerType)
{
  // Convert pointer type to char*
  wxCharBuffer strPointerType = pointerType.ToUTF8();
  const char* localPointerType = strPointerType;

  // Check whether pointer type was already registered
  char* ptrTypeCopy = nullptr;
  size_t nPtrTypes = ptrTypes.GetCount();
  for (size_t j = 0; (ptrTypeCopy == nullptr) && (j < nPtrTypes); ++j)
  {
    if (strcmp(localPointerType, static_cast<char*>(ptrTypes[j])) == 0)
    {
      ptrTypeCopy = static_cast<char*>(ptrTypes[j]);
    }
  }

  // Create copy of pointer type if not found
  if (ptrTypeCopy == nullptr)
  {
    int n = static_cast<int>(strlen(localPointerType));
    ptrTypeCopy = static_cast<char*>(sqlite3_malloc(n + 1));
    if (ptrTypeCopy != nullptr)
    {
      strcpy(ptrTypeCopy, localPointerType);
      ptrTypes.Add(ptrTypeCopy);
    }
  }

  return static_cast<const char*>(ptrTypeCopy);
}

/// Database handle (internal)
class DatabaseHandle
{
public:
  /// Default constructor
  explicit DatabaseHandle(sqlite3* db = nullptr)
    : m_db(db)
  {
  }

  inline sqlite3* Get() const noexcept
  {
    return m_db;
  }

  int Close() noexcept
  {
    if (m_db == nullptr)
      return SQLITE_OK;

    sqlite3* db = m_db;
    m_db = nullptr;
    return sqlite3_close(db);
  }

  /// Default destructor
  virtual ~DatabaseHandle() noexcept
  {
    Close();
  }

private:
  sqlite3* m_db;        ///< SQLite database reference
};

/// Reference counted statement object (internal)
class StatementHandle
{
public:
  /// Default constructor
  StatementHandle(sqlite3_stmt* stmt = nullptr)
    : m_stmt(stmt), m_ptrTypes(nullptr)
  {
  }

  inline sqlite3_stmt* Get() const noexcept
  {
    return m_stmt;
  }

  int Finalize() noexcept
  {
    if (m_stmt == nullptr)
      return SQLITE_OK;

    sqlite3_stmt* stmt = m_stmt;
    m_stmt = nullptr;

    return sqlite3_finalize(stmt);
  }

  /// Default destructor
  virtual ~StatementHandle() noexcept
  {
    Finalize();
    if (m_ptrTypes != nullptr)
    {
      size_t n = m_ptrTypes->GetCount();
      for (size_t j = 0; j < n; ++j)
      {
        sqlite3_free((*m_ptrTypes)[j]);
      }
      delete m_ptrTypes;
    }
  }

  /// Manage pointer types
  const char* MakePointerTypeCopy(const wxString& pointerType)
  {
    // Allocate pointer type array if necessary
    if (m_ptrTypes == nullptr)
    {
      m_ptrTypes = new wxArrayPtrVoid();
    }

    // Convert pointer type to char*
    return LocalMakePointerTypeCopy(*m_ptrTypes, pointerType);
  }

private:
  sqlite3_stmt*   m_stmt;           ///< SQLite statement reference
  wxArrayPtrVoid* m_ptrTypes;       ///< Keeping track of pointer types
};

/// Reference counted blob object (internal)
class BlobHandle
{
public:
  /// Default constructor
  BlobHandle(sqlite3_blob* blob = nullptr)
    : m_blob(blob)
  {
  }

  inline sqlite3_blob* Get() const noexcept
  {
    return m_blob;
  }

  int Finalize() noexcept
  {
    if (m_blob == nullptr)
      return SQLITE_OK;

    sqlite3_blob* blob = m_blob;
    m_blob = nullptr;

    return sqlite3_blob_close(blob);;
  }

  /// Default destructor
  virtual ~BlobHandle() noexcept
  {
    Finalize();
  }

private:
  sqlite3_blob* m_blob;           ///< SQLite blob reference
};

// ----------------------------------------------------------------------------
// inline conversion from wxString to wxLongLong
// ----------------------------------------------------------------------------

static inline wxLongLong ConvertStringToLongLong(const wxString& str, wxLongLong defValue /*=0*/)
{
  size_t n = str.Length();
  size_t j = 0;
  wxLongLong value = 0;
  bool negative = false;

  if (str[j] == '-')
  {
    negative = true;
    j++;
  }

  while (j < n)
  {
    if (str[j] < '0' || str[j] > '9')
    {
      return defValue;
    }
    value *= 10;
    value += (str[j] - '0');
    j++;
  }

  return negative ? -value : value;
}

const char* GetLastErrorMessage(sqlite3* db)
{
  static const char* unknownError = "Unknown error";
  const char* localError = sqlite3_errmsg(db);
  if (localError == nullptr)
    localError = sqlite3_errstr(sqlite3_errcode(db));
  if (localError == nullptr)
    localError = unknownError;
  return localError;
}

// ----------------------------------------------------------------------------
// Exception: class
// ----------------------------------------------------------------------------

Exception::Exception(int errorCode, const wxString& message)
  : std::runtime_error(ConstructMessage(errorCode, message)),
    m_errorCode(errorCode), m_errorMessage(message)
{
}

const wxString Exception::ErrorCodeAsString(int errorCode)
{
  if (errorCode == WXSQLITE_ERROR)
  {
    return wxS("WXSQLITE_ERROR");
  }
  else
  {
    const char* errmsg = sqlite3_errstr(errorCode);
    return wxString::FromUTF8(errmsg);
  }
}

const std::string Exception::ConstructMessage(int errorCode, const wxString& errMsg)
{
  wxString msg = wxString::Format(wxS("[%d] "), errorCode) + errMsg;
  return std::string(msg.ToUTF8());
}


// ----------------------------------------------------------------------------
// StatementBuffer: class providing a statement buffer
//                  for use with the SQLite3 vmprintf function
// ----------------------------------------------------------------------------

StatementBuffer::StatementBuffer()
{
  m_buffer = nullptr;
}

StatementBuffer::~StatementBuffer() noexcept
{
  Clear();
}

void StatementBuffer::Clear() noexcept
{
  if (m_buffer)
  {
    sqlite3_free(m_buffer);
    m_buffer = nullptr;
  }
}

const char* StatementBuffer::Format(const char* format, ...)
{
  Clear();
  va_list va;
  va_start(va, format);
  m_buffer = sqlite3_vmprintf(format, va);
  va_end(va);
  return m_buffer;
}

const char* StatementBuffer::FormatV(const char* format, va_list va)
{
  Clear();
  m_buffer = sqlite3_vmprintf(format, va);
  return m_buffer;
}

// ----------------------------------------------------------------------------
// ResultSet: class providing access to the result set of a query
// ----------------------------------------------------------------------------

ResultSet::ResultSet()
{
  m_db.reset();
  m_stmt.reset();
  m_eof = true;
  m_first = true;
  m_cols = 0;
}

ResultSet::ResultSet(DatabaseHandlePtr db,
                     StatementHandlePtr stmt,
                     bool eof,
                     bool first)
{
  m_db = db;
  m_stmt = stmt;
  CheckStmt();
  m_eof = eof;
  m_first = first;
  m_cols = (m_stmt != nullptr) ? sqlite3_column_count(m_stmt->Get()) : 0;
}

ResultSet::~ResultSet()
{
  m_stmt.reset();
  m_db.reset();
}

int ResultSet::GetColumnCount() const
{
  CheckStmt();
  return m_cols;
}

wxString ResultSet::GetAsString(int columnIndex) const
{
  CheckStmt();

  if (columnIndex < 0 || columnIndex > m_cols-1)
  {
    throw Exception(WXSQLITE_ERROR, wxERRMSG_INVALID_INDEX);
  }

  const char* localValue = reinterpret_cast<const char*>(sqlite3_column_text(m_stmt->Get(), columnIndex));
  return wxString::FromUTF8(localValue);
}

wxString ResultSet::GetAsString(const wxString& columnName) const
{
  int columnIndex = FindColumnIndex(columnName);
  const char* localValue = reinterpret_cast<const char*>(sqlite3_column_text(m_stmt->Get(), columnIndex));
  return wxString::FromUTF8(localValue);
}

int ResultSet::GetInt(int columnIndex, int nullValue /* = 0 */) const
{
  if (GetColumnType(columnIndex) == SQLITE_NULL)
  {
    return nullValue;
  }
  else
  {
    return sqlite3_column_int(m_stmt->Get(), columnIndex);
  }
}


int ResultSet::GetInt(const wxString& columnName, int nullValue /* = 0 */) const
{
  int columnIndex = FindColumnIndex(columnName);
  return GetInt(columnIndex, nullValue);
}

wxLongLong ResultSet::GetInt64(int columnIndex, wxLongLong nullValue /* = 0 */) const
{
  if (GetColumnType(columnIndex) == SQLITE_NULL)
  {
    return nullValue;
  }
  else
  {
    return wxLongLong(sqlite3_column_int64(m_stmt->Get(), columnIndex));
  }
}

wxLongLong ResultSet::GetInt64(const wxString& columnName, wxLongLong nullValue /* = 0 */) const
{
  int columnIndex = FindColumnIndex(columnName);
  return GetInt64(columnIndex, nullValue);
}

double ResultSet::GetDouble(int columnIndex, double nullValue /* = 0.0 */) const
{
  if (GetColumnType(columnIndex) == SQLITE_NULL)
  {
    return nullValue;
  }
  else
  {
    return sqlite3_column_double(m_stmt->Get(), columnIndex);
  }
}

double ResultSet::GetDouble(const wxString& columnName, double nullValue /* = 0.0 */) const
{
  int columnIndex = FindColumnIndex(columnName);
  return GetDouble(columnIndex, nullValue);
}

wxString ResultSet::GetString(int columnIndex, const wxString& nullValue /* = wxEmptyString */) const
{
  if (GetColumnType(columnIndex) == SQLITE_NULL)
  {
    return nullValue;
  }
  else
  {
    const char* localValue = (const char*) sqlite3_column_text(m_stmt->Get(), columnIndex);
    return wxString::FromUTF8(localValue);
  }
}

wxString ResultSet::GetString(const wxString& columnName, const wxString& nullValue /* = wxEmptyString */) const
{
  int columnIndex = FindColumnIndex(columnName);
  return GetString(columnIndex, nullValue);
}

const unsigned char* ResultSet::GetBlob(int columnIndex, int& len) const
{
  CheckStmt();

  if (columnIndex < 0 || columnIndex > m_cols-1)
  {
    throw Exception(WXSQLITE_ERROR, wxERRMSG_INVALID_INDEX);
  }

  len = sqlite3_column_bytes(m_stmt->Get(), columnIndex);
  return static_cast<const unsigned char*>(sqlite3_column_blob(m_stmt->Get(), columnIndex));
}

const unsigned char* ResultSet::GetBlob(const wxString& columnName, int& len) const
{
  int columnIndex = FindColumnIndex(columnName);
  return GetBlob(columnIndex, len);
}

wxMemoryBuffer& ResultSet::GetBlob(int columnIndex, wxMemoryBuffer& buffer) const
{
  CheckStmt();

  if (columnIndex < 0 || columnIndex > m_cols-1)
  {
    throw Exception(WXSQLITE_ERROR, wxERRMSG_INVALID_INDEX);
  }

  int len = sqlite3_column_bytes(m_stmt->Get(), columnIndex);
  const void* blob = sqlite3_column_blob(m_stmt->Get(), columnIndex);
  buffer.AppendData(blob, static_cast<size_t>(len));
  return buffer;
}

wxMemoryBuffer& ResultSet::GetBlob(const wxString& columnName, wxMemoryBuffer& buffer) const
{
  int columnIndex = FindColumnIndex(columnName);
  return GetBlob(columnIndex, buffer);
}

wxDateTime ResultSet::GetDate(int columnIndex) const
{
  if (GetColumnType(columnIndex) == SQLITE_NULL)
  {
    return wxInvalidDateTime;
  }
  else
  {
    wxDateTime date;
    const wxChar* result = date.ParseDate(GetString(columnIndex));
    if (result != nullptr)
    {
      return date;
    }
    else
    {
      return wxInvalidDateTime;
    }
  }
}

wxDateTime ResultSet::GetDate(const wxString& columnName) const
{
  int columnIndex = FindColumnIndex(columnName);
  return GetDate(columnIndex);
}


wxDateTime ResultSet::GetTime(int columnIndex) const
{
  if (GetColumnType(columnIndex) == SQLITE_NULL)
  {
    return wxInvalidDateTime;
  }
  else
  {
    wxDateTime date;
    const wxChar* result = date.ParseTime(GetString(columnIndex));
    if (result != nullptr)
    {
      return date;
    }
    else
    {
      return wxInvalidDateTime;
    }
  }
}

wxDateTime ResultSet::GetTime(const wxString& columnName) const
{
  int columnIndex = FindColumnIndex(columnName);
  return GetTime(columnIndex);
}

wxDateTime ResultSet::GetDateTime(int columnIndex) const
{
  if (GetColumnType(columnIndex) == SQLITE_NULL)
  {
    return wxInvalidDateTime;
  }
  else
  {
    wxDateTime date;
    const wxChar* result = date.ParseDateTime(GetString(columnIndex));
    if (result != nullptr)
    {
      date.SetMillisecond(0);
      return date;
    }
    else
    {
      return wxInvalidDateTime;
    }
  }
}

wxDateTime ResultSet::GetDateTime(const wxString& columnName) const
{
  int columnIndex = FindColumnIndex(columnName);
  return GetDateTime(columnIndex);
}

wxDateTime ResultSet::GetTimestamp(int columnIndex) const
{
  if (GetColumnType(columnIndex) == SQLITE_NULL)
  {
    return wxInvalidDateTime;
  }
  else
  {
    wxDateTime date;
    const wxChar* result = date.ParseDateTime(GetString(columnIndex));
    if (result != nullptr)
    {
      return date;
    }
    else
    {
      return wxInvalidDateTime;
    }
  }
}

wxDateTime ResultSet::GetTimestamp(const wxString& columnName) const
{
  int columnIndex = FindColumnIndex(columnName);
  return GetTimestamp(columnIndex);
}

wxDateTime ResultSet::GetNumericDateTime(int columnIndex) const
{
  if (GetColumnType(columnIndex) == SQLITE_NULL)
  {
    return wxInvalidDateTime;
  }
  else
  {
    wxLongLong value = GetInt64(columnIndex);
    return wxDateTime(value);
  }
}

wxDateTime ResultSet::GetNumericDateTime(const wxString& columnName) const
{
  int columnIndex = FindColumnIndex(columnName);
  return GetNumericDateTime(columnIndex);
}

wxDateTime ResultSet::GetUnixDateTime(int columnIndex) const
{
  if (GetColumnType(columnIndex) == SQLITE_NULL)
  {
    return wxInvalidDateTime;
  }
  else
  {
    wxLongLong value = GetInt64(columnIndex);
    return wxDateTime((time_t) value.GetValue());
  }
}

wxDateTime ResultSet::GetUnixDateTime(const wxString& columnName) const
{
  int columnIndex = FindColumnIndex(columnName);
  return GetUnixDateTime(columnIndex);
}

wxDateTime ResultSet::GetJulianDayNumber(int columnIndex) const
{
  if (GetColumnType(columnIndex) == SQLITE_NULL)
  {
    return wxInvalidDateTime;
  }
  else
  {
    double value = GetDouble(columnIndex);
    return wxDateTime(value);
  }
}

wxDateTime ResultSet::GetJulianDayNumber(const wxString& columnName) const
{
  int columnIndex = FindColumnIndex(columnName);
  return GetJulianDayNumber(columnIndex);
}

bool ResultSet::GetBool(int columnIndex) const
{
  return GetInt(columnIndex) != 0;
}

wxDateTime ResultSet::GetAutomaticDateTime(int columnIndex, bool milliSeconds) const
{
  wxDateTime result;
  int columnType = GetColumnType(columnIndex);
  switch (columnType)
  {
    case SQLITE3_TEXT:
      result = GetDateTime(columnIndex);
      break;
    case SQLITE_INTEGER:
      if (milliSeconds)
      {
        wxLongLong value = GetInt64(columnIndex);
        result = wxDateTime(value);
      }
      else
      {
        time_t value = GetInt64(columnIndex).GetValue();
        result = wxDateTime(value);
      }
      break;
    case SQLITE_FLOAT:
      result = GetJulianDayNumber(columnIndex);
      break;
    case SQLITE_NULL:
    default:
      result = wxInvalidDateTime;
      break;
  }
  return result;
}

wxDateTime ResultSet::GetAutomaticDateTime(const wxString& columnName, bool milliSeconds) const
{
  int columnIndex = FindColumnIndex(columnName);
  return GetAutomaticDateTime(columnIndex, milliSeconds);
}

bool ResultSet::GetBool(const wxString& columnName) const
{
  int columnIndex = FindColumnIndex(columnName);
  return GetBool(columnIndex);
}

bool ResultSet::IsNull(int columnIndex) const
{
  return (GetColumnType(columnIndex) == SQLITE_NULL);
}

bool ResultSet::IsNull(const wxString& columnName) const
{
  int columnIndex = FindColumnIndex(columnName);
  return (GetColumnType(columnIndex) == SQLITE_NULL);
}

int ResultSet::FindColumnIndex(const wxString& columnName) const
{
  CheckStmt();

  wxCharBuffer strColumnName = columnName.ToUTF8();
  const char* localColumnName = strColumnName;

  if (columnName.Len() > 0)
  {
    for (int columnIndex = 0; columnIndex < m_cols; columnIndex++)
    {
      const char* temp = sqlite3_column_name(m_stmt->Get(), columnIndex);

      if (strcmp(localColumnName, temp) == 0)
      {
        return columnIndex;
      }
    }
  }

  throw Exception(WXSQLITE_ERROR, wxERRMSG_INVALID_INDEX);
}

wxString ResultSet::GetColumnName(int columnIndex) const
{
  CheckStmt();

  if (columnIndex < 0 || columnIndex > m_cols-1)
  {
    throw Exception(WXSQLITE_ERROR, wxERRMSG_INVALID_INDEX);
  }

  const char* localValue = sqlite3_column_name(m_stmt->Get(), columnIndex);
  return wxString::FromUTF8(localValue);
}

wxString ResultSet::GetDeclaredColumnType(int columnIndex) const
{
  CheckStmt();

  if (columnIndex < 0 || columnIndex > m_cols-1)
  {
    throw Exception(WXSQLITE_ERROR, wxERRMSG_INVALID_INDEX);
  }

  const char* localValue = sqlite3_column_decltype(m_stmt->Get(), columnIndex);
  return wxString::FromUTF8(localValue);
}

int ResultSet::GetColumnType(int columnIndex) const
{
  CheckStmt();

  if (columnIndex < 0 || columnIndex > m_cols-1)
  {
    throw Exception(WXSQLITE_ERROR, wxERRMSG_INVALID_INDEX);
  }

  return sqlite3_column_type(m_stmt->Get(), columnIndex);
}

bool ResultSet::Eof() const
{
  CheckStmt();
  return m_eof;
}

bool ResultSet::CursorMoved() const
{
  CheckStmt();
  return !m_first;
}

bool ResultSet::NextRow()
{
  CheckStmt();

  int rc;
  if (m_first)
  {
    m_first = false;
    rc = (m_eof) ? SQLITE_DONE : SQLITE_ROW;
  }
  else
  {
    rc = sqlite3_step(m_stmt->Get());
  }

  if (rc == SQLITE_DONE) // no more rows
  {
    m_eof = true;
    return false;
  }
  else if (rc == SQLITE_ROW) // more rows
  {
    return true;
  }
  else
  {
    rc = m_stmt->Finalize();
    const char* localError = GetLastErrorMessage(m_db->Get());
    throw Exception(rc, wxString::FromUTF8(localError));
  }
}

void ResultSet::Finalize()
{
  if (m_stmt != nullptr)
  {
    int rc = m_stmt->Finalize();
    if (rc != SQLITE_OK)
    {
      if (m_db != nullptr && m_db->Get() != nullptr)
      {
        const char* localError = GetLastErrorMessage(m_db->Get());
        throw Exception(rc, wxString::FromUTF8(localError));
      }
      else
      {
        throw Exception(rc, wxERRMSG_FINALIZE_FAILED);
      }
    }
  }
  m_stmt.reset();
  m_db.reset();
}

wxString ResultSet::GetSQL() const
{
  wxString sqlString = wxEmptyString;
  CheckStmt();
  const char* sqlLocal = sqlite3_sql(m_stmt->Get());
  if (sqlLocal != nullptr) sqlString = wxString::FromUTF8(sqlLocal);
  return sqlString;
}

wxString ResultSet::GetExpandedSQL() const
{
  wxString sqlString = wxEmptyString;
  CheckStmt();
  char* sqlLocal = sqlite3_expanded_sql(m_stmt->Get());
  if (sqlLocal != nullptr)
  {
    sqlString = wxString::FromUTF8(sqlLocal);
    sqlite3_free(sqlLocal);
  }
  return sqlString;
}

bool ResultSet::IsOk() const
{
  return (m_db != nullptr) && (m_db->Get() != nullptr) && (m_stmt != nullptr) && (m_stmt->Get() != nullptr);
}

ResultSet::Iterator::Iterator(ResultSet* res, bool end)
  : m_resultSet(res), m_isEnd(end)
{
  if (!m_isEnd && !m_resultSet->NextRow())
  {
    m_isEnd = true;
  }
}

ResultSet::Iterator& ResultSet::Iterator::operator++()
{
  if (!m_resultSet->NextRow())
    m_isEnd = true;
  return *this;
}

bool ResultSet::Iterator::operator!=(const ResultSet::Iterator& other) const
{
  return m_isEnd != other.m_isEnd;
}

void ResultSet::CheckStmt() const
{
  if (m_stmt == nullptr || m_stmt->Get() == nullptr)
  {
    throw Exception(WXSQLITE_ERROR, wxERRMSG_NOSTMT);
  }
}

wxString ResultSet::GetDatabaseName(int columnIndex) const
{
#if SQLITE_ENABLE_COLUMN_METADATA
  CheckStmt();
  if (columnIndex < 0 || columnIndex > m_cols-1)
  {
    throw Exception(WXSQLITE_ERROR, wxERRMSG_INVALID_INDEX);
  }

  const char* localValue = sqlite3_column_database_name(m_stmt->Get(), columnIndex);
  if (localValue != nullptr)
    return wxString::FromUTF8(localValue);
  else
    return wxEmptyString;
#else
  wxUnusedVar(columnIndex);
  throw Exception(WXSQLITE_ERROR, wxERRMSG_NOMETADATA);
#endif
}

wxString ResultSet::GetTableName(int columnIndex) const
{
#if SQLITE_ENABLE_COLUMN_METADATA
  CheckStmt();
  if (columnIndex < 0 || columnIndex > m_cols-1)
  {
    throw Exception(WXSQLITE_ERROR, wxERRMSG_INVALID_INDEX);
  }

  const char* localValue = sqlite3_column_table_name(m_stmt->Get(), columnIndex);
  if (localValue != nullptr)
    return wxString::FromUTF8(localValue);
  else
    return wxEmptyString;
#else
  wxUnusedVar(columnIndex);
  throw Exception(WXSQLITE_ERROR, wxERRMSG_NOMETADATA);
#endif
}

wxString ResultSet::GetOriginName(int columnIndex) const
{
#if SQLITE_ENABLE_COLUMN_METADATA
  CheckStmt();
  if (columnIndex < 0 || columnIndex > m_cols-1)
  {
    throw Exception(WXSQLITE_ERROR, wxERRMSG_INVALID_INDEX);
  }

  const char* localValue = sqlite3_column_origin_name(m_stmt->Get(), columnIndex);
  if (localValue != nullptr)
    return wxString::FromUTF8(localValue);
  else
    return wxEmptyString;
#else
  wxUnusedVar(columnIndex);
  throw Exception(WXSQLITE_ERROR, wxERRMSG_NOMETADATA);
#endif
}

// ----------------------------------------------------------------------------
// Table: class holding the complete result set of a query
// ----------------------------------------------------------------------------

Table::Table()
{
  m_results = 0;
  m_rows = 0;
  m_cols = 0;
  m_currentRow = 0;
}

Table::Table(const Table& table)
{
  m_results = table.m_results;
  // Only one object can own the results
  const_cast<Table&>(table).m_results = 0;
  m_rows = table.m_rows;
  m_cols = table.m_cols;
  m_currentRow = table.m_currentRow;
}

Table::Table(char** results, int rows, int cols)
{
  m_results = results;
  m_rows = rows;
  m_cols = cols;
  m_currentRow = 0;
}

Table::~Table()
{
  try
  {
    Finalize();
  }
  catch (...)
  {
  }
}

Table& Table::operator=(const Table& table)
{
  if (this != &table)
  {
    try
    {
      Finalize();
    }
    catch (...)
    {
    }
    m_results = table.m_results;
    // Only one object can own the results
    const_cast<Table&>(table).m_results = 0;
    m_rows = table.m_rows;
    m_cols = table.m_cols;
    m_currentRow = table.m_currentRow;
  }
  return *this;
}

void Table::Finalize()
{
  if (m_results)
  {
    sqlite3_free_table(m_results);
    m_results = 0;
  }
}

int Table::GetColumnCount() const
{
  CheckResults();
  return m_cols;
}

int Table::GetRowCount() const
{
  CheckResults();
  return m_rows;
}

int Table::FindColumnIndex(const wxString& columnName) const
{
  CheckResults();

  wxCharBuffer strColumnName = columnName.ToUTF8();
  const char* localColumnName = strColumnName;

  if (columnName.Len() > 0)
  {
    for (int columnIndex = 0; columnIndex < m_cols; columnIndex++)
    {
      if (strcmp(localColumnName, m_results[columnIndex]) == 0)
      {
        return columnIndex;
      }
    }
  }

  throw Exception(WXSQLITE_ERROR, wxERRMSG_INVALID_NAME);
}

wxString Table::GetAsString(int columnIndex) const
{
  if (columnIndex < 0 || columnIndex > m_cols-1)
  {
    throw Exception(WXSQLITE_ERROR, wxERRMSG_INVALID_INDEX);
  }

  int nIndex = (m_currentRow*m_cols) + m_cols + columnIndex;
  const char* localValue = m_results[nIndex];
  return wxString::FromUTF8(localValue);
}

wxString Table::GetAsString(const wxString& columnName) const
{
  int index = FindColumnIndex(columnName);
  return GetAsString(index);
}

int Table::GetInt(int columnIndex, int nullValue /* = 0 */) const
{
  if (IsNull(columnIndex))
  {
    return nullValue;
  }
  else
  {
    long value = nullValue;
    GetAsString(columnIndex).ToLong(&value);
    return static_cast<int>(value);
  }
}

int Table::GetInt(const wxString& columnName, int nullValue /* = 0 */) const
{
  if (IsNull(columnName))
  {
    return nullValue;
  }
  else
  {
    long value = nullValue;
    GetAsString(columnName).ToLong(&value);
    return static_cast<int>(value);
  }
}

wxLongLong Table::GetInt64(int columnIndex, wxLongLong nullValue /* = 0 */) const
{
  if (IsNull(columnIndex))
  {
    return nullValue;
  }
  else
  {
    return ConvertStringToLongLong(GetAsString(columnIndex), nullValue);
  }
}

wxLongLong Table::GetInt64(const wxString& columnName, wxLongLong nullValue /* = 0 */) const
{
  if (IsNull(columnName))
  {
    return nullValue;
  }
  else
  {
    return ConvertStringToLongLong(GetAsString(columnName), nullValue);
  }
}

// Since SQLite uses internally a locale independent string representation
// of double values, we need to provide our own conversion procedure using
// always a point as the decimal separator.
// The following code duplicates a SQLite utility function with minor modifications.

static double AtoF(const char *z)
{
  int sign = 1;
  long double v1 = 0.0;
  int nSignificant = 0;
  while (isspace(*reinterpret_cast<const unsigned char*>(z)))
  {
    ++z;
  }
  if (*z == '-')
  {
    sign = -1;
    ++z;
  }
  else if (*z == '+')
  {
    ++z;
  }
  while (*z == '0')
  {
    ++z;
  }
  while (isdigit(*reinterpret_cast<const unsigned char*>(z)))
  {
    v1 = v1*10.0 + (*z - '0');
    ++z;
    ++nSignificant;
  }
  if (*z == '.')
  {
    long double divisor = 1.0;
    ++z;
    if (nSignificant == 0)
    {
      while (*z == '0')
      {
        divisor *= 10.0;
        ++z;
      }
    }
    while (isdigit(*reinterpret_cast<const unsigned char*>(z)))
    {
      if (nSignificant < 18)
      {
        v1 = v1*10.0 + (*z - '0');
        divisor *= 10.0;
        ++nSignificant;
      }
      ++z;
    }
    v1 /= divisor;
  }
  if (*z=='e' || *z=='E')
  {
    int esign = 1;
    int eval = 0;
    long double scale = 1.0;
    ++z;
    if (*z == '-')
    {
      esign = -1;
      ++z;
    }
    else if (*z == '+')
    {
      ++z;
    }
    while (isdigit(*reinterpret_cast<const unsigned char*>(z)))
    {
      eval = eval*10 + *z - '0';
      ++z;
    }
    while (eval >= 64) { scale *= 1.0e+64; eval -= 64; }
    while (eval >= 16) { scale *= 1.0e+16; eval -= 16; }
    while (eval >=  4) { scale *= 1.0e+4;  eval -= 4; }
    while (eval >=  1) { scale *= 1.0e+1;  eval -= 1; }
    if (esign < 0)
    {
      v1 /= scale;
    }
    else
    {
      v1 *= scale;
    }
  }
  return static_cast<double>((sign < 0) ? -v1 : v1);
}

double Table::GetDouble(int columnIndex, double nullValue /* = 0.0 */) const
{
  if (IsNull(columnIndex))
  {
    return nullValue;
  }
  else
  {
    if (columnIndex < 0 || columnIndex > m_cols-1)
    {
      throw Exception(WXSQLITE_ERROR, wxERRMSG_INVALID_INDEX);
    }
    int nIndex = (m_currentRow*m_cols) + m_cols + columnIndex;
    return AtoF(m_results[nIndex]);
  }
}

double Table::GetDouble(const wxString& columnName, double nullValue /* = 0.0 */) const
{
  int index = FindColumnIndex(columnName);
  return GetDouble(index, nullValue);
}

wxString Table::GetString(int columnIndex, const wxString& nullValue /* = wxEmptyString */) const
{
  if (IsNull(columnIndex))
  {
    return nullValue;
  }
  else
  {
    return GetAsString(columnIndex);
  }
}

wxString Table::GetString(const wxString& columnName, const wxString& nullValue /* = wxEmptyString */) const
{
  if (IsNull(columnName))
  {
    return nullValue;
  }
  else
  {
    return GetAsString(columnName);
  }
}

wxDateTime Table::GetDate(int columnIndex) const
{
  wxDateTime date;
  const wxChar* result = date.ParseDate(GetString(columnIndex));
  if (result != nullptr)
  {
    return date;
  }
  else
  {
    return wxInvalidDateTime;
  }
}

wxDateTime Table::GetDate(const wxString& columnName) const
{
  int columnIndex = FindColumnIndex(columnName);
  return GetDate(columnIndex);
}

wxDateTime Table::GetTime(int columnIndex) const
{
  wxDateTime date;
  const wxChar* result = date.ParseTime(GetString(columnIndex));
  if (result != nullptr)
  {
    return date;
  }
  else
  {
    return wxInvalidDateTime;
  }
}

wxDateTime Table::GetTime(const wxString& columnName) const
{
  int columnIndex = FindColumnIndex(columnName);
  return GetTime(columnIndex);
}

wxDateTime Table::GetDateTime(int columnIndex) const
{
  wxDateTime date;
  const wxChar* result = date.ParseDateTime(GetString(columnIndex));
  if (result != nullptr)
  {
    return date;
  }
  else
  {
    return wxInvalidDateTime;
  }
}

wxDateTime Table::GetDateTime(const wxString& columnName) const
{
  int columnIndex = FindColumnIndex(columnName);
  return GetDateTime(columnIndex);
}

bool Table::GetBool(int columnIndex) const
{
  return GetInt(columnIndex) != 0;
}

bool Table::GetBool(const wxString& columnName) const
{
  int columnIndex = FindColumnIndex(columnName);
  return GetBool(columnIndex);
}

bool Table::IsNull(int columnIndex) const
{
  CheckResults();

  if (columnIndex < 0 || columnIndex > m_cols-1)
  {
    throw Exception(WXSQLITE_ERROR, wxERRMSG_INVALID_INDEX);
  }

  int index = (m_currentRow*m_cols) + m_cols + columnIndex;
  const char* localValue = m_results[index];
  return (localValue == 0);
}

bool Table::IsNull(const wxString& columnName) const
{
  int index = FindColumnIndex(columnName);
  return IsNull(index);
}

wxString Table::GetColumnName(int columnIndex) const
{
  CheckResults();

  if (columnIndex < 0 || columnIndex > m_cols-1)
  {
    throw Exception(WXSQLITE_ERROR, wxERRMSG_INVALID_INDEX);
  }

  const char* localValue = m_results[columnIndex];
  return wxString::FromUTF8(localValue);
}

void Table::SetRow(int row)
{
  CheckResults();

  if (row < 0 || row > m_rows-1)
  {
    throw Exception(WXSQLITE_ERROR, wxERRMSG_INVALID_ROW);
  }

  m_currentRow = row;
}

bool Table::IsOk() const
{
  return (m_results != 0);
}

void Table::CheckResults() const
{
  if (m_results == 0)
  {
    throw Exception(WXSQLITE_ERROR, wxERRMSG_NORESULT);
  }
}

// ----------------------------------------------------------------------------
// Statement: class holding a prepared statement
// ----------------------------------------------------------------------------

Statement::Statement()
{
  m_db = 0;
  m_stmt = 0;
}

Statement::Statement(DatabaseHandlePtr db, StatementHandlePtr stmt)
{
  m_db = db;
  m_stmt = stmt;
}

Statement::~Statement()
{
  m_stmt.reset();
  m_db.reset();
}

int Statement::ExecuteUpdate()
{
  CheckDatabase();
  CheckStmt();

  const char* localError = 0;

  int rc = sqlite3_step(m_stmt->Get());

  if (rc == SQLITE_DONE)
  {
    int rowsChanged = sqlite3_changes(m_db->Get());

    rc = sqlite3_reset(m_stmt->Get());

    if (rc != SQLITE_OK)
    {
      localError = GetLastErrorMessage(m_db->Get());
      throw Exception(rc, wxString::FromUTF8(localError));
    }

    return rowsChanged;
  }
  else
  {
    rc = sqlite3_reset(m_stmt->Get());
    localError = GetLastErrorMessage(m_db->Get());
    throw Exception(rc, wxString::FromUTF8(localError));
  }
}

ResultSet Statement::ExecuteQuery()
{
  CheckDatabase();
  CheckStmt();

  int rc = sqlite3_step(m_stmt->Get());

  if (rc == SQLITE_DONE)  // no more rows
  {
    return ResultSet(m_db, m_stmt, true/*eof*/, true/*first*/);
  }
  else if (rc == SQLITE_ROW)  // one or more rows
  {
    return ResultSet(m_db, m_stmt, false/*eof*/, true/*first*/);
  }
  else
  {
    rc = sqlite3_reset(m_stmt->Get());
    const char* localError = GetLastErrorMessage(m_db->Get());
    throw Exception(rc, wxString::FromUTF8(localError));
  }
}

int Statement::ExecuteScalar()
{
  ResultSet resultSet = ExecuteQuery();

  if (resultSet.Eof() || resultSet.GetColumnCount() < 1)
  {
    throw Exception(WXSQLITE_ERROR, wxERRMSG_INVALID_QUERY);
  }

  long value = 0;
  resultSet.GetAsString(0).ToLong(&value);
  return static_cast<int>(value);
}

int Statement::GetParamCount() const
{
  CheckStmt();
  return sqlite3_bind_parameter_count(m_stmt->Get());
}

int Statement::GetParamIndex(const wxString& paramName) const
{
  CheckStmt();

  wxCharBuffer strParamName = paramName.ToUTF8();
  const char* localParamName = strParamName;

  return sqlite3_bind_parameter_index(m_stmt->Get(), localParamName);
}

wxString Statement::GetParamName(int paramIndex) const
{
  CheckStmt();
  const char* localParamName = sqlite3_bind_parameter_name(m_stmt->Get(), paramIndex);
  return wxString::FromUTF8(localParamName);
}

void Statement::Bind(int paramIndex, const wxString& stringValue)
{
  CheckStmt();

  wxCharBuffer strStringValue = stringValue.ToUTF8();
  const char* localStringValue = strStringValue;

  int rc = sqlite3_bind_text(m_stmt->Get(), paramIndex, localStringValue, -1, SQLITE_TRANSIENT);

  if (rc != SQLITE_OK)
  {
    throw Exception(rc, wxERRMSG_BIND_STR);
  }
}

void Statement::Bind(int paramIndex, int intValue)
{
  CheckStmt();
  int rc = sqlite3_bind_int(m_stmt->Get(), paramIndex, intValue);

  if (rc != SQLITE_OK)
  {
    throw Exception(rc, wxERRMSG_BIND_INT);
  }
}

void Statement::Bind(int paramIndex, wxLongLong int64Value)
{
  CheckStmt();
  int rc = sqlite3_bind_int64(m_stmt->Get(), paramIndex, int64Value.GetValue());

  if (rc != SQLITE_OK)
  {
    throw Exception(rc, wxERRMSG_BIND_INT64);
  }
}

void Statement::Bind(int paramIndex, double doubleValue)
{
  CheckStmt();
  int rc = sqlite3_bind_double(m_stmt->Get(), paramIndex, doubleValue);

  if (rc != SQLITE_OK)
  {
    throw Exception(rc, wxERRMSG_BIND_DBL);
  }
}

void Statement::Bind(int paramIndex, const char* charValue)
{
  CheckStmt();
  int rc = sqlite3_bind_text(m_stmt->Get(), paramIndex, charValue, -1, SQLITE_TRANSIENT);

  if (rc != SQLITE_OK)
  {
    throw Exception(rc, wxERRMSG_BIND_STR);
  }
}

void Statement::Bind(int paramIndex, const unsigned char* blobValue, int blobLen)
{
  CheckStmt();
  int rc = sqlite3_bind_blob(m_stmt->Get(), paramIndex,
                             static_cast<const void*>(blobValue),
                             blobLen, SQLITE_TRANSIENT);

  if (rc != SQLITE_OK)
  {
    throw Exception(rc, wxERRMSG_BIND_BLOB);
  }
}

void Statement::Bind(int paramIndex, const wxMemoryBuffer& blobValue)
{
  CheckStmt();
  int blobLen = static_cast<int>(blobValue.GetDataLen());
  int rc = sqlite3_bind_blob(m_stmt->Get(), paramIndex,
                             static_cast<const void*>(blobValue.GetData()),
                             blobLen, SQLITE_TRANSIENT);

  if (rc != SQLITE_OK)
  {
    throw Exception(rc, wxERRMSG_BIND_BLOB);
  }
}

void Statement::Bind(int paramIndex, void* pointer, const wxString& pointerType, void(*DeletePointer)(void*))
{
  CheckStmt();

  const char* localPointerType = m_stmt->MakePointerTypeCopy(pointerType);
  int rc = sqlite3_bind_pointer(m_stmt->Get(), paramIndex, pointer, localPointerType, DeletePointer);

  if (rc != SQLITE_OK)
  {
    throw Exception(rc, wxERRMSG_BIND_POINTER);
  }
}

void Statement::BindDate(int paramIndex, const wxDateTime& date)
{
  if (date.IsValid())
  {
    Bind(paramIndex, date.FormatISODate());
  }
  else
  {
    throw Exception(WXSQLITE_ERROR, wxERRMSG_BIND_DATETIME);
  }
}

void Statement::BindTime(int paramIndex, const wxDateTime& time)
{
  if (time.IsValid())
  {
    Bind(paramIndex, time.FormatISOTime());
  }
  else
  {
    throw Exception(WXSQLITE_ERROR, wxERRMSG_BIND_DATETIME);
  }
}

void Statement::BindDateTime(int paramIndex, const wxDateTime& datetime)
{
  if (datetime.IsValid())
  {
    Bind(paramIndex, datetime.Format(wxS("%Y-%m-%d %H:%M:%S")));
  }
  else
  {
    throw Exception(WXSQLITE_ERROR, wxERRMSG_BIND_DATETIME);
  }
}

void Statement::BindTimestamp(int paramIndex, const wxDateTime& timestamp)
{
  if (timestamp.IsValid())
  {
    Bind(paramIndex, timestamp.Format(wxS("%Y-%m-%d %H:%M:%S.%l")));
  }
  else
  {
    throw Exception(WXSQLITE_ERROR, wxERRMSG_BIND_DATETIME);
  }
}

void Statement::BindNumericDateTime(int paramIndex, const wxDateTime& datetime)
{
  if (datetime.IsValid())
  {
    Bind(paramIndex, datetime.GetValue());
  }
  else
  {
    throw Exception(WXSQLITE_ERROR, wxERRMSG_BIND_DATETIME);
  }
}

void Statement::BindUnixDateTime(int paramIndex, const wxDateTime& datetime)
{
  if (datetime.IsValid())
  {
    wxLongLong ticks = datetime.GetTicks();
    Bind(paramIndex, ticks);
  }
  else
  {
    throw Exception(WXSQLITE_ERROR, wxERRMSG_BIND_DATETIME);
  }
}

void Statement::BindJulianDayNumber(int paramIndex, const wxDateTime& datetime)
{
  if (datetime.IsValid())
  {
    Bind(paramIndex, datetime.GetJulianDayNumber());
  }
  else
  {
    throw Exception(WXSQLITE_ERROR, wxERRMSG_BIND_DATETIME);
  }
}

void Statement::BindBool(int paramIndex, bool value)
{
  Bind(paramIndex, value ? 1 : 0);
}

void Statement::BindNull(int paramIndex)
{
  CheckStmt();
  int rc = sqlite3_bind_null(m_stmt->Get(), paramIndex);

  if (rc != SQLITE_OK)
  {
    throw Exception(rc, wxERRMSG_BIND_NULL);
  }
}

void Statement::BindZeroBlob(int paramIndex, int blobSize)
{
  CheckStmt();
  int rc = sqlite3_bind_zeroblob(m_stmt->Get(), paramIndex, blobSize);
  if (rc != SQLITE_OK)
  {
    throw Exception(rc, wxERRMSG_BIND_ZEROBLOB);
  }
}

void Statement::ClearBindings()
{
  CheckStmt();
#if 0 // missing in SQLite DLL
  int rc = sqlite3_clear_bindings(m_stmt->Get());

  if (rc != SQLITE_OK)
  {
    throw Exception(rc, wxERRMSG_BIND_CLEAR);
  }
#else
  for (int paramIndex = 1; paramIndex <= GetParamCount(); paramIndex++)
  {
    BindNull(paramIndex);
  }
#endif
}

wxString Statement::GetSQL() const
{
  wxString sqlString = wxEmptyString;
  CheckStmt();
  const char* sqlLocal = sqlite3_sql(m_stmt->Get());
  if (sqlLocal != nullptr) sqlString = wxString::FromUTF8(sqlLocal);
  return sqlString;
}

wxString Statement::GetExpandedSQL() const
{
  wxString sqlString = wxEmptyString;
  CheckStmt();
  char* sqlLocal = sqlite3_expanded_sql(m_stmt->Get());
  if (sqlLocal != nullptr)
  {
    sqlString = wxString::FromUTF8(sqlLocal);
    sqlite3_free(sqlLocal);
  }
  return sqlString;
}

void Statement::Reset()
{
  if (m_stmt != nullptr && m_stmt->Get() != nullptr)
  {
    int rc = sqlite3_reset(m_stmt->Get());

    if (rc != SQLITE_OK)
    {
      const char* localError = GetLastErrorMessage(m_db->Get());
      throw Exception(rc, wxString::FromUTF8(localError));
    }
  }
}

bool Statement::IsReadOnly() const
{
  CheckStmt();
  return sqlite3_stmt_readonly(m_stmt->Get()) != 0;
}

void Statement::Finalize()
{
  if (m_stmt != nullptr)
  {
    int rc = m_stmt->Finalize();
    if (rc != SQLITE_OK)
    {
      if (m_db != nullptr && m_db->Get() != nullptr)
      {
        const char* localError = GetLastErrorMessage(m_db->Get());
        throw Exception(rc, wxString::FromUTF8(localError));
      }
      else
      {
        throw Exception(rc, wxERRMSG_FINALIZE_FAILED);
      }
    }
  }
  m_stmt.reset();
  m_db.reset();
}

bool Statement::IsOk() const
{
  return (m_db != 0) && (m_stmt != 0);
}

bool Statement::IsBusy() const
{
  CheckStmt();
  int rc = sqlite3_stmt_busy(m_stmt->Get());
  return (rc != 0);
}

int Statement::Status(StatementStatus opCode, bool resetFlag) const
{
  int count = 0;
  CheckStmt();
  count = sqlite3_stmt_status(m_stmt->Get(), static_cast<int>(opCode), (resetFlag) ? 1 : 0 );
  return count;
}

void Statement::CheckDatabase() const
{
  if (m_db == nullptr || m_db->Get() == nullptr)
  {
    throw Exception(WXSQLITE_ERROR, wxERRMSG_NODB);
  }
}

void Statement::CheckStmt() const
{
  if (m_stmt == nullptr || m_stmt->Get() == nullptr)
  {
    throw Exception(WXSQLITE_ERROR, wxERRMSG_NOSTMT);
  }
}

//

Blob::Blob()
{
  m_db   = nullptr;
  m_blob = nullptr;
  m_writable = false;
}

Blob::Blob(DatabaseHandlePtr db, BlobHandlePtr blob, bool writable)
{
  m_db   = db;
  m_blob = blob;
  m_writable = writable;
}

Blob::~Blob()
{
  m_blob.reset();
  m_db.reset();
}

wxMemoryBuffer& Blob::Read(wxMemoryBuffer& blobValue, int length, int offset) const
{
  CheckBlob();
  char* localBuffer = static_cast<char*>(blobValue.GetAppendBuf(static_cast<size_t>(length)));
  int rc = sqlite3_blob_read(m_blob->Get(), localBuffer, length, offset);

  if (rc != SQLITE_OK)
  {
    const char* localError = GetLastErrorMessage(m_db->Get());
    throw Exception(rc, wxString::FromUTF8(localError));
  }

  blobValue.UngetAppendBuf((size_t) length);
  return blobValue;
}

void Blob::Write(const wxMemoryBuffer& blobValue, int offset)
{
  CheckBlob();
  if (m_writable)
  {
    int blobLen = static_cast<int>(blobValue.GetDataLen());
    int rc = sqlite3_blob_write(m_blob->Get(),
                                static_cast<const void*>(blobValue.GetData()), blobLen, offset);

    if (rc != SQLITE_OK)
    {
      const char* localError = GetLastErrorMessage(m_db->Get());
      throw Exception(rc, wxString::FromUTF8(localError));
    }
  }
  else
  {
    throw Exception(WXSQLITE_ERROR, wxERRMSG_INVALID_BLOB);
  }
}

bool Blob::IsOk() const
{
  return (m_blob != nullptr);
}

bool Blob::IsReadOnly() const
{
  return !m_writable;
}

int Blob::GetSize() const
{
  CheckBlob();
  return sqlite3_blob_bytes(m_blob->Get());
}

void Blob::Rebind(wxLongLong rowid)
{
  CheckBlob();
  int rc = sqlite3_blob_reopen(m_blob->Get(), rowid.GetValue());
  if (rc != SQLITE_OK)
  {
    const char* localError = GetLastErrorMessage(m_db->Get());
    throw Exception(rc, wxString::FromUTF8(localError));
  }
}

void Blob::Finalize()
{
  if (m_blob != nullptr)
  {
    int rc = m_blob->Finalize();
    if (rc != SQLITE_OK)
    {
      if (m_db != nullptr && m_db->Get() != nullptr)
      {
        const char* localError = GetLastErrorMessage(m_db->Get());
        throw Exception(rc, wxString::FromUTF8(localError));
      }
      else
      {
        throw Exception(rc, wxERRMSG_FINALIZE_FAILED);
      }
    }
  }
}

void Blob::CheckBlob() const
{
  if (m_db == nullptr || m_db->Get() == nullptr || m_blob == nullptr)
  {
    throw Exception(WXSQLITE_ERROR, wxERRMSG_INVALID_BLOB);
  }
}

// ----------------------------------------------------------------------------
// Database: class holding a SQLite3 database object
// ----------------------------------------------------------------------------

bool Database::ms_sharedCacheEnabled = false;

void
Database::SetSharedCache(bool enable)
{
  int flag = (enable) ? 1 : 0;
  int rc = sqlite3_enable_shared_cache(flag);
  if (rc != SQLITE_OK)
  {
    throw Exception(rc, wxERRMSG_SHARED_CACHE);
  }
  ms_sharedCacheEnabled = enable;
}

bool Database::ms_hasEncryptionSupport = true;

#if SQLITE_ENABLE_COLUMN_METADATA
bool Database::ms_hasMetaDataSupport = true;
#else
bool Database::ms_hasMetaDataSupport = false;
#endif

#if WXSQLITE3_HAVE_LOAD_EXTENSION
bool Database::ms_hasLoadExtSupport = true;
#else
bool Database::ms_hasLoadExtSupport = false;
#endif

#if WXSQLITE3_USE_NAMED_COLLECTIONS
bool Database::ms_hasNamedCollectionSupport = true;
#else
bool Database::ms_hasNamedCollectionSupport = false;
#endif

bool Database::ms_hasIncrementalBlobSupport = true;

bool Database::ms_hasSavepointSupport = true;

bool Database::ms_hasBackupSupport = true;

bool Database::ms_hasWriteAheadLogSupport = true;

bool Database::ms_hasPointerParamsSupport = true;

bool
Database::HasEncryptionSupport()
{
  return ms_hasEncryptionSupport;
}

bool
Database::HasMetaDataSupport()
{
  return ms_hasMetaDataSupport;
}

bool
Database::HasLoadExtSupport()
{
  return ms_hasLoadExtSupport;
}

bool
Database::HasNamedCollectionSupport()
{
  return ms_hasNamedCollectionSupport;
}

bool
Database::HasIncrementalBlobSupport()
{
  return ms_hasIncrementalBlobSupport;
}

bool
Database::HasSavepointSupport()
{
  return ms_hasSavepointSupport;
}

bool
Database::HasBackupSupport()
{
  return ms_hasBackupSupport;
}

bool
Database::HasWriteAheadLogSupport()
{
  return ms_hasWriteAheadLogSupport;
}

bool
Database::HasPointerParamsSupport()
{
  return ms_hasPointerParamsSupport;
}

Database::Database()
{
  m_db = 0;
  m_isOpen = false;
  m_busyTimeoutMs = 60000; // 60 seconds
  m_isEncrypted = false;
  m_lastRollbackRC = 0;
  m_backupPageCount = 10;
}

Database::Database(const Database& db)
{
  m_db = db.m_db;
  m_isOpen = db.m_isOpen;
  m_busyTimeoutMs = 60000; // 60 seconds
  m_isEncrypted = db.m_isEncrypted;
  m_lastRollbackRC = db.m_lastRollbackRC;
  m_backupPageCount = db.m_backupPageCount;
}

Database::~Database() noexcept
{
  m_db.reset();
}

Database& Database::operator=(const Database& db)
{
  if (this != &db)
  {
    m_db = db.m_db;
    if (m_db != nullptr)
    {
      m_isOpen = db.m_isOpen;
      m_busyTimeoutMs = 60000; // 60 seconds
      m_isEncrypted = db.m_isEncrypted;
      m_lastRollbackRC = db.m_lastRollbackRC;
      m_backupPageCount = db.m_backupPageCount;
    }

    if (m_db == nullptr)
    {
      throw Exception(WXSQLITE_ERROR, wxERRMSG_DBASSIGN_FAILED);
    }
  }
  return *this;
}

void Database::Open(const wxString& fileName, const wxString& key, int flags, const wxString& vfs)
{
  wxCharBuffer strLocalKey = key.ToUTF8();
  const char* localKey = strLocalKey;
  wxMemoryBuffer binaryKey;
  if (key.Length() > 0)
  {
    binaryKey.AppendData((void*) localKey, strlen(localKey));
  }
  Open(fileName, binaryKey, flags, vfs);
}

void Database::Open(const wxString& fileName, const wxMemoryBuffer& key, int flags, const wxString& vfs)
{
  wxCharBuffer strFileName = fileName.ToUTF8();
  const char* localFileName = strFileName;
  wxCharBuffer strVfs = vfs.ToUTF8();
  const char* localVfs = (!vfs.IsEmpty()) ? (const char*) strVfs : (const char*) nullptr;
  sqlite3* db;

  int rc = sqlite3_open_v2(localFileName, &db, flags, localVfs);

  if (rc != SQLITE_OK)
  {
    const char* localError = "Out of memory";
    if (db != nullptr)
    {
      localError = GetLastErrorMessage(db);
      sqlite3_close(db);
    }
    throw Exception(rc, wxString::FromUTF8(localError));
  }

  rc = sqlite3_extended_result_codes(db, 1);
  if (rc != SQLITE_OK)
  {
    const char* localError = GetLastErrorMessage(db);
    sqlite3_close(db);
    throw Exception(rc, wxString::FromUTF8(localError));
  }

  if (key.GetDataLen() > 0)
  {
    rc = sqlite3_key(db, key.GetData(), static_cast<int>(key.GetDataLen()));
    if (rc != SQLITE_OK)
    {
      const char* localError = GetLastErrorMessage(db);
      sqlite3_close(db);
      throw Exception(rc, wxString::FromUTF8(localError));
    }
    m_isEncrypted = true;
  }

  m_db = std::make_shared<DatabaseHandle>(db);
  m_isOpen = true;
  SetBusyTimeout(m_busyTimeoutMs);
}

void Database::Open(const wxString& fileName, const Cipher& cipher, const wxString& key, int flags, const wxString& vfs)
{
  wxCharBuffer strLocalKey = key.ToUTF8();
  const char* localKey = strLocalKey;
  wxMemoryBuffer binaryKey;
  if (key.Length() > 0)
  {
    binaryKey.AppendData((void*)localKey, strlen(localKey));
  }
  Open(fileName, cipher, binaryKey, flags, vfs);
}

void Database::Open(const wxString& fileName, const Cipher& cipher, const wxMemoryBuffer& key, int flags, const wxString& vfs)
{
  wxCharBuffer strFileName = fileName.ToUTF8();
  const char* localFileName = strFileName;
  wxCharBuffer strVfs = vfs.ToUTF8();
  const char* localVfs = (!vfs.IsEmpty()) ? (const char*) strVfs : (const char*) nullptr;
  sqlite3* db;

  int rc = sqlite3_open_v2((const char*) localFileName, &db, flags, localVfs);

  if (rc != SQLITE_OK)
  {
    const char* localError = "Out of memory";
    if (db != nullptr)
    {
      localError = GetLastErrorMessage(db);
      sqlite3_close(db);
    }
    throw Exception(rc, wxString::FromUTF8(localError));
  }

  rc = sqlite3_extended_result_codes(db, 1);
  if (rc != SQLITE_OK)
  {
    const char* localError = GetLastErrorMessage(db);
    sqlite3_close(db);
    throw Exception(rc, wxString::FromUTF8(localError));
  }

  if (cipher.IsOk())
  {
    if (!cipher.Apply(db))
    {
      throw Exception(WXSQLITE_ERROR, wxERRMSG_CIPHER_APPLY_FAILED);
    }
  }

  if (key.GetDataLen() > 0)
  {
    rc = sqlite3_key(db, key.GetData(), static_cast<int>(key.GetDataLen()));
    if (rc != SQLITE_OK)
    {
      const char* localError = GetLastErrorMessage(db);
      sqlite3_close(db);
      throw Exception(rc, wxString::FromUTF8(localError));
    }
    m_isEncrypted = true;
  }

  m_db = std::make_shared<DatabaseHandle>(db);
  m_isOpen = true;
  SetBusyTimeout(m_busyTimeoutMs);
}

bool Database::IsOpen() const
{
  return (m_db != nullptr && m_db->Get() != nullptr && m_isOpen);
}

bool Database::IsReadOnly(const wxString& databaseName) const
{
  CheckDatabase();
  wxCharBuffer strDatabaseName = databaseName.ToUTF8();
  const char* localDatabaseName = strDatabaseName;
  return sqlite3_db_readonly(m_db->Get(), localDatabaseName) > 0;
}

void Database::Close()
{
  CheckDatabase();
  m_db.reset();
  m_isEncrypted = false;
  m_isOpen = false;
}

void Database::AttachDatabase(const wxString& fileName, const wxString& schemaName)
{
  CheckDatabase();
  Statement attachStmt = PrepareStatement("ATTACH DATABASE ? AS ?");
  attachStmt.Bind(1, fileName);
  attachStmt.Bind(2, schemaName);
  int rc = attachStmt.ExecuteUpdate();
}

void Database::AttachDatabase(const wxString& fileName, const wxString& schemaName, const wxString& key)
{
  CheckDatabase();
  Statement attachStmt = PrepareStatement("ATTACH DATABASE ? AS ? KEY ?");
  attachStmt.Bind(1, fileName);
  attachStmt.Bind(2, schemaName);
  attachStmt.Bind(3, key);
  int rc = attachStmt.ExecuteUpdate();
}

void Database::AttachDatabase(const wxString& fileName, const wxString& schemaName, const Cipher& cipher, const wxString& key)
{
  CheckDatabase();
  if (cipher.IsOk())
  {
    if (!cipher.Apply(m_db->Get()))
    {
      throw Exception(WXSQLITE_ERROR, wxERRMSG_CIPHER_APPLY_FAILED);
    }
  }

  Statement attachStmt = PrepareStatement("ATTACH DATABASE ? AS ? KEY ?");
  attachStmt.Bind(1, fileName);
  attachStmt.Bind(2, schemaName);
  attachStmt.Bind(3, key);
  int rc = attachStmt.ExecuteUpdate();
}

void Database::DetachDatabase(const wxString& schemaName)
{
  Statement detachStmt = PrepareStatement("DETACH DATABASE ?");
  detachStmt.Bind(1, schemaName);
  int rc = detachStmt.ExecuteUpdate();
}

static bool
BackupRestoreCallback(int total, int remaining, BackupProgress* progressCallback)
{
  return progressCallback->Progress(total, remaining);
}

void Database::Backup(const wxString& targetFileName, const wxString& key, 
                      const wxString& sourceDatabaseName)
{
  Backup(nullptr, targetFileName, Cipher(), key, sourceDatabaseName);
}

void Database::Backup(const wxString& targetFileName, const Cipher& cipher, 
                               const wxString& key, const wxString& sourceDatabaseName)
{
  Backup(nullptr, targetFileName, cipher, key, sourceDatabaseName);
}

void Database::Backup(BackupProgress* progressCallback,
                      const wxString& targetFileName, const wxString& key,
                      const wxString& sourceDatabaseName)
{
  Backup(progressCallback, targetFileName, Cipher(), key, sourceDatabaseName);
}

void Database::Backup(BackupProgress* progressCallback, 
                      const wxString& targetFileName, const Cipher& cipher, 
                      const wxString& key, const wxString& sourceDatabaseName)
{
  wxCharBuffer strLocalKey = key.ToUTF8();
  const char* localKey = strLocalKey;
  wxMemoryBuffer binaryKey;
  if (key.Length() > 0)
  {
    binaryKey.AppendData((void*) localKey, strlen(localKey));
  }
  Backup(progressCallback, targetFileName, cipher, binaryKey, sourceDatabaseName);
}

void Database::Backup(const wxString& targetFileName, const wxMemoryBuffer& key, 
                      const wxString& sourceDatabaseName)
{
  Backup(nullptr, targetFileName, Cipher(), key, sourceDatabaseName);
}

void Database::Backup(const wxString& targetFileName, const Cipher& cipher, 
                               const wxMemoryBuffer& key, const wxString& sourceDatabaseName)
{
  Backup(nullptr, targetFileName, cipher, key, sourceDatabaseName);
}

void Database::Backup(BackupProgress* progressCallback, const wxString& targetFileName,
                      const wxMemoryBuffer& key, const wxString& sourceDatabaseName)
{
  Backup(progressCallback, targetFileName, Cipher(), key, sourceDatabaseName);
}

void Database::Backup(BackupProgress* progressCallback,
                      const wxString& targetFileName, const Cipher& cipher, 
                      const wxMemoryBuffer& key, const wxString& sourceDatabaseName)
{
  CheckDatabase();

  wxCharBuffer strFileName = targetFileName.ToUTF8();
  const char* localTargetFileName = strFileName;
  wxCharBuffer strDatabaseName = sourceDatabaseName.ToUTF8();
  const char* localSourceDatabaseName = strDatabaseName;

  sqlite3* pDest;
  sqlite3_backup* pBackup;
  int rc;
  rc = sqlite3_open(localTargetFileName, &pDest);
  if (rc != SQLITE_OK)
  {
    sqlite3_close(pDest);
    throw Exception(rc, wxERRMSG_DBOPEN_FAILED);
  }

  if (key.GetDataLen() > 0)
  {
    if (cipher.IsOk())
    {
      if (!cipher.Apply(pDest))
      {
        throw Exception(WXSQLITE_ERROR, wxERRMSG_CIPHER_APPLY_FAILED);
      }
    }
    rc = sqlite3_key(pDest, key.GetData(), static_cast<int>(key.GetDataLen()));
    if (rc != SQLITE_OK)
    {
      const char* localError = GetLastErrorMessage(pDest);
      sqlite3_close(pDest);
      throw Exception(rc, wxString::FromUTF8(localError));
    }
  }

  pBackup = sqlite3_backup_init(pDest, "main", m_db->Get(), localSourceDatabaseName);
  if (pBackup == 0)
  {
    const char* localError = GetLastErrorMessage(pDest);
    sqlite3_close(pDest);
    throw Exception(rc, wxString::FromUTF8(localError));
  }

  do
  {
    rc = sqlite3_backup_step(pBackup, m_backupPageCount);
    if (progressCallback != nullptr)
    {
      if (!BackupRestoreCallback(sqlite3_backup_pagecount(pBackup),
                                 sqlite3_backup_remaining(pBackup),
                                 progressCallback))
      {
        rc = SQLITE_DONE;
      }
    }
    if (rc == SQLITE_BUSY || rc == SQLITE_LOCKED)
    {
      sqlite3_sleep(250);
    }
  }
  while (rc == SQLITE_OK || rc == SQLITE_BUSY || rc == SQLITE_LOCKED);

  sqlite3_backup_finish(pBackup);
  if (rc == SQLITE_DONE)
  {
    sqlite3_close(pDest);
  }
  else
  {
    const char* localError = GetLastErrorMessage(pDest);
    sqlite3_close(pDest);
    throw Exception(rc, wxString::FromUTF8(localError));
  }
}

void Database::Restore(const wxString& sourceFileName, const wxString& key, 
                                const wxString& targetDatabaseName)
{
  Restore(nullptr, sourceFileName, Cipher(), key, targetDatabaseName);
}

void Database::Restore(const wxString& sourceFileName, const Cipher& cipher,
                                const wxString& key, const wxString& targetDatabaseName)
{
  Restore(nullptr, sourceFileName, cipher, key, targetDatabaseName);
}

void Database::Restore(BackupProgress* progressCallback,
                       const wxString& sourceFileName, const wxString& key,
                       const wxString& targetDatabaseName)
{
  Restore(progressCallback, sourceFileName, Cipher(), key, targetDatabaseName);
}

void Database::Restore(BackupProgress* progressCallback,
                       const wxString& sourceFileName, const Cipher& cipher,
                       const wxString& key, const wxString& targetDatabaseName)
{
  wxCharBuffer strLocalKey = key.ToUTF8();
  const char* localKey = strLocalKey;
  wxMemoryBuffer binaryKey;
  if (key.Length() > 0)
  {
    binaryKey.AppendData((void*) localKey, strlen(localKey));
  }
  Restore(progressCallback, sourceFileName, cipher, binaryKey, targetDatabaseName);
}

void Database::Restore(const wxString& sourceFileName, const wxMemoryBuffer& key, 
                                const wxString& targetDatabaseName)
{
  Restore(nullptr, sourceFileName, Cipher(), key, targetDatabaseName);
}

void Database::Restore(BackupProgress* progressCallback, const wxString& sourceFileName,
                       const wxMemoryBuffer& key, const wxString& targetDatabaseName)
{
  Restore(progressCallback, sourceFileName, Cipher(), key, targetDatabaseName);
}

void Database::Restore(const wxString& sourceFileName, const Cipher& cipher,
                                const wxMemoryBuffer& key, const wxString& targetDatabaseName)
{
    Restore(nullptr, sourceFileName, cipher, key, targetDatabaseName);
}

void Database::Restore(BackupProgress* progressCallback,
                       const wxString& sourceFileName, const Cipher& cipher,
                       const wxMemoryBuffer& key, const wxString& targetDatabaseName)
{
  CheckDatabase();

  wxCharBuffer strFileName = sourceFileName.ToUTF8();
  const char* localSourceFileName = strFileName;
  wxCharBuffer strDatabaseName = targetDatabaseName.ToUTF8();
  const char* localTargetDatabaseName = strDatabaseName;

  sqlite3* pSrc;
  sqlite3_backup* pBackup;
  int rc;
  int nTimeout = 0;

  rc = sqlite3_open(localSourceFileName, &pSrc);
  if (rc != SQLITE_OK)
  {
    sqlite3_close(pSrc);
    throw Exception(rc, wxERRMSG_DBOPEN_FAILED);
  }

  if (key.GetDataLen() > 0)
  {
    if (cipher.IsOk())
    {
      if (!cipher.Apply(pSrc))
      {
        throw Exception(WXSQLITE_ERROR, wxERRMSG_CIPHER_APPLY_FAILED);
      }
    }
    rc = sqlite3_key(pSrc, key.GetData(), static_cast<int>(key.GetDataLen()));
    if (rc != SQLITE_OK)
    {
      const char* localError = GetLastErrorMessage(pSrc);
      sqlite3_close(pSrc);
      throw Exception(rc, wxString::FromUTF8(localError));
    }
  }

  pBackup = sqlite3_backup_init(m_db->Get(), localTargetDatabaseName, pSrc, "main");
  if (pBackup == 0)
  {
    const char* localError = GetLastErrorMessage(m_db->Get());
    sqlite3_close(pSrc);
    throw Exception(rc, wxString::FromUTF8(localError));
  }

  do
  {
    rc = sqlite3_backup_step(pBackup, m_backupPageCount);
    if (progressCallback != nullptr)
    {
      if (!BackupRestoreCallback(sqlite3_backup_pagecount(pBackup),
                                 sqlite3_backup_remaining(pBackup), progressCallback))
      {
        rc = SQLITE_DONE;
      }
    }
    if (rc == SQLITE_BUSY || rc == SQLITE_LOCKED)
    {
      if (nTimeout++ >= 20) break;
      sqlite3_sleep(250);
    }
    else
    {
      nTimeout = 0;
    }
  }
  while (rc == SQLITE_OK || rc == SQLITE_BUSY || rc == SQLITE_LOCKED);

  sqlite3_backup_finish(pBackup);
  if (rc == SQLITE_DONE)
  {
    sqlite3_close(pSrc);
  }
  else if (rc == SQLITE_BUSY || rc == SQLITE_LOCKED)
  {
    sqlite3_close(pSrc);
    throw Exception(rc, wxERRMSG_SOURCEDB_BUSY);
  }
  else
  {
    const char* localError = GetLastErrorMessage(pSrc);
    sqlite3_close(pSrc);
    throw Exception(rc, wxString::FromUTF8(localError));
  }
}

void Database::SetBackupRestorePageCount(int pageCount)
{
  m_backupPageCount = pageCount;
}

void Database::Vacuum()
{
  ExecuteUpdate("vacuum");
}

void Database::Begin(TransactionType transactionType)
{
  wxString sql;
  switch (transactionType)
  {
    case TransactionType::TRANSACTION_DEFERRED:
      sql << wxS("begin deferred transaction");
      break;
    case TransactionType::TRANSACTION_IMMEDIATE:
      sql << wxS("begin immediate transaction");
      break;
    case TransactionType::TRANSACTION_EXCLUSIVE:
      sql << wxS("begin exclusive transaction");
      break;
    default:
      sql << wxS("begin transaction");
      break;
  }
  ExecuteUpdate(sql);
}

void Database::Commit()
{
  ExecuteUpdate("commit transaction");
}

void Database::Rollback(const wxString& savepointName)
{
  if (savepointName.IsEmpty())
  {
    ExecuteUpdate("rollback transaction");
  }
  else
  {
    wxString localSavepointName = savepointName;
    localSavepointName.Replace(wxString(wxS("\"")), wxString(wxS("\"\"")));
    ExecuteUpdate(wxString(wxS("rollback transaction to savepoint \""))+localSavepointName+wxString(wxS("\"")));
  }
}

bool Database::GetAutoCommit() const
{
  CheckDatabase();
  return sqlite3_get_autocommit(m_db->Get()) != 0;
}

int Database::QueryRollbackState() const
{
  return m_lastRollbackRC;
}

TransactionState Database::QueryTransactionState(const wxString& schemaName) const
{
  TransactionState state = TransactionState::TRANSACTION_NONE;
  int txnState;
  CheckDatabase();
  if (schemaName.IsEmpty())
  {
    txnState = sqlite3_txn_state(m_db->Get(), nullptr);
  }
  else
  {
    wxCharBuffer strSchema = schemaName.ToUTF8();
    const char* localSchema = strSchema;
    txnState = sqlite3_txn_state(m_db->Get(), localSchema);
  }
  if (txnState < 0)
  {
    throw Exception(WXSQLITE_ERROR, wxERRMSG_SCHEMANAME_UNKNOWN);
  }
  else
  {
    switch (txnState)
    {
      case SQLITE_TXN_READ:
        state = TransactionState::TRANSACTION_READ;
        break;
      case SQLITE_TXN_WRITE:
        state = TransactionState::TRANSACTION_WRITE;
        break;
      case SQLITE_TXN_NONE:
      default:
        state = TransactionState::TRANSACTION_NONE;
        break;
    }
  }
  return state;
}

void Database::Savepoint(const wxString& savepointName)
{
  wxString localSavepointName = savepointName;
  localSavepointName.Replace(wxString(wxS("\"")), wxString(wxS("\"\"")));
  ExecuteUpdate(wxString(wxS("savepoint \"")) + localSavepointName + wxString(wxS("\"")));
}

void Database::ReleaseSavepoint(const wxString& savepointName)
{
  wxString localSavepointName = savepointName;
  localSavepointName.Replace(wxString(wxS("\"")), wxString(wxS("\"\"")));
  ExecuteUpdate(wxString(wxS("release savepoint \"")) + localSavepointName + wxString(wxS("\"")));
}

Statement Database::PrepareStatement(const wxString& sql)
{
  wxCharBuffer strSql = sql.ToUTF8();
  const char* localSql = strSql;
  return PrepareStatement(localSql);
}

Statement Database::PrepareStatement(const StatementBuffer& sql)
{
  return PrepareStatement((const char*) sql);
}

Statement Database::PrepareStatement(const char* sql)
{
  CheckDatabase();
  sqlite3_stmt* stmt = (sqlite3_stmt*) Prepare(sql);
  StatementHandlePtr stmtHandle = std::make_shared<StatementHandle>(stmt);
  return Statement(m_db, stmtHandle);
}

Statement Database::PreparePersistentStatement(const wxString& sql)
{
  wxCharBuffer strSql = sql.ToUTF8();
  const char* localSql = strSql;
  return PreparePersistentStatement(localSql);
}

Statement Database::PreparePersistentStatement(const StatementBuffer& sql)
{
  return PreparePersistentStatement((const char*) sql);
}

Statement Database::PreparePersistentStatement(const char* sql)
{
  CheckDatabase();
  sqlite3_stmt* stmt = (sqlite3_stmt*) PreparePersistent(sql);
  StatementHandlePtr stmtHandle = std::make_shared<StatementHandle>(stmt);
  return Statement(m_db, stmtHandle);
}

bool Database::TableExists(const wxString& tableName, const wxString& databaseName)
{
  wxString sql;
  if (databaseName.IsEmpty())
  {
    sql = wxS("select count(*) from sqlite_schema where type='table' and name like ?");
  }
  else
  {
    sql = wxString(wxS("select count(*) from ")) + databaseName + wxString(wxS(".sqlite_schema where type='table' and name like ?"));
  }
  Statement stmt = PrepareStatement(sql);
  stmt.Bind(1, tableName);
  ResultSet resultSet = stmt.ExecuteQuery();
  long value = 0;
  resultSet.GetAsString(0).ToLong(&value);
  return (value > 0);
}

bool Database::TableExists(const wxString& tableName, wxArrayString& databaseNames)
{
  wxArrayString databaseList;
  GetDatabaseList(databaseList);

  bool found = false;
  size_t count = databaseList.GetCount();
  if (count > 0)
  {
    size_t j;
    for (j = 0; j < count; j++)
    {
      if (TableExists(tableName, databaseList.Item(j)))
      {
        found = true;
        databaseNames.Add(databaseList.Item(j));
      }
    }
  }
  return found;
}

void Database::GetDatabaseList(wxArrayString& databaseNames)
{
  databaseNames.Empty();
  ResultSet resultSet = ExecuteQuery("PRAGMA database_list;");
  while (resultSet.NextRow())
  {
    databaseNames.Add(resultSet.GetString(1));
  }
}

void Database::GetDatabaseList(wxArrayString& databaseNames, wxArrayString& databaseFiles)
{
  databaseNames.Empty();
  databaseFiles.Empty();
  ResultSet resultSet = ExecuteQuery("PRAGMA database_list;");
  while (resultSet.NextRow())
  {
    databaseNames.Add(resultSet.GetString(1));
    databaseFiles.Add(resultSet.GetString(2));
  }
}

wxString Database::GetDatabaseFilename(const wxString& databaseName)
{
  CheckDatabase();
  wxCharBuffer strDatabaseName = databaseName.ToUTF8();
  const char* localDatabaseName = strDatabaseName;
  const char* localFilename = sqlite3_db_filename(m_db->Get(), localDatabaseName);
  return wxString::FromUTF8(localFilename);
}

bool Database::EnableForeignKeySupport(bool enable)
{
  if (enable)
  {
    ExecuteUpdate("PRAGMA foreign_keys=ON;");
  }
  else
  {
    ExecuteUpdate("PRAGMA foreign_keys=OFF;");
  }
  bool enabled = IsForeignKeySupportEnabled();
  return (enable && enabled) || (!enable && !enabled);
}

bool Database::IsForeignKeySupportEnabled()
{
  bool enabled = false;
  ResultSet resultSet = ExecuteQuery("PRAGMA foreign_keys;");
  if (resultSet.NextRow())
  {
    enabled = (resultSet.GetInt(0) == 1);
  }
  return enabled;
}

JournalMode
Database::SetJournalMode(JournalMode journalMode, const wxString& database)
{
  wxString mode = ConvertJournalMode(journalMode);
  wxString query = wxS("PRAGMA ");
  if (!database.IsEmpty())
  {
    query += database;
    query += wxS(".");
  }
  query += wxS("journal_mode=");
  query += mode;
  query += wxS(";");
  ResultSet resultSet = ExecuteQuery(query);
  if (resultSet.NextRow())
  {
    mode = resultSet.GetString(0);
  }
  return ConvertJournalMode(mode);
}

JournalMode
Database::GetJournalMode(const wxString& database)
{
  wxString mode = wxS("DELETE");
  wxString query = wxS("PRAGMA ");
  if (!database.IsEmpty())
  {
    query += database;
    query += wxS(".");
  }
  query += wxS("journal_mode;");
  ResultSet resultSet = ExecuteQuery(query);
  if (resultSet.NextRow())
  {
    mode = resultSet.GetString(0);
  }
  return ConvertJournalMode(mode);
}

/* static */
wxString Database::ConvertJournalMode(JournalMode mode)
{
  wxString journalMode;
  if      (mode == JournalMode::JOURNALMODE_DELETE)   journalMode = wxS("DELETE");
  else if (mode == JournalMode::JOURNALMODE_PERSIST)  journalMode = wxS("PERSIST");
  else if (mode == JournalMode::JOURNALMODE_OFF)      journalMode = wxS("OFF");
  else if (mode == JournalMode::JOURNALMODE_TRUNCATE) journalMode = wxS("TRUNCATE");
  else if (mode == JournalMode::JOURNALMODE_MEMORY)   journalMode = wxS("MEMORY");
  else if (mode == JournalMode::JOURNALMODE_WAL)      journalMode = wxS("WAL");
  else                                                journalMode = wxS("DELETE");
  return journalMode;
}

/* static */
JournalMode Database::ConvertJournalMode(const wxString& mode)
{
  JournalMode journalMode;
  if      (mode.IsSameAs(wxS("DELETE"), false))   journalMode = JournalMode::JOURNALMODE_DELETE;
  else if (mode.IsSameAs(wxS("PERSIST"), false))  journalMode = JournalMode::JOURNALMODE_PERSIST;
  else if (mode.IsSameAs(wxS("OFF"), false))      journalMode = JournalMode::JOURNALMODE_OFF;
  else if (mode.IsSameAs(wxS("TRUNCATE"), false)) journalMode = JournalMode::JOURNALMODE_TRUNCATE;
  else if (mode.IsSameAs(wxS("MEMORY"), false))   journalMode = JournalMode::JOURNALMODE_MEMORY;
  else if (mode.IsSameAs(wxS("WAL"), false))      journalMode = JournalMode::JOURNALMODE_WAL;
  else                                            journalMode = JournalMode::JOURNALMODE_DELETE;
  return journalMode;
}

bool Database::CheckSyntax(const wxString& sql) const
{
  wxCharBuffer strSql = sql.ToUTF8();
  const char* localSql = strSql;
  return CheckSyntax(localSql);
}

bool Database::CheckSyntax(const StatementBuffer& sql) const
{
  return CheckSyntax((const char*) sql);
}

bool Database::CheckSyntax(const char* sql) const
{
  return sqlite3_complete(sql) != 0;
}

int Database::ExecuteUpdate(const wxString& sql)
{
  wxCharBuffer strSql = sql.ToUTF8();
  const char* localSql = strSql;
  return ExecuteUpdate(localSql);
}

int Database::ExecuteUpdate(const StatementBuffer& sql)
{
  return ExecuteUpdate((const char*) sql);
}

int Database::ExecuteUpdate(const char* sql, bool saveRC)
{
  CheckDatabase();

  char* localError = 0;

  int rc = sqlite3_exec(m_db->Get(), sql, 0, 0, &localError);
  if (saveRC)
  {
    if (strncmp(sql, "rollback transaction", 20) == 0)
    {
      m_lastRollbackRC = rc;
    }
  }

  if (rc == SQLITE_OK)
  {
    return sqlite3_changes(m_db->Get());
  }
  else
  {
    wxString errmsg = wxString::FromUTF8(localError);
    sqlite3_free(localError);
    throw Exception(rc, errmsg);
  }
}

ResultSet Database::ExecuteQuery(const wxString& sql)
{
  wxCharBuffer strSql = sql.ToUTF8();
  const char* localSql = strSql;
  return ExecuteQuery(localSql);
}

ResultSet Database::ExecuteQuery(const StatementBuffer& sql)
{
  return ExecuteQuery((const char*) sql);
}

ResultSet Database::ExecuteQuery(const char* sql)
{
  CheckDatabase();

  sqlite3_stmt* stmt = static_cast<sqlite3_stmt*>(Prepare(sql));

  int rc = sqlite3_step(stmt);

  if (rc == SQLITE_DONE) // no rows
  {
    StatementHandlePtr stmtHandle = std::make_shared<StatementHandle>(stmt);
    return ResultSet(m_db, stmtHandle, true /* eof */);
  }
  else if (rc == SQLITE_ROW) // one or more rows
  {
    StatementHandlePtr stmtHandle = std::make_shared<StatementHandle>(stmt);
    return ResultSet(m_db, stmtHandle, false /* eof */);
  }
  else
  {
    rc = sqlite3_finalize(stmt);
    const char* localError= GetLastErrorMessage(m_db->Get());
    throw Exception(rc, wxString::FromUTF8(localError));
  }
}

int Database::ExecuteScalar(const wxString& sql)
{
  wxCharBuffer strSql = sql.ToUTF8();
  const char* localSql = strSql;
  return ExecuteScalar(localSql);
}

int Database::ExecuteScalar(const StatementBuffer& sql)
{
  return ExecuteScalar((const char*) sql);
}

int Database::ExecuteScalar(const char* sql)
{
  ResultSet resultSet = ExecuteQuery(sql);

  if (resultSet.Eof() || resultSet.GetColumnCount() < 1)
  {
    throw Exception(WXSQLITE_ERROR, wxERRMSG_INVALID_QUERY);
  }

  long value = 0;
  resultSet.GetAsString(0).ToLong(&value);
  return static_cast<int>(value);
}

Table Database::GetTable(const wxString& sql)
{
  wxCharBuffer strSql = sql.ToUTF8();
  const char* localSql = strSql;
  return GetTable(localSql);
}

Table Database::GetTable(const StatementBuffer& sql)
{
  return GetTable((const char*) sql);
}

Table Database::GetTable(const char* sql)
{
  CheckDatabase();

  char* localError=0;
  char** results=0;
  int rc;
  int rows(0);
  int cols(0);

  rc = sqlite3_get_table(m_db->Get(), sql, &results, &rows, &cols, &localError);

  if (rc == SQLITE_OK)
  {
    return Table(results, rows, cols);
  }
  else
  {
    wxString errmsg = wxString::FromUTF8(localError);
    sqlite3_free(localError);
    throw Exception(rc, errmsg);
  }
}

wxLongLong Database::GetLastRowId() const
{
  CheckDatabase();
  return wxLongLong(sqlite3_last_insert_rowid(m_db->Get()));
}

Blob Database::GetReadOnlyBlob(wxLongLong rowId,
                               const wxString& columnName,
                               const wxString& tableName,
                               const wxString& dbName)
{
  return GetBlob(rowId, columnName, tableName, dbName, false);
}

Blob Database::GetWritableBlob(wxLongLong rowId,
                               const wxString& columnName,
                               const wxString& tableName,
                               const wxString& dbName)
{
  return GetBlob(rowId, columnName, tableName, dbName, true);
}

Blob Database::GetBlob(wxLongLong rowId,
                       const wxString& columnName,
                       const wxString& tableName,
                       const wxString& dbName,
                       bool writable)
{
  wxCharBuffer strColumnName = columnName.ToUTF8();
  const char* localColumnName = strColumnName;
  wxCharBuffer strTableName = tableName.ToUTF8();
  const char* localTableName = strTableName;
  wxCharBuffer strDbName = dbName.ToUTF8();
  const char* localDbName = (!dbName.IsEmpty()) ? (const char*) strDbName : (const char*) nullptr;
  int flags = (writable) ? 1 : 0;
  sqlite3_blob* blobHandle;
  CheckDatabase();
  int rc = sqlite3_blob_open(m_db->Get(), localDbName, localTableName, localColumnName, rowId.GetValue(), flags, &blobHandle);
  if (rc != SQLITE_OK)
  {
    const char* localError = GetLastErrorMessage(m_db->Get());
    throw Exception(rc, wxString::FromUTF8(localError));
  }
  BlobHandlePtr blobHandlePtr = std::make_shared<BlobHandle>(blobHandle);
  return Blob(m_db, blobHandlePtr, writable);
}

void Database::Interrupt()
{
  CheckDatabase();
  sqlite3_interrupt(m_db->Get());
}

bool Database::IsInterrupted()
{
  CheckDatabase();
  return (sqlite3_is_interrupted(m_db->Get()) != 0);
}

void Database::SetBusyTimeout(int nMillisecs)
{
  CheckDatabase();
  m_busyTimeoutMs = nMillisecs;
  sqlite3_busy_timeout(m_db->Get(), m_busyTimeoutMs);
}

void Database::SetLockTimeout(int nMillisecs, bool blockOnConnect)
{
#if SQLITE_VERSION_NUMBER >= 3050000
  CheckDatabase();
  int rc = sqlite3_setlk_timeout(m_db->Get(), nMillisecs, (blockOnConnect) ? 1 : 0);
  if (rc != SQLITE_OK)
  {
    const char* localError = GetLastErrorMessage(m_db->Get());
    throw Exception(rc, wxString::FromUTF8(localError));
  }
#else
  wxUnusedVar(nMillisecs);
  wxUnusedVar(blockOnConnect);
#endif
}

void Database::Configure(DbConfig cfgType, int cfgValue, int& cfgResult)
{
  CheckDatabase();
  int rc = SQLITE_ERROR;
  int localCfgType = static_cast<int>(cfgType);
  if (localCfgType >= SQLITE_DBCONFIG_ENABLE_FKEY && localCfgType <= SQLITE_DBCONFIG_ENABLE_COMMENTS)
  {
    rc = sqlite3_db_config(m_db->Get(), cfgType, cfgValue, &cfgResult);
    if (rc != SQLITE_OK)
    {
      const char* localError = GetLastErrorMessage(m_db->Get());
      throw Exception(rc, wxString::FromUTF8(localError));
    }
  }
  else
  {
    throw Exception(WXSQLITE_ERROR, wxERRMSG_DBCONFIG_OPTION_UNKNOWN);
  }
}

wxString Database::GetWrapperVersion()
{
  return wxString(wxSQLITE3_VERSION_STRING);
}

wxString Database::GetMCVersion()
{
    return wxString::FromUTF8(sqlite3mc_version());
}

wxString Database::GetVersion()
{
  return wxString::FromUTF8(sqlite3_libversion());
}

wxString Database::GetSourceId()
{
  return wxString::FromUTF8(sqlite3_sourceid());
}

bool Database::CompileOptionUsed(const wxString& optionName)
{
  wxCharBuffer strOption = optionName.ToUTF8();
  const char* localOption = strOption;
  return sqlite3_compileoption_used(localOption) == 1;
}

wxString Database::GetCompileOptionName(int optionIndex)
{
  const char* unknownOption = "";
  const char* optionName = sqlite3_compileoption_get(optionIndex);
  if (optionName == nullptr)
  {
    optionName = unknownOption;
  }
  return wxString::FromUTF8(optionName);
}

bool Database::CreateFunction(const wxString& funcName, int argCount, ScalarFunction& function, int functionFlags)
{
  CheckDatabase();
  wxCharBuffer strFuncName = funcName.ToUTF8();
  const char* localFuncName = strFuncName;
  int flags = SQLITE_UTF8;
  flags |= functionFlags;
  int rc = sqlite3_create_function(m_db->Get(), localFuncName, argCount,
                                   flags, &function,
                                   (void (*)(sqlite3_context*,int,sqlite3_value**)) FunctionContext::ExecScalarFunction, nullptr, nullptr);
  return rc == SQLITE_OK;
}

bool Database::CreateFunction(const wxString& funcName, int argCount, AggregateFunction& function, int functionFlags)
{
  CheckDatabase();
  wxCharBuffer strFuncName = funcName.ToUTF8();
  const char* localFuncName = strFuncName;
  int flags = SQLITE_UTF8;
  flags |= functionFlags;
  int rc = sqlite3_create_function(m_db->Get(), localFuncName, argCount,
                                   flags, &function,
                                   nullptr,
                                   (void (*)(sqlite3_context*,int,sqlite3_value**)) FunctionContext::ExecAggregateStep,
                                   (void (*)(sqlite3_context*)) FunctionContext::ExecAggregateFinalize);
  return rc == SQLITE_OK;
}

bool Database::CreateFunction(const wxString& funcName, int argCount, WindowFunction& function, int functionFlags)
{
  CheckDatabase();
  wxCharBuffer strFuncName = funcName.ToUTF8();
  const char* localFuncName = strFuncName;
  int flags = SQLITE_UTF8 | functionFlags;
  int rc = sqlite3_create_window_function(m_db->Get(), localFuncName, argCount,
                                          flags, &function,
                                          (void(*)(sqlite3_context*, int, sqlite3_value**)) FunctionContext::ExecWindowStep,
                                          (void(*)(sqlite3_context*)) FunctionContext::ExecWindowFinalize,
                                          (void(*)(sqlite3_context*)) FunctionContext::ExecWindowValue,
                                          (void(*)(sqlite3_context*, int, sqlite3_value**)) FunctionContext::ExecWindowInverse,
                                          nullptr);
  return rc == SQLITE_OK;
}

bool Database::SetAuthorizer(Authorizer& authorizer)
{
  CheckDatabase();
  int rc = sqlite3_set_authorizer(m_db->Get(), (sqlite3_xauth)FunctionContextExecAuthorizer, &authorizer);
  return rc == SQLITE_OK;
}

bool Database::RemoveAuthorizer()
{
  CheckDatabase();
  int rc = sqlite3_set_authorizer(m_db->Get(), (sqlite3_xauth) nullptr, nullptr);
  return rc == SQLITE_OK;
}

void Database::SetCommitHook(Hook* commitHook)
{
  CheckDatabase();
  if (commitHook)
  {
    sqlite3_commit_hook(m_db->Get(), (int(*)(void*)) FunctionContext::ExecCommitHook, commitHook);
  }
  else
  {
    sqlite3_commit_hook(m_db->Get(), (int(*)(void*)) nullptr, nullptr);
  }
}

void Database::SetRollbackHook(Hook* rollbackHook)
{
  CheckDatabase();
  if (rollbackHook)
  {
    sqlite3_rollback_hook(m_db->Get(), (void(*)(void*)) FunctionContext::ExecRollbackHook, rollbackHook);
  }
  else
  {
    sqlite3_rollback_hook(m_db->Get(), (void(*)(void*)) nullptr, nullptr);
  }
}

void Database::SetUpdateHook(Hook* updateHook)
{
  CheckDatabase();
  if (updateHook)
  {
    sqlite3_update_hook(m_db->Get(), (void(*)(void*, int, const char*, const char*, wxsqlite_int64)) FunctionContext::ExecUpdateHook, updateHook);
  }
  else
  {
    sqlite3_update_hook(m_db->Get(), (void(*)(void*, int, const char*, const char*, wxsqlite_int64)) nullptr, nullptr);
  }
}

void Database::SetWriteAheadLogHook(Hook* walHook)
{
  CheckDatabase();
  if (walHook)
  {
    walHook->SetDatabase(this);
    sqlite3_wal_hook(m_db->Get(), (int(*)(void*, sqlite3*, const char*, int)) FunctionContext::ExecWriteAheadLogHook, walHook);
  }
  else
  {
    sqlite3_wal_hook(m_db->Get(), (int(*)(void*, sqlite3*, const char*, int)) nullptr, nullptr);
  }
}

void Database::WriteAheadLogCheckpoint(const wxString& database, int mode, 
                                       int* logFrameCount, int* ckptFrameCount)
{
  CheckDatabase();
  wxCharBuffer strDatabase = database.ToUTF8();
  const char* localDatabase = strDatabase;
  int rc = sqlite3_wal_checkpoint_v2(m_db->Get(), localDatabase, mode, logFrameCount, ckptFrameCount);

  if (rc != SQLITE_OK)
  {
    const char* localError = GetLastErrorMessage(m_db->Get());
    throw Exception(rc, wxString::FromUTF8(localError));
  }
}

void Database::AutoWriteAheadLogCheckpoint(int frameCount)
{
  CheckDatabase();
  int rc = sqlite3_wal_autocheckpoint(m_db->Get(), frameCount);

  if (rc != SQLITE_OK)
  {
    const char* localError = GetLastErrorMessage(m_db->Get());
    throw Exception(rc, wxString::FromUTF8(localError));
  }
}

void Database::SetCollation(const wxString& collationName, Collation* collation)
{
  CheckDatabase();
  wxCharBuffer strCollationName = collationName.ToUTF8();
  const char* localCollationName = strCollationName;
  int rc;
  if (collation)
  {
    rc = sqlite3_create_collation(m_db->Get(), localCollationName, SQLITE_UTF8, collation, (int(*)(void*, int, const void*, int, const void*)) Database::ExecComparisonWithCollation);
  }
  else
  {
    rc = sqlite3_create_collation(m_db->Get(), localCollationName, SQLITE_UTF8, nullptr, (int(*)(void*, int, const void*, int, const void*)) nullptr);
  }
}

void* Database::GetDatabaseHandle() const
{
  return (m_db != nullptr) ? m_db->Get() : nullptr;
}

void Database::SetCollationNeededCallback()
{
  CheckDatabase();
  int rc = sqlite3_collation_needed(m_db->Get(), this, (void(*)(void*, sqlite3*, int, const char*)) Database::ExecCollationNeeded);
  if (rc != SQLITE_OK)
  {
    const char* localError = GetLastErrorMessage(m_db->Get());
    throw Exception(rc, wxString::FromUTF8(localError));
  }
}

void Database::CheckDatabase() const
{
  if (m_db == nullptr || m_db->Get() == nullptr || !m_isOpen)
  {
    throw Exception(WXSQLITE_ERROR, wxERRMSG_NODB);
  }
}

void* Database::Prepare(const char* sql)
{
  CheckDatabase();

  const char* tail=0;
  sqlite3_stmt* stmt;

  int rc = sqlite3_prepare_v2(m_db->Get(), sql, -1, &stmt, &tail);

  if (rc != SQLITE_OK)
  {
    const char* localError = GetLastErrorMessage(m_db->Get());
    throw Exception(rc, wxString::FromUTF8(localError));
  }

  return stmt;
}

void* Database::PreparePersistent(const char* sql)
{
  CheckDatabase();

  const char* tail = 0;
  sqlite3_stmt* stmt;

  int rc = sqlite3_prepare_v3(m_db->Get(), sql, -1, SQLITE_PREPARE_PERSISTENT, &stmt, &tail);

  if (rc != SQLITE_OK)
  {
    const char* localError = GetLastErrorMessage(m_db->Get());
    throw Exception(rc, wxString::FromUTF8(localError));
  }

  return stmt;
}

/* static */
int Database::ExecComparisonWithCollation(void* collation,
                                          int len1, const void* text1,
                                          int len2, const void* text2)
{
  wxString locText1 = wxString::FromUTF8((const char*) text1, (size_t) len1);
  wxString locText2 = wxString::FromUTF8((const char*) text2, (size_t) len2);
  return ((Collation*) collation)->Compare(locText1, locText2);
}

void Database::ExecCollationNeeded(void* db, void*, int, const char* collationName)
{
  wxString locCollation = wxString::FromUTF8((const char*) collationName);
  ((Database*) db)->SetNeededCollation(locCollation);
}

void Database::GetMetaData(const wxString& databaseName, const wxString& tableName, const wxString& columnName,
                           wxString* dataType, wxString* collation, bool* notNull, bool* primaryKey, bool* autoIncrement)
{
#if SQLITE_ENABLE_COLUMN_METADATA
  CheckDatabase();
  wxCharBuffer strDatabaseName = databaseName.ToUTF8();
  const char* localDatabaseName = strDatabaseName;
  if (databaseName == wxEmptyString) localDatabaseName = nullptr;
  wxCharBuffer strTableName = tableName.ToUTF8();
  const char* localTableName = strTableName;
  wxCharBuffer strColumnName = columnName.ToUTF8();
  const char* localColumnName = strColumnName;
  const char* localDataType;
  const char* localCollation;
  int localNotNull;
  int localPrimaryKey;
  int localAutoIncrement;
  int rc = sqlite3_table_column_metadata(m_db->Get(), localDatabaseName, localTableName, localColumnName,
                                         &localDataType, &localCollation, &localNotNull, &localPrimaryKey, &localAutoIncrement);

  if (rc != SQLITE_OK)
  {
    const char* localError = GetLastErrorMessage(m_db->Get());
    throw Exception(rc, wxString::FromUTF8(localError));
  }

  if (dataType      != nullptr) *dataType      = wxString::FromUTF8(localDataType);
  if (collation     != nullptr) *collation     = wxString::FromUTF8(localCollation);

  if (notNull       != nullptr) *notNull       = (localNotNull       != 0);
  if (primaryKey    != nullptr) *primaryKey    = (localPrimaryKey    != 0);
  if (autoIncrement != nullptr) *autoIncrement = (localAutoIncrement != 0);
#else
  wxUnusedVar(databaseName);
  wxUnusedVar(tableName);
  wxUnusedVar(columnName);
  wxUnusedVar(dataType);
  wxUnusedVar(collation);
  wxUnusedVar(notNull);
  wxUnusedVar(primaryKey);
  wxUnusedVar(autoIncrement);
  throw Exception(WXSQLITE_ERROR, wxERRMSG_NOMETADATA);
#endif
}

void Database::LoadExtension(const wxString& fileName, const wxString& entryPoint)
{
#if WXSQLITE3_HAVE_LOAD_EXTENSION
  CheckDatabase();
  wxCharBuffer strFileName = fileName.ToUTF8();
  const char* localFileName = strFileName;
  wxCharBuffer strEntryPoint = entryPoint.ToUTF8();
  const char* localEntryPoint = strEntryPoint;

  int rc = sqlite3_load_extension(m_db->Get(), localFileName, localEntryPoint, nullptr);
  if (rc != SQLITE_OK)
  {
    const char* localError = GetLastErrorMessage(m_db->Get());
    throw Exception(rc, wxString::FromUTF8(localError));
  }
#else
  wxUnusedVar(fileName);
  wxUnusedVar(entryPoint);
  throw Exception(WXSQLITE_ERROR, wxERRMSG_NOLOADEXT);
#endif
}

void Database::EnableLoadExtension(bool enable)
{
#if WXSQLITE3_HAVE_LOAD_EXTENSION
  CheckDatabase();
  int onoff = (enable) ? 1 : 0;
  int rc = sqlite3_enable_load_extension(m_db->Get(), onoff);
  if (rc != SQLITE_OK)
  {
    const char* localError = GetLastErrorMessage(m_db->Get());
    throw Exception(rc, wxString::FromUTF8(localError));
  }
#else
  wxUnusedVar(enable);
  throw Exception(WXSQLITE_ERROR, wxERRMSG_NOLOADEXT);
#endif
}

void Database::ReKey(const wxString& newKey)
{
  ReKey(Cipher(), newKey);
}

void Database::ReKey(const Cipher& cipher, const wxString& newKey)
{
  wxCharBuffer strLocalNewKey = newKey.ToUTF8();
  const char* localNewKey = strLocalNewKey;
  wxMemoryBuffer binaryNewKey;
  if (newKey.Length() > 0)
  {
    binaryNewKey.AppendData((void*) localNewKey, strlen(localNewKey));
  }
  ReKey(cipher, binaryNewKey);
}

void Database::ReKey(const wxMemoryBuffer& newKey)
{
  ReKey(Cipher(), newKey);
}

void Database::ReKey(const Cipher& cipher, const wxMemoryBuffer& newKey)
{
  CheckDatabase();
  if (cipher.IsOk())
  {
    if (!cipher.Apply(m_db->Get()))
    {
      throw Exception(WXSQLITE_ERROR, wxERRMSG_CIPHER_APPLY_FAILED);
    }
  }
  int rc = sqlite3_rekey(m_db->Get(), newKey.GetData(), static_cast<int>(newKey.GetDataLen()));
  if (rc != SQLITE_OK)
  {
    const char* localError = GetLastErrorMessage(m_db->Get());
    throw Exception(rc, wxString::FromUTF8(localError));
  }
}

wxString Database::GetKeySalt(const wxString& schemaName) const
{
  wxString keySalt = wxEmptyString;
  if (IsOpen())
  {
    const char* localSchemaName = nullptr;
    wxCharBuffer strSchema = schemaName.ToUTF8();
    if (!schemaName.IsEmpty())
    {
      localSchemaName = strSchema;
    }
    char* localKeySalt = reinterpret_cast<char*>(sqlite3mc_codec_data(m_db->Get(), localSchemaName, "cipher_salt"));
    if (localKeySalt != nullptr)
    {
      keySalt = wxString::FromUTF8(localKeySalt);
      sqlite3_free(localKeySalt);
    }
  }
  return keySalt;
}

int Database::GetLimit(LimitType id) const
{
  int value = -1;
  CheckDatabase();
  if (id >= LimitType::LIMIT_LENGTH && id <= LimitType::LIMIT_WORKER_THREADS)
  {
    value = sqlite3_limit(m_db->Get(), static_cast<int>(id), -1);
  }
  return value;
}

int Database::SetLimit(LimitType id, int newValue)
{
  int value = -1;
  CheckDatabase();
  if (id >= LimitType::LIMIT_LENGTH && id <= LimitType::LIMIT_WORKER_THREADS)
  {
    value = sqlite3_limit(m_db->Get(), static_cast<int>(id), newValue);
  }
  return value;
}

void Database::ReleaseMemory()
{
  CheckDatabase();
  int rc = sqlite3_db_release_memory(m_db->Get());
  if (rc != SQLITE_OK)
  {
    const char* localError = GetLastErrorMessage(m_db->Get());
    throw Exception(rc, wxString::FromUTF8(localError));
  }
}

int Database::GetSystemErrorCode() const
{
  int rc = 0;
  if (m_db != nullptr)
  {
    rc = sqlite3_system_errno(m_db->Get());
  }
  return rc;
}

#if wxCHECK_VERSION(2,9,0)
static const wxStringCharType* limitCodeString[] =
#else
static const wxChar* limitCodeString[] =
#endif
{ wxS("SQLITE_LIMIT_LENGTH"),              wxS("SQLITE_LIMIT_SQL_LENGTH"),
  wxS("SQLITE_LIMIT_COLUMN"),              wxS("SQLITE_LIMIT_EXPR_DEPTH"),
  wxS("SQLITE_LIMIT_COMPOUND_SELECT"),     wxS("SQLITE_LIMIT_VDBE_OP"),
  wxS("SQLITE_LIMIT_FUNCTION_ARG"),        wxS("SQLITE_LIMIT_ATTACHED"),
  wxS("SQLITE_LIMIT_LIKE_PATTERN_LENGTH"), wxS("SQLITE_LIMIT_VARIABLE_NUMBER"),
  wxS("SQLITE_LIMIT_TRIGGER_DEPTH"),       wxS("SQLITE_LIMIT_WORKER_THREADS"),
  wxS("SQLITE_LIMIT_PARSER_DEPTH")
};


/* static */
wxString Database::LimitTypeToString(LimitType type)
{
  wxString limitString(wxS("Unknown"));
  if (type >= LimitType::LIMIT_LENGTH && type <= LimitType::LIMIT_PARSER_DEPTH)
  {
    limitString = limitCodeString[static_cast<int>(type)];
  }
  return limitString;
}

/* static */
void Database::InitializeSQLite()
{
  int rc = sqlite3_initialize();
  if (rc != SQLITE_OK)
  {
    throw Exception(rc, wxERRMSG_INITIALIZE);
  }
}

/* static */
void Database::InitializeSQLite(const Logger& logger)
{
  int rc = sqlite3_config(SQLITE_CONFIG_LOG, Logger::ExecLoggerHook, &logger);
  if (rc == SQLITE_OK)
  {
    InitializeSQLite();
  }
  else
  {
    throw Exception(rc, wxERRMSG_INITIALIZE);
  }
}

/* static */
void Database::ShutdownSQLite()
{
  int rc = sqlite3_shutdown();
  if (rc != SQLITE_OK)
  {
    throw Exception(rc, wxERRMSG_SHUTDOWN);
  }
}

/* static */
bool Database::SetTemporaryDirectory(const wxString& tempDirectory)
{
  bool ok = false;
#if defined(__WXMSW__)
#if wxUSE_UNICODE
  const wxChar* zValue = tempDirectory.wc_str();
#else
  const wxWCharBuffer zValue = tempDirectory.wc_str(wxConvLocal);
#endif
  int rc = sqlite3_win32_set_directory(SQLITE_WIN32_TEMP_DIRECTORY_TYPE, (void*) zValue);
  ok = (rc == SQLITE_OK);
#endif
  return ok;
}

/* static */
bool Database::Randomness(int n, wxMemoryBuffer& random)
{
  bool ok = false;
  if (n > 0)
  {
    void* buffer = random.GetWriteBuf(n);
    sqlite3_randomness(n, buffer);
    random.UngetWriteBuf(n);
    ok = true;
  }
  return ok;
}

// ----------------------------------------------------------------------------
// FunctionContext: class providing the function context
//                  for user defined functions
// ----------------------------------------------------------------------------

int FunctionContext::GetArgCount() const
{
  return m_argc;
}

int FunctionContext::GetArgType(int argIndex) const
{
  if (argIndex >= 0 && argIndex < m_argc)
  {
    return sqlite3_value_type(static_cast<sqlite3_value*>(m_argv[argIndex]));
  }
  else
  {
    return SQLITE_NULL;
  }
}

bool FunctionContext::IsNull(int argIndex) const
{
  if (argIndex >= 0 && argIndex < m_argc)
  {
    return sqlite3_value_type(static_cast<sqlite3_value*>(m_argv[argIndex])) == SQLITE_NULL;
  }
  else
  {
    return true;
  }
}

int FunctionContext::GetInt(int argIndex, int nullValue) const
{
  if (argIndex >= 0 && argIndex < m_argc)
  {
    if (!IsNull(argIndex))
    {
      return sqlite3_value_int(static_cast<sqlite3_value*>(m_argv[argIndex]));
    }
    else
    {
      return nullValue;
    }
  }
  else
  {
    return nullValue;
  }
}

wxLongLong FunctionContext::GetInt64(int argIndex, wxLongLong nullValue) const
{
  if (argIndex >= 0 && argIndex < m_argc)
  {
    if (!IsNull(argIndex))
    {
      return wxLongLong(sqlite3_value_int64(static_cast<sqlite3_value*>(m_argv[argIndex])));
    }
    else
    {
      return nullValue;
    }
  }
  else
  {
    return nullValue;
  }
}

double FunctionContext::GetDouble(int argIndex, double nullValue) const
{
  if (argIndex >= 0 && argIndex < m_argc)
  {
    if (!IsNull(argIndex))
    {
      return sqlite3_value_double(static_cast<sqlite3_value*>(m_argv[argIndex]));
    }
    else
    {
      return nullValue;
    }
  }
  else
  {
    return nullValue;
  }
}

wxString FunctionContext::GetString(int argIndex, const wxString& nullValue) const
{
  if (argIndex >= 0 && argIndex < m_argc)
  {
    if (!IsNull(argIndex))
    {
      const char* localValue = reinterpret_cast<const char*>(sqlite3_value_text(static_cast<sqlite3_value*>(m_argv[argIndex])));
      return wxString::FromUTF8(localValue);
    }
    else
    {
      return nullValue;
    }
  }
  else
  {
    return nullValue;
  }
}

const unsigned char* FunctionContext::GetBlob(int argIndex, int& len) const
{
  const unsigned char* buffer = nullptr;
  if (argIndex >= 0 && argIndex < m_argc)
  {
    if (!IsNull(argIndex))
    {
      len = sqlite3_value_bytes((sqlite3_value*) m_argv[argIndex]);
      buffer = static_cast<const unsigned char*>(sqlite3_value_blob(static_cast<sqlite3_value*>(m_argv[argIndex])));
    }
  }
  return buffer;
}

wxMemoryBuffer& FunctionContext::GetBlob(int argIndex, wxMemoryBuffer& buffer) const
{
  if (argIndex >= 0 && argIndex < m_argc)
  {
    if (!IsNull(argIndex))
    {
      int len = sqlite3_value_bytes((sqlite3_value*) m_argv[argIndex]);
      const void* blob = sqlite3_value_blob(static_cast<sqlite3_value*>(m_argv[argIndex]));
      buffer.AppendData(blob, (size_t) len);
    }
  }
  return buffer;
}

void* FunctionContext::GetPointer(int argIndex, const wxString& pointerType) const
{
  void* pointer = nullptr;
  if (argIndex >= 0 && argIndex < m_argc)
  {
    if (!IsNull(argIndex))
    {
      wxCharBuffer strPointerType = pointerType.ToUTF8();
      const char* localPointerType = strPointerType;

      pointer = sqlite3_value_pointer(static_cast<sqlite3_value*>(m_argv[argIndex]), localPointerType);
    }
  }
  return pointer;
}

void FunctionContext::SetResult(int value)
{
  sqlite3_result_int(static_cast<sqlite3_context*>(m_ctx), value);
}

void FunctionContext::SetResult(wxLongLong value)
{
  sqlite3_result_int64(static_cast<sqlite3_context*>(m_ctx), value.GetValue());
}

void FunctionContext::SetResult(double value)
{
  sqlite3_result_double(static_cast<sqlite3_context*>(m_ctx), value);
}

void FunctionContext::SetResult(const wxString& value)
{
  wxCharBuffer strValue = value.ToUTF8();
  const char* localValue = strValue;
  sqlite3_result_text(static_cast<sqlite3_context*>(m_ctx), localValue, -1, SQLITE_TRANSIENT);
}

void FunctionContext::SetResult(unsigned char* value, int len)
{
  sqlite3_result_blob(static_cast<sqlite3_context*>(m_ctx), value, len, SQLITE_TRANSIENT);
}

void FunctionContext::SetResult(const wxMemoryBuffer& buffer)
{
  sqlite3_result_blob(static_cast<sqlite3_context*>(m_ctx), buffer.GetData(), static_cast<int>(buffer.GetDataLen()), SQLITE_TRANSIENT);
}

void FunctionContext::SetResult(void* pointer, const wxString& pointerType, void(*DeletePointer)(void*))
{
  const char* localPointerType = MakePointerTypeCopy(pointerType);
  sqlite3_result_pointer(static_cast<sqlite3_context*>(m_ctx), pointer, localPointerType, DeletePointer);
}

void FunctionContext::SetResultNull()
{
  sqlite3_result_null(static_cast<sqlite3_context*>(m_ctx));
}

void FunctionContext::SetResultZeroBlob(int blobSize)
{
  sqlite3_result_zeroblob(static_cast<sqlite3_context*>(m_ctx), blobSize);
}

void FunctionContext::SetResultArg(int argIndex)
{
  if (argIndex >= 0 && argIndex < m_argc) {
    sqlite3_result_value(static_cast<sqlite3_context*>(m_ctx), static_cast<sqlite3_value*>(m_argv[argIndex]));
  } else {
    sqlite3_result_null(static_cast<sqlite3_context*>(m_ctx));
  }
}

void FunctionContext::SetResultError(const wxString& errmsg)
{
  wxCharBuffer strErrmsg = errmsg.ToUTF8();
  const char* localErrmsg = strErrmsg;
  sqlite3_result_error(static_cast<sqlite3_context*>(m_ctx), localErrmsg, -1);
}

int FunctionContext::GetAggregateCount() const
{
  if (m_isAggregate)
  {
    return m_count;
  }
  else
  {
    return 0;
  }
}

void* FunctionContext::GetAggregateStruct(int len) const
{
  if (m_isAggregate)
  {
    return sqlite3_aggregate_context(static_cast<sqlite3_context*>(m_ctx), len);
  }
  else
  {
    return nullptr;
  }
}

/* static */
void FunctionContext::ExecScalarFunction(void* ctx, int argc, void** argv)
{
  FunctionContext context(ctx, false, argc, argv);
  ScalarFunction* func = static_cast<ScalarFunction*>(sqlite3_user_data(static_cast<sqlite3_context*>(ctx)));
  func->Execute(context);
}

/* static */
void FunctionContext::ExecAggregateStep(void* ctx, int argc, void** argv)
{
  FunctionContext context(ctx, true, argc, argv);
  AggregateFunction* func = static_cast<AggregateFunction*>(sqlite3_user_data(static_cast<sqlite3_context*>(ctx)));
  func->IncrementCount();
  context.m_count = func->GetCount();
  func->Aggregate(context);
}

/* static */
void FunctionContext::ExecAggregateFinalize(void* ctx)
{
  FunctionContext context(ctx, true, 0, nullptr);
  AggregateFunction* func = static_cast<AggregateFunction*>(sqlite3_user_data(static_cast<sqlite3_context*>(ctx)));
  context.m_count = func->GetCount();
  func->Finalize(context);
}

/* static */
void FunctionContext::ExecWindowStep(void* ctx, int argc, void** argv)
{
  FunctionContext context(ctx, true, argc, argv);
  WindowFunction* func = static_cast<WindowFunction*>(sqlite3_user_data(static_cast<sqlite3_context*>(ctx)));
  func->IncrementCount();
  context.m_count = func->GetCount();
  func->Aggregate(context);
}

/* static */
void FunctionContext::ExecWindowFinalize(void* ctx)
{
  FunctionContext context(ctx, true, 0, nullptr);
  WindowFunction* func = static_cast<WindowFunction*>(sqlite3_user_data(static_cast<sqlite3_context*>(ctx)));
  context.m_count = func->GetCount();
  func->Finalize(context);
}

/* static */
void FunctionContext::ExecWindowValue(void* ctx)
{
  FunctionContext context(ctx, true, 0, nullptr);
  WindowFunction* func = static_cast<WindowFunction*>(sqlite3_user_data(static_cast<sqlite3_context*>(ctx)));
  context.m_count = func->GetCount();
  func->CurrentValue(context);
}

/* static */
void FunctionContext::ExecWindowInverse(void* ctx, int argc, void** argv)
{
  FunctionContext context(ctx, true, argc, argv);
  WindowFunction* func = static_cast<WindowFunction*>(sqlite3_user_data(static_cast<sqlite3_context*>(ctx)));
  func->DecrementCount();
  context.m_count = func->GetCount();
  func->Reverse(context);
}

// 
static int FunctionContextExecAuthorizer(void* func, int type,
                                         const char* arg1, const char* arg2,
                                         const char* arg3, const char* arg4
                                        )
{
  wxString locArg1 = (arg1 != nullptr) ? wxString::FromUTF8(arg1) : wxString();
  wxString locArg2 = (arg2 != nullptr) ? wxString::FromUTF8(arg2) : wxString();
  wxString locArg3 = (arg3 != nullptr) ? wxString::FromUTF8(arg3) : wxString();
  wxString locArg4 = (arg4 != nullptr) ? wxString::FromUTF8(arg4) : wxString();
  wxString locArg5 = wxEmptyString;
  AuthorizationCode localType = static_cast<AuthorizationCode>(type);
  return static_cast<int>((static_cast<Authorizer*>(func))->Authorize(localType, locArg1, locArg2, locArg3, locArg4, locArg5));
}

/* static */
int FunctionContext::ExecCommitHook(void* hook)
{
  return static_cast<int>(((Hook*) hook)->CommitCallback());
}

/* static */
void FunctionContext::ExecRollbackHook(void* hook)
{
  ((Hook*) hook)->RollbackCallback();
}

/* static */
void FunctionContext::ExecUpdateHook(void* hook, int type,
                                     const char* database, const char* table,
                                     wxsqlite_int64 rowid)
{
  wxString locDatabase = wxString::FromUTF8(database);
  wxString locTable = wxString::FromUTF8(table);
  AuthorizationCode locType = static_cast<AuthorizationCode>(type);
  wxLongLong locRowid = rowid;
  ((Hook*) hook)->UpdateCallback(locType, locDatabase, locTable, locRowid);
}

FunctionContext::FunctionContext(void* ctx, bool isAggregate, int argc, void** argv)
  : m_ctx(ctx), m_isAggregate(isAggregate), m_count(0), m_argc(argc), m_argv(argv), m_ptrTypes(nullptr)
{
}

FunctionContext::~FunctionContext()
{
  if (m_ptrTypes != nullptr)
  {
    size_t n = m_ptrTypes->GetCount();
    for (size_t j = 0; j < n; ++j)
    {
      sqlite3_free((*m_ptrTypes)[j]);
    }
    delete m_ptrTypes;
  }
}

const char* FunctionContext::MakePointerTypeCopy(const wxString& pointerType)
{
  // Allocate pointer type array if necessary
  if (m_ptrTypes == nullptr)
  {
    m_ptrTypes = new wxArrayPtrVoid();
  }

  // Convert pointer type to char*
  return LocalMakePointerTypeCopy(*m_ptrTypes, pointerType);
}

/* static */
int FunctionContext::ExecWriteAheadLogHook(void* hook, void* dbHandle,
                                           const char* database, int numPages)
{
  wxString locDatabase = wxString::FromUTF8(database);
  wxUnusedVar(dbHandle);
  return static_cast<int>((static_cast<Hook*>(hook))->WriteAheadLogCallback(locDatabase, numPages));
}

#if wxCHECK_VERSION(2,9,0)
static const wxStringCharType* authCodeString[] =
#else
static const wxChar* authCodeString[] =
#endif
{ wxS("SQLITE_COPY"),              wxS("SQLITE_CREATE_INDEX"),      wxS("SQLITE_CREATE_TABLE"),
  wxS("SQLITE_CREATE_TEMP_INDEX"), wxS("SQLITE_CREATE_TEMP_TABLE"), wxS("SQLITE_CREATE_TEMP_TRIGGER"),
  wxS("SQLITE_CREATE_TEMP_VIEW"),  wxS("SQLITE_CREATE_TRIGGER"),    wxS("SQLITE_CREATE_VIEW"),
  wxS("SQLITE_DELETE"),            wxS("SQLITE_DROP_INDEX"),        wxS("SQLITE_DROP_TABLE"),
  wxS("SQLITE_DROP_TEMP_INDEX"),   wxS("SQLITE_DROP_TEMP_TABLE"),   wxS("SQLITE_DROP_TEMP_TRIGGER"),
  wxS("SQLITE_DROP_TEMP_VIEW"),    wxS("SQLITE_DROP_TRIGGER"),      wxS("SQLITE_DROP_VIEW"),
  wxS("SQLITE_INSERT"),            wxS("SQLITE_PRAGMA"),            wxS("SQLITE_READ"),
  wxS("SQLITE_SELECT"),            wxS("SQLITE_TRANSACTION"),       wxS("SQLITE_UPDATE"),
  wxS("SQLITE_ATTACH"),            wxS("SQLITE_DETACH"),            wxS("SQLITE_ALTER_TABLE"),
  wxS("SQLITE_REINDEX"),           wxS("SQLITE_ANALYZE"),           wxS("SQLITE_CREATE_VTABLE"),
  wxS("SQLITE_DROP_VTABLE"),       wxS("SQLITE_FUNCTION"),          wxS("SQLITE_SAVEPOINT"),
  wxS("SQLITE_RECURSIVE")
};


/* static */
wxString Authorizer::AuthorizationCodeToString(AuthorizationCode type)
{
  wxString authString(wxS("Unknown"));
  if (type >= AUTH_COPY && type <= AUTH_MAX_CODE)
  {
    authString = authCodeString[type];
  }
  return authString;
}

// ----------------------------------------------------------------------------
// Transaction
// ----------------------------------------------------------------------------

Transaction::Transaction(Database* db, TransactionType transactionType)
{
  wxASSERT(db != nullptr);
  m_database = db;
  try
  {
    m_database->Begin(transactionType);
  }
  catch (...)
  {
    m_database = nullptr; // Flag that transaction is not active
  }
}

Transaction::~Transaction()
{
  if (m_database != nullptr)
  {
    try
    {
      m_database->Rollback();
    }
    catch (...)
    {
      // Intentionally do nothing
    }
  }
}

void Transaction::Commit()
{
  m_database->Commit();
  m_database = nullptr;
}

void Transaction::Rollback()
{
  m_database->Rollback();
  m_database = nullptr;
}

// --- SQLite logging

Logger::Logger()
  : m_isActive(false)
{
}

Logger::~Logger()
{
}

void
Logger::HandleLogMessage(int errorCode, const wxString& errorMessage)
{
  if (m_isActive)
  {
#if wxCHECK_VERSION(2,9,0)
    wxLogInfo(wxS("SQLite3 %s (%d): %s"), Exception::ErrorCodeAsString(errorCode), errorCode, errorMessage);
#else
    wxLogInfo(wxS("SQLite3 %s (%d): %s"), Exception::ErrorCodeAsString(errorCode).c_str(), errorCode, errorMessage.c_str());
#endif
  }
}

/* static */
void
Logger::ExecLoggerHook(void* logger, int errorCode, const char* errorMsg)
{
  ((Logger*) logger)->HandleLogMessage(errorCode, wxString::FromUTF8(errorMsg));
}

// --- User defined function classes

#if wxUSE_REGEX

RegExpOperator::RegExpOperator(int flags) : m_flags(flags)
{
}

RegExpOperator::~RegExpOperator()
{
}

void RegExpOperator::Execute(FunctionContext& ctx)
{
  int argCount = ctx.GetArgCount();
  if (argCount == 2)
  {
    wxString exprStr = ctx.GetString(0);
    wxString textStr = ctx.GetString(1);
    if (!m_exprStr.IsSameAs(exprStr))
    {
      m_exprStr = exprStr;
      m_regEx.Compile(m_exprStr, m_flags);
    }
    if (m_regEx.IsValid())
    {
      int rc = (m_regEx.Matches(textStr)) ? 1 : 0;
      ctx.SetResult(rc);
    }
    else
    {
      ctx.SetResultError(wxString(_("Regular expression invalid: '"))+exprStr+_T("'."));
    }
  }
  else
  {
    ctx.SetResultError(wxString::Format(_("REGEXP called with wrong number of arguments: %d instead of 2."), argCount));
  }
}

#endif

// --- Support for named collections

#if WXSQLITE3_USE_NAMED_COLLECTIONS

// The following code is based on the SQLite test_intarray source code.

#include <string.h>
#include <assert.h>

/// Definition of the sqlite3_intarray object (internal)
struct sqlite3_intarray
{
  int n;                    // Number of elements in the array
  sqlite3_int64* a;         // Contents of the array
  void (*xFree)(void*);     // Function used to free a[]
};

// Objects used internally by the virtual table implementation
using intarray_vtab = struct intarray_vtab;
using intarray_cursor = struct intarray_cursor;

/// Definition of intarray table object (internal)
struct intarray_vtab
{
  sqlite3_vtab base;            // Base class
  sqlite3_intarray* pContent;   // Content of the integer array
};

/// Definition of  intarray cursor object (internal)
struct intarray_cursor
{
  sqlite3_vtab_cursor base;    // Base class
  int i;                       // Current cursor position
};

// Free an sqlite3_intarray object.
static void intarrayFree(sqlite3_intarray* p)
{
  if (p->a != nullptr && p->xFree)
  {
    p->xFree(p->a);
  }
  sqlite3_free(p);
}

// Table destructor for the intarray module.
static int intarrayDestroy(sqlite3_vtab* p)
{
  intarray_vtab* pVtab = (intarray_vtab*)p;
  sqlite3_free(pVtab);
  return 0;
}

// Table constructor for the intarray module.
static int intarrayCreate(sqlite3* db,                  // Database where module is created
                          void* pAux,                   // clientdata for the module
                          int /*argc*/,                 // Number of arguments
                          const char* const* /*argv*/,  // Value for all arguments
                          sqlite3_vtab** ppVtab,        // Write the new virtual table object here
                          char** /*pzErr*/)             // Put error message text here
{
  int rc = SQLITE_NOMEM;
  intarray_vtab* pVtab = (intarray_vtab*) sqlite3_malloc(sizeof(intarray_vtab));

  if (pVtab)
  {
    memset(pVtab, 0, sizeof(intarray_vtab));
    pVtab->pContent = static_cast<sqlite3_intarray*>(pAux);
    rc = sqlite3_declare_vtab(db, "CREATE TABLE x(value INTEGER PRIMARY KEY)");
  }
  *ppVtab = (sqlite3_vtab*)pVtab;
  return rc;
}

// Open a new cursor on the intarray table.
static int intarrayOpen(sqlite3_vtab* /*pVTab*/, sqlite3_vtab_cursor** ppCursor)
{
  int rc = SQLITE_NOMEM;
  intarray_cursor* pCur = static_cast<intarray_cursor*>(sqlite3_malloc(sizeof(intarray_cursor)));
  if (pCur)
  {
    memset(pCur, 0, sizeof(intarray_cursor));
    *ppCursor = reinterpret_cast<sqlite3_vtab_cursor*>(pCur);
    rc = SQLITE_OK;
  }
  return rc;
}

// Close a intarray table cursor.
static int intarrayClose(sqlite3_vtab_cursor* cur)
{
  intarray_cursor* pCur = reinterpret_cast<intarray_cursor*>(cur);
  sqlite3_free(pCur);
  return SQLITE_OK;
}

// Retrieve a column of data.
static int intarrayColumn(sqlite3_vtab_cursor* cur, sqlite3_context* ctx, int /*i*/)
{
  intarray_cursor* pCur = reinterpret_cast<intarray_cursor*>(cur);
  intarray_vtab* pVtab = reinterpret_cast<intarray_vtab*>(cur->pVtab);
  if (pCur->i >= 0 && pCur->i < pVtab->pContent->n)
  {
    sqlite3_result_int64(ctx, pVtab->pContent->a[pCur->i]);
  }
  return SQLITE_OK;
}

// Retrieve the current rowid.
static int intarrayRowid(sqlite3_vtab_cursor* cur, sqlite_int64* pRowid)
{
  intarray_cursor* pCur = reinterpret_cast<intarray_cursor*>(cur);
  *pRowid = pCur->i;
  return SQLITE_OK;
}

static int intarrayEof(sqlite3_vtab_cursor* cur)
{
  intarray_cursor* pCur = reinterpret_cast<intarray_cursor*>(cur);
  intarray_vtab* pVtab = reinterpret_cast<intarray_vtab*>(cur->pVtab);
  return pCur->i >= pVtab->pContent->n;
}

// Advance the cursor to the next row.
static int intarrayNext(sqlite3_vtab_cursor* cur)
{
  intarray_cursor* pCur = reinterpret_cast<intarray_cursor*>(cur);
  pCur->i++;
  return SQLITE_OK;
}

// Reset a intarray table cursor.
static int intarrayFilter(sqlite3_vtab_cursor* pVtabCursor,
                          int /*idxNum*/, const char* /*idxStr*/,
                          int /*argc*/, sqlite3_value** /*argv*/)
{
  intarray_cursor* pCur = reinterpret_cast<intarray_cursor*>(pVtabCursor);
  pCur->i = 0;
  return SQLITE_OK;
}

// Analyse the WHERE condition.
static int intarrayBestIndex(sqlite3_vtab* /*tab*/, sqlite3_index_info* /*pIdxInfo*/)
{
  return SQLITE_OK;
}

// Definition of a virtual table module for integer collections
static sqlite3_module intarrayModule =
{
  0,                           // iVersion
  intarrayCreate,              // xCreate - create a new virtual table
  intarrayCreate,              // xConnect - connect to an existing vtab
  intarrayBestIndex,           // xBestIndex - find the best query index
  intarrayDestroy,             // xDisconnect - disconnect a vtab
  intarrayDestroy,             // xDestroy - destroy a vtab
  intarrayOpen,                // xOpen - open a cursor
  intarrayClose,               // xClose - close a cursor
  intarrayFilter,              // xFilter - configure scan constraints
  intarrayNext,                // xNext - advance a cursor
  intarrayEof,                 // xEof
  intarrayColumn,              // xColumn - read data
  intarrayRowid,               // xRowid - read data
  0,                           // xUpdate
  0,                           // xBegin
  0,                           // xSync
  0,                           // xCommit
  0,                           // xRollback
  0,                           // xFindMethod
  0,                           // xRename
  0,                           // xSavepoint
  0,                           // xRelease
  0                            // xRollbackTo
};

/// Definition of the sqlite3_chararray object (internal)
struct sqlite3_chararray
{
  int n;                    // Number of elements in the array
  char** a;                 // Contents of the array
  void (*xFree)(void*);     // Function used to free a[]
};

// Objects used internally by the virtual table implementation
using chararray_vtab = struct chararray_vtab;
using chararray_cursor = struct chararray_cursor;

/// Definition of chararray table object (internal)
struct chararray_vtab
{
  sqlite3_vtab base;            // Base class
  sqlite3_chararray* pContent;  // Content of the char array
};

/// Definition of chararray cursor object (internal)
struct chararray_cursor
{
  sqlite3_vtab_cursor base;    // Base class
  int i;                       // Current cursor position
};

// Free an sqlite3_chararray object.
static void chararrayFree(sqlite3_chararray* p)
{
  if (p->a != nullptr && p->xFree)
  {
    int j;
    for (j = 0; j < p->n; ++j)
    {
      p->xFree(p->a[j]);
    }
    p->xFree(p->a);
  }
  sqlite3_free(p);
}

// Table destructor for the chararray module.
static int chararrayDestroy(sqlite3_vtab* p)
{
  chararray_vtab* pVtab = (chararray_vtab*)p;
  sqlite3_free(pVtab);
  return 0;
}

// Table constructor for the chararray module.
static int chararrayCreate(sqlite3* db,                  // Database where module is created
                           void* pAux,                   // clientdata for the module
                           int /*argc*/,                 // Number of arguments
                           const char* const* /*argv*/,  // Value for all arguments
                           sqlite3_vtab** ppVtab,        // Write the new virtual table object here
                           char** /*pzErr*/)             // Put error message text here
{
  int rc = SQLITE_NOMEM;
  chararray_vtab* pVtab = static_cast<chararray_vtab*>(sqlite3_malloc(sizeof(chararray_vtab)));

  if (pVtab)
  {
    memset(pVtab, 0, sizeof(chararray_vtab));
    pVtab->pContent = static_cast<sqlite3_chararray*>(pAux);
    rc = sqlite3_declare_vtab(db, "CREATE TABLE x(value CHAR PRIMARY KEY)");
  }
  *ppVtab = reinterpret_cast<sqlite3_vtab*>(pVtab);
  return rc;
}

// Open a new cursor on the chararray table.
static int chararrayOpen(sqlite3_vtab* /*pVTab*/, sqlite3_vtab_cursor** ppCursor)
{
  int rc = SQLITE_NOMEM;
  chararray_cursor* pCur = static_cast<chararray_cursor*>(sqlite3_malloc(sizeof(chararray_cursor)));
  if (pCur)
  {
    memset(pCur, 0, sizeof(chararray_cursor));
    *ppCursor = reinterpret_cast<sqlite3_vtab_cursor*>(pCur);
    rc = SQLITE_OK;
  }
  return rc;
}

// Close a chararray table cursor.
static int chararrayClose(sqlite3_vtab_cursor* cur)
{
  chararray_cursor* pCur = reinterpret_cast<chararray_cursor*>(cur);
  sqlite3_free(pCur);
  return SQLITE_OK;
}

// Retrieve a column of data.
static int chararrayColumn(sqlite3_vtab_cursor* cur, sqlite3_context* ctx, int /*i*/)
{
  chararray_cursor* pCur = reinterpret_cast<chararray_cursor*>(cur);
  chararray_vtab* pVtab = reinterpret_cast<chararray_vtab*>(cur->pVtab);
  if (pCur->i >= 0 && pCur->i < pVtab->pContent->n)
  {
    sqlite3_result_text(ctx, pVtab->pContent->a[pCur->i], -1, SQLITE_STATIC);
  }
  return SQLITE_OK;
}

// Retrieve the current rowid.
static int chararrayRowid(sqlite3_vtab_cursor* cur, sqlite_int64* pRowid)
{
  chararray_cursor* pCur = reinterpret_cast<chararray_cursor*>(cur);
  *pRowid = pCur->i;
  return SQLITE_OK;
}

static int chararrayEof(sqlite3_vtab_cursor* cur)
{
  chararray_cursor* pCur = reinterpret_cast<chararray_cursor*>(cur);
  chararray_vtab* pVtab = reinterpret_cast<chararray_vtab*>(cur->pVtab);
  return pCur->i >= pVtab->pContent->n;
}

// Advance the cursor to the next row.
static int chararrayNext(sqlite3_vtab_cursor* cur)
{
  chararray_cursor* pCur = reinterpret_cast<chararray_cursor*>(cur);
  pCur->i++;
  return SQLITE_OK;
}

// Reset a chararray table cursor.
static int chararrayFilter(sqlite3_vtab_cursor* pVtabCursor,
                           int /*idxNum*/, const char* /*idxStr*/,
                           int /*argc*/, sqlite3_value** /*argv*/)
{
  chararray_cursor *pCur = reinterpret_cast<chararray_cursor*>(pVtabCursor);
  pCur->i = 0;
  return SQLITE_OK;
}

// Analyse the WHERE condition.
static int chararrayBestIndex(sqlite3_vtab* /*tab*/, sqlite3_index_info* /*pIdxInfo*/)
{
  return SQLITE_OK;
}

// Definition of a virtual table module for string collections
static sqlite3_module chararrayModule =
{
  0,                           // iVersion
  chararrayCreate,             // xCreate - create a new virtual table
  chararrayCreate,             // xConnect - connect to an existing vtab
  chararrayBestIndex,          // xBestIndex - find the best query index
  chararrayDestroy,            // xDisconnect - disconnect a vtab
  chararrayDestroy,            // xDestroy - destroy a vtab
  chararrayOpen,               // xOpen - open a cursor
  chararrayClose,              // xClose - close a cursor
  chararrayFilter,             // xFilter - configure scan constraints
  chararrayNext,               // xNext - advance a cursor
  chararrayEof,                // xEof
  chararrayColumn,             // xColumn - read data
  chararrayRowid,              // xRowid - read data
  0,                           // xUpdate
  0,                           // xBegin
  0,                           // xSync
  0,                           // xCommit
  0,                           // xRollback
  0,                           // xFindMethod
  0,                           // xRename
  0,                           // xSavepoint
  0,                           // xRelease
  0                            // xRollbackTo
};

#endif // WXSQLITE3_USE_NAMED_COLLECTIONS

NamedCollection::NamedCollection(const wxString& collectionName, void* collectionData)
  : m_name(collectionName), m_data(collectionData)
{
}

NamedCollection::NamedCollection(const NamedCollection& collection)
  : m_name(collection.m_name), m_data(collection.m_data)
{
}

NamedCollection&
NamedCollection::operator=(const NamedCollection& collection)
{
  if (this != &collection)
  {
    m_name = collection.m_name;
    m_data = collection.m_data;
  }
  return *this;
}

NamedCollection::~NamedCollection()
{
}

IntegerCollection::IntegerCollection(const IntegerCollection& collection)
  : NamedCollection(collection)
{
}

IntegerCollection&
IntegerCollection::operator=(const IntegerCollection& collection)
{
  if (this != &collection)
  {
    NamedCollection::operator=(collection);
  }
  return *this;
}

IntegerCollection::IntegerCollection(const wxString& collectionName, void* collectionData)
  : NamedCollection(collectionName, collectionData)
{
}

IntegerCollection::~IntegerCollection()
{
}

void
IntegerCollection::Bind(const wxArrayInt& integerCollection)
{
  if (IsOk())
  {
    size_t n = integerCollection.Count();
    sqlite3_intarray* pIntArray = static_cast<sqlite3_intarray*>(m_data);
    if (pIntArray->a != nullptr && pIntArray->xFree)
    {
      pIntArray->xFree(pIntArray->a);
    }
    pIntArray->n = n;
    if (n > 0)
    {
      pIntArray->a = static_cast<sqlite3_int64*>(sqlite3_malloc(sizeof(sqlite3_int64)*n));
      pIntArray->xFree = sqlite3_free;
    }
    else
    {
      pIntArray->a = nullptr;
      pIntArray->xFree = nullptr;
    }

    size_t j;
    for (j = 0; j < n; ++j)
    {
      pIntArray->a[j] = integerCollection[j];
    }
  }
  else
  {
    throw Exception(WXSQLITE_ERROR, wxERRMSG_INVALID_COLLECTION);
  }
}

void
IntegerCollection::Bind(int n, int* integerCollection)
{
  if (IsOk())
  {
    sqlite3_intarray* pIntArray = static_cast<sqlite3_intarray*>(m_data);
    if (pIntArray->a != nullptr && pIntArray->xFree)
    {
      pIntArray->xFree(pIntArray->a);
    }
    pIntArray->n = n;
    if (n > 0)
    {
      pIntArray->a = static_cast<sqlite3_int64*>(sqlite3_malloc(sizeof(sqlite3_int64)*n));
      pIntArray->xFree = sqlite3_free;
    }
    else
    {
      pIntArray->a = nullptr;
      pIntArray->xFree = nullptr;
    }

    int j;
    for (j = 0; j < n; ++j)
    {
      pIntArray->a[j] = integerCollection[j];
    }
  }
  else
  {
    throw Exception(WXSQLITE_ERROR, wxERRMSG_INVALID_COLLECTION);
  }
}

IntegerCollection
Database::CreateIntegerCollection(const wxString& collectionName)
{
#if WXSQLITE3_USE_NAMED_COLLECTIONS
  CheckDatabase();
  int rc = SQLITE_OK;
  wxCharBuffer strCollectionName = collectionName.ToUTF8();
  const char* zName = strCollectionName;
  sqlite3_intarray* p = static_cast<sqlite3_intarray*>(sqlite3_malloc(sizeof(*p)));
  if (p == 0)
  {
    throw Exception(WXSQLITE_ERROR, wxERRMSG_NOMEM);
  }
  p->n = 0;
  p->a= nullptr;
  p->xFree = nullptr;
  rc = sqlite3_create_module_v2(m_db->Get(), zName, &intarrayModule, p, (void(*)(void*))intarrayFree);
  if (rc == SQLITE_OK)
  {
    StatementBuffer zBuffer;
    const char* zSql = zBuffer.Format("CREATE VIRTUAL TABLE temp.\"%w\" USING \"%w\"", zName, zName);
    rc = sqlite3_exec(m_db->Get(), zSql, 0, 0, 0);
  }
  if (rc != SQLITE_OK)
  {
    const char* localError = GetLastErrorMessage(m_db->Get());
    throw Exception(rc, wxString::FromUTF8(localError));
  }
  return IntegerCollection(collectionName, p);
#else
  wxUnusedVar(collectionName);
  throw Exception(WXSQLITE_ERROR, wxERRMSG_NOCOLLECTIONS);
#endif // WXSQLITE3_USE_NAMED_COLLECTIONS
}

StringCollection::StringCollection(const StringCollection& collection)
  : NamedCollection(collection)
{
}

StringCollection&
StringCollection::operator=(const StringCollection& collection)
{
  if (this != &collection)
  {
    NamedCollection::operator=(collection);
  }
  return *this;
}

StringCollection::StringCollection(const wxString& collectionName, void* collectionData)
  : NamedCollection(collectionName, collectionData)
{
}

StringCollection::~StringCollection()
{
}

void
StringCollection::Bind(const wxArrayString& stringCollection)
{
  if (IsOk())
  {
    size_t n = stringCollection.Count();
    sqlite3_chararray* pCharArray = static_cast<sqlite3_chararray*>(m_data);
    if (pCharArray->a != nullptr && pCharArray->xFree)
    {
      pCharArray->xFree(pCharArray->a);
    }
    pCharArray->n = n;
    if (n > 0)
    {
      pCharArray->a = static_cast<char**>(sqlite3_malloc(sizeof(char*)*n));
      pCharArray->xFree = sqlite3_free;
    }
    else
    {
      pCharArray->a = nullptr;
      pCharArray->xFree = nullptr;
    }

    size_t j;
    for (j = 0; j < n; ++j)
    {
      wxCharBuffer strValue = stringCollection[j].ToUTF8();
      const char* zValue = strValue;
      size_t k = strlen(zValue) + 1;
      pCharArray->a[j] = static_cast<char*>(sqlite3_malloc(sizeof(char)*k));
      strcpy(pCharArray->a[j], zValue);
    }
  }
  else
  {
    throw Exception(WXSQLITE_ERROR, wxERRMSG_INVALID_COLLECTION);
  }
}

StringCollection
Database::CreateStringCollection(const wxString& collectionName)
{
#if WXSQLITE3_USE_NAMED_COLLECTIONS
  CheckDatabase();
  int rc = SQLITE_OK;
  wxCharBuffer strCollectionName = collectionName.ToUTF8();
  const char* zName = strCollectionName;
  sqlite3_chararray* p = static_cast<sqlite3_chararray*>(sqlite3_malloc(sizeof(*p)));
  if (p == 0)
  {
    throw Exception(WXSQLITE_ERROR, wxERRMSG_NOMEM);
  }
  p->n = 0;
  p->a= nullptr;
  p->xFree = nullptr;
  rc = sqlite3_create_module_v2(m_db->Get(), zName, &chararrayModule, p, (void(*)(void*))chararrayFree);
  if (rc == SQLITE_OK)
  {
    StatementBuffer zBuffer;
    const char* zSql = zBuffer.Format("CREATE VIRTUAL TABLE temp.\"%w\" USING \"%w\"", zName, zName);
    rc = sqlite3_exec(m_db->Get(), zSql, 0, 0, 0);
  }
  if (rc != SQLITE_OK)
  {
    const char* localError = GetLastErrorMessage(m_db->Get());
    throw Exception(rc, wxString::FromUTF8(localError));
  }
  return StringCollection(collectionName, p);
#else
  wxUnusedVar(collectionName);
  throw Exception(WXSQLITE_ERROR, wxERRMSG_NOCOLLECTIONS);
#endif // WXSQLITE3_USE_NAMED_COLLECTIONS
}

// --- Cipher support ---

Cipher::Cipher()
  : m_initialized(false), m_cipherType(CipherType::UNKNOWN), m_legacyPageSize(0)
{
}

Cipher::Cipher(CipherType cipherType)
  : m_initialized(false), m_cipherType(cipherType), m_legacyPageSize(0)
{
}

Cipher::Cipher(const Cipher&  cipher)
  : m_initialized(cipher.m_initialized), m_cipherType(cipher.m_cipherType), m_legacyPageSize(cipher.m_legacyPageSize)
{
}

/// Destructor
Cipher::~Cipher()
{
}

bool
Cipher::InitializeFromGlobalDefault()
{
  return false;
}

bool
Cipher::InitializeFromCurrent(Database& db)
{
  return false;
}

bool
Cipher::InitializeFromCurrentDefault(Database& db)
{
  return false;
}

bool
Cipher::Apply(Database& db) const
{
  return false;
}

bool
Cipher::Apply(void* dbHandle) const
{
  return false;
}

void
Cipher::SetLegacyPageSize(int pageSize)
{
  if (pageSize >= 512 && pageSize <= 65536 && ((pageSize - 1) & pageSize) == 0)
  {
    m_legacyPageSize = pageSize;
  }
  else
  {
    m_legacyPageSize = 0;
  }
}

int
Cipher::GetLegacyPageSize() const
{
  return m_legacyPageSize;
}

CipherType
Cipher::GetCipherType() const
{
  return m_cipherType;
}

bool
Cipher::IsOk() const
{
  return (m_initialized && m_cipherType != CipherType::UNKNOWN);
}

const wxString
Cipher::GetCipherName(CipherType cipherType)
{
  wxString cipherName;
  switch (cipherType)
  {
    case CipherType::AES128:    cipherName = wxS("aes128cbc"); break;
    case CipherType::AES256:    cipherName = wxS("aes256cbc"); break;
    case CipherType::CHACHA20:  cipherName = wxS("chacha20");  break;
    case CipherType::SQLCIPHER: cipherName = wxS("sqlcipher"); break;
    case CipherType::RC4:       cipherName = wxS("rc4");       break;
    case CipherType::ASCON128:  cipherName = wxS("ascon128");  break;
    case CipherType::AEGIS:     cipherName = wxS("aegis");     break;
    default:                           cipherName = wxS("unknown");   break;
  }
  return cipherName;
}

CipherType
Cipher::GetCipherType(const wxString& cipherName)
{
  CipherType cipherType;
  if (cipherName.IsSameAs(wxS("aes128cbc"), false))      cipherType = CipherType::AES128;
  else if (cipherName.IsSameAs(wxS("aes256cbc"), false)) cipherType = CipherType::AES256;
  else if (cipherName.IsSameAs(wxS("chacha20"), false))  cipherType = CipherType::CHACHA20;
  else if (cipherName.IsSameAs(wxS("sqlcipher"), false)) cipherType = CipherType::SQLCIPHER;
  else if (cipherName.IsSameAs(wxS("rc4"), false))       cipherType = CipherType::RC4;
  else if (cipherName.IsSameAs(wxS("ascon128"), false))  cipherType = CipherType::ASCON128;
  else if (cipherName.IsSameAs(wxS("aegis"), false))     cipherType = CipherType::AEGIS;
  else                                                   cipherType = CipherType::UNKNOWN;
  return cipherType;
}

bool
Cipher::SetCipher(Database& db, CipherType cipherType)
{
  wxCharBuffer strCipherName = GetCipherName(cipherType).utf8_str();
  const char* cipherName = strCipherName;
  sqlite3* dbHandle = static_cast<sqlite3*>(GetDatabaseHandle(db));
  int newCipherType = (dbHandle != nullptr) ? sqlite3mc_config(dbHandle, "cipher", sqlite3mc_cipher_index(cipherName)) : static_cast<int>(CipherType::UNKNOWN);
  return (newCipherType > 0 && newCipherType == static_cast<int>(cipherType) && newCipherType != static_cast<int>(CipherType::UNKNOWN));
}

bool
Cipher::SetCipherDefault(Database& db, CipherType cipherType)
{
  wxCharBuffer strCipherName = GetCipherName(cipherType).utf8_str();
  const char* cipherName = strCipherName;
  sqlite3* dbHandle = static_cast<sqlite3*>(GetDatabaseHandle(db));
  int newCipherType = (dbHandle != nullptr)
                    ? sqlite3mc_config(dbHandle, "default:cipher", sqlite3mc_cipher_index(cipherName))
                    : static_cast<int>(CipherType::UNKNOWN);
  return (newCipherType > 0 && newCipherType == static_cast<int>(cipherType) && newCipherType != static_cast<int>(CipherType::UNKNOWN));
}

CipherType
Cipher::GetCipher(Database& db)
{
  sqlite3* dbHandle = static_cast<sqlite3*>(GetDatabaseHandle(db));
  int cipherType = sqlite3mc_config(dbHandle, "cipher", -1);
  char cipherName[32] = "";
  int rc = sqlite3mc_cipher_name_copy(cipherType, cipherName, 32);
  return GetCipherType(wxString((rc == 1) ? cipherName : ""));
}

CipherType
Cipher::GetCipherDefault(Database& db)
{
  sqlite3* dbHandle = static_cast<sqlite3*>(GetDatabaseHandle(db));
  int cipherType = sqlite3mc_config(dbHandle, "default:cipher", -1);
  char cipherName[32] = "";
  int rc = sqlite3mc_cipher_name_copy(cipherType, cipherName, 32);
  return GetCipherType(wxString((rc == 1) ? cipherName : ""));
}

CipherType
Cipher::GetGlobalCipherDefault()
{
  int cipherType = sqlite3mc_config(0, "default:cipher", -1);
  char cipherName[32] = "";
  int rc = sqlite3mc_cipher_name_copy(cipherType, cipherName, 32);
  return GetCipherType(wxString((rc == 1) ? cipherName : ""));
}

int
Cipher::GetCipherParameterMin(const wxString& cipherName, const wxString& paramName)
{
  wxCharBuffer strCipherName = cipherName.ToUTF8();
  const char* zCipherName = strCipherName;
  wxString minParamName = wxString(wxS("min:")) + paramName;
  wxCharBuffer strParamName = minParamName.ToUTF8();
  const char* zParamName = strParamName;
  return sqlite3mc_config_cipher(0, zCipherName, zParamName, -1);
}

int
Cipher::GetCipherParameterMax(const wxString& cipherName, const wxString& paramName)
{
  wxCharBuffer strCipherName = cipherName.ToUTF8();
  const char* zCipherName = strCipherName;
  wxString maxParamName = wxString(wxS("max:")) + paramName;
  wxCharBuffer strParamName = maxParamName.ToUTF8();
  const char* zParamName = strParamName;
  return sqlite3mc_config_cipher(0, zCipherName, zParamName, -1);
}

void
Cipher::SetInitialized(bool initialized)
{
  m_initialized = initialized;
}

void
Cipher::SetCipherType(CipherType cipherType)
{
  m_cipherType = cipherType;
}

void*
Cipher::GetDatabaseHandle(Database& db)
{
  return db.GetDatabaseHandle();
}


CipherAes128::CipherAes128()
  : Cipher(CipherType::AES128), m_legacy(false)
{
  SetInitialized(true);
}

CipherAes128::CipherAes128(const CipherAes128&  cipher)
  : Cipher(cipher), m_legacy(cipher.m_legacy)
{
}

CipherAes128::~CipherAes128()
{
}

bool
CipherAes128::InitializeFromGlobalDefault()
{
#if HAVE_CIPHER_AES_128_CBC
  int legacy = sqlite3mc_config_cipher(0, "aes128cbc", "legacy", -1);
  m_legacy = legacy != 0;
  bool initialized = legacy >= 0;
  SetInitialized(initialized);
  return initialized;
#else
  throw Exception(WXSQLITE_ERROR, wxERRMSG_CIPHER_NOT_SUPPORTED);
#endif
}

bool
CipherAes128::InitializeFromCurrent(Database& db)
{
#if HAVE_CIPHER_AES_128_CBC
  sqlite3* dbHandle = static_cast<sqlite3*>(GetDatabaseHandle(db));
  int legacy = sqlite3mc_config_cipher(dbHandle, "aes128cbc", "legacy", -1);
  m_legacy = legacy != 0;
  bool initialized = legacy >= 0;
  SetInitialized(initialized);
  return initialized;
#else
  throw Exception(WXSQLITE_ERROR, wxERRMSG_CIPHER_NOT_SUPPORTED);
#endif
}

bool
CipherAes128::InitializeFromCurrentDefault(Database& db)
{
#if HAVE_CIPHER_AES_128_CBC
  sqlite3* dbHandle = static_cast<sqlite3*>(GetDatabaseHandle(db));
  int legacy = sqlite3mc_config_cipher(dbHandle, "aes128cbc", "default:legacy", -1);
  m_legacy = legacy != 0;
  bool initialized = legacy >= 0;
  SetInitialized(initialized);
  return initialized;
#else
  throw Exception(WXSQLITE_ERROR, wxERRMSG_CIPHER_NOT_SUPPORTED);
#endif
}

bool
CipherAes128::Apply(Database& db) const
{
  return Apply(GetDatabaseHandle(db));
}

bool
CipherAes128::Apply(void* dbHandle) const
{
#if HAVE_CIPHER_AES_128_CBC
  bool applied = false;
  if (IsOk())
  {
    if (dbHandle != nullptr)
    {
      int newCipherType = sqlite3mc_config(static_cast<sqlite3*>(dbHandle), "cipher", sqlite3mc_cipher_index("aes128cbc"));
      int legacy = sqlite3mc_config_cipher(static_cast<sqlite3*>(dbHandle), "aes128cbc", "legacy", (m_legacy) ? 1 : 0);
      int legacyPageSize = sqlite3mc_config_cipher(static_cast<sqlite3*>(dbHandle), "aes128cbc", "legacy_page_size", GetLegacyPageSize());
      applied = (newCipherType > 0) && (legacy >= 0) && (legacyPageSize >= 0);
    }
  }
  return applied;
#else
  throw Exception(WXSQLITE_ERROR, wxERRMSG_CIPHER_NOT_SUPPORTED);
#endif
}


CipherAes256::CipherAes256()
  : Cipher(CipherType::AES256), m_legacy(false), m_kdfIter(4001)
{
  SetInitialized(true);
}

CipherAes256::CipherAes256(const CipherAes256& cipher)
  : Cipher(cipher), m_legacy(cipher.m_legacy), m_kdfIter(cipher.m_kdfIter)
{
}

CipherAes256::~CipherAes256()
{
}

bool
CipherAes256::InitializeFromGlobalDefault()
{
#if HAVE_CIPHER_AES_256_CBC
  int legacy = sqlite3mc_config_cipher(0, "aes256cbc", "legacy", -1);
  m_legacy = legacy != 0;
  m_kdfIter = sqlite3mc_config_cipher(0, "aes256cbc", "kdf_iter", -1);
  bool initialized = legacy >= 0 && m_kdfIter > 0;
  SetInitialized(initialized);
  return initialized;
#else
  throw Exception(WXSQLITE_ERROR, wxERRMSG_CIPHER_NOT_SUPPORTED);
#endif
}

bool
CipherAes256::InitializeFromCurrent(Database& db)
{
#if HAVE_CIPHER_AES_256_CBC
  sqlite3* dbHandle = static_cast<sqlite3*>(GetDatabaseHandle(db));
  int legacy = sqlite3mc_config_cipher(dbHandle, "aes256cbc", "legacy", -1);
  m_legacy = legacy != 0;
  m_kdfIter = sqlite3mc_config_cipher(dbHandle, "aes256cbc", "kdf_iter", -1);
  bool initialized = legacy >= 0 && m_kdfIter > 0;
  SetInitialized(initialized);
  return initialized;
#else
  throw Exception(WXSQLITE_ERROR, wxERRMSG_CIPHER_NOT_SUPPORTED);
#endif
}

bool
CipherAes256::InitializeFromCurrentDefault(Database& db)
{
#if HAVE_CIPHER_AES_256_CBC
  sqlite3* dbHandle = static_cast<sqlite3*>(GetDatabaseHandle(db));
  int legacy = sqlite3mc_config_cipher(dbHandle, "aes256cbc", "default:legacy", -1);
  m_legacy = legacy != 0;
  m_kdfIter = sqlite3mc_config_cipher(dbHandle, "aes256cbc", "default:kdf_iter", -1);
  bool initialized = legacy >= 0 && m_kdfIter > 0;
  SetInitialized(initialized);
  return initialized;
#else
  throw Exception(WXSQLITE_ERROR, wxERRMSG_CIPHER_NOT_SUPPORTED);
#endif
}

bool
CipherAes256::Apply(Database& db) const
{
  return Apply(GetDatabaseHandle(db));
}

bool
CipherAes256::Apply(void* dbHandle) const
{
#if HAVE_CIPHER_AES_256_CBC
  bool applied = false;
  if (IsOk())
  {
    if (dbHandle != nullptr)
    {
      int newCipherType = sqlite3mc_config(static_cast<sqlite3*>(dbHandle), "cipher", sqlite3mc_cipher_index("aes256cbc"));
      int legacy = sqlite3mc_config_cipher(static_cast<sqlite3*>(dbHandle), "aes256cbc", "legacy", (m_legacy) ? 1 : 0);
      int legacyPageSize = sqlite3mc_config_cipher(static_cast<sqlite3*>(dbHandle), "aes256cbc", "legacy_page_size", GetLegacyPageSize());
      int kdfIter = sqlite3mc_config_cipher(static_cast<sqlite3*>(dbHandle), "aes256cbc", "kdf_iter", m_kdfIter);
      applied = (newCipherType > 0) && (legacy >= 0) && (legacyPageSize >= 0) && (kdfIter > 0);
    }
  }
  return applied;
#else
  throw Exception(WXSQLITE_ERROR, wxERRMSG_CIPHER_NOT_SUPPORTED);
#endif
}

CipherChaCha20::CipherChaCha20()
  : Cipher(CipherType::CHACHA20), m_legacy(false), m_kdfIter(64007)
{
  SetInitialized(true);
}

CipherChaCha20::CipherChaCha20(const CipherChaCha20&  cipher)
  : Cipher(cipher), m_legacy(cipher.m_legacy), m_kdfIter(cipher.m_kdfIter)
{
}

CipherChaCha20::~CipherChaCha20()
{
}

bool
CipherChaCha20::InitializeFromGlobalDefault()
{
#if HAVE_CIPHER_CHACHA20
  int legacy = sqlite3mc_config_cipher(0, "chacha20", "legacy", -1);
  m_legacy = legacy != 0;
  m_kdfIter = sqlite3mc_config_cipher(0, "chacha20", "kdf_iter", -1);
  bool initialized = legacy >= 0 && m_kdfIter > 0;
  SetInitialized(initialized);
  return initialized;
#else
  throw Exception(WXSQLITE_ERROR, wxERRMSG_CIPHER_NOT_SUPPORTED);
#endif
}

bool
CipherChaCha20::InitializeFromCurrent(Database& db)
{
#if HAVE_CIPHER_CHACHA20
  sqlite3* dbHandle = static_cast<sqlite3*>(GetDatabaseHandle(db));
  int legacy = sqlite3mc_config_cipher(dbHandle, "chacha20", "legacy", -1);
  m_legacy = legacy != 0;
  m_kdfIter = sqlite3mc_config_cipher(dbHandle, "chacha20", "kdf_iter", -1);
  bool initialized = legacy >= 0 && m_kdfIter > 0;
  SetInitialized(initialized);
  return initialized;
#else
  throw Exception(WXSQLITE_ERROR, wxERRMSG_CIPHER_NOT_SUPPORTED);
#endif
}

bool
CipherChaCha20::InitializeFromCurrentDefault(Database& db)
{
#if HAVE_CIPHER_CHACHA20
  sqlite3* dbHandle = static_cast<sqlite3*>(GetDatabaseHandle(db));
  int legacy = sqlite3mc_config_cipher(dbHandle, "chacha20", "default:legacy", -1);
  m_legacy = legacy != 0;
  m_kdfIter = sqlite3mc_config_cipher(dbHandle, "chacha20", "default:kdf_iter", -1);
  bool initialized = legacy >= 0 && m_kdfIter > 0;
  SetInitialized(initialized);
  return initialized;
#else
  throw Exception(WXSQLITE_ERROR, wxERRMSG_CIPHER_NOT_SUPPORTED);
#endif
}

bool
CipherChaCha20::Apply(Database& db) const
{
  return Apply(GetDatabaseHandle(db));
}

bool
CipherChaCha20::Apply(void* dbHandle) const
{
#if HAVE_CIPHER_CHACHA20
  bool applied = false;
  if (IsOk())
  {
    if (dbHandle != nullptr)
    {
      int newCipherType = sqlite3mc_config(static_cast<sqlite3*>(dbHandle), "cipher", sqlite3mc_cipher_index("chacha20"));
      int legacy = sqlite3mc_config_cipher(static_cast<sqlite3*>(dbHandle), "chacha20", "legacy", (m_legacy) ? 1 : 0);
      int legacyPageSize = sqlite3mc_config_cipher(static_cast<sqlite3*>(dbHandle), "chacha20", "legacy_page_size", GetLegacyPageSize());
      int kdfIter = sqlite3mc_config_cipher(static_cast<sqlite3*>(dbHandle), "chacha20", "kdf_iter", m_kdfIter);
      applied = (newCipherType > 0) && (legacy >= 0) && (legacyPageSize >= 0) && (kdfIter > 0);
    }
  }
  return applied;
#else
  throw Exception(WXSQLITE_ERROR, wxERRMSG_CIPHER_NOT_SUPPORTED);
#endif
}


CipherSQLCipher::CipherSQLCipher()
  : Cipher(CipherType::SQLCIPHER), m_legacy(false), m_legacyVersion(0), m_kdfIter(256000),
                    m_fastKdfIter(2), m_hmacUse(true), m_hmacPgNo(1), m_hmacSaltMask(0x3a),
                    m_kdfAlgorithm(ALGORITHM_SHA512), m_hmacAlgorithm(ALGORITHM_SHA512)
{
  SetInitialized(true);
}

CipherSQLCipher::CipherSQLCipher(const CipherSQLCipher&  cipher)
  : Cipher(cipher), m_legacy(cipher.m_legacy), m_legacyVersion(cipher.m_legacyVersion), m_kdfIter(cipher.m_kdfIter),
    m_fastKdfIter(cipher.m_fastKdfIter), m_hmacUse(cipher.m_hmacUse), 
    m_hmacPgNo(cipher.m_hmacPgNo), m_hmacSaltMask(cipher.m_hmacSaltMask),
    m_kdfAlgorithm(cipher.m_kdfAlgorithm), m_hmacAlgorithm(cipher.m_hmacAlgorithm)
{
}

CipherSQLCipher::~CipherSQLCipher()
{
}

bool
CipherSQLCipher::InitializeFromGlobalDefault()
{
#if HAVE_CIPHER_SQLCIPHER
  int legacy = sqlite3mc_config_cipher(0, "sqlcipher", "legacy", -1);
  m_legacy = legacy != 0;
  m_legacyVersion = legacy;
  m_kdfIter = sqlite3mc_config_cipher(0, "sqlcipher", "kdf_iter", -1);
  m_fastKdfIter = sqlite3mc_config_cipher(0, "sqlcipher", "fast_kdf_iter", -1);
  int hmacUse = sqlite3mc_config_cipher(0, "sqlcipher", "hmac_use", -1);
  m_hmacUse = hmacUse != 0;
  m_hmacPgNo = sqlite3mc_config_cipher(0, "sqlcipher", "hmac_pgno", -1);
  m_hmacSaltMask = sqlite3mc_config_cipher(0, "sqlcipher", "hmac_salt_mask", -1);
  int kdfAlgorithm = sqlite3mc_config_cipher(0, "sqlcipher", "kdf_algorithm", -1);
  if (kdfAlgorithm >= 0) m_kdfAlgorithm = static_cast<Algorithm>(kdfAlgorithm);
  int hmacAlgorithm = sqlite3mc_config_cipher(0, "sqlcipher", "hmac_algorithm", -1);
  if (hmacAlgorithm >= 0) m_hmacAlgorithm = static_cast<Algorithm>(hmacAlgorithm);
  bool initialized = legacy >= 0 && m_kdfIter > 0 && m_fastKdfIter > 0 &&
                     hmacUse >= 0 && m_hmacPgNo >= 0 && m_hmacSaltMask >= 0 &&
                     kdfAlgorithm >= 0 && hmacAlgorithm >= 0;
  SetInitialized(initialized);
  return initialized;
#else
  throw Exception(WXSQLITE_ERROR, wxERRMSG_CIPHER_NOT_SUPPORTED);
#endif
}

bool
CipherSQLCipher::InitializeFromCurrent(Database& db)
{
#if HAVE_CIPHER_SQLCIPHER
  sqlite3* dbHandle = static_cast<sqlite3*>(GetDatabaseHandle(db));
  int legacy = sqlite3mc_config_cipher(dbHandle, "sqlcipher", "legacy", -1);
  m_legacy = legacy != 0;
  m_kdfIter = sqlite3mc_config_cipher(dbHandle, "sqlcipher", "kdf_iter", -1);
  m_fastKdfIter = sqlite3mc_config_cipher(dbHandle, "sqlcipher", "fast_kdf_iter", -1);
  int hmacUse = sqlite3mc_config_cipher(dbHandle, "sqlcipher", "hmac_use", -1);
  m_hmacUse = hmacUse != 0;
  m_hmacPgNo = sqlite3mc_config_cipher(dbHandle, "sqlcipher", "hmac_pgno", -1);
  m_hmacSaltMask = sqlite3mc_config_cipher(dbHandle, "sqlcipher", "hmac_salt_mask", -1);
  int kdfAlgorithm = sqlite3mc_config_cipher(dbHandle, "sqlcipher", "kdf_algorithm", -1);
  if (kdfAlgorithm >= 0) m_kdfAlgorithm = static_cast<Algorithm>(kdfAlgorithm);
  int hmacAlgorithm = sqlite3mc_config_cipher(dbHandle, "sqlcipher", "hmac_algorithm", -1);
  if (hmacAlgorithm >= 0) m_hmacAlgorithm = static_cast<Algorithm>(hmacAlgorithm);
  bool initialized = legacy >= 0 && m_kdfIter > 0 && m_fastKdfIter > 0 &&
                     hmacUse >= 0 && m_hmacPgNo >= 0 && m_hmacSaltMask >= 0 &&
                     kdfAlgorithm >= 0 && hmacAlgorithm >= 0;
  SetInitialized(initialized);
  return initialized;
#else
  throw Exception(WXSQLITE_ERROR, wxERRMSG_CIPHER_NOT_SUPPORTED);
#endif
}

bool
CipherSQLCipher::InitializeFromCurrentDefault(Database& db)
{
#if HAVE_CIPHER_SQLCIPHER
  sqlite3* dbHandle = static_cast<sqlite3*>(GetDatabaseHandle(db));
  int legacy = sqlite3mc_config_cipher(dbHandle, "sqlcipher", "default:legacy", -1);
  m_legacy = legacy != 0;
  m_kdfIter = sqlite3mc_config_cipher(dbHandle, "sqlcipher", "default:kdf_iter", -1);
  m_fastKdfIter = sqlite3mc_config_cipher(dbHandle, "sqlcipher", "default:fast_kdf_iter", -1);
  int hmacUse = sqlite3mc_config_cipher(dbHandle, "sqlcipher", "default:hmac_use", -1);
  m_hmacUse = hmacUse != 0;
  m_hmacPgNo = sqlite3mc_config_cipher(dbHandle, "sqlcipher", "default:hmac_pgno", -1);
  m_hmacSaltMask = sqlite3mc_config_cipher(dbHandle, "sqlcipher", "default:hmac_salt_mask", -1);
  int kdfAlgorithm = sqlite3mc_config_cipher(dbHandle, "sqlcipher", "default:kdf_algorithm", -1);
  if (kdfAlgorithm >= 0) m_kdfAlgorithm = static_cast<Algorithm>(kdfAlgorithm);
  int hmacAlgorithm = sqlite3mc_config_cipher(dbHandle, "sqlcipher", "default:hmac_algorithm", -1);
  if (hmacAlgorithm >= 0) m_hmacAlgorithm = static_cast<Algorithm>(hmacAlgorithm);
  bool initialized = legacy >= 0 && m_kdfIter > 0 && m_fastKdfIter > 0 &&
                     hmacUse >= 0 && m_hmacPgNo >= 0 && m_hmacSaltMask >= 0 &&
                     kdfAlgorithm >= 0 && hmacAlgorithm >= 0;
  SetInitialized(initialized);
  return initialized;
#else
  throw Exception(WXSQLITE_ERROR, wxERRMSG_CIPHER_NOT_SUPPORTED);
#endif
}

bool
CipherSQLCipher::Apply(Database& db) const
{
  return Apply(GetDatabaseHandle(db));
}

bool
CipherSQLCipher::Apply(void* dbHandle) const
{
#if HAVE_CIPHER_SQLCIPHER
  bool applied = false;
  if (IsOk())
  {
    if (dbHandle != nullptr)
    {
      int newCipherType = sqlite3mc_config(static_cast<sqlite3*>(dbHandle), "cipher", sqlite3mc_cipher_index("sqlcipher"));
      int legacy = sqlite3mc_config_cipher(static_cast<sqlite3*>(dbHandle), "sqlcipher", "legacy", (m_legacy) ? 1 : 0);
      int legacyPageSize = sqlite3mc_config_cipher(static_cast<sqlite3*>(dbHandle), "sqlcipher", "legacy_page_size", GetLegacyPageSize());
      int kdfIter = sqlite3mc_config_cipher(static_cast<sqlite3*>(dbHandle), "sqlcipher", "kdf_iter", m_kdfIter);
      int fastKdfIter = sqlite3mc_config_cipher(static_cast<sqlite3*>(dbHandle), "sqlcipher", "fast_kdf_iter", m_fastKdfIter);
      int hmacUse = sqlite3mc_config_cipher(static_cast<sqlite3*>(dbHandle), "sqlcipher", "hmac_use", (m_hmacUse) ? 1 : 0);
      int hmacPgNo = sqlite3mc_config_cipher(static_cast<sqlite3*>(dbHandle), "sqlcipher", "hmac_pgno", m_hmacPgNo);
      int hmacSaltMask = sqlite3mc_config_cipher(static_cast<sqlite3*>(dbHandle), "sqlcipher", "hmac_salt_mask", m_hmacSaltMask);
      int kdfAlgorithm = sqlite3mc_config_cipher(static_cast<sqlite3*>(dbHandle), "sqlcipher", "kdf_algorithm", static_cast<int>(m_kdfAlgorithm));
      int hmacAlgorithm = sqlite3mc_config_cipher(static_cast<sqlite3*>(dbHandle), "sqlcipher", "hmac_algorithm", static_cast<int>(m_hmacAlgorithm));
      applied = (newCipherType > 0) && (legacy >= 0) && (legacyPageSize >= 0) &&
                (kdfIter > 0) && (fastKdfIter > 0) &&
                (hmacUse >= 0) && (hmacPgNo >= 0) && (hmacSaltMask >= 0) &&
                (kdfAlgorithm >= 0) && (hmacAlgorithm >= 0);
    }
  }
  return applied;
#else
  throw Exception(WXSQLITE_ERROR, wxERRMSG_CIPHER_NOT_SUPPORTED);
#endif
}

void
CipherSQLCipher::InitializeVersionDefault(int version)
{
#if HAVE_CIPHER_SQLCIPHER
  switch (version)
  {
    case 1:
      m_legacy = true;
      m_legacyVersion = 1;
      m_kdfIter = 4000;
      m_fastKdfIter = 2;
      m_hmacUse = false;
      m_hmacPgNo = 1;
      m_hmacSaltMask = 0x3a;
      m_kdfAlgorithm = ALGORITHM_SHA1;
      m_hmacAlgorithm = ALGORITHM_SHA1;
      SetLegacyPageSize(1024);
      break;
    case 2:
      m_legacy = true;
      m_legacyVersion = 2;
      m_kdfIter = 4000;
      m_fastKdfIter = 2;
      m_hmacUse = true;
      m_hmacPgNo = 1;
      m_hmacSaltMask = 0x3a;
      m_kdfAlgorithm = ALGORITHM_SHA1;
      m_hmacAlgorithm = ALGORITHM_SHA1;
      SetLegacyPageSize(1024);
      break;
    case 3:
      m_legacy = true;
      m_legacyVersion = 3;
      m_kdfIter = 64000;
      m_fastKdfIter = 2;
      m_hmacUse = true;
      m_hmacPgNo = 1;
      m_hmacSaltMask = 0x3a;
      m_kdfAlgorithm = ALGORITHM_SHA1;
      m_hmacAlgorithm = ALGORITHM_SHA1;
      SetLegacyPageSize(1024);
      break;
    case 4:
    default:
      m_legacy = true;
      m_legacyVersion = 4;
      m_kdfIter = 256000;
      m_fastKdfIter = 2;
      m_hmacUse = true;
      m_hmacPgNo = 1;
      m_hmacSaltMask = 0x3a;
      m_kdfAlgorithm = ALGORITHM_SHA512;
      m_hmacAlgorithm = ALGORITHM_SHA512;
      SetLegacyPageSize(4096);
      break;
  }
#else
  throw Exception(WXSQLITE_ERROR, wxERRMSG_CIPHER_NOT_SUPPORTED);
#endif
}

CipherRC4::CipherRC4()
  : Cipher(CipherType::RC4), m_legacy(true)
{
  SetInitialized(true);
}

CipherRC4::CipherRC4(const CipherRC4&  cipher)
  : Cipher(cipher), m_legacy(cipher.m_legacy)
{
}

CipherRC4::~CipherRC4()
{
}

bool
CipherRC4::InitializeFromGlobalDefault()
{
#if HAVE_CIPHER_RC4
  int legacy = sqlite3mc_config_cipher(0, "rc4", "legacy", -1);
  m_legacy = legacy != 0;
  bool initialized = legacy >= 0;
  SetInitialized(initialized);
  return initialized;
#else
  throw Exception(WXSQLITE_ERROR, wxERRMSG_CIPHER_NOT_SUPPORTED);
#endif
}

bool
CipherRC4::InitializeFromCurrent(Database& db)
{
#if HAVE_CIPHER_RC4
  sqlite3* dbHandle = static_cast<sqlite3*>(GetDatabaseHandle(db));
  int legacy = sqlite3mc_config_cipher(dbHandle, "rc4", "legacy", -1);
  m_legacy = legacy != 0;
  bool initialized = legacy >= 0;
  SetInitialized(initialized);
  return initialized;
#else
  throw Exception(WXSQLITE_ERROR, wxERRMSG_CIPHER_NOT_SUPPORTED);
#endif
}

bool
CipherRC4::InitializeFromCurrentDefault(Database& db)
{
#if HAVE_CIPHER_RC4
  sqlite3* dbHandle = static_cast<sqlite3*>(GetDatabaseHandle(db));
  int legacy = sqlite3mc_config_cipher(dbHandle, "rc4", "default:legacy", -1);
  m_legacy = legacy != 0;
  bool initialized = legacy >= 0;
  SetInitialized(initialized);
  return initialized;
#else
  throw Exception(WXSQLITE_ERROR, wxERRMSG_CIPHER_NOT_SUPPORTED);
#endif
}

bool
CipherRC4::Apply(Database& db) const
{
  return Apply(GetDatabaseHandle(db));
}

bool
CipherRC4::Apply(void* dbHandle) const
{
#if HAVE_CIPHER_RC4
  bool applied = false;
  if (IsOk())
  {
    if (dbHandle != nullptr)
    {
      int newCipherType = sqlite3mc_config(static_cast<sqlite3*>(dbHandle), "cipher", sqlite3mc_cipher_index("rc4"));
      int legacy = sqlite3mc_config_cipher(static_cast<sqlite3*>(dbHandle), "rc4", "legacy", (m_legacy) ? 1 : 0);
      int legacyPageSize = sqlite3mc_config_cipher(static_cast<sqlite3*>(dbHandle), "rc4", "legacy_page_size", GetLegacyPageSize());
      applied = (newCipherType > 0) && (legacy >= 0) && (legacyPageSize >= 0);
    }
  }
  return applied;
#else
  throw Exception(WXSQLITE_ERROR, wxERRMSG_CIPHER_NOT_SUPPORTED);
#endif
}

CipherAscon128::CipherAscon128()
  : Cipher(CipherType::ASCON128), m_legacy(false), m_kdfIter(64007)
{
  SetInitialized(true);
}

CipherAscon128::CipherAscon128(const CipherAscon128&  cipher)
  : Cipher(cipher), m_legacy(cipher.m_legacy), m_kdfIter(cipher.m_kdfIter)
{
}

CipherAscon128::~CipherAscon128()
{
}

bool
CipherAscon128::InitializeFromGlobalDefault()
{
#if HAVE_CIPHER_ASCON128
#if 0
  int legacy = sqlite3mc_config_cipher(0, "ascon128", "legacy", -1);
  m_legacy = legacy != 0;
#endif
  m_kdfIter = sqlite3mc_config_cipher(0, "ascon128", "kdf_iter", -1);
  bool initialized = m_kdfIter > 0;
  SetInitialized(initialized);
  return initialized;
#else
  throw Exception(WXSQLITE_ERROR, wxERRMSG_CIPHER_NOT_SUPPORTED);
#endif
}

bool
CipherAscon128::InitializeFromCurrent(Database& db)
{
#if HAVE_CIPHER_ASCON128
  sqlite3* dbHandle = static_cast<sqlite3*>(GetDatabaseHandle(db));
#if 0
  int legacy = sqlite3mc_config_cipher(dbHandle, "ascon128", "legacy", -1);
  m_legacy = legacy != 0;
#endif
  m_kdfIter = sqlite3mc_config_cipher(dbHandle, "ascon128", "kdf_iter", -1);
  bool initialized = m_kdfIter > 0;
  SetInitialized(initialized);
  return initialized;
#else
  throw Exception(WXSQLITE_ERROR, wxERRMSG_CIPHER_NOT_SUPPORTED);
#endif
}

bool
CipherAscon128::InitializeFromCurrentDefault(Database& db)
{
#if HAVE_CIPHER_ASCON128
  sqlite3* dbHandle = static_cast<sqlite3*>(GetDatabaseHandle(db));
#if 0
  int legacy = sqlite3mc_config_cipher(dbHandle, "ascon128", "default:legacy", -1);
  m_legacy = legacy != 0;
#endif
  m_kdfIter = sqlite3mc_config_cipher(dbHandle, "ascon128", "default:kdf_iter", -1);
  bool initialized = m_kdfIter > 0;
  SetInitialized(initialized);
  return initialized;
#else
  throw Exception(WXSQLITE_ERROR, wxERRMSG_CIPHER_NOT_SUPPORTED);
#endif
}

bool
CipherAscon128::Apply(Database& db) const
{
  return Apply(GetDatabaseHandle(db));
}

bool
CipherAscon128::Apply(void* dbHandle) const
{
#if HAVE_CIPHER_ASCON128
  bool applied = false;
  if (IsOk())
  {
    if (dbHandle != nullptr)
    {
      int newCipherType = sqlite3mc_config(static_cast<sqlite3*>(dbHandle), "cipher", sqlite3mc_cipher_index("ascon128"));
#if 0
      int legacy = sqlite3mc_config_cipher(static_cast<sqlite3*>(dbHandle), "ascon128", "legacy", (m_legacy) ? 1 : 0);
      int legacyPageSize = sqlite3mc_config_cipher(static_cast<sqlite3*>(dbHandle), "ascon128", "legacy_page_size", GetLegacyPageSize());
#endif
      int kdfIter = sqlite3mc_config_cipher(static_cast<sqlite3*>(dbHandle), "ascon128", "kdf_iter", m_kdfIter);
      applied = (newCipherType > 0) /* && (legacy >= 0) && (legacyPageSize >= 0) */ && (kdfIter > 0);
    }
  }
  return applied;
#else
  throw Exception(WXSQLITE_ERROR, wxERRMSG_CIPHER_NOT_SUPPORTED);
#endif
}

CipherAegis::CipherAegis()
  : Cipher(CipherType::AEGIS), m_legacy(false),
    m_tcost(2), m_mcost(19*1024), m_pcost(1), m_algorithm(Algorithm::ALGORITHM_AEGIS_256)
{
  SetInitialized(true);
}

CipherAegis::CipherAegis(const CipherAegis&  cipher)
  : Cipher(cipher), m_legacy(cipher.m_legacy),
    m_tcost(cipher.m_tcost), m_mcost(cipher.m_mcost), m_pcost(cipher.m_pcost),
    m_algorithm(cipher.m_algorithm)
{
}

CipherAegis::~CipherAegis()
{
}

bool
CipherAegis::InitializeFromGlobalDefault()
{
#if HAVE_CIPHER_AEGIS
#if 0
  int legacy = sqlite3mc_config_cipher(0, "aegis", "legacy", -1);
  m_legacy = legacy != 0;
#endif
  m_tcost = sqlite3mc_config_cipher(0, "aegis", "tcost", -1);
  m_mcost = sqlite3mc_config_cipher(0, "aegis", "mcost", -1);
  m_pcost = sqlite3mc_config_cipher(0, "aegis", "pcost", -1);
  int algorithm = sqlite3mc_config_cipher(0, "aegis", "algorithm", -1);
  if (algorithm > 0) m_algorithm = static_cast<Algorithm>(algorithm);
  bool initialized = m_tcost > 0 && m_mcost > 0 && m_pcost > 0 && algorithm > 0;
  SetInitialized(initialized);
  return initialized;
#else
  throw Exception(WXSQLITE_ERROR, wxERRMSG_CIPHER_NOT_SUPPORTED);
#endif
}

bool
CipherAegis::InitializeFromCurrent(Database& db)
{
#if HAVE_CIPHER_AEGIS
  sqlite3* dbHandle = static_cast<sqlite3*>(GetDatabaseHandle(db));
#if 0
  int legacy = sqlite3mc_config_cipher(dbHandle, "aegis", "legacy", -1);
  m_legacy = legacy != 0;
#endif
  m_tcost = sqlite3mc_config_cipher(dbHandle, "aegis", "tcost", -1);
  m_mcost = sqlite3mc_config_cipher(dbHandle, "aegis", "mcost", -1);
  m_pcost = sqlite3mc_config_cipher(dbHandle, "aegis", "pcost", -1);
  int algorithm = sqlite3mc_config_cipher(dbHandle, "aegis", "algorithm", -1);
  if (algorithm > 0) m_algorithm = static_cast<Algorithm>(algorithm);
  bool initialized = m_tcost > 0 && m_mcost > 0 && m_pcost > 0 && algorithm > 0;
  SetInitialized(initialized);
  return initialized;
#else
  throw Exception(WXSQLITE_ERROR, wxERRMSG_CIPHER_NOT_SUPPORTED);
#endif
}

bool
CipherAegis::InitializeFromCurrentDefault(Database& db)
{
#if HAVE_CIPHER_AEGIS
  sqlite3* dbHandle = static_cast<sqlite3*>(GetDatabaseHandle(db));
#if 0
  int legacy = sqlite3mc_config_cipher(dbHandle, "aegis", "default:legacy", -1);
  m_legacy = legacy != 0;
#endif
  m_tcost = sqlite3mc_config_cipher(dbHandle, "aegis", "default:tcost", -1);
  m_mcost = sqlite3mc_config_cipher(dbHandle, "aegis", "default:mcost", -1);
  m_pcost = sqlite3mc_config_cipher(dbHandle, "aegis", "default:pcost", -1);
  int algorithm = sqlite3mc_config_cipher(dbHandle, "aegis", "default:algorithm", -1);
  if (algorithm > 0) m_algorithm = static_cast<Algorithm>(algorithm);
  bool initialized = m_tcost > 0 && m_mcost > 0 && m_pcost > 0 && algorithm > 0;
  SetInitialized(initialized);
  return initialized;
#else
  throw Exception(WXSQLITE_ERROR, wxERRMSG_CIPHER_NOT_SUPPORTED);
#endif
}

bool
CipherAegis::Apply(Database& db) const
{
  return Apply(GetDatabaseHandle(db));
}

bool
CipherAegis::Apply(void* dbHandle) const
{
#if HAVE_CIPHER_AEGIS
  bool applied = false;
  if (IsOk())
  {
    if (dbHandle != nullptr)
    {
      int newCipherType = sqlite3mc_config(static_cast<sqlite3*>(dbHandle), "cipher", sqlite3mc_cipher_index("aegis"));
#if 0
      int legacy = sqlite3mc_config_cipher(static_cast<sqlite3*>( dbHandle, "aegis", "legacy", (m_legacy) ? 1 : 0);
      int legacyPageSize = sqlite3mc_config_cipher(static_cast<sqlite3*>( dbHandle, "aegis", "legacy_page_size", GetLegacyPageSize());
#endif
      int tcost = sqlite3mc_config_cipher(static_cast<sqlite3*>(dbHandle), "aegis", "tcost", m_tcost);
      int mcost = sqlite3mc_config_cipher(static_cast<sqlite3*>(dbHandle), "aegis", "mcost", m_mcost);
      int pcost = sqlite3mc_config_cipher(static_cast<sqlite3*>(dbHandle), "aegis", "pcost", m_pcost);
      int algorithm = sqlite3mc_config_cipher(static_cast<sqlite3*>(dbHandle), "aegis", "algorithm", static_cast<int>(m_algorithm));
      applied = (newCipherType > 0) && (tcost > 0) && (mcost > 0) && (pcost > 0) && (algorithm > 0);
    }
  }
  return applied;
#else
  throw Exception(WXSQLITE_ERROR, wxERRMSG_CIPHER_NOT_SUPPORTED);
#endif
}

}  // namespace wxSQLite3
