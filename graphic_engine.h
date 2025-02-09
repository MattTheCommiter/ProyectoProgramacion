/**
 * @brief It defines the textual graphic engine interface
 *
 * @file graphic_engine.h
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#ifndef GRAPHIC_ENGINE_H
#define GRAPHIC_ENGINE_H

#include "game.h"

typedef struct _Graphic_engine Graphic_engine;

Graphic_engine *graphic_engine_create();

/**
 * @brief destroys all the areas of the screen stored in the pointer to the graphic engine
 * 
 * @param ge pointer to the game's textual graphic engine
 */
void graphic_engine_destroy(Graphic_engine *ge);

/**
 * @brief paints the graphic interface of the game
 * 
 * @param ge pointer to the game's textual graphic engine
 * @param game pointer to the game interface, with information about the player and the object being used in the function
 */
void graphic_engine_paint_game(Graphic_engine *ge, Game *game);

#endif
