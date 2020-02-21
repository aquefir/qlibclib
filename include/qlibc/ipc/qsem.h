/****************************************************************************\
 *                                  qlibc™                                  *
 *                                                                          *
 *               Copyright © 2010-2015 Seungyoung “Steve” Kim               *
 *                      Copyright © 2020 ARQADIUM, LLC                      *
 *                       Licenced under BSD-2-Clause.                       *
\****************************************************************************/

/**
 * qsem header file.
 *
 * @file qsem.h
 */

#ifndef QSEM_H
#define QSEM_H

#ifdef __cplusplus
extern "C" {
#endif

extern int qsem_init(
   const char* keyfile, int keyid, int nsems, bool recreate );
extern int qsem_getid( const char* keyfile, int keyid );
extern bool qsem_enter( int semid, int semno );
extern bool qsem_enter_nowait( int semid, int semno );
extern bool qsem_enter_force(
   int semid, int semno, int maxwaitms, bool* forceflag );
extern bool qsem_leave( int semid, int semno );
extern bool qsem_check( int semid, int semno );
extern bool qsem_free( int semid );

#ifdef __cplusplus
}
#endif

#endif /* QSEM_H */
