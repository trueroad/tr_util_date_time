//
// Date and time utility
// https://github.com/trueroad/tr_util_date_time
//
// tr_util_date_time_tz.cc:
//   Utility functions implementation
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
#include "tr_util_date_time_tz.hh"

#include <chrono>
#include <iomanip>
#include <sstream>
#include <string>

#include <time.h>

#include "tr_util_date_time_funcwrapper.hh"

namespace tr_util
{

  date_time_tz
  get_date_time_tz_local (const std::chrono::system_clock::time_point &tp)
  {
    date_time_tz retval;

    time_t t {std::chrono::system_clock::to_time_t (tp)};

    struct tm tm_local;
    tr_util::localtime_r (&t, &tm_local);

    retval.year = tm_local.tm_year + 1900;
    retval.month = tm_local.tm_mon + 1;
    retval.day = tm_local.tm_mday;
    retval.hour = tm_local.tm_hour;
    retval.minute = tm_local.tm_min;
    retval.second = tm_local.tm_sec;

    long tz_offset;

#ifdef HAVE_BSD_TM_GMTOFF
    tz_offset = tm_local.tm_gmtoff;
#else
    {
      struct tm tm_utc;
      tr_util::gmtime_r (&t, &tm_utc);

      tz_offset = (tm_local.tm_hour - tm_utc.tm_hour) * 60 * 60 +
        (tm_local.tm_min - tm_utc.tm_min) * 60 +
        (tm_local.tm_sec - tm_utc.tm_sec);

      if (tm_local.tm_year > tm_utc.tm_year)
        tz_offset += 24 * 60 * 60;
      else if (tm_local.tm_year < tm_utc.tm_year)
        tz_offset -= 24 * 60 * 60;
      else
        {
          if (tm_local.tm_mon > tm_utc.tm_mon)
            tz_offset += 24 * 60 * 60;
          else if (tm_local.tm_mon < tm_utc.tm_mon)
            tz_offset -= 24 * 60 * 60;
          else
            {
              if (tm_local.tm_mday > tm_utc.tm_mday)
                tz_offset += 24 * 60 * 60;
              else if (tm_local.tm_mday < tm_utc.tm_mday)
                tz_offset -= 24 * 60 * 60;
            }
        }
    }
#endif // HAVE_BSD_TM_GMTOFF

    if (tz_offset > 0)
      {
        retval.tz_hour = tz_offset / (60 * 60);
        retval.tz_minute = tz_offset % (60 * 60) / 60;
      }
    else if (tz_offset < 0)
      {
        retval.tz_hour = tz_offset / (60 * 60);
        retval.tz_minute = (-tz_offset) % (60 * 60) / 60;
      }
    else
      {
        retval.tz_hour = 0;
        retval.tz_minute = 0;
      }

    return retval;
  }

  date_time_tz
  get_date_time_tz_utc (const std::chrono::system_clock::time_point &tp)
  {
    date_time_tz retval;

    time_t t {std::chrono::system_clock::to_time_t (tp)};

    struct tm tm_utc;
    tr_util::gmtime_r (&t, &tm_utc);

    retval.year = tm_utc.tm_year + 1900;
    retval.month = tm_utc.tm_mon + 1;
    retval.day = tm_utc.tm_mday;
    retval.hour = tm_utc.tm_hour;
    retval.minute = tm_utc.tm_min;
    retval.second = tm_utc.tm_sec;

    retval.tz_hour = 0;
    retval.tz_minute = 0;

    return retval;
  }

  std::string to_rfc3339 (const date_time_tz &dtz)
  {
    std::stringstream ss;
    ss << std::setw (4) << std::setfill ('0') << dtz.year
       << "-"
       << std::setw (2) << std::setfill ('0') << dtz.month
       << "-"
       << std::setw (2) << std::setfill ('0') << dtz.day
       << "T"
       << std::setw (2) << std::setfill ('0') << dtz.hour
       << ":"
       << std::setw (2) << std::setfill ('0') << dtz.minute
       << ":"
       << std::setw (2) << std::setfill ('0') << dtz.second;

    if (dtz.tz_hour == 0 && dtz.tz_minute == 0)
      ss << "Z";
    else
      {
        ss << (dtz.tz_hour < 0 ? "-" : "+")
           << std::setw (2) << std::setfill ('0')
           << (dtz.tz_hour < 0 ? -dtz.tz_hour : dtz.tz_hour)
           << ":"
           << std::setw (2) << std::setfill ('0') << dtz.tz_minute;
      }

    return ss.str ();
  }

  std::string to_pdfdate (const date_time_tz &dtz)
  {
    std::stringstream ss;
    ss << "D:"
       << std::setw (4) << std::setfill ('0') << dtz.year
       << std::setw (2) << std::setfill ('0') << dtz.month
       << std::setw (2) << std::setfill ('0') << dtz.day
       << std::setw (2) << std::setfill ('0') << dtz.hour
       << std::setw (2) << std::setfill ('0') << dtz.minute
       << std::setw (2) << std::setfill ('0') << dtz.second;

    if (dtz.tz_hour == 0 && dtz.tz_minute == 0)
      ss << "Z";
    else
      {
        ss << (dtz.tz_hour < 0 ? "-" : "+")
           << std::setw (2) << std::setfill ('0')
           << (dtz.tz_hour < 0 ? -dtz.tz_hour : dtz.tz_hour)
           << "'"
           << std::setw (2) << std::setfill ('0') << dtz.tz_minute
           << "'";
      }

    return ss.str ();
  }

  std::chrono::system_clock::time_point
  get_time_point (const date_time_tz &dtz)
  {
    struct tm st {0};
    st.tm_year = dtz.year - 1900;
    st.tm_mon = dtz.month - 1;
    st.tm_mday = dtz.day;
    st.tm_hour = dtz.hour;
    st.tm_min = dtz.minute;
    st.tm_sec = dtz.second;

    std::chrono::system_clock::time_point tp
      {std::chrono::system_clock::from_time_t (tr_util::timegm (&st))};

    std::chrono::hours tz_hour {dtz.tz_hour};
    std::chrono::minutes tz_minute {dtz.tz_minute};
    std::chrono::seconds tz_offset {tz_hour + tz_minute};

    return tp - tz_offset;
  }

  date_time_tz from_rfc3339 (const std::string &str)
  {
    date_time_tz dtz;

    std::stringstream ss;
    ss << str;
    ss >> dtz.year;
    ss.ignore (1, '-');
    ss >> dtz.month;
    ss.ignore (1, '-');
    ss >> dtz.day;
    ss.ignore (1, 'T');
    ss >> dtz.hour;
    ss.ignore (1, ':');
    ss >> dtz.minute;
    ss.ignore (1, ':');
    ss >> dtz.second;

    char c;
    ss >> c;
    if (c == 'Z')
      {
        dtz.tz_hour = 0;
        dtz.tz_minute = 0;
      }
    else if (c == '+')
      {
        ss >> dtz.tz_hour;
        ss.ignore (1, ':');
        ss >> dtz.tz_minute;
      }
    else if (c == '-')
      {
        ss >> dtz.tz_hour;
        dtz.tz_hour = -dtz.tz_hour;
        ss.ignore (1, ':');
        ss >> dtz.tz_minute;
      }
    else
      {
        throw std::runtime_error ("tr_util::from_rfc3339: parse error");
      }

    return dtz;
  }

}
