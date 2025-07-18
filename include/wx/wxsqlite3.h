/*
** Name:        wxsqlite3.h
** Purpose:     wxWidgets wrapper around the SQLite3 embedded database library.
** Author:      Ulrich Telle
** Created:     2005-07-14
** Copyright:   (c) 2005-2025 Ulrich Telle
** License:     LGPL-3.0+ WITH WxWindows-exception-3.1
*/

/// \file wxsqlite3.h Interface of the wxSQLite3 class

#ifndef WX_SQLITE3_H_
#define WX_SQLITE3_H_

#if defined(__GNUG__) && !defined(__APPLE__)
    #pragma interface "wxsqlite3.h"
#endif

#include <wx/arrstr.h>
#include <wx/datetime.h>
#include <wx/dynarray.h>
#include <wx/buffer.h>
#include <wx/hashmap.h>
#include <wx/regex.h>
#include <wx/string.h>

#include "wx/wxsqlite3def.h"
#include "wx/wxsqlite3_version.h"

/// wxSQLite3 version string
#define wxSQLITE3_VERSION_STRING   wxS(WXSQLITE3_VERSION_STRING)

/// Enumeration of supported cipher types
enum wxSQLite3CipherType
{
  WXSQLITE_CIPHER_UNKNOWN,
  WXSQLITE_CIPHER_AES128,
  WXSQLITE_CIPHER_AES256,
  WXSQLITE_CIPHER_CHACHA20,
  WXSQLITE_CIPHER_SQLCIPHER,
  WXSQLITE_CIPHER_RC4,
  WXSQLITE_CIPHER_ASCON128,
  WXSQLITE_CIPHER_AEGIS
};

#define WXSQLITE_ERROR 1000

#define WXSQLITE_INTEGER  1
#define WXSQLITE_FLOAT    2
#define WXSQLITE_TEXT     3
#define WXSQLITE_BLOB     4
#define WXSQLITE_NULL     5

#if defined(_MSC_VER) || defined(__BORLANDC__)
  typedef __int64 wxsqlite_int64;
#else
  typedef long long int wxsqlite_int64;
#endif

/// Enumeration of transaction types
enum wxSQLite3TransactionType
{
  WXSQLITE_TRANSACTION_DEFAULT,
  WXSQLITE_TRANSACTION_DEFERRED,
  WXSQLITE_TRANSACTION_IMMEDIATE,
  WXSQLITE_TRANSACTION_EXCLUSIVE
};

/// Enumeration of transaction state
enum wxSQLite3TransactionState
{
  WXSQLITE_TRANSACTION_INVALID,
  WXSQLITE_TRANSACTION_NONE,
  WXSQLITE_TRANSACTION_READ,
  WXSQLITE_TRANSACTION_WRITE
};

/// Enumeration of SQLite limitation types
enum wxSQLite3LimitType
{
  WXSQLITE_LIMIT_LENGTH              = 0,
  WXSQLITE_LIMIT_SQL_LENGTH          = 1,
  WXSQLITE_LIMIT_COLUMN              = 2,
  WXSQLITE_LIMIT_EXPR_DEPTH          = 3,
  WXSQLITE_LIMIT_COMPOUND_SELECT     = 4,
  WXSQLITE_LIMIT_VDBE_OP             = 5,
  WXSQLITE_LIMIT_FUNCTION_ARG        = 6,
  WXSQLITE_LIMIT_ATTACHED            = 7,
  WXSQLITE_LIMIT_LIKE_PATTERN_LENGTH = 8,
  WXSQLITE_LIMIT_VARIABLE_NUMBER     = 9,
  WXSQLITE_LIMIT_TRIGGER_DEPTH       = 10,
  WXSQLITE_LIMIT_WORKER_THREADS      = 11 
};

/// Enumeration of journal modes
enum wxSQLite3JournalMode
{
  WXSQLITE_JOURNALMODE_DELETE     = 0,   // Commit by deleting journal file
  WXSQLITE_JOURNALMODE_PERSIST    = 1,   // Commit by zeroing journal header
  WXSQLITE_JOURNALMODE_OFF        = 2,   // Journal omitted.
  WXSQLITE_JOURNALMODE_TRUNCATE   = 3,   // Commit by truncating journal
  WXSQLITE_JOURNALMODE_MEMORY     = 4,   // In-memory journal file
  WXSQLITE_JOURNALMODE_WAL        = 5    // Use write-ahead logging
};

/// Enumeration of statement status counters
enum wxSQLite3StatementStatus
{
  WXSQLITE_STMTSTATUS_FULLSCAN_STEP = 1,
  WXSQLITE_STMTSTATUS_SORT          = 2,
  WXSQLITE_STMTSTATUS_AUTOINDEX     = 3,
  WXSQLITE_STMTSTATUS_VM_STEP       = 4,
  WXSQLITE_STMTSTATUS_REPREPARE     = 5,
  WXSQLITE_STMTSTATUS_RUN           = 6,
  WXSQLITE_STMTSTATUS_MEMUSED       = 99
};

/// Enumeration of statement status counters
enum wxSQLite3DbConfig
{
  WXSQLITE_DBCONFIG_ENABLE_FKEY           = 1002,
  WXSQLITE_DBCONFIG_ENABLE_TRIGGER        = 1003,
  WXSQLITE_DBCONFIG_ENABLE_FTS3_TOKENIZER = 1004,
  WXSQLITE_DBCONFIG_ENABLE_LOAD_EXTENSION = 1005,
  WXSQLITE_DBCONFIG_NO_CKPT_ON_CLOSE      = 1006,
  WXSQLITE_DBCONFIG_ENABLE_QPSG           = 1007,
  WXSQLITE_DBCONFIG_TRIGGER_EQP           = 1008,
  WXSQLITE_DBCONFIG_RESET_DATABASE        = 1009,
  WXSQLITE_DBCONFIG_DEFENSIVE             = 1010,
  WXSQLITE_DBCONFIG_WRITABLE_SCHEMA       = 1011,
  WXSQLITE_DBCONFIG_LEGACY_ALTER_TABLE    = 1012,
  WXSQLITE_DBCONFIG_DQS_DML               = 1013,
  WXSQLITE_DBCONFIG_DQS_DDL               = 1014,
  WXSQLITE_DBCONFIG_ENABLE_VIEW           = 1015,
  WXSQLITE_DBCONFIG_LEGACY_FILE_FORMAT    = 1016,
  WXSQLITE_DBCONFIG_TRUSTED_SCHEMA        = 1017,
  WXSQLITE_DBCONFIG_STMT_SCANSTATUS       = 1018,
  WXSQLITE_DBCONFIG_REVERSE_SCANORDER     = 1019,
  WXSQLITE_DBCONFIG_ENABLE_ATTACH_CREATE  = 1020,
  WXSQLITE_DBCONFIG_ENABLE_ATTACH_WRITE   = 1021,
  WXSQLITE_DBCONFIG_ENABLE_COMMENTS       = 1022
};

#define WXSQLITE_OPEN_READONLY         0x00000001
#define WXSQLITE_OPEN_READWRITE        0x00000002
#define WXSQLITE_OPEN_CREATE           0x00000004
#define WXSQLITE_OPEN_URI              0x00000040
#define WXSQLITE_OPEN_MEMORY           0x00000080
#define WXSQLITE_OPEN_NOMUTEX          0x00008000
#define WXSQLITE_OPEN_FULLMUTEX        0x00010000
#define WXSQLITE_OPEN_SHAREDCACHE      0x00020000
#define WXSQLITE_OPEN_PRIVATECACHE     0x00040000
#define WXSQLITE_OPEN_NOFOLLOW         0x01000000
 
#define WXSQLITE_CHECKPOINT_PASSIVE  0
#define WXSQLITE_CHECKPOINT_FULL     1
#define WXSQLITE_CHECKPOINT_RESTART  2
#define WXSQLITE_CHECKPOINT_TRUNCATE 3

#define WXSQLITE_DETERMINISTIC    0x000000800
#define WXSQLITE_DIRECTONLY       0x000080000
#define WXSQLITE_SUBTYPE          0x000100000
#define WXSQLITE_INNOCUOUS        0x000200000
#define WXSQLITE_RESULT_SUBTYPE   0x001000000

inline void operator++(wxSQLite3LimitType& value)
{
  value = wxSQLite3LimitType(value+1);
}

/// SQL exception
class WXDLLIMPEXP_SQLITE3 wxSQLite3Exception
{
public:
  /// Constructor
  wxSQLite3Exception(int errorCode, const wxString& errMsg);

  /// Copy constructor
  wxSQLite3Exception(const wxSQLite3Exception&  e);

  /// Destructor
  virtual ~wxSQLite3Exception();

  /// Get error code associated with the exception
  int GetErrorCode() const { return (m_errorCode & 0xff); }

  /// Get extended error code associated with the exception
  int GetExtendedErrorCode() const { return m_errorCode; }

  /// Get error message associated with the exception
  const wxString GetMessage() const { return m_errorMessage; }

  /// Convert error code to error message
  static const wxString ErrorCodeAsString(int errorCode);

private:
  int      m_errorCode;       ///< SQLite3 error code associated with this exception
  wxString m_errorMessage;    ///< SQLite3 error message associated with this exception
};

/// SQL statement buffer for use with SQLite3's printf method
class WXDLLIMPEXP_SQLITE3 wxSQLite3StatementBuffer
{
public:
  /// Constructor
  wxSQLite3StatementBuffer();

  /// Destructor
  ~wxSQLite3StatementBuffer();

  /// Format a SQL statement using SQLite3's printf method
  /**
  * This method is a variant of the "sprintf()" from the standard C library.
  * All of the usual printf formatting options apply. In addition,
  * there is a "%q" option. %q works like %s in that it substitutes
  * a null-terminated string from the argument list. But %q also
  * doubles every '\'' character. %q is designed for use inside a
  * string literal. By doubling each '\'' character it escapes that
  * character and allows it to be inserted into the string.
  *
  * For example, so some string variable contains text as follows:
  *
  * char *zText = "It's a happy day!";
  *
  * One can use this text in an SQL statement as follows:
  *
  * wxSQLite3StatementBuffer stmtBuffer;
  * stmtBuffer.Format("INSERT INTO table VALUES('%q')", zText);
  *
  * Because the %q format string is used, the '\'' character in
  * zText is escaped and the SQL generated is as follows:
  *
  * INSERT INTO table1 VALUES('It''s a happy day!')
  *
  * \param format SQL statement string with formatting options
  * \param ... list of statement parameters
  * \return const char pointer to the resulting statement buffer
  */
  const char* Format(const char* format, ...);

  /// Format a SQL statement using SQLite3's printf method
  /**
  * This method is like method Format but takes a va_list argument
  * to pass the statement parameters.
  *
  * \param format SQL statement string with formatting options
  * \param va va_list of statement parameters
  * \return const char pointer to the resulting statement buffer
  */
  const char* FormatV(const char* format, va_list va);

  /// Dereference the internal buffer
  /**
  * \return const char pointer to the resulting statement buffer
  */
  operator const char*() const { return m_buffer; }

  /// Clear the internal buffer
  void Clear();

private:
  char* m_buffer;  ///< Internal buffer
};

/// SQLite logging hook
class WXDLLIMPEXP_SQLITE3 wxSQLite3Logger
{
public:
  /// Constructor
  wxSQLite3Logger();

  /// Destructor
  virtual ~wxSQLite3Logger();

  void Activate(bool active = true) { m_isActive = active; }
  void Deactivate() { m_isActive = false;  }
  bool IsActive() const { return m_isActive;  }

  virtual void HandleLogMessage(int errorCode, const wxString& errorMessage);

  /// Execute the user defined commit hook (internal use only)
  static void ExecLoggerHook(void* logger, int errorCode, const char* errorMsg);

private:
  /// Copy constructor
  wxSQLite3Logger(const wxSQLite3Logger&  logger);

  bool m_isActive;
};


/// Context for user defined scalar or aggregate functions
/**
* A function context gives user defined scalar or aggregate functions
* access to function arguments and function results. The "Execute" method
* resp. the "Aggregate" and "Finalize" methods receive the current
* function context as an argument.
*/
class WXDLLIMPEXP_SQLITE3 wxSQLite3FunctionContext
{
public:
  /// Default destructor
  virtual ~wxSQLite3FunctionContext();

  /// Get the number of function arguments
  /**
  * \return the number of arguments the function was called with
  */
  int GetArgCount() const;

  /// Get the type of a function argument
  /**
  * \param argIndex index of the function argument. Indices start with 0.
  * \return argument type as one of the values WXSQLITE_INTEGER, WXSQLITE_FLOAT, WXSQLITE_TEXT, WXSQLITE_BLOB, or WXSQLITE_NULL
  */
  int GetArgType(int argIndex) const;

  /// Check whether a function argument is a NULL value
  /**
  * \param argIndex index of the function argument. Indices start with 0.
  * \return TRUE if the argument is NULL or the argIndex is out of bounds, FALSE otherwise
  */
  bool IsNull(int argIndex) const;

  /// Get a function argument as an integer value
  /**
  * \param argIndex index of the function argument. Indices start with 0.
  * \param nullValue value to be returned in case the argument is NULL
  * \return argument value
  */
  int GetInt(int argIndex, int nullValue = 0) const;

  /// Get a function argument as an 64-bit integer value
  /**
  * \param argIndex index of the function argument. Indices start with 0.
  * \param nullValue value to be returned in case the argument is NULL
  * \return argument value
  */
  wxLongLong GetInt64(int argIndex, wxLongLong nullValue = 0) const;

  /// Get a function argument as a double value
  /**
  * \param argIndex index of the function argument. Indices start with 0.
  * \param nullValue value to be returned in case the argument is NULL
  * \return argument value
  */
  double GetDouble(int argIndex, double nullValue = 0) const;

  /// Get a function argument as a string value
  /**
  * \param argIndex index of the function argument. Indices start with 0.
  * \param nullValue value to be returned in case the argument is NULL
  * \return argument value
  */
  wxString GetString(int argIndex, const wxString& nullValue = wxEmptyString) const;

  /// Get a function argument as a BLOB value
  /**
  * \param argIndex index of the function argument. Indices start with 0.
  * \param[out] len length of the blob argument in bytes
  * \return argument value
  */
  const unsigned char* GetBlob(int argIndex, int& len) const;

  /// Get a function argument as a BLOB value
  /**
  * \param argIndex index of the function argument. Indices start with 0.
  * \param[out] buffer to which the blob argument value is appended
  * \return reference to argument value
  */
  wxMemoryBuffer& GetBlob(int argIndex, wxMemoryBuffer& buffer) const;

  /// Get a function argument as a pointer value
  /**
  * \param argIndex index of the function argument. Indices start with 0.
  * \param pointerType a name identifying the pointer type.
  * \return argument value
  */
  void* GetPointer(int argIndex, const wxString& pointerType) const;

  /// Set the function result as an integer value
  /**
  * \param value function result value
  */
  void SetResult(int value);

  /// Set the function result as an 64-bit integer value
  /**
  * \param value function result value
  */
  void SetResult(wxLongLong value);

  /// Set the function result as a double value
  /**
  * \param value function result value
  */
  void SetResult(double value);

  /// Set the function result as a string value
  /**
  * \param value function result value
  */
  void SetResult(const wxString& value);

  /// Set the function result as a BLOB value
  /**
  * \param value function result value
  * \param len length of the result blob in bytes
  */
  void SetResult(unsigned char* value, int len);

  /// Set the function result as a BLOB value
  /**
  * \param buffer containing the function result value
  */
  void SetResult(const wxMemoryBuffer& buffer);

  /// Set the function result as a pointer value
  /**
  * \param pointer pointer value
  * \param pointerType descriptive name of the pointer type as expected by the extension module
  * \param DeletePointer pointer to a function for deleting the object pointed to by the pointer after use in SQLite (default: NULL)
  */
  void SetResult(void* pointer, const wxString& pointerType, void(*DeletePointer)(void*) = NULL);

  /// Set the function result as a NULL value
  void SetResultNull();

  /// Set the function result as a zero BLOB value
  /**
  * \param blobSize size of the zero filled BLOB value
  */
  void SetResultZeroBlob(int blobSize);

  /// Set the function result as a exact copy of a function argument
  /**
  * \param argIndex index of the argument which should be copied as the result value
  */
  void SetResultArg(int argIndex);

  /// Set an error message as the function result
  /**
  * \param errmsg string containing an error message
  */
  void SetResultError(const wxString& errmsg);

  /// Get the number of aggregate steps
  /**
  * \return the number of aggregation steps. The current aggregation step counts so at least 1 is returned.
  */
  int GetAggregateCount() const;

  /// Get a pointer to an aggregate structure of specified length
  /**
  * Usually an aggregation functions needs temporary memory to collect
  * the information gathered from each invocation of the "Aggregate" method.
  * On the first invocation of this method the returned memory contains
  * binary zeros.
  * If this memory is used to store pointers to allocated objects,
  * it is important to free all allocated objects in the "Finalize" method.
  *
  * \param len amount of memory needed in bytes
  * \return pointer to the allocated memory
  */
  void* GetAggregateStruct(int len) const;

  /// Execute a user defined scalar function (internal use only)
  static void ExecScalarFunction(void* ctx, int argc, void** argv);

  /// Execute an aggregate step of a user defined aggregate function (internal use only)
  static void ExecAggregateStep(void* ctx, int argc, void** argv);

  /// Execute the final step of a user defined aggregate function (internal use only)
  static void ExecAggregateFinalize(void* ctx);

  /// Execute an aggregate step of a user defined aggregate window function (internal use only)
  static void ExecWindowStep(void* ctx, int argc, void** argv);

  /// Execute the final step of a user defined aggregate window function (internal use only)
  static void ExecWindowFinalize(void* ctx);

  /// Execute the current value step of a user defined aggregate window function (internal use only)
  static void ExecWindowValue(void* ctx);

  /// Execute the inverse step of a user defined aggregate window function (internal use only)
  static void ExecWindowInverse(void* ctx, int argc, void** argv);

  /// Execute the user defined commit hook (internal use only)
  static int ExecCommitHook(void* hook);

  /// Execute the user defined rollback hook (internal use only)
  static void ExecRollbackHook(void* hook);

  /// Execute the user defined update hook (internal use only)
  static void ExecUpdateHook(void* hook, int type,
                             const char* database, const char* table,
                             wxsqlite_int64 rowid);

  /// Execute the user defined Write Ahead Log hook (internal use only)
  static int ExecWriteAheadLogHook(void* hook, void* dbHandle,
                                   const char* database, int numPages);

private:
  /// Constructor
  wxSQLite3FunctionContext(void* ctx, bool isAggregate, int argc = 0, void** argv = NULL);

