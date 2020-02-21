/****************************************************************************\
 *                                  qlibc™                                  *
 *                                                                          *
 *               Copyright © 2010-2015 Seungyoung “Steve” Kim               *
 *                      Copyright © 2020 ARQADIUM, LLC                      *
 *                       Licenced under BSD-2-Clause.                       *
\****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "qlibc.h"

int main(void) {
    // create a hash-table.
    qhashtbl_t *tbl = qhashtbl(0, 0);

    //
    // TEST 1 : adding elements.
    //

    // insert elements (key duplication is not allowed)
    tbl->putstr(tbl, "e1", "a");
    tbl->putstr(tbl, "e2", "b");
    tbl->putstr(tbl, "e2", "c");
    tbl->putstr(tbl, "e3", "d");
    tbl->putstr(tbl, "e4", "e");
    tbl->putstr(tbl, "e5", "f");

    // print out
    printf("--[Test 1 : adding elements]--\n");
    tbl->debug(tbl, stdout);

    //
    // TEST 2 : many ways to find a key.
    //

    printf("\n--[Test 2 : many ways to find a key]--\n");
    printf("get('e2') : %s\n", (char *) tbl->get(tbl, "e2", NULL, false));
    printf("getstr('e2') : %s\n", tbl->getstr(tbl, "e2", false));

    char *e2 = tbl->getstr(tbl, "e2", true);
    printf("getstr('e2') with newmem parameter: %s\n", e2);
    free(e2);

    //
    // TEST 3 : travesal a table.
    //

    printf("\n--[Test 3 : travesal a table]--\n");
    printf("list size : %zu elements\n", tbl->size(tbl));
    qhashtbl_obj_t obj;
    memset((void *) &obj, 0, sizeof(obj));  // must be cleared before call
    tbl->lock(tbl);
    while (tbl->getnext(tbl, &obj, true) == true) {
        printf("NAME=%s, DATA=%s, SIZE=%zu\n", obj.name, (char *) obj.data,
               obj.size);
        free(obj.name);
        free(obj.data);
    }
    tbl->unlock(tbl);

    // free object
    tbl->free(tbl);

    return 0;
}
