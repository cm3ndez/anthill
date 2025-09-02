/**
 * @brief It tests the functions of TAD Link
 *
 * @file link_test.c
 * @author Jorge Ochoa
 * @version 1.0
 * @date 25-03-2025
 * @copyright GNU Public License
 */

#include "link.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "link_test.h"
#include "test.h"
/**
 * @def MAX_TESTS
 * @brief Defines the max number of test
 */
#define MAX_TESTS 35

/**
 * @brief Main function for SPACE unit tests.
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
                printf("Running all test for module Link:\n");
        } else {
                test = atoi(argv[1]);
                all = 0;
                printf("Running test %d:\t", test);
                if (test < 1 && test > MAX_TESTS) {
                        printf("Error: unknown test %d\t", test);
                        exit(EXIT_SUCCESS);
                }
        }

        if (all || test == 1) test1_link_create();
        if (all || test == 2) test2_link_create();
        if (all || test == 3) test1_link_destroy();
        if (all || test == 4) test2_link_destroy();
        if (all || test == 5) test1_link_set_id();
        if (all || test == 6) test2_link_set_id();
        if (all || test == 7) test3_link_set_id();
        if (all || test == 8) test1_link_get_id();
        if (all || test == 9) test2_link_get_id();
        if (all || test == 10) test1_link_set_name();
        if (all || test == 11) test2_link_set_name();
        if (all || test == 12) test3_link_set_name();
        if (all || test == 13) test1_link_get_name();
        if (all || test == 14) test2_link_get_name();
        if (all || test == 15) test1_link_set_origin();
        if (all || test == 16) test1_link_set_origin();
        if (all || test == 17) test2_link_set_origin();
        if (all || test == 18) test1_link_get_origin();
        if (all || test == 19) test2_link_get_origin();
        if (all || test == 20) test1_link_set_destination();
        if (all || test == 21) test2_link_set_destination();
        if (all || test == 22) test3_link_set_destination();
        if (all || test == 23) test1_link_get_destination();
        if (all || test == 24) test2_link_get_destination();
        if (all || test == 25) test1_link_set_direction();
        if (all || test == 26) test2_link_set_direction();
        if (all || test == 27) test1_link_get_direction();
        if (all || test == 28) test2_link_get_direction();
        if (all || test == 29) test1_link_set_open();
        if (all || test == 30) test2_link_set_open();
        if (all || test == 31) test3_link_set_open();
        if (all || test == 32) test1_link_get_open();
        if (all || test == 33) test2_link_get_open();

        PRINT_PASSED_PERCENTAGE;

        return EXIT_SUCCESS;
}

void test1_link_create() {
        Link *link = link_create(5);

        PRINT_TEST_RESULT(link != NULL);

        link_destroy(link);
}

void test2_link_create() {
        Link *link = link_create(NO_ID);

        PRINT_TEST_RESULT(link == NULL);
}

void test1_link_destroy() {
        Link *link = link_create(5);

        PRINT_TEST_RESULT(link_destroy(link) == OK);
}

void test2_link_destroy() { PRINT_TEST_RESULT(link_destroy(NULL) == ERROR); }

void test1_link_set_id() {
        Link *link = link_create(1);

        PRINT_TEST_RESULT(link_set_id(link, 10) == OK);

        link_destroy(link);
}

void test2_link_set_id() {
        Link *link = link_create(1);

        PRINT_TEST_RESULT(link_set_id(link, NO_ID) == ERROR);

        link_destroy(link);
}

void test3_link_set_id() { PRINT_TEST_RESULT(link_set_id(NULL, 10) == ERROR); }

void test1_link_get_id() {
        Link *link = link_create(10);

        PRINT_TEST_RESULT(link_get_id(link) == 10);

        link_destroy(link);
}

void test2_link_get_id() { PRINT_TEST_RESULT(link_get_id(NULL) == NO_ID); }

void test1_link_set_name() {
        Link *link = link_create(22);

        PRINT_TEST_RESULT(link_set_name(link, "Door") == OK);

        link_destroy(link);
}

void test2_link_set_name() {
        Link *link = link_create(22);

        PRINT_TEST_RESULT(link_set_name(link, NULL) == ERROR);

        link_destroy(link);
}

void test3_link_set_name() { PRINT_TEST_RESULT(link_set_name(NULL, "Door") == ERROR); }

void test1_link_get_name() {
        Link *link = link_create(22);

        link_set_name(link, "Door");

        PRINT_TEST_RESULT(strcmp(link_get_name(link), "Door") == 0);

        link_destroy(link);
}

void test2_link_get_name() { PRINT_TEST_RESULT(link_get_name(NULL) == NULL); }

void test1_link_set_origin() {
        Link *link = link_create(22);

        PRINT_TEST_RESULT(link_set_origin(link, 3) == OK);

        link_destroy(link);
}

void test2_link_set_origin() { PRINT_TEST_RESULT(link_set_origin(NULL, 3) == ERROR); }

void test3_link_set_origin() {
        Link *link = link_create(3);

        PRINT_TEST_RESULT(link_set_origin(link, NO_ID) == ERROR);

        link_destroy(link);
}

void test1_link_get_origin() {
        Link *link = link_create(22);

        link_set_origin(link, 100);

        PRINT_TEST_RESULT(link_get_origin(link) == 100);

        link_destroy(link);
}

void test2_link_get_origin() { PRINT_TEST_RESULT(link_get_origin(NULL) == NO_ID); }

void test1_link_set_destination() {
        Link *link = link_create(1);

        PRINT_TEST_RESULT(link_set_destination(link, 20) == OK);

        link_destroy(link);
}

void test2_link_set_destination() {
        Link *link = link_create(1);

        PRINT_TEST_RESULT(link_set_destination(link, NO_ID) == ERROR);

        link_destroy(link);
}

void test3_link_set_destination() { PRINT_TEST_RESULT(link_set_destination(NULL, 20) == ERROR); }

void test1_link_get_destination() {
        Link *link = link_create(3);

        link_set_destination(link, 5);

        PRINT_TEST_RESULT(link_get_destination(link) == 5);

        link_destroy(link);
}

void test2_link_get_destination() { PRINT_TEST_RESULT(link_get_destination(NULL) == NO_ID); }

void test1_link_set_direction() {
        Link *link = link_create(4);

        PRINT_TEST_RESULT(link_set_direction(link, 1) == OK);

        link_destroy(link);
}

void test2_link_set_direction() { PRINT_TEST_RESULT(link_set_direction(NULL, 1) == ERROR); }

void test1_link_get_direction() {
        Link *link = link_create(4);

        link_set_direction(link, 1);

        PRINT_TEST_RESULT(link_get_direction(link) == 1);

        link_destroy(link);
}

void test2_link_get_direction() { PRINT_TEST_RESULT(link_get_direction(NULL) == NO_DIRECTION); }

void test1_link_set_open() {
        Link *link = link_create(9);

        PRINT_TEST_RESULT(link_set_open(link, TRUE) == OK);

        link_destroy(link);
}

void test2_link_set_open() {
        Link *link = link_create(9);

        PRINT_TEST_RESULT(link_set_open(link, FALSE) == OK);

        link_destroy(link);
}

void test3_link_set_open() { PRINT_TEST_RESULT(link_set_open(NULL, 30) == ERROR); }

void test1_link_get_open() {
        Link *link = link_create(5);

        link_set_open(link, 1);

        PRINT_TEST_RESULT(link_get_open(link) == TRUE);

        link_destroy(link);
}

void test2_link_get_open() { PRINT_TEST_RESULT(link_get_open(NULL) == FALSE); }
