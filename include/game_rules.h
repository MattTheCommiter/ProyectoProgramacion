

/**
 * @file game_rules.h
 * @author Álvaro Iñigo, Araceli Gutiérrez
 * @brief Implements the rules of the game
 * @version 0.1
 * @date May 2025
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef GAMERULES_H
#define GAMERULES_H

#include "game.h"
#include "types.h"

#define STAIRS_DAMAGE 2  /*!<Corresponds to the damage dealed to Alice after getting to the second floor*/


/**
 * @brief this function updates the missions of the game, acording to the last command and current state of the game, also modifies the dialogs printed in the graphic engine
 * @author Alvaro Inigo
 * @param game a pointer to the game
 */
void game_rules_mission_update(Game *game);




#endif
