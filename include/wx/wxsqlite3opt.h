/*
** Name:        wxsqlite3opt.h
** Purpose:     wxSQLite3 optional feature selection
** Author:      Ulrich Telle
** Created:     2007-02-01
** Copyright:   (c) 2007-2018 Ulrich Telle
** License:     LGPL-3.0+ WITH WxWindows-exception-3.1
*/

/// \file wxsqlite3opt.h Compile time switches for the wxSQLite3 class

#ifndef _WX_SQLITE3_OPT_H_
#define _WX_SQLITE3_OPT_H_

// Conditional compilation
// -----------------------

//! If this define is set to 1, then the SQLite library will be loaded dynamically
//! otherwise a link library is required to build wxSQLite3.
#ifndef wxUSE_DYNAMIC_SQLITE3_LOAD
#define wxUSE_DYNAMIC_SQLITE3_LOAD   0
#endif

//! To enable SQLite's meta data methods define WXSQLITE3_HAVE_METADATA as 1 here.
//! Attention: SQLite needs to be compiled with SQLITE_ENABLE_COLUMN_METADATA for this to work
#ifndef WXSQLITE3_HAVE_METADATA
#define WXSQLITE3_HAVE_METADATA 1
#endif

//! To enable SQLite's user authentication define WXSQLITE3_USER_AUTHENTICATION as 1 here.
//! Attention: SQLite needs to be compiled with SQLITE_USER_AUTHENTICATION for this to work
#ifndef WXSQLITE3_USER_AUTHENTICATION
#define WXSQLITE3_USER_AUTHENTICATION 1
#endif

//! To enable SQLite's database encryption support define WXSQLITE3_HAVE_CODEC as 1 here.
//! Attention: SQLite needs to be compiled with SQLITE_HAS_CODEC for this to work
#ifndef WXSQLITE3_HAVE_CODEC
#define WXSQLITE3_HAVE_CODEC 1
#endif

//! To enable SQLite's loadable extension feature define WXSQLITE3_HAVE_LOAD_EXTENSION as 1 here.
//! Attention: SQLite needs to be compiled without SQLITE_OMIT_LOAD_EXTENSION for this to work
#ifndef WXSQLITE3_HAVE_LOAD_EXTENSION
#define WXSQLITE3_HAVE_LOAD_EXTENSION 0
#endif

//! To disable support for named collections define WXSQLITE3_USE_NAMED_COLLECTIONS as 0 here.
//! Attention: if WXSQLITE3_USE_NAMED_COLLECTIONS is defined as 1 (default) SQLite needs to be
//! compiled without SQLITE_OMIT_VIRTUALTABLE for this to work
#ifndef WXSQLITE3_USE_NAMED_COLLECTIONS
#define WXSQLITE3_USE_NAMED_COLLECTIONS 1
#endif

#endif // _WX_SQLITE3_OPT_H_
