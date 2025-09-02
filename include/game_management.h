/**
 * @brief It defines the fucntions neede to create the spaces
 * and asign them their vaules according to the file
 *
 * @file game_management.h
 * @author Jorge Ochoa
 * @version 4.0
 * @date 01-05-2025
 * @copyright GNU Public License
 */

#ifndef GAME_MANAGEMENT_H
#define GAME_MANAGEMENT_H

#include "game.h"
#include "types.h"

/**
 * @brief Reads from a file the spaces that need to be created
 * @author Jorge Ochoa
 *
 * @param game Pointer to pointer to the game being played
 * @param file File name of the .dat for reading data
 * @return OK if everything goes well and ERROR if it couldnt complete its task
 */
Status game_management_load_spaces(Game **game, char *file);

/**
 * @brief Reads from a file the objects that need to be created
 * @author Jorge Ochoa
 *
 * @param game Pointer to pointer to the game being played
 * @param file File name of the .dat for reading data
 * @return OK if everything goes well and ERROR if it couldnt complete its task
 */
Status game_management_load_objects(Game **game, char *file);

/**
 * @brief Reads from a file the characters that need to be created
 * @author Jorge Ochoa
 *
 * @param game Pointer to pointer to the game being played
 * @param file File name of the .dat for reading data
 * @return OK if everything goes well and ERROR if it couldnt complete its task
 */
Status game_management_load_characters(Game **game, char *file);

/**
 * @brief Reads from a file the links that need to be created
 * @author Jorge Ochoa
 *
 * @param game Pointer to pointer to the game being played
 * @param file File name of the .dat for reading data
 * @return OK if everything goes well and ERROR if it couldnt complete its task
 */
Status game_management_load_links(Game **game, char *file);

/**
 * @brief Reads from a file the players that need to be created
 * @author Jorge Ochoa
 *
 * @param game Pointer to pointer to the game being played
 * @param file File name of the .dat for reading data
 * @return OK if everything goes well and ERROR if it couldnt complete its task
 */
Status game_management_load_players(Game **game, char *file);

/**
 * @brief Reads from a file all the information to load the game
 * @author Jorge Ochoa
 *
 * @param game Pointer to pointer to the game being created
 * @param filename File name of the .dat for reading data
 * @return OK if everything goes well and ERROR if it couldnt complete its task
 */
Status game_management_load_game_from_file(Game **game, char *filename);

/**
 * @brief Saves a game with a new .dat
 * @author Jorge Ochoa
 *
 * @param game Pointer to pointer to the game being created
 * @param filename File name of the .dat for reading data
 * @return OK if everything goes well and ERROR if it couldnt complete its task
 */
Status game_management_save(Game **game, const char *filename);

/**
 * @brief loads a game already started
 * @author Jorge Ochoa
 *
 * @param game Pointer to pointer to the game being created
 * @param file File name of the .dat for reading data
 * @return OK if everything goes well and ERROR if it couldnt complete its task
 */
Status game_management_load(Game **game, const char *file);

#endif
