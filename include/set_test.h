/**
 * @brief It declares the tests for the set module
 *
 * @file set_test.h
 * @author Carlos Méndez
 * @version 1.0
 * @date 28-02-2025
 * @copyright GNU Public License
 */

#ifndef SET_TEST_H
#define SET_TEST_H

/**
 * @test Test set creation
 * @pre No parameters
 * @post Non NULL pointer to set
 */
void test1_set_create();

/**
 * @test Test set creation
 * @pre No parameters
 * @post Set is empty
 */
void test2_set_create();

/**
 * @test Test function for retrieving number of IDs in a set
 * @pre NULL set
 * @post Output == -1
 */
void test1_set_get_nIds();

/**
 * @test Test function for retrieving number of IDs in a set
 * @pre Set with one ID
 * @post Output == 1
 */
void test2_set_get_nIds();

/**
 * @test Test function for adding an ID to a set
 * @pre Valid ID
 * @post Output == OK
 */
void test1_set_add();

/**
 * @test Test function for adding an invalid ID to a set
 * @pre ID == NO_ID
 * @post Output == ERROR
 */
void test2_set_add();

/**
 * @test Test function for adding IDs to a set until full
 * @pre Set with MAX_IDS elements
 * @post Output == ERROR
 */
void test3_set_add();

/**
 * @test Test function for adding to a NULL set
 * @pre NULL set
 * @post Output == ERROR
 */
void test4_set_add();

/**
 * @test Test function for deleting an ID from a set
 * @pre Set contains the ID
 * @post ID is removed, Output == OK
 */
void test1_set_del();

/**
 * @test Test function for deleting an ID from a set
 * @pre Set contains the ID
 * @post ID no longer present, Output == OK
 */
void test2_set_del();

/**
 * @test Test function for deleting an invalid ID from a set
 * @pre ID == NO_ID
 * @post Output == ERROR
 */
void test3_set_del();

/**
 * @test Test function for deleting an ID from a NULL set
 * @pre NULL set
 * @post Output == ERROR
 */
void test4_set_del();

/**
 * @test Test function for deleting a non-existent ID
 * @pre ID not in set
 * @post Output == OK
 */
void test5_set_del();

/**
 * @test Test function for checking if an object or character exists in set
 * @pre ID exists in set
 * @post Output == TRUE
 */
void test1_set_has();

/**
 * @test Test function for checking if an object or character exists in set
 * @pre ID does not exist in set
 * @post Output == FALSE
 */
void test2_set_has();

/**
 * @test Test function for checking if an object or character exists in set
 * @pre Set is NULL
 * @post Output == FALSE
 */
void test3_set_has();

/**
 * @test Test function for checking if an object or character exists in set
 * @pre ID is NO_ID
 * @post Output == FALSE
 */
void test4_set_has();

/**
 * @test Test function for checking if an object or character exists in set
 * @pre Set is empty
 * @post Output == FALSE
 */
void test5_set_has();

/**
 * @test Test function for getting and ID given its position
 * @pre ID exists in set
 * @post Output == ID
 */
void test1_set_get_id_at_index();

/**
 * @test Test function for getting and ID given its position
 * @pre NULL set
 * @post Output == -1
 */
void test2_set_get_id_at_index();

/**
 * @test Test function for getting and ID given its position
 * @pre Position given is higher than the number of ids in the set
 * @post Output == -1
 */
void test3_set_get_id_at_index();

/**
 * @test Test function for getting and ID given its position
 * @pre Position given is negati
 * @post Output == -1
 */
void test4_set_get_id_at_index();

#endif
