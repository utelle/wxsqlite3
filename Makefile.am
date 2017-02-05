# Process this file with automake to create Makefile.in for wxsqlite3 library
#
# Copyright (C) 2017 Ulrich Telle <ulrich@telle-online.de>, Vadim Zeitlin <vadim@wxwidgets.org>
#
# This file is covered by the same licence as the entire wxSQLite3 package.

ACLOCAL_AMFLAGS = -I admin/m4

# Flags used for compiling all the targets and linking all the executables
# (libraries use LIBADD which is set for lib@WXSQLITE3_LIBNAME@.la only).
AM_CXXFLAGS = -I$(top_srcdir)/include -I$(top_srcdir)/sqlite3/secure/src $(WX_CXXFLAGS)
AM_CFLAGS   = -I$(top_srcdir)/include -I$(top_srcdir)/sqlite3/secure/src $(WX_CXXFLAGS)

AM_CXXFLAGS += -DwxUSE_DYNAMIC_SQLITE3_LOAD=0 -DWXSQLITE3_HAVE_METADATA=1 -DWXSQLITE3_USER_AUTHENTICATION=1 -DWXSQLITE3_HAVE_CODEC=1 -DWXSQLITE3_HAVE_LOAD_EXTENSION=0
AM_CFLAGS += -DTHREADSAFE=1 -DSQLITE_SOUNDEX -DSQLITE_ENABLE_COLUMN_METADATA -DSQLITE_HAS_CODEC -DSQLITE_SECURE_DELETE -DSQLITE_ENABLE_FTS3 -DSQLITE_ENABLE_FTS3_PARENTHESIS -DSQLITE_ENABLE_FTS4 -DSQLITE_ENABLE_FTS5 -DSQLITE_ENABLE_JSON1 -DSQLITE_ENABLE_RTREE -DSQLITE_CORE -DSQLITE_ENABLE_EXTFUNC -DSQLITE_ENABLE_CSV -DSQLITE_USE_URI -DSQLITE_USER_AUTHENTICATION 

LDADD = lib@WXSQLITE3_LIBNAME@.la $(WX_LIBS)

# Define the directory where the library headers are installed.
includewxdir = $(includedir)/wx

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = wxsqlite3.pc

# The main library. Notice that it uses dynamic, i.e. determined when running
# configure, name because it depends on the version of wxWidgets used. This is
# rather unusual, but Automake doesn't seem to mind.
lib_LTLIBRARIES = lib@WXSQLITE3_LIBNAME@.la

lib@WXSQLITE3_LIBNAME@_la_SOURCES = \
    sqlite3/secure/src/sqlite3secure.c \
    src/wxsqlite3.cpp

includewx_HEADERS = \
    include/wx/wxsqlite3.h \
    include/wx/wxsqlite3_version.h \
    include/wx/wxsqlite3def.h

noinst_HEADERS = \
    include/wx/wxsqlite3dyn.h \
    include/wx/wxsqlite3opt.h \
    sqlite3/secure/src/sqlite3.c \
    sqlite3/secure/src/sha2.c \
    sqlite3/secure/src/userauth.c \
    sqlite3/secure/src/rijndael.c \
    sqlite3/secure/src/codec.c \
    sqlite3/secure/src/codecext.c \
    sqlite3/secure/src/extensionfunctions.c \
    sqlite3/secure/src/csv.c \
    sqlite3/secure/src/codec.h \
    sqlite3/secure/src/rijndael.h \
    sqlite3/secure/src/sha2.h \
    sqlite3/secure/src/sqlite3.h \
    sqlite3/secure/src/sqlite3ext.h \
    sqlite3/secure/src/sqlite3userauth.h

lib@WXSQLITE3_LIBNAME@_la_LDFLAGS = -no-undefined $(AM_LDFLAGS)
lib@WXSQLITE3_LIBNAME@_la_LIBADD = $(WX_LIBS)


# Samples (don't need to be installed).
noinst_PROGRAMS = samples/minimal

if BUILD_TREEVIEW_SAMPLE
noinst_PROGRAMS += samples/treeview/treeview
endif

samples_minimal_SOURCES = \
    samples/minimal.cpp

samples_minimal_LDFLAGS = -no-install

samples_treeview_treeview_SOURCES = \
    samples/treeview/foldertree.cpp \
    samples/treeview/projectlist.cpp \
    samples/treeview/treeviewapp.cpp \
    samples/treeview/treeviewsample.cpp \
    samples/treeview/foldertree.h \
    samples/treeview/projectlist.h \
    samples/treeview/treeviewapp.h \
    samples/treeview/treeviewsample.h

samples_treeview_treeview_LDADD = $(WX_LIBS_TREEVIEW_SAMPLE) $(LDADD)

samples_treeview_treeview_LDFLAGS = -no-install