  /// Copy constructor
  wxSQLite3FunctionContext(wxSQLite3FunctionContext& ctx);

  /// Make copy of pointer type
  const char* MakePointerTypeCopy(const wxString& pointerType);

  void*  m_ctx;          ///< SQLite3 context
  bool   m_isAggregate;  ///< Flag whether this is the context of an aggregate function
  int    m_count;        ///< Aggregate count
  int    m_argc;         ///< Number of arguments
  void** m_argv;         ///< Array of SQLite3 arguments

  wxArrayPtrVoid* m_ptrTypes;       ///< Keeping track of pointer types
};


/// Interface for user defined scalar functions
/**
*/
class WXDLLIMPEXP_SQLITE3 wxSQLite3ScalarFunction
{
public:
  /// Constructor
  wxSQLite3ScalarFunction() {}

  /// Virtual destructor
  virtual ~wxSQLite3ScalarFunction() {}

  /// Execute the scalar function
  /**
  * This method is invoked for each appearance of the scalar function in the SQL query.
  * \param ctx function context which can be used to access arguments and result value
  */
  virtual void Execute(wxSQLite3FunctionContext& ctx) = 0;
};


/// Interface for user defined aggregate functions
/**
*/
class WXDLLIMPEXP_SQLITE3 wxSQLite3AggregateFunction
{
public:
  /// Constructor
  wxSQLite3AggregateFunction() { m_count = 0; }

  /// Virtual destructor
  virtual ~wxSQLite3AggregateFunction() {}

  /// Execute the aggregate of the function
  /**
  * This method is invoked for each row of the result set of the query using the aggregate function.
  * \param ctx function context which can be used to access arguments and result value
  */
  virtual void Aggregate(wxSQLite3FunctionContext& ctx) = 0;

  /// Prepare the result of the aggregate function
  /**
  * This method is invoked after all rows of the result set of the query
  * using the aggregate function have been processed. Usually the final result
  * is calculated and returned in this method.
  * \param ctx function context which can be used to access arguments and result value
  */
  virtual void Finalize(wxSQLite3FunctionContext& ctx) = 0;

private:
  int    m_count;        ///< Aggregate count
  friend class wxSQLite3FunctionContext;
};

/// Interface for user defined aggregate window functions
/**
*/
class WXDLLIMPEXP_SQLITE3 wxSQLite3WindowFunction
{
public:
  /// Constructor
  wxSQLite3WindowFunction() { m_count = 0; }

  /// Virtual destructor
  virtual ~wxSQLite3WindowFunction() {}

  /// Execute the aggregate of the window function
  /**
  * This method is invoked for each row of the result set of the query using the aggregate window function.
  * \param ctx function context which can be used to access arguments and result value
  */
  virtual void Aggregate(wxSQLite3FunctionContext& ctx) = 0;

  /// Prepare the result of the aggregate window function
  /**
  * This method is invoked after all rows of the result set of the query
  * using the aggregate window function have been processed. Usually the final result
  * is calculated and returned in this method.
  * \param ctx function context which can be used to access arguments and result value
  */
  virtual void Finalize(wxSQLite3FunctionContext& ctx) = 0;

  /// Get current value of the aggregate window function
  /**
  * This method is invoked to return the current value of the aggregate.
  * Unlike Finalize, the implementation should not delete any context.
  * \param ctx function context which can be used to access arguments and result value
  */
  virtual void CurrentValue(wxSQLite3FunctionContext& ctx) = 0;

  /// Reverse an aggregate step of the window function
  /**
  * This method is invoked to remove a row from the current window.
  * The function arguments, if any, correspond to the row being removed.
  * \param ctx function context which can be used to access arguments and result value
  */
  virtual void Reverse(wxSQLite3FunctionContext& ctx) = 0;

private:
  int    m_count;        ///< Aggregate count
  friend class wxSQLite3FunctionContext;
};


/// Interface for a user defined authorizer function
/**
*/
class WXDLLIMPEXP_SQLITE3 wxSQLite3Authorizer
{
public:
  /// Codes identifying the command for which authorization is requested
  enum wxAuthorizationCode
  {                                    // arg1 =          arg2 =
    SQLITE_COPY                =  0,   // Table Name      File Name
    SQLITE_CREATE_INDEX        =  1,   // Index Name      Table Name
    SQLITE_CREATE_TABLE        =  2,   // Table Name      NULL
    SQLITE_CREATE_TEMP_INDEX   =  3,   // Index Name      Table Name
    SQLITE_CREATE_TEMP_TABLE   =  4,   // Table Name      NULL
    SQLITE_CREATE_TEMP_TRIGGER =  5,   // Trigger Name    Table Name
    SQLITE_CREATE_TEMP_VIEW    =  6,   // View Name       NULL
    SQLITE_CREATE_TRIGGER      =  7,   // Trigger Name    Table Name
    SQLITE_CREATE_VIEW         =  8,   // View Name       NULL
    SQLITE_DELETE              =  9,   // Table Name      NULL
    SQLITE_DROP_INDEX          = 10,   // Index Name      Table Name
    SQLITE_DROP_TABLE          = 11,   // Table Name      NULL
    SQLITE_DROP_TEMP_INDEX     = 12,   // Index Name      Table Name
    SQLITE_DROP_TEMP_TABLE     = 13,   // Table Name      NULL
    SQLITE_DROP_TEMP_TRIGGER   = 14,   // Trigger Name    Table Name
    SQLITE_DROP_TEMP_VIEW      = 15,   // View Name       NULL
    SQLITE_DROP_TRIGGER        = 16,   // Trigger Name    Table Name
    SQLITE_DROP_VIEW           = 17,   // View Name       NULL
    SQLITE_INSERT              = 18,   // Table Name      NULL
    SQLITE_PRAGMA              = 19,   // Pragma Name     1st arg or NULL
    SQLITE_READ                = 20,   // Table Name      Column Name
    SQLITE_SELECT              = 21,   // NULL            NULL
    SQLITE_TRANSACTION         = 22,   // Operation       NULL
    SQLITE_UPDATE              = 23,   // Table Name      Column Name
    SQLITE_ATTACH              = 24,   // Filename        NULL
    SQLITE_DETACH              = 25,   // Database Name   NULL
    SQLITE_ALTER_TABLE         = 26,   // Database Name   Table Name
    SQLITE_REINDEX             = 27,   // Index Name      NULL
    SQLITE_ANALYZE             = 28,   // Table Name      NULL
    SQLITE_CREATE_VTABLE       = 29,   // Table Name      Module Name
    SQLITE_DROP_VTABLE         = 30,   // Table Name      Module Name
    SQLITE_FUNCTION            = 31,   // NULL            Function Name
    SQLITE_SAVEPOINT           = 32,   // Operation       Savepoint Name
    SQLITE_RECURSIVE           = 33,   // NULL            NULL
    SQLITE_MAX_CODE            = SQLITE_RECURSIVE
  };

  /// Return codes of the authorizer
  enum wxAuthorizationResult
  {
    SQLITE_OK     = 0,   // Allow access
    SQLITE_DENY   = 1,   // Abort the SQL statement with an error
    SQLITE_IGNORE = 2    // Don't allow access, but don't generate an error
  };
  
  /// Virtual destructor
  virtual ~wxSQLite3Authorizer() {}
  
  /// Execute the authorizer function
  /**
  * Please refer to the SQLite documentation for further information about the
  * meaning of the parameters.
  *
  * \param type wxAuthorizationCode. The value signifies what kind of operation is to be authorized.
  * \param arg1 first argument (value depends on "type")
  * \param arg2 second argument (value depends on "type")
  * \param arg3 third argument (name of database if applicable)
  * \param arg4 fourth argument (name of trigger or view if applicable)
  * \param arg5 fifth argument (name of authorized user or empty if user authentication is not activated)
  * \return a wxAuthorizationResult, i.e. SQLITE_OK, SQLITE_DENY or SQLITE_IGNORE
  */
  virtual wxAuthorizationResult Authorize(wxAuthorizationCode type,
                                          const wxString& arg1, const wxString& arg2,
                                          const wxString& arg3, const wxString& arg4,
                                          const wxString& arg5) = 0;
  /// Convert authorization code to string
  /**
  * \param type wxAuthorizationCode. The value signifies what kind of operation is to be authorized.
  */
  static wxString AuthorizationCodeToString(wxSQLite3Authorizer::wxAuthorizationCode type);
};

class wxSQLite3DatabaseReference;
class wxSQLite3StatementReference;
class wxSQLite3BlobReference;

class WXDLLIMPEXP_FWD_SQLITE3 wxSQLite3Database;

/// Cipher base class
class WXDLLIMPEXP_SQLITE3 wxSQLite3Cipher
{
public:
  /// Constructor
  wxSQLite3Cipher();

  /// Destructor
  virtual ~wxSQLite3Cipher();

  /// Initialize the cipher instance based on global default settings
  /**
  * The parameters of the cipher instance are initialize with the global default settings of the associated cipher type.
  * \return true if the cipher instance could be initialized successfully, false otherwise
  */
  virtual bool InitializeFromGlobalDefault();

  /// Initialize the cipher instance based on current settings
  /**
  * The parameters of the cipher instance are initialize with the current settings of the associated cipher type
  * as defined in the given database connection. 
  * \param db database instance representing a database connection
  * \return true if the cipher instance could be initialized successfully, false otherwise
  */
  virtual bool InitializeFromCurrent(wxSQLite3Database& db);

  /// Initialize the cipher instance based on current default settings
  /**
  * The parameters of the cipher instance are initialize with the current default settings of the associated cipher type
  * as defined in the given database connection.
  * \param db database instance representing a database connection
  * \return true if the cipher instance could be initialized successfully, false otherwise
  */
  virtual bool InitializeFromCurrentDefault(wxSQLite3Database& db);

  /// Apply the cipher parameters to a database connection
  /**
  * The parameters of the cipher instance are applied to the given database connection.
  * \param db database instance representing a database connection
  * \return true if the cipher parameters could be applied successfully, false otherwise
  */
  virtual bool Apply(wxSQLite3Database& db) const;
  virtual bool Apply(void* dbHandle) const;

  void SetLegacyPageSize(int pageSize);

  int GetLegacyPageSize() const;

  /// Get the type of this cipher instance
  /**
  * The type of the cipher instance is returned.
  * \return the cipher type
  */
  wxSQLite3CipherType GetCipherType() const;

  /// Check whether the cipher instance is valid
  /**
  * The method checks whether the cipher instance is initialized correctly.
  * \return true if the cipher instance is valid, false otherwise
  */
  bool IsOk() const;

  /// Convert cipher type to string representation
  /**
  * The given cipher type is converted to a string representation.
  * \param cipherType the type of a cipher
  * \return string representation of the given cipher type
  */
  static const wxString GetCipherName(wxSQLite3CipherType cipherType);

  /// Convert string representation to cipher type
  /**
  * The given string representation of a cipher is converted to the corresponding cipher type..
  * The parameters of the cipher instance are applied to the given database connection.
  * WXSQLITE_CIPHER_UNKNOWN will be returned if the string representation is invalid.
  * \param cipherName the string representation of a cipher type
  * \return cipher type corresponding to the given string representation
  */
  static wxSQLite3CipherType GetCipherType(const wxString& cipherName);

  /// Set the current cipher type for a database connection
  /**
  * \param db database instance
  * \param cipherType the cipher type to be set
  * \return true if the cipher type could be set, false otherwise
  */
  static bool SetCipher(wxSQLite3Database& db, wxSQLite3CipherType cipherType);

  /// Set the default cipher type for a database connection
  /**
  * \param db database instance
  * \param cipherType the cipher type to be set
  * \return true if the cipher type could be set, false otherwise
  */
  static bool SetCipherDefault(wxSQLite3Database& db, wxSQLite3CipherType cipherType);

  /// Get the current cipher type of a database connection
  /**
  * \param db database instance
  * \return the enum representation of the cipher type
  */
  static wxSQLite3CipherType GetCipher(wxSQLite3Database& db);

  /// Get the default cipher type of a database connection
  /**
  * \param db database instance 
  * \return the enum representation of the cipher type
  */
  static wxSQLite3CipherType GetCipherDefault(wxSQLite3Database& db);

  /// Get the globally defined default cipher type
  /**
  * \return the enum representation of the cipher type
  */
  static wxSQLite3CipherType GetGlobalCipherDefault();

  /// Get minimum allowed cipher parameter value
  /**
  * \param cipherName the name of the cipher to be queried
  * \param paramName the name of the parameter to be queried
  * \return the minimum value for the given cipher parameter
  */
  static int GetCipherParameterMin(const wxString& cipherName, const wxString& paramName);

  /// Get maximum allowed cipher parameter value
  /**
  * \param cipherName the name of the cipher to be queried
  * \param paramName the name of the parameter to be queried
  * \return the maximum value for the given cipher parameter
  */
  static int GetCipherParameterMax(const wxString& cipherName, const wxString& paramName);

protected:
  /// Constructor
  /**
  * \param cipherType the type of the cipher
  */
  wxSQLite3Cipher(wxSQLite3CipherType cipherType);

  /// Copy constructor
  wxSQLite3Cipher(const wxSQLite3Cipher& cipher);

  /// Set initialization status of the cipher instance
  /**
  * \param initialized the initialization status
  */
  void SetInitialized(bool initialized);

  /// Set type of the cipher instance
  /**
  * \param cipherType the cipher type to be set
  */
  void SetCipherType(wxSQLite3CipherType cipherType);

  /// Get the SQLite3 database handle of a database instance
  /**
  * \param db database instance
  * \return SQLite3 database handle
  */
  static void* GetDatabaseHandle(wxSQLite3Database& db);

private:
  bool                m_initialized;    ///< Initialization status
  wxSQLite3CipherType m_cipherType;     ///< Cypher type
  int                 m_legacyPageSize; ///< Page size in legacy mode of cipher
};

/// Cipher class representing AES 128 bit encryption in CBC mode
class WXDLLIMPEXP_SQLITE3 wxSQLite3CipherAes128 : public wxSQLite3Cipher
{
public:
  /// Constructor
  wxSQLite3CipherAes128();

  /// Copy constructor
  wxSQLite3CipherAes128(const wxSQLite3CipherAes128& cipher);

  /// Destructor
  virtual ~wxSQLite3CipherAes128();

  /// Initialize the cipher instance based on global default settings
  /**
  * The parameters of the cipher instance are initialize with the global default settings of the associated cipher type.
  * \return true if the cipher instance could be initialized successfully, false otherwise
  */
  virtual bool InitializeFromGlobalDefault();

  /// Initialize the cipher instance based on current settings
  /**
  * The parameters of the cipher instance are initialize with the current settings of the associated cipher type
  * as defined in the given database connection.
  * \param db database instance representing a database connection
  * \return true if the cipher instance could be initialized successfully, false otherwise
  */
  virtual bool InitializeFromCurrent(wxSQLite3Database& db);

  /// Initialize the cipher instance based on current default settings
  /**
  * The parameters of the cipher instance are initialize with the current default settings of the associated cipher type
  * as defined in the given database connection.
  * \param db database instance representing a database connection
  * \return true if the cipher instance could be initialized successfully, false otherwise
  */
  virtual bool InitializeFromCurrentDefault(wxSQLite3Database& db);

  /// Apply the cipher parameters to a database connection
  /**
  * The parameters of the cipher instance are applied to the given database connection.
  * \param db database instance representing a database connection
  * \return true if the cipher parameters could be applied successfully, false otherwise
  */
  virtual bool Apply(wxSQLite3Database& db) const;
  virtual bool Apply(void* dbHandle) const;

  /// Set legacy mode
  void SetLegacy(bool legacy) { m_legacy = legacy; }

  /// Get legacy mode
  bool GetLegacy() const { return m_legacy; }

private:
  bool m_legacy; ///< Flag for legacy mode
};

/// Cipher class representing AES 256 bit encryption in CBC mode
class WXDLLIMPEXP_SQLITE3 wxSQLite3CipherAes256 : public wxSQLite3Cipher
{
public:
  /// Constructor
  wxSQLite3CipherAes256();

  /// Copy constructor
  wxSQLite3CipherAes256(const wxSQLite3CipherAes256& cipher);

  /// Destructor
  virtual ~wxSQLite3CipherAes256();

  /// Initialize the cipher instance based on global default settings
  /**
  * The parameters of the cipher instance are initialize with the global default settings of the associated cipher type.
  * \return true if the cipher instance could be initialized successfully, false otherwise
  */
  virtual bool InitializeFromGlobalDefault();

  /// Initialize the cipher instance based on current settings
  /**
  * The parameters of the cipher instance are initialize with the current settings of the associated cipher type
  * as defined in the given database connection.
  * \param db database instance representing a database connection
  * \return true if the cipher instance could be initialized successfully, false otherwise
  */
  virtual bool InitializeFromCurrent(wxSQLite3Database& db);

  /// Initialize the cipher instance based on current default settings
  /**
  * The parameters of the cipher instance are initialize with the current default settings of the associated cipher type
  * as defined in the given database connection.
  * \param db database instance representing a database connection
  * \return true if the cipher instance could be initialized successfully, false otherwise
  */
  virtual bool InitializeFromCurrentDefault(wxSQLite3Database& db);

  /// Apply the cipher parameters to a database connection
  /**
  * The parameters of the cipher instance are applied to the given database connection.
  * \param db database instance representing a database connection
  * \return true if the cipher parameters could be applied successfully, false otherwise
  */
  virtual bool Apply(wxSQLite3Database& db) const;
  virtual bool Apply(void* dbHandle) const;

  /// Set legacy mode
  void SetLegacy(bool legacy) { m_legacy = legacy; }

  /// Get legacy mode
  bool GetLegacy() const { return m_legacy; }

  /// Set iteration count of KDF function for ordinary key
  void SetKdfIter(int kdfIter) { m_kdfIter = kdfIter;  }

  /// Get iteration count of KDF function for ordinary key
  int GetKdfIter() const { return m_kdfIter; }

private:
  bool m_legacy;   ///< Flag for legacy mode
  int  m_kdfIter;  ///< Iteration count for KDF function
};

/// Cipher class representing ChaCha20 encryption with Poly1305 HMAC
class WXDLLIMPEXP_SQLITE3 wxSQLite3CipherChaCha20 : public wxSQLite3Cipher
{
public:
  /// Constructor
  wxSQLite3CipherChaCha20();

  /// Copy constructor
  wxSQLite3CipherChaCha20(const wxSQLite3CipherChaCha20& cipher);

  /// Destructor
  virtual ~wxSQLite3CipherChaCha20();

  /// Initialize the cipher instance based on global default settings
  /**
  * The parameters of the cipher instance are initialize with the global default settings of the associated cipher type.
  * \return true if the cipher instance could be initialized successfully, false otherwise
  */
  virtual bool InitializeFromGlobalDefault();

