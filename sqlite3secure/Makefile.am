# Process this file with automake to create Makefile.in for sqlite3secure library
#
# Copyright (C) 2018 Ulrich Telle <ulrich@telle-online.de>
#
# This file is covered by the same licence as the entire wxSQLite3 package.

ACLOCAL_AMFLAGS = -I ../admin/m4

# Flags used for compiling all the targets and linking all the executables
# (libraries use LIBADD which is set for lib@WXSQLITE3_LIBNAME@.la only).
AM_CXXFLAGS = -I$(top_srcdir)/src
AM_CFLAGS   = -I$(top_srcdir)/src

AM_CFLAGS += -std=c99 -DTHREADSAFE=1 -DSQLITE_MAX_ATTACHED=10 -DSQLITE_SOUNDEX -DSQLITE_ENABLE_COLUMN_METADATA -DSQLITE_HAS_CODEC -DSQLITE_SECURE_DELETE -DSQLITE_ENABLE_FTS3 -DSQLITE_ENABLE_FTS3_PARENTHESIS -DSQLITE_ENABLE_FTS4 -DSQLITE_ENABLE_FTS5 -DSQLITE_ENABLE_JSON1 -DSQLITE_ENABLE_RTREE -DSQLITE_ENABLE_GEOPOLY -DSQLITE_CORE -DSQLITE_ENABLE_EXTFUNC -DSQLITE_ENABLE_CSV -DSQLITE_ENABLE_SHA3 -DSQLITE_ENABLE_CARRAY -DSQLITE_ENABLE_FILEIO -DSQLITE_ENABLE_SERIES -DSQLITE_TEMP_STORE=2 -DSQLITE_USE_URI -DSQLITE_USER_AUTHENTICATION 

AM_LDFLAGS = -pthread -ldl -lm

LDADD = lib@SQLITE3SECURE_LIBNAME@.la

if USE_MSW
# Use old style suffix rule instead of the pattern one as automake only
# recognizes this kind of rules.
#
# Also notice that we use .res_o_o extension for the object files obtained by
# compiling resource files, instead of just the usual .o, because we'd have
# conflicts between object file names for foo.cpp and foo.rc otherwise. Due to
# this we have to add the .res_o files manually to LDADD later, but such is life.
.rc.res_o:
	$(AM_V_GEN) $(WINDRES) -I $(top_srcdir) $(WX_CPPFLAGS) -O coff $< $@
endif

# Define the directory where the library headers are installed.
includedir = $(includedir)

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = sqlite3secure.pc

# The main library. Notice that it uses dynamic, i.e. determined when running
# configure, name because it depends on the version of wxWidgets used. This is
# rather unusual, but Automake doesn't seem to mind.
lib_LTLIBRARIES = lib@SQLITE3SECURE_LIBNAME@.la

lib@SQLITE3SECURE_LIBNAME@_la_SOURCES = \
    src/sqlite3secure.c

#include_HEADERS = \
#    src/sqlite3.h \
#    src/sqlite3secure.h

noinst_HEADERS = \
    src/sqlite3.c \
    src/sha2.c \
    src/userauth.c \
    src/rijndael.c \
    src/codec.c \
    src/codecext.c \
    src/extensionfunctions.c \
    src/csv.c \
    src/codec.h \
    src/rijndael.h \
    src/sha2.h \
    src/sqlite3.h \
    src/sqlite3ext.h \
    src/sqlite3userauth.h

lib@SQLITE3SECURE_LIBNAME@_la_LDFLAGS = -no-undefined $(AM_LDFLAGS)
lib@SQLITE3SECURE_LIBNAME@_la_LIBADD = -ldl -lm


# Samples (don't need to be installed).
noinst_PROGRAMS = sqlite3shell

sqlite3shell_SOURCES = \
    src/sqlite3secure.c \
    src/shell.c

sqlite3shell_CFLAGS = -I$(top_srcdir)/src -std=c99 -DTHREADSAFE=1 -DSQLITE_MAX_ATTACHED=10 -DSQLITE_SOUNDEX -DSQLITE_ENABLE_COLUMN_METADATA -DSQLITE_HAS_CODEC -DSQLITE_SECURE_DELETE -DSQLITE_ENABLE_FTS3 -DSQLITE_ENABLE_FTS3_PARENTHESIS -DSQLITE_ENABLE_FTS4 -DSQLITE_ENABLE_FTS5 -DSQLITE_ENABLE_JSON1 -DSQLITE_ENABLE_RTREE -DSQLITE_ENABLE_GEOPOLY -DSQLITE_CORE -DSQLITE_ENABLE_EXTFUNC -DSQLITE_ENABLE_CSV -DSQLITE_ENABLE_CARRAY -DSQLITE_ENABLE_SERIES -DSQLITE_TEMP_STORE=2 -DSQLITE_USE_URI -DSQLITE_USER_AUTHENTICATION 

sqlite3shell_LDADD = -ldl -lm
sqlite3shell_LDFLAGS = -pthread

if USE_MSW
sqlite3shell_SOURCES += src/sqlite3shell.rc
sqlite3shell_LDADD += src/sqlite3shell.res_o
CLEANFILES = src/sqlite3shell.res_o
else
# libtool complains about unknown "-no-install" option when targetting MSW, so
# use it only in the "else" branch.
sqlite3shell_LDFLAGS += -no-install
endif

