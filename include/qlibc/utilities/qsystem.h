/****************************************************************************\
 *                                  qlibc™                                  *
 *                                                                          *
 *               Copyright © 2010-2015 Seungyoung “Steve” Kim               *
 *                      Copyright © 2020 ARQADIUM, LLC                      *
 *                       Licenced under BSD-2-Clause.                       *
\****************************************************************************/

/**
 * qsystem header file.
 *
 * @file qsystem.h
 */

#ifndef QSYSTEM_H
#define QSYSTEM_H

#ifdef __cplusplus
extern "C" {
#endif

extern const char* qgetenv( const char* envname, const char* nullstr );
extern char* qsyscmd( const char* cmd );

#ifdef __cplusplus
}
#endif

#endif /* QSYSTEM_H */
