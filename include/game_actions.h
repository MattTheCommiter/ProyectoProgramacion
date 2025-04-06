/**
 * @brief It defines the game update interface
 *
 * @file game.h
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
#include <strings.h>

#define PLAYER_DAMAGE 1 /*The ammount of health a character loses when attacked by a player*/
#define ENEMY_DAMAGE 1  /*The ammount of health a player loses when attacked by an enemy*/
#define ATTACK_CHANCE 4 /*A number betweeen 0 and 9 that determines the odds of the player hitting an enemy when ussing the command "attack". The higher the number, the higher the odds of the enemy damaging the player*/

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
