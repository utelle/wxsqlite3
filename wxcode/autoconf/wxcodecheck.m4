dnl ---------------------------------------------------------------------------
dnl Author:          Francesco Montorsi
dnl Creation date:   14/9/2005
dnl RCS-ID:          $Id$
dnl Purpose:         Contains M4 macros intended to be used also by external
dnl                  projects which depends from a wxCode component
dnl ---------------------------------------------------------------------------


dnl ---------------------------------------------------------------------------
dnl WXCODE_SAVE_COREVAR()
dnl
dnl Saves the CPPFLAGS, CXXFLAGS, CFLAGS and LIBS variables in some helper
dnl variables which are used to restore them later (see AM_RESTORE_COREVAR)
dnl ---------------------------------------------------------------------------
AC_DEFUN([WXCODE_SAVE_COREVAR],
        [
        SAVED_CPPFLAGS="$CPPFLAGS"
        SAVED_CXXFLAGS="$CXXFLAGS"
        SAVED_CFLAGS="$CFLAGS"
        SAVED_LIBS="$LIBS"
    ])


dnl ---------------------------------------------------------------------------
dnl WXCODE_RESTORE_COREVAR()
dnl
dnl Loads into the CPPFLAGS, CXXFLAGS, CFLAGS and LIBS variables the values
dnl of the helper variables set by AM_SAVE_COREVAR
dnl ---------------------------------------------------------------------------
AC_DEFUN([WXCODE_RESTORE_COREVAR],
        [
        CPPFLAGS="$SAVED_CPPFLAGS"
        CXXFLAGS="$SAVED_CXXFLAGS"
        CFLAGS="$SAVED_CFLAGS"
        LIBS="$SAVED_LIBS"
    ])



