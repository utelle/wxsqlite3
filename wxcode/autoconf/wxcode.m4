dnl ---------------------------------------------------------------------------
dnl Author:          Francesco Montorsi
dnl Creation date:   14/9/2005
dnl RCS-ID:          $Id$
dnl Purpose:         Some M4 macros specific for wxCode components
dnl ---------------------------------------------------------------------------


dnl
dnl This file contains macros meant to be used by the wxCode component's configure.ac
dnl files. If you are looking for autoconf macros which _detect_ wxCode components,
dnl then please look at wxcodecheck.m4
dnl


dnl ---------------------------------------------------------------------------
dnl WXCODE_INIT
dnl
dnl Sets as language the C++ language and includes the wxpresets.m4 macro file
dnl ---------------------------------------------------------------------------
AC_DEFUN([WXCODE_INIT],
        [
            AC_PREREQ([2.57])

            m4_include(../wxcode/autoconf/wxwin.m4)
            AC_LANG(C++)

            dnl wxCode components usually keep the install.sh and config.{guess|sub}
            dnl scripts in the "build" folder; however we cannot add this line:
            dnl     AC_CONFIG_AUX_DIR(build)
            dnl inside this macro as otherwise autoconf would not get the "build"
            dnl relative path correctly. The line above must be _directly_ written
            dnl in the component's configure.ac!

            dnl required by Bakefile:
            AC_CANONICAL_SYSTEM
        ])


dnl ---------------------------------------------------------------------------
dnl WXCODE_ARG_ENABLE([name of the --enable- feature],
dnl                      [description of that feature],
dnl                      [default value for that feature])
dnl
dnl ---------------------------------------------------------------------------
AC_DEFUN([WXCODE_ARG_ENABLE],
        [
          AC_ARG_ENABLE([$1],
                        AC_HELP_STRING([--enable-$1],
                                       [$2 (default is $3)]),,
          [enable_$1=$3])
        ])


dnl ---------------------------------------------------------------------------
dnl WXCODE_ARG_WITH([name of the --with- option],
dnl                    [description of that option],
dnl                    [default value for that option])
dnl
dnl ---------------------------------------------------------------------------
AC_DEFUN([WXCODE_ARG_WITH],
        [
          AC_ARG_WITH([$1],
                      AC_HELP_STRING([--with-$1],
                                     [$2 (default is $3)]),,
          [with_$1=$3])
        ])


dnl ---------------------------------------------------------------------------
dnl WXCODE_OPTIONS([option-list])
dnl
dnl This macro is here to sum up the macro calls required to get the standard
dnl wxWidgets options.
dnl "option-list" is a comma-separed list of the following possible values:
dnl - shared           => --enable-shared
dnl - debug            => --enable-debug
dnl - unicode          => --enable-unicode
dnl - toolkit          => --with-toolkit
dnl - wxversion        => --with-wxversion
dnl - wxshared         => --with-wxshared
dnl ---------------------------------------------------------------------------
AC_DEFUN([WXCODE_OPTIONS],
        [
            WX_CONFIG_OPTIONS
            WX_STANDARD_OPTIONS([$1])

            # we want to always have DEBUG==WX_DEBUG and UNICODE==WX_UNICODE
            WX_DEBUG=$DEBUG
            WX_UNICODE=$UNICODE
        ])


dnl ---------------------------------------------------------------------------
dnl WXCODE_CHECKS([minimum-wx-version], [addwxlibraries])
dnl
dnl Calls WX_CONFIG_CHECK with the wx-config flags determined using the
dnl options defined by WXCODE_OPTIONS
dnl ---------------------------------------------------------------------------
AC_DEFUN([WXCODE_CHECKS],
        [
            WX_CONVERT_STANDARD_OPTIONS_TO_WXCONFIG_FLAGS
            WX_CONFIG_CHECK([$1],,,[$2],[$WXCONFIG_FLAGS])
            WX_DETECT_STANDARD_OPTION_VALUES

            # VERY IMPORTANT: these AC_PROG_C* checks must go after WX_DEBUG
            #                 option handling or they'll add automatically "-g -O0"
            #                 flags to the CXXFLAGS and CPPFLAGS:

            # required when compiling C files:
            AC_PROG_CC

            # required when compiling C++ files:
            AC_PROG_CXX
        ])


dnl ---------------------------------------------------------------------------
dnl WXCODE_END_PART1
dnl
dnl Tells autoconf which output files must be generated; includes bakefile
dnl checks for the options present in the BKL file; prints a nice message
dnl about the configuration of the component.
dnl ---------------------------------------------------------------------------
AC_DEFUN([WXCODE_END_PART1],
        [
            dnl config output files
            AC_BAKEFILE([m4_include(autoconf_inc.m4)])
            AC_CONFIG_FILES([Makefile])
            AC_OUTPUT

            WX_STANDARD_OPTIONS_SUMMARY_MSG_BEGIN
        ])


dnl ---------------------------------------------------------------------------
dnl WXCODE_END_PART2
dnl
dnl Completes the message to the user printing the settings of the wxWidgets
dnl build which will be used to compile the component.
dnl ---------------------------------------------------------------------------
AC_DEFUN([WXCODE_END_PART2],
        [
            WX_STANDARD_OPTIONS_SUMMARY_MSG_END
        ])


dnl ---------------------------------------------------------------------------
dnl WXCODE_END
dnl
dnl The WXCODE_END macros are divided in two parts WXCODE_END_PART1 and
dnl WXCODE_END_PART2 so that if you want to show additional component
dnl configuration settings you can write:
dnl
dnl WXCODE_END_PART1
dnl if [[ "$MYVAR" = "1" ]]; then
dnl     echo "  - MYVAR is set"
dnl else
dnl     echo "  - MYVAR is not set"
dnl fi
dnl WXCODE_END_PART2
dnl ---------------------------------------------------------------------------
AC_DEFUN([WXCODE_END],
        [
            WXCODE_END_PART1
            WXCODE_END_PART2
        ])


dnl Other generic macros
m4_include(../wxcode/autoconf/wxcodecheck.m4)
