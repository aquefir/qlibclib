/****************************************************************************\
 *                                  qlibc™                                  *
 *                                                                          *
 *               Copyright © 2010-2015 Seungyoung “Steve” Kim               *
 *                      Copyright © 2020 ARQADIUM, LLC                      *
 *                       Licenced under BSD-2-Clause.                       *
\****************************************************************************/

#include "qunit.h"
#include "qlibc.h"
#include <errno.h>

void test_thousands_of_keys(size_t memsize, int num_keys, char *key_postfix, char *value_postfix);

QUNIT_START("Test qhasharr.c");

TEST("Test basic but complete") {
    const char *KEYS[] = {
            "key0",
            "key1_long_key-fef6bd00f77aef990a6d62969fee0cb904d052665a1dcf10492156124fafc59769e91d1a06ec1215e435e29ef43de177f6f2a5e035860e702c82e08084950313",
    };
    const char *VALUES[] = {
            "value0",
            "value1_long_value-1a087a6982371bbfc9d4e14ae76e05ddd784a5d9c6b0fc9e6cd715baab66b90987b2ee054764e58fc04e449dfa060a68398601b64cf470cb6f0a260ec6539866",
    };

    char memory[qhasharr_calculate_memsize(10)];
    qhasharr_t *tbl = qhasharr(memory, sizeof(memory));
    ASSERT_EQUAL_INT(0, tbl->size(tbl, NULL, NULL));

    tbl->putstr(tbl, KEYS[0], VALUES[0]);
    ASSERT_EQUAL_INT(1, tbl->size(tbl, NULL, NULL));
    ASSERT_EQUAL_STR(VALUES[0], tbl->getstr(tbl, KEYS[0]));

    tbl->putstr(tbl, KEYS[1], VALUES[1]);
    ASSERT_EQUAL_INT(2, tbl->size(tbl, NULL, NULL));
    ASSERT_EQUAL_STR(VALUES[1], tbl->getstr(tbl, KEYS[1]));

    tbl->remove(tbl, KEYS[0]);
    ASSERT_EQUAL_INT(1, tbl->size(tbl, NULL, NULL));
    ASSERT_EQUAL_PT(NULL, tbl->getstr(tbl, KEYS[0]));
    ASSERT_EQUAL_STR(VALUES[1], tbl->getstr(tbl, KEYS[1]));

    tbl->clear(tbl);
    ASSERT_EQUAL_INT(0, tbl->size(tbl, NULL, NULL));

    tbl->free(tbl);
}

TEST("Test thousands of keys insertion and removal: short key + short value") {
    test_thousands_of_keys(
        qhasharr_calculate_memsize(10000),
        10000,
        "",
        ""
    );
}

TEST("Test thousands of keys insertion and removal: short key + long value") {
    test_thousands_of_keys(
        qhasharr_calculate_memsize(10000),
        10000,
        "",
        "1a087a6982371bbfc9d4e14ae76e05ddd784a5d9c6b0fc9e6cd715baab66b90987b2ee054764e58fc04e449dfa060a68398601b64cf470cb6f0a260ec6539866"
    );
}

TEST("Test thousands of keys insertion and removal: long key + short value") {
    test_thousands_of_keys(
        qhasharr_calculate_memsize(10000),
        10000,
        "1a087a6982371bbfc9d4e14ae76e05ddd784a5d9c6b0fc9e6cd715baab66b90987b2ee054764e58fc04e449dfa060a68398601b64cf470cb6f0a260ec6539866",
        ""
    );
}

TEST("Test thousands of keys insertion and removal: long key + long value") {
    test_thousands_of_keys(
        qhasharr_calculate_memsize(10000),
        10000,
        "1a087a6982371bbfc9d4e14ae76e05ddd784a5d9c6b0fc9e6cd715baab66b90987b2ee054764e58fc04e449dfa060a68398601b64cf470cb6f0a260ec6539866",
        "1a087a6982371bbfc9d4e14ae76e05ddd784a5d9c6b0fc9e6cd715baab66b90987b2ee054764e58fc04e449dfa060a68398601b64cf470cb6f0a260ec6539866"
    );
}

TEST("Test remove_by_idx()") {
    char memory[qhasharr_calculate_memsize(10)];
    qhasharr_t *tbl = qhasharr(memory, sizeof(memory));

    tbl->putstr(tbl, "key1", "");
    tbl->putstr(tbl, "key2", "short");
    tbl->putstr(tbl, "key3", "1a087a6982371bbfc9d4e14ae76e05ddd784a5d9c6b0fc9e6cd715baab66b90987b2ee054764e58fc04e449dfa060a68398601b64cf470cb6f0a260ec6539866");
    tbl->putstr(tbl, "key4-1a087a6982371bbfc9d4e14ae76e05ddd784a5d9c6b0fc9e6cd715baab66b90987b2ee054764e58fc04e449dfa060a68398601b64cf470cb6f0a260ec6539866", "");
    tbl->putstr(tbl, "key5-1a087a6982371bbfc9d4e14ae76e05ddd784a5d9c6b0fc9e6cd715baab66b90987b2ee054764e58fc04e449dfa060a68398601b64cf470cb6f0a260ec6539866", "short");
    tbl->putstr(tbl, "key6-1a087a6982371bbfc9d4e14ae76e05ddd784a5d9c6b0fc9e6cd715baab66b90987b2ee054764e58fc04e449dfa060a68398601b64cf470cb6f0a260ec6539866", "1a087a6982371bbfc9d4e14ae76e05ddd784a5d9c6b0fc9e6cd715baab66b90987b2ee054764e58fc04e449dfa060a68398601b64cf470cb6f0a260ec6539866");
    ASSERT_EQUAL_INT(6, tbl->size(tbl, NULL, NULL));

    int idx = 0;
    qhasharr_obj_t obj;
    while(tbl->getnext(tbl, &obj, &idx) == true) {
        ASSERT_EQUAL_BOOL(true, tbl->remove_by_idx(tbl, --idx));
        free(obj.name);
        free(obj.data);
    }

    ASSERT_EQUAL_INT(0, tbl->size(tbl, NULL, NULL));
    tbl->free(tbl);
}

QUNIT_END();


void test_thousands_of_keys(size_t memsize, int num_keys, char *key_postfix, char *value_postfix) {
    char memory[memsize];
    qhasharr_t *tbl = qhasharr(memory, sizeof(memory));

    int i;
    for (i = 0; i < num_keys; i++) {
        char *key = qstrdupf("key%d%s", i, key_postfix);
        char *value = qstrdupf("value%d%s", i, value_postfix);

        if (tbl->putstr(tbl, key, value) == false) {
            ASSERT(errno == ENOBUFS);
            break;
        }
        ASSERT_EQUAL_INT(i + 1, tbl->size(tbl, NULL, NULL));
        ASSERT_EQUAL_STR(value, tbl->getstr(tbl, key));

        free(key);
        free(value);
    }

    for (; i >= 0; i--) {
        char *key = qstrdupf("key%d%s", i, key_postfix);
        tbl->remove(tbl, key);
        ASSERT_EQUAL_INT(i, tbl->size(tbl, NULL, NULL));
        ASSERT_EQUAL_PT(NULL, tbl->getstr(tbl, key));
        free(key);
    }

    int usedslots = -1;
    ASSERT_EQUAL_INT(0, tbl->size(tbl, NULL, &usedslots));
    ASSERT_EQUAL_INT(0, usedslots);
    if(usedslots > 0 ) {
        printf("==== %d\n", usedslots);
        tbl->debug(tbl, stdout);
    }

    tbl->free(tbl);
}
