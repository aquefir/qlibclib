/****************************************************************************\
 *                                  qlibc™                                  *
 *                                                                          *
 *               Copyright © 2010-2015 Seungyoung “Steve” Kim               *
 *                      Copyright © 2020 ARQADIUM, LLC                      *
 *                       Licenced under BSD-2-Clause.                       *
\****************************************************************************/

#include "qlibc.h"

// This includes all extension header files.
#include "qlibcext.h"
// In case, you want to include only particular extensions, replace with this.
//#include "extensions/qconfig.h"

#define CONF_PATH   "config.conf"

int main(void) {
#ifdef DISABLE_QCONFIG
    printf("qconfig extension is disabled at compile time.\n");
    return 1;
#else
    qlisttbl_t *tbl = qlisttbl(0);
    if (qconfig_parse_file(tbl, CONF_PATH, '=') == NULL) {
        printf("Failed to open '" CONF_PATH "'.\n");
        return -1;
    }
    tbl->debug(tbl, stdout);

    return 0;
#endif
}
