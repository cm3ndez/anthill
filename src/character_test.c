/**
 * @brief It tests character module
 *
 * @file character_test.c
 * Carlos Méndez
 * @version 0.0
 * @date 17-02-2025
 * @copyright GNU Public License
 */

#include "character.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "character_test.h"
#include "test.h"

/**
 * @def MAX_TESTS
 * @brief Defines the number of tests
 */
#define MAX_TESTS 50

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
                printf("Running all test for module Character:\n");
        } else {
                test = atoi(argv[1]);
                all = 0;
                printf("Running test %d:\t", test);
                if (test < 1 && test > MAX_TESTS) {
                        printf("Error: unknown test %d\t", test);
                        exit(EXIT_SUCCESS);
                }
        }

        if (all || test == 1) test1_character_create();
        if (all || test == 2) test2_character_create();
        if (all || test == 3) test1_character_destroy();
        if (all || test == 4) test2_character_destroy();
        if (all || test == 5) test1_character_set_friendly();
        if (all || test == 6) test2_character_set_friendly();
        if (all || test == 7) test1_character_get_friendly();
        if (all || test == 8) test2_character_get_friendly();
        if (all || test == 9) test1_character_set_health();
        if (all || test == 10) test2_character_set_health();
        if (all || test == 11) test1_character_get_health();
        if (all || test == 12) test2_character_get_health();
        if (all || test == 13) test1_character_set_gdesc();
        if (all || test == 14) test2_character_set_gdesc();
        if (all || test == 15) test3_character_set_gdesc();
        if (all || test == 16) test1_character_get_gdesc();
        if (all || test == 17) test2_character_get_gdesc();
        if (all || test == 18) test1_character_get_id();
        if (all || test == 19) test2_character_get_id();
        if (all || test == 20) test1_character_set_name();
        if (all || test == 21) test2_character_set_name();
        if (all || test == 22) test3_character_set_name();
        if (all || test == 23) test1_character_get_name();
        if (all || test == 24) test2_character_get_name();
        if (all || test == 25) test1_character_set_message();
        if (all || test == 26) test2_character_set_message();
        if (all || test == 27) test3_character_set_message();
        if (all || test == 28) test1_character_get_message();
        if (all || test == 29) test2_character_get_message();
        if (all || test == 30) test1_character_set_following();
        if (all || test == 31) test2_character_set_following();
        if (all || test == 32) test1_character_get_following();
        if (all || test == 33) test2_character_get_following();

        PRINT_PASSED_PERCENTAGE;

        return EXIT_SUCCESS;
}

void test1_character_create() {
        int result;
        Character *c = NULL;
        c = character_create(5);
        result = c != NULL;
        PRINT_TEST_RESULT(result);
        character_destroy(c);
}

void test2_character_create() {
        Character *c = NULL;
        c = character_create(4);
        PRINT_TEST_RESULT(character_get_id(c) == 4);
        character_destroy(c);
}

void test1_character_destroy() {
        Character *c;
        c = character_create(5);
        PRINT_TEST_RESULT(character_destroy(c) == OK);
}

void test2_character_destroy() {
        Character *c = NULL;
        PRINT_TEST_RESULT(character_destroy(c) == OK);
}

void test1_character_set_friendly() {
        Character *c = NULL;
        Bool friendly = TRUE;
        c = character_create(25);
        character_set_friendly(c, friendly);
        PRINT_TEST_RESULT(character_get_friendly(c) == TRUE);
        character_destroy(c);
}

void test2_character_set_friendly() {
        Character *c = NULL;
        Bool friendly = TRUE;
        character_set_friendly(c, friendly);
        PRINT_TEST_RESULT(character_get_friendly(c) == TRUE);
}

void test1_character_get_friendly() {
        Character *c = NULL;
        Bool friendly = TRUE;
        c = character_create(25);
        character_set_friendly(c, friendly);
        PRINT_TEST_RESULT(character_get_friendly(c) == TRUE);
        character_destroy(c);
}

void test2_character_get_friendly() {
        Character *c = NULL;
        Bool friendly = TRUE;
        character_set_friendly(c, friendly);
        PRINT_TEST_RESULT(character_get_friendly(c) == TRUE);
}

void test1_character_set_health() {
        Character *c = NULL;
        c = character_create(25);
        PRINT_TEST_RESULT(character_set_health(c, 5) == OK);
        character_destroy(c);
}

void test2_character_set_health() {
        Character *c = NULL;
        PRINT_TEST_RESULT(character_set_health(c, 5) == ERROR);
}

