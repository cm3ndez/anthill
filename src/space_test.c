/**
 * @brief It tests space module
 *
 * @file space_test.c
 * @author Carlos Méndez and Jorge Pastor
 * @version 0.0
 * @date 24-03-2025
 * @copyright GNU Public License
 */

#include "space.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "space_test.h"
#include "test.h"

/**
 * @def MAX_TESTS
 * @brief Defines the maximum number of tests
 */
#define MAX_TESTS 50

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
                printf("Running all test for module Space:\n");
        } else {
                test = atoi(argv[1]);
                all = 0;
                printf("Running test %d:\t", test);
                if (test < 1 && test > MAX_TESTS) {
                        printf("Error: unknown test %d\t", test);
                        exit(EXIT_SUCCESS);
                }
        }

        if (all || test == 1) test1_space_create();
        if (all || test == 2) test2_space_create();
        if (all || test == 3) test1_space_destroy();
        if (all || test == 4) test2_space_destroy();
        if (all || test == 5) test1_space_get_id();
        if (all || test == 6) test2_space_get_id();
        if (all || test == 7) test1_space_set_name();
        if (all || test == 8) test2_space_set_name();
        if (all || test == 9) test3_space_set_name();
        if (all || test == 10) test1_space_get_name();
        if (all || test == 11) test2_space_get_name();
        if (all || test == 12) test1_space_set_discovered();
        if (all || test == 13) test2_space_set_discovered();
        if (all || test == 14) test1_space_get_discovered();
        if (all || test == 15) test2_space_get_discovered();
        if (all || test == 16) test1_space_add_object();
        if (all || test == 17) test2_space_add_object();
        if (all || test == 18) test3_space_add_object();
        if (all || test == 19) test1_space_del_object();
        if (all || test == 20) test2_space_del_object();
        if (all || test == 21) test3_space_del_object();
        if (all || test == 22) test1_space_set_gdesc();
        if (all || test == 23) test2_space_set_gdesc();
        if (all || test == 24) test3_space_set_gdesc();
        if (all || test == 25) test1_space_get_gdesc();
        if (all || test == 26) test2_space_get_gdesc();
        if (all || test == 27) test1_space_get_num_objects();
        if (all || test == 28) test2_space_get_num_objects();
        if (all || test == 29) test1_space_has_object();
        if (all || test == 30) test2_space_has_object();
        if (all || test == 31) test3_space_has_object();
        if (all || test == 32) test4_space_has_object();
        if (all || test == 33) test1_space_set_characters();
        if (all || test == 34) test2_space_set_characters();
        if (all || test == 35) test1_space_get_id_at_index();
        if (all || test == 36) test2_space_get_id_at_index();

        PRINT_PASSED_PERCENTAGE;

        return EXIT_SUCCESS;
}

void test1_space_create() {
        int result;
        Space *s;
        s = space_create(5);
        result = s != NULL;
        PRINT_TEST_RESULT(result);
        space_destroy(s);
}

void test2_space_create() {
        Space *s;
        s = space_create(4);
        PRINT_TEST_RESULT(space_get_id(s) == 4);
        space_destroy(s);
}

void test1_space_destroy() {
        Space *s;
        s = space_create(5);
        PRINT_TEST_RESULT(space_destroy(s) == OK);
}

void test2_space_destroy() {
        Space *s = NULL;
        s = space_create(5);
        space_add_object(s, 5);
        PRINT_TEST_RESULT(space_destroy(s) == OK);
}

void test1_space_get_id() {
        Space *s;
        s = space_create(25);
        PRINT_TEST_RESULT(space_get_id(s) == 25);
        space_destroy(s);
}

void test2_space_get_id() {
        Space *s = NULL;
        PRINT_TEST_RESULT(space_get_id(s) == NO_ID);
}

void test1_space_set_name() {
        Space *s;
        s = space_create(5);
        PRINT_TEST_RESULT(space_set_name(s, "hola") == OK);
        space_destroy(s);
}

void test2_space_set_name() {
        Space *s = NULL;
        PRINT_TEST_RESULT(space_set_name(s, "hola") == ERROR);
}

void test3_space_set_name() {
        Space *s;
        s = space_create(5);
        PRINT_TEST_RESULT(space_set_name(s, NULL) == ERROR);
        space_destroy(s);
}

void test1_space_get_name() {
        Space *s;
        s = space_create(5);
        space_set_name(s, "hola");
        PRINT_TEST_RESULT(strcmp(space_get_name(s), "hola") == 0);
        space_destroy(s);
}

void test2_space_get_name() {
        Space *s = NULL;
        space_set_name(s, "hola");
        PRINT_TEST_RESULT(space_get_name(s) == NULL);
}

void test1_space_set_discovered() {
        Space *s = NULL;
        s = space_create(1);
        PRINT_TEST_RESULT(space_set_discovered(s, TRUE) == OK);
        space_destroy(s);
}

void test2_space_set_discovered() {
        Space *s = NULL;
        PRINT_TEST_RESULT(space_set_discovered(s, TRUE) == ERROR);
}

void test1_space_get_discovered() {
        Space *s = NULL;
        s = space_create(1);
        space_set_discovered(s, TRUE);
        PRINT_TEST_RESULT(space_get_discovered(s) == TRUE);
        space_destroy(s);
}

