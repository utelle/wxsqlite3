# Process this file with automake to create Makefile.in for wxsqlite3 library
#
# Copyright (C) 2017-2020 Ulrich Telle <ulrich@telle-online.de>, Vadim Zeitlin <vadim@wxwidgets.org>
#
# This file is covered by the same licence as the entire wxSQLite3 package.

if HOST_X86
X86_FLAGS = -msse4.2 -maes 
else
X86_FLAGS =
endif
 
if HOST_ARM
ARM_FLAGS = -march=native 
else
ARM_FLAGS =
endif

ACLOCAL_AMFLAGS = -I admin/m4

# Flags used for compiling all the targets and linking all the executables
# (libraries use LIBADD which is set for lib@WXSQLITE3_LIBNAME@.la only).
AM_CXXFLAGS = -I$(top_srcdir)/include -I$(top_srcdir)/src $(WX_CXXFLAGS)
AM_CFLAGS   = -I$(top_srcdir)/include -I$(top_srcdir)/src $(WX_CXXFLAGS)

AM_CXXFLAGS += -DSQLITE_ENABLE_COLUMN_METADATA=1 -DSQLITE_USER_AUTHENTICATION=1
AM_CFLAGS += -std=c99 -DSQLITE_THREADSAFE=1 -DSQLITE_DQS=0 -DSQLITE_MAX_ATTACHED=10 -DSQLITE_ENABLE_EXPLAIN_COMMENTS=1 -DSQLITE_SOUNDEX=1 -DSQLITE_ENABLE_COLUMN_METADATA=1 -DSQLITE_SECURE_DELETE=1 -DSQLITE_ENABLE_DESERIALIZE=1 -DSQLITE_ENABLE_FTS3=1 -DSQLITE_ENABLE_FTS3_PARENTHESIS=1 -DSQLITE_ENABLE_FTS4=1 -DSQLITE_ENABLE_FTS5=1 -DSQLITE_ENABLE_JSON1=1 -DSQLITE_ENABLE_RTREE=1 -DSQLITE_ENABLE_GEOPOLY=1 -DSQLITE_CORE=1 -DSQLITE_ENABLE_EXTFUNC=1 -DSQLITE_ENABLE_CSV=1 -DSQLITE_ENABLE_VSV=1 -DSQLITE_ENABLE_SHA3=1 -DSQLITE_ENABLE_CARRAY=1 -DSQLITE_ENABLE_FILEIO=1 -DSQLITE_ENABLE_SERIES=1 -DSQLITE_ENABLE_UUID=1 -DSQLITE_ENABLE_REGEXP=1 -DSQLITE_TEMP_STORE=2 -DSQLITE_USE_URI=1 -DSQLITE_USER_AUTHENTICATION=1 $(X86_FLAGS) $(ARM_FLAGS)

AM_LDFLAGS = -pthread -ldl -lm

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
    src/sqlite3mc_amalgamation.c \
    src/wxsqlite3.cpp

includewx_HEADERS = \
    include/wx/wxsqlite3.h \
    include/wx/wxsqlite3_version.h \
    include/wx/wxsqlite3def.h

noinst_HEADERS = \
    include/wx/wxsqlite3opt.h \
    src/sqlite3mc_amalgamation.h 

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
