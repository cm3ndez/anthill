/**
 * @brief It declares the tests for the character module
 *
 * @file character_test.h
 * Carlos Méndez
 * @version 0.0
 * @date 17-02-2025
 * @copyright GNU Public License
 */

#ifndef CHARACTER_TEST_H
#define CHARACTER_TEST_H

/**
 * @test Test character creation
 * @pre No parameters
 * @post Non NULL pointer to character
 */
void test1_character_create();

/**
 * @test Test character creation
 * @pre No parameters
 * @post Character_ID == Supplied Character ID
 */
void test2_character_create();

/**
 * @test Test character destruction
 * @pre Valid character
 * @post Output == OK
 */
void test1_character_destroy();

/**
 * @test Test character destruction
 * @pre NULL character
 * @post Output == OK
 */
void test2_character_destroy();

/**
 * @test Test setting character friendliness
 * @pre Valid character and friendly flag
 * @post Output == TRUE
 */
void test1_character_set_friendly();

/**
 * @test Test setting character friendliness
 * @pre NULL character
 * @post Output == FALSE
 */
void test2_character_set_friendly();

/**
 * @test Test getting character friendliness
 * @pre Character with friendliness set
 * @post Output == TRUE
 */
void test1_character_get_friendly();

/**
 * @test Test getting character friendliness
 * @pre NULL character
 * @post Output == FALSE
 */
void test2_character_get_friendly();

/**
 * @test Test setting character health
 * @pre Valid character and health value
 * @post Output == OK
 */
void test1_character_set_health();

/**
 * @test Test setting character health
 * @pre NULL character
 * @post Output == ERROR
 */
void test2_character_set_health();

/**
 * @test Test getting character health
 * @pre Character with health set
 * @post Output == Correct health value
 */
void test1_character_get_health();

/**
 * @test Test getting character health
 * @pre NULL character
 * @post Output == -1
 */
void test2_character_get_health();

/**
 * @test Test setting graphical description
 * @pre Valid character and graphical description
 * @post Output == OK
 */
void test1_character_set_gdesc();

/**
 * @test Test setting graphical description
 * @pre NULL character
 * @post Output == ERROR
 */
void test2_character_set_gdesc();

/**
 * @test Test setting graphical description
 * @pre NULL graphical description
 * @post Output == ERROR
 */
void test3_character_set_gdesc();

/**
 * @test Test getting graphical description
 * @pre Character with graphical description set
 * @post Output == Correct graphical description
 */
void test1_character_get_gdesc();

/**
 * @test Test getting graphical description
 * @pre NULL character
 * @post Output == NULL
 */
void test2_character_get_gdesc();

/**
 * @test Test getting character ID
 * @pre Valid character
 * @post Output == Character ID
 */
void test1_character_get_id();

/**
 * @test Test getting character ID
 * @pre NULL character
 * @post Output == NO_ID
 */
void test2_character_get_id();

/**
 * @test Test setting character name
 * @pre Valid character and name
 * @post Output == OK
 */
void test1_character_set_name();

/**
 * @test Test setting character name
 * @pre NULL character
 * @post Output == ERROR
 */
void test2_character_set_name();

/**
 * @test Test setting character name
 * @pre NULL name
 * @post Output == ERROR
 */
void test3_character_set_name();

/**
 * @test Test getting character name
 * @pre Character with name set
 * @post Output == Correct name
 */
void test1_character_get_name();

/**
 * @test Test getting character name
 * @pre NULL character
 * @post Output == NULL
 */
void test2_character_get_name();

/**
 * @test Test setting character message
 * @pre Valid character and message
 * @post Output == OK
 */
void test1_character_set_message();

/**
 * @test Test setting character message
 * @pre NULL character
 * @post Output == ERROR
 */
void test2_character_set_message();

/**
 * @test Test setting character message
 * @pre NULL message
 * @post Output == ERROR
 */
void test3_character_set_message();

/**
 * @test Test getting character message
 * @pre Character with message set
 * @post Output == Correct message
 */
void test1_character_get_message();

/**
 * @test Test getting character message
 * @pre NULL character
 * @post Output == NULL
 */
void test2_character_get_message();

/**
 * @test Test setting folllowing
 * @pre valid character
 * @post Output == TRUE
 */
void test1_character_set_following();

/**
 * @test Test setting folllowing
 * @pre NULL character
 * @post Output == ERROR
 */
void test2_character_set_following();

/**
 * @test Test getting following boolean
 * @pre valid character. Valid Id following
 * @post Output == Id
 */
void test1_character_get_following();

/**
 * @test Test getting following boolean
 * @pre NULL character
 * @post Output == NO_ID
 */
void test2_character_get_following();

#endif