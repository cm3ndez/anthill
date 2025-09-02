/**
 * @brief It tests player module
 *
 * @file player_test.c
 * @author Jorge Pastor
 * @version 1.0
 * @date 22-03-2025
 * @copyright GNU Public License
 */

#include "player.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "player_test.h"
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
 * @def INITIAL_HEALTH
 * @brief Defines the initial health of the player
 */
#define INITIAL_HEALTH 5

/**
 * @brief Main function for PLAYER unit tests.
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
                printf("Running all test for module Player:\n");
        } else {
                test = atoi(argv[1]);
                all = 0;
                printf("Running test %d:\t", test);
                if (test < 1 && test > MAX_TESTS) {
                        printf("Error: unknown test %d\t", test);
                        exit(EXIT_SUCCESS);
                }
        }

        if (all || test == 1) test1_player_create();
        if (all || test == 2) test2_player_create();
        if (all || test == 3) test1_player_destroy();
        if (all || test == 4) test2_player_destroy();
        if (all || test == 5) test1_player_get_id();
        if (all || test == 6) test2_player_get_id();
        if (all || test == 7) test1_player_set_name();
        if (all || test == 8) test2_player_set_name();
        if (all || test == 9) test3_player_set_name();
        if (all || test == 10) test1_player_get_name();
        if (all || test == 11) test2_player_get_name();
        if (all || test == 12) test1_player_set_location();
        if (all || test == 13) test2_player_set_location();
        if (all || test == 14) test3_player_set_location();
        if (all || test == 15) test1_player_get_location();
        if (all || test == 16) test2_player_get_location();
        if (all || test == 17) test1_player_add_object();
        if (all || test == 18) test2_player_add_object();
        if (all || test == 19) test3_player_add_object();
        if (all || test == 20) test1_player_del_object();
        if (all || test == 21) test2_player_del_object();
        if (all || test == 22) test3_player_del_object();
        if (all || test == 23) test1_player_get_object_at_index();
        if (all || test == 24) test2_player_get_object_at_index();
        if (all || test == 25) test3_player_get_object_at_index();
        if (all || test == 26) test4_player_get_object_at_index();
        if (all || test == 27) test1_player_set_health();
        if (all || test == 28) test2_player_set_health();
        if (all || test == 29) test3_player_set_health();
        if (all || test == 30) test1_player_get_health();
        if (all || test == 31) test2_player_get_health();
        if (all || test == 32) test1_player_set_gdesc();
        if (all || test == 33) test2_player_set_gdesc();
        if (all || test == 34) test3_player_set_gdesc();
        if (all || test == 35) test1_player_get_gdesc();
        if (all || test == 36) test2_player_get_gdesc();
        if (all || test == 37) test1_player_set_backpack_size();
        if (all || test == 38) test2_player_set_backpack_size();
        if (all || test == 39) test3_player_set_backpack_size();
        if (all || test == 40) test1_player_set_damage();
        if (all || test == 41) test2_player_set_damage();
        if (all || test == 42) test1_player_get_damage();
        if (all || test == 43) test2_player_get_damage();
        PRINT_PASSED_PERCENTAGE;

        return EXIT_SUCCESS;
}

void test1_player_create() {
        int result;
        Player *p = NULL;
        p = player_create(5);
        result = p != NULL;
        PRINT_TEST_RESULT(result);
        player_destroy(p);
}

void test2_player_create() {
        Player *p = NULL;
        p = player_create(5);
        PRINT_TEST_RESULT(player_get_health(p) == 0);
        player_destroy(p);
}

void test1_player_destroy() {
        Player *p = NULL;
        p = player_create(5);
        PRINT_TEST_RESULT(player_destroy(p) == OK);
}

void test2_player_destroy() {
        Player *p = NULL;
        PRINT_TEST_RESULT(player_destroy(p) == OK);
}

void test1_player_get_id() {
        Player *p = NULL;
        p = player_create(5);
        PRINT_TEST_RESULT(player_get_id(p) == 5);
        player_destroy(p);
}

void test2_player_get_id() {
        Player *p = NULL;
        PRINT_TEST_RESULT(player_get_id(p) == NO_ID);
}

void test1_player_set_name() {
        Player *p = NULL;
        p = player_create(5);
        PRINT_TEST_RESULT(player_set_name(p, "ABC") == OK);
        player_destroy(p);
}

void test2_player_set_name() {
        Player *p = NULL;
        PRINT_TEST_RESULT(player_set_name(p, "ABC") == ERROR);
}

void test3_player_set_name() {
        Player *p = NULL;
        char *name = NULL;
        p = player_create(5);
        PRINT_TEST_RESULT(player_set_name(p, name) == ERROR);
        player_destroy(p);
}

void test1_player_get_name() {
        Player *p = NULL;
        p = player_create(5);
        player_set_name(p, "ABC");
        PRINT_TEST_RESULT((strcmp(player_get_name(p), "ABC")) == 0);
        player_destroy(p);
}

void test2_player_get_name() {
        Player *p = NULL;
        player_set_name(p, "ABC");
        PRINT_TEST_RESULT(player_get_name(p) == NULL);
}

void test1_player_set_location() {
        Player *p = NULL;
        p = player_create(5);
        PRINT_TEST_RESULT(player_set_location(p, 3) == OK);
        player_destroy(p);
}

void test2_player_set_location() {
        Player *p = NULL;
        PRINT_TEST_RESULT(player_set_location(p, 3) == ERROR);
}

void test3_player_set_location() {
        Player *p = NULL;
        p = player_create(5);
        PRINT_TEST_RESULT(player_set_location(p, NO_ID) == ERROR);
        player_destroy(p);
}

void test1_player_get_location() {
        Player *p = NULL;
        p = player_create(5);
        player_set_location(p, 3);
        PRINT_TEST_RESULT(player_get_location(p) == 3);
        player_destroy(p);
}

void test2_player_get_location() {
        Player *p = NULL;
        PRINT_TEST_RESULT(player_get_location(p) == NO_ID);
}

void test1_player_add_object() {
        Player *p = NULL;
        p = player_create(5);
        PRINT_TEST_RESULT(player_add_object(p, 4) == OK);
        player_destroy(p);
}

void test2_player_add_object() {
        Player *p = NULL;
        p = player_create(5);
        PRINT_TEST_RESULT(player_add_object(p, NO_ID) == ERROR);
        player_destroy(p);
}

void test3_player_add_object() {
        Player *p = NULL;
        PRINT_TEST_RESULT(player_add_object(p, 3) == ERROR);
}

void test1_player_del_object() {
        Player *p = NULL;
        p = player_create(5);
        if (player_add_object(p, 4) == OK) {
                PRINT_TEST_RESULT(player_del_object(p, 4) == 4);
        }
        player_destroy(p);
}

void test2_player_del_object() {
        Player *p = NULL;
        p = player_create(5);
        if (player_add_object(p, 4) == OK) {
                PRINT_TEST_RESULT(player_del_object(p, NO_ID) == NO_ID);
        }
        player_destroy(p);
}

void test3_player_del_object() {
        Player *p = NULL;
        player_add_object(p, 4);
        PRINT_TEST_RESULT(player_del_object(p, 4) == NO_ID);
        player_destroy(p);
}

void test1_player_get_object_at_index() {
        Player *p = NULL;
        p = player_create(5);
        player_add_object(p, 4);
        PRINT_TEST_RESULT(player_get_object_at_index(p, 0) == 4);
        player_destroy(p);
}

void test2_player_get_object_at_index() {
        Player *p = NULL;
        player_add_object(p, 4);
        PRINT_TEST_RESULT(player_get_object_at_index(p, 4) == NO_ID);
}

void test3_player_get_object_at_index() {
        Player *p = NULL;
        p = player_create(5);
        player_add_object(p, 4);
        PRINT_TEST_RESULT(player_get_object_at_index(p, -1) == NO_ID);
        player_destroy(p);
}

void test4_player_get_object_at_index() {
        Player *p = NULL;
        p = player_create(5);
        player_add_object(p, 4);
        PRINT_TEST_RESULT(player_get_object_at_index(p, 1) == NO_ID);
        player_destroy(p);
}

void test1_player_set_health() {
        Player *p = NULL;
        p = player_create(5);
        PRINT_TEST_RESULT(player_set_health(p, 3) == OK);
        player_destroy(p);
}

void test2_player_set_health() {
        Player *p = NULL;
        PRINT_TEST_RESULT(player_set_health(p, 3) == ERROR);
}

void test3_player_set_health() {
        Player *p = NULL;
        p = player_create(5);
        PRINT_TEST_RESULT(player_set_health(p, NO_ID) == ERROR);
        player_destroy(p);
}

void test1_player_get_health() {
        Player *p = NULL;
        p = player_create(5);
        player_set_health(p, 3);
        PRINT_TEST_RESULT(player_get_health(p) == 3);
        player_destroy(p);
}

void test2_player_get_health() {
        Player *p = NULL;
        PRINT_TEST_RESULT(player_get_health(p) == -1);
}

void test1_player_set_gdesc() {
        Player *p = NULL;
        p = player_create(5);
        PRINT_TEST_RESULT(player_set_gdesc(p, "ABC") == OK);
        player_destroy(p);
}

void test2_player_set_gdesc() {
        Player *p = NULL;
        PRINT_TEST_RESULT(player_set_gdesc(p, "ABC") == ERROR);
}

void test3_player_set_gdesc() {
        Player *p = NULL;
        char *gdesc = NULL;
        p = player_create(5);
        PRINT_TEST_RESULT(player_set_gdesc(p, gdesc) == ERROR);
        player_destroy(p);
}

void test1_player_get_gdesc() {
        Player *p = NULL;
        p = player_create(5);
        player_set_gdesc(p, "ABC");
        PRINT_TEST_RESULT(strcmp(player_get_gdesc(p), "   ABC") == 0);
        player_destroy(p);
}

void test2_player_get_gdesc() {
        Player *p = NULL;
        PRINT_TEST_RESULT(strcmp(player_get_gdesc(p), " ") == 0);
}

void test1_player_set_backpack_size() {
        Player *p = NULL;
        p = player_create(5);
        PRINT_TEST_RESULT(player_set_backpack_size(p, 4) == OK);
        player_destroy(p);
}

void test2_player_set_backpack_size() {
        Player *p = NULL;
        PRINT_TEST_RESULT(player_set_backpack_size(p, 4) == ERROR);
}

void test3_player_set_backpack_size() {
        Player *p = NULL;
        p = player_create(5);
        PRINT_TEST_RESULT(player_set_backpack_size(p, -1) == ERROR);
        player_destroy(p);
}

void test1_player_set_damage() {
        Player *p = NULL;
        p = player_create(5);
        PRINT_TEST_RESULT(player_set_damage(p, 3) == OK);
        player_destroy(p);
}

void test2_player_set_damage() {
        Player *p = NULL;
        int damage = -1;
        p = player_create(5);
        PRINT_TEST_RESULT(player_set_damage(p, damage) == ERROR);
        player_destroy(p);
}

void test1_player_get_damage() {
        Player *p = NULL;
        p = player_create(5);
        PRINT_TEST_RESULT(player_get_damage(p) == OK);
        player_destroy(p);
}

void test2_player_get_damage() {
        Player *p = NULL;
        PRINT_TEST_RESULT(player_get_damage(p) == -1);
}
