dnl Process this script with autoconf to create configure for sqlite3secure library
dnl
dnl Copyright (C) 2018 Ulrich Telle <ulrich@telle-online.de>
dnl
dnl This file is covered by the same licence as the entire wxSQLite3 package.

AC_INIT([sqlite3secure], [1.0.0], [ulrich@telle-online.de])

dnl This is the version tested with, might work with earlier ones.
AC_PREREQ([2.69])

AC_CONFIG_SRCDIR([src/sqlite3.h])
AC_CONFIG_AUX_DIR([../admin/build-aux])
AC_CONFIG_MACRO_DIR([../admin/m4])

AM_INIT_AUTOMAKE([1.11 foreign subdir-objects])
AM_MAINTAINER_MODE([enable])
AM_SILENT_RULES([yes])

dnl Allow adding MSW-specific fragments to the makefile.
case "${host}" in
    *-*-cygwin* )
        USE_MSW=1
        ;;

    *-*-mingw32* )
        USE_MSW=1
        ;;
esac
AM_CONDITIONAL(USE_MSW, [test -n "$USE_MSW"])

if test -n "$USE_MSW"; then
    AC_CHECK_TOOL([WINDRES], [windres], no)
fi

LT_INIT()
AC_PROG_CXX
AC_LANG(C++)

AC_ARG_ENABLE(codec,
    [  --enable-codec[=<codec type>] Specify the codec type:
                              aes128: AES 128 Bit CBC Encryption
                              aes256: AES 256 Bit CBC Encryption
                              chacha20 [default]: ChaCha20-Poly1305 Encryption
                              sqlcipher: SQLCipher Encryption],
    [ if   test "x$enableval" = "xaes128" ; then
        codec_type=CODEC_TYPE_AES128
      elif test "x$enableval" = "xaes256" ; then
        codec_type=CODEC_TYPE_AES256
      elif test "x$enableval" = "xchacha20" ; then
        codec_type=CODEC_TYPE_CHACHA20
      elif test "x$enableval" = "xsqlcipher" ; then
        codec_type=CODEC_TYPE_SQLCIPHER
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

AC_SUBST(SQLITE3SECURE_LIBNAME, "sqlite3secure-1.0")
AC_SUBST( LIBDIR, "lib" )

AC_CONFIG_FILES([Makefile sqlite3secure.pc])
AC_OUTPUT
