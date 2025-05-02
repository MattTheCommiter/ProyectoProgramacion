/**
 * @brief It implements the non deterministic nature of the game
 *
 * @file GameRules.c
 * @author Araceli Gutiérrez
 * @version 0.1
 * @date May 2025
 * @copyright GNU Public License
 */

#include "gamerules.h"
#include <stdlib.h>
#include <time.h>



/**
 * @brief Applies game rules based on various conditions.
 * Depending on the conditions met, it performs actions such as opening or closing
 * links, moving objects, and handling unexpected attacks on the player.
 * @author Araceli Gutiérrez
 * @param game Pointer to the Game structure.
 */
void game_rules_apply(Game *game) {

    Bool condition_1 = FALSE;   /*condition for opening a link*/
    Bool condition_2 = FALSE;   /*condition for closing a link*/
    Bool condition_3 = FALSE;   /*contion for changing location of an object*/
    Bool condition_4 = FALSE;   /*condition for triggering an attack from an enemy*/
    
    /*open the link to the generator if Alice has the flashlight with batteries, for example */
    if (player_backpack_contains(.....*ALICE......, Id obj_id flashlight......)) {
        condition_1 = TRUE;
    }
    
    /*close the link to the kitchen if the ghost has been defeated, for example */
    if (character_get_health(.....*GHOST....) == 0) {
        condition_2 = TRUE;
    }

    /*move the object to a new location if players backpack contains......whatever*/
    if (player_backpack_contains(game_get_current_player(game), ....object_id in backpack)) {
        condition_3 = TRUE;
    }

    /*receive an attack from an enemy when the current player enters into .......wherever*/
    if(game_get_current_player_location(Game *game) == .........space_id of a "dangerous space"){
    }
    
    /* Apply rules based on conditions */
    if (condition_1) {
        game_rules_set_link_state(game, ......*.GENERATOR_LINK......., TRUE);
    }
    
    if (condition_2) {
        game_rules_set_link_state(game, ........*KITCHEN_LINK........, FALSE);
    }

    if (condition_3) {
        game_rules_set_object_location(Game *game, Id object_id, Id space_id);
    }

    if (condition_4) {
        game_rules_receive_foe_attack(game, ENEMY_NAME);
    }
    
}

/**
 * @brief Changes the state of a link within the game.
 * This function sets the state of a specified link to either open or closed.
 * @author Araceli Gutiérrez
 * @param game Pointer to the Game structure.
 * @param l Pointer to the Link structure.
 * @param is_open Boolean value indicating whether the link should be open (TRUE) or closed (FALSE).
 */
void game_rules_set_link_state(Game *game, Link *l, Bool is_open) {

    char message[DIALOGUE_LINE_LENGTH]="";
    
    if (!game || l == NULL){
        return;
    }
    
    /* Change the state of the link */
    if(link_set_is_open(l, is_open) == ERROR){
        return;
    }

    /*set and show a message*/
    sprintf(message, "Link '%s' has been %s.", link_get_name(l), is_open ? "opened" : "closed");

    game_set_message(game, message);
    game_set_show_message(game, TRUE);

}


/**
 * @brief Changes the location of an object within the game.
 * This function moves an object to a specified space within the game.
 * @author Araceli Gutiérrez
 * @param game Pointer to the Game structure.
 * @param object_id Id of the object to be moved.
 * @param space_id Id of the space where the object will be moved.
 */
void game_rules_set_object_location(Game *game, Id object_id, Id space_id) {
    
    Space *current_space = NULL;
    Space *new_space = NULL;
    Id current_space_id = NO_ID;
    char message[DIALOGUE_LINE_LENGTH] = "";

    if (!game || object_id == NO_ID || space_id == NO_ID) {
        return;
    }

    /* Get the current location of the object */
    current_space_id = game_get_object_location(game, object_id);
    if (current_space_id == NO_ID) {
        return;
    }

    /* Remove the object from the current space */
    if (space_delete_object(current_space, object_id) == ERROR) {
        return;
    }

    /* Get the new space */
    space = game_get_space(game, space_id);
    if (!space) {
        return;
    }

    /* Add the object to the new space */
    if (space_add_objectId(space, object_id) == ERROR) {
        return;
    }

    /* Format the message */
    sprintf(message, "Object '%ld' has been moved from space '%s' to space '%s'.", object_id, space_get_name(current_space), space_get_name(new_space));

    /* Set and show the message */
    game_set_message(game, message);
    game_set_show_message(game, TRUE);  
}


/**
 * @brief This function implements an unexpected attack on the player by an enemy.
 * It calls the game_actions_attack function to process the attack. After the attack
 * is processed, it sets a message indicating that the player has been attacked by the
 * specified enemy and the message is displayed in the game interface.
 * @author Araceli Gutiérrez
 * @param game Pointer to the Game structure.
 * @param enemy_name Name of the enemy attacking the player.
 */
void game_rules_receive_foe_attack(Game *game, char *enemy_name) {

    char message[DIALOGUE_LINE_LENGTH] = "";

    if (game == NULL || enemy_name == NULL){
        return;
    }

    game_actions_attack(game, enemy_name);

    /* Set and show a message */
    sprintf(message, "You have been attacked by '%s'.", enemy_name);
    game_set_message(game, message);
    game_set_show_message(game, TRUE);

}



/**
 * @brief Applies a random game rule.
 * This function selects and applies one of several predefined game rules at random.
 * The rules include actions such as opening or closing links, moving objects, and
 * triggering an enemy attack. This function is intended to introduce non-deterministic
 * elements into the game.
 * @author Araceli Gutiérrez
 * @param game Pointer to the Game structure.
 */
void game_rules_apply_random(Game *game) {
    int rule = rand() % 6; /*if we have 6 rules (min to implement according to the requirements)*/
    
    switch (rule) {
    case 0:
        game_rules_set_link_state(game, ......GENERATOR_LINK...., TRUE);
        break;
    case 1:
         game_rules_set_link_state(game, .....KITCHEN_LINK......, FALSE);
        break;
    case 2:
        game_rules_set_object_location(game, ......OBJECT_ID....., .....NEW_LOCATION_ID.....);
        break;
    case 3:
         game_rules_receive_foe_attack(game, enemy_name);
        break;
    case 4:
        /*Implement another rule*/
        break;
    case 5:
        /*Implement another rule*/
        break;
    default:
        break;
    }
}



