/*
** Name:        wxsqlite3opt.h
** Purpose:     wxSQLite3 optional feature selection
** Author:      Ulrich Telle
** Created:     2007-02-01
** Copyright:   (c) 2007-2020 Ulrich Telle
** License:     LGPL-3.0+ WITH WxWindows-exception-3.1
*/

/// \file wxsqlite3opt.h Compile time switches for the wxSQLite3 class

#ifndef WX_SQLITE3_OPT_H_
#define WX_SQLITE3_OPT_H_

// Conditional compilation
// -----------------------

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

#endif // WX_SQLITE3_OPT_H_