dnl ---------------------------------------------------------------------------
dnl WXCODE_CHECKFOR_COMPONENT(
dnl         [name (mixed case) of the component to check],
dnl         [name of a header of the component to check (with 'wx/' prefix and '.h' suffix)],
dnl         [name of the library of the component to check (without 'lib' prefix and without .a/.so suffix)],
dnl         [a C++ line of code that forces the test program to be linked against the component in order to work],
dnl         [action if found],
dnl         [action if not found])
dnl
dnl Creates a little test program to check for presence of a wxCode component.
dnl Note that this macro does not automatically adds anything to the CPPFLAGS,
dnl CFLAGS or LIBS variables.
dnl ---------------------------------------------------------------------------
AC_DEFUN([WXCODE_CHECKFOR_COMPONENT],
        [
            dnl save original flags into support variables
            WXCODE_SAVE_COREVAR()

            dnl add to the compilation & link flags the wxWidgets flags
            dnl (we assume they have been set by AM_WXPRESETS)
            dnl
            dnl NOTE: this is very important since the test program
            dnl       we will compile needs to be linked against wx
            dnl       and the configure script will use these *FLAGS
            dnl       variables and it cannot be told to use other flags.
            dnl
            dnl NOTE2: we don't want to put into *FLAGS variables the
            dnl        WX_* variable values since the Makefile.in for
            dnl        a wxpresets-based application already merges
            dnl        the *FLAGS contents with WX_* vars
            dnl
            dnl NOTE3: the CXXFLAGS are merged with CPPFLAGS and
            dnl        thus we don't need to add the WX_CPPFLAGS to both
            CPPFLAGS="$CPPFLAGS $WX_CPPFLAGS"
            CFLAGS="$CFLAGS $WX_CFLAGS_ONLY"

            dnl before WX_LIBS we want the lib of the component to check
            LIBS="$LIBS -l$3 $WX_LIBS"

            dnl check for this component presence
            if test -z "$COMPCHECK_MSG"; then
                dnl allow customized messages
                COMPCHECK_MSG="if $1 is available"
            fi
            AC_MSG_CHECKING([$COMPCHECK_MSG])
            AC_LINK_IFELSE([
                            AC_LANG_PROGRAM([#include <$2>],
                                            [$4])
                           ],
                            [$1_PRESENCE=1], [$1_PRESENCE=0])

            if test "$$1_PRESENCE" = "1"; then
               AC_MSG_RESULT([yes])
               $5
            else
               AC_MSG_RESULT([no])
               $6
            fi

            dnl restore the original flags
            WXCODE_RESTORE_COREVAR()
        ])


dnl ---------------------------------------------------------------------------
dnl WXCODE_CHECKFOR_COMPONENT_VERSION(
dnl         [name (mixed case) of the component to check],
dnl         [name of a header of the component to check (with 'wx/' prefix and '.h' suffix)],
dnl         [name of the library of the component to check (without 'lib' prefix and without .a/.so suffix)],
dnl         [a C++ line of code that forces the test program to be linked against the component in order to work],
dnl    *    [major-version.minor-version],
dnl    *    [versionsym-prefix],
dnl    *    [versionsym-postfix],
dnl         [action if found],
dnl         [action if not found])
dnl
dnl Like AM_WXCODE_CHECKFOR_COMPONENT (the only new arguments it takes are marked
dnl with *) but also includes a version check against the component to check for.
dnl Note that the given version MUST be composed of three digits separed by a dot,
dnl i.e. a string in form "1.2.3" which will be checked against the string
dnl
dnl     [versionsym-prefix]MAJOR[versionsym-postfix].\
dnl           [versionsym-prefix]MINOR[versionsym-postfix].\
dnl               [versionsym-prefix]RELEASE[versionsym-postfix]
dnl
dnl where *MAJOR*, *MINOR* and *RELEASE* are three symbols which should have
dnl been #defined in the compdef.h header file (see template/include/wx/mycompdef.h).
dnl ---------------------------------------------------------------------------
AC_DEFUN([WXCODE_CHECKFOR_COMPONENT_VERSION],
        [
            dnl break version string in single digits
            major=`echo $5 | sed 's/\([[0-9]]\).\([[0-9]]\).\([[0-9]]\)/\1/'`
            minor=`echo $5 | sed 's/\([[0-9]]\).\([[0-9]]\).\([[0-9]]\)/\2/'`
            release=`echo $5 | sed 's/\([[0-9]]\).\([[0-9]]\).\([[0-9]]\)/\3/'`

            dnl cache the symbol names
            majsym="$6""MAJOR""$7"
            minsym="$6""MINOR""$7"
            relsym="$6""RELEASE""$7"

            dnl call our base macro adding the version check
            COMPCHECK_MSG="if $1 (version >= $5) is available"
            WXCODE_CHECKFOR_COMPONENT([$1], [$2], [$3],
                [
                    $4

                    // version check
                    #if defined($majsym) && defined($minsym) && defined($relsym)
                        #if ($majsym > ($major) || \
                            ($majsym == ($major) && $minsym > ($minor)) || \
                            ($majsym == ($major) && $minsym == ($minor) && $relsym >= ($release)))
                            // this component is recent enough
                        #else
                            #error $1 is too old ! At least version $5 is required
                        #endif
                    #else
                        #error $1 does not define its version symbols $majsym, $minsym, $relsym
                    #endif
                ],
                [$8], [$9])
        ])


dnl ---------------------------------------------------------------------------
dnl Deprecated macro wrappers
dnl ---------------------------------------------------------------------------

AC_DEFUN([AM_SAVE_COREVAR], [WXCODE_SAVE_COREVAR])
AC_DEFUN([AM_RESTORE_COREVAR], [WXCODE_RESTORE_COREVAR])
AC_DEFUN([AM_WXCODE_CHECKFOR_COMPONENT], [WXCODE_CHECKFOR_COMPONENT])
AC_DEFUN([AM_WXCODE_CHECKFOR_COMPONENT_VERSION], [WXCODE_CHECKFOR_COMPONENT_VERSION])

