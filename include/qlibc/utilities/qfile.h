/****************************************************************************\
 *                                  qlibc™                                  *
 *                                                                          *
 *               Copyright © 2010-2015 Seungyoung “Steve” Kim               *
 *                      Copyright © 2020 ARQADIUM, LLC                      *
 *                       Licenced under BSD-2-Clause.                       *
\****************************************************************************/

/**
 * qfile header file.
 *
 * @file qfile.h
 */

#ifndef QFILE_H
#define QFILE_H

#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

extern bool qfile_lock( int fd );
extern bool qfile_unlock( int fd );
extern bool qfile_exist( const char* filepath );
extern void* qfile_load( const char* filepath, size_t* nbytes );
extern void* qfile_read( FILE* fp, size_t* nbytes );
extern ssize_t qfile_save(
   const char* filepath, const void* buf, size_t size, bool append );
extern bool qfile_mkdir( const char* dirpath, mode_t mode, bool recursive );

extern char* qfile_get_name( const char* filepath );
extern char* qfile_get_dir( const char* filepath );
extern char* qfile_get_ext( const char* filepath );
extern off_t qfile_get_size( const char* filepath );

extern bool qfile_check_path( const char* path );
extern char* qfile_correct_path( char* path );
extern char* qfile_abspath( char* buf, size_t bufsize, const char* path );

#ifdef __cplusplus
}
#endif

#endif /* QFILE_H */
