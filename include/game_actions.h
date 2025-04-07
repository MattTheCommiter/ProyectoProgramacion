/**
 * @brief It defines the game update interface
 *
 * @file game_actions.h
 * @author Matteo Artunedo
 * @version 0.2
 * @date 15-03-2025
 * @copyright GNU Public License
 */

#ifndef GAME_ACTIONS_H
#define GAME_ACTIONS_H

#include "command.h"
#include "game.h"
#include "types.h"
#include "space.h"
#include "character.h"
#include "player.h"
#include "object.h"

/**
 * @brief The amount of health a character loses when attacked by a player.
 */

#define PLAYER_DAMAGE 1 

/**
 * @brief The amount of health a player loses when attacked by an enemy.
 */
#define ENEMY_DAMAGE 1

/**
 * @brief A number between 0 and 9 that determines the odds of the player hitting an enemy when using the command "attack".
 * The higher the number, the higher the odds of the enemy damaging the player.
 */
#define ATTACK_CHANCE 4

/**
 * @brief Updates the game's last_cmd to the newest command, calling the action functions (which are private) depending on the command
 *
 * @date 27-01-2025
 * @author Profesores
 *
 * @param game a pointer to the structure with the game's main information
 * @param cmd the newest command
 * @return Status : whether function was completed succesfully
 */
Status game_actions_update(Game *game, Command *cmd);

#endif