  /// Initialize the cipher instance based on current settings
  /**
  * The parameters of the cipher instance are initialize with the current settings of the associated cipher type
  * as defined in the given database connection.
  * \param db database instance representing a database connection
  * \return true if the cipher instance could be initialized successfully, false otherwise
  */
  virtual bool InitializeFromCurrent(wxSQLite3Database& db);

  /// Initialize the cipher instance based on current default settings
  /**
  * The parameters of the cipher instance are initialize with the current default settings of the associated cipher type
  * as defined in the given database connection.
  * \param db database instance representing a database connection
  * \return true if the cipher instance could be initialized successfully, false otherwise
  */
  virtual bool InitializeFromCurrentDefault(wxSQLite3Database& db);

  /// Apply the cipher parameters to a database connection
  /**
  * The parameters of the cipher instance are applied to the given database connection.
  * \param db database instance representing a database connection
  * \return true if the cipher parameters could be applied successfully, false otherwise
  */
  virtual bool Apply(wxSQLite3Database& db) const;
  virtual bool Apply(void* dbHandle) const;

  /// Set legacy mode
  void SetLegacy(bool legacy) { m_legacy = legacy; }

  /// Get legacy mode
  bool GetLegacy() const { return m_legacy; }

  /// Set iteration count of KDF function for ordinary key
  void SetKdfIter(int kdfIter) { m_kdfIter = kdfIter; }

  /// Get iteration count of KDF function for ordinary key
  int GetKdfIter() const { return m_kdfIter; }

private:
  bool m_legacy;   ///< Flag for legacy mode
  int  m_kdfIter;  ///< Iteration count for KDF function
};

/// Cipher class representing SQLCipher encryption (AES 256 bit in CBC mode with SHA1 HMAC)
class WXDLLIMPEXP_SQLITE3 wxSQLite3CipherSQLCipher : public wxSQLite3Cipher
{
public:
  /// Constructor
  wxSQLite3CipherSQLCipher();

  /// Copy constructor
  wxSQLite3CipherSQLCipher(const wxSQLite3CipherSQLCipher& cipher);

  /// Destructor
  virtual ~wxSQLite3CipherSQLCipher();

  /// Initialize the cipher instance based on global default settings
  /**
  * The parameters of the cipher instance are initialize with the global default settings of the associated cipher type.
  * \return true if the cipher instance could be initialized successfully, false otherwise
  */
  virtual bool InitializeFromGlobalDefault();

  /// Initialize the cipher instance based on current settings
  /**
  * The parameters of the cipher instance are initialize with the current settings of the associated cipher type
  * as defined in the given database connection.
  * \param db database instance representing a database connection
  * \return true if the cipher instance could be initialized successfully, false otherwise
  */
  virtual bool InitializeFromCurrent(wxSQLite3Database& db);

  /// Initialize the cipher instance based on current default settings
  /**
  * The parameters of the cipher instance are initialize with the current default settings of the associated cipher type
  * as defined in the given database connection.
  * \param db database instance representing a database connection
  * \return true if the cipher instance could be initialized successfully, false otherwise
  */
  virtual bool InitializeFromCurrentDefault(wxSQLite3Database& db);

  /// Apply the cipher parameters to a database connection
  /**
  * The parameters of the cipher instance are applied to the given database connection.
  * \param db database instance representing a database connection
  * \return true if the cipher parameters could be applied successfully, false otherwise
  */
  virtual bool Apply(wxSQLite3Database& db) const;
  virtual bool Apply(void* dbHandle) const;

  /// Initialize the cipher instance based on specific SQLCipher version
  /**
  * The cipher parameters are initialized to the default values of the given SQLCipher version.
  * Currently version 1, 2 and 3 of SQLCipher are supported.
  * If the version number is invalid, version 3 is assumed.
  * \param version the SQLCipher version
  */
  void InitializeVersionDefault(int version);

  /// Set legacy mode
  void SetLegacy(bool legacy) { m_legacy = legacy; }

  /// Get legacy mode
  bool GetLegacy() const { return m_legacy; }

  /// Get legacy version
  int GetLegacyVersion() const { return m_legacyVersion; }

  /// Set iteration count of KDF function for ordinary key
  void SetKdfIter(int kdfIter) { m_kdfIter = kdfIter; }

  /// Get iteration count of KDF function for ordinary key
  int GetKdfIter() const { return m_kdfIter; }

  /// Set iteration count of KDF function for HMAC key
  void SetFastKdfIter(int fastKdfIter) { m_fastKdfIter = fastKdfIter; }

  /// Get iteration count of KDF function for HMAC key
  int GetFastKdfIter() const { return m_fastKdfIter; }

  /// Set HMAC calculation status
  void SetHmacUse(bool hmacUse) { m_hmacUse = hmacUse; }

  /// Get HMAC calculation status
  bool GetHmacUse() const { return m_hmacUse; }

  /// Set the page number encoding for the HMAC calculation
  void SetHmacPgNo(int hmacPgNo) { m_hmacPgNo = hmacPgNo; }

  /// Get the page number encoding of the HMAC calculation
  int GetHmacPgNo() const { return m_hmacPgNo; }

  /// Set the salt mask for the HMAC calculation
  void SetHmacSaltMask(int hmacSaltMask) { m_hmacSaltMask = hmacSaltMask; }

  /// Get the salt mask of the HMAC calculation
  int GetHmacSaltMask() const { return m_hmacSaltMask; }

  /// KDF and HMAC algorithm types
  enum Algorithm
  {
    ALGORITHM_SHA1,
    ALGORITHM_SHA256,
    ALGORITHM_SHA512
  };

  /// Set the algorithm for the KDF function
  void SetKdfAlgorithm(Algorithm algorithm) { m_kdfAlgorithm = algorithm; }

  /// Set the algorithm for the KDF function
  Algorithm GetKdfAlgorithm() const { return m_kdfAlgorithm; }

  /// Set the algorithm for the HMAC function
  void SetHmacAlgorithm(Algorithm algorithm) { m_hmacAlgorithm = algorithm; }

  /// Set the algorithm for the HMAC function
  Algorithm GetHmacAlgorithm() const { return m_hmacAlgorithm; }

private:
  bool m_legacy;        ///< Flag for legacy mode
  int  m_legacyVersion; ///< Version number of a legacy SQLCipher database format
  int  m_kdfIter;       ///< Iteration count for KDF function for ordinary key
  int  m_fastKdfIter;   ///< Iteration count for KDF function for HMAC key
  bool m_hmacUse;       ///< Flag indicating whether HMACs should be used
  int  m_hmacPgNo;      ///< Encoding type for page number iin HMAC
  int  m_hmacSaltMask;  ///< Salt mask for HMAC calculation
  Algorithm m_kdfAlgorithm;  ///< KDF algorithm
  Algorithm m_hmacAlgorithm; ///< HMAC algorithm
};

/// Cipher class representing RC4 encryption (System.Data.SQLite)
class WXDLLIMPEXP_SQLITE3 wxSQLite3CipherRC4 : public wxSQLite3Cipher
{
public:
  /// Constructor
  wxSQLite3CipherRC4();

  /// Copy constructor
  wxSQLite3CipherRC4(const wxSQLite3CipherRC4& cipher);

  /// Destructor
  virtual ~wxSQLite3CipherRC4();

  /// Initialize the cipher instance based on global default settings
  /**
  * The parameters of the cipher instance are initialize with the global default settings of the associated cipher type.
  * \return true if the cipher instance could be initialized successfully, false otherwise
  */
  virtual bool InitializeFromGlobalDefault();

  /// Initialize the cipher instance based on current settings
  /**
  * The parameters of the cipher instance are initialize with the current settings of the associated cipher type
  * as defined in the given database connection.
  * \param db database instance representing a database connection
  * \return true if the cipher instance could be initialized successfully, false otherwise
  */
  virtual bool InitializeFromCurrent(wxSQLite3Database& db);

  /// Initialize the cipher instance based on current default settings
  /**
  * The parameters of the cipher instance are initialize with the current default settings of the associated cipher type
  * as defined in the given database connection.
  * \param db database instance representing a database connection
  * \return true if the cipher instance could be initialized successfully, false otherwise
  */
  virtual bool InitializeFromCurrentDefault(wxSQLite3Database& db);

  /// Apply the cipher parameters to a database connection
  /**
  * The parameters of the cipher instance are applied to the given database connection.
  * \param db database instance representing a database connection
  * \return true if the cipher parameters could be applied successfully, false otherwise
  */
  virtual bool Apply(wxSQLite3Database& db) const;
  virtual bool Apply(void* dbHandle) const;

#if 0
  // Currently no non-legacy mode available
  /// Set legacy mode
  void SetLegacy(bool legacy) { m_legacy = legacy; }
#endif

  /// Get legacy mode
  bool GetLegacy() const { return m_legacy; }

private:
  bool m_legacy; ///< Flag for legacy mode
};

/// Cipher class representing Ascon-128 encryption with Ascon tag
class WXDLLIMPEXP_SQLITE3 wxSQLite3CipherAscon128 : public wxSQLite3Cipher
{
public:
  /// Constructor
  wxSQLite3CipherAscon128();

  /// Copy constructor
  wxSQLite3CipherAscon128(const wxSQLite3CipherAscon128& cipher);

  /// Destructor
  virtual ~wxSQLite3CipherAscon128();

  /// Initialize the cipher instance based on global default settings
  /**
  * The parameters of the cipher instance are initialize with the global default settings of the associated cipher type.
  * \return true if the cipher instance could be initialized successfully, false otherwise
  */
  virtual bool InitializeFromGlobalDefault();

  /// Initialize the cipher instance based on current settings
  /**
  * The parameters of the cipher instance are initialize with the current settings of the associated cipher type
  * as defined in the given database connection.
  * \param db database instance representing a database connection
  * \return true if the cipher instance could be initialized successfully, false otherwise
  */
  virtual bool InitializeFromCurrent(wxSQLite3Database& db);

  /// Initialize the cipher instance based on current default settings
  /**
  * The parameters of the cipher instance are initialize with the current default settings of the associated cipher type
  * as defined in the given database connection.
  * \param db database instance representing a database connection
  * \return true if the cipher instance could be initialized successfully, false otherwise
  */
  virtual bool InitializeFromCurrentDefault(wxSQLite3Database& db);

  /// Apply the cipher parameters to a database connection
  /**
  * The parameters of the cipher instance are applied to the given database connection.
  * \param db database instance representing a database connection
  * \return true if the cipher parameters could be applied successfully, false otherwise
  */
  virtual bool Apply(wxSQLite3Database& db) const;
  virtual bool Apply(void* dbHandle) const;

#if 0
  // Currently no legacy mode available
  /// Set legacy mode
  void SetLegacy(bool legacy) { m_legacy = legacy; }

  /// Get legacy mode
  bool GetLegacy() const { return m_legacy; }
#endif

  /// Set iteration count of KDF function for ordinary key
  void SetKdfIter(int kdfIter) { m_kdfIter = kdfIter; }

  /// Get iteration count of KDF function for ordinary key
  int GetKdfIter() const { return m_kdfIter; }

private:
  bool m_legacy;   ///< Flag for legacy mode
  int  m_kdfIter;  ///< Iteration count for KDF function
};

/// Cipher class representing Aegis encryption with Ascon tag
class WXDLLIMPEXP_SQLITE3 wxSQLite3CipherAegis : public wxSQLite3Cipher
{
public:
  /// Constructor
  wxSQLite3CipherAegis();

  /// Copy constructor
  wxSQLite3CipherAegis(const wxSQLite3CipherAegis& cipher);

  /// Destructor
  virtual ~wxSQLite3CipherAegis();

  /// Initialize the cipher instance based on global default settings
  /**
  * The parameters of the cipher instance are initialize with the global default settings of the associated cipher type.
  * \return true if the cipher instance could be initialized successfully, false otherwise
  */
  virtual bool InitializeFromGlobalDefault();

  /// Initialize the cipher instance based on current settings
  /**
  * The parameters of the cipher instance are initialize with the current settings of the associated cipher type
  * as defined in the given database connection.
  * \param db database instance representing a database connection
  * \return true if the cipher instance could be initialized successfully, false otherwise
  */
  virtual bool InitializeFromCurrent(wxSQLite3Database& db);

  /// Initialize the cipher instance based on current default settings
  /**
  * The parameters of the cipher instance are initialize with the current default settings of the associated cipher type
  * as defined in the given database connection.
  * \param db database instance representing a database connection
  * \return true if the cipher instance could be initialized successfully, false otherwise
  */
  virtual bool InitializeFromCurrentDefault(wxSQLite3Database& db);

  /// Apply the cipher parameters to a database connection
  /**
  * The parameters of the cipher instance are applied to the given database connection.
  * \param db database instance representing a database connection
  * \return true if the cipher parameters could be applied successfully, false otherwise
  */
  virtual bool Apply(wxSQLite3Database& db) const;
  virtual bool Apply(void* dbHandle) const;

#if 0
  // Currently no legacy mode available
  /// Set legacy mode
  void SetLegacy(bool legacy) { m_legacy = legacy; }

  /// Get legacy mode
  bool GetLegacy() const { return m_legacy; }
#endif

  /// Set number of iterations of KDF function for ordinary key
  void SetIterCount(int iterCount) { m_tcost = iterCount; }

  /// Get number of iterations of KDF function for ordinary key
  int GetIterCount() const { return m_tcost; }

  /// Set size of memory in kB of KDF function for ordinary key
  void SetMemorySize(int memSize) { m_mcost = memSize; }

  /// Get size of memory in kB of KDF function for ordinary key
  int GetMemorySize() const { return m_mcost; }

  /// Set number of threads of KDF function for ordinary key
  void SetThreadCount(int threads) { m_pcost = threads; }

  /// Get number of threads of KDF function for ordinary key
  int GetThreadCount() const { return m_pcost; }

  /// Aegis algorithm types
  enum Algorithm
  {
    ALGORITHM_AEGIS_128L = 1,
    ALGORITHM_AEGIS_128X2,
    ALGORITHM_AEGIS_128X4,
    ALGORITHM_AEGIS_256,
    ALGORITHM_AEGIS_256X2,
    ALGORITHM_AEGIS_256X4
  };

  /// Set Aegis algorithm to be used for encryption
  void SetAlgorithm(Algorithm algorithm) { m_algorithm = algorithm; }

  /// Get Aegis algorithm used for encryption
  Algorithm GetAlgorithm() const { return m_algorithm; }

private:
  bool m_legacy;  ///< Flag for legacy mode
  int  m_tcost;   ///< Time cost (number of iterations) for KDF function
  int  m_mcost;   ///< Amount of memory in kB for KDF function
  int  m_pcost;   ///< Parallelism (number of threads) for KDF function
  Algorithm m_algorithm; ///< Aegis algorithm to be used for encryption
};


/// Interface for a user defined hook function
/**
*/
class WXDLLIMPEXP_SQLITE3 wxSQLite3Hook
{
public:
  /// Codes identifying the command for which the hook is called
  enum wxUpdateType
  {
    SQLITE_DELETE              =  9,
    SQLITE_INSERT              = 18,
    SQLITE_UPDATE              = 23
  };
  /// Default constructor
  wxSQLite3Hook() : m_db(NULL) {}

  /// Virtual destructor
  virtual ~wxSQLite3Hook() {}

  /// Execute the commit hook callback function
  /**
  * Please refer to the SQLite documentation for further information.
  * \return true to request rollback of the transaction, false to continue with commit
  */
  virtual bool CommitCallback() { return false; }

  /// Execute the rollback hook callback function
  /**
  * Please refer to the SQLite documentation for further information.
  */
  virtual void RollbackCallback() {}

  /// Execute the hook callback function
  /**
  * Please refer to the SQLite documentation for further information about the
  * meaning of the parameters.
  *
  * \param type wxHookType. The value signifies what kind of operation is to be authorized.
  * \param database Name of the database
  * \param table Name of the table
  * \param rowid The rowid of the affected row
  */
  virtual void UpdateCallback(wxUpdateType WXUNUSED(type),
                              const wxString& WXUNUSED(database), const wxString& WXUNUSED(table),
                              wxLongLong WXUNUSED(rowid)) {}

  /// Execute the write-ahead log hook callback function
  /**
  * Please refer to the SQLite documentation for further information about the
  * meaning of the parameters.
  *
  * \param database Name of the database
  * \param numPages the number of pages
  */
  virtual int WriteAheadLogCallback(const wxString& WXUNUSED(database),
                                    int WXUNUSED(numPages)) { return 0; }

  /// Set the associated database
  /**
  * For the write-ahead log hook the associated database is set internally.
  * \param db pointer to the associated database instance
  */
  void SetDatabase(wxSQLite3Database* db) { m_db = db; }

  /// Get the associated database
  /**
  * For the write-ahead log hook the associated database can be accessed.
  *
  * \return pointer to the associated database instance
  * \note Access to the associated database is only provided for write-ahead log hooks.
  */
  wxSQLite3Database* GetDatabase() const { return m_db; }

private:
  wxSQLite3Database* m_db;
};

/// Interface for a user defined backup progress function
/**
*/
class WXDLLIMPEXP_SQLITE3 wxSQLite3BackupProgress
{
public:
  /// Default constructor
  wxSQLite3BackupProgress() {}

  /// Virtual destructor
  virtual ~wxSQLite3BackupProgress() {}

  /// Execute the backup progress callback
  /**
  * This method allows an application to display information about the progress of a backup
  * operation to the user.
  * \param totalPages total number of pages to copy
  * \param remainingPages number of pages remaining to be copied
  * \return TRUE if backup should continue, FALSE otherwise
  */
  virtual bool Progress(int WXUNUSED(totalPages), int WXUNUSED(remainingPages)) { return true; }
};

/// Interface for a user defined collation sequence
/**
*/
class WXDLLIMPEXP_SQLITE3 wxSQLite3Collation
{
public:
  /// Virtual destructor
  virtual ~wxSQLite3Collation() {}

  /// Execute a comparison using a user-defined collation sequence
  /**
  * Please refer to the SQLite documentation for further information.
  * \param text1 first text string
  * \param text2 second text string
  * \return an integer < 0, = 0, or > 0 depending on whether text1 is less than, equal to, or greater than text2.
  */
  virtual int Compare(const wxString& text1, const wxString& text2) { return text1.Cmp(text2); }
};

/// Result set of a SQL query
class WXDLLIMPEXP_SQLITE3 wxSQLite3ResultSet
{
public:
  /// Constructor
  wxSQLite3ResultSet();

  /// Copy constructor
  wxSQLite3ResultSet(const wxSQLite3ResultSet& resultSet);

  /// Constructor for internal use
  wxSQLite3ResultSet(wxSQLite3DatabaseReference* db, 
                     wxSQLite3StatementReference* stmt,
                     bool eof, bool first = true);

