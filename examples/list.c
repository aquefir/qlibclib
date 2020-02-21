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
    // create a list.
    qlist_t *list = qlist(0);

    //
    // TEST 1 : adding elements.
    //

    // insert elements
    list->addlast(list, "e1", sizeof("e1"));
    list->addlast(list, "e2", sizeof("e2"));
    list->addlast(list, "e3", sizeof("e3"));
    list->addfirst(list, "e4", sizeof("e4"));
    list->addfirst(list, "e5", sizeof("e5"));

    // print out
    printf("--[Test 1 : adding elements]--\n");
    list->debug(list, stdout);

    //
    // TEST 2 : get methods
    //

    printf("\n--[Test 2 : get methods]--\n");
    printf("getFirst() : %s\n", (char *) list->getfirst(list, NULL, false));
    printf("getLast() : %s\n", (char *) list->getlast(list, NULL, false));
    printf("getAt(0) : %s\n", (char *) list->getat(list, 0, NULL, false));
    printf("getAt(5) : %s\n", (char *) list->getat(list, 4, NULL, false));
    printf("getAt(-1) : %s\n", (char *) list->getat(list, -1, NULL, false));
    printf("getAt(-2) : %s\n", (char *) list->getat(list, -2, NULL, false));

    //
    // TEST 3 : pop methods
    //

    printf("\n--[Test 3 : pop(get and remove) methods]--\n");
    char *first = (char *) list->popfirst(list, NULL);
    char *last = (char *) list->poplast(list, NULL);
    printf("popFirst() : %s\n", first);
    printf("popLast() : %s\n", last);
    free(first);
    free(last);

    list->debug(list, stdout);

    //
    // TEST 4 : travesal list.
    //

    printf("\n--[Test 4 : travesal list]--\n");
    printf("list size : %zu elements\n", list->size(list));
    qlist_obj_t obj;
    memset((void *) &obj, 0, sizeof(obj));  // must be cleared before call
    list->lock(list);
    while (list->getnext(list, &obj, false) == true) {
        printf("DATA=%s, SIZE=%zu\n", (char *) obj.data, obj.size);
    }
    list->unlock(list);

    //
    // TEST 5 :  reverse list
    //

    list->reverse(list);

    // print out
    printf("\n--[Test 5 : reverse]--\n");
    list->debug(list, stdout);

    // free object
    list->free(list);

    return 0;
}
