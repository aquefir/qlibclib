/****************************************************************************\
 *                                  qlibc™                                  *
 *                                                                          *
 *               Copyright © 2010-2015 Seungyoung “Steve” Kim               *
 *                      Copyright © 2020 ARQADIUM, LLC                      *
 *                       Licenced under BSD-2-Clause.                       *
\****************************************************************************/

/**
 * @file qshm.c Shared-memory APIs.
 *
 * @note
 * @code
 *   [your header file]
 *   struct SharedData {
 *     (... structrue definitions ...)
 *   }
 *
 *   [shared memory creater]
 *   // create shared memory
 *   int shmid = qshm_init("/some/file/for/generating/unique/key", 's',
 * sizeof(struct SharedData), true); if(shmid < 0) { printf("ERROR: Can't
 * initialize shared memory.\n"); return -1;
 *   }
 *
 *   // get shared memory pointer
 *   struct SharedData *sdata = (SharedData *)qshm_get(shmid);
 *   if(sdata == NULL) {
 *     printf("ERROR: Can't get shared memory.\n");
 *     return -1;
 *   }
 *
 *   [shared memory user]
 *   // get shared memory id
 *   int shmid = qshm_getid("/some/file/for/generating/unique/key", 's');
 *   if(shmid < 0) {
 *     printf("ERROR: Can't get shared memory id.\n");
 *     return -1;
 *   }
 *
 *   // get shared memory pointer
 *   struct SharedData *sdata = (SharedData *)qshm_get(shmid);
 *   if(sdata == NULL) {
 *     printf("ERROR: Can't get shared memory.\n");
 *     return -1;
 *   }
 * @endcode
 */

#ifndef DISABLE_IPC

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/shm.h>
#include "qinternal.h"
#include "ipc/qshm.h"

/**
 * Initialize shared-memory
 *
 * @param keyfile   seed for generating unique IPC key
 * @param keyid     seed for generating unique IPC key
 * @param size      size of shared memory
 * @param recreate  set to true to re-create shared-memory if already exists
 *
 * @return non-negative shared memory identifier if successful, otherwise
 * returns -1
 */
int qshm_init( const char* keyfile, int keyid, size_t size, bool recreate )
{
	key_t semkey;
	int shmid;

	/* generate unique key using ftok() */
	if( keyfile != NULL )
	{
		semkey = ftok( keyfile, keyid );
		if( semkey == -1 )
			return -1;
	}
	else
	{
		semkey = IPC_PRIVATE;
	}

	/* create shared memory */
	if( ( shmid = shmget( semkey, size, IPC_CREAT | IPC_EXCL | 0666 ) ) == -1 )
	{
		if( recreate == false )
			return -1;

		/* destroy & re-create */
		if( ( shmid = qshm_getid( keyfile, keyid ) ) >= 0 )
			qshm_free( shmid );
		if( ( shmid = shmget( semkey, size, IPC_CREAT | IPC_EXCL | 0666 ) ) ==
		   -1 )
			return -1;
	}

	return shmid;
}

/**
 * Get shared memory identifier by keyfile and keyid for existing shared memory
 *
 * @param keyfile   seed for generating unique IPC key
 * @param keyid     seed for generating unique IPC key
 *
 * @return non-negative shared memory identifier if successful, otherwise
 * returns -1
 */
int qshm_getid( const char* keyfile, int keyid )
{
	int shmid;

	/* generate unique key using ftok() */
	key_t semkey = ftok( keyfile, keyid );
	if( semkey == -1 )
		return -1;

	/* get current shared memory id */
	if( ( shmid = shmget( semkey, 0, 0 ) ) == -1 )
		return -1;

	return shmid;
}

/**
 * Get a pointer of shared memory
 *
 * @param shmid     shared memory identifier
 *
 * @return a pointer of shared memory
 */
void* qshm_get( int shmid )
{
	void* pShm;

	if( shmid < 0 )
		return NULL;
	pShm = shmat( shmid, 0, 0 );
	if( pShm == (void*)-1 )
		return NULL;
	return pShm;
}

/**
 * De-allocate shared memory
 *
 * @param shmid     shared memory identifier
 *
 * @return true if successful, otherwise returns false
 */
bool qshm_free( int shmid )
{
	if( shmid < 0 )
		return false;
	if( shmctl( shmid, IPC_RMID, 0 ) != 0 )
		return false;
	return true;
}

#endif /* DISABLE_IPC */
