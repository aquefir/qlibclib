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
    // sample object
    struct sampleobj {
        int num;
        char str[10];
    };

    // get new grow
    qgrow_t *grow = qgrow(0);

    // add objects
    int i;
    struct sampleobj obj;
    for (i = 0; i < 3; i++) {
        // filling object with sample data
        obj.num = i;
        sprintf(obj.str, "hello%d", i);

        // stack
        grow->add(grow, (void *) &obj, sizeof(struct sampleobj));
    }

    // final
    struct sampleobj *final;
    final = (struct sampleobj *) grow->toarray(grow, NULL);

    // print out
    printf("Number of Objects = %zu\n", grow->size(grow));
    for (i = 0; i < grow->size(grow); i++) {
        printf("Object%d %d, %s\n", i + 1, final[i].num, final[i].str);
    }

    // release
    free(final);
    grow->free(grow);

    return 0;
}
