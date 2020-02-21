/****************************************************************************\
 *                                  qlibc™                                  *
 *                                                                          *
 *               Copyright © 2010-2015 Seungyoung “Steve” Kim               *
 *                      Copyright © 2020 ARQADIUM, LLC                      *
 *                       Licenced under BSD-2-Clause.                       *
\****************************************************************************/

/**
 * Generic database interface.
 *
 * This is a qLibc extension implementing generic database interface.
 * For now, it supports only MySQL database.
 *
 * @file qdatabase.h
 */

#ifndef QDATABASE_H
#define QDATABASE_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* database header files should be included before this header file. */
#ifdef _mysql_h
#define Q_ENABLE_MYSQL ( 1 )
#endif /* _mysql_h */

/* types */
typedef struct qdbresult_s qdbresult_t;
typedef struct qdb_s qdb_t;

/* public functions */
extern qdb_t* qdb( const char* dbtype,
   const char* addr,
   int port,
   const char* database,
   const char* username,
   const char* password,
   bool autocommit );

/**
 * qdbresult object structure
 */
struct qdbresult_s
{
	/* encapsulated member functions */
	const char* ( *getstr )( qdbresult_t* result, const char* field );
	const char* ( *get_str_at )( qdbresult_t* result, int idx );
	int ( *getint )( qdbresult_t* result, const char* field );
	int ( *get_int_at )( qdbresult_t* result, int idx );
	bool ( *getnext )( qdbresult_t* result );

	int ( *get_cols )( qdbresult_t* result );
	int ( *get_rows )( qdbresult_t* result );
	int ( *get_row )( qdbresult_t* result );

	void ( *free )( qdbresult_t* result );

#ifdef Q_ENABLE_MYSQL
	/* private variables for mysql database - do not access directly */
	bool fetchtype;
	MYSQL_RES* rs;
	MYSQL_FIELD* fields;
	MYSQL_ROW row;
	int cols;
	int cursor;
#endif
};

/* qdb object structure */
struct qdb_s
{
	/* encapsulated member functions */
	bool ( *open )( qdb_t* db );
	bool ( *close )( qdb_t* db );

	int ( *execute_update )( qdb_t* db, const char* query );
	int ( *execute_updatef )( qdb_t* db, const char* format, ... );

	qdbresult_t* ( *execute_query )( qdb_t* db, const char* query );
	qdbresult_t* ( *execute_queryf )( qdb_t* db, const char* format, ... );

	bool ( *begin_tran )( qdb_t* db );
	bool ( *end_tran )( qdb_t* db, bool commit );
	bool ( *commit )( qdb_t* db );
	bool ( *rollback )( qdb_t* db );

	bool ( *set_fetchtype )( qdb_t* db, bool fromdb );
	bool ( *get_conn_status )( qdb_t* db );
	bool ( *ping )( qdb_t* db );
	const char* ( *get_error )( qdb_t* db, unsigned int* errorno );
	void ( *free )( qdb_t* db );

	/* private variables - do not access directly */
	void* qmutex;

	bool connected; /*!< if opened true, if closed false */

	struct
	{
		char* dbtype;
		char* addr;
		int port;
		char* username;
		char* password;
		char* database;
		bool autocommit;
		bool fetchtype;
	} info; /*!< database connection information */

#ifdef Q_ENABLE_MYSQL
	/* private variables for mysql database - do not access directly */
	MYSQL* mysql;
#endif
};

#ifdef __cplusplus
}
#endif

#endif /* QDATABASE_H */
