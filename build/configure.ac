# ======================================================================================
# Author: Francesco Montorsi
# RCS-ID: $Id: configure.ac,v 1.12 2007/11/10 09:06:31 utelle Exp $
#
# A basic "configure.ac" for a wxCode component.
# See 
#    http://www.gnu.org/software/autoconf/manual/autoconf-2.57/html_mono/autoconf.html
# for more info about autoconf and the autoconf macros.
# ======================================================================================

# Init this configure script with basic info about the component
# (DON'T PUT ANYTHING BEFORE AC_INIT, JUST COMMENTS)
AC_INIT([wxSqlite3], [3.0.4], [utelle@users.sourceforge.net])
AC_CONFIG_AUX_DIR(build)

# ENABLES/DISABLES THE DEBUG MODE FOR THIS CONFIGURE SCRIPT
#WX_DEBUG_CONFIGURE=1

# you need the wxCode/build/bakefiles in your local repository to generate a configure
# script from this configure.ac file since wxcode.m4 is required....
m4_include(../../../build/autoconf/wxcode.m4)
WXCODE_INIT

## CONFIGURE OPTIONS
##
## Before starting checks, declare the options of this configure script
## Here you should use the AC_ARG_ENABLE and AC_ARG_WITH macros
## or the wxCode-specific AM_WXCODE_ARG_ENABLE & AM_WXCODE_ARG_WITH macros,
## to add to this configure script the --enable-XXX and/or --with-XXX
## options required. If you did not use any <option> tag in your
## component's bakefile, then you can leave this section as is
#####################################################################

WXCODE_OPTIONS([debug,unicode,shared,toolkit,wxshared,wxversion]) 

AC_ARG_WITH([sqlite3_prefix],
                AC_HELP_STRING([--with-sqlite3-prefix],
                        [Prefix where sqlite3 is installed (optional; default is /usr/local)]),, 
                [with_sqlite3_prefix=/usr/local])
SQLITE3_DIR=$with_sqlite3_prefix
AC_SUBST(SQLITE3_DIR)


## CONFIGURE CHECKS
##
## Here you should use the AC_CHECK_LIB, AC_COMPILE_IFELSE, 
## AC_LINK_IFELSE, etc macros to check that the libraries required
## by your component exist on the host machine and match your
## required options (version, build settings, etc)
#####################################################################

# argument 1: here put the minimum required version of wx
# argument 2: here you must put a comma-separed list of all wx required libraries 
#             except for base,core (e.g. "xml,net,adv"); leave empty if you use only core & base
WXCODE_CHECKS([2.8.0], [core,base])

WXCODE_ARG_ENABLE([dynamic_load], [Enables the SQLite dynamic load support], [no])
AC_MSG_CHECKING([for the --enable-dynamic-load option])
if test "$enable_dynamic_load" = "yes"; then
    USE_DYNAMIC_SQLITE3_LOAD=1
    AC_MSG_RESULT([yes])
else
    USE_DYNAMIC_SQLITE3_LOAD=0
    AC_MSG_RESULT([no])
fi

WXCODE_ARG_ENABLE([metadata], [Enables the wxSQLite3 meta data support (SQLite needs to be compiled with meta data support)], [no])
AC_MSG_CHECKING([for the --enable-metadata option])
if test "$enable_metadata" = "yes"; then
    HAVE_METADATA=1
    AC_MSG_RESULT([yes])
else
    HAVE_METADATA=0
    AC_MSG_RESULT([no])
fi

WXCODE_ARG_ENABLE([codec], [Enables the wxSQLite3 CODEC support (SQLite needs to be compiled with CODEC support)], [no])
AC_MSG_CHECKING([for the --enable-codec option])
if test "$enable_codec" = "yes"; then
    HAVE_CODEC=1
    AC_MSG_RESULT([yes])
else
    HAVE_CODEC=0
    AC_MSG_RESULT([no])
fi

WXCODE_ARG_ENABLE([load_extension], [Enables the wxSQLite3 loadable extension support (SQLite needs to be compiled with loadable extension support)], [no])
AC_MSG_CHECKING([for the --enable-load-extension option])
if test "$enable_load_extension" = "yes"; then
    HAVE_LOAD_EXTENSION=1
    AC_MSG_RESULT([yes])
else
    HAVE_LOAD_EXTENSION=0
    AC_MSG_RESULT([no])
fi

# end in a nice way the configure script
WXCODE_END_PART1
if test "$USE_DYNAMIC_SQLITE3_LOAD" = "1"; then
echo "  - dynamic load enabled"
else
echo "  - dynamic load disabled"
fi
if test "$HAVE_METADATA" = "1"; then
echo "  - meta data support enabled"
else
echo "  - meta data support disabled"
fi
if test "$HAVE_CODEC" = "1"; then
echo "  - CODEC support enabled"
else
echo "  - CODEC support disabled"
fi
if test "$HAVE_LOAD_EXTENSION" = "1"; then
echo "  - loadable extension support enabled"
else
echo "  - loadable extension support disabled"
fi
WXCODE_END_PART2


