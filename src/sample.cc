//
// Date and time utility
// https://github.com/trueroad/tr_util_date_time
//
// sample.cc:
//   Sample for using utility functions
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

#include <chrono>
#include <iostream>

#include <ctime>

#include "tr_util_date_time_tz.hh"

int main (int argc, char *argv[])
{
  std::chrono::system_clock::time_point tp;

  if (argc == 1)
    {
      tp = std::chrono::system_clock::now ();
    }
  else if (argc == 2)
    {
      auto dtz {tr_util::from_rfc3339 (argv[1])};
      tp = tr_util::get_time_point (dtz);
    }

  auto dtz_local {tr_util::get_date_time_tz_local (tp)};
  std::cout << tr_util::to_rfc3339 (dtz_local) << std::endl
            << tr_util::to_pdfdate (dtz_local) << std::endl;

  auto dtz_utc {tr_util::get_date_time_tz_utc (tp)};
  std::cout << tr_util::to_rfc3339 (dtz_utc) << std::endl
            << tr_util::to_pdfdate (dtz_utc) << std::endl;

  return 0;
}
