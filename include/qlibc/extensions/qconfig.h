/****************************************************************************\
 *                                  qlibc™                                  *
 *                                                                          *
 *               Copyright © 2010-2015 Seungyoung “Steve” Kim               *
 *                      Copyright © 2020 ARQADIUM, LLC                      *
 *                       Licenced under BSD-2-Clause.                       *
\****************************************************************************/

/**
 * INI-style Configuration File Parser.
 *
 * This is a qLibc extension implementing INI-style configuration file parser.
 *
 * @file qconfig.h
 */

#ifndef QCONFIG_H
#define QCONFIG_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "../containers/qlisttbl.h"

#ifdef __cplusplus
extern "C" {
#endif

/* public functions */
extern qlisttbl_t* qconfig_parse_file(
   qlisttbl_t* tbl, const char* filepath, char sepchar );
extern qlisttbl_t* qconfig_parse_str(
   qlisttbl_t* tbl, const char* str, char sepchar );

#ifdef __cplusplus
}
#endif

#endif /* QCONFIG_H */
