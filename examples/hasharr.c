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
    // initialize hash-table
    int memsize = qhasharr_calculate_memsize(10);
    char memory[memsize];
    qhasharr_t *tbl = qhasharr(memory, sizeof(memory));
    if (tbl == NULL) {
        return -1;
    }

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
    tbl->putstr(tbl, "12345678901234567890",
                "1234567890123456789012345678901234567890");

    // print out
    printf("--[Test 1 : adding elements]--\n");
    tbl->debug(tbl, stdout);

    //
    // TEST 2 : many ways to find key.
    //

    printf("\n--[Test 2 : many ways to find key]--\n");
    char *e2 = tbl->getstr(tbl, "e2");
    if (e2 != NULL) {
        printf("getstr('e2') : %s\n", e2);
        free(e2);
    }

    //
    // TEST 3 : travesal table.
    //

    printf("\n--[Test 3 : travesal table]--\n");
    printf("table size : %d elements\n", tbl->size(tbl, NULL, NULL));
    int idx = 0;
    qhasharr_obj_t obj;
    while (tbl->getnext(tbl, &obj, &idx) == true) {
        printf("NAME=%s(%zu), DATA=%s(%zu)\n",
               (char *)obj.name, obj.namesize,
               (char *)obj.data, obj.datasize);
        free(obj.name);
        free(obj.data);
    }

    // free table reference object.
    tbl->free(tbl);

    return 0;
}
