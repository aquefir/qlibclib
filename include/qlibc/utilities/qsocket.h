/****************************************************************************\
 *                                  qlibc™                                  *
 *                                                                          *
 *               Copyright © 2010-2015 Seungyoung “Steve” Kim               *
 *                      Copyright © 2020 ARQADIUM, LLC                      *
 *                       Licenced under BSD-2-Clause.                       *
\****************************************************************************/

/**
 * qsocket header file.
 *
 * @file qsocket.h
 */

#ifndef QSOCKET_H
#define QSOCKET_H

#include <stdlib.h>
#include <stdbool.h>
#include <netinet/in.h>

#ifdef __cplusplus
extern "C" {
#endif

extern int qsocket_open( const char* hostname, int port, int timeoutms );
extern bool qsocket_close( int sockfd, int timeoutms );
extern bool qsocket_get_addr(
   struct sockaddr_in* addr, const char* hostname, int port );
extern char* qsocket_get_localaddr( char* buf, size_t bufsize );

#ifdef __cplusplus
}
#endif

#endif /* QSOCKET_H */
