dnl Process this script with autoconf to create configure for wxsqlite3 library
dnl
dnl Copyright (C) 2017 Ulrich Telle <ulrich@telle-online.de>, Vadim Zeitlin <vadim@wxwidgets.org>
dnl
dnl This file is covered by the same licence as the entire wxSQLite3 package.

AC_INIT([wxsqlite3], [3.5.1], [ulrich@telle-online.de])

dnl This is the version tested with, might work with earlier ones.
AC_PREREQ([2.69])

AC_CONFIG_SRCDIR([include/wx/wxsqlite3.h])
AC_CONFIG_AUX_DIR([admin/build-aux])
AC_CONFIG_MACRO_DIR([admin/m4])

AM_INIT_AUTOMAKE([1.11 foreign subdir-objects])
AM_MAINTAINER_MODE([enable])
AM_SILENT_RULES([yes])

LT_INIT()
AC_PROG_CXX
AC_LANG(C++)

AC_ARG_VAR(WX_CONFIG, [Path to wx-config script (default: search in PATH).])
WX_CONFIG_OPTIONS
WX_CONFIG_CHECK([2.8.0],
    [],
    [AC_MSG_FAILURE([wxWidgets required but not detected.])],
    [base,core]
)

AC_ARG_ENABLE(codec,
    [  --enable-codec[=<codec type>] Specify the codec type:
                              aes128 [default]: AES 128 Bit Encryption
                              aes256: AES 256 Bit Encryption],
    [ if   test "x$enableval" = "xaes128" ; then
        codec_type=CODEC_TYPE_AES128
      elif test "x$enableval" = "xaes256" ; then
        codec_type=CODEC_TYPE_AES256
      else
        echo
        echo "Error!"
        echo "Unknown codec type"
        exit -1
     fi
     AC_DEFINE_UNQUOTED([CODEC_TYPE], [$codec_type])
    ])

AC_ARG_ENABLE(sqlite-debug,
    [  --enable-sqlite-debug  Enable SQLite Debug assertions
                         This is a debugging feature
                         which should usually not be enabled],
    [ 
      AC_DEFINE([SQLITE_DEBUG])
    ])

dnl We only need the libraries above for the main library itself, but the
dnl pdfdc sample has additional requirements, check for them too (notice that
dnl we can't use "--optional-libs" wx-config option to do it all in one check
dnl for as long as we support 2.8 in which wx-config doesn't have this option
dnl yet).
core_WX_LIBS=$WX_LIBS
WX_CONFIG_CHECK([2.8.0],
    [WX_LIBS_TREEVIEW_SAMPLE=$WX_LIBS],
    [AC_MSG_WARN([Some wxWidgets libraries not available, treeview sample won't be built])],
    [adv,base,core,xml]
)
WX_LIBS=$core_WX_LIBS
AM_CONDITIONAL([BUILD_TREEVIEW_SAMPLE], [test -n "$WX_LIBS_TREEVIEW_SAMPLE"])

dnl This is needed by WX_LIKE_LIBNAME
WX_DETECT_STANDARD_OPTION_VALUES
dnl This macro is used to preserve the same name as was used with the previous
dnl build systems only.
WX_LIKE_LIBNAME([WXSQLITE3_LIBNAME], [wxcode], [wxsqlite3])

AC_SUBST(WXSQLITE3_LIBNAME)
AC_SUBST(WX_LIBS_TREEVIEW_SAMPLE)
AC_SUBST( LIBDIR, "lib" )

AC_CONFIG_FILES([Makefile wxsqlite3.pc])
AC_OUTPUT