  /// Assignment constructor
  wxSQLite3ResultSet& operator=(const wxSQLite3ResultSet& resultSet);

  /// Destructor
  /**
  */
  virtual ~wxSQLite3ResultSet();

  /// Get the number of columns in the result set
  /**
  * \return number of columns in result set
  */
  int GetColumnCount() const;

  /// Find the index of a column by name
  /**
  * \param columnName name of the column
  * \return index of the column. Indices start with 0.
  */
  int FindColumnIndex(const wxString& columnName) const;

  /// Get the name of a column
  /**
  * \param columnIndex index of the column. Indices start with 0.
  * \return column name as string
  */
  wxString GetColumnName(int columnIndex) const;

  /// Get the declared type of a column
  /**
  * \param columnIndex index of the column. Indices start with 0.
  * \return type string as specified in the table definition
  */
  wxString GetDeclaredColumnType(int columnIndex) const;

  /// Get the actual type of a column
  /**
  * \param columnIndex index of the column. Indices start with 0.
  * \return column type as one of the values WXSQLITE_INTEGER, WXSQLITE_FLOAT, WXSQLITE_TEXT, WXSQLITE_BLOB, or WXSQLITE_NULL
  */
  int GetColumnType(int columnIndex) const;

  /// Get the database name of a column
  /**
  * \param columnIndex index of the column. Indices start with 0.
  * \return database name the column belongs to or empty string
  *
  * This method is only available if SQLite has been compiled with SQLITE_ENABLE_COLUMN_METADATA defined.
  */
  wxString GetDatabaseName(int columnIndex) const;

  /// Get the table name of a column
  /**
  * \param columnIndex index of the column. Indices start with 0.
  * \return table name the column belongs to or empty string
  *
  * This method is only available if SQLite has been compiled with SQLITE_ENABLE_COLUMN_METADATA defined.
  */
  wxString GetTableName(int columnIndex) const;

  /// Get the origin name of a column
  /**
  * \param columnIndex index of the column. Indices start with 0.
  * \return origin name the column belongs to or empty string
  *
  * This method is only available if SQLite has been compiled with SQLITE_ENABLE_COLUMN_METADATA defined.
  */
  wxString GetOriginName(int columnIndex) const;

  /// Get a column as a string using the column index
  /**
  * \param columnIndex index of the column. Indices start with 0.
  * \return value of the column as string
  */
  wxString GetAsString(int columnIndex) const;

  /// Get a column as a string using the column name
  /**
  * \param columnName name of the column
  * \return value of the column
  */
  wxString GetAsString(const wxString& columnName) const;

  /// Get a column as an integer using the column index
  /**
  * \param columnIndex index of the column. Indices start with 0.
  * \param nullValue value to be returned in case the column is NULL
  * \return value of the column
  */
  int GetInt(int columnIndex, int nullValue = 0) const;

  /// Get a column as an integer using the column name
  /**
  * \param columnName name of the column
  * \param nullValue value to be returned in case the column is NULL
  * \return value of the column
  */
  int GetInt(const wxString& columnName, int nullValue = 0) const;

  /// Get a column as a 64-bit integer using the column index
  /**
  * \param columnIndex index of the column. Indices start with 0.
  * \param nullValue value to be returned in case the column is NULL
  * \return value of the column
  */
  wxLongLong GetInt64(int columnIndex, wxLongLong nullValue = 0) const;

  /// Get a column as a 64-bit integer using the column name
  /**
  * \param columnName name of the column
  * \param nullValue value to be returned in case the column is NULL
  * \return value of the column
  */
  wxLongLong GetInt64(const wxString& columnName, wxLongLong nullValue = 0) const;

  /// Get a column as a double using the column index
  /**
  * \param columnIndex index of the column. Indices start with 0.
  * \param nullValue value to be returned in case the column is NULL
  * \return value of the column
  */
  double GetDouble(int columnIndex, double nullValue = 0.0) const;

  /// Get a column as a double using the column name
  /**
  * \param columnName name of the column
  * \param nullValue value to be returned in case the column is NULL
  * \return value of the column
  */
  double GetDouble(const wxString& columnName, double nullValue = 0.0) const;

  /// Get a column as a string using the column index
  /**
  * \param columnIndex index of the column. Indices start with 0.
  * \param nullValue value to be returned in case the column is NULL
  * \return value of the column
  */
  wxString GetString(int columnIndex, const wxString& nullValue = wxEmptyString) const;

  /// Get a column as a string using the column name
  /**
  * \param columnName name of the column
  * \param nullValue value to be returned in case the column is NULL
  * \return value of the column
  */
  wxString GetString(const wxString& columnName, const wxString& nullValue = wxEmptyString) const;

  /// Get a column as a BLOB using the column index
  /**
  * \param columnIndex index of the column. Indices start with 0.
  * \param[out] len length of the blob in bytes
  * \return value of the column
  */
  const unsigned char* GetBlob(int columnIndex, int& len) const;

  /// Get a column as a BLOB using the column name
  /**
  * \param columnName name of the column
  * \param[out] len length of the blob in bytes
  * \return value of the column
  */
  const unsigned char* GetBlob(const wxString& columnName, int& len) const;

  /// Get a column as a BLOB using the column index and append to memory buffer
  /**
  * \param columnIndex index of the column. Indices start with 0.
  * \param[out] buffer the memory buffer to which the BLOB value is appended
  * \return reference to the memory buffer
  */
  wxMemoryBuffer& GetBlob(int columnIndex, wxMemoryBuffer& buffer) const;

  /// Get a column as a BLOB using the column index and append to memory buffer
  /**
  * \param columnName name of the column
  * \param[out] buffer the memory buffer to which the BLOB value is appended
  * \return reference to the memory buffer
  */
  wxMemoryBuffer& GetBlob(const wxString& columnName, wxMemoryBuffer& buffer) const;

  /// Get a column as a date value using the column index
  /**
  * Date value is expected to be in format 'YYYY-MM-DD'.
  * \param columnIndex index of the column. Indices start with 0.
  * \return value of the column
  */
  wxDateTime GetDate(int columnIndex) const;

  /// Get a column as a date value using the column name
  /**
  * Date value is expected to be in format 'YYYY-MM-DD'.
  * \param columnName name of the column
  * \return value of the column
  */
  wxDateTime GetDate(const wxString& columnName) const;

  /// Get a column as a time value using the column index
  /**
  * Date value is expected to be in format 'HH:MM:SS'.
  * \param columnIndex index of the column. Indices start with 0.
  * \return value of the column
  */
  wxDateTime GetTime(int columnIndex) const;

  /// Get a column as a time value using the column name
  /**
  * Date value is expected to be in format 'HH:MM:SS'.
  * \param columnName name of the column
  * \return value of the column
  */
  wxDateTime GetTime(const wxString& columnName) const;

  /// Get a column as a date and time value using the column index
  /**
  * Date value is expected to be in format 'YYYY-MM-DD HH:MM:SS'.
  * \param columnIndex index of the column. Indices start with 0.
  * \return value of the column
  */
  wxDateTime GetDateTime(int columnIndex) const;

  /// Get a column as a date and time value using the column name
  /**
  * Date value is expected to be in format 'YYYY-MM-DD HH:MM:SS'.
  * \param columnName name of the column
  * \return value of the column
  */
  wxDateTime GetDateTime(const wxString& columnName) const;

  /// Get a column as a timestamp value using the column index
  /**
  * Date value is expected to be in format 'YYYY-MM-DD HH:MM:SS.mmm'.
  * \param columnIndex index of the column. Indices start with 0.
  * \return value of the column
  */
  wxDateTime GetTimestamp(int columnIndex) const;

  /// Get a column as a timestamp value using the column name
  /**
  * Date value is expected to be in format 'YYYY-MM-DD HH:MM:SS.mmm'.
  * \param columnName name of the column
  * \return value of the column
  */
  wxDateTime GetTimestamp(const wxString& columnName) const;

  /// Get a column as a date and time value using the column index
  /**
  * The date/time value is expected to be stored in the database as a numeric value (i.e. int64),
  * measured in milliseconds since 1970-01-01.
  *
  * \param columnIndex index of the column. Indices start with 0.
  * \return value of the column
  */
  wxDateTime GetNumericDateTime(int columnIndex) const;

  /// Get a column as a date and time value using the column name
  /**
  * The date/time value is expected to be stored in the database as a numeric value (i.e. int64),
  * measured in milliseconds since 1970-01-01.
  *
  * \param columnName name of the column
  * \return value of the column
  */
  wxDateTime GetNumericDateTime(const wxString& columnName) const;

  /// Get a column as a date and time value using the column index
  /**
  * The date/time value is expected to be stored in the database as an integer value (i.e. int64),
  * measured in seconds since 1970-01-01.
  *
  * \param columnIndex index of the column. Indices start with 0.
  * \return value of the column
  */
  wxDateTime GetUnixDateTime(int columnIndex) const;

  /// Get a column as a date and time value using the column name
  /**
  * The date/time value is expected to be stored in the database as an integer value (i.e. int64),
  * measured in seconds since 1970-01-01.
  *
  * \param columnName name of the column
  * \return value of the column
  */
  wxDateTime GetUnixDateTime(const wxString& columnName) const;

  /// Get a column as a date and time value using the column index
  /**
  * The date/time value is expected to be stored in the database as a Julian Day Number (i.e. double).
  *
  * \param columnIndex index of the column. Indices start with 0.
  * \return value of the column
  */
  wxDateTime GetJulianDayNumber(int columnIndex) const;

  /// Get a column as a date and time value using the column name
  /**
  * The date/time value is expected to be stored in the database as a Julian Day Number (i.e. double).
  *
  * \param columnName name of the column
  * \return value of the column
  */
  wxDateTime GetJulianDayNumber(const wxString& columnName) const;

  /// Get a column as a date and time value using the column index
  /**
  * The date/time value is interpreted based on the type of column value.
  *
  * \param columnIndex index of the column. Indices start with 0.
  * \param milliSeconds interpret integer value as milliseconds since 1970-01-01, default: false
  * \return value of the column
  */
  wxDateTime GetAutomaticDateTime(int columnIndex, bool milliSeconds = false) const;

  /// Get a column as a date and time value using the column name
  /**
  * The date/time value is interpreted based on the type of column value.
  *
  * \param columnName name of the column
  * \param milliSeconds interpret integer value as milliseconds since 1970-01-01, default: false
  * \return value of the column
  */
  wxDateTime GetAutomaticDateTime(const wxString& columnName, bool milliSeconds = false) const;

  /// Get a column as a boolean value using the column index
  /**
  * \param columnIndex index of the column. Indices start with 0.
  * \return value of the column
  */
  bool GetBool(int columnIndex) const;

  /// Get a column as a boolean value using the column name
  /**
  * \param columnName name of the column
  * \return value of the column
  */
  bool GetBool(const wxString& columnName) const;

  /// Check whether a column has a NULL value using the column index
  /**
  * \param columnIndex index of the column. Indices start with 0.
  * \return TRUE if the value is NULL, FALSE otherwise
  */
  bool IsNull(int columnIndex) const;

  /// Check whether a column has a NULL value using the column name
  /**
  * \param columnName name of the column
  * \return TRUE if the value is NULL, FALSE otherwise
  */
  bool IsNull(const wxString& columnName) const;

  /// Check whether all rows of the result set have been processed
  /**
  * \return TRUE if all rows of the result have been processed, FALSE otherwise
  */
  bool Eof() const;

  /// Check whether the cursor has been moved
  /**
  * \return TRUE if the cursor has been moved using method NextRow, FALSE otherwise
  */
  bool CursorMoved() const;

  /// Retrieve next row of the result set
  /**
  * Advances the cursor to the next row.
  * On creation of the result set the cursor is positioned BEFORE the first row, i.e.
  * the first call to this method makes the first row available for processing.
  * \return TRUE while there are still rows to process, FALSE otherwise
  */
  bool NextRow();

  /// Finalize the result set
  /**
  */
  void Finalize();

  /// Get the original SQL string for preparing the query statement
  /**
  * \return the original SQL string used to prepare the query statement
  */
  wxString GetSQL() const;

  /// Get the original SQL string for preparing the query statement with expanded bound parameters
  /**
  * \return the original SQL string used to prepare the statement with expanded bound parameters
  */
  wxString GetExpandedSQL() const;

  /// Validate associated SQLite database and statement
  /**
  * \return TRUE if both, a SQLite database and a SQLite statement, are associated, FALSE otherwise
  */
  bool IsOk() const;

private:
  /// Check the validity of the associated statement
  void CheckStmt() const;

  /// Finalize the result set (internal)
  void Finalize(wxSQLite3DatabaseReference* db,wxSQLite3StatementReference* stmt);

  wxSQLite3DatabaseReference*  m_db;   ///< associated database
  wxSQLite3StatementReference* m_stmt; ///< associated statement
  bool  m_eof;      ///< Flag for end of result set
  bool  m_first;    ///< Flag for first row of the result set
  int   m_cols;     ///< Number of columns in row set
};


/// Holds the complete result set of a SQL query
class WXDLLIMPEXP_SQLITE3 wxSQLite3Table
{
public:
  /// Constructor
  wxSQLite3Table();

  wxSQLite3Table(const wxSQLite3Table& table);

  wxSQLite3Table(char** results, int rows, int cols);

  virtual ~wxSQLite3Table();

  wxSQLite3Table& operator=(const wxSQLite3Table& table);

  /// Get the number of columns in the result set
  /**
  * \return the number of columns
  */
  int GetColumnCount() const;

  /// Get the number of rows in the result set
  /**
  * \return the number of rows
  */
  int GetRowCount() const;

  /// Find the index of a column by name
  /**
  * \param columnName name of the column
  * \return the index of the column
  */
  int FindColumnIndex(const wxString& columnName) const;

  /// Get the name of a column
  /**
  * \param columnIndex index of the column. Indices start with 0.
  * \return name of the column
  */
  wxString GetColumnName(int columnIndex) const;

  /// Get a column as a string using the column index
  /**
  * \param columnIndex index of the column. Indices start with 0.
  * \return value of the column as a string
  *
  * \note This method returns values of type <code>double</code>
  * always using the point character as the decimal separator.
  * This is SQLite default behaviour. Use method wxSQLite3Table::GetDouble
  * to apply correct conversion from <code>string</code> to <code>double</code>.
  */
  wxString GetAsString(int columnIndex) const;

  /// Get a column as a string using the column name
  /**
  * \param columnName name of the column
  * \return value of the column as a string
  *
  * \note This method returns values of type <code>double</code>
  * always using the point character as the decimal separator.
  * This is SQLite default behaviour. Use method wxSQLite3Table::GetDouble
  * to apply correct conversion from <code>string</code> to <code>double</code>.
  */
  wxString GetAsString(const wxString& columnName) const;

  /// Get a column as an integer using the column index
  /**
  * \param columnIndex index of the column. Indices start with 0.
  * \param nullValue value to be returned in case the column is NULL
  * \return value of the column
  */
  int GetInt(int columnIndex, int nullValue = 0) const;

  /// Get a column as an integer using the column name
  /**
  * \param columnName name of the column
  * \param nullValue value to be returned in case the column is NULL
  * \return value of the column
  */
  int GetInt(const wxString& columnName, int nullValue = 0) const;

  /// Get a column as a 64-bit integer using the column index
  /**
  * \param columnIndex index of the column. Indices start with 0.
  * \param nullValue value to be returned in case the column is NULL
  * \return value of the column
  */
  wxLongLong GetInt64(int columnIndex, wxLongLong nullValue = 0) const;

  /// Get a column as an integer using the column name
  /**
  * \param columnName name of the column
  * \param nullValue value to be returned in case the column is NULL
  * \return value of the column
  */
  wxLongLong GetInt64(const wxString& columnName, wxLongLong nullValue = 0) const;

  /// Get a column as a double using the column index
  /**
  * \param columnIndex index of the column. Indices start with 0.
  * \param nullValue value to be returned in case the column is NULL
  * \return value of the column
  */
  double GetDouble(int columnIndex, double nullValue = 0.0) const;

  /// Get a column as a double using the column name
  /**
  * \param columnName name of the column
  * \param nullValue value to be returned in case the column is NULL
  * \return value of the column
  */
  double GetDouble(const wxString& columnName, double nullValue = 0.0) const;

  /// Get a column as a string using the column index
  /**
  * \param columnIndex index of the column. Indices start with 0.
  * \param nullValue value to be returned in case the column is NULL
  * \return value of the column
  */
  wxString GetString(int columnIndex, const wxString& nullValue = wxEmptyString) const;

  /// Get a column as a string using the column name
  /**
  * \param columnName name of the column
  * \param nullValue value to be returned in case the column is NULL
  * \return value of the column
  */
  wxString GetString(const wxString& columnName, const wxString& nullValue = wxEmptyString) const;

  /// Get a column as a date value using the column index
  /**
  * \param columnIndex index of the column. Indices start with 0.
  * \return value of the column
  */
  wxDateTime GetDate(int columnIndex) const;

  /// Get a column as a date value using the column name
  /**
  * \param columnName name of the column
  * \return value of the column
  */
  wxDateTime GetDate(const wxString& columnName) const;

  /// Get a column as a time value using the column index
  /**
  * \param columnIndex index of the column. Indices start with 0.
  * \return value of the column
  */
  wxDateTime GetTime(int columnIndex) const;

  /// Get a column as a time value using the column name
  /**
  * \param columnName name of the column
  * \return value of the column
  */
  wxDateTime GetTime(const wxString& columnName) const;

  /// Get a column as a date/time value using the column index
  /**
  * \param columnIndex index of the column. Indices start with 0.
  * \return value of the column
  */
  wxDateTime GetDateTime(int columnIndex) const;

  /// Get a column as a date/time value using the column name
  /**
  * \param columnName name of the column
  * \return value of the column
  */
  wxDateTime GetDateTime(const wxString& columnName) const;

  /// Get a column as a boolean using the column index
  /**
  * \param columnIndex index of the column. Indices start with 0.
  * \return value of the column
  */
  bool GetBool(int columnIndex) const;

  /// Get a column as a boolean using the column name
  /**
  * \param columnName name of the column
  * \return value of the column
  */
  bool GetBool(const wxString& columnName) const;

  /// Check whether the column selected by index is a NULL value
  /**
  * \param columnIndex index of the column. Indices start with 0.
  * \return TRUE if the value is NULL, FALSE otherwise
  */
  bool IsNull(int columnIndex) const;

  /// Check whether the column selected by name is a NULL value
  /**
  * \param columnName name of the column
  * \return TRUE if the value is NULL, FALSE otherwise
  */
  bool IsNull(const wxString& columnName) const;

