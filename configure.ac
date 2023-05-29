dnl Process this script with autoconf to create configure for wxsqlite3 library
dnl
dnl Copyright (C) 2017-2023 Ulrich Telle <ulrich@telle-online.de>, Vadim Zeitlin <vadim@wxwidgets.org>
dnl
dnl This file is covered by the same licence as the entire wxSQLite3 package.

AC_INIT([wxsqlite3], [4.9.4], [ulrich@telle-online.de])

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

AC_ARG_ENABLE(sqlite-debug,
    [  --enable-sqlite-debug  Enable SQLite Debug assertions
                         This is a debugging feature
                         which should usually not be enabled],
    [
      AC_DEFINE([SQLITE_DEBUG])
    ])

AC_ARG_WITH([aes128cbc],
    [AS_HELP_STRING([--without-aes128cbc],
        [Disable support for AES 128 Bit CBC Encryption])],
    [],
    [with_aes128cbc=yes])

AS_IF([test "x$with_aes128cbc" = xno],
    [AC_DEFINE([WXSQLITE3_HAVE_CIPHER_AES_128_CBC], [0], [Define if you have AES 128 Bit CBC disabled])])

AC_ARG_WITH([aes256cbc],
    [AS_HELP_STRING([--without-aes256cbc],
        [Disable support for AES 256 Bit CBC Encryption])],
    [],
    [with_aes256cbc=yes])

AS_IF([test "x$with_aes256cbc" = xno],
    [AC_DEFINE([WXSQLITE3_HAVE_CIPHER_AES_256_CBC], [0], [Define if you have AES 256 Bit CBC disabled])])

AC_ARG_WITH([chacha20],
    [AS_HELP_STRING([--without-chacha20],
        [Disable support for ChaCha20-Poly1305 Encryption])],
    [],
    [with_chacha20=yes])

AS_IF([test "x$with_chacha20" = xno],
    [AC_DEFINE([WXSQLITE3_HAVE_CIPHER_CHACHA20], [0], [Define if you have ChaCha20-Poly1305 disabled])])

AC_ARG_WITH([sqlcipher],
    [AS_HELP_STRING([--without-sqlcipher],
        [Disable support for SQLCipher Encryption])],
    [],
    [with_sqlcipher=yes])

AS_IF([test "x$with_sqlcipher" = xno],
    [AC_DEFINE([WXSQLITE3_HAVE_CIPHER_SQLCIPHER], [0], [Define if you have SQLCipher disabled])])

AC_ARG_WITH([rc4],
    [AS_HELP_STRING([--without-rc4],
        [Disable support for RC4 Encryption])],
    [],
    [with_rc4=yes])

AS_IF([test "x$with_rc4" = xno],
    [AC_DEFINE([WXSQLITE3_HAVE_CIPHER_RC4], [0], [Define if you have RC4 disabled])])

AC_ARG_ENABLE(codec,
    [  --enable-codec[=<codec type>] Specify the codec type:
                              aes128: AES 128 Bit CBC Encryption
                              aes256: AES 256 Bit CBC Encryption
                              chacha20 [default]: ChaCha20-Poly1305 Encryption
                              sqlcipher: SQLCipher Encryption
                              rc4: RC4 Encryption],
      [if   test "x$enableval" = "xaes128" && test "x$with_aes128cbc" = xyes ; then
        codec_type=CODEC_TYPE_AES128
      elif test "x$enableval" = "xaes256" && test "x$with_aes256cbc" = xyes ; then
        codec_type=CODEC_TYPE_AES256
      elif test "x$enableval" = "xchacha20" && test "x$with_chacha20" = xyes ; then
        codec_type=CODEC_TYPE_CHACHA20
      elif test "x$enableval" = "xsqlcipher" && test "x$with_sqlcipher" = xyes ; then
        codec_type=CODEC_TYPE_SQLCIPHER
      elif test "x$enableval" = "xrc4" && test "x$with_rc4" = xyes ; then
        codec_type=CODEC_TYPE_RC4
      else
        echo
        echo "Error!"
        echo "Unknown or Unsupported codec type"
        exit -1
     fi
     AC_DEFINE_UNQUOTED([CODEC_TYPE], [$codec_type])
    ])

AS_IF([test "x$with_aes128cbc" = xno &&
       test "x$with_aes256cbc" = xno &&
       test "x$with_chacha20" = xno &&
       test "x$with_sqlcipher" = xno &&
       test "x$with_rc4" = xno],
       [AC_DEFINE([WXSQLITE3_HAVE_CODEC], [0], [All ciphers disabled so encryption is disabled])])

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

dnl Ensure that the samples can find the files they need when running from the
dnl build directory.
AC_CONFIG_LINKS([samples/sqlcipher-1.1.8-testkey.db:samples/sqlcipher-1.1.8-testkey.db
    samples/sqlcipher-2.0-beta-testkey.db:samples/sqlcipher-2.0-beta-testkey.db
    samples/sqlcipher-2.0-be-testkey.db:samples/sqlcipher-2.0-be-testkey.db
    samples/sqlcipher-2.0-le-testkey.db:samples/sqlcipher-2.0-le-testkey.db
    samples/sqlcipher-3.0-testkey.db:samples/sqlcipher-3.0-testkey.db
    samples/sqlcipher-4.0-testkey.db:samples/sqlcipher-4.0-testkey.db
])

AC_CANONICAL_HOST
hostX86=false
hostARM=false
AS_CASE([$host_cpu],
  [i?86], [hostX86=true],
  [x86_64], [hostX86=true],
  [arm*|aarch64*], [hostARM=true]
)
AM_CONDITIONAL([HOST_X86], [test x$hostX86 = xtrue])
AM_CONDITIONAL([HOST_ARM], [test x$hostARM = xtrue])

AC_CONFIG_FILES([Makefile wxsqlite3.pc])
AC_OUTPUT
