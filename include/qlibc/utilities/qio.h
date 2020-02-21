/****************************************************************************\
 *                                  qlibc™                                  *
 *                                                                          *
 *               Copyright © 2010-2015 Seungyoung “Steve” Kim               *
 *                      Copyright © 2020 ARQADIUM, LLC                      *
 *                       Licenced under BSD-2-Clause.                       *
\****************************************************************************/

/**
 * qio header file.
 *
 * @file qio.h
 */

#ifndef QIO_H
#define QIO_H

#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

extern int qio_wait_readable( int fd, int timeoutms );
extern int qio_wait_writable( int fd, int timeoutms );
extern ssize_t qio_read( int fd, void* buf, size_t nbytes, int timeoutms );
extern ssize_t qio_write(
   int fd, const void* data, size_t nbytes, int timeoutms );
extern off_t qio_send( int outfd, int infd, off_t nbytes, int timeoutms );
extern ssize_t qio_gets( int fd, char* buf, size_t bufsize, int timeoutms );
extern ssize_t qio_puts( int fd, const char* str, int timeoutms );
extern ssize_t qio_printf( int fd, int timeoutms, const char* format, ... );

#ifdef __cplusplus
}
#endif

#endif /* QIO_H */