  /// Set the current row
  /**
  * \param row index of the requested row. Indices start with 0.
  */
  void SetRow(int row);

  /// Finalize the result set
  /**
  */
  void Finalize();

  /// Validate associated SQLite resultset
  /**
  * \return TRUE if SQLite resultset is associated, FALSE otherwise
  */
  bool IsOk() const;

private:
    /// Check for valid results
    void CheckResults() const;

    int m_cols;        ///< Number of columns
    int m_rows;        ///< Number of rows
    int m_currentRow;  ///< Index of the current row
    char** m_results;  ///< SQLite3 result buffer
};


/// Represents a prepared SQL statement
class WXDLLIMPEXP_SQLITE3 wxSQLite3Statement
{
public:
  /// Constructor
  /**
  */
  wxSQLite3Statement();

  /// Copy constructor
  /**
  */
  wxSQLite3Statement(const wxSQLite3Statement& statement);

  /// Assignment constructor
  /**
  */
  wxSQLite3Statement& operator=(const wxSQLite3Statement& statement);

  /// Constructor (internal use only)
  /**
  */
  wxSQLite3Statement(wxSQLite3DatabaseReference* db, wxSQLite3StatementReference* stmt);

  /// Destructor
  /**
  */
  virtual ~wxSQLite3Statement();

  /// Execute the database update represented by this statement
  /**
  * \return the number of database rows that were changed (or inserted or deleted)
  */
  int ExecuteUpdate();

  /// Execute the query represented by this statement
  /**
  * \return result set instance
  */
  wxSQLite3ResultSet ExecuteQuery();

  /// Execute a scalar SQL query statement given as a wxString
  /**
  * Allows to easily retrieve the result of queries returning a single integer result
  * like SELECT COUNT(*) FROM table WHERE condition.
  * \return first column of first row as an int
  */
  int ExecuteScalar();

  /// Get the number of statement parameters
  /**
  * \return the number of parameters in the prepared statement
  */
  int GetParamCount() const;

  /// Get the index of a parameter with a given name
  /**
  * \param paramName
  * \return the index of the parameter with the given name. The name must match exactly.
  * If there is no parameter with the given name, return 0.
  */
  int GetParamIndex(const wxString& paramName) const;

  /// Get the name of a paramater at the given position
  /**
  * \param paramIndex index of the parameter. The first parameter has an index of 1.
  * \return the name of the paramIndex-th parameter in the precompiled statement.
  * Parameters of the form ":AAA" or "$VVV" have a name which is the string ":AAA" or "$VVV".
  * Parameters of the form "?" have no name.
  */
  wxString GetParamName(int paramIndex) const;

  /// Bind parameter to a string value
  /**
  * \param paramIndex index of the parameter. The first parameter has an index of 1.
  * \param stringValue value of the parameter
  */
  void Bind(int paramIndex, const wxString& stringValue);

  /// Bind parameter to a integer value
  /**
  * \param paramIndex index of the parameter. The first parameter has an index of 1.
  * \param intValue value of the parameter
  */
  void Bind(int paramIndex, int intValue);

  /// Bind parameter to a 64-bit integer value
  /**
  * \param paramIndex index of the parameter. The first parameter has an index of 1.
  * \param int64Value value of the parameter
  */
  void Bind(int paramIndex, wxLongLong int64Value);

  /// Bind parameter to a double value
  /**
  * \param paramIndex index of the parameter. The first parameter has an index of 1.
  * \param doubleValue value of the parameter
  */
  void Bind(int paramIndex, double doubleValue);

  /// Bind parameter to a utf-8 character string value
  /**
  * \param paramIndex index of the parameter. The first parameter has an index of 1.
  * \param charValue value of the parameter
  */
  void Bind(int paramIndex, const char* charValue);

  /// Bind parameter to a BLOB value
  /**
  * \param paramIndex index of the parameter. The first parameter has an index of 1.
  * \param blobValue value of the parameter
  * \param blobLen length of the blob in bytes
  */
  void Bind(int paramIndex, const unsigned char* blobValue, int blobLen);

  /// Bind parameter to a BLOB value
  /**
  * \param paramIndex index of the parameter. The first parameter has an index of 1.
  * \param blobValue value of the parameter
  */
  void Bind(int paramIndex, const wxMemoryBuffer& blobValue);

  /// Bind parameter to a pointer value
  /**
  * \param paramIndex index of the parameter. The first parameter has an index of 1.
  * \param pointer pointer value of the parameter
  * \param pointerType descriptive name of the pointer type as expected by the extension module
  * \param DeletePointer pointer to a function for deleting the object pointed to by the pointer after use in SQLite (default: NULL)
  */
  void Bind(int paramIndex, void* pointer, const wxString& pointerType, void(*DeletePointer)(void*) = NULL);

  /// Bind parameter to a date value
  /**
  * Only the date part is stored in format 'YYYY-MM-DD'.
  * \param paramIndex index of the parameter. The first parameter has an index of 1.
  * \param date value of the parameter
  */
  void BindDate(int paramIndex, const wxDateTime& date);

  /// Bind parameter to a time value
  /**
  * Only the time part is stored in format 'HH:MM:SS'.
  * \param paramIndex index of the parameter. The first parameter has an index of 1.
  * \param time value of the parameter
  */
  void BindTime(int paramIndex, const wxDateTime& time);

  /// Bind parameter to a date and time value
  /**
  * Date and time are stored in format 'YYYY-MM-DD HH:MM:SS'.
  * \param paramIndex index of the parameter. The first parameter has an index of 1.
  * \param datetime value of the parameter
  */
  void BindDateTime(int paramIndex, const wxDateTime& datetime);

  /// Bind parameter to a timestamp value
  /**
  * Timestamp is stored in format 'YYYY-MM-DD HH:MM:SS.mmm'.
  * \param paramIndex index of the parameter. The first parameter has an index of 1.
  * \param timestamp value of the parameter
  */
  void BindTimestamp(int paramIndex, const wxDateTime& timestamp);

  /// Bind parameter to a date and time value
  /**
  * The date/time value is transferred to the database as a numeric value (i.e. int64).
  * The value is measured in milliseconds since 1970-01-01.
  *
  * \param paramIndex index of the parameter. The first parameter has an index of 1.
  * \param datetime value of the parameter
  */
  void BindNumericDateTime(int paramIndex, const wxDateTime& datetime);

  /// Bind parameter to a date and time value
  /**
  * The date/time value is transferred to the database as an integer value.
  * The value is measured in seconds since 1970-01-01.
  *
  * \param paramIndex index of the parameter. The first parameter has an index of 1.
  * \param datetime value of the parameter
  */
  void BindUnixDateTime(int paramIndex, const wxDateTime& datetime);

  /// Bind parameter to a date and time value
  /**
  * The date/time value is transferred to the database as a Julian Day Number value (i.e. double).
  *
  * \param paramIndex index of the parameter. The first parameter has an index of 1.
  * \param datetime value of the parameter
  */
  void BindJulianDayNumber(int paramIndex, const wxDateTime& datetime);

  /// Bind parameter to a boolean value
  /**
  * \param paramIndex index of the parameter. The first parameter has an index of 1.
  * \param value value of the parameter
  */
  void BindBool(int paramIndex, bool value);

  /// Bind parameter to a NULL value
  /**
  * \param paramIndex index of the parameter. The first parameter has an index of 1.
  */
  void BindNull(int paramIndex);

  /// Bind parameter to a Zero BLOB value
  /**
  * Space for a BLOB is reserved and filled with binary zeros for later reference
  * through a BLOB handle.
  *
  * \param paramIndex index of the parameter. The first parameter has an index of 1.
  * \param blobSize size of the BLOB
  */
  void BindZeroBlob(int paramIndex, int blobSize);

  /// Clear all parameter bindings
  /**
  * Sets all the parameters in the prepared SQL statement back to NULL.
  */
  void ClearBindings();

  /// Get the original SQL string for the prepared statement
  /**
  * \return the original SQL string used to prepare the statement
  */
  wxString GetSQL() const;

  /// Get the original SQL string for the prepared statement with expanded bound parameters
  /**
  * \return the original SQL string used to prepare the statement with expanded bound parameters
  */
  wxString GetExpandedSQL() const;

  /// Reset the prepared statement
  /**
  * Resets the statement back to it's initial state, ready to be re-executed.
  * Any SQL statement variables that had values bound to them retain their values.
  */
  void Reset();

  /// Determine whether the statement is read-only
  /**
  * \return TRUE if the statement is read-only, FALSE otherwise
  * \since SQLite3 version 3.7.4
  * \note For SQLite3 version before version 3.7.4 this method returns always FALSE.
  */
  bool IsReadOnly() const;

  /// Finalize the prepared statement
  /**
  */
  void Finalize();

  /// Validate associated SQLite database and statement
  /**
  * \return TRUE if both, a SQLite database and a SQLite statement, are associated, FALSE otherwise
  */
  bool IsOk() const;

  /// Determine if a prepared statement has been reset
  /**
  * \return TRUE if the prepared statement has been stepped at least once but has not run to completion and/or has not been reset, FALSE otherwise
  */
  bool IsBusy() const;

  /// Determine internal operation counters of the underlying prepared statement
  /**
  * Prepared statements maintain various counters to measure the performance of specific operations.
  * This method allows to monitor the performance characteristics of the prepared statement.
  * \param opCode operation code of the operation to be queried
  * \param resetFlag flag whether the associated counter should be reset to zero (default: false)
  * \return the counter value for the requested counter
  */
  int Status(wxSQLite3StatementStatus opCode, bool resetFlag = false) const;

private:
  /// Check for valid database connection
  void CheckDatabase() const;

  /// Check for valid statement
  void CheckStmt() const;

  /// Finalize the result set (internal)
  void Finalize(wxSQLite3DatabaseReference* db,wxSQLite3StatementReference* stmt);

  wxSQLite3DatabaseReference*  m_db;    ///< associated SQLite3 database
  wxSQLite3StatementReference* m_stmt;  ///< associated SQLite3 statement
};


/// Represents a SQLite BLOB handle
class WXDLLIMPEXP_SQLITE3 wxSQLite3Blob
{
public:
  /// Constructor
  /**
  */
  wxSQLite3Blob();

  /// Copy constructor
  /**
  */
  wxSQLite3Blob(const wxSQLite3Blob& blob);

  /// Assignment constructor
  /**
  */
  wxSQLite3Blob& operator=(const wxSQLite3Blob& blob);

  /// Constructor (internal use only)
  /**
  */
  wxSQLite3Blob(wxSQLite3DatabaseReference* m_db, wxSQLite3BlobReference* blobHandle, bool writable);

  /// Destructor
  /**
  */
  virtual ~wxSQLite3Blob();

  /// Read partial BLOB value
  /**
   * \param blobValue memory buffer receiving the partial content of the BLOB
   * \param length length of BLOB content to be read
   * \param offset offset within BLOB where the read starts
   * \return the address of the memory buffer
  */
  wxMemoryBuffer& Read(wxMemoryBuffer& blobValue, int length, int offset) const;

  /// Write partial BLOB value
  /**
   * \param blobValue memory buffer receiving the partial content of the BLOB
   * \param offset offset within BLOB where the read starts
  */
  void Write(const wxMemoryBuffer& blobValue, int offset);

  /// Check whether the BLOB handle is correctly initialized
  /**
   * \return TRUE if the BLOB handle is correctly initialized, FALSE otherwise
  */
  bool IsOk() const;

  /// Check whether the BLOB handle is read only
  /**
   * \return TRUE if the BLOB handle is readonly, FALSE otherweis
  */
  bool IsReadOnly() const;

  /// Get the size of the associated BLOB
  /**
   * \return the BLOB size
  */
  int GetSize() const;

  /// Rebind the associated BLOB to a new row
  /**
   * Please refer to the SQLite documentation for further information
   * (see function sqlite3_blob_reopen)
   * \param rowid id of the row to which the BLOB should be rebound
   * \since SQLite3 version 3.7.4
  */
  void Rebind(wxLongLong rowid);

  /// Finalize the BLOB
  /**
  */
  void Finalize();

private:
  /// Check for valid BLOB
  void CheckBlob() const;

  void Finalize(wxSQLite3DatabaseReference* db, wxSQLite3BlobReference* blob);

  wxSQLite3DatabaseReference* m_db;    ///< associated SQLite3 database handle
  wxSQLite3BlobReference*     m_blob;  ///< associated SQLite3 BLOB handle
  bool  m_writable; ///< flag whether the BLOB is writable or read only
};

/// Represents a named collection
/**
* A named collection is designed to facilitate using an array of
* integers or strings as the right-hand side of an IN operator.
* So instead of doing a prepared statement like this:
*
*     SELECT * FROM table WHERE x IN (?,?,?,...,?);
*
* And then binding individual integers to each of ? slots, an application
* can create a named collection object (named "ex1" in the following
* example), prepare a statement like this:
*
*     SELECT * FROM table WHERE x IN ex1;
*
* Then bind an array of integer or string values to the ex1 object
* to run the statement.
*
* USAGE:
*
* One or more named collection objects can be created as follows:
*
*      wxSQLite3IntegerCollection p1, p2, p3;
*      p1 = db.CreateIntegerCollection("ex1");
*      p2 = db.CreateIntegerCollection("ex2");
*      p3 = db.CreateIntegerCollection("ex3");
*
* Each call to CreateIntegerCollection generates a new virtual table
* module and a singleton of that virtual table module in the TEMP
* database.  Both the module and the virtual table instance use the
* name given by the second parameter.  The virtual tables can then be
* used in prepared statements:
*
*      SELECT * FROM t1, t2, t3
*       WHERE t1.x IN ex1
*         AND t2.y IN ex2
*         AND t3.z IN ex3;
*
* Each integer array is initially empty.  New arrays can be bound to
* an integer array as follows:
*
*     int a1[] = { 1, 2, 3, 4 };
*     int a2[] = { 5, 6, 7, 8, 9, 10, 11 };
*     wxArrayInt a3;
*     // Fill a3
*     p1.Bind(4, a1);
*     p2.Bind(7, a2);
*     p3.Bind(a3);
*
* A single named collection object can be rebound multiple times.  But do not
* attempt to change the bindings of a named collection while it is in the middle
* of a query.
*
* The array that holds the integer or string values is automatically allocated
* by the Bind method.
*
* The named collection object is automatically destroyed when its corresponding
* virtual table is dropped.  Since the virtual tables are created in the
* TEMP database, they are automatically dropped when the database connection
* closes so the application does not normally need to take any special
* action to free the named collection objects.
*/
class WXDLLIMPEXP_SQLITE3 wxSQLite3NamedCollection
{
public:
  /// Copy constructor
  wxSQLite3NamedCollection(const wxSQLite3NamedCollection& collection);

  /// Assignment constructor
  wxSQLite3NamedCollection& operator=(const wxSQLite3NamedCollection& collection);

  /// Destructor
  virtual ~wxSQLite3NamedCollection();

  /// Get the name of the collection
  /**
  * \return the name of the collection
  */
  const wxString& GetName() const { return m_name; }

  /// Gets state of the collection 
  /**
  * \return state of the collection
  */
  bool IsOk() const { return (m_data != NULL); }

  /// Gets state of the collection (same as IsOk() method)
  /**
  * \return state of the collection
  */
  operator bool() const { return IsOk(); }

protected:
  /// Constructor (internal use only)
  wxSQLite3NamedCollection(const wxString& collectionName, void* collectionData);

  /// Default constructor
  /**
    Creates completely empty collection instance that must be set by assignment, be careful
  */
  wxSQLite3NamedCollection() : m_name(wxEmptyString), m_data(NULL) {}

  wxString m_name; ///< Name of the collection
  void*    m_data; ///< Reference to the actual array of values representing the collection

  friend class wxSQLite3Database;
};

/// Represents a named integer value collection
class WXDLLIMPEXP_SQLITE3 wxSQLite3IntegerCollection : public wxSQLite3NamedCollection
{
public:
  /// Default constructor
  /**
  *  Creates completely empty collection instance that must be set by assignment, be careful
  */
  wxSQLite3IntegerCollection() {}

  /// Copy constructor
  wxSQLite3IntegerCollection(const wxSQLite3IntegerCollection& collection);

  /// Assignment constructor
  wxSQLite3IntegerCollection& operator=(const wxSQLite3IntegerCollection& collection);

  /// Destructor
  virtual ~wxSQLite3IntegerCollection();

  /// Bind a new array of integer values
  /**
  * Bind a new array of integer values to this named collection object.
  * \param integerCollection array of integer values to be bound
  * \note Binding values to a named collection after closing the corresponding
  * database results in undefined behavior, i.e. the application is likely to crash.
  */
  void Bind(const wxArrayInt& integerCollection);

  /// Bind a new array of integer values
  /**
  * Bind a new array of integer values to this named collection object.
  * \param n number of elements in the array
  * \param integerCollection array of integer values to be bound
  * \note Binding values to a named collection after closing the corresponding
  * database results in undefined behavior, i.e. the application is likely to crash.
  */
  void Bind(int n, int* integerCollection);

protected:
  /// Constructor (internal use only)
  wxSQLite3IntegerCollection(const wxString& collectionName, void* collectionData);

private:
  friend class wxSQLite3Database;
};

/// Represents a named string value collection
class WXDLLIMPEXP_SQLITE3 wxSQLite3StringCollection : public wxSQLite3NamedCollection
{
public:
  /// Default constructor
  /**
  *  Creates completely empty collection instance that must be set by assignment, be careful
  */
  wxSQLite3StringCollection() {}

  /// Copy constructor
  wxSQLite3StringCollection(const wxSQLite3StringCollection& collection);

  /// Assignment constructor
  wxSQLite3StringCollection& operator=(const wxSQLite3StringCollection& collection);

  /// Destructor
  virtual ~wxSQLite3StringCollection();

  /// Bind a new array of integer values
  /**
  * Bind a new array of integer values to this named collection object.
  * \param stringCollection array of integer values to be bound
  * \note Binding values to a named collection after closing the corresponding
  * database results in undefined behavior, i.e. the application is likely to crash.
  */
  void Bind(const wxArrayString& stringCollection);

protected:
  /// Constructor (internal use only)
  wxSQLite3StringCollection(const wxString& collectionName, void* collectionData);

private:
  friend class wxSQLite3Database;
};

/// Represents a SQLite3 database object
class WXDLLIMPEXP_SQLITE3 wxSQLite3Database
{
public:
  /// Default constructor
  /**
  * Initializes a SQLite database object.
  * The SQLite database object can only be used in the same thread in which it was created.
  */
  wxSQLite3Database();

  /// Destructor
  /**
  * Destructs a SQLite database object.
  * The database will be closed implicitly if it is still open.
  */
  virtual ~wxSQLite3Database();

