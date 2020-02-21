/****************************************************************************\
 *                                  qlibc™                                  *
 *                                                                          *
 *               Copyright © 2010-2015 Seungyoung “Steve” Kim               *
 *                      Copyright © 2020 ARQADIUM, LLC                      *
 *                       Licenced under BSD-2-Clause.                       *
\****************************************************************************/

/**
 * qstring header file.
 *
 * @file qstring.h
 */

#ifndef QSTRING_H
#define QSTRING_H

#include <stdlib.h>
#include <stdbool.h>
#include "../containers/qlist.h"

#ifdef __cplusplus
extern "C" {
#endif

extern char* qstrtrim( char* str );
extern char* qstrtrim_head( char* str );
extern char* qstrtrim_tail( char* str );
extern char* qstrunchar( char* str, char head, char tail );
extern char* qstrreplace(
   const char* mode, char* srcstr, const char* tokstr, const char* word );
extern char* qstrcpy( char* dst, size_t size, const char* src );
extern char* qstrncpy(
   char* dst, size_t size, const char* src, size_t nbytes );
extern char* qstrdupf( const char* format, ... );
extern char* qstrdup_between(
   const char* str, const char* start, const char* end );
extern void* qmemdup( const void* data, size_t size );
extern char* qstrcatf( char* str, const char* format, ... );
extern char* qstrgets( char* buf, size_t size, char** offset );
extern char* qstrrev( char* str );
extern char* qstrupper( char* str );
extern char* qstrlower( char* str );
extern char* qstrtok(
   char* str, const char* delimiters, char* retstop, int* offset );
extern qlist_t* qstrtokenizer( const char* str, const char* delimiters );
extern char* qstrunique( const char* seed );
extern char* qstr_comma_number( int number );
extern bool qstrtest( int ( *testfunc )( int ), const char* str );
extern bool qstr_is_email( const char* email );
extern bool qstr_is_ip4addr( const char* str );
extern char* qstr_conv_encoding(
   const char* fromstr, const char* fromcode, const char* tocode, float mag );

#ifdef __cplusplus
}
#endif

#endif /* QSTRING_H */
