/****************************************************************************\
 *                                  qlibc™                                  *
 *                                                                          *
 *               Copyright © 2010-2015 Seungyoung “Steve” Kim               *
 *                      Copyright © 2020 ARQADIUM, LLC                      *
 *                       Licenced under BSD-2-Clause.                       *
\****************************************************************************/

/**
 * Queue container.
 *
 * @file qqueue.h
 */

#ifndef QQUEUE_H
#define QQUEUE_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "qlist.h"

#ifdef __cplusplus
extern "C" {
#endif

/* types */
typedef struct qqueue_s qqueue_t;

enum
{
	QQUEUE_THREADSAFE = ( QLIST_THREADSAFE ) /*!< make it thread-safe */
};

/* member functions
 *
 * All the member functions can be accessed in both ways:
 *  - tbl->push(tbl, ...);    // easier to switch the container type to other
 * kinds.
 *  - qqueue_push(tbl, ...);  // where avoiding pointer overhead is preferred.
 */
extern qqueue_t* qqueue( int options );
extern size_t qqueue_setsize( qqueue_t* queue, size_t max );

extern bool qqueue_push( qqueue_t* queue, const void* data, size_t size );
extern bool qqueue_pushstr( qqueue_t* queue, const char* str );
extern bool qqueue_pushint( qqueue_t* queue, int64_t num );

extern void* qqueue_pop( qqueue_t* queue, size_t* size );
extern char* qqueue_popstr( qqueue_t* queue );
extern int64_t qqueue_popint( qqueue_t* queue );
extern void* qqueue_popat( qqueue_t* queue, int index, size_t* size );

extern void* qqueue_get( qqueue_t* queue, size_t* size, bool newmem );
extern char* qqueue_getstr( qqueue_t* queue );
extern int64_t qqueue_getint( qqueue_t* queue );
extern void* qqueue_getat(
   qqueue_t* queue, int index, size_t* size, bool newmem );

extern size_t qqueue_size( qqueue_t* queue );
extern void qqueue_clear( qqueue_t* queue );
extern bool qqueue_debug( qqueue_t* queue, FILE* out );
extern void qqueue_free( qqueue_t* queue );

/**
 * qqueue container object structure
 */
struct qqueue_s
{
	/* encapsulated member functions */
	size_t ( *setsize )( qqueue_t* stack, size_t max );

	bool ( *push )( qqueue_t* stack, const void* data, size_t size );
	bool ( *pushstr )( qqueue_t* stack, const char* str );
	bool ( *pushint )( qqueue_t* stack, int64_t num );

	void* ( *pop )( qqueue_t* stack, size_t* size );
	char* ( *popstr )( qqueue_t* stack );
	int64_t ( *popint )( qqueue_t* stack );
	void* ( *popat )( qqueue_t* stack, int index, size_t* size );

	void* ( *get )( qqueue_t* stack, size_t* size, bool newmem );
	char* ( *getstr )( qqueue_t* stack );
	int64_t ( *getint )( qqueue_t* stack );
	void* ( *getat )( qqueue_t* stack, int index, size_t* size, bool newmem );

	size_t ( *size )( qqueue_t* stack );
	void ( *clear )( qqueue_t* stack );
	bool ( *debug )( qqueue_t* stack, FILE* out );
	void ( *free )( qqueue_t* stack );

	/* private variables - do not access directly */
	qlist_t* list; /*!< data container */
};

#ifdef __cplusplus
}
#endif

#endif /* QQUEUE_H */
