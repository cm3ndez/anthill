/**
 * @brief It contains the declaration of link_test.c
 *
 * @file link_test.h
 * @author Jorge Ochoa
 * @version 1.0
 * @date 25-03-2025
 * @copyright GNU Public License
 */

#ifndef LINK_TEST_H
#define LINK_TEST_H

#include "link.h"
#include "test.h"

/**
 * @test Test link creation
 * @pre No parameters
 * @post Output == NewLink
 */
void test1_link_create();

/**
 * @test Test link creation
 * @pre No parameters
 * @post Output == NULL
 */
void test2_link_create();

/**
 * @test Test link destruction
 * @pre Valid link pointer
 * @post Output == OK
 */
void test1_link_destroy();

/**
 * @test Test link destruction
 * @pre NULL link
 * @post Output == ERROR
 */
void test2_link_destroy();

/**
 * @test Test setting link ID
 * @pre Valid link and valid ID
 * @post Output == OK
 */
void test1_link_set_id();

/**
 * @test Test setting link ID
 * @pre NULL link
 * @post Output == ERROR
 */
void test2_link_set_id();

/**
 * @test Test setting link ID
 * @pre Invalid ID (e.g., NO_ID)
 * @post Output == ERROR
 */
void test3_link_set_id();

/**
 * @test Test getting link ID
 * @pre Valid link with assigned ID
 * @post Output == ID
 */
void test1_link_get_id();

/**
 * @test Test getting link ID
 * @pre NULL link
 * @post Output == NO_ID
 */
void test2_link_get_id();

/**
 * @test Test setting link name
 * @pre Valid link and valid name
 * @post Output == OK
 */
void test1_link_set_name();

/**
 * @test Test setting link name
 * @pre NULL link
 * @post Output == ERROR
 */
void test2_link_set_name();

/**
 * @test Test setting link name
 * @pre Invalid name (NULL or empty)
 * @post Output == ERROR
 */
void test3_link_set_name();

/**
 * @test Test getting link name
 * @pre Valid link with assigned name
 * @post Output == Name
 */
void test1_link_get_name();

/**
 * @test Test getting link name
 * @pre NULL link
 * @post Output == NULL
 */
void test2_link_get_name();

/**
 * @test Test setting link origin
 * @pre Valid link and valid origin ID
 * @post Output == OK
 */
void test1_link_set_origin();

/**
 * @test Test setting link origin
 * @pre NULL link
 * @post Output == ERROR
 */
void test2_link_set_origin();

/**
 * @test Test setting link origin
 * @pre Invalid origin ID (e.g., NO_ID)
 * @post Output == ERROR
 */
void test3_link_set_origin();

/**
 * @test Test getting link origin
 * @pre Valid link with assigned origin
 * @post Output == ID
 */
void test1_link_get_origin();

/**
 * @test Test getting link origin
 * @pre NULL link
 * @post Output == NO_ID
 */
void test2_link_get_origin();

/**
 * @test Test setting link destination
 * @pre Valid link and valid destination ID
 * @post Output == OK
 */
void test1_link_set_destination();

/**
 * @test Test setting link destination
 * @pre NULL link
 * @post Output == ERROR
 */
void test2_link_set_destination();

/**
 * @test Test setting link destination
 * @pre Invalid destination ID (e.g., NO_ID)
 * @post Output == ERROR
 */
void test3_link_set_destination();

/**
 * @test Test getting link destination
 * @pre Valid link with assigned destination
 * @post Output == ID
 */
void test1_link_get_destination();

/**
 * @test Test getting link destination
 * @pre NULL link
 * @post Output == NO_ID
 */
void test2_link_get_destination();

/**
 * @test Test setting link direction
 * @pre Valid link and valid direction
 * @post Output == OK
 */
void test1_link_set_direction();

/**
 * @test Test setting link direction
 * @pre NULL link
 * @post Output == ERROR
 */
void test2_link_set_direction();

/**
 * @test Test getting link direction
 * @pre Valid link with assigned direction
 * @post Output == Direction
 */
void test1_link_get_direction();

/**
 * @test Test getting link direction
 * @pre NULL link
 * @post Output == NO_DIRECTION
 */
void test2_link_get_direction();

/**
 * @test Test setting link open status
 * @pre Valid link and valid open state
 * @post Output == OK
 */
void test1_link_set_open();

/**
 * @test Test setting link open status
 * @pre NULL link
 * @post Output == ERROR
 */
void test2_link_set_open();

/**
 * @test Test setting link open status
 * @pre Invalid open state
 * @post Output == ERROR
 */
void test3_link_set_open();

/**
 * @test Test getting link open status
 * @pre Valid link with assigned open state
 * @post Output == Open state
 */
void test1_link_get_open();

/**
 * @test Test getting link open status
 * @pre NULL link
 * @post Output == FALSE
 */
void test2_link_get_open();

#endif