  /// Open a SQLite3 database
  /**
  * Opens the SQLite database file "filename". The "filename" is UTF-8 encoded.
  * If the database could not be opened (or created) successfully, then an exception is thrown.
  * If the database file does not exist, then a new database will be created as needed.
  * \param[in] fileName Name of the database file.
  * \param[in] key Database encryption key.
  * \param[in] flags Control over the database connection (see http://www.sqlite.org/c3ref/open.html for further information).
  * Flag values are prefixed by WX to distinguish them from the original SQLite flag values.
  * \param[in] vfs Name of VFS to be used.
  * Use the VFS name prefix "multipleciphers-" to enable encryption support.
  * An empty VFS name refers to the default VFS.
  */
  void Open(const wxString& fileName, const wxString& key = wxEmptyString,
            int flags = WXSQLITE_OPEN_READWRITE | WXSQLITE_OPEN_CREATE,
            const wxString& vfs = wxEmptyString);

  /// Open a SQLite3 database using a binary key
  /**
  * Opens the SQLite database file "filename". The "filename" is UTF-8 encoded.
  * If the database could not be opened (or created) successfully, then an exception is thrown.
  * If the database file does not exist, then a new database will be created as needed.
  * \param[in] fileName Name of the database file.
  * \param[in] key Database encryption key.
  * \param[in] flags Control over the database connection (see http://www.sqlite.org/c3ref/open.html for further information).
  * Flag values are prefixed by WX to distinguish them from the original SQLite flag values.
  * \param[in] vfs Name of VFS to be used.
  * Use the VFS name prefix "multipleciphers-" to enable encryption support.
  * An empty VFS name refers to the default VFS.
  */
  void Open(const wxString& fileName, const wxMemoryBuffer& key,
            int flags = WXSQLITE_OPEN_READWRITE | WXSQLITE_OPEN_CREATE,
            const wxString& vfs = wxEmptyString);

  /// Open a SQLite3 database
  /**
  * Opens the SQLite database file "filename". The "filename" is UTF-8 encoded.
  * If the database could not be opened (or created) successfully, then an exception is thrown.
  * If the database file does not exist, then a new database will be created as needed.
  * \param[in] fileName Name of the database file.
  * \param[in] cipher Cipher to be used for database encryption.
  * \param[in] key Database encryption key.
  * \param[in] flags Control over the database connection (see http://www.sqlite.org/c3ref/open.html for further information).
  * Flag values are prefixed by WX to distinguish them from the original SQLite flag values.
  * \param[in] vfs Name of VFS to be used.
  * Use the VFS name prefix "multipleciphers-" to enable encryption support.
  * An empty VFS name refers to the default VFS.
  */
  void Open(const wxString& fileName, const wxSQLite3Cipher& cipher, const wxString& key,
            int flags = WXSQLITE_OPEN_READWRITE | WXSQLITE_OPEN_CREATE,
            const wxString& vfs = wxEmptyString);

  /// Open a SQLite3 database using a binary key
  /**
  * Opens the SQLite database file "filename". The "filename" is UTF-8 encoded.
  * If the database could not be opened (or created) successfully, then an exception is thrown.
  * If the database file does not exist, then a new database will be created as needed.
  * \param[in] fileName Name of the database file.
  * \param[in] cipher Cipher to be used for database encryption.
  * \param[in] key Database encryption key.
  * \param[in] flags Control over the database connection (see http://www.sqlite.org/c3ref/open.html for further information).
  * Flag values are prefixed by WX to distinguish them from the original SQLite flag values.
  * \param[in] vfs Name of VFS to be used.
  * Use the VFS name prefix "multipleciphers-" to enable encryption support.
  * An empty VFS name refers to the default VFS.
  */
  void Open(const wxString& fileName, const wxSQLite3Cipher& cipher, const wxMemoryBuffer& key,
            int flags = WXSQLITE_OPEN_READWRITE | WXSQLITE_OPEN_CREATE,
            const wxString& vfs = wxEmptyString);

  /// Check whether the database has been opened
  /**
  * \return TRUE if database has been opened, FALSE otherwise
  */
  bool IsOpen() const;

  /// Determine whether a database is read-only
  /**
  * \param[in] databaseName Name of the database (default "main").
  * \return TRUE if the database is read-only, FALSE otherwise
  * \since SQLite3 version 3.7.11
  * \note For SQLite3 version before version 3.7.11 this method returns always FALSE.
  */
  bool IsReadOnly(const wxString& databaseName = wxS("main")) const;

  /// Close a SQLite3 database
  /**
  * Take care that all prepared statements have been finalized!
  *
  * NOTE: Starting with version 3.6.0 SQLite has support to finalize all not-finalized
  * prepared statements. Unfortunately this feature can't be used due to a possible
  * crash if the RTree module is active.
  *
  * NOTE: Finalizing all wxSQLite3Blob instances before closing a database is required!
  *
  */
  void Close();

  /// Attach SQLite3 database
  /**
  * This method allows to attach a SQLite3 database to the current database connection.
  *
  * NOTE: If the main database is encrypted, the same encryption method and key will be used.
  *
  * \param[in] fileName Name of the database file that should be attached.
  * \param[in] schemaName Name of the schema that should be used for the attached database.
  */
  void AttachDatabase(const wxString& fileName, const wxString& schemaName);

  /// Attach SQLite3 database with encryption key
  /**
  * This method allows to attach a SQLite3 database to the current database connection
  * using the given encryption key and  the default encryption cipher.
  *
  * NOTE: The default encryption cipher will be used, and the given key will be used
  * as the pass phrase. Use an empty key to attach a plain (unencrypted) database file
  * to an encrypted main database.
  *
  * \param[in] fileName Name of the database file that should be attached.
  * \param[in] schemaName Name of the schema that should be used for the attached database.
  * \param[in] key Pass phrase for the attached database.
  */
  void AttachDatabase(const wxString& fileName, const wxString& schemaName, const wxString& key);

  /// Attach SQLite3 database with encryption cipher and key
  /**
  * This method allows to attach a SQLite3 database to the current database connection
  * using the given encryption scheme and key.
  *
  * NOTE: If the main database is encrypted, the default encryption cipher will be used.
  * The given key will be used as the pass phrase. Use an empty key to attach a plain
  * (unencrypted) database file.
  *
  * \param[in] fileName Name of the database file that should be attached.
  * \param[in] schemaName Name of the schema that should be used for the attached database.
  * \param[in] cipher Cipher to be used for database encryption.
  * \param[in] key Pass phrase for the attached database.
  */
  void AttachDatabase(const wxString& fileName, const wxString& schemaName, const wxSQLite3Cipher& cipher, const wxString& key);

  void DetachDatabase(const wxString& schemaName);

  /// Backup a SQLite3 database
  /**
  * This method is used to overwrite the contents of a database with the contents
  * of this database. This is useful either for creating backups of the database or
  * for copying an in-memory database to persistent files.
  *
  * NOTE: Exclusive access is required to the target database for the
  * duration of the operation. However the source database is only
  * read-locked while it is actually being read, it is not locked
  * continuously for the entire operation. Thus, the backup may be
  * performed on a live database without preventing other users from
  * writing to the database for an extended period of time.
  *
  * NOTE: If the target database file already exists it must be a valid
  * SQLite database, in case of an encrypted database the key used for
  * backup must be the same as the key used for creation.
  * If this does not hold true, the file should be deleted prior to
  * performing the backup.
  *
  * \param[in] targetFileName Name of the target database file.
  * \param[in] key Optional database encryption key for the target database.
  * \param[in] sourceDatabaseName Optional name of the source database (default: 'main').
  */
  void Backup(const wxString& targetFileName, const wxString& key = wxEmptyString, 
              const wxString& sourceDatabaseName = wxS("main"));
  void Backup(wxSQLite3BackupProgress* progressCallback, 
              const wxString& targetFileName, const wxString& key = wxEmptyString, 
              const wxString& sourceDatabaseName = wxS("main"));
  void Backup(const wxString& targetFileName, const wxSQLite3Cipher& cipher, const wxString& key,
              const wxString& sourceDatabaseName = wxS("main"));
  void Backup(wxSQLite3BackupProgress* progressCallback,
              const wxString& targetFileName, const wxSQLite3Cipher& cipher, const wxString& key,
              const wxString& sourceDatabaseName = wxS("main"));

  /// Backup a SQLite3 database
  /**
  * This method is used to overwrite the contents of a database with the contents
  * of this database. This is useful either for creating backups of the database or
  * for copying an in-memory database to persistent files.
  *
  * NOTE: Exclusive access is required to the target database for the
  * duration of the operation. However the source database is only
  * read-locked while it is actually being read, it is not locked
  * continuously for the entire operation. Thus, the backup may be
  * performed on a live database without preventing other users from
  * writing to the database for an extended period of time.
  *
  * NOTE: If the target database file already exists it must be a valid
  * SQLite database, in case of an encrypted database the key used for
  * backup must be the same as the key used for creation.
  * If this does not hold true, the file should be deleted prior to
  * performing the backup.
  *
  * \param[in] targetFileName Name of the target database file.
  * \param[in] key Binary database encryption key for the target database.
  * \param[in] sourceDatabaseName Optional name of the source database (default: 'main').
  */
  void Backup(const wxString& targetFileName, const wxMemoryBuffer& key, 
              const wxString& sourceDatabaseName = wxS("main"));
  void Backup(wxSQLite3BackupProgress* progressCallback,
              const wxString& targetFileName, const wxMemoryBuffer& key, 
              const wxString& sourceDatabaseName = wxS("main"));
  void Backup(const wxString& targetFileName, const wxSQLite3Cipher& cipher, const wxMemoryBuffer& key,
              const wxString& sourceDatabaseName = wxS("main"));
  void Backup(wxSQLite3BackupProgress* progressCallback,
              const wxString& targetFileName, const wxSQLite3Cipher& cipher, const wxMemoryBuffer& key,
              const wxString& sourceDatabaseName = wxS("main"));

  /// Restore a SQLite3 database
  /**
  * This method is used to restore the contents of this database with the contents
  * of another database. This is useful either for restoring a backup of the database or
  * for copying a persistent file to an in-memory database.
  *
  * NOTE: Exclusive access is required to the target database for the
  * duration of the operation. However the source database is only
  * read-locked while it is actually being read, it is not locked
  * continuously for the entire operation. Thus, the backup may be
  * performed on a live database without preventing other users from
  * writing to the database for an extended period of time.
  *
  * \param[in] sourceFileName Name of the source database file.
  * \param[in] key Optional database encryption key for the source database.
  * \param[in] targetDatabaseName Optional name of the target database (default: 'main').
  */
  void Restore(const wxString& sourceFileName, const wxString& key = wxEmptyString, 
               const wxString& targetDatabaseName = wxS("main"));
  void Restore(wxSQLite3BackupProgress* progressCallback,
               const wxString& sourceFileName, const wxString& key = wxEmptyString, 
               const wxString& targetDatabaseName = wxS("main"));
  void Restore(const wxString& sourceFileName, const wxSQLite3Cipher& cipher, 
               const wxString& key, const wxString& targetDatabaseName = wxS("main"));
  void Restore(wxSQLite3BackupProgress* progressCallback,
               const wxString& sourceFileName, const wxSQLite3Cipher& cipher, 
               const wxString& key, const wxString& targetDatabaseName = wxS("main"));

  /// Restore a SQLite3 database
  /**
  * This method is used to restore the contents of this database with the contents
  * of another database. This is useful either for restoring a backup of the database or
  * for copying a persistent file to an in-memory database.
  *
  * NOTE: Exclusive access is required to the target database for the
  * duration of the operation. However the source database is only
  * read-locked while it is actually being read, it is not locked
  * continuously for the entire operation. Thus, the backup may be
  * performed on a live database without preventing other users from
  * writing to the database for an extended period of time.
  *
  * \param[in] sourceFileName Name of the source database file.
  * \param[in] key Optional binary database encryption key for the source database.
  * \param[in] targetDatabaseName Optional name of the target database (default: 'main').
  */
  void Restore(const wxString& sourceFileName, const wxMemoryBuffer& key, 
               const wxString& targetDatabaseName = wxS("main"));
  void Restore(wxSQLite3BackupProgress* progressCallback,
               const wxString& sourceFileName, const wxMemoryBuffer& key, 
               const wxString& targetDatabaseName = wxS("main"));
  void Restore(const wxString& sourceFileName, const wxSQLite3Cipher& cipher,
               const wxMemoryBuffer& key, const wxString& targetDatabaseName = wxS("main"));
  void Restore(wxSQLite3BackupProgress* progressCallback, const wxString& sourceFileName, 
               const wxSQLite3Cipher& cipher, const wxMemoryBuffer& key,
               const wxString& targetDatabaseName = wxS("main"));

  /// Set the page count for backup or restore operations
  /**
  * Backup and restore operations perform in slices of a given number of pages.
  * This method allows to set the size of a slice. The default size is 10 pages.
  *
  * \param[in] pageCount number of pages to be copied in one slice.
  */
  void SetBackupRestorePageCount(int pageCount);

  /// Vacuum
  /**
  * Performs a VACUUM operation on the database.
  */
  void Vacuum();

  /// Begin transaction
  /**
  * In SQLite transactions can be deferred, immediate, or exclusive.
  * Deferred means that no locks are acquired on the database until the database is first accessed.
  * Thus with a deferred transaction, the BEGIN statement itself does nothing. Locks are not
  * acquired until the first read or write operation. The first read operation against a database
  * creates a SHARED lock and the first write operation creates a RESERVED lock. Because the
  * acquisition of locks is deferred until they are needed, it is possible that another thread or
  * process could create a separate transaction and write to the database after the BEGIN on the
  * current thread has executed. If the transaction is immediate, then RESERVED locks are acquired
  * on all databases as soon as the BEGIN command is executed, without waiting for the database to
  * be used. After a BEGIN IMMEDIATE, it is guaranteed that no other thread or process will be able
  * to write to the database or do a BEGIN IMMEDIATE or BEGIN EXCLUSIVE. Other processes can continue
  * to read from the database, however. An exclusive transaction causes EXCLUSIVE locks to be acquired
  * on all databases. After a BEGIN EXCLUSIVE, it is guaranteed that no other thread or process will
  * be able to read or write the database until the transaction is complete.
  *
  * \param[in] transactionType type of transaction (default: DEFERRED).
  */
  void Begin(wxSQLite3TransactionType transactionType = WXSQLITE_TRANSACTION_DEFAULT);

  /// Commit transaction
  /**
  */
  void Commit();

  /// Rollback transaction
  /**
  * Rolls back a transaction or optionally to a previously set savepoint
  *
  * \param savepointName optional name of a previously set savepoint
  */
  void Rollback(const wxString& savepointName = wxEmptyString);

  /// Get the auto commit state
  /**
  * Test to see whether or not the database connection is in autocommit mode.
  * \return TRUE if it is and FALSE if not.
  * Autocommit mode is on by default. Autocommit is disabled by a BEGIN statement
  * and reenabled by the next COMMIT or ROLLBACK.
  */
  bool GetAutoCommit() const;

  /// Query the return code of the last rollback
  /**
  * When using the class wxSQLite3Transaction there is the possibility
  * that the automatic rollback which is executed in case of an exception
  * fails. This method allows to query the return code of that operation
  * to check whether the automatic rollback succeeded or not.
  * \return the return code of the last rollback.
  * \note In case of a successful rollback the value 0 is returned.
  */
  int QueryRollbackState() const;

  /// Query the transaction state of a database
  /**
  * Describes the transaction state of the given schema in the database connection. If no schema is given,
  * then the highest transaction state of any schema on the database connection is returned.
  * The transaction state can be one of the following:
  * - WXSQLITE_TRANSACTION_NONE : No transaction is currently pending.
  * - WXSQLITE_TRANSACTION_READ : The database is currently in a read transaction. Content has been read from the database file but nothing in the database file has changed. The transaction state will advanced to WXSQLITE_TRANSACTION_WRITE if any changes occur and there are no other conflicting concurrent write transactions. The transaction state will revert to WXSQLITE_TRANSACTION_NONE following a ROLLBACK or COMMIT.
  * - WXSQLITE_TRANSACTION_WRITE : The database is currently in a write transaction. Content has been written to the database file but has not yet committed. The transaction state will change to to WXSQLITE_TRANSACTION_NONE at the next ROLLBACK or COMMIT.
  * \param[in] schemaName Name of the schema (optional)
  * \return the return code of the last rollback.
  * \note In case of a successful rollback the value 0 is returned.
  */
  wxSQLite3TransactionState QueryTransactionState(const wxString& schemaName = wxEmptyString) const;

  /// Set savepoint
  /*
  * Sets a savepoint with a given name
  *
  * \param savepointName the name of the savepoint
  */
  void Savepoint(const wxString& savepointName);

  /// Release savepoint
  /*
  * Releases a savepoint with a given name
  *
  * \param savepointName the name of the savepoint
  */
  void ReleaseSavepoint(const wxString& savepointName);

  /// Check whether a table with the given name exists
  /**
  * Checks the main database or a specific attached database for existence of a table
  * with a given name.
  *
  * \param tableName name of the table
  * \param databaseName optional name of an attached database
  * \return TRUE if the table exists, FALSE otherwise
  */
  bool TableExists(const wxString& tableName, const wxString& databaseName = wxEmptyString);

  /// Check whether a table with the given name exists in the main database or any attached database
  /**
  * \param tableName name of the table
  * \param databaseNames list of the names of those databases in which the table exists
  * \return TRUE if the table exists at least in one database, FALSE otherwise
  */
  bool TableExists(const wxString& tableName, wxArrayString& databaseNames);

  /// Get a list containing the names of all attached databases including the main database
  /**
  * \param databaseNames contains on return the list of the database names
  */
  void GetDatabaseList(wxArrayString& databaseNames);

  /// Get a list containing the names of all attached databases including the main database
  /**
  * \param databaseNames contains on return the list of the database names
  * \param databaseFiles contains on return the list of the database file names
  */
  void GetDatabaseList(wxArrayString& databaseNames, wxArrayString& databaseFiles);

  /// Return the filename for a database connection
  /**
  * \param databaseName contains on return the list of the database names
  */
  wxString GetDatabaseFilename(const wxString& databaseName);

  /// Enable or disable foreign key support
  /**
  * Starting with SQLite version 3.6.19 foreign key constraints can be enforced.
  * Foreign key constraints are disabled by default (for backwards compatibility),
  * so they must be enabled separately for each database connection.
  * \note Future releases of SQLite might change so that foreign key constraints
  * are enabled by default. No assumptions should be made about whether or not
  * foreign keys are enabled by default
  * \return TRUE if the requested action succeeded, FALSE otherwise
  */
  bool EnableForeignKeySupport(bool enable);

