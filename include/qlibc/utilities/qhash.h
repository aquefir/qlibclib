/****************************************************************************\
 *                                  qlibc™                                  *
 *                                                                          *
 *               Copyright © 2010-2015 Seungyoung “Steve” Kim               *
 *                      Copyright © 2020 ARQADIUM, LLC                      *
 *                       Licenced under BSD-2-Clause.                       *
\****************************************************************************/

/**
 * qhash header file.
 *
 * @file qhash.h
 */

#ifndef QHASH_H
#define QHASH_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

extern bool qhashmd5( const void* data, size_t nbytes, void* retbuf );
extern bool qhashmd5_file(
   const char* filepath, off_t offset, ssize_t nbytes, void* retbuf );

extern uint32_t qhashfnv1_32( const void* data, size_t nbytes );
extern uint64_t qhashfnv1_64( const void* data, size_t nbytes );

extern uint32_t qhashmurmur3_32( const void* data, size_t nbytes );
extern bool qhashmurmur3_128( const void* data, size_t nbytes, void* retbuf );

#ifdef __cplusplus
}
#endif

#endif /* QHASH_H */
