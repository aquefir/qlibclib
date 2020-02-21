/****************************************************************************\
 *                                  qlibc™                                  *
 *                                                                          *
 *               Copyright © 2010-2015 Seungyoung “Steve” Kim               *
 *                      Copyright © 2020 ARQADIUM, LLC                      *
 *                       Licenced under BSD-2-Clause.                       *
\****************************************************************************/

/**
 * qcount header file.
 *
 * @file qcount.h
 */

#ifndef QCOUNT_H
#define QCOUNT_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

extern int64_t qcount_read( const char* filepath );
extern bool qcount_save( const char* filepath, int64_t number );
extern int64_t qcount_update( const char* filepath, int64_t number );

#ifdef __cplusplus
}
#endif

#endif /* QCOUNT_H */
