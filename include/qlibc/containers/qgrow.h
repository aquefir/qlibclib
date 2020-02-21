/****************************************************************************\
 *                                  qlibc™                                  *
 *                                                                          *
 *               Copyright © 2010-2015 Seungyoung “Steve” Kim               *
 *                      Copyright © 2020 ARQADIUM, LLC                      *
 *                       Licenced under BSD-2-Clause.                       *
\****************************************************************************/

/**
 * Grow container that handles growable objects.
 *
 * @file qgrow.h
 */

#ifndef QGROW_H
#define QGROW_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "qlist.h"

#ifdef __cplusplus
extern "C" {
#endif

/* types */
typedef struct qgrow_s qgrow_t;

/* public functions */
enum
{
	QGROW_THREADSAFE = ( QLIST_THREADSAFE ) /*!< make it thread-safe */
};

extern qgrow_t* qgrow( int options );

extern bool qgrow_add( qgrow_t* grow, const void* object, size_t size );
extern bool qgrow_addstr( qgrow_t* grow, const char* str );
extern bool qgrow_addstrf( qgrow_t* grow, const char* format, ... );

extern size_t qgrow_size( qgrow_t* grow );
extern size_t qgrow_datasize( qgrow_t* grow );

extern void* qgrow_toarray( qgrow_t* grow, size_t* size );
extern char* qgrow_tostring( qgrow_t* grow );

extern void qgrow_clear( qgrow_t* grow );
extern bool qgrow_debug( qgrow_t* grow, FILE* out );
extern void qgrow_free( qgrow_t* grow );

/**
 * qgrow container object
 */
struct qgrow_s
{
	/* capsulated member functions */
	bool ( *add )( qgrow_t* grow, const void* data, size_t size );
	bool ( *addstr )( qgrow_t* grow, const char* str );
	bool ( *addstrf )( qgrow_t* grow, const char* format, ... );

	size_t ( *size )( qgrow_t* grow );
	size_t ( *datasize )( qgrow_t* grow );

	void* ( *toarray )( qgrow_t* grow, size_t* size );
	char* ( *tostring )( qgrow_t* grow );

	void ( *clear )( qgrow_t* grow );
	bool ( *debug )( qgrow_t* grow, FILE* out );

	void ( *free )( qgrow_t* grow );

	/* private variables - do not access directly */
	qlist_t* list; /*!< data container */
};

#ifdef __cplusplus
}
#endif

#endif /* QGROW_H */
