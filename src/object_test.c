/**
 * @brief It tests the object module.
 *
 * @file object_test.c
 * @author Jorge Pastor
 * @version 1.0
 * @date 25-03-2025
 * @copyright GNU Public License
 */

#include "object.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "object_test.h"
#include "test.h"

/**
 * @def MAX_TESTS
 * @brief Defines the number of tests
 */
#define MAX_TESTS 10

/**
 * @brief Main function for CHARACTER unit tests.
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
                printf("Running all test for module Object:\n");
        } else {
                test = atoi(argv[1]);
                all = 0;
                printf("Running test %d:\t", test);
                if (test < 1 && test > MAX_TESTS) {
                        printf("Error: unknown test %d\t", test);
                        exit(EXIT_SUCCESS);
                }
        }

        if (all || test == 1) test1_object_create();
        if (all || test == 2) test2_object_create();
        if (all || test == 3) test1_object_destroy();
        if (all || test == 4) test2_object_destroy();
        if (all || test == 5) test1_object_get_id();
        if (all || test == 6) test2_object_get_id();
        if (all || test == 7) test1_object_set_name();
        if (all || test == 8) test2_object_set_name();
        if (all || test == 9) test1_object_get_name();
        if (all || test == 10) test2_object_get_name();
        if (all || test == 11) test1_object_set_description();
        if (all || test == 12) test2_object_set_description();
        if (all || test == 13) test1_object_get_description();
        if (all || test == 14) test2_object_get_description();
        if (all || test == 15) test1_object_set_health();
        if (all || test == 16) test2_object_set_health();
        if (all || test == 17) test1_object_get_health();
        if (all || test == 18) test2_object_get_health();
        if (all || test == 19) test1_object_set_movable();
        if (all || test == 20) test2_object_set_movable();
        if (all || test == 21) test1_object_get_movable();
        if (all || test == 22) test2_object_get_movable();
        if (all || test == 23) test1_object_set_open();
        if (all || test == 24) test2_object_set_open();
        if (all || test == 25) test1_object_get_open();
        if (all || test == 26) test2_object_get_open();
        if (all || test == 27) test1_object_set_dependency();
        if (all || test == 28) test2_object_set_dependency();
        if (all || test == 29) test1_object_get_dependency();
        if (all || test == 30) test2_object_get_dependency();

        PRINT_PASSED_PERCENTAGE;

        return EXIT_SUCCESS;
}

void test1_object_create() {
        int result;
        Object *o = NULL;
        o = object_create(5);
        result = o != NULL;
        PRINT_TEST_RESULT(result);
        object_destroy(o);
}

void test2_object_create() {
        Object *o = NULL;
        o = object_create(4);
        PRINT_TEST_RESULT(object_get_id(o) == 4);
        object_destroy(o);
}

void test1_object_destroy() {
        Object *o = object_create(1);
        PRINT_TEST_RESULT(object_destroy(o) == OK);
}

void test2_object_destroy() { PRINT_TEST_RESULT(object_destroy(NULL) == ERROR); }

void test1_object_get_id() {
        Object *o = object_create(10);
        PRINT_TEST_RESULT(object_get_id(o) == 10);
        object_destroy(o);
}

void test2_object_get_id() { PRINT_TEST_RESULT(object_get_id(NULL) == NO_ID); }

void test1_object_set_name() {
        Object *o = object_create(1);
        PRINT_TEST_RESULT(object_set_name(o, "Crumb") == OK);
        object_destroy(o);
}

void test2_object_set_name() { PRINT_TEST_RESULT(object_set_name(NULL, "Crumb") == ERROR); }

void test1_object_get_name() {
        Object *o = object_create(1);
        object_set_name(o, "Apple");
        PRINT_TEST_RESULT(strcmp(object_get_name(o), "Apple") == 0);
        object_destroy(o);
}

void test2_object_get_name() { PRINT_TEST_RESULT(object_get_name(NULL) == NULL); }

void test1_object_set_description() {
        Object *o = object_create(1);
        PRINT_TEST_RESULT(object_set_description(o, "ABC") == OK);
        object_destroy(o);
}

void test2_object_set_description() { PRINT_TEST_RESULT(object_set_description(NULL, "ABC") == ERROR); }

void test1_object_get_description() {
        Object *o = object_create(1);
        object_set_description(o, "ABC");
        PRINT_TEST_RESULT(strcmp(object_get_description(o), "ABC") == 0);
        object_destroy(o);
}

void test2_object_get_description() { PRINT_TEST_RESULT(object_get_description(NULL) == NULL); }

/*----------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------*/
void test1_object_set_health() {
        Object *o = object_create(1);
        PRINT_TEST_RESULT(object_set_health(o, 10) == OK);
        object_destroy(o);
}

void test2_object_set_health() { PRINT_TEST_RESULT(object_set_health(NULL, 10) == ERROR); }

void test1_object_get_health() {
        Object *o = object_create(10);
        PRINT_TEST_RESULT(object_get_health(o) == 0);
        object_destroy(o);
}

void test2_object_get_health() { PRINT_TEST_RESULT(object_get_health(NULL) == -1); }

/*----------------------------------------------------------------------------------------------------*/
void test1_object_set_movable() {
        Object *o = object_create(1);
        PRINT_TEST_RESULT(object_set_movable(o, TRUE) == OK);
        object_destroy(o);
}

void test2_object_set_movable() { PRINT_TEST_RESULT(object_set_movable(NULL, TRUE) == ERROR); }

void test1_object_get_movable() {
        Object *o = object_create(10);
        PRINT_TEST_RESULT(object_get_movable(o) == FALSE);
        object_destroy(o);
}

void test2_object_get_movable() { PRINT_TEST_RESULT(object_get_movable(NULL) == FALSE); }

/*----------------------------------------------------------------------------------------------------*/
void test1_object_set_open() {
        Object *o = object_create(1);
        PRINT_TEST_RESULT(object_set_open(o, 1) == OK);
        object_destroy(o);
}

void test2_object_set_open() { PRINT_TEST_RESULT(object_set_open(NULL, 1) == ERROR); }

void test1_object_get_open() {
        Object *o = object_create(10);
        PRINT_TEST_RESULT(object_get_open(o) == NO_ID);
        object_destroy(o);
}

void test2_object_get_open() { PRINT_TEST_RESULT(object_get_open(NULL) == NO_ID); }

/*----------------------------------------------------------------------------------------------------*/
void test1_object_set_dependency() {
        Object *o = object_create(1);
        PRINT_TEST_RESULT(object_set_dependency(o, 1) == OK);
        object_destroy(o);
}

void test2_object_set_dependency() { PRINT_TEST_RESULT(object_set_dependency(NULL, 1) == ERROR); }

void test1_object_get_dependency() {
        Object *o = object_create(10);
        PRINT_TEST_RESULT(object_get_dependency(o) == NO_ID);
        object_destroy(o);
}

void test2_object_get_dependency() { PRINT_TEST_RESULT(object_get_dependency(NULL) == NO_ID); }
