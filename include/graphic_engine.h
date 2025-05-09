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
#include "command.h"
#include "libscreen.h"
#include "player.h"
#include "space.h"
#include "types.h"
#include "character.h"

#define MIN_VALUE_WITH_THREE_NUMBERS 100    /*!<The smallest value that requires three positions to be written*/
/**
 * @brief Structure where the entire graphic interface will be stored and updated
 * 
 */
typedef struct _Graphic_engine Graphic_engine;

/**
 * @brief Creates a new graphic engine
 *
 * @date 27-01-2025
 * @author Profesores
 *
 */
Graphic_engine *graphic_engine_create();

/**
 * @brief frees the memory allocated for all the areas of the screen, which are stored in the pointer to the graphic engine
 *
 * @date 27-01-2025
 * @author Profesores
 *
 * @param ge pointer to the game's textual graphic engine
 */
void graphic_engine_destroy(Graphic_engine *ge);

/**
 * @brief paints the graphic interface of the game
 *
 * @date 05-05-2025
 * @author Profesores
 *
 * @param ge pointer to the game's textual graphic engine
 * @param game pointer to the game interface, with information about the player and the object being used in the function
 */
void graphic_engine_paint_game(Graphic_engine *ge, Game *game);


#endif