  /// Check whether foreign key support is enabled for this database
  /**
  * \return TRUE if foreign key support is enabled, FALSE otherwise
  */
  bool IsForeignKeySupportEnabled();

  /// Set SQLite journal mode
  /**
  * \param mode the journal mode to be set
  * \param database the attached database for which the journal mode should be set. If not given then
  *                 the journal mode of all attached databases is set.
  * \return the active journal mode
  * \note The journal mode for an in-memory database  is either MEMORY or OFF and can not be changed
  * to a different value. An attempt to change the journal mode of an in-memory database to any setting
  * other than MEMORY or OFF is ignored. Note also that the journal mode cannot be changed while a
  * transaction is active.
  * The WAL journaling mode uses a write-ahead log instead of a rollback journal to implement transactions.
  * The WAL journaling mode is persistent; after being set it stays in effect across multiple database
  * connections and after closing and reopening the database. A database in WAL journaling mode can only be
  * accessed by SQLite version 3.7.0 or later.
  */
  wxSQLite3JournalMode SetJournalMode(wxSQLite3JournalMode mode, const wxString& database = wxEmptyString);

  /// Get the active SQLite journal mode
  /**
  * \param database the attached database for which the journal mode should be queried (default: main)
  * \return active journal mode
  */
  wxSQLite3JournalMode GetJournalMode(const wxString& database = wxEmptyString);

  /// Check the syntax of an SQL statement given as a wxString
  /**
  * \param sql query string
  * \return TRUE if the syntax is correct, FALSE otherwise
  */
  bool CheckSyntax(const wxString& sql) const;

  /// Check the syntax of an SQL statement given as a statement buffer
  /**
  * \param sql query string
  * \return TRUE if the syntax is correct, FALSE otherwise
  */
  bool CheckSyntax(const wxSQLite3StatementBuffer& sql) const;

  /// Check the syntax of an SQL statement given as a utf-8 character string
  /**
  * \param sql query string
  * \return TRUE if the syntax is correct, FALSE otherwise
  */
  bool CheckSyntax(const char* sql) const;

  /// Execute a data defining or manipulating SQL statement given as a wxString
  /**
  * Execute a data defining or manipulating SQL statement given as a wxString,
  * i.e. create, alter, drop, insert, update, delete and so on
  * \param sql query string
  * \return the number of database rows that were changed (or inserted or deleted)
  */
  int ExecuteUpdate(const wxString& sql);

  /// Execute a data defining or manipulating SQL statement given as a statement buffer
  /**
  * Execute a data defining or manipulating SQL statement given as a statement buffer,
  * i.e. create, alter, drop, insert, update, delete and so on
  * \param sql query string
  * \return the number of database rows that were changed (or inserted or deleted)
  */
  int ExecuteUpdate(const wxSQLite3StatementBuffer& sql);

  /// Execute a data defining or manipulating SQL statement given as a utf-8 character string
  /**
  * Execute a data defining or manipulating SQL statement given as a utf-8 character string,
  * i.e. create, alter, drop, insert, update, delete and so on
  * \param sql query string
  * \param saveRC flag whether to save the SQLite return code in case of a rollback
  * \return the number of database rows that were changed (or inserted or deleted)
  */
  int ExecuteUpdate(const char* sql, bool saveRC = false);

  /// Execute a SQL query statement given as a wxString
  /**
  * \param sql query string
  * \return result set instance
  */
  wxSQLite3ResultSet ExecuteQuery(const wxString& sql);

  /// Execute a SQL query statement given as a statement buffer
  /**
  * \param sql query string
  * \return result set instance
  */
  wxSQLite3ResultSet ExecuteQuery(const wxSQLite3StatementBuffer& sql);

  /// Execute a SQL query statement given as a utf-8 character string
  /**
  * \param sql query string
  * \return result set instance
  */
  wxSQLite3ResultSet ExecuteQuery(const char* sql);

  /// Execute a scalar SQL query statement given as a wxString
  /**
  * Allows to easily retrieve the result of queries returning a single integer result
  * like SELECT COUNT(*) FROM table WHERE condition.
  * \param sql query string
  * \return first column of first row as an int
  */
  int ExecuteScalar(const wxString& sql);

  /// Execute a scalar SQL query statement given as a statement buffer
  /**
  * Allows to easily retrieve the result of queries returning a single integer result
  * like SELECT COUNT(*) FROM table WHERE condition.
  * \param sql query string
  * \return first column of first row as an int
  */
  int ExecuteScalar(const wxSQLite3StatementBuffer& sql);

  /// Execute a scalar SQL query statement given as a utf-8 character string
  /**
  * Allows to easily retrieve the result of queries returning a single integer result
  * like SELECT COUNT(*) FROM table WHERE condition.
  * \param sql query string
  * \return first column of first row as an int
  */
  int ExecuteScalar(const char* sql);

  /// Get the result table for a SQL query statement given as a wxString
  /**
  * Returns all resulting rows of the query for later processing.
  * \param sql query string
  * \return table instance
  */
  wxSQLite3Table GetTable(const wxString& sql);

  /// Get the result table for a SQL query statement given as a statement buffer
  /**
  * Returns all resulting rows of the query for later processing.
  * \param sql query string
  * \return table instance
  */
  wxSQLite3Table GetTable(const wxSQLite3StatementBuffer& sql);

  /// Get the result table for a SQL query statement given as a utf-8 character string
  /**
  * Returns all resulting rows of the query for later processing.
  * \param sql query string
  * \return table instance
  */
  wxSQLite3Table GetTable(const char* sql);

  /// Prepare a SQL query statement given as a wxString for parameter binding
  /**
  * \param sql query string
  * \return statement instance
  */
  wxSQLite3Statement PrepareStatement(const wxString& sql);

  /// Prepare a SQL query statement given as a statement buffer for parameter binding
  /**
  * \param sql query string
  * \return statement instance
  */
  wxSQLite3Statement PrepareStatement(const wxSQLite3StatementBuffer& sql);

  /// Prepare a SQL query statement given as a utf-8 character string for parameter binding
  /**
  * \param sql query string
  * \return statement instance
  */
  wxSQLite3Statement PrepareStatement(const char* sql);

  /// Prepare a (long-lasting) SQL query statement given as a wxString for parameter binding
  /**
  * \param sql query string
  * \return statement instance
  *
  * SQLite3 assumes that this prepared statement will be retained for a long time and probably reused many times.
  */
  wxSQLite3Statement PreparePersistentStatement(const wxString& sql);

  /// Prepare a (long-lasting) SQL query statement given as a statement buffer for parameter binding
  /**
  * \param sql query string
  * \return statement instance
  *
  * SQLite3 assumes that this prepared statement will be retained for a long time and probably reused many times.
  */
  wxSQLite3Statement PreparePersistentStatement(const wxSQLite3StatementBuffer& sql);

  /// Prepare a (long-lasting) SQL query statement given as a utf-8 character string for parameter binding
  /**
  * \param sql query string
  * \return statement instance
  *
  * SQLite3 assumes that this prepared statement will be retained for a long time and probably reused many times.
  */
  wxSQLite3Statement PreparePersistentStatement(const char* sql);

  /// Get the row id of last inserted row
  /**
  * Each entry in an SQLite table has a unique integer key.
  * (The key is the value of the INTEGER PRIMARY KEY column if there is such a column,
  * otherwise the key is generated at random. The unique key is always available as the
  * ROWID, OID, or _ROWID_ column.)
  * \return the integer key of the most recent insert in the database.
  */
  wxLongLong GetLastRowId() const;

  /// Get handle to a read only BLOB
  /**
  * \param rowId
  * \param columnName
  * \param tableName
  * \param dbName
  */
  wxSQLite3Blob GetReadOnlyBlob(wxLongLong rowId,
                                const wxString& columnName,
                                const wxString& tableName,
                                const wxString& dbName = wxEmptyString);

  /// Get handle to a writable BLOB
  /**
  * \param rowId
  * \param columnName
  * \param tableName
  * \param dbName
  */
  wxSQLite3Blob GetWritableBlob(wxLongLong rowId,
                                const wxString& columnName,
                                const wxString& tableName,
                                const wxString& dbName = wxEmptyString);

  /// Get handle to a BLOB
  /**
  * \param rowId
  * \param columnName
  * \param tableName
  * \param dbName
  * \param writable
  */
  wxSQLite3Blob GetBlob(wxLongLong rowId,
                        const wxString& columnName,
                        const wxString& tableName,
                        const wxString& dbName = wxEmptyString,
                        bool writable = true);

  /// Create a named integer value collection
  /**
  * Invoke this method to create a specific instance of an integer collection object.
  * Initially the created collection is empty. Use it's Bind method to actually bind
  * an array of values to the collection.
  * \param collectionName name of the collection
  * \return the new integer collection object.
  *
  * Each integer value collection object corresponds to a virtual table in the TEMP table
  * with a name of collectionName.
  *
  * The virtual table will be dropped implicitly when the database connection is closed.
  */
  wxSQLite3IntegerCollection CreateIntegerCollection(const wxString& collectionName);

  /// Create a named string value collection
  /**
  * Invoke this method to create a specific instance of a string collection object.
  * Initially the created collection is empty. Use it's Bind method to actually bind
  * an array of values to the collection.
  * \param collectionName name of the collection
  * \return the new string collection object.
  *
  * Each integer value collection object corresponds to a virtual table in the TEMP table
  * with a name of collectionName.
  *
  * The virtual table will be dropped implicitly when the database connection is closed.
  */
  wxSQLite3StringCollection CreateStringCollection(const wxString& collectionName);

  /// Interrupt a long running query
  /**
  * Causes any pending database operation to abort and return at its earliest opportunity.
  * This method is typically called in response to a user action such as pressing "Cancel"
  * or Ctrl-C where the user wants a long query operation to halt immediately.
  */
  void Interrupt();

  /// Determine whether or not an interrupt is currently in effect
  /**
  * \return TRUE if an interrupt is in effect, FALSE otherwise.
  */
  bool IsInterrupted();

  /// Set the busy timeout
  /**
  * This method sets a busy handler that sleeps for a while when a table is locked.
  * The handler will sleep multiple times until at least "ms" milliseconds of sleeping
  * have been done.
  * Calling this routine with an argument less than or equal to zero turns off all busy handlers.
  * \param milliSeconds timeout in milliseconds
  */
  void SetBusyTimeout(int milliSeconds);

  /// Set the setlk timeout
  /**
  * This method sets a setlk timeout in ms used by eligible locks taken on wal mode databases
  * by the specified database handle, if the VFS supports blocking locks. If the VFS does not
  * support blocking locks, this function is a no-op.
  *
  * Passing 0 to this function disables blocking locks altogether. Passing -1 to this function
  * requests that the VFS blocks for a long time - indefinitely if possible. The results of
  * passing any other negative value are undefined.
  *
  * Internally, each SQLite database handle stores two timeout values - the busy-timeout
  * (used for rollback mode databases, or if the VFS does not support blocking locks) and
  * the setlk-timeout (used for blocking locks on wal-mode databases). The method
  * SetBusyTimeout() sets both values, while this method sets only the setlk-timeout value.
  * Therefore, to configure separate busy-timeout and setlk-timeout values for a single database
  * handle, call SetBusyTimeout() followed by this method.
  *
  * Whenever the number of connections to a wal mode database falls from 1 to 0, the last
  * connection takes an exclusive lock on the database, then checkpoints and deletes the wal file.
  * While it is doing this, any new connection that tries to read from the database fails with an
  * SQLITE_BUSY error. Or, if the blockOnConnect flag is true, the new connection blocks until
  * the exclusive lock has been released. 
  * \param milliSeconds timeout in milliseconds
  * \param blockOnConnect flag whether new connections should block until exclusive lock has been released
  */
  void SetLockTimeout(int milliSeconds, bool blockOnConnect = false);

  /// Set a database configuration option
  /**
  * This method allows to configure several database settings. Most settings can be changed
  * via PRAGMA commands, too.
  * The configuration identifiers and their meaning can be found in the SQLite documenation
  * (https://sqlite.org/c3ref/c_dbconfig_defensive.html). Currently only those identifiers are
  * supported which are specified with an integer value. Except for a WX prefix in their name
  * the identifiers are identical to the original SQLite identifiers.
  * \param cfgType configuration type identifier
  * \param cfgValue intended value of the configuration option
  * \param cfgResult resulting value of the configuration option
  */
  void Configure(wxSQLite3DbConfig cfgType, int cfgValue, int& cfgResult);

  /// Create a user-defined scalar function
  /**
  * Registers a SQL scalar function with the database.
  * \param funcName name of the scalar function
  * \param argCount number of arguments the scalar function takes.
  *                 If this argument is -1 then the scalar function may take any number of arguments.
  * \param function instance of an scalar function
  * \param flags    specifies a combination of function flags (WXSQLITE_DETERMINISTIC, WXSQLITE_DIRECTONLY,
  *                 WXSQLITE_SUBTYPE, WXSQLITE_INNOCUOUS). (Default: none)
  *                 (see https://www.sqlite.org/c3ref/c_deterministic.html for detailed explanations
  * \return TRUE on successful registration, FALSE otherwise
  */
  bool CreateFunction(const wxString& funcName, int argCount, wxSQLite3ScalarFunction& function, int flags = 0);

  /// Create a user-defined aggregate function
  /**
  * Registers a SQL aggregate function with the database.
  * \param funcName name of the aggregate function
  * \param argCount number of arguments the aggregate function takes.
  *                 If this argument is -1 then the aggregate function may take any number of arguments.
  * \param function instance of an aggregate function
  * \param flags    specifies a combination of function flags (WXSQLITE_DETERMINISTIC, WXSQLITE_DIRECTONLY,
  *                 WXSQLITE_SUBTYPE, WXSQLITE_INNOCUOUS). (Default: none)
  *                 (see https://www.sqlite.org/c3ref/c_deterministic.html for detailed explanations
  * \return TRUE on successful registration, FALSE otherwise
  */
  bool CreateFunction(const wxString& funcName, int argCount, wxSQLite3AggregateFunction& function, int flags = 0);

  /// Create a user-defined aggregate window function
  /**
  * Registers a SQL aggregate window function with the database.
  * \param funcName name of the aggregate window function
  * \param argCount number of arguments the aggregate window function takes.
  *                 If this argument is -1 then the aggregate function may take any number of arguments.
  * \param function instance of an aggregate window function
  * \param flags    specifies a combination of function flags (WXSQLITE_DETERMINISTIC, WXSQLITE_DIRECTONLY,
  *                 WXSQLITE_SUBTYPE, WXSQLITE_INNOCUOUS). (Default: none)
  *                 (see https://www.sqlite.org/c3ref/c_deterministic.html for detailed explanations
  * \return TRUE on successful registration, FALSE otherwise
  */
  bool CreateFunction(const wxString& funcName, int argCount, wxSQLite3WindowFunction& function, int flags = 0);

  /// Create a user-defined authorizer function
  /**
  * Registers an authorizer object with the SQLite library. The authorizer is invoked
  * (at compile-time, not at run-time) for each attempt to access a column of a table in the database.
  * The authorizer should return SQLITE_OK if access is allowed, SQLITE_DENY if the entire SQL statement
  * should be aborted with an error and SQLITE_IGNORE if the column should be treated as a NULL value.
  * \param authorizer instance of an authorizer function
  * \return TRUE on successful registration, FALSE otherwise
  */
  bool SetAuthorizer(wxSQLite3Authorizer& authorizer);

  /// Remove a user-defined authorizer function
  /**
  * Removes a previously registered authorizer object.
  * \return TRUE on successful removal, FALSE otherwise
  */
  bool RemoveAuthorizer();

  /// Create a user-defined commit callback function
  /**
  * Registers a callback function object to be invoked whenever a new transaction is committed.
  * If the callback function returns non-zero, then the commit is converted into a rollback.
  * Registering a NULL function object disables the callback. Only a single commit hook callback
  * can be registered at a time.
  * \param commitHook address of an instance of a commit callback function
  */
  void SetCommitHook(wxSQLite3Hook* commitHook);

  /// Create a user-defined rollback callback function
  /**
  * Registers a callback function object to be invoked whenever a transaction is rolled back.
  * Registering a NULL function object disables the callback. Only a single rollback hook callback
  * can be registered at a time.
  *
  * For the purposes of this API, a transaction is said to have been rolled back if an explicit
  * "ROLLBACK" statement is executed, or an error or constraint causes an implicit rollback to occur.
  * The callback is not invoked if a transaction is automatically rolled back because the database
  * connection is closed.
  * \param rollbackHook address of an instance of a rollback callback function
  */
  void SetRollbackHook(wxSQLite3Hook* rollbackHook);

  /// Create a user-defined update callback function
  /**
  * Registers a callback function object to be invoked whenever a row is updated, inserted or deleted.
  * Registering a NULL function object disables the callback. Only a single commit hook callback
  * can be registered at a time.
  * The update hook is not invoked when internal system tables are modified (i.e. sqlite_master and sqlite_sequence).
  * \param updateHook address of an instance of an update callback function
  */
  void SetUpdateHook(wxSQLite3Hook* updateHook);

  /// Create a user-defined Write Ahead Log callback function
  /**
  * Registers a callback function object to be invoked whenever a commit has taken place in WAL journal mode.
  * Registering a NULL function object disables the callback. Only a single Write Ahead Log hook callback
  * can be registered at a time.
  * \param walHook address of an instance of a Write Ahead Log callback function
  */
  void SetWriteAheadLogHook(wxSQLite3Hook* walHook);

  /// Checkpoint database in write-ahead log mode
  /**
  * Causes an optionally named database to be checkpointed.
  * If no database name is given, then a checkpoint is run on all databases associated with this
  * database instance. If the database instance is not in write-ahead log mode then this method
  * is a harmless no-op.
  * \param database name of a database to be checkpointed
  * \param mode checkpoint mode, allowed values: WXSQLITE_CHECKPOINT_PASSIVE (default),
  *             WXSQLITE_CHECKPOINT_FULL, WXSQLITE_CHECKPOINT_RESTART
  *             (see http://www.sqlite.org/c3ref/wal_checkpoint_v2.html)
  * \param logFrameCount size of write-ahead log in frames
  * \param ckptFrameCount number of frames actually checkpointed
  * \note The frame counts are set to zero if the SQLite version is below 3.7.6.
  */
  void WriteAheadLogCheckpoint(const wxString& database, int mode = WXSQLITE_CHECKPOINT_PASSIVE,
                               int* logFrameCount = NULL, int* ckptFrameCount = NULL);

  /// Automatically checkpoint database in write-ahead log mode
  /**
  * Causes any database associated with this database instance to automatically checkpoint after
  * committing a transaction if there are N or more frames in the write-ahead log file.
  * Passing zero or a negative value as the nFrame parameter disables automatic checkpoints entirely.
  * \param frameCount frame threshold
  */
  void AutoWriteAheadLogCheckpoint(int frameCount);

