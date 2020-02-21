/****************************************************************************\
 *                                  qlibc™                                  *
 *                                                                          *
 *               Copyright © 2010-2015 Seungyoung “Steve” Kim               *
 *                      Copyright © 2020 ARQADIUM, LLC                      *
 *                       Licenced under BSD-2-Clause.                       *
\****************************************************************************/

/**
 * qunit C Unit Test Framework.
 *
 * @file qunit.h
 */

#ifndef QUNIT_H
#define QUNIT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/time.h>

#ifdef __cplusplus
extern "C" {
#endif

#define OUTSTREAM    (stdout)
#define PRINT(fmt, args...) do {                                            \
        fprintf(OUTSTREAM, "" fmt, ##args);                                 \
    } while(0)
#define PRINTLN(fmt, args...) do {                                          \
        fprintf(OUTSTREAM, "" fmt "\n", ##args);                            \
    } while(0)

#define QUNIT_START(title)                                                  \
char *_q_title = title;                                                     \
int _q_tot_tests = 0;                                                       \
int _q_tot_failed = 0;                                                      \
int _q_this_failed = 0;                                                     \
int _q_errcnt = 0;                                                          \
int _q_assert_cnt = 0;  /* number of assert test in a test */               \
int _q_assert_dot_cnt = 0;  /* number of dots printed out in a test. */     \
long _q_timer;                                                              \
int main(int argc, char **argv) {                                           \
    PRINTLN("%s", _q_title);                                                \
    PRINTLN("======================================================================");  \

#define QUNIT_END()                                                         \
    _TEST_RESULT();                                                         \
    PRINTLN("======================================================================");  \
    PRINTLN("%s - %d/%d tests passed.",                                     \
        ((_q_tot_failed == 0) ? "PASS" : "FAIL"),                           \
        (_q_tot_tests - _q_tot_failed), _q_tot_tests);                      \
    return _q_tot_failed;                                                   \
}

#define TEST(name)                                                          \
    _TEST_RESULT();                                                         \
    _q_tot_tests++;                                                         \
    _q_assert_cnt = 0;                                                      \
    _q_assert_dot_cnt = 0;                                                  \
    PRINT("* TEST : %s ", name);                                            \
    TIMER_START(_q_timer);

#define _TEST_RESULT()                                                      \
    TIMER_STOP(_q_timer);                                                   \
    if (_q_tot_tests ) PRINTLN(" %s (%d assertions, %ldms)",                \
        (_q_this_failed) ? "FAIL" : "OK", _q_assert_cnt, _q_timer);         \
    _q_tot_failed += (_q_this_failed) ? 1 : 0;                              \
    _q_this_failed = 0;

#define ASSERT(expr)                                                        \
    _q_assert_cnt++;                                                        \
    if (! (expr))  {                                                        \
        _q_this_failed++;                                                   \
        PRINTLN("\nAssertion '%s' failed (%s:%d)", #expr, __FILE__, __LINE__); \
    } else if (_q_assert_dot_cnt < 30) {                                    \
        PRINT(".");                                                         \
        _q_assert_dot_cnt++;                                                \
    }

#define ASSERT_EQUAL_STR(s1, s2) ASSERT(!strcmp(s1, s2))
#define ASSERT_EQUAL_INT(d1, d2) ASSERT(d1 == d2)
#define ASSERT_EQUAL_BOOL(d1, d2) ASSERT(d1 == d2)
#define ASSERT_EQUAL_PT(p1, p2) ASSERT(p1 == p2)
#define ASSERT_EQUAL_MEM(p1, p2, n) ASSERT(!memcmp(p1, p2, n))
#define ASSERT_NULL(p) ASSERT(NULL == p)
#define ASSERT_NOT_NULL(p) ASSERT(NULL != p)
#define ASSERT_TRUE(b) ASSERT(b)
#define ASSERT_FALSE(b) ASSERT(!(b))

#define TIMER_START(x) do {                                                 \
        x = qtime_current_milli();                                          \
    } while(0)

#define TIMER_STOP(x) do {                                                  \
        x = qtime_current_milli() - x;                                      \
    } while(0)

#ifdef __cplusplus
}
#endif

#endif /* QUNIT_H */
