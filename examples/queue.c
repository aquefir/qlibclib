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
#include <inttypes.h>
#include <string.h>
#include "qlibc.h"

int main(void) {
    // create queue
    qqueue_t *queue = qqueue(0);

    // example: integer queue
    queue->pushint(queue, 1);
    queue->pushint(queue, 2);
    queue->pushint(queue, 3);

    printf("popint(): %"PRId64"\n", queue->popint(queue));
    printf("popint(): %"PRId64"\n", queue->popint(queue));
    printf("popint(): %"PRId64"\n", queue->popint(queue));

    // example: string queue
    queue->pushstr(queue, "A string");
    queue->pushstr(queue, "B string");
    queue->pushstr(queue, "C string");

    char *str = queue->popstr(queue);
    printf("popstr(): %s\n", str);
    free(str);
    str = queue->popstr(queue);
    printf("popstr(): %s\n", str);
    free(str);
    str = queue->popstr(queue);
    printf("popstr(): %s\n", str);
    free(str);

    // example: object queue
    queue->push(queue, "A object", sizeof("A object"));
    queue->push(queue, "B object", sizeof("B object"));
    queue->push(queue, "C object", sizeof("C object"));

    void *obj = queue->pop(queue, NULL);
    printf("pop(): %s\n", (char *) obj);
    free(obj);
    obj = queue->pop(queue, NULL);
    printf("pop(): %s\n", (char *) obj);
    free(obj);
    obj = queue->pop(queue, NULL);
    printf("pop(): %s\n", (char *) obj);
    free(obj);

    // release
    queue->free(queue);

    return 0;
}
