/**
 * @brief It declares the tests for the space module
 *
 * @file space_test.h
 * @author Carlos Méndez and Jorge Pastor
 * @version 0.0
 * @date 24-03-2025
 * @copyright GNU Public License
 */

#ifndef SPACE_TEST_H
#define SPACE_TEST_H

/**
 * @test Test space creation
 * @pre Space ID
 * @post Non NULL pointer to space
 */
void test1_space_create();

/**
 * @test Test space creation
 * @pre Space ID
 * @post Space_ID == Supplied Space Id
 */
void test2_space_create();

/**
 * @test Test function for space destruction
 * @pre Valid space
 * @post Output == OK
 */
void test1_space_destroy();

/**
 * @test Test function for space destruction
 * @pre NULL space
 * @post Output == OK
 */
void test2_space_destroy();

/**
 * @test Test function for getting space ID
 * @pre Valid space
 * @post Output == space ID
 */
void test1_space_get_id();

/**
 * @test Test function for getting space ID
 * @pre NULL space
 * @post Output == NO_ID
 */
void test2_space_get_id();

/**
 * @test Test function for space_name setting
 * @pre String with space name
 * @post Ouput==OK
 */
void test1_space_set_name();

/**
 * @test Test function for space_name setting
 * @pre pointer to space = NULL
 * @post Output==ERROR
 */
void test2_space_set_name();

/**
 * @test Test function for space_name setting
 * @pre name = NULL
 * @post Output==ERROR
 */
void test3_space_set_name();

/**
 * @test Test function for getting space name
 * @pre Valid space
 * @post Output == space name
 */
void test1_space_get_name();

/**
 * @test Test function for getting space name
 * @pre NULL space
 * @post Output == NULL
 */
void test2_space_get_name();

/**
 * @test Test function for setting space discovered field
 * @pre Valid space
 * @post Output == OK
 */
void test1_space_set_discovered();

/**
 * @test Test function for setting space discovered field
 * @pre NULL space
 * @post Output == ERROR
 */
void test2_space_set_discovered();

/**
 * @test Test function for getting space discovered field
 * @pre Valid space
 * @post Output == TRUE
 */
void test1_space_get_discovered();

/**
 * @test Test function for getting space discovered field
 * @pre NULL space
 * @post Output == FALSE
 */
void test2_space_get_discovered();

/**
 * @test Test function for adding an object to a space
 * @pre Valid space and object ID
 * @post Output == OK
 */
void test1_space_add_object();

/**
 * @test Test function for adding an object to a space
 * @pre NULL space
 * @post Output == ERROR
 */
void test2_space_add_object();

/**
 * @test Test function for adding an object to a space
 * @pre ID == NO_ID
 * @post Output == ERROR
 */
void test3_space_add_object();

/**
 * @test Test function for removing an object from a space
 * @pre Object exists in space
 * @post Output == OK
 */
void test1_space_del_object();

/**
 * @test Test function for removing an object from a space
 * @pre NULL space
 * @post Output == ERROR
 */
void test2_space_del_object();

/**
 * @test Test function for removing an object from a space
 * @pre Object does not exist in space
 * @post Output == ERROR
 */
void test3_space_del_object();

/**
 * @test Test function for setting graphical description
 * @pre Valid space and graphical description
 * @post Output == OK
 */
void test1_space_set_gdesc();

/**
 * @test Test function for setting graphical description
 * @pre NULL space
 * @post Output == ERROR
 */
void test2_space_set_gdesc();

/**
 * @test Test function for setting graphical description
 * @pre NULL graphical description
 * @post Output == ERROR
 */
void test3_space_set_gdesc();

/**
 * @test Test function for getting graphical description
 * @pre Valid space with graphical description set
 * @post Output == correct graphical description
 */
void test1_space_get_gdesc();

/**
 * @test Test function for getting graphical description
 * @pre NULL space
 * @post Output == EMPTY_ROW
 */
void test2_space_get_gdesc();

/**
 * @test Test function for getting the number of objects in a space
 * @pre Valid space with objects
 * @post Output == correct number of objects
 */
void test1_space_get_num_objects();

/**
 * @test Test function for getting the number of objects in a space
 * @pre NULL space
 * @post Output == 0
 */
void test2_space_get_num_objects();

/**
 * @test Test function for checking object presence in space
 * @pre Object exists in space
 * @post Output == TRUE
 */
void test1_space_has_object();

/**
 * @test Test function for checking object presence in space
 * @pre Object does not exist in space
 * @post Output == FALSE
 */
void test2_space_has_object();

/**
 * @test Test function for checking object presence in space
 * @pre NULL space
 * @post Output == FALSE
 */
void test3_space_has_object();

/**
 * @test Test function for checking object presence in space
 * @pre ID == NO_ID
 * @post Output == FALSE
 */
void test4_space_has_object();

/**
 * @test Test function for setting character ID in space
 * @pre Valid space and character ID
 * @post Output == OK
 */
void test1_space_set_characters();

/**
 * @test Test function for setting character ID in space
 * @pre NULL space
 * @post Output == ERROR
 */
void test2_space_set_characters();

/**
 * @test Test function for getting ID at a specific index
 * @pre Valid space with objects
 * @post Output == correct ID
 */
void test1_space_get_id_at_index();

/**
 * @test Test function for getting ID at a specific index
 * @pre NULL space
 * @post Output == NO_ID
 */
void test2_space_get_id_at_index();
#endif
