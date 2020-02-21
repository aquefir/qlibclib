/****************************************************************************\
 *                                  qlibc™                                  *
 *                                                                          *
 *               Copyright © 2010-2015 Seungyoung “Steve” Kim               *
 *                      Copyright © 2015 Zhenjiang Xie                      *
 *                      Copyright © 2020 ARQADIUM, LLC                      *
 *                       Licenced under BSD-2-Clause.                       *
\****************************************************************************/

/**
 * Vector container.
 *
 * @file qvector.h
 */

#ifndef QVECTOR_H
#define QVECTOR_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* types */
typedef struct qvector_s qvector_t;
typedef struct qvector_obj_s qvector_obj_t;

/* public functions */
enum
{
	QVECTOR_THREADSAFE    = ( 0x01 ), /*!< make it thread-safe */
	QVECTOR_RESIZE_DOUBLE = ( 0x02 ), /*!< double the size when vector is full*/
	QVECTOR_RESIZE_LINEAR =
	   ( 0x04 ), /*!< add the size with initial num when vector is full*/
	QVECTOR_RESIZE_EXACT = ( 0x08 ) /*!< add up as much as needed*/
};

extern qvector_t* qvector( size_t max, size_t objsize, int options );

extern bool qvector_addfirst( qvector_t* vector, const void* data );
extern bool qvector_addlast( qvector_t* vector, const void* data );
extern bool qvector_addat( qvector_t* vector, int index, const void* data );

extern void* qvector_getfirst( qvector_t* vector, bool newmem );
extern void* qvector_getlast( qvector_t* vector, bool newmem );
extern void* qvector_getat( qvector_t* vector, int index, bool newmem );

extern bool qvector_setfirst( qvector_t* vector, const void* data );
extern bool qvector_setlast( qvector_t* vector, const void* data );
extern bool qvector_setat( qvector_t* vector, int index, const void* data );

extern void* qvector_popfirst( qvector_t* vector );
extern void* qvector_poplast( qvector_t* vector );
extern void* qvector_popat( qvector_t* vector, int index );

extern bool qvector_removefirst( qvector_t* vector );
extern bool qvector_removelast( qvector_t* vector );
extern bool qvector_removeat( qvector_t* vector, int index );

extern size_t qvector_size( qvector_t* vector );
extern bool qvector_resize( qvector_t* vector, size_t newmax );

extern void* qvector_toarray( qvector_t* vector, size_t* size );

extern void qvector_lock( qvector_t* vector );
extern void qvector_unlock( qvector_t* vector );

extern void qvector_clear( qvector_t* vector );
extern bool qvector_debug( qvector_t* vector, FILE* out );
extern void qvector_free( qvector_t* vector );

extern void qvector_reverse( qvector_t* vector );
extern bool qvector_getnext(
   qvector_t* vector, qvector_obj_t* obj, bool newmem );

/**
 * qvector container object
 */
struct qvector_s
{
	/* capsulated member functions */

	bool ( *addfirst )( qvector_t* vector, const void* object );
	bool ( *addlast )( qvector_t* vector, const void* data );
	bool ( *addat )( qvector_t* vector, int index, const void* data );

	void* ( *getfirst )( qvector_t* vector, bool newmem );
	void* ( *getlast )( qvector_t* vector, bool newmem );
	void* ( *getat )( qvector_t* vector, int index, bool newmem );

	bool ( *setfirst )( qvector_t* vector, const void* data );
	bool ( *setlast )( qvector_t* vector, const void* data );
	bool ( *setat )( qvector_t* vector, int index, const void* data );

	void* ( *popfirst )( qvector_t* vector );
	void* ( *poplast )( qvector_t* vector );
	void* ( *popat )( qvector_t* vector, int index );

	bool ( *removefirst )( qvector_t* vector );
	bool ( *removelast )( qvector_t* vector );
	bool ( *removeat )( qvector_t* vector, int index );

	size_t ( *size )( qvector_t* vector );
	bool ( *resize )( qvector_t* vector, size_t newmax );

	void* ( *toarray )( qvector_t* vector, size_t* size );

	void ( *lock )( qvector_t* vector );
	void ( *unlock )( qvector_t* vector );

	void ( *clear )( qvector_t* vector );
	bool ( *debug )( qvector_t* vector, FILE* out );
	void ( *free )( qvector_t* vector );

	void ( *reverse )( qvector_t* vector );
	bool ( *getnext )( qvector_t* vector, qvector_obj_t* obj, bool newmem );

	/* private variables - do not access directly */
	void* qmutex;
	void* data;
	size_t num; /*number of elements*/
	size_t objsize; /*the size of each element*/
	size_t max; /*allocated number of elements*/
	int options;
	size_t initnum;
};

struct qvector_obj_s
{
	void* data;
	int index;
};

#ifdef __cplusplus
}
#endif

#endif /* QVECTOR_H */
