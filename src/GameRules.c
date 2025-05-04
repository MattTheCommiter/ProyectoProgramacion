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
#include <strings.h>

/*PRIVATE FUNCTIONS*/

void game_rules_team_mission(Game *game, Mission *mission);
void game_rules_lantern_mission(Game *game, Mission *mission);
void game_rules_generator_mission(Game *game, Mission *mission);
void game_rules_father_mission(Game *game, Mission *mission);
void game_rules_second_floor_mission(Game *game, Mission *mission);
void game_rules_medkit_mission(Game *game, Mission *mission);
void game_rules_bedroom_mission(Game *game, Mission *mission);
void game_rules_REX_mission(Game *game, Mission *mission);
void game_rules_third_floor_mission(Game *game, Mission *mission);
void game_rules_boss_mission(Game *game, Mission *mission);

void game_rules_alice_flashback_init(Game *game);

/******************/
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



void game_rules_mission_update(Game *game){
    if(!game) return;
    Mission_Code mission_code = game_get_current_mission_code(game);
    Mission *mission = NULL;
    mission = game_get_current_mission(game);
    if(!mission) return;

    switch(mission_code){
        case NO_MISSION:
            break;
        case TEAM_MISSION:
            break;
        case LANTERN_MISSION:
            break;
        case GENERATOR_MISSION:
            break;
        case FATHER_MISSION:
            break;
        case SECOND_FLOOR_MISSION:
            break;
        case MEDKIT_MISSION:
            break;
        case BEDROOM_MISSION:
            break;
        case REX_MISSION:
            break;
        case THIRD_FLOOR_MISSION:
            break;
        case BOSS_MISSION:
            break;
        default:
            break;
    }
}

void game_rules_team_mission(Game *game, Mission *mission){
    if(!game || !mission) return;
    int step;
    step = mission_get_current_step(mission);
    switch(step){
        case(0):
        /*Si estan en el mismo equipo, la mision se termina ahi*/
            if(player_get_team(game_get_player_in_pos(game, ALICE_TURN)) == player_get_team(game_get_player_in_pos(game, BOB_TURN))){
                game_set_current_mission(game, LANTERN_MISSION);
                game_set_next_objective(game);
                game_set_next_dialogue(game);
            }
            break;
        default:
            break;
    }
    return;
}
void game_rules_lantern_mission(Game *game, Mission *mission){
    if(!game || !mission) return;
    int step = mission_get_current_step(mission);

    switch(step){
        /*en el primer paso, se solicita que se cambie de turno a Bob*/
        case(0):
            if(game_get_turn(game) == BOB_TURN){
                mission_set_current_step(mission, step + 1);
                game_set_next_dialogue(game);
                game_set_next_objective(game);
            }
            break;
        /*en el segundo paso, se solicita que se de las baterias a Alice, entonces la mision terminara*/
        case(1):
            if(player_backpack_contains(game_get_player_in_pos(game, ALICE_TURN), BATTERIES_ID) == TRUE){
                game_set_current_mission(game, GENERATOR_MISSION);
                game_set_next_dialogue(game);
                game_set_next_objective(game);
            }
            break;
        default:
            break;
    }
    return;
}

void game_rules_generator_mission(Game *game, Mission *mission){
    if(!game || !mission) return;
    int step = mission_get_current_step(mission);
    switch(step){
        case(0):
            /*el primer paso solicita que Alice busque el cuarto con el generador*/
            if(player_get_location(game_get_player_in_pos(game, ALICE_TURN)) == GENERATOR_SPACE){
                mission_set_current_step(mission, step + 1);
                game_set_next_dialogue(game);
                game_set_next_objective(game);
            }
            break;
        case(1):
            /*en el segundo paso, se solicita a Alice que inspeccione el generador, cuando lo hace pasamos a la mission de flashback*/
            if(command_get_code(game_interface_data_get_cmd_in_pos(game, LAST)) == INSPECT && command_get_lastcmd_success(game_interface_data_get_cmd_in_pos(game, LAST)) == OK && !strcasecmp(command_get_argument(game_interface_data_get_cmd_in_pos(game, LAST)), GENERATOR_NAME)){
                game_rules_alice_flashback_init(game);
                game_set_current_mission(game, FATHER_MISSION);
                game_set_next_dialogue(game);
                game_set_next_objective(game);
            }
            break;
        default:
            break;
        
    }
    return;
}
void game_rules_father_mission(Game *game, Mission *mission){
    if(!game || !mission) return;
    int step = mission_get_current_step(mission);
    return;
}
void game_rules_second_floor_mission(Game *game, Mission *mission){
    if(!game || !mission) return;
    int step = mission_get_current_step(mission);
    return;
}
void game_rules_medkit_mission(Game *game, Mission *mission){
    if(!game || !mission) return;
    int step = mission_get_current_step(mission);
    return;
}
void game_rules_bedroom_mission(Game *game, Mission *mission){
    if(!game || !mission) return;
    int step = mission_get_current_step(mission);
    return;
}
void game_rules_REX_mission(Game *game, Mission *mission){
    if(!game || !mission) return;
    int step = mission_get_current_step(mission);
    return;
}
void game_rules_third_floor_mission(Game *game, Mission *mission){
    if(!game || !mission) return;
    int step = mission_get_current_step(mission);
    return;
}
void game_rules_boss_mission(Game *game, Mission *mission){
    if(!game || !mission) return;
    int step = mission_get_current_step(mission);
    return;
}



void game_rules_alice_flashback_init(Game *game){
    if(!game) return;
    /*movemos a Alice a los espacios reservados para el flashback*/
    player_set_location(game_get_player_in_pos(game, ALICE_TURN), GENERATOR_FLASH_SPACE);
    return;
}