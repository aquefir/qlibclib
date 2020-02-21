/****************************************************************************\
 *                                  qlibc™                                  *
 *                                                                          *
 *               Copyright © 2010-2015 Seungyoung “Steve” Kim               *
 *                      Copyright © 2020 ARQADIUM, LLC                      *
 *                       Licenced under BSD-2-Clause.                       *
\****************************************************************************/

/**
 * @file qsystem.c System APIs.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "qinternal.h"
#include "utilities/qfile.h"
#include "utilities/qsystem.h"

/**
 * Get system environment variable
 *
 * @param envname   environment name
 * @param defstr    if not found, return this string
 *
 * @return a pointer of environment variable
 */
const char* qgetenv( const char* envname, const char* defstr )
{
	const char* envstr = getenv( envname );
	return ( envstr ) ? envstr : defstr;
}

/**
 * Get the result string of external command execution
 *
 * @param cmd       external command
 *
 * @return malloced string pointer which contains result if successful,
 *         otherwise returns NULL
 *
 * @note
 *  If the command does not report result but it is executed successfully,
 *  this will returns empty string(not null)
 */
char* qsyscmd( const char* cmd )
{
	FILE* fp = popen( cmd, "r" );
	if( fp == NULL )
		return NULL;
	char* str = qfile_read( fp, NULL );
	pclose( fp );

	if( str == NULL )
		str = strdup( "" );
	return str;
}
