/**
 * @brief It tests space module
 *
 * @file set_test.c
 * @author Carlos Méndez
 * @version 1.0
 * @date 28-02-2025
 * @copyright GNU Public License
 */

#include "set.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "set_test.h"
#include "test.h"

/**
 * @def MAX_TESTS
 * @brief Defines the maximum number of tests
 */
#define MAX_TESTS 30
/**
 * @def MAX_IDS
 * @brief Defines the maximum number of ids
 */
#define MAX_IDS 50

/**
 * @brief Main function for SET unit tests.
 *
 * You may execute ALL or a SINGLE test
 *   1.- No parameter -> ALL test are executed
 *   2.- A number means a particular test (the one identified by that number)
 *       is executed
 *
 */
int main(int argc, char **argv) {
        int test = 0;
        int all = 1;

        if (argc < 2) {
                printf("Running all test for module Set:\n");
        } else {
                test = atoi(argv[1]);
                all = 0;
                printf("Running test %d:\t", test);
                if (test < 1 && test > MAX_TESTS) {
                        printf("Error: unknown test %d\t", test);
                        exit(EXIT_SUCCESS);
                }
        }

        if (all || test == 1) test1_set_create();
        if (all || test == 2) test2_set_create();
        if (all || test == 3) test1_set_get_nIds();
        if (all || test == 4) test2_set_get_nIds();
        if (all || test == 5) test1_set_add();
        if (all || test == 6) test2_set_add();
        if (all || test == 7) test3_set_add();
        if (all || test == 8) test4_set_add();
        if (all || test == 9) test1_set_del();
        if (all || test == 10) test2_set_del();
        if (all || test == 11) test3_set_del();
        if (all || test == 12) test4_set_del();
        if (all || test == 13) test5_set_del();
        if (all || test == 14) test1_set_has();
        if (all || test == 15) test2_set_has();
        if (all || test == 16) test3_set_has();
        if (all || test == 17) test4_set_has();
        if (all || test == 18) test5_set_has();
        if (all || test == 19) test1_set_get_id_at_index();
        if (all || test == 20) test2_set_get_id_at_index();
        if (all || test == 21) test3_set_get_id_at_index();
        if (all || test == 22) test4_set_get_id_at_index();

        PRINT_PASSED_PERCENTAGE;

        return EXIT_SUCCESS;
}

void test1_set_create() {
        int result;
        Set *s;
        s = set_create();
        result = s != NULL;
        PRINT_TEST_RESULT(result);
        set_destroy(s);
}

void test2_set_create() {
        Set *s = NULL;
        s = set_create();
        PRINT_TEST_RESULT(set_get_nIds(s) == 0);
        set_destroy(s);
}

void test1_set_get_nIds() {
        Set *s = NULL;
        PRINT_TEST_RESULT(set_get_nIds(s) == -1);
}

void test2_set_get_nIds() {
        Set *s;
        s = set_create();
        set_add(s, 1);
        PRINT_TEST_RESULT(set_get_nIds(s) == 1);
        set_destroy(s);
}

void test1_set_add() {
        Set *s;
        s = set_create();
        PRINT_TEST_RESULT(set_add(s, 4) == OK);
        set_destroy(s);
}

void test2_set_add() {
        Set *s = NULL;
        s = set_create();
        PRINT_TEST_RESULT(set_add(s, NO_ID) == ERROR);
        set_destroy(s);
}

void test3_set_add() {
        Set *s = NULL;
        int i = 0;
        for (i = 0; i < MAX_IDS; i++) {
                set_add(s, i);
        }
        PRINT_TEST_RESULT(set_add(s, 4) == ERROR);
}

void test4_set_add() {
        Set *s = NULL;
        PRINT_TEST_RESULT(set_add(s, 4) == ERROR);
}

void test1_set_del() {
        Set *s = NULL;
        s = set_create();
        if (set_add(s, 4) == OK) {
                if (set_del(s, 4) == OK) {
                        PRINT_TEST_RESULT(set_get_nIds(s) == 0);
                }
        }
        set_destroy(s);
}

void test2_set_del() {
        Set *s = NULL;
        s = set_create();
        if (set_add(s, 4) == OK) {
                if (set_del(s, 4) == OK) {
                        PRINT_TEST_RESULT(set_get_id_at_index(s, 0) == -1);
                }
        }
        set_destroy(s);
}

void test3_set_del() {
        Set *s = NULL;
        s = set_create();
        PRINT_TEST_RESULT(set_del(s, NO_ID) == NO_ID);
        set_destroy(s);
}

void test4_set_del() {
        Set *s = NULL;
        PRINT_TEST_RESULT(set_del(s, 4) == NO_ID);
}

void test5_set_del() {
        Set *s = NULL;
        s = set_create();
        PRINT_TEST_RESULT(set_del(s, 4) == NO_ID);
        set_destroy(s);
}

void test1_set_has() {
        Set *s = NULL;
        s = set_create();
        set_add(s, 5);
        PRINT_TEST_RESULT(set_has(s, 5) == TRUE);
        set_destroy(s);
}

void test2_set_has() {
        Set *s = NULL;
        s = set_create();
        set_add(s, 5);
        PRINT_TEST_RESULT(set_has(s, 4) == FALSE);
        set_destroy(s);
}

void test3_set_has() {
        Set *s = NULL;
        set_add(s, 5);
        PRINT_TEST_RESULT(set_has(s, 4) == FALSE);
        set_destroy(s);
}

void test4_set_has() {
        Set *s = NULL;
        s = set_create();
        PRINT_TEST_RESULT(set_has(s, NO_ID) == FALSE);
        set_destroy(s);
}

void test5_set_has() {
        Set *s = NULL;
        s = set_create();
        PRINT_TEST_RESULT(set_has(s, 4) == FALSE);
        set_destroy(s);
}

void test1_set_get_id_at_index() {
        Set *s;
        s = set_create();
        set_add(s, 5);
        PRINT_TEST_RESULT(set_get_id_at_index(s, 0) == 5);
        set_destroy(s);
}

void test2_set_get_id_at_index() {
        Set *s = NULL;
        set_add(s, 4);
        PRINT_TEST_RESULT(set_get_id_at_index(s, 0) == NO_ID);
}

void test3_set_get_id_at_index() {
        Set *s;
        s = set_create();
        set_add(s, 4);
        PRINT_TEST_RESULT(set_get_id_at_index(s, 1) == NO_ID);
        set_destroy(s);
}

void test4_set_get_id_at_index() {
        Set *s;
        s = set_create();
        set_add(s, 4);
        PRINT_TEST_RESULT(set_get_id_at_index(s, -2) == NO_ID);
        set_destroy(s);
}
