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
    // create stack
    qstack_t *stack = qstack(0);

    // example: integer stack
    stack->pushint(stack, 1);
    stack->pushint(stack, 2);
    stack->pushint(stack, 3);

    printf("popint(): %"PRId64"\n", stack->popint(stack));
    printf("popint(): %"PRId64"\n", stack->popint(stack));
    printf("popint(): %"PRId64"\n", stack->popint(stack));

    // example: string stack
    stack->pushstr(stack, "A string");
    stack->pushstr(stack, "B string");
    stack->pushstr(stack, "C string");

    char *str = stack->popstr(stack);
    printf("popstr(): %s\n", str);
    free(str);
    str = stack->popstr(stack);
    printf("popstr(): %s\n", str);
    free(str);
    str = stack->popstr(stack);
    printf("popstr(): %s\n", str);
    free(str);

    // example: object stack
    stack->push(stack, "A object", sizeof("A object"));
    stack->push(stack, "B object", sizeof("B object"));
    stack->push(stack, "C object", sizeof("C object"));

    void *obj = stack->pop(stack, NULL);
    printf("pop(): %s\n", (char *) obj);
    free(obj);
    obj = stack->pop(stack, NULL);
    printf("pop(): %s\n", (char *) obj);
    free(obj);
    obj = stack->pop(stack, NULL);
    printf("pop(): %s\n", (char *) obj);
    free(obj);

    // release
    stack->free(stack);

    return 0;
}
