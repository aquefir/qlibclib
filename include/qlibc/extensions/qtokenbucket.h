/****************************************************************************\
 *                                  qlibc™                                  *
 *                                                                          *
 *               Copyright © 2010-2015 Seungyoung “Steve” Kim               *
 *                      Copyright © 2020 ARQADIUM, LLC                      *
 *                       Licenced under BSD-2-Clause.                       *
\****************************************************************************/

/**
 * Rotating file logger.
 *
 * This is a qLibc extension implementing application level auto-rotating file
 * logger.
 *
 * @file qtokenbucket.h
 */

#ifndef QTOKENBUCKET_H
#define QTOKENBUCKET_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/* types */
typedef struct qtokenbucket_s qtokenbucket_t;

/* public functions */
extern void qtokenbucket_init( qtokenbucket_t* bucket,
   int init_tokens,
   int max_tokens,
   int tokens_per_sec );
extern bool qtokenbucket_consume( qtokenbucket_t* bucket, int tokens );
extern long qtokenbucket_waittime( qtokenbucket_t* bucket, int tokens );

/**
 * qtokenbucket internal data structure
 */
struct qtokenbucket_s
{
	double tokens; /*!< current number of tokens. */
	int max_tokens; /*!< maximum number of tokens. */
	int tokens_per_sec; /*!< fill rate per second. */
	long last_fill; /*!< last refill time in Millisecond. */
};

#ifdef __cplusplus
}
#endif

#endif /* QTOKENBUCKET_H */
