/**
 * @brief It implements the non deterministic nature of the game
 *
 * @file GameRules.c
 * @author Araceli Gutiérrez
 * @version 0.1
 * @date May 2025
 * @copyright GNU Public License
 */

#include "game_rules.h"
#include <stdlib.h>
#include <time.h>
#include <strings.h>

/*PRIVATE FUNCTIONS*/
void game_rules_no_mission(Game *game);
void game_rules_team_mission(Game *game, Mission *mission, Graphic_engine *ge);
void game_rules_lantern_mission(Game *game, Mission *mission, Graphic_engine *ge);
void game_rules_generator_mission(Game *game, Mission *mission, Graphic_engine *ge);
void game_rules_father_mission(Game *game, Mission *mission, Graphic_engine *ge);
void game_rules_second_floor_mission(Game *game, Mission *mission, Graphic_engine *ge);
void game_rules_medkit_mission(Game *game, Mission *mission, Graphic_engine *ge);
void game_rules_bedroom_mission(Game *game, Mission *mission, Graphic_engine *ge);
void game_rules_REX_mission(Game *game, Mission *mission, Graphic_engine *ge);
void game_rules_third_floor_mission(Game *game, Mission *mission, Graphic_engine *ge);
void game_rules_boss_mission(Game *game, Mission *mission, Graphic_engine *ge);

void game_rules_alice_flashback_init(Game *game);




void game_rules_mission_update(Game *game, Graphic_engine *ge){
    Mission_Code mission_code;
    Mission *mission = NULL;
    if(!game || !ge) return;
    mission_code = game_get_current_mission_code(game);
    mission = game_get_current_mission(game);


    if(mission_code == NO_MISSION){
        game_rules_no_mission(game);
        return;
    }
    mission = game_get_current_mission(game);
    if(!mission) return;
    switch(mission_code){
        case TEAM_MISSION:
            game_rules_team_mission(game, mission, ge);
            break;
        case LANTERN_MISSION:
            game_rules_lantern_mission(game, mission, ge);
            break;
        case GENERATOR_MISSION:
            game_rules_generator_mission(game, mission, ge);
            break;
        case FATHER_MISSION:
            game_rules_father_mission(game, mission, ge);
            break;
        case SECOND_FLOOR_MISSION:
            game_rules_second_floor_mission(game, mission, ge);
            break;
        case MEDKIT_MISSION:
            game_rules_medkit_mission(game, mission, ge);
            break;
        case BEDROOM_MISSION:
            game_rules_bedroom_mission(game, mission, ge);
            break;
        case REX_MISSION:
            game_rules_REX_mission(game, mission, ge);
            break;
        case THIRD_FLOOR_MISSION:
            game_rules_third_floor_mission(game, mission, ge);
            break;
        case BOSS_MISSION:
            game_rules_boss_mission(game, mission, ge);
            break;
        default:
            break;
    }
}


void game_rules_no_mission(Game *game){
    if(!game) return;
    game_set_current_mission(game, TEAM_MISSION);
    game_set_next_objective(game);
    game_set_next_dialogue(game);
    game_set_show_message(game , TRUE);

    return;

}

