/****************************************************************************\
 *                                  qlibc™                                  *
 *                                                                          *
 *               Copyright © 2010-2015 Seungyoung “Steve” Kim               *
 *                      Copyright © 2020 ARQADIUM, LLC                      *
 *                       Licenced under BSD-2-Clause.                       *
\****************************************************************************/

#include "qunit.h"
#include "qlibc.h"

QUNIT_START("Test qhashtbl.c");

TEST("Test basic but complete") {
    const char *KEYS[] = {
            "key0",
            "key1_long_key-fef6bd00f77aef990a6d62969fee0cb904d052665a1dcf10492156124fafc59769e91d1a06ec1215e435e29ef43de177f6f2a5e035860e702c82e08084950313",
    };
    const char *VALUES[] = {
            "value0",
            "value1_long_value-1a087a6982371bbfc9d4e14ae76e05ddd784a5d9c6b0fc9e6cd715baab66b90987b2ee054764e58fc04e449dfa060a68398601b64cf470cb6f0a260ec6539866",
    };

    qhashtbl_t *tbl = qhashtbl(0, 0);
    ASSERT_EQUAL_INT(0, tbl->size(tbl));

    tbl->putstr(tbl, KEYS[0], VALUES[0]);
    ASSERT_EQUAL_INT(1, tbl->size(tbl));
    ASSERT_EQUAL_STR(VALUES[0], tbl->getstr(tbl, KEYS[0], false));

    tbl->putstr(tbl, KEYS[1], VALUES[1]);
    ASSERT_EQUAL_INT(2, tbl->size(tbl));
    ASSERT_EQUAL_STR(VALUES[1], tbl->getstr(tbl, KEYS[1], false));

    tbl->remove(tbl, KEYS[0]);
    ASSERT_EQUAL_INT(1, tbl->size(tbl));
    ASSERT_NULL(tbl->getstr(tbl, KEYS[0], false));
    ASSERT_EQUAL_STR(VALUES[1], tbl->getstr(tbl, KEYS[1], false));

    tbl->clear(tbl);
    ASSERT_EQUAL_INT(0, tbl->size(tbl));

    tbl->free(tbl);
}

void test_thousands_of_keys(int num_keys, char *key_postfix, char *value_postfix) {
    qhashtbl_t *tbl = qhashtbl(0, 0);
    ASSERT_EQUAL_INT(0, tbl->size(tbl));

    int i;
    for (i = 0; i < num_keys; i++) {
        char *key = qstrdupf("key%d%s", i, key_postfix);
        char *value = qstrdupf("value%d%s", i, value_postfix);

        tbl->putstr(tbl, key, value);
        ASSERT_EQUAL_INT(i + 1, tbl->size(tbl));
        ASSERT_EQUAL_STR(value, tbl->getstr(tbl, key, false));

        free(key);
        free(value);
    }

    for (i--; i >= 0; i--) {
        char *key = qstrdupf("key%d%s", i, key_postfix);
        tbl->remove(tbl, key);
        ASSERT_EQUAL_INT(i, tbl->size(tbl));
        ASSERT_NULL(tbl->getstr(tbl, key, false));
        free(key);
    }

    ASSERT_EQUAL_INT(0, tbl->size(tbl));
    tbl->free(tbl);
}


TEST("Test thousands of keys insertion and removal: short key + short value") {
    test_thousands_of_keys(10000, "", "");
}

TEST("Test thousands of keys insertion and removal: short key + long value") {
    test_thousands_of_keys(10000, "", "1a087a6982371bbfc9d4e14ae76e05ddd784a5d9c6b0fc9e6cd715baab66b90987b2ee054764e58fc04e449dfa060a68398601b64cf470cb6f0a260ec6539866");
}

TEST("Test thousands of keys insertion and removal: long key + short value") {
    test_thousands_of_keys(10000, "1a087a6982371bbfc9d4e14ae76e05ddd784a5d9c6b0fc9e6cd715baab66b90987b2ee054764e58fc04e449dfa060a68398601b64cf470cb6f0a260ec6539866", "");
}

TEST("Test thousands of keys insertion and removal: long key + long value") {
    test_thousands_of_keys(10000, "1a087a6982371bbfc9d4e14ae76e05ddd784a5d9c6b0fc9e6cd715baab66b90987b2ee054764e58fc04e449dfa060a68398601b64cf470cb6f0a260ec6539866", "1a087a6982371bbfc9d4e14ae76e05ddd784a5d9c6b0fc9e6cd715baab66b90987b2ee054764e58fc04e449dfa060a68398601b64cf470cb6f0a260ec6539866");
}

QUNIT_END();
