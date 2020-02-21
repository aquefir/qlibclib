/****************************************************************************\
 *                                  qlibc™                                  *
 *                                                                          *
 *               Copyright © 2010-2015 Seungyoung “Steve” Kim               *
 *                      Copyright © 2020 ARQADIUM, LLC                      *
 *                       Licenced under BSD-2-Clause.                       *
\****************************************************************************/

/**
 * qtime header file.
 *
 * @file qtime.h
 */

#ifndef QTIME_H
#define QTIME_H

#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void qtime_timespec_diff(
   struct timespec t1, struct timespec t2, struct timespec* diff );
extern void qtime_timeval_diff(
   struct timeval t1, struct timeval t2, struct timeval* diff );

extern long qtime_current_milli( void );

extern char* qtime_localtime_strf(
   char* buf, int size, time_t utctime, const char* format );
extern char* qtime_localtime_str( time_t utctime );
extern const char* qtime_localtime_staticstr( time_t utctime );
extern char* qtime_gmt_strf(
   char* buf, int size, time_t utctime, const char* format );
extern char* qtime_gmt_str( time_t utctime );
extern const char* qtime_gmt_staticstr( time_t utctime );
extern time_t qtime_parse_gmtstr( const char* gmtstr );

#ifdef __cplusplus
}
#endif

#endif /* QTIME_H */
