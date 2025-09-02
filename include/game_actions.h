/**
 * @brief It defines the game update through user actions
 *
 * @file game_actions.h
 * @author Abraham Martin
 * @version 3.0
 * @date 30-03-2025
 * @copyright GNU Public License
 */

#ifndef GAME_ACTIONS_H
#define GAME_ACTIONS_H

#include "command.h"
#include "game.h"
#include "types.h"

/**
 * @brief Updates the game depending on what the player introduces
 * @author Abraham Martín
 *
 * @param game Pointer to pointer to the game that is being played
 * @param command Pointer to the command entered
 * @return OK if everything went well, ERROR otherwise
 */
Status game_actions_update(Game *game, Command *command);

#endif