void test1_character_get_health() {
        Character *c = NULL;
        c = character_create(25);
        character_set_health(c, 5);
        PRINT_TEST_RESULT(character_get_health(c) == 5);
        character_destroy(c);
}

void test2_character_get_health() {
        Character *c = NULL;
        character_set_health(c, 5);
        PRINT_TEST_RESULT(character_get_health(c) == -1);
}

void test1_character_set_gdesc() {
        Character *c = NULL;
        char gdesc[50] = "ABC";
        c = character_create(25);
        PRINT_TEST_RESULT(character_set_gdesc(c, gdesc) == OK);
        character_destroy(c);
}

void test2_character_set_gdesc() {
        Character *c = NULL;
        char gdesc[50] = "ABC";
        PRINT_TEST_RESULT(character_set_gdesc(c, gdesc) == ERROR);
}

void test3_character_set_gdesc() {
        Character *c = NULL;
        char *gdesc = NULL;
        c = character_create(25);
        PRINT_TEST_RESULT(character_set_gdesc(c, gdesc) == ERROR);
        character_destroy(c);
}

void test1_character_get_gdesc() {
        Character *c = NULL;
        char gdesc[50] = "ABC";
        c = character_create(25);
        character_set_gdesc(c, gdesc);
        PRINT_TEST_RESULT((strcmp((char *)character_get_gdesc(c), gdesc)) == 0);
        character_destroy(c);
}

void test2_character_get_gdesc() {
        Character *c = NULL;
        char gdesc[50] = "ABC";
        character_set_gdesc(c, gdesc);
        PRINT_TEST_RESULT(character_get_gdesc(c) == NULL);
}

void test1_character_get_id() {
        Character *c = NULL;
        c = character_create(25);
        PRINT_TEST_RESULT(character_get_id(c) == 25);
        character_destroy(c);
}

void test2_character_get_id() {
        Character *c = NULL;
        PRINT_TEST_RESULT(character_get_id(c) == NO_ID);
}

void test1_character_set_name() {
        Character *c = NULL;
        c = character_create(25);
        PRINT_TEST_RESULT(character_set_name(c, "hola") == OK);
        character_destroy(c);
}

void test2_character_set_name() {
        Character *c = NULL;
        PRINT_TEST_RESULT(character_set_name(c, "hola") == ERROR);
}

void test3_character_set_name() {
        Character *c = NULL;
        c = character_create(25);
        PRINT_TEST_RESULT(character_set_name(c, NULL) == ERROR);
        character_destroy(c);
}

void test1_character_get_name() {
        Character *c = NULL;
        c = character_create(5);
        character_set_name(c, "hola");
        PRINT_TEST_RESULT(strcmp(character_get_name(c), "hola") == 0);
        character_destroy(c);
}

void test2_character_get_name() {
        Character *c = NULL;
        c = character_create(5);
        character_set_name(c, "hola");
        PRINT_TEST_RESULT(strcmp(character_get_name(c), "hola") == 0);
        character_destroy(c);
}

void test1_character_set_message() {
        Character *c = NULL;
        c = character_create(25);
        PRINT_TEST_RESULT(character_set_message(c, "hola") == OK);
        character_destroy(c);
}

void test2_character_set_message() {
        Character *c = NULL;
        PRINT_TEST_RESULT(character_set_message(c, "hola") == ERROR);
}

void test3_character_set_message() {
        Character *c = NULL;
        c = character_create(25);
        PRINT_TEST_RESULT(character_set_message(c, NULL) == ERROR);
        character_destroy(c);
}

void test1_character_get_message() {
        Character *c = NULL;
        c = character_create(5);
        character_set_message(c, "hola");
        PRINT_TEST_RESULT(strcmp(character_get_message(c), "hola") == 0);
        character_destroy(c);
}

void test2_character_get_message() {
        Character *c = NULL;
        character_set_message(c, "hola");
        PRINT_TEST_RESULT(strcmp(character_get_message(c), "hola") != 0);
}

void test1_character_set_following() {
        Character *c = NULL;
        c = character_create(25);
        PRINT_TEST_RESULT(character_set_following(c, TRUE) == OK);
        character_destroy(c);
}

void test2_character_set_following() {
        Character *c = NULL;
        PRINT_TEST_RESULT(character_set_health(c, 5) == ERROR);
}

void test1_character_get_following() {
        Character *c = NULL;
        c = character_create(25);
        character_set_following(c, 11);
        PRINT_TEST_RESULT(character_get_following(c) == 11);
        character_destroy(c);
}

void test2_character_get_following() {
        Character *c = NULL;
        character_set_following(c, 5);
        PRINT_TEST_RESULT(character_get_following(c) == NO_ID);
}