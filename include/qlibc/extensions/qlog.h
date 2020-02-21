/****************************************************************************\
 *                                  qlibc™                                  *
 *                                                                          *
 *               Copyright © 2010-2015 Seungyoung “Steve” Kim               *
 *                      Copyright © 2020 ARQADIUM, LLC                      *
 *                       Licenced under BSD-2-Clause.                       *
\****************************************************************************/

/**
 * Rotating file logger.
 *
 * This is a qLibc extension implementing application level auto-rotating file
 * logger.
 *
 * @file qlog.h
 */

#ifndef QLOG_H
#define QLOG_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <limits.h>

#ifdef __cplusplus
extern "C" {
#endif

/* types */
typedef struct qlog_s qlog_t;

/* constants */
#define QLOG_OPT_THREADSAFE ( 0x01 )
#define QLOG_OPT_FLUSH ( 0x01 << 1 )

/* public functions */
extern qlog_t* qlog(
   const char* filepathfmt, mode_t mode, int rotateinterval, int options );

/**
 * qlog structure object structure
 */
struct qlog_s
{
	/* encapsulated member functions */
	bool ( *write )( qlog_t* log, const char* str );
	bool ( *writef )( qlog_t* log, const char* format, ... );
	bool ( *duplicate )( qlog_t* log, FILE* outfp, bool flush );
	bool ( *flush )( qlog_t* log );
	void ( *free )( qlog_t* log );

	/* private variables - do not access directly */
	void* qmutex; /*!< activated if compiled with --enable-threadsafe */

	char filepathfmt[PATH_MAX]; /*!< file file naming format like
	                                 /somepath/daily-%Y%m%d.log */
	char filepath[PATH_MAX]; /*!< generated system path of log file */
	FILE* fp; /*!< file pointer of logpath */
	mode_t mode; /*!< file mode */
	int rotateinterval; /*!< log file will be rotate in this interval seconds */
	int nextrotate; /*!< next rotate universal time, seconds */
	bool logflush; /*!< flag for immediate flushing */

	FILE* outfp; /*!< stream pointer for duplication */
	bool outflush; /*!< flag for immediate flushing for duplicated stream */
};

#ifdef __cplusplus
}
#endif

#endif /* QLOG_H */
