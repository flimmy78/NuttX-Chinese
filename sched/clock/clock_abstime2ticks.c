/****************************************************************************
 * sched/clock/clock_abstime2ticks.c
 *
 *   Copyright (C) 2007, 2008, 2013-2014, 2016 Gregory Nutt. All rights reserved.
 *   Author: Gregory Nutt <gnutt@nuttx.org>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name NuttX nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <time.h>
#include <errno.h>
#include <debug.h>
#include "clock/clock.h"

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: compare_timespec
 *
 * Description:
 *    Return < 0 if time a is before time b
 *    Return > 0 if time b is before time a
 *    Return 0 if time a is the same as time b
 *
 ****************************************************************************/

static long compare_timespec(FAR const struct timespec *a,
                             FAR const struct timespec *b)
{
  if (a->tv_sec < b->tv_sec)
    {
      return -1;
    }

  if (a->tv_sec > b->tv_sec)
    {
      return 1;
    }

  return (long)a->tv_nsec - (long)b->tv_nsec;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: clock_abstime2ticks
 *
 * Description:
 *   Convert an absolute timespec delay to system timer ticks.
 *
 * Input Parameters:
 *   clockid - The timing source to use in the conversion
 *   reltime - Convert this absolue time to system clock ticks.
 *   ticks - Return the converted number of ticks here.
 *
 * Returned Value:
 *   OK on success; A non-zero error number on failure;
 *
 * Assumptions:
 *   Interrupts should be disabled so that the time is not changing during
 *   the calculation
 *
 ****************************************************************************/

int clock_abstime2ticks(clockid_t clockid, FAR const struct timespec *abstime,
                        FAR ssystime_t *ticks)
{
  struct timespec currtime;
  struct timespec reltime;
  int             ret;

  /* Convert the timespec to clock ticks.  NOTE: Here we use internal knowledge
   * that CLOCK_REALTIME is defined to be zero!
   */

  ret = clock_gettime(clockid, &currtime);
  if (ret != OK)
    {
      return EINVAL;
    }

  if (compare_timespec(abstime, &currtime) < 0)
    {
      /* Every caller of clock_abstime2ticks check 'ticks < 0' to see if
       * absolute time is in the past. So lets just return negative tick
       * here.
       */

      *ticks = -1;
      return OK;
    }

  /* The relative time to wait is the absolute time minus the current time. */

  reltime.tv_nsec = (abstime->tv_nsec - currtime.tv_nsec);
  reltime.tv_sec  = (abstime->tv_sec  - currtime.tv_sec);

  /* Check if we were supposed to borrow from the seconds to borrow from the
   * seconds
   */

  if (reltime.tv_nsec < 0)
    {
      reltime.tv_nsec += NSEC_PER_SEC;
      reltime.tv_sec  -= 1;
    }

  /* Convert this relative time into clock ticks. */

  return clock_time2ticks(&reltime, ticks);
}
