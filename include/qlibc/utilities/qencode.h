/****************************************************************************\
 *                                  qlibc™                                  *
 *                                                                          *
 *               Copyright © 2010-2015 Seungyoung “Steve” Kim               *
 *                      Copyright © 2020 ARQADIUM, LLC                      *
 *                       Licenced under BSD-2-Clause.                       *
\****************************************************************************/

/**
 * qencode header file.
 *
 * @file qencode.h
 */

#ifndef QENCODE_H
#define QENCODE_H

#include <stdlib.h>
#include <stdbool.h>
#include "../containers/qlisttbl.h"

#ifdef __cplusplus
extern "C" {
#endif

extern qlisttbl_t* qparse_queries( qlisttbl_t* tbl,
   const char* query,
   char equalchar,
   char sepchar,
   int* count );
extern char* qurl_encode( const void* bin, size_t size );
extern size_t qurl_decode( char* str );
extern char* qbase64_encode( const void* bin, size_t size );
extern size_t qbase64_decode( char* str );
extern char* qhex_encode( const void* bin, size_t size );
extern size_t qhex_decode( char* str );

#ifdef __cplusplus
}
#endif

#endif /* QENCODE_H */