void game_rules_team_mission(Game *game, Mission *mission, Graphic_engine *ge){
    int step;
    if(!game || !mission) return;
    step = mission_get_current_step(mission);
    switch(step){
        case(0):
        /*Si estan en el mismo equipo, la mision se termina ahi*/
            if(player_get_team(game_get_player_in_pos(game, ALICE_TURN)) == player_get_team(game_get_player_in_pos(game, BOB_TURN))){
                game_set_current_mission(game, LANTERN_MISSION);
                game_set_next_objective(game);
                game_set_next_dialogue(game);
                game_set_show_message(game , TRUE);
                graphic_engine_clear_dialogue(ge);
                return;
            }
            break;
        default:
            break;
    }
    return;
}
void game_rules_lantern_mission(Game *game, Mission *mission, Graphic_engine *ge){
    int step;
    if(!game || !mission) return;
    step = mission_get_current_step(mission);

    switch(step){
        /*en el primer paso, se solicita que se cambie de turno a Bob*/
        case(0):
            if(game_get_turn(game) == BOB_TURN){
                mission_set_current_step(mission, step + 1);
                game_set_next_dialogue(game);
                game_set_next_objective(game);
                game_set_show_message(game , TRUE);
                graphic_engine_clear_dialogue(ge);
            }
            break;
        /*en el segundo paso, se solicita que se de las baterias a Alice, entonces la mision terminara*/
        case(1):
            if(player_backpack_contains(game_get_player_in_pos(game, ALICE_TURN), BATTERIES_ID) == TRUE){
                game_set_current_mission(game, GENERATOR_MISSION);
                game_set_next_dialogue(game);
                game_set_next_objective(game);
                game_set_show_message(game , TRUE);
                graphic_engine_clear_dialogue(ge);
            }
            break;
        default:
            break;
    }
    return;
}

void game_rules_generator_mission(Game *game, Mission *mission, Graphic_engine *ge){
    int step;
    if(!game || !mission) return;
    step = mission_get_current_step(mission);
    switch(step){
        case(0):
            /*el primer paso solicita que Alice busque el cuarto con el generador*/
            if(player_get_location(game_get_player_in_pos(game, ALICE_TURN)) == GENERATOR_SPACE){
                mission_set_current_step(mission, step + 1);
                game_set_next_dialogue(game);
                game_set_next_objective(game);
                game_set_show_message(game , TRUE);
                graphic_engine_clear_dialogue(ge);
            }
            break;
        case(1):
            /*en el segundo paso, se solicita a Alice que inspeccione el generador, cuando lo hace pasamos a la mission de flashback*/
            if(command_get_code(game_interface_data_get_cmd_in_pos(game, LAST)) == INSPECT && command_get_lastcmd_success(game_interface_data_get_cmd_in_pos(game, LAST)) == OK && !strcasecmp(command_get_argument(game_interface_data_get_cmd_in_pos(game, LAST)), GENERATOR_NAME)){
                game_rules_alice_flashback_init(game);
                game_set_current_mission(game, FATHER_MISSION);
                game_set_next_dialogue(game);
                game_set_next_objective(game);
                game_set_show_message(game , TRUE);
                graphic_engine_clear_dialogue(ge);
            }
            break;
        default:
            break;
        
    }
    return;
}
void game_rules_father_mission(Game *game, Mission *mission, Graphic_engine *ge){
    int step;
    if(!game || !mission) return;
    step = mission_get_current_step(mission);
    return;
}
void game_rules_second_floor_mission(Game *game, Mission *mission, Graphic_engine *ge){
    int step;
    if(!game || !mission) return;
    step = mission_get_current_step(mission);
    return;
}
void game_rules_medkit_mission(Game *game, Mission *mission, Graphic_engine *ge){
    int step;
    if(!game || !mission) return;
    step = mission_get_current_step(mission);
    return;
}
void game_rules_bedroom_mission(Game *game, Mission *mission, Graphic_engine *ge){
    int step;
    if(!game || !mission) return;
    step = mission_get_current_step(mission);
    return;
}
void game_rules_REX_mission(Game *game, Mission *mission, Graphic_engine *ge){
    int step;
    if(!game || !mission) return;
    step = mission_get_current_step(mission);
    return;
}
void game_rules_third_floor_mission(Game *game, Mission *mission, Graphic_engine *ge){
    int step;
    if(!game || !mission) return;
    step = mission_get_current_step(mission);
    return;
}
void game_rules_boss_mission(Game *game, Mission *mission, Graphic_engine *ge){
    int step;
    if(!game || !mission) return;
    step = mission_get_current_step(mission);
    return;
}



void game_rules_alice_flashback_init(Game *game){
    if(!game) return;
    /*movemos a Alice a los espacios reservados para el flashback*/
    player_set_location(game_get_player_in_pos(game, ALICE_TURN), GENERATOR_FLASH_SPACE);
    return;
}