  /// Create a user-defined collation sequence
  /**
  * Registers a callback function object to be invoked whenever this collation is needed
  * in comparing strings.
  * Registering a NULL function object disables the specified collation sequence.
  * \param name name of a user-defined collation sequence
  * \param collation address of an instance of a user-defined collation sequence
  */
  void SetCollation(const wxString& name, wxSQLite3Collation* collation);

  /// Return meta information about a specific column of a specific database table
  /**
  * \param dbName is either the name of the database (i.e. "main", "temp" or an attached database) or an empty string. If it is an empty string all attached databases are searched for the table.
  * \param tableName name of the database table
  * \param columnName name of the database column
  * \param dataType declared data type of the column. Pass NULL if information not needed.
  * \param collation name of the collation sequence. Pass NULL if information is not needed.
  * \param notNull output flag whether the column has a not null constraint. Pass NULL if information not needed.
  * \param primaryKey output flag whether the column is part of the primary key. Pass NULL if information not needed.
  * \param autoIncrement output flag whether the column is an auto increment column. Pass NULL if information not needed.
  *
  * This method is only available if SQLite has been compiled with SQLITE_ENABLE_COLUMN_METADATA defined.
  */
  void GetMetaData(const wxString& dbName, const wxString& tableName, const wxString& columnName,
                   wxString* dataType = NULL, wxString* collation = NULL,
                   bool* notNull = NULL, bool* primaryKey = NULL, bool* autoIncrement = NULL);

  /// Load a database extension
  /**
  * \param fileName Name of the shared library containing extension.
  * \param entryPoint Name of the entry point.
  */
  void LoadExtension(const wxString& fileName, const wxString& entryPoint = wxS("sqlite3_extension_init"));

  /// Enable or disable loading of database extensions
  /**
  * \param enable Flag whether to enable (TRUE) or disable (FALSE) loadable extensions
  */
  void EnableLoadExtension(bool enable);

  /// Change the encryption key of the database
  /**
  * If the database is currently not encrypted, this method will encrypt it.
  * If an empty key (with key length == 0) is given, the database is decrypted.
  *
  * \param newKey The new encryption key (will be converted to UTF-8)
  */
  void ReKey(const wxString& newKey);
  void ReKey(const wxSQLite3Cipher& cipher, const wxString& newKey);

  /// Change the encryption key of the database
  /**
  * If the database is currently not encrypted, this method will encrypt it.
  * If an empty key (with key length == 0) is given, the database is decrypted.
  *
  * \param newKey The new encryption key
  */
  void ReKey(const wxMemoryBuffer& newKey);
  void ReKey(const wxSQLite3Cipher& cipher, const wxMemoryBuffer& newKey);

  /// Check whether the database is encrypted
  /**
  * Check whether the database has been opened using an encryption key.
  *
  * \return TRUE if database is encrypted, FALSE otherwise
  */
  bool IsEncrypted() const { return m_isEncrypted; }

  /// Get the key salt of an encrypted database
  /**
  * If the database is encrypted and if the encryption scheme uses key salt,
  * this method allows to get the key salt as a hexadecimal encoded string.
  *
  * In case of database header corruption it is essential to know the key salt
  * of the encryption schemes ChaCha20 or SQLCipher. Without the correct key salt
  * recovering such a corrupted database is almost impossible.
  *
  * \param schemaName The name of the schema (attached database), default: "main"
  *
  * \return the key salt as a hexadecimal encoded string, empty if database not opened, or if no key salt is in use
  */
  wxString GetKeySalt(const wxString& schemaName = wxEmptyString) const;

  /// Authenticate the user on a database with user authentication
  /**
  * \param username name of the user to be authenticated
  * \param password password
  * \return TRUE if the authentication succeeded, FALSE otherwise
  */
  bool UserLogin(const wxString& username, const wxString& password);

  /// Add a user to a database with user authentication
  /**
  * \param username name of the user to be added
  * \param password password
  * \param isAdmin TRUE to give the new user admin privileges (default: FALSE)
  * \return TRUE if the authentication succeeded, FALSE otherwise
  */
  bool UserAdd(const wxString& username, const wxString& password, bool isAdmin = false);

  /// Change password and/or privileges of a user on a database with user authentication
  /**
  * \param username name of the user for which the credentials should be changed
  * \param password modified password
  * \param isAdmin modified admin privilege
  * \return TRUE if the credentials could be changed, FALSE otherwise
  */
  bool UserChange(const wxString& username, const wxString& password, bool isAdmin);

  /// Delete a user from a database with user authentication
  /**
  * \param username name of the user to be removed
  * \return TRUE if the user could be deleted, FALSE otherwise
  */
  bool UserDelete(const wxString& username);

  /// Check whether a user of a database with user authentication is privileged
  /**
  * \param username name of the user to be checked
  * \return TRUE if the user exists and is privileged, FALSE otherwise
  */
  bool UserIsPrivileged(const wxString& username);

  /// Get a list of users for a database with user authentication
  /**
  * A privileged user can list the users registered in the database. For a non-privileged user this
  * method will throw an exception.
  *
  * \param userList array of user names
  */
  void GetUserList(wxArrayString& userList);

  /// Query the value of a database limit
  /**
  * This method allows to query several database limits. Consult the SQLite
  * documentation for further explanation.
  *
  * \param id The identifier of the limit to be queried
  * \return the current value of the queried limit
  */
  int GetLimit(wxSQLite3LimitType id) const;

  /// Change a database limit to a new value
  /**
  * This method allows to change several database limits. Consult the SQLite
  * documentation for further explanation.
  *
  * \param id The identifier of the limit to be queried
  * \param newValue The new value of the limit to be set
  * \return the previous value of the specified limit
  */
  int SetLimit(wxSQLite3LimitType id, int newValue);

  /// Free memory used by a database connection
  /**
  * This method attempts to free as much heap memory as possible from database connection.
  * Consult the SQLite documentation for further explanation.
  */
  void ReleaseMemory();

  /// Get system error code
  /**
  * Get the underlying system error code after a SQLite function has failed, i.e. a file couldn't be opened
  */
  int GetSystemErrorCode() const;

  /// Convert database limit type to string
  /**
  * \param type The database limit type to be converted to string representation.
  */
  static wxString LimitTypeToString(wxSQLite3LimitType type);

  /// Initialize the SQLite library
  /**
  * Starting with SQLite version 3.6.0 there is a new method to initialize
  * the SQLite library. Currently an explicit call to this method is not
  * required, but this behaviour might change in the future of SQLite.
  * Therefore it is recommended to call this method once before accessing
  * any SQLite databases.
  */
  static void InitializeSQLite();
  static void InitializeSQLite(const wxSQLite3Logger& logger);

  /// Shutdown the SQLite library
  /**
  * Starting with SQLite version 3.6.0 there is a new method to shutdown
  * the SQLite library. Currently an explicit call to this method is not
  * required, but this behaviour might change in the future of SQLite.
  * Therefore it is recommended to call this method once when no further
  * access to any SQLite databases is required.
  */
  static void ShutdownSQLite();

  /// Set temporary directory where SQLite stores temporary files (Windows only)
  /**
  * On Windows platforms it is recommended to set the temporary directory before
  * using any SQLite databases. This method should not be called if you have
  * currently open database connections.
  *
  * \return TRUE if the temporary directory could be set successfully, FALSE otherwise
  *
  * \note This method is supported only for Windows platforms and
  * SQLite versions 3.7.14 or above. For all other platforms FALSE is returned.
  */
  static bool SetTemporaryDirectory(const wxString& tempDirectory);

  /// Get random bytes
  /**
  * SQLite contains a high-quality pseudo-random number generator.
  * This method allows to access it for application specific purposes.
  *
  * \param n The amount of random bytes to be created
  * \param random A memory buffer containing the random bytes on return
  */
  static bool Randomness(int n, wxMemoryBuffer& random);

  /// Enable or disable SQLite shared cache
  /**
  * The cache sharing mode set effects all subsequent database connections.
  * Existing database connections continue use the sharing mode that was in effect
  * at the time they were opened.
  *
  * Virtual tables cannot be used with a shared cache.
  */
  static void SetSharedCache(bool enable);

  /// Check whether SQLite shared cache is enabled
  /**
  * \return TRUE if the SQLite shared cache is enabled, FALSE otherwise
  */
  static bool IsSharedCacheEnabled() { return ms_sharedCacheEnabled; }

  /// Get the version of the wxSQLite3 wrapper
  /**
  * \return a string which contains the name and version number of the wxSQLite3 wrapper
  */
  static wxString GetWrapperVersion();

  /// Get the version of the underlying SQLite3 library
  /**
  * \return a string which contains the version number of the library
  */
  static wxString GetVersion();

  /// Get the source id of the underlying SQLite3 library
  /**
  * \return a string which contains the source id of the library
  */
  static wxString GetSourceId();

  /// Check SQLite compile option
  /**
  * Check whether the compile option with a given name has been used on building SQLite.
  * The SQLITE_ prefix may be omitted from the option name passed to this method.
  *
  * \param optionName name of the compile option to be queried
  * \return TRUE if the compile option was in use, FALSE otherwise
  *
  * \note If the option name is unknown or if the SQLite version is lower than 3.6.23
  * this method returns FALSE.
  */
  static bool CompileOptionUsed(const wxString& optionName);

  /// Get SQLite compile option name
  /**
  * Get the name of a SQLite compile option at a given index.
  * This method allows interating over the list of options that were defined
  * at compile time. If the option index is out of range, an empty string is returned.
  * The SQLITE_ prefix is omitted from any strings returned by this method.
  *
  * \param optionIndex Index of the compile option
  * \return a string containing the name of the n-th
  */
  static wxString GetCompileOptionName(int optionIndex);

  /// Convert journal mode to/from string
  /**
  * \param mode the wxSQLite3JournalMode enum value signifying the desired journal mode.
  * \return the string representation of the journal mode
  */
  static wxString ConvertJournalMode(wxSQLite3JournalMode mode);

  /// Convert journal mode to/from string
  /**
  * \param mode the string representation of the desired journal mode.
  * \return the enum representation of the journal mode
  */
  static wxSQLite3JournalMode ConvertJournalMode(const wxString& mode);

  /// Check whether wxSQLite3 has been compiled with encryption support
  /**
  * \return TRUE if encryption support is enabled, FALSE otherwise
  */
  static bool HasEncryptionSupport();

  /// Check whether wxSQLite3 has been compiled with meta data support
  /**
  * \return TRUE if meta data support is enabled, FALSE otherwise
  */
  static bool HasMetaDataSupport();

  /// Check whether wxSQLite3 has been compiled with user authentication support
  /**
  * \return TRUE if user authentication support is enabled, FALSE otherwise
  */
  static bool HasUserAuthenticationSupport();

  /// Check whether wxSQLite3 has been compiled with loadable extension support
  /**
  * \return TRUE if loadable extension support is enabled, FALSE otherwise
  */
  static bool HasLoadExtSupport();

  /// Check whether wxSQLite3 has been compiled with support for named collections
  /**
  * \return TRUE if named collection support is enabled, FALSE otherwise
  */
  static bool HasNamedCollectionSupport();

  /// Check whether wxSQLite3 has support for incremental BLOBs
  /**
  * \return TRUE if incremental BLOB support is available, FALSE otherwise
  */
  static bool HasIncrementalBlobSupport();

  /// Check whether wxSQLite3 has support for SQLite savepoints
  /**
  * \return TRUE if SQLite savepoints are supported, FALSE otherwise
  */
  static bool HasSavepointSupport();

  /// Check whether wxSQLite3 has support for SQLite backup/restore
  /**
  * \return TRUE if SQLite backup/restore is supported, FALSE otherwise
  */
  static bool HasBackupSupport();

  /// Check whether wxSQLite3 has support for SQLite write-ahead log
  /**
  * \return TRUE if SQLite write-ahead log is supported, FALSE otherwise
  */
  static bool HasWriteAheadLogSupport();

  /// Check whether wxSQLite3 has support for SQLite pointer parameters
  /**
  * \return TRUE if SQLite pointer parameters are supported, FALSE otherwise
  */
  static bool HasPointerParamsSupport();

protected:
  /// Access SQLite's internal database handle
  void* GetDatabaseHandle() const;

  /// Activate the callback for needed collations for this database
  /**
  * To avoid having to register all collation sequences before a database can be used,
  * a single callback function may be registered with the database handle to be called
  * whenever an undefined collation sequence is required.
  */
  void SetCollationNeededCallback();

  /// Request the instantiation of a user defined collation sequence
  /**
  * This method is called for every undefined collation sequence.
  * In a derived database class this method should call SetCollation registering an
  * appropriate collation class instance.
  * \param collationName name of the collation which is needed for string comparison
  */
  virtual void SetNeededCollation(const wxString& WXUNUSED(collationName)) {}

  /// Execute a comparison using a user-defined collation
  static int ExecComparisonWithCollation(void* collation, int len1, const void* txt1, int len2, const void* txt2);

  /// Execute callback for needed collation sequences
  static void ExecCollationNeeded(void* db, void* internalDb, int eTextRep, const char* name);

private:
  /// Private copy constructor
  wxSQLite3Database(const wxSQLite3Database& db);

  /// Private assignment constructor
  wxSQLite3Database& operator=(const wxSQLite3Database& db);

  /// Prepare a SQL statement (internal use only)
  void* Prepare(const char* sql);

  /// Prepare a (long-lasting) SQL statement (internal use only)
  void* PreparePersistent(const char* sql);

  /// Check for valid database connection
  void CheckDatabase() const;

  /// Close associated database
  void Close(wxSQLite3DatabaseReference* db);

  wxSQLite3DatabaseReference* m_db;  ///< associated SQLite3 database
  bool  m_isOpen;          ///< Flag whether the database is opened or not
  int   m_busyTimeoutMs;   ///< Busy timeout in milli seconds
  bool  m_isEncrypted;     ///< Flag whether the database is encrypted or not
  int   m_lastRollbackRC;  ///< The return code of the last executed rollback operation
  int   m_backupPageCount; ///< Number of pages per slice for backup and restore operations

  static bool  ms_sharedCacheEnabled;        ///< Flag whether SQLite shared cache is enabled
  static bool  ms_hasEncryptionSupport;      ///< Flag whether wxSQLite3 has been compiled with encryption support
  static bool  ms_hasMetaDataSupport;        ///< Flag whether wxSQLite3 has been compiled with meta data support
  static bool  ms_hasUserAuthentication;     ///< Flag whether wxSQLite3 has been compiled with user authentication support
  static bool  ms_hasLoadExtSupport;         ///< Flag whether wxSQLite3 has been compiled with loadable extension support
  static bool  ms_hasNamedCollectionSupport; ///< Flag whether wxSQLite3 has been compiled with support for named collections
  static bool  ms_hasIncrementalBlobSupport; ///< Flag whether wxSQLite3 has support for incremental BLOBs
  static bool  ms_hasSavepointSupport;       ///< Flag whether wxSQLite3 has support for SQLite savepoints
  static bool  ms_hasBackupSupport;          ///< Flag whether wxSQLite3 has support for SQLite backup/restore
  static bool  ms_hasWriteAheadLogSupport;   ///< Flag whether wxSQLite3 has support for SQLite write-ahead log
  static bool  ms_hasPointerParamsSupport;   ///< Flag whether wxSQLite3 has support for SQLite pointer parameters

  friend class wxSQLite3Cipher;
};

/// RAII class for managing transactions
/***
* This object allows easy managment of transaction. It con only be
* created on the stack. This guarantees that the destructor is called
* at the moment it goes out of scope. Usage:
* \code
* void doDB(wxSQLite3Database *db)
* {
*   wxSQLite3Transaction t(db);
*   doDatabaseOperations();
*   t.Commit();
* }
* \endcode
* In case doDatabseOperations() fails by throwing an exception,
* the transaction is automatically rolled back. If it succedes,
* Commit() commits the changes to the db and the destructor
* of Transaction does nothing.
*/
class WXDLLIMPEXP_SQLITE3 wxSQLite3Transaction
{
public:
  /// Constructor. Start the Transaction.
  /**
    * The constructor starts the transaction.
    * \param db Pointer to the open Database. The pointer to the database
    * is NOT freed on destruction!
    * \param transactionType Type of the transaction to be opened.
    */
  explicit wxSQLite3Transaction(wxSQLite3Database* db, wxSQLite3TransactionType transactionType = WXSQLITE_TRANSACTION_DEFAULT);

  /// Destructor.
  /**
    * The destructor does nothing if the changes were already commited (see commit()).
    * In case the changes were not committed, a call to the destructor rolls back the
    * transaction.
    */
  ~wxSQLite3Transaction();

  /// Commits the transaction
  /**
    * Commits the transaction if active. If not, it does nothing.
    * After the commit, the transaction is not active.
    */
  void Commit();

  /// Rolls back the transaction
  /**
    * Rolls back the transaction if active. If not, it does nothing.
    * After the rollback, the transaction is not active.
    */
  void Rollback();

  /// Determines whether the transaction is open or not
  /**
    * \return TRUE if the constructor successfully opend the transaction, false otherwise.
    * After committing the transaction, active returns false.
    */
  inline bool IsActive() const
  {
    return m_database != NULL;
  }

private:
  /// New operator (May only be created on the stack)
  static void *operator new(size_t size);

  /// Delete operator (May not be deleted (for symmetry))
  static void operator delete(void *ptr);

  /// Copy constructor (Must not be copied)
  wxSQLite3Transaction(const wxSQLite3Transaction&);

  /// Assignment operator (Must not be assigned)
  wxSQLite3Transaction& operator=(const wxSQLite3Transaction&);

  wxSQLite3Database* m_database; ///< Pointer to the associated database (no ownership)
};


#if wxUSE_REGEX

/// User defined function for REGEXP operator
/**
*/
class WXDLLIMPEXP_SQLITE3 wxSQLite3RegExpOperator : public wxSQLite3ScalarFunction
{
public:
  /// Constructor
  wxSQLite3RegExpOperator(int flags = wxRE_DEFAULT);

  /// Virtual destructor
  virtual ~wxSQLite3RegExpOperator();

  /// Execute the scalar function
  /**
  * This method is invoked for each appearance of the scalar function in the SQL query.
  * \param ctx function context which can be used to access arguments and result value
  */
  virtual void Execute(wxSQLite3FunctionContext& ctx);

private:
  wxString m_exprStr; ///< Last regular expression string
  wxRegEx  m_regEx;   ///< Regular expression cache (currently only 1 instance)
  int      m_flags;   ///< Flags for regular expression
};

#endif // wxUSE_REGEX

#endif

