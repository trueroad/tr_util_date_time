//
// Date and time utility
// https://github.com/trueroad/tr_util_date_time
//
// tr_util_date_time_funcwrapper.cc:
//   Standard function wrapper
//
// Copyright (C) 2019 Masamichi Hosoda.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
// * Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
//
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED.
// IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
// OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
// OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
// SUCH DAMAGE.
//

#include "config.h"

#if (defined HAVE_C11_LOCALTIME_S || defined HAVE_C11_GMTIME_S)
#define __STDC_WANT_LIB_EXT1__ 1
#endif

#include "tr_util_date_time_funcwrapper.hh"

#include <mutex>

#include <stdlib.h>
#include <time.h>

namespace
{
  std::mutex mtx;

  inline void inner_tzset (void)
  {
#if (defined HAVE_WINDOWS__TZSET && defined _WIN32)
    _tzset ();
#else
#ifdef HAVE_POSIX_TZSET
    tzset ();
#endif
#endif
  }

}

namespace tr_util
{

  void tzset (void)
  {
#if (defined HAVE_POSIX_TZSET || \
     (defined HAVE_WINDOWS__TZSET && defined _WIN32))
    std::lock_guard<std::mutex> lock (mtx);
    inner_tzset ();
#endif
  }

  struct tm *localtime_r (const time_t *t, struct tm *st)
  {
    std::lock_guard<std::mutex> lock (mtx);
    inner_tzset ();
#ifdef HAVE_POSIX_LOCALTIME_R
    // POSIX localtime_r
    return ::localtime_r (t, st);
#else
#ifdef HAVE_C11_LOCALTIME_S
    // C11 localtime_s
    return localtime_s (t, st);
#else
#ifdef HAVE_WINDOWS_LOCALTIME_S
    // Windows localtime_s
    return (localtime_s (st, t) ? nullptr : st);
#else
    // Standard C localtime
    struct tm *lst = localtime (t);
    if (lst)
      {
        *st = *lst;
        return st;
      }
    return nullptr;
#endif
#endif
#endif
  }

  struct tm *gmtime_r (const time_t *t, struct tm *st)
  {
    std::lock_guard<std::mutex> lock (mtx);
#ifdef HAVE_POSIX_GMTIME_R
    // POSIX gmtime_r
    return ::gmtime_r (t, st);
#else
#ifdef HAVE_C11_GMTIME_S
    // C11 gmtime_s
    return gmtime_s (t, st);
#else
#ifdef HAVE_WINDOWS_GMTIME_S
    // Windows gmtime_s
    return (gmtime_s (st, t) ? nullptr : st);
#else
    // Standard C gmtime
    struct tm *lst = gmtime (t);
    if (lst)
      {
        *st = *lst;
        return st;
      }
    return nullptr;
#endif
#endif
#endif
  }

  time_t timegm (struct tm *st)
  {
#ifdef HAVE_BSD_TIMEGM
    // BSD timegm
    return ::timegm (st);
#else
#if (defined HAVE_WINDOWS__MKGMTIME && defined _WIN32)
    // Windows _mkgmtime
    return _mkgmtime (st);
#else
#if (defined HAVE_POSIX_SETENV && defined HAVE_POSIX_UNSETENV && \
     defined HAVE_POSIX_TZSET)
    // POSIX portable
    std::lock_guard<std::mutex> lock (mtx);

    char *tz {getenv ("TZ")};
    std::string str_tz;
    if (tz)
      str_tz = tz;
    setenv ("TZ", "UTC0", 1);
    inner_tzset ();
    time_t t {mktime (st)};
    if (tz)
      setenv ("TZ", str_tz.c_str (), 1);
    else
      unsetenv ("TZ");
    inner_tzset ();

    return t;
#else
#error No portable way
#endif
#endif
#endif
  }

}
