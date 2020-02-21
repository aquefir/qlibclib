/****************************************************************************\
 *                                  qlibc™                                  *
 *                                                                          *
 *               Copyright © 2010-2015 Seungyoung “Steve” Kim               *
 *                      Copyright © 2020 ARQADIUM, LLC                      *
 *                       Licenced under BSD-2-Clause.                       *
\****************************************************************************/

/**
 * Hash Table container.
 *
 * @file qhashtbl.h
 */

#ifndef QHASHTBL_H
#define QHASHTBL_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

/* types */
typedef struct qhashtbl_s qhashtbl_t;
typedef struct qhashtbl_obj_s qhashtbl_obj_t;

enum
{
	QHASHTBL_THREADSAFE = ( 0x01 ) /*!< make it thread-safe */
};

/* member functions
 *
 * All the member functions can be accessed in both ways:
 *  - tbl->put(tbl, ...);      // easier to switch the container type to other
 * kinds.
 *  - qhashtbl_put(tbl, ...);  // where avoiding pointer overhead is preferred.
 */
extern qhashtbl_t* qhashtbl(
   size_t range, int options ); /*!< qhashtbl constructor */

extern bool qhashtbl_put(
   qhashtbl_t* tbl, const char* name, const void* data, size_t size );
extern bool qhashtbl_putstr(
   qhashtbl_t* tbl, const char* name, const char* str );
extern bool qhashtbl_putstrf(
   qhashtbl_t* tbl, const char* name, const char* format, ... );
extern bool qhashtbl_putint( qhashtbl_t* tbl, const char* name, int64_t num );

extern void* qhashtbl_get(
   qhashtbl_t* tbl, const char* name, size_t* size, bool newmem );
extern char* qhashtbl_getstr( qhashtbl_t* tbl, const char* name, bool newmem );
extern int64_t qhashtbl_getint( qhashtbl_t* tbl, const char* name );

extern bool qhashtbl_remove( qhashtbl_t* tbl, const char* name );

extern bool qhashtbl_getnext(
   qhashtbl_t* tbl, qhashtbl_obj_t* obj, bool newmem );

extern size_t qhashtbl_size( qhashtbl_t* tbl );
extern void qhashtbl_clear( qhashtbl_t* tbl );
extern bool qhashtbl_debug( qhashtbl_t* tbl, FILE* out );

extern void qhashtbl_lock( qhashtbl_t* tbl );
extern void qhashtbl_unlock( qhashtbl_t* tbl );

extern void qhashtbl_free( qhashtbl_t* tbl );

/**
 * qhashtbl container object structure
 */
struct qhashtbl_s
{
	/* encapsulated member functions */
	bool ( *put )(
	   qhashtbl_t* tbl, const char* name, const void* data, size_t size );
	bool ( *putstr )( qhashtbl_t* tbl, const char* name, const char* str );
	bool ( *putstrf )(
	   qhashtbl_t* tbl, const char* name, const char* format, ... );
	bool ( *putint )( qhashtbl_t* tbl, const char* name, const int64_t num );

	void* ( *get )(
	   qhashtbl_t* tbl, const char* name, size_t* size, bool newmem );
	char* ( *getstr )( qhashtbl_t* tbl, const char* name, bool newmem );
	int64_t ( *getint )( qhashtbl_t* tbl, const char* name );

	bool ( *remove )( qhashtbl_t* tbl, const char* name );

	bool ( *getnext )( qhashtbl_t* tbl, qhashtbl_obj_t* obj, bool newmem );

	size_t ( *size )( qhashtbl_t* tbl );
	void ( *clear )( qhashtbl_t* tbl );
	bool ( *debug )( qhashtbl_t* tbl, FILE* out );

	void ( *lock )( qhashtbl_t* tbl );
	void ( *unlock )( qhashtbl_t* tbl );

	void ( *free )( qhashtbl_t* tbl );

	/* private variables - do not access directly */
	void* qmutex; /*!< initialized when QHASHTBL_THREADSAFE is given */
	size_t num; /*!< number of objects in this table */
	size_t range; /*!< hash range, vertical number of slots */
	qhashtbl_obj_t** slots; /*!< slot pointer container */
};

/**
 * qhashtbl object data structure
 */
struct qhashtbl_obj_s
{
	uint32_t hash; /*!< 32bit-hash value of object name */
	char* name; /*!< object name */
	void* data; /*!< data */
	size_t size; /*!< data size */

	qhashtbl_obj_t* next; /*!< for chaining next collision object */
};

#ifdef __cplusplus
}
#endif

#endif /* QHASHTBL_H */
