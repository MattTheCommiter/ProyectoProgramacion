/**
 * @brief It implements the non deterministic nature of the game
 *
 * @file game_rules.c
 * @author Álvaro Iñigo; Araceli Gutiérrez
 * @version 0.1
 * @date May 2025
 * @copyright GNU Public License
 */

#include "game_rules.h"
#include <stdlib.h>
#include <time.h>
#include <strings.h>

#define BOB (game_get_player_in_pos(game, BOB_TURN))
#define ALICE (game_get_player_in_pos(game, ALICE_TURN))

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
void game_rules_mission_step(Game *game, Mission *mission, int step, Graphic_engine *ge);
void game_rules_spawn_ghost(Game *game);
void game_rules_spawn_dinosaur_leg(Game *game);
void game_rules_spawn_final_boss(Game *game);

void game_rules_mission_update(Game *game, Graphic_engine *ge)
{
    Mission_Code mission_code;
    Mission *mission = NULL;
    if (!game || !ge)
        return;
    mission_code = game_get_current_mission_code(game);
    mission = game_get_current_mission(game);

    if (mission_code == NO_MISSION)
    {
        game_rules_no_mission(game);
        return;
    }
    mission = game_get_current_mission(game);
    if (!mission)
        return;
    switch (mission_code)
    {
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

void game_rules_no_mission(Game *game)
{
    if (!game)
        return;
    game_set_current_mission(game, TEAM_MISSION);
    game_set_next_objective(game);
    game_set_next_dialogue(game);
    game_set_show_message(game, TRUE);

    return;
}

void game_rules_team_mission(Game *game, Mission *mission, Graphic_engine *ge)
{
    int step;
    if (!game || !mission || !ge)
        return;
    step = mission_get_current_step(mission);
    switch (step)
    {
    case (0):
        /*Si estan en el mismo equipo, la mision se termina ahi*/
        if (player_get_team(ALICE) == player_get_team(BOB))
        {
            game_set_current_mission(game, LANTERN_MISSION);
            game_set_next_objective(game);
            game_set_next_dialogue(game);
            game_set_show_message(game, TRUE);
            graphic_engine_clear_dialogue(ge);
            return;
        }
        break;
    default:
        break;
    }
    return;
}
void game_rules_lantern_mission(Game *game, Mission *mission, Graphic_engine *ge)
{
    int step;
    if (!game || !mission || !ge)
        return;
    step = mission_get_current_step(mission);

    switch (step)
    {
    /*en el primer paso, se solicita que se cambie de turno a Bob*/
    case (0):
        if (game_get_turn(game) == BOB_TURN)
        {
            game_rules_mission_step(game, mission, step, ge);
        }
        break;
    /*en el segundo paso, se solicita que se de las baterias a Alice, entonces la mision terminara*/
    case (1):
        if (player_backpack_contains(ALICE, BATTERIES_ID) == TRUE)
        {
            game_set_current_mission(game, GENERATOR_MISSION);
            game_set_next_dialogue(game);
            game_set_next_objective(game);
            game_set_show_message(game, TRUE);
            /*tambien ponemos los mensajes nuevos en el turno de alice*/
            game_interface_in_pos_set_objective(game, ALICE_TURN, game_get_objective(game));
            game_set_show_message_in_pos(game , TRUE, ALICE_TURN);

            graphic_engine_clear_dialogue(ge);
        }
        break;
    default:
        break;
    }
    return;
}

void game_rules_generator_mission(Game *game, Mission *mission, Graphic_engine *ge)
{
    int step;
    if (!game || !mission || !ge)
        return;
    step = mission_get_current_step(mission);
    switch (step)
    {
    case (0):
        /*el primer paso solicita que Alice busque el cuarto con el generador*/
        if (player_get_location(ALICE) == GENERATOR_SPACE)
        {
            game_rules_mission_step(game, mission, step, ge);
        }
        break;
    case (1):
        /*en el segundo paso, se solicita a Alice que inspeccione el generador, cuando lo hace pasamos a la mission de flashback*/
        if (command_get_code(game_interface_data_get_cmd_in_pos(game, LAST)) == INSPECT && command_get_lastcmd_success(game_interface_data_get_cmd_in_pos(game, LAST)) == OK && !strcasecmp(command_get_argument(game_interface_data_get_cmd_in_pos(game, LAST)), GENERATOR_NAME))
        {
            game_rules_alice_flashback_init(game);
            game_set_current_mission(game, FATHER_MISSION);
            game_set_next_dialogue(game);
            game_set_next_objective(game);
            game_set_show_message(game, TRUE);
            graphic_engine_clear_dialogue(ge);
        }
        break;
    default:
        break;
    }
    return;
}
void game_rules_father_mission(Game *game, Mission *mission, Graphic_engine *ge)
{
    int step;
    if (!game || !mission || !ge)
        return;
    step = mission_get_current_step(mission);
    switch (step)
    {
    case (0):
        /*cuando alice llega al espacio del storage room, se pasa en la mision*/
        if (player_get_location(ALICE) == STORAGE_ROOM__FLASH_SPACE)
        {
            game_rules_mission_step(game, mission, step, ge);
            return;
        }
    case (1):
        /*cuando alice abre la caja de herramientas, se pasa*/
        if (command_get_code(game_interface_data_get_cmd_in_pos(game, LAST)) == INSPECT && command_get_lastcmd_success(game_interface_data_get_cmd_in_pos(game, LAST)) == OK && !strcasecmp(command_get_argument(game_interface_data_get_cmd_in_pos(game, LAST)), TOOLBOX_NAME))
        {
            /*se genera la llave inglesa en el espacio*/
            space_add_objectId(game_get_space(game, STORAGE_ROOM__FLASH_SPACE), WRENCH_ID);
            game_rules_mission_step(game, mission, step, ge);
            return;
        }
    case (2):
        /*cuando alice vuelve con la llave inglesa al espacio del padre, se vuelve*/
        if (player_get_location(ALICE) == GENERATOR_FLASH_SPACE && player_backpack_contains(game_get_player_in_pos(game, ALICE_TURN), WRENCH_ID))
        {
            game_rules_mission_step(game, mission, step, ge);
            return;
        }
    case (3):
        /*cuando alice inspecciona el generador, se termina la mision y se encienden las luces*/
        if (command_get_code(game_interface_data_get_cmd_in_pos(game, LAST)) == INSPECT && command_get_lastcmd_success(game_interface_data_get_cmd_in_pos(game, LAST)) == OK && !strcasecmp(command_get_argument(game_interface_data_get_cmd_in_pos(game, LAST)), GENERATOR_FLASH_NAME))
        {
            game_set_current_mission(game, SECOND_FLOOR_MISSION);
            player_set_location(ALICE, GENERATOR_SPACE);
            game_set_next_dialogue(game);
            game_set_next_objective(game);
            game_set_show_message(game, TRUE);

            /*imprimimos el siguiente mensaje tambien en el turno de BOB*/
            game_interface_in_pos_set_objective(game, BOB_TURN, game_get_objective(game));
            game_set_show_message_in_pos(game , TRUE, BOB_TURN);

            graphic_engine_clear_dialogue(ge);
            game_set_lights_on(game, TRUE);
            return;
        }
    }
    return;
}

void game_rules_second_floor_mission(Game *game, Mission *mission, Graphic_engine *ge)
{
    int step;
    if (!game || !mission || !ge)
        return;
    step = mission_get_current_step(mission);
    switch (step)
    {
    case (0):
        /*En el primer paso se solicita a los jugadores ir al espacio de las escaleras*/
        if (player_get_location(ALICE) == FIRST_STAIRS_ROOM && player_get_location(BOB) == FIRST_STAIRS_ROOM)
        {
            game_rules_mission_step(game, mission, step, ge);
            game_rules_spawn_ghost(game);
            return;
        }
    case (1):
        /*Durante el segundo paso, se pide a bob que busque el cuchillo*/
        if (player_backpack_contains(BOB, KNIFE_ID))
        {
            /*si ya lo habia cogido antes, saltamos dos pasos*/
            if (player_get_location(BOB) == FIRST_STAIRS_ROOM)
                mission_set_current_step(mission, step + 1);

            game_rules_mission_step(game, mission, step, ge);
            return;
        }
    case (2):
        /*Una vez con el cuchillo, se pide a bob volver al espacio del fantasma*/
        if (player_get_location(BOB) == FIRST_STAIRS_ROOM)
        {
            game_rules_mission_step(game, mission, step, ge);
            return;
        }
    case (3):
        /*ahora se pide acabar con el fantasma*/
        if (character_get_health(game_get_character(game, GHOST_ID)) <= 0)
        {
            game_rules_mission_step(game, mission, step, ge);
            return;
        }
    case (4):
        /*se pide subir al espacio de arriba, cuando suben, se llama a la cinematica de escaleras y se cambia de mision a la de curar a alice*/
        if (player_get_location(BOB) == HALL1 && player_get_location(ALICE) == HALL1)
        {
            /*llamar a la cinematica de alice haciendose daño*/
            game_set_current_cinematic(game, FIRST_STAIRS);
            game_set_current_mission(game, MEDKIT_MISSION);
            game_set_next_dialogue(game);
            game_set_next_objective(game);
            game_set_show_message(game, TRUE);
            graphic_engine_clear_dialogue(ge);
            return;
        }

    default:
        break;
    }
    return;
}
void game_rules_medkit_mission(Game *game, Mission *mission, Graphic_engine *ge)
{
    int step;
    if (!game || !mission || !ge)
        return;
    step = mission_get_current_step(mission);
    switch(step){
        case(0):
        /*en el primer paso se pide llegar al baño a buscar el medkit*/
            if(player_get_location(ALICE) == BATHROOM_SPACE){
                game_rules_mission_step(game, mission, step, ge);
                return;
            }
        case(1):
        /*el segundo paso consiste en inspeccionar el medkit*/
            if(command_get_code(game_interface_data_get_cmd_in_pos(game, LAST)) == INSPECT && command_get_lastcmd_success(game_interface_data_get_cmd_in_pos(game, LAST)) == OK && !strcasecmp(command_get_argument(game_interface_data_get_cmd_in_pos(game, LAST)), MEDKIT_NAME)){
                /*metemos los objetos en el espacio(aparecen)*/
                space_add_objectId(game_get_space(game, BATHROOM_SPACE), BANDAIDS_ID);
                space_add_objectId(game_get_space(game, BATHROOM_SPACE), MEDICINE_ID);

                game_rules_mission_step(game, mission, step, ge);
                return;
            }
        case(2):
        /*en el tercer paso, se pide a alice curarse, despues se termina la mision*/
        if(command_get_code(game_interface_data_get_cmd_in_pos(game, LAST)) == USE && command_get_lastcmd_success(game_interface_data_get_cmd_in_pos(game, LAST)) == OK && (!strcasecmp(command_get_argument(game_interface_data_get_cmd_in_pos(game, LAST)), BANDAIDS_NAME) || !strcasecmp(command_get_argument(game_interface_data_get_cmd_in_pos(game, LAST)), MEDICINE_NAME))){
            game_set_current_mission(game, REX_MISSION);
            game_set_next_dialogue(game);
            game_set_next_objective(game);
            game_set_show_message(game, TRUE);
            graphic_engine_clear_dialogue(ge);
            return;
        }


    }
    return;
}
void game_rules_bedroom_mission(Game *game, Mission *mission, Graphic_engine *ge)
{
    int step;
    if (!game || !mission || !ge)
        return;
    step = mission_get_current_step(mission);
    switch(step){
        case(0):
        /*cuando bob llega a su habitacion, llamamos a la cinematica del dinosaurio pidiendo ayuda*/
        if(player_get_location(BOB) == BEDROOM){
            game_set_current_mission(game, REX_MISSION);
            game_set_next_dialogue(game);
            game_set_next_objective(game);
            game_set_show_message(game, TRUE);
            graphic_engine_clear_dialogue(ge);
            game_set_current_cinematic(game, BOBS_ROOM);
            return;
        }
        case (1):
        
        default:
            break;
    }
    return;
}
void game_rules_REX_mission(Game *game, Mission *mission, Graphic_engine *ge)
{
    int step;
    if (!game || !mission || !ge)
        return;
    step = mission_get_current_step(mission);
    switch(step){
        case(0):
        /*Bob in his room and Dinasourleg also in BEDROOM*/
        if(game_get_current_player_location(game) == BEDROOM && game_get_object_location(game, DINOSAURLEG_ID) == BEDROOM){
            game_rules_mission_step(game, mission, step, ge);
            return;
        }
        case (1):
        /*Bob busca la pata del dinosaurio y la coge (TAKE)*/
        if (command_get_code(game_interface_data_get_cmd_in_pos(game, LAST)) == TAKE && command_get_lastcmd_success(game_interface_data_get_cmd_in_pos(game, LAST)) == OK && !strcasecmp(command_get_argument(game_interface_data_get_cmd_in_pos(game, LAST)), DINOSAUR_LEG_NAME))
        {
            game_rules_mission_step(game, mission, step, ge);
        
            return;
        }
        case (2):
        /*Bob recluta al dinosaurio (RECRUIT) y acaba la misión; se llama a la siguiente misión: THIRD_FLOOR_MISSION*/
        if (command_get_code(game_interface_data_get_cmd_in_pos(game, LAST)) == RECRUIT && command_get_lastcmd_success(game_interface_data_get_cmd_in_pos(game, LAST)) == OK && !strcasecmp(command_get_argument(game_interface_data_get_cmd_in_pos(game, LAST)), REX_NAME))
        {
            game_set_current_mission(game, THIRD_FLOOR_MISSION);
            game_set_next_dialogue(game);
            game_set_next_objective(game);
            game_set_show_message(game, TRUE);
            graphic_engine_clear_dialogue(ge);
        
            return;
        }
        default:
            break;
    }
    return;
}
void game_rules_third_floor_mission(Game *game, Mission *mission, Graphic_engine *ge)
{
    int step;
    if (!game || !mission || !ge)
        return;
    step = mission_get_current_step(mission);
    switch (step)
    {
    case (0):
        /*Both players go to the upper floor; mission ends when both get there*/
        /*HIDDEN_ROOM es la habitación a la que llegan cuando acceden al tercer piso desde el segundo*/
        if (player_get_location(ALICE) == HIDDENROOM && player_get_location(BOB) == HIDDENROOM)
        {
            space_set_discovered(game_get_space(game, HIDDENROOM), TRUE);
            game_set_current_mission(game, BOSS_MISSION);
            game_set_next_objective(game);
            game_set_next_dialogue(game);
            game_set_show_message(game, TRUE);
            graphic_engine_clear_dialogue(ge);
            return;
        }
        break;
    default:
        break;
    }
    
    return;
}

void game_rules_boss_mission(Game *game, Mission *mission, Graphic_engine *ge)
{
    int step;
    if (!game || !mission || !ge)
        return;
    step = mission_get_current_step(mission);
    switch(step){
        case(0):
        /*cuando se acaba con el boss final, se pasa y spawneamos la llave*/
            if(character_get_health(game_get_character(game, BOSS_ID)) <= 0){
                game_rules_mission_step(game, mission, step, ge);
                space_add_objectId(game_get_space(game,HIDDENROOM), KEY_ID);
                return;
            }
        case(1):
        /*en el segundo paso se pide abrir el link con la llave*/
            if(link_get_is_open(game_get_link(game, HIDDENROOMTOTREASURE)) == TRUE){
                game_rules_mission_step(game, mission, step, ge);
                return;
            }
        case(2):
            /*al final se pide abrir el cofre del tesoro, gift*/
            return;
    }
    return;
}


void game_rules_alice_flashback_init(Game *game)
{
    if (!game)
        return;
    /*movemos a Alice a los espacios reservados para el flashback*/
    player_set_location(game_get_player_in_pos(game, ALICE_TURN), GENERATOR_FLASH_SPACE);
    space_set_discovered(game_get_space(game, GENERATOR_FLASH_SPACE), TRUE);
    return;
}

void game_rules_spawn_ghost(Game *game)
{
    if (!game)
        return;
    character_set_location(game_get_character(game, GHOST_ID), FIRST_STAIRS_ROOM);
    return;
}


void game_rules_spawn_dinosaur_leg(Game *game)
{
    if (!game)
        return;
    space_add_objectId(game_get_space(game, HALL2), DINOSAURLEG_ID);
    return;
}

void game_rules_spawn_final_boss(Game *game)
{
    if (!game)
        return;
    character_set_location(game_get_character(game, BOSS_ID), HIDDENROOM);
    return;
}


void game_rules_mission_step(Game *game, Mission *mission, int step, Graphic_engine *ge)
{
    if (!game || !mission || !ge || step < 0)
        return;
    mission_set_current_step(mission, step + 1);
    game_set_next_dialogue(game);
    game_set_next_objective(game);
    game_set_show_message(game, TRUE);

    /*nos aseguramos de que el mensaje objetivo que hemos puesto le salga a ambos jugadores */
    if(game_get_turn(game) == BOB_TURN){
        game_interface_in_pos_set_objective(game, ALICE_TURN, game_get_objective(game));
        game_set_show_message_in_pos(game , TRUE, ALICE_TURN);
    }else{
        game_interface_in_pos_set_objective(game, BOB_TURN, game_get_objective(game));
        game_set_show_message_in_pos(game , TRUE, BOB_TURN);
    }

    graphic_engine_clear_dialogue(ge);
    return;
}