

/**
 * @file game_rules.h
 * @author Araceli Gutiérrez
 * @brief 
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

/**
 * @brief Applies game rules based on various conditions.
 * Depending on the conditions met, it performs actions such as opening or closing
 * links, moving objects, and handling unexpected attacks on the player.
 * @author Araceli Gutiérrez
 *
 * @param game Pointer to the Game structure.
 */
void game_rules_apply(Game *game);

/**
 * @brief Changes the state of a link within the game.
 * This function sets the state of a specified link to either open or closed.
 * @author Araceli Gutiérrez
 *
 * @param game Pointer to the Game structure.
 * @param l Pointer to the Link structure.
 * @param is_open Boolean value indicating whether the link should be open (TRUE) or closed (FALSE).
 */
void game_rules_set_link_state(Game *game, Link *l, Bool is_open);

/**
 * @brief Changes the location of an object within the game.
 * This function moves an object to a specified space within the game.
 * @author Araceli Gutiérrez
 * @param game Pointer to the Game structure.
 * @param object_id Id of the object to be moved.
 * @param space_id Id of the space where the object will be moved.
 */
void game_rules_set_object_location(Game *game, Id object_id, Id space_id);

/**
 * @brief This function implements an unexpected attack on the player by an enemy.
 * @author Araceli Gutiérrez
 * It calls the game_actions_attack function to process the attack. After the attack
 * is processed, it sets a message indicating that the player has been attacked by the
 * specified enemy and the message is displayed in the game interface.
 *
 * @param game Pointer to the Game structure.
 * @param enemy_name Name of the enemy attacking the player.
 */
void game_rules_receive_foe_attack(Game *game, char *enemy_name);

/**
 * @brief this function updates the missions of the game, acording to the last command and current state of the game, also modifies the dialogs printed in the graphic engine
 * @author Alvaro Inigo
 * @param game a pointer to the game
 */
void game_rules_mission_update(Game *game);




#endif
