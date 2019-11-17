#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([sample-tr_util_date_time], [20191117])
AM_INIT_AUTOMAKE([foreign])
AC_CONFIG_SRCDIR([src/sample.cc])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX
AX_CXX_COMPILE_STDCXX([14], [noext], [optional])
AS_IF([test $HAVE_CXX14 = 0],
    [AX_CXX_COMPILE_STDCXX([11], [noext], [mandatory])])

# Checks for libraries.

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([Makefile
                 src/Makefile])
AC_CONFIG_SUBDIRS([lib/tr_util_date_time])
AC_OUTPUT
