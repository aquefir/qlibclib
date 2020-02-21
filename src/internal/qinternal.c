/****************************************************************************\
 *                                  qlibc™                                  *
 *                                                                          *
 *               Copyright © 2010-2015 Seungyoung “Steve” Kim               *
 *                      Copyright © 2020 ARQADIUM, LLC                      *
 *                       Licenced under BSD-2-Clause.                       *
\****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include "qinternal.h"

// Change two hex character to one hex value.
char _q_x2c( char hex_up, char hex_low )
{
	char digit;

	digit =
	   16 * ( hex_up >= 'A' ? ( ( hex_up & 0xdf ) - 'A' ) + 10 : hex_up - '0' );
	digit +=
	   ( hex_low >= 'A' ? ( ( hex_low & 0xdf ) - 'A' ) + 10 : hex_low - '0' );

	return digit;
}

char* _q_makeword( char* str, char stop )
{
	char* word;
	int len, i;

	for( len = 0; ( ( str[len] != stop ) && ( str[len] ) ); len++ )
		;
	word = (char*)malloc( sizeof( char ) * ( len + 1 ) );
	if( word == NULL )
		return NULL;

	for( i = 0; i < len; i++ )
		word[i] = str[i];
	word[i] = '\0';

	if( str[len] )
		len++;
	for( i = len; str[i]; i++ )
		str[i - len] = str[i];
	str[i - len] = '\0';

	return word;
}

void _q_textout( FILE* fp, void* data, size_t size, size_t max )
{
	size_t i;
	for( i = 0; i < size && i < max; i++ )
	{
		int c = ( (char*)data )[i];
		if( isprint( c ) == 0 )
			c = '?';
		fputc( c, fp );
	}

	if( size > max )
		fputs( "...", fp );
}
