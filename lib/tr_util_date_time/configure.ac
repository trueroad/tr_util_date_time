#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([libtr_util_date_time], [20191117])
AC_CONFIG_AUX_DIR([.])
AM_INIT_AUTOMAKE([foreign])
AC_CONFIG_SRCDIR([src/tr_util_date_time_tz.cc])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX
AX_CXX_COMPILE_STDCXX([14], [ext], [optional])
AS_IF([test $HAVE_CXX14 = 0],
    [AX_CXX_COMPILE_STDCXX([11], [ext], [mandatory])])
AC_PROG_RANLIB

# Checks for libraries.

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
TR_CXX_CHECK_BSD_TM_GMTOFF

# Checks for library functions.
TR_CXX_CHECK_POSIX_TZSET
TR_CXX_CHECK_WINDOWS__TZSET
TR_CXX_CHECK_POSIX_LOCALTIME_R
TR_CXX_CHECK_C11_LOCALTIME_S
TR_CXX_CHECK_WINDOWS_LOCALTIME_S
TR_CXX_CHECK_POSIX_GMTIME_R
TR_CXX_CHECK_C11_GMTIME_S
TR_CXX_CHECK_WINDOWS_GMTIME_S
TR_CXX_CHECK_BSD_TIMEGM
TR_CXX_CHECK_WINDOWS__MKGMTIME
TR_CXX_CHECK_POSIX_SETENV
TR_CXX_CHECK_POSIX_UNSETENV

AC_CONFIG_FILES([Makefile
                 src/Makefile])
AC_OUTPUT
