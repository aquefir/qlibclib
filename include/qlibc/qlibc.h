/****************************************************************************\
 *                                  qlibc™                                  *
 *                                                                          *
 *               Copyright © 2010-2015 Seungyoung “Steve” Kim               *
 *                      Copyright © 2020 ARQADIUM, LLC                      *
 *                       Licenced under BSD-2-Clause.                       *
\****************************************************************************/

/**
 * qlibc header file.
 *
 * @file qlibc.h
 */

#ifndef QLIBC_H
#define QLIBC_H

/* containers */
#include "containers/qtreetbl.h"
#include "containers/qhashtbl.h"
#include "containers/qhasharr.h"
#include "containers/qlisttbl.h"
#include "containers/qlist.h"
#include "containers/qvector.h"
#include "containers/qqueue.h"
#include "containers/qstack.h"
#include "containers/qgrow.h"

/* utilities */
#include "utilities/qcount.h"
#include "utilities/qencode.h"
#include "utilities/qfile.h"
#include "utilities/qhash.h"
#include "utilities/qio.h"
#include "utilities/qsocket.h"
#include "utilities/qstring.h"
#include "utilities/qsystem.h"
#include "utilities/qtime.h"

/* ipc */
#include "ipc/qsem.h"
#include "ipc/qshm.h"

#endif /* QLIBC_H */
