/****************************************************************************\
 *                                  qlibc™                                  *
 *                                                                          *
 *               Copyright © 2010-2015 Seungyoung “Steve” Kim               *
 *                      Copyright © 2020 ARQADIUM, LLC                      *
 *                       Licenced under BSD-2-Clause.                       *
\****************************************************************************/

/**
 * @file qtokenbucket.c Token Bucket implementation.
 *
 * Current implementation is not thread-safe.
 *
 * More information about token-bucket:
 *   http://en.wikipedia.org/wiki/Token_bucket
 *
 * @code
 *   qtokenbucket_t bucket;
 *   qtokenbucket_init(&bucket, 500, 1000, 1000);
 *   while (1) {
 *     if (qtokenbucket_consume(&bucket, 1) == false) {
 *       // Bucket is empty. Let's wait
 *       usleep(qtokenbucket_waittime(&bucket, 1) * 1000);
 *       continue;
 *     }
 *     // Got a token. Let's do something here.
 *     do_something();
 *   }
 * @endcode
 */

#include "extensions/qtokenbucket.h"

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <sys/time.h>
#include "utilities/qtime.h"
#include "qinternal.h"

#ifndef _DOXYGEN_SKIP
/* internal functions */
static void refill_tokens( qtokenbucket_t* bucket );
#endif

/**
 * Initialize the token bucket.
 *
 * @param init_tokens
 *      the initial number of tokens.
 * @param max_tokens
 *      maximum number of tokens in the bucket.
 * @param tokens_per_sec
 *      number of tokens to fill per a second.
 */
void qtokenbucket_init( qtokenbucket_t* bucket,
   int init_tokens,
   int max_tokens,
   int tokens_per_sec )
{
	memset( bucket, 0, sizeof( qtokenbucket_t ) );
	bucket->tokens         = init_tokens;
	bucket->max_tokens     = max_tokens;
	bucket->tokens_per_sec = tokens_per_sec;
	bucket->last_fill      = qtime_current_milli( );
}

/**
 * Consume tokens from the bucket.
 *
 * @param bucket tockenbucket object.
 * @param tokens number of tokens to request.
 *
 * @return return true if there are enough tokens, otherwise false.
 */
bool qtokenbucket_consume( qtokenbucket_t* bucket, int tokens )
{
	refill_tokens( bucket );
	if( bucket->tokens < tokens )
	{
		return false;
	}
	bucket->tokens -= tokens;
	return true;
}

/**
 * Get the estimate time until given number of token is ready.
 *
 * @param tokens number of tokens
 *
 * @return estimated milliseconds
 */
long qtokenbucket_waittime( qtokenbucket_t* bucket, int tokens )
{
	refill_tokens( bucket );
	if( bucket->tokens >= tokens )
	{
		return 0;
	}
	int tokens_needed     = tokens - (int)bucket->tokens;
	double estimate_milli = ( 1000 * tokens_needed ) / bucket->tokens_per_sec;
	estimate_milli +=
	   ( ( 1000 * tokens_needed ) % bucket->tokens_per_sec ) ? 1 : 0;
	return estimate_milli;
}

#ifndef _DOXYGEN_SKIP
/**
 * Refill tokens.
 */
static void refill_tokens( qtokenbucket_t* bucket )
{
	long now = qtime_current_milli( );
	if( bucket->tokens < bucket->max_tokens )
	{
		double new_tokens =
		   ( now - bucket->last_fill ) * 0.001 * bucket->tokens_per_sec;
		bucket->tokens = ( ( bucket->tokens + new_tokens ) < bucket->max_tokens )
		   ? ( bucket->tokens + new_tokens )
		   : bucket->max_tokens;
	}
	bucket->last_fill = now;
}
#endif // _DOXYGEN_SKIP
