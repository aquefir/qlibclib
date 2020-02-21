/****************************************************************************\
 *                                  qlibc™                                  *
 *                                                                          *
 *               Copyright © 2010-2015 Seungyoung “Steve” Kim               *
 *                      Copyright © 2020 ARQADIUM, LLC                      *
 *                       Licenced under BSD-2-Clause.                       *
\****************************************************************************/

/**
 * HTTP client.
 *
 * This is a qLibc extension implementing HTTP client.
 *
 * @file qhttpclient.h
 */

#ifndef QHTTPCLIENT_H
#define QHTTPCLIENT_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* types */
typedef struct qhttpclient_s qhttpclient_t;

/* constants */
#define QHTTPCLIENT_NAME "qLibc"

/* public functions */
extern qhttpclient_t* qhttpclient( const char* hostname, int port );

/**
 * qhttpclient object structure
 */
struct qhttpclient_s
{
	/* encapsulated member functions */
	bool ( *setssl )( qhttpclient_t* client );
	void ( *settimeout )( qhttpclient_t* client, int timeoutms );
	void ( *setkeepalive )( qhttpclient_t* client, bool keepalive );
	void ( *setuseragent )( qhttpclient_t* client, const char* useragent );

	bool ( *open )( qhttpclient_t* client );

	bool ( *head )( qhttpclient_t* client,
	   const char* uri,
	   int* rescode,
	   qlisttbl_t* reqheaders,
	   qlisttbl_t* resheaders );
	bool ( *get )( qhttpclient_t* client,
	   const char* uri,
	   int fd,
	   off_t* savesize,
	   int* rescode,
	   qlisttbl_t* reqheaders,
	   qlisttbl_t* resheaders,
	   bool ( *callback )( void* userdata, off_t recvbytes ),
	   void* userdata );
	bool ( *put )( qhttpclient_t* client,
	   const char* uri,
	   int fd,
	   off_t length,
	   int* retcode,
	   qlisttbl_t* userheaders,
	   qlisttbl_t* resheaders,
	   bool ( *callback )( void* userdata, off_t sentbytes ),
	   void* userdata );
	void* ( *cmd )( qhttpclient_t* client,
	   const char* method,
	   const char* uri,
	   void* data,
	   size_t size,
	   int* rescode,
	   size_t* contentslength,
	   qlisttbl_t* reqheaders,
	   qlisttbl_t* resheaders );

	bool ( *sendrequest )( qhttpclient_t* client,
	   const char* method,
	   const char* uri,
	   qlisttbl_t* reqheaders );
	int ( *readresponse )(
	   qhttpclient_t* client, qlisttbl_t* resheaders, off_t* contentlength );

	ssize_t ( *gets )( qhttpclient_t* client, char* buf, size_t bufsize );
	ssize_t ( *read )( qhttpclient_t* client, void* buf, size_t nbytes );
	ssize_t ( *write )( qhttpclient_t* client, const void* buf, size_t nbytes );
	off_t ( *recvfile )( qhttpclient_t* client, int fd, off_t nbytes );
	off_t ( *sendfile )( qhttpclient_t* client, int fd, off_t nbytes );

	bool ( *close )( qhttpclient_t* client );
	void ( *free )( qhttpclient_t* client );

	/* private variables - do not access directly */
	int socket; /*!< socket descriptor */
	void* ssl; /*!< will be used if SSL has been enabled at compile time */

	struct sockaddr_in addr;
	char* hostname;
	int port;

	int timeoutms; /*< wait timeout milliseconds*/
	bool keepalive; /*< keep-alive flag */
	char* useragent; /*< user-agent name */

	bool connclose; /*< response keep-alive flag for a last request */
};

#ifdef __cplusplus
}
#endif

#endif /* QHTTPCLIENT_H */
