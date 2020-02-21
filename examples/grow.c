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
#include <stdint.h>
#include <string.h>
#include "qlibc.h"

int main(void) {
    qgrow_t *grow = qgrow(0);

    // add elements
    grow->addstr(grow, "AB");       // no need to supply size
    grow->addstrf(grow, "%d", 12);  // for formatted string
    grow->addstr(grow, "CD");

    char *final = grow->tostring(grow);
    // get the chunk as a string

    // print out
    grow->debug(grow, stdout);
    printf("Number of elements = %zu\n", grow->size(grow));
    printf("Final string = %s\n", final);

    // release
    free(final);
    grow->free(grow);

    return 0;
}
