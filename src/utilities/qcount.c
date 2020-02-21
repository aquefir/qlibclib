/****************************************************************************\
 *                                  qlibc™                                  *
 *                                                                          *
 *               Copyright © 2010-2015 Seungyoung “Steve” Kim               *
 *                      Copyright © 2020 ARQADIUM, LLC                      *
 *                       Licenced under BSD-2-Clause.                       *
\****************************************************************************/

/**
 * @file qcount.c Counter file handling APIs.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "qinternal.h"
#include "utilities/qstring.h"
#include "utilities/qcount.h"

/**
 * Read counter(integer) from file with advisory file locking.
 *
 * @param filepath  file path
 *
 * @return counter value readed from file. in case of failure, returns 0.
 *
 * @code
 *   qcount_save("number.dat", 75);
 *   int count = qcount_read("number.dat");
 * @endcode
 *
 * @code
 *   ---- number.dat ----
 *   75
 *   --------------------
 * @endcode
 */
int64_t qcount_read( const char* filepath )
{
	int fd = open( filepath, O_RDONLY, 0 );
	if( fd < 0 )
		return 0;

	char buf[20 + 1];
	ssize_t readed = read( fd, buf, ( sizeof( buf ) - 1 ) );
	close( fd );

	int64_t num = 0;
	if( readed > 0 )
	{
		buf[readed] = '\0';
		num         = atoll( buf );
	}

	return num;
}

/**
 * Save counter(integer) to file with advisory file locking.
 *
 * @param filepath  file path
 * @param number    counter integer value
 *
 * @return true if successful, otherwise returns false.
 *
 * @code
 *   qcount_save("number.dat", 75);
 * @endcode
 */
bool qcount_save( const char* filepath, int64_t number )
{
	int fd = open( filepath,
	   O_CREAT | O_WRONLY | O_TRUNC,
	   ( S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH ) );
	if( fd < 0 )
		return false;

	char* str       = qstrdupf( "%" PRId64, number );
	ssize_t updated = write( fd, str, strlen( str ) );
	close( fd );

	if( updated > 0 )
		return true;
	return false;
}

/**
 * Increases(or decrease) the counter value as much as specified number
 * with advisory file locking.
 *
 * @param filepath  file path
 * @param number    how much increase or decrease
 *
 * @return updated counter value. in case of failure, returns 0.
 *
 * @code
 *   int count;
 *   count = qcount_update("number.dat", -3);
 * @endcode
 */
int64_t qcount_update( const char* filepath, int64_t number )
{
	int64_t counter = qcount_read( filepath );
	counter += number;
	if( qcount_save( filepath, counter ) == true )
	{
		return counter;
	}
	return 0;
}
