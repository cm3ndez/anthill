/**
 * @brief It tests the inventory module
 *
 * @file inventory_test.c
 * @author Carlos Méndez
 * @version 1.0
 * @date 25-03-2025
 * @copyright GNU Public License
 */

#include "inventory.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "inventory_test.h"
#include "test.h"

/**
 * @def MAX_TESTS
 * @brief Defines the number of tests
 */
#define MAX_TESTS 50

/**
 * @def MAX_OBJECTS
 * @brief Defines the maximum amount of objects
 */
#define MAX_OBJECTS 25

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
                printf("Running all test for module Inventory:\n");
        } else {
                test = atoi(argv[1]);
                all = 0;
                printf("Running test %d:\t", test);
                if (test < 1 && test > MAX_TESTS) {
                        printf("Error: unknown test %d\t", test);
                        exit(EXIT_SUCCESS);
                }
        }

        if (all || test == 1) test1_inventory_create();
        if (all || test == 2) test2_inventory_create();
        if (all || test == 3) test1_inventory_destroy();
        if (all || test == 4) test2_inventory_destroy();
        if (all || test == 5) test1_inventory_get_max_objs();
        if (all || test == 6) test2_inventory_get_max_objs();
        if (all || test == 7) test1_inventory_set_max_objs();
        if (all || test == 8) test2_inventory_set_max_objs();
        if (all || test == 9) test1_inventory_get_object_id_at_index();
        if (all || test == 10) test2_inventory_get_object_id_at_index();
        if (all || test == 11) test1_inventory_add_object();
        if (all || test == 12) test2_inventory_add_object();
        if (all || test == 13) test3_inventory_add_object();
        if (all || test == 14) test4_inventory_add_object();
        if (all || test == 15) test1_inventory_del_object();
        if (all || test == 16) test2_inventory_del_object();
        if (all || test == 17) test1_inventory_has_object();
        if (all || test == 18) test2_inventory_has_object();
        if (all || test == 19) test3_inventory_has_object();


        PRINT_PASSED_PERCENTAGE;

        return EXIT_SUCCESS;
}

void test1_inventory_create() {
        int result;
        Inventory *i = NULL;
        i = inventory_create();
        result = i != NULL;
        PRINT_TEST_RESULT(result);
        inventory_destroy(i);
}

void test2_inventory_create() {
        Inventory *i = NULL;
        i = inventory_create();
        PRINT_TEST_RESULT(inventory_get_max_objs(i) == MAX_OBJECTS);
        inventory_destroy(i);
}

void test1_inventory_destroy() {
        Inventory *i = NULL;
        i = inventory_create();
        PRINT_TEST_RESULT(inventory_destroy(i) == OK);
}

void test2_inventory_destroy() {
        Inventory *i = NULL;
        i = inventory_create();
        PRINT_TEST_RESULT(inventory_destroy(i) == OK);
}

void test1_inventory_get_max_objs() {
        Inventory *i = NULL;
        i = inventory_create();
        inventory_set_max_objs(i, 5);
        PRINT_TEST_RESULT(inventory_get_max_objs(i) == 5);
        inventory_destroy(i);
}

void test2_inventory_get_max_objs() {
        Inventory *i = NULL;
        inventory_set_max_objs(i, 5);
        PRINT_TEST_RESULT(inventory_get_max_objs(i) == -1);
}

void test1_inventory_set_max_objs() {
        Inventory *i = NULL;
        i = inventory_create();
        PRINT_TEST_RESULT(inventory_set_max_objs(i, 5) == OK);
        inventory_destroy(i);
}

void test2_inventory_set_max_objs() {
        Inventory *i = NULL;
        inventory_set_max_objs(i, 5);
        PRINT_TEST_RESULT(inventory_set_max_objs(i, 5) == ERROR);
}

void test1_inventory_get_object_id_at_index() {
        Inventory *i = NULL;
        i = inventory_create();
        inventory_set_max_objs(i, 5);
        inventory_add_object(i, 5);
        PRINT_TEST_RESULT(inventory_get_object_id_at_index(i, 0) == 5); /*Estña devolviendo NO_ID*/
        inventory_destroy(i);
}

void test2_inventory_get_object_id_at_index() {
        Inventory *i = NULL;
        inventory_add_object(i, 5);
        PRINT_TEST_RESULT(inventory_get_object_id_at_index(i, 0) == NO_ID);
}

void test1_inventory_add_object() {
        Inventory *i = NULL;
        i = inventory_create();
        inventory_set_max_objs(i, 5);
        PRINT_TEST_RESULT(inventory_add_object(i, 5) == OK); /*Está devolviendo ERROR*/
        inventory_destroy(i);
}

void test2_inventory_add_object() {
        Inventory *i = NULL;
        inventory_set_max_objs(i, 5);
        PRINT_TEST_RESULT(inventory_add_object(i, 5) == ERROR);
}

void test3_inventory_add_object() {
        Inventory *i = NULL;
        i = inventory_create();
        inventory_set_max_objs(i, 5);
        PRINT_TEST_RESULT(inventory_add_object(i, NO_ID) == ERROR);
        inventory_destroy(i);
}

void test4_inventory_add_object() {
        Inventory *i = NULL;
        i = inventory_create();
        inventory_set_max_objs(i, 0);
        PRINT_TEST_RESULT(inventory_add_object(i, 5) == ERROR);
        inventory_destroy(i);
}

void test1_inventory_del_object() {
        Inventory *i = NULL;
        i = inventory_create();
        inventory_add_object(i, 5);
        PRINT_TEST_RESULT(inventory_del_object(i, 5) == 5); /*Está devolviendo NO_ID*/
        inventory_destroy(i);
}

void test2_inventory_del_object() {
        Inventory *i = NULL;
        inventory_add_object(i, 5);
        PRINT_TEST_RESULT(inventory_del_object(i, 5) == NO_ID);
}

void test1_inventory_has_object(){
        Inventory *i = NULL;
        i = inventory_create();
        inventory_add_object(i, 5);
        PRINT_TEST_RESULT(inventory_has_object(i, 5) == TRUE);
        inventory_destroy(i);
}

void test2_inventory_has_object(){
        Inventory *i = NULL;
        i = inventory_create();
        inventory_add_object(i, NO_ID);
        PRINT_TEST_RESULT(inventory_has_object(i, NO_ID) == FALSE);
        inventory_destroy(i);
}

void test3_inventory_has_object(){
        Inventory *i = NULL;
        inventory_add_object(i, 5);
        PRINT_TEST_RESULT(inventory_has_object(i, 5) == FALSE);
}
