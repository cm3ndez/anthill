/**
 * @brief It declares the tests for the object module
 *
 * @file object_test.h
 * @author Jorge Pastor
 * @version 1.0
 * @date 25-03-2025
 * @copyright GNU Public License
 */

#ifndef OBJECT_TEST_H
#define OBJECT_TEST_H

/**
 * @test Tests object creation
 * @pre No parameters
 * @post Non NULL pointer to object (1) or NULL pointer (0)
 */
void test1_object_create();

/**
 * @test Tests object creation
 * @pre No parameters
 * @post Object_ID == Supplied Object ID
 */
void test2_object_create();

/**
 * @test Test function for destroying an object
 * @pre pointer to the object
 * @post Output==OK
 */
void test1_object_destroy();

/**
 * @test Test function for destroying an object
 * @pre NULL object
 * @post Output==ERROR
 */
void test2_object_destroy();

/**
 * @test Test function for getting the id of an object
 * @pre pointer to the objectd
 * @post Output==10
 */
void test1_object_get_id();

/**
 * @test Test function for getting the id of an object
 * @pre NULL object
 * @post Output==NO_ID
 */
void test2_object_get_id();

/**
 * @test Test function for setting the name of an object
 * @pre pointer to the object
 * @post Output==OK
 */
void test1_object_set_name();

/**
 * @test Test function for setting the name of an object
 * @pre NULL object
 * @post Output==ERROR
 */
void test2_object_set_name();

/**
 * @test Test function for getting the name of an object
 * @pre pointer to the object
 * @post Output==Crumb
 */
void test1_object_get_name();

/**
 * @test Test function for getting the name of an object
 * @pre  NULL object
 * @post Output== NULL
 */
void test2_object_get_name();

/**
 * @test Test function for setting the description of an object
 * @pre pointer to the object
 * @post Output==OK
 */
void test1_object_set_description();

/**
 * @test Test function for setting the description of an object
 * @pre NULL object
 * @post Output== ERROR
 */
void test2_object_set_description();

/**
 * @test Test function for getting the description of an object
 * @pre pointer to the object
 * @post Output== NULL"ABC"
 */
void test1_object_get_description();

/**
 * @test Test function for getting the description of an object
 * @pre NULL object
 * @post Output== NULL
 */
void test2_object_get_description();

/**
 * @test Test function for setting the health of an object
 * @pre Object created with ID 1
 * @post Output == OK
 */
void test1_object_set_health();

/**
 * @test Test function for setting the health of an object
 * @pre NULL object
 * @post Output == ERROR
 */
void test2_object_set_health();

/**
 * @test Test function for getting the health of an object
 * @pre Object created with ID 10 (default health = 0)
 * @post Output == 0
 */
void test1_object_get_health();

/**
 * @test Test function for getting the health of an object
 * @pre NULL object
 * @post Output == -1
 */
void test2_object_get_health();

/**
 * @test Test function for setting the movable attribute of an object
 * @pre Object created with ID 1
 * @post Output == OK
 */
void test1_object_set_movable();

/**
 * @test Test function for setting the movable attribute of an object
 * @pre NULL object
 * @post Output == ERROR
 */
void test2_object_set_movable();

/**
 * @test Test function for getting the movable attribute of an object
 * @pre Object created with ID 10 (default movable = FALSE)
 * @post Output == FALSE
 */
void test1_object_get_movable();

/**
 * @test Test function for getting the movable attribute of an object
 * @pre NULL object
 * @post Output == FALSE
 */
void test2_object_get_movable();

/**
 * @test Test function for setting the open attribute of an object
 * @pre Object created with ID 1
 * @post Output == OK
 */
void test1_object_set_open();

/**
 * @test Test function for setting the open attribute of an object
 * @pre NULL object
 * @post Output == ERROR
 */
void test2_object_set_open();

/**
 * @test Test function for getting the open attribute of an object
 * @pre Object created with ID 10 (default open = NO_ID)
 * @post Output == NO_ID
 */
void test1_object_get_open();

/**
 * @test Test function for getting the open attribute of an object
 * @pre NULL object
 * @post Output == NO_ID
 */
void test2_object_get_open();

/**
 * @test Test function for setting the dependency of an object
 * @pre Object created with ID 1
 * @post Output == OK
 */
void test1_object_set_dependency();

/**
 * @test Test function for setting the dependency of an object
 * @pre NULL object
 * @post Output == ERROR
 */
void test2_object_set_dependency();

/**
 * @test Test function for getting the dependency of an object
 * @pre Object created with ID 10 (default dependency = NO_ID)
 * @post Output == NO_ID
 */
void test1_object_get_dependency();

/**
 * @test Test function for getting the dependency of an object
 * @pre NULL object
 * @post Output == NO_ID
 */
void test2_object_get_dependency();

#endif
