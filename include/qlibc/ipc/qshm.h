/****************************************************************************\
 *                                  qlibc™                                  *
 *                                                                          *
 *               Copyright © 2010-2015 Seungyoung “Steve” Kim               *
 *                      Copyright © 2020 ARQADIUM, LLC                      *
 *                       Licenced under BSD-2-Clause.                       *
\****************************************************************************/

/**
 * qshm header file.
 *
 * @file qshm.h
 */

#ifndef QSHM_H
#define QSHM_H

#ifdef __cplusplus
extern "C" {
#endif

extern int qshm_init(
   const char* keyfile, int keyid, size_t size, bool recreate );
extern int qshm_getid( const char* keyfile, int keyid );
extern void* qshm_get( int shmid );
extern bool qshm_free( int shmid );

#ifdef __cplusplus
}
#endif

#endif /* QSHM_H */
