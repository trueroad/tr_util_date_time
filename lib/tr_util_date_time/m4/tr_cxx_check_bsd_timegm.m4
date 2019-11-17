#
# Date and time utility
# https://github.com/trueroad/tr_util_date_time
#
# tr_cxx_check_bsd_timegm.m4:
#   autoconf macro TR_CXX_CHECK_BSD_TIMEGM
#
# Copyright (C) 2019 Masamichi Hosoda.
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
# * Redistributions of source code must retain the above copyright notice,
#   this list of conditions and the following disclaimer.
#
# * Redistributions in binary form must reproduce the above copyright notice,
#   this list of conditions and the following disclaimer in the documentation
#   and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED.
# IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
# OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
# OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
# SUCH DAMAGE.
#

AC_DEFUN([TR_CXX_CHECK_BSD_TIMEGM],
    [AC_LANG_PUSH([C++])
     AC_MSG_CHECKING([for BSD timegm on C++])
     AC_COMPILE_IFELSE(
         [AC_LANG_PROGRAM([[
#include <time.h>
              ]], [[
struct tm st {0};
st.tm_year = 70;
st.tm_mday = 1;
time_t t = timegm (&st);
              ]])],
         [HAVE_BSD_TIMEGM=1
          AC_DEFINE([HAVE_BSD_TIMEGM], [1],
              [Define if you have BSD timegm function on C++])
          AC_MSG_RESULT([yes])],
         [HAVE_BSD_TIMEGM=0
          AC_MSG_RESULT([no])])
     AC_LANG_POP([C++])])
