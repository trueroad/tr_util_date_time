//
// Date and time utility
// https://github.com/trueroad/tr_util_date_time
//
// tr_util_date_time_tz.hh:
//   Utility functions header file
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

#ifndef INCLUDE_GUARD_TR_UTIL_DATE_TIME_TZ_HH
#define INCLUDE_GUARD_TR_UTIL_DATE_TIME_TZ_HH

#include <chrono>
#include <string>

namespace tr_util
{
  class date_time_tz
  {
  public:
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
    int tz_hour;
    int tz_minute;
  };

  date_time_tz
  get_date_time_tz_local
  (const std::chrono::system_clock::time_point & /* tp */);
  date_time_tz
  get_date_time_tz_utc
  (const std::chrono::system_clock::time_point & /* tp */);

  std::string
  to_rfc3339 (const date_time_tz & /* dtz */);
  std::string
  to_pdfdate (const date_time_tz & /* dtz */);

  std::chrono::system_clock::time_point
  get_time_point (const date_time_tz & /* dtz */);

  date_time_tz
  from_rfc3339 (const std::string & /* str */);

}

#endif // INCLUDE_GUARD_TR_UTIL_DATE_TIME_TZ_HH
