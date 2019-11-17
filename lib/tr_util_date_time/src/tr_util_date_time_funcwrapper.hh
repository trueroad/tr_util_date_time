//
// Date and time utility
// https://github.com/trueroad/tr_util_date_time
//
// tr_util_date_time_funcwrapper.hh:
//   Header file for standard functions wrapper
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

#ifndef INCLUDE_GUARD_TR_UTIL_DATE_TIME_FUNCWRAPPER_HH
#define INCLUDE_GUARD_TR_UTIL_DATE_TIME_FUNCWRAPPER_HH

#include <time.h>

namespace tr_util
{

  void tzset (void);
  struct tm *localtime_r (const time_t * /* t */, struct tm * /* st */);
  struct tm *gmtime_r (const time_t * /* t */, struct tm * /* st */);
  time_t timegm (struct tm * /* st */);

}

#endif // INCLUDE_GUARD_TR_UTIL_DATE_TIME_FUNCWRAPPER_HH