void test2_space_get_discovered() {
        Space *s = NULL;
        space_set_discovered(s, TRUE);
        PRINT_TEST_RESULT(space_get_discovered(s) == FALSE);
}

void test1_space_add_object() {
        Space *s = NULL;
        s = space_create(1);
        PRINT_TEST_RESULT(space_add_object(s, 3) == OK);
        space_destroy(s);
}

void test2_space_add_object() {
        Space *s = NULL;
        s = space_create(1);
        PRINT_TEST_RESULT(space_add_object(s, NO_ID) == ERROR);
        space_destroy(s);
}

void test3_space_add_object() {
        Space *s = NULL;
        PRINT_TEST_RESULT(space_add_object(s, 3) == ERROR);
}

void test1_space_del_object() {
        Space *s = NULL;
        s = space_create(1);
        space_add_object(s, 3);
        PRINT_TEST_RESULT(space_del_object(s, 3) == 3);
        space_destroy(s);
}

void test2_space_del_object() {
        Space *s = NULL;
        PRINT_TEST_RESULT(space_del_object(s, 3) == NO_ID);
}

void test3_space_del_object() {
        Space *s = NULL;
        space_add_object(s, 3);
        PRINT_TEST_RESULT(space_del_object(s, 3) == NO_ID);
}

void test1_space_set_gdesc() {
        Space *s = space_create(1);
        char gdesc[GDESC_LINES][LINE_LENGTH + 1] = {"Line1", "Line2", "Line3"};
        PRINT_TEST_RESULT(space_set_gdesc(s, gdesc) == OK);
        space_destroy(s);
}

void test2_space_set_gdesc() {
        Space *s = NULL;
        char gdesc[GDESC_LINES][LINE_LENGTH + 1] = {"Line1", "Line2", "Line3"};
        PRINT_TEST_RESULT(space_set_gdesc(s, gdesc) == ERROR);
}

void test3_space_set_gdesc() {
        Space *s = space_create(1);
        PRINT_TEST_RESULT(space_set_gdesc(s, NULL) == ERROR);
        space_destroy(s);
}

void test1_space_get_gdesc() {
        Space *s = NULL;
        char gdesc_aux[GDESC_LINES][LINE_LENGTH + 1] = {"ABC"};
        s = space_create(1);
        space_set_gdesc(s, gdesc_aux);
        space_set_discovered(s, TRUE);
        PRINT_TEST_RESULT(strcmp(space_get_gdesc(s, 0), "ABC") == 0);
        space_destroy(s);
}

void test2_space_get_gdesc() {
        Space *s = NULL;
        char gdesc_aux[GDESC_LINES][LINE_LENGTH + 1] = {"ABC"};
        s = space_create(1);
        space_set_gdesc(s, gdesc_aux);
        PRINT_TEST_RESULT(strcmp(space_get_gdesc(s, 1), "ABC") != 0);
        space_destroy(s);
}

void test1_space_get_num_objects() {
        Space *s = NULL;
        s = space_create(1);
        space_add_object(s, 3);
        space_add_object(s, 4);
        PRINT_TEST_RESULT(space_get_num_objects(s) == 2);
        space_destroy(s);
}

void test2_space_get_num_objects() {
        Space *s = NULL;
        space_add_object(s, 3);
        space_add_object(s, 4);
        PRINT_TEST_RESULT(space_get_num_objects(s) == 0);
        space_destroy(s);
}

void test1_space_has_object() {
        Space *s = NULL;
        s = space_create(1);
        space_add_object(s, 3);
        PRINT_TEST_RESULT(space_has_object(s, 3) == TRUE);
        space_destroy(s);
}

void test2_space_has_object() {
        Space *s = NULL;
        s = space_create(1);
        space_add_object(s, 3);
        PRINT_TEST_RESULT(space_has_object(s, 4) == FALSE);
        space_destroy(s);
}

void test3_space_has_object() {
        Space *s = NULL;
        space_add_object(s, 3);
        PRINT_TEST_RESULT(space_has_object(s, 3) == FALSE);
}

void test4_space_has_object() {
        Space *s = NULL;
        s = space_create(1);
        PRINT_TEST_RESULT(space_has_object(s, NO_ID) == FALSE);
        space_destroy(s);
}
/*
void test1_space_get_character_id() {
        Space *s = NULL;
        s = space_create(1);
        space_set_characters(s, NO_ID);
        PRINT_TEST_RESULT(space_get_character_id(s) == NO_ID);
        space_destroy(s);
}

void test2_space_get_character_id() {
        Space *s = NULL;
        space_set_characters(s, 3);
        PRINT_TEST_RESULT(space_get_character_id(s) == NO_ID);
}
*/
void test1_space_set_characters() {
        Space *s = NULL;
        s = space_create(1);
        PRINT_TEST_RESULT(space_set_characters(s, 4) == OK);
        space_destroy(s);
}

void test2_space_set_characters() {
        Space *s = NULL;
        PRINT_TEST_RESULT(space_set_characters(s, 4) == ERROR);
}

void test1_space_get_id_at_index() {
        Space *s = NULL;
        s = space_create(1);
        space_add_object(s, 4);
        PRINT_TEST_RESULT(space_get_id_at_index(s, 0) == 4);
        space_destroy(s);
}

void test2_space_get_id_at_index() {
        Space *s = NULL;
        PRINT_TEST_RESULT(space_get_id_at_index(s, 4) == NO_ID);
}
