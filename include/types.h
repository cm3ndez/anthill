/**
 * @brief It defines common types for the whole project
 *
 * @file types.h
 * @author Jorge Ochoa
 * @version 1.0
 * @date 25-03-2025
 * @copyright GNU Public License
 */

#ifndef TYPES_H
#define TYPES_H

/**
 * @def WORD_SIZE
 * @brief Defines the length of the buffer for general purposes
 */
#define WORD_SIZE 1000

/**
 * @def MAX_LINES
 * @brief Defines the max lines of a file for general purposes
 */
#define MAX_LINES 1020

/**
 * @def NO_ID
 * @brief Defines the default invalid Id
 */
#define NO_ID -1

/**
 * @brief Id
 *
 * This struct "renames" a long with an id.
 */
typedef long Id;

/**
 * @brief Bool
 *
 * This struct creates the type of variable Bool, with values its posible values being TRUE or FALSE.
 */
typedef enum { FALSE, TRUE } Bool;

/**
 * @brief Status
 *
 * This struct creates the type of variable Status, with values its posible values being OK or ERROR.
 */
typedef enum { ERROR, OK } Status;

/**
 * @brief Direction
 *
 * This struct creates the type of variable Direction, with values its posible values being N, S, E or W.
 */
typedef enum { N, S, E, W, U, D, NO_DIRECTION } Direction;

#endif
