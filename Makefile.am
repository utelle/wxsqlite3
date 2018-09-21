# Process this file with automake to create Makefile.in for wxsqlite3 library
#
# Copyright (C) 2017-2018 Ulrich Telle <ulrich@telle-online.de>, Vadim Zeitlin <vadim@wxwidgets.org>
#
# This file is covered by the same licence as the entire wxSQLite3 package.

ACLOCAL_AMFLAGS = -I admin/m4

# Flags used for compiling all the targets and linking all the executables
# (libraries use LIBADD which is set for lib@WXSQLITE3_LIBNAME@.la only).
AM_CXXFLAGS = -I$(top_srcdir)/include -I$(top_srcdir)/sqlite3secure/src $(WX_CXXFLAGS)
AM_CFLAGS   = -I$(top_srcdir)/include -I$(top_srcdir)/sqlite3secure/src $(WX_CXXFLAGS)

AM_CXXFLAGS += -DwxUSE_DYNAMIC_SQLITE3_LOAD=0 -DWXSQLITE3_HAVE_METADATA=1 -DWXSQLITE3_USER_AUTHENTICATION=1 -DWXSQLITE3_HAVE_CODEC=1 -DWXSQLITE3_HAVE_LOAD_EXTENSION=0
AM_CFLAGS += -std=c99 -DTHREADSAFE=1 -DSQLITE_MAX_ATTACHED=10 -DSQLITE_SOUNDEX -DSQLITE_ENABLE_COLUMN_METADATA -DSQLITE_HAS_CODEC=1 -DSQLITE_SECURE_DELETE -DSQLITE_ENABLE_FTS3 -DSQLITE_ENABLE_FTS3_PARENTHESIS -DSQLITE_ENABLE_FTS4 -DSQLITE_ENABLE_FTS5 -DSQLITE_ENABLE_JSON1 -DSQLITE_ENABLE_RTREE -DSQLITE_ENABLE_GEOPOLY -DSQLITE_CORE -DSQLITE_ENABLE_EXTFUNC -DSQLITE_ENABLE_CSV -DSQLITE_ENABLE_SHA3 -DSQLITE_ENABLE_CARRAY -DSQLITE_ENABLE_FILEIO -DSQLITE_ENABLE_SERIES -DSQLITE_TEMP_STORE=2 -DSQLITE_USE_URI -DSQLITE_USER_AUTHENTICATION 

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
    sqlite3secure/src/sqlite3secure.c \
    src/wxsqlite3.cpp

includewx_HEADERS = \
    include/wx/wxsqlite3.h \
    include/wx/wxsqlite3_version.h \
    include/wx/wxsqlite3def.h

noinst_HEADERS = \
    include/wx/wxsqlite3dyn.h \
    include/wx/wxsqlite3opt.h \
    sqlite3secure/src/sqlite3.c \
    sqlite3secure/src/carray.c \
    sqlite3secure/src/chacha20poly1305.c \
    sqlite3secure/src/codec.c \
    sqlite3secure/src/codec.h \
    sqlite3secure/src/codecext.c \
    sqlite3secure/src/csv.c \
    sqlite3secure/src/extensionfunctions.c \
    sqlite3secure/src/fastpbkdf2.c \
    sqlite3secure/src/fastpbkdf2.h \
    sqlite3secure/src/fileio.c \
    sqlite3secure/src/md5.c \
    sqlite3secure/src/regexp.c \
    sqlite3secure/src/rekeyvacuum.c \
    sqlite3secure/src/rijndael.c \
    sqlite3secure/src/rijndael.h \
    sqlite3secure/src/series.c \
    sqlite3secure/src/sha1.c \
    sqlite3secure/src/sha1.h \
    sqlite3secure/src/sha2.c \
    sqlite3secure/src/sha2.h \
    sqlite3secure/src/shathree.c \
    sqlite3secure/src/shell.c \
    sqlite3secure/src/sqlite3.c \
    sqlite3secure/src/sqlite3.h \
    sqlite3secure/src/sqlite3ext.h \
    sqlite3secure/src/sqlite3secure.c \
    sqlite3secure/src/sqlite3userauth.h \
    sqlite3secure/src/test_windirent.c \
    sqlite3secure/src/test_windirent.h \
    sqlite3secure/src/userauth.c

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
