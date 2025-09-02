/**
 * @brief It declares the tests for the player module
 *
 * @file player_test.h
 * @author Jorge Pastor
 * @version 1.0
 * @date 22-03-2025
 * @copyright GNU Public License
 */

#ifndef PLAYER_TEST_H
#define PLAYER_TEST_H

/**
 * @test Test player creation
 * @pre No parameters
 * @post Non NULL pointer to player
 */
void test1_player_create();

/**
 * @test Test player creation
 * @pre No parameters
 * @post Player is empty
 */
void test2_player_create();

/**
 * @test Test player destruction
 * @pre Valid player
 * @post Player is empty
 */
void test1_player_destroy();

/**
 * @test Test player destuction
 * @pre NULL player
 * @post Player is empty
 */
void test2_player_destroy();

/**
 * @test Test function for getting the ID of a player
 * @pre Valid player
 * @post Output == player ID
 */
void test1_player_get_id();

/**
 * @test Test function for getting the ID of a NULL player
 * @pre NULL player
 * @post Output == NO_ID
 */
void test2_player_get_id();

/**
 * @test Test function for setting the name of a player
 * @pre Valid player and valid name
 * @post Output == OK
 */
void test1_player_set_name();

/**
 * @test Test function for setting the name of a NULL player
 * @pre NULL player
 * @post Output == ERROR
 */
void test2_player_set_name();

/**
 * @test Test function for setting a NULL name to a player
 * @pre Valid player, NULL name
 * @post Output == ERROR
 */
void test3_player_set_name();

/**
 * @test Test function for getting the name of a player
 * @pre Valid player with assigned name
 * @post Output == assigned name
 */
void test1_player_get_name();

/**
 * @test Test function for getting the name of a NULL player
 * @pre NULL player
 * @post Output == NULL
 */
void test2_player_get_name();

/**
 * @test Test function for setting the location of a player
 * @pre Valid player and valid location ID
 * @post Output == OK
 */
void test1_player_set_location();

/**
 * @test Test function for setting the location of a NULL player
 * @pre NULL player
 * @post Output == ERROR
 */
void test2_player_set_location();

/**
 * @test Test function for setting an invalid location ID to a player
 * @pre Valid player, invalid location ID (NO_ID)
 * @post Output == ERROR
 */
void test3_player_set_location();

/**
 * @test Test function for getting the location of a player
 * @pre Valid player with assigned location
 * @post Output == location ID
 */
void test1_player_get_location();

/**
 * @test Test function for getting the location of a NULL player
 * @pre NULL player
 * @post Output == NO_ID
 */
void test2_player_get_location();

/**
 * @test Test function for adding an ID to a player
 * @pre Valid ID
 * @post Output == OK
 */
void test1_player_add_object();

/**
 * @test Test function for adding an invalid ID to a player
 * @pre ID == NO_ID
 * @post Output == ERROR
 */
void test2_player_add_object();

/**
 * @test Test function for adding IDs to a player until full
 * @pre Player with MAX_IDS elements
 * @post Output == ERROR
 */
void test3_player_add_object();

/**
 * @test Test function for deleting an ID from a player
 * @pre Player contains the ID
 * @post ID is removed, Output == OK
 */
void test1_player_del_object();

/**
 * @test Test function for deleting an ID from a player
 * @pre Player contains the ID
 * @post ID no longer present, Output == OK
 */
void test2_player_del_object();

/**
 * @test Test function for deleting an invalid ID from a player
 * @pre ID == NO_ID
 * @post Output == ERROR
 */
void test3_player_del_object();

/**
 * @test Test function for getting and ID given its position
 * @pre ID exists in player
 * @post Output == ID
 */
void test1_player_get_object_at_index();

/**
 * @test Test function for getting and ID given its position
 * @pre NULL player
 * @post Output == -1
 */
void test2_player_get_object_at_index();

/**
 * @test Test function for getting and ID given its position
 * @pre Position given is higher than the number of ids in the player
 * @post Output == -1
 */
void test3_player_get_object_at_index();

/**
 * @test Test function for getting and ID given its position
 * @pre Position given is negati
 * @post Output == -1
 */
void test4_player_get_object_at_index();

/**
 * @test Test function for setting the health of a player
 * @pre Valid player and valid health value
 * @post Output == OK
 */
void test1_player_set_health();

/**
 * @test Test function for setting the health of a NULL player
 * @pre NULL player
 * @post Output == ERROR
 */
void test2_player_set_health();

/**
 * @test Test function for setting an invalid health value to a player
 * @pre Valid player, invalid health value (NO_ID)
 * @post Output == ERROR
 */
void test3_player_set_health();

/**
 * @test Test function for getting the health of a player
 * @pre Valid player with assigned health value
 * @post Output == health value
 */
void test1_player_get_health();

/**
 * @test Test function for getting the health of a NULL player
 * @pre NULL player
 * @post Output == -1
 */
void test2_player_get_health();

/**
 * @test Test function for setting the graphical description of a player
 * @pre Valid player and valid description
 * @post Output == OK
 */
void test1_player_set_gdesc();

/**
 * @test Test function for setting the graphical description of a NULL player
 * @pre NULL player
 * @post Output == ERROR
 */
void test2_player_set_gdesc();

/**
 * @test Test function for setting a NULL graphical description to a player
 * @pre Valid player, NULL description
 * @post Output == ERROR
 */
void test3_player_set_gdesc();

/**
 * @test Test function for getting the graphical description of a player
 * @pre Valid player with assigned description
 * @post Output == assigned description
 */
void test1_player_get_gdesc();

/**
 * @test Test function for getting the graphical description of a NULL player
 * @pre NULL player
 * @post Output == default empty description
 */
void test2_player_get_gdesc();

/**
 * @test Test function for setting the backpack size of a player
 * @pre Valid player and valid size
 * @post Output == OK
 */
void test1_player_set_backpack_size();

/**
 * @test Test function for setting the backpack size of a NULL player
 * @pre NULL player
 * @post Output == ERROR
 */
void test2_player_set_backpack_size();

/**
 * @test Test function for setting an invalid backpack size to a player
 * @pre Valid player, invalid size (negative value)
 * @post Output == ERROR
 */
void test3_player_set_backpack_size();

/**
 * @test Test function for setting damage
 * @pre Valid player, valid damage
 * @post Output == OK
 */
void test1_player_set_damage();

/**
 * @test Test function for setting damage
 * @pre Valid player, negative damage
 * @post Output == ERROR
 */
void test2_player_set_damage();

/**
 * @test Test function to get damage
 * @pre Invalid player
 * @post Output == OK
 */
void test1_player_get_damage();

/**
 * @test Test function to get damage
 * @pre Valid player
 * @post Output == OK
 */
void test2_player_get_damage();
#endif
