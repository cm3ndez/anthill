/**
 * @brief It defines the textual graphic engine interface
 *
 * @file graphic_engine.h
 * @author Abraham Martín
 * @version 5.2
 * @date 03-04-2025
 * @copyright GNU Public License
 */

#ifndef GRAPHIC_ENGINE_H
#define GRAPHIC_ENGINE_H

#include "game.h"

/**
 * @brief Graphic_engine
 *
 * This struct stores all the information related to a graphic_engine.
 */
typedef struct _Graphic_engine Graphic_engine;

/**
 * @brief Allocates memory for a new Graphic_engine
 * @author Abraham Martín
 *
 * @return Pointer to the Graphic_engine created
 */
Graphic_engine *graphic_engine_create(void);

/**
 * @brief Frees the memory for the given Graphic_engine
 * @author Abraham Martín
 *
 * @param ge A pointer to a Graphic_engine
 */
void graphic_engine_destroy(Graphic_engine *ge);

/**
 * @brief Draws the game map, the game description and the game banner, among other things
 * @author Abraham Martín
 *
 * @param ge A pointer to a Graphic_engine
 * @param game A double pointer to a Game
 */
void graphic_engine_paint_game(Graphic_engine *ge, Game *game);

#endif
