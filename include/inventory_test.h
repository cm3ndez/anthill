/**
 * @brief It declares the tests for the inventory module
 *
 * @file inventory_test.h
 * Carlos Méndez
 * @version 0.0
 * @date 17-02-2025
 * @copyright GNU Public License
 */

#ifndef INVENTORY_TEST_H
#define INVENTORY_TEST_H

/**
 * @test Test inventory creation
 * @pre No parameters
 * @post Non NULL pointer to inventory
 */
void test1_inventory_create();

/**
 * @test Test inventory creation
 * @pre No parameters
 * @post Inventory_ID == Supplied Inventory ID
 */
void test2_inventory_create();

/**
 * @test Test inventory destruction
 * @pre Valid inventory
 * @post Output == OK
 */
void test1_inventory_destroy();

/**
 * @test Test inventory destruction
 * @pre NULL inventory
 * @post Output == OK
 */
void test2_inventory_destroy();

/**
 * @test Test inventory max objects getter
 * @pre Inventory created with max_objs = 5
 * @post Output == 5
 */
void test1_inventory_get_max_objs();

/**
 * @test Test inventory max objects getter with NULL inventory
 * @pre NULL inventory
 * @post Output == -1
 */
void test2_inventory_get_max_objs();

/**
 * @test Test inventory max objects setter
 * @pre Inventory created
 * @post Output == OK
 */
void test1_inventory_set_max_objs();

/**
 * @test Test inventory max objects setter with NULL inventory
 * @pre NULL inventory
 * @post Output == ERROR
 */
void test2_inventory_set_max_objs();

/**
 * @test Test get object ID at index
 * @pre Inventory with object id = 5 at index 0
 * @post Output == 5
 */
void test1_inventory_get_object_id_at_index();

/**
 * @test Test get object ID at index with NULL inventory
 * @pre NULL inventory
 * @post Output == NO_ID
 */
void test2_inventory_get_object_id_at_index();

/**
 * @test Test add object to inventory
 * @pre Valid inventory and valid object id
 * @post Output == OK
 */
void test1_inventory_add_object();

/**
 * @test Test add object to NULL inventory
 * @pre NULL inventory
 * @post Output == ERROR
 */
void test2_inventory_add_object();

/**
 * @test Test add NO_ID object to inventory
 * @pre Inventory created, object id == NO_ID
 * @post Output == ERROR
 */
void test3_inventory_add_object();

/**
 * @test Test add object exceeding max_objs
 * @pre Inventory with max_objs = 0
 * @post Output == ERROR
 */
void test4_inventory_add_object();

/**
 * @test Test delete object from inventory
 * @pre Inventory with object id = 5 added
 * @post Output == 5
 */
void test1_inventory_del_object();

/**
 * @test Test delete object from NULL inventory
 * @pre NULL inventory
 * @post Output == NO_ID
 */
void test2_inventory_del_object();

/**
 * @test Test if there is an object in the inventory
 * @pre Valid inventory and valid ID
 * @post Output == TRUE
 */
void test1_inventory_has_object();

/**
 * @test Test if there is an object in the inventory
 * @pre invalid ID
 * @post Output == FALSE
 */
void test2_inventory_has_object();

/**
 * @test Test if there is an object in the inventory
 * @pre invalid inventory
 * @post Output == FALSE
 */
void test3_inventory_has_object();

#endif