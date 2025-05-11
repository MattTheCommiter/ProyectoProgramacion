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


#define BOB_PLAYER (game_get_player_in_pos(game, BOB_TURN)) /*!<Define function that gets the player BOB*/
#define ALICE_PLAYER (game_get_player_in_pos(game, ALICE_TURN)) /*!<Defined function that gets the player ALICE*/


/**
 * @brief Define function that shows the next dialogue only to BOB. 
 * This macro sets the message visibility for BOB's turn to TRUE and for ALICE's turn to FALSE.
 * @author Alvaro Inigo
 */
#define show_next_dialogue_to_bob() ( \
    game_set_show_message(game, TRUE, BOB_TURN), \
    game_set_show_message(game, FALSE, ALICE_TURN) \
)


/**
 * @brief Define function that shows the next dialogue only to ALICE.
 * This macro sets the message visibility for ALICE's turn to TRUE and for BOB's turn to FALSE.
 * @author Alvaro Inigo
 */
#define show_next_dialogue_to_alice() ( \
    game_set_show_message(game, TRUE, ALICE_TURN), \
    game_set_show_message(game, FALSE, BOB_TURN) \
)


/*PRIVATE FUNCTIONS*/

/**
 * @brief The sets the current mission to the first one on the game and steps into it.
 * @author Alvaro Inigo
 * @param game a pointer to the game
 */
void game_rules_no_mission(Game *game);

/**
 * @brief controls the game while the current mission is team mission, when finished, calls the next one and steps into it.
 * @author Alvaro Inigo
 * @param game A pointer to the game
 * @param mission a pointer to the current mission
 */
void game_rules_team_mission(Game *game, Mission *mission);

/**
 * @brief controls the game while the current mission is lantern mission, when finished, calls the next one and steps into it.
 * @author Alvaro Inigo
 * @param game A pointer to the game
 * @param mission a pointer to the current mission
 */
void game_rules_lantern_mission(Game *game, Mission *mission);

/**
 * @brief controls the game while the current mission is generator mission, when finished, calls the next one and steps into it.
 * @author Alvaro Inigo
 * @param game A pointer to the game
 * @param mission a pointer to the current mission
 */
void game_rules_generator_mission(Game *game, Mission *mission);

/**
 * @brief controls the game while the current mission is father flashback mission, when finished, calls the next one and steps into it.
 * @author Alvaro Inigo
 * @param game A pointer to the game
 * @param mission a pointer to the current mission
 */
void game_rules_father_mission(Game *game, Mission *mission);

/**
 * @brief controls the game while the current mission is second floor mission, when finished, calls the next one and steps into  and sets the cinematic of the second floor.
 * @author Alvaro Inigo
 * @param game A pointer to the game
 * @param mission a pointer to the current mission
 */
void game_rules_second_floor_mission(Game *game, Mission *mission);

/**
 * @brief controls the game while the current mission is medkit mission, when finished, calls the next one and steps into it.
 * @author Alvaro Inigo
 * @param game A pointer to the game
 * @param mission a pointer to the current mission
 */
void game_rules_medkit_mission(Game *game, Mission *mission);

/**
 * @brief controls the game while the current mission is bedroom mission, when finished, calls the next one and steps into it and sets the current cinematic to the dinosaur one.
 * @author Alvaro Inigo
 * @param game A pointer to the game
 * @param mission a pointer to the current mission
 */
void game_rules_bedroom_mission(Game *game, Mission *mission);

/**
 * @brief controls the game while the current mission is rex mission, when finished, calls the next one and steps into it.
 * @author Alvaro Inigo
 * @param game A pointer to the game
 * @param mission a pointer to the current mission
 */
void game_rules_REX_mission(Game *game, Mission *mission);

/**
 * @brief controls the game while the current mission is thir floor mission, when finished, calls the next one and steps into it and sets the current cinematic to the final boss one.
 * @author Alvaro Inigo
 * @param game A pointer to the game
 * @param mission a pointer to the current mission
 */
void game_rules_third_floor_mission(Game *game, Mission *mission);

/**
 * @brief controls the game while the current mission is boss mission.
 * @author Alvaro Inigo
 * @param game A pointer to the game
 * @param mission a pointer to the current mission
 */
void game_rules_boss_mission(Game *game, Mission *mission);

/**
 * @brief initilizes the flashback for Alice where the father mission takes place, moves Alice to that special space.
 * @author Alvaro Inigo
 * @param game a pointer to the game
 */
void game_rules_alice_flashback_init(Game *game);

/**
 * @brief steps forward in the current mission, sets the next dialogue, sets the next objetctive to both players
 * and modifies the show message boolean of game to TRUE 
 * @author Alvaro Inigo
 * @param game a pointer to the game
 * @param mission a pointer to the current mission
 * @param step the current step
 */

void game_rules_mission_step(Game *game, Mission *mission, int step);

/**
 * @brief spawns the ghost at the first stairs room
 * @author Alvaro Inigo
 * @param game a pointer to the game
 */

void game_rules_spawn_ghost(Game *game);

/**
 * @brief spawns the dino leg at the hall2
 * @author Alvaro Inigo
 * @param game a pointer to the game
 */
void game_rules_spawn_dinosaur_leg(Game *game);

/**
 * @brief spawns the final boss at the hidden room
 * @author Alvaro Inigo
 * @param game a pointer to the game
 */
void game_rules_spawn_final_boss(Game *game);



void game_rules_mission_update(Game *game)
{
    Mission_Code mission_code;
    Mission *mission = NULL;
    if (!game)
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
        game_rules_team_mission(game, mission);
        break;
    case LANTERN_MISSION:
        game_rules_lantern_mission(game, mission);
        break;
    case GENERATOR_MISSION:
        game_rules_generator_mission(game, mission);
        break;
    case FATHER_MISSION:
        game_rules_father_mission(game, mission);
        break;
    case SECOND_FLOOR_MISSION:
        game_rules_second_floor_mission(game, mission);
        break;
    case MEDKIT_MISSION:
        game_rules_medkit_mission(game, mission);
        break;
    case BEDROOM_MISSION:
        game_rules_bedroom_mission(game, mission);
        break;
    case REX_MISSION:
        game_rules_REX_mission(game, mission);
        break;
    case THIRD_FLOOR_MISSION:
        game_rules_third_floor_mission(game, mission);
        break;
    case BOSS_MISSION:
        game_rules_boss_mission(game, mission);
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
    game_set_next_dialogue(game, ALICE);
    /*The first dialogue is displayed to ALICE*/
    show_next_dialogue_to_alice();

    return;
}

void game_rules_team_mission(Game *game, Mission *mission)
{
    int step;
    if (!game || !mission)
        return;
    step = mission_get_current_step(mission);
    switch (step)
    {
    case (0):
        /*Si estan en el mismo equipo, la mision se termina ahi*/
        if (player_get_team(ALICE_PLAYER) == player_get_team(BOB_PLAYER))
        {
            game_next_turn(game);
            game_set_current_mission(game, LANTERN_MISSION);
            game_set_next_objective(game);
            game_set_next_dialogue(game, BOB);
            /*The dialogue for the lantern mission is shown to Bob*/
            show_next_dialogue_to_bob();
            return;
        }
        break;
    default:
        break;
    }
    return;
}
void game_rules_lantern_mission(Game *game, Mission *mission)
{
    int step;
    if (!game || !mission)
        return;
    step = mission_get_current_step(mission);

    switch (step)
    {
    /*en el primer paso, se solicita que se de las baterias a Alice, entonces la mision terminara*/
    case (0):
        if (player_backpack_contains(ALICE_PLAYER, BATTERIES_ID) == TRUE)
        {
            game_next_turn(game);
            game_set_current_mission(game, GENERATOR_MISSION);
            game_set_next_objective(game);
            /*tambien ponemos los mensajes nuevos en el turno de alice*/
            game_interface_in_pos_set_objective(game, ALICE_TURN, game_get_objective(game));
            game_set_next_dialogue(game, ALICE);
            show_next_dialogue_to_alice();

        }
        break;
    default:
        break;
    }
    return;
}

void game_rules_generator_mission(Game *game, Mission *mission)
{
    int step;
    if (!game || !mission)
        return;
    step = mission_get_current_step(mission);
    switch (step)
    {
    case (0):
        /*el primer paso solicita que Alice busque el cuarto con el generador*/
        if (player_get_location(ALICE_PLAYER) == GENERATOR_SPACE)
        {
            game_rules_mission_step(game, mission, step);
            show_next_dialogue_to_alice();
        }
        break;
    case (1):
        /*en el segundo paso, se solicita a Alice que inspeccione el generador, cuando lo hace pasamos a la mission de flashback*/
        if (command_get_code(game_interface_data_get_cmd_in_pos(game, LAST)) == INSPECT && command_get_lastcmd_success(game_interface_data_get_cmd_in_pos(game, LAST)) == OK && !strcasecmp(command_get_argument(game_interface_data_get_cmd_in_pos(game, LAST)), GENERATOR_NAME))
        {
            game_rules_alice_flashback_init(game);
            game_set_current_mission(game, FATHER_MISSION);
            game_set_next_dialogue(game, ALICE);
            show_next_dialogue_to_alice();
            game_set_next_objective(game);
        }
        break;
    default:
        break;
    }
    return;
}
void game_rules_father_mission(Game *game, Mission *mission)
{
    int step;
    if (!game || !mission)
        return;
    step = mission_get_current_step(mission);
    switch (step)
    {
    case (0):
        /*cuando alice llega al espacio del storage room, se pasa en la mision*/
        if (player_get_location(ALICE_PLAYER) == STORAGE_ROOM__FLASH_SPACE)
        {
            game_rules_mission_step(game, mission, step);
            return;
        }
        break;
    case (1):
        /*cuando alice abre la caja de herramientas, se pasa*/
        if (command_get_code(game_interface_data_get_cmd_in_pos(game, LAST)) == INSPECT && command_get_lastcmd_success(game_interface_data_get_cmd_in_pos(game, LAST)) == OK && !strcasecmp(command_get_argument(game_interface_data_get_cmd_in_pos(game, LAST)), TOOLBOX_NAME))
        {
            /*se genera la llave inglesa en el espacio*/
            space_add_objectId(game_get_space(game, STORAGE_ROOM__FLASH_SPACE), WRENCH_ID);
            game_rules_mission_step(game, mission, step);
            return;
        }
        break;
    case (2):
        /*cuando alice vuelve con la llave inglesa al espacio del padre, se vuelve*/
        if (player_get_location(ALICE_PLAYER) == GENERATOR_FLASH_SPACE && player_backpack_contains(game_get_player_in_pos(game, ALICE_TURN), WRENCH_ID))
        {
            game_rules_mission_step(game, mission, step);
            return;
        }
        break;
    case (3):
        /*cuando alice inspecciona el generador, se termina la mision y se encienden las luces*/
        if (player_backpack_contains(game_get_player_in_pos(game, ALICE_TURN), WRENCH_ID) && command_get_code(game_interface_data_get_cmd_in_pos(game, LAST)) == INSPECT && command_get_lastcmd_success(game_interface_data_get_cmd_in_pos(game, LAST)) == OK && !strcasecmp(command_get_argument(game_interface_data_get_cmd_in_pos(game, LAST)), GENERATOR_FLASH_NAME))
        {
            game_set_current_mission(game, SECOND_FLOOR_MISSION);
            player_set_location(ALICE_PLAYER, GENERATOR_SPACE);
            game_set_next_objective(game);
            game_set_next_dialogue(game, ALICE);
            show_next_dialogue_to_alice();

            /*imprimimos el siguiente mensaje tambien en el turno de BOB*/
            game_interface_in_pos_set_objective(game, BOB_TURN, game_get_objective(game));

            game_set_lights_on(game, TRUE);
            return;
        }
        break;
    default:
        break;
    }
    return;
}

void game_rules_second_floor_mission(Game *game, Mission *mission)
{
    int step;
    if (!game || !mission )
        return;
    step = mission_get_current_step(mission);
    switch (step)
    {
    case (0):
        /*En el primer paso se solicita a los jugadores ir al espacio de las escaleras*/
        if (player_get_location(ALICE_PLAYER) == FIRST_STAIRS_ROOM && player_get_location(BOB_PLAYER) == FIRST_STAIRS_ROOM)
        {
            game_rules_mission_step(game, mission, step);
            game_rules_spawn_ghost(game);
            /*hacemos aparecer el cuchillo en el espacio del pasillo*/
            space_add_objectId(game_get_space(game, CORRIDOR1), KNIFE_ID);
            show_next_dialogue_to_bob();
            return;
        }
        break;
    case (1):
        /*Durante el segundo paso, se pide a bob que busque el cuchillo*/
        if (player_backpack_contains(BOB_PLAYER, KNIFE_ID))
        {
            game_rules_mission_step(game, mission, step);
            show_next_dialogue_to_bob();
            return;
        }
        break;
    case (2):
        /*Una vez con el cuchillo, se pide a bob volver al espacio del fantasma*/
        if (player_get_location(BOB_PLAYER) == FIRST_STAIRS_ROOM)
        {
            game_rules_mission_step(game, mission, step);
            show_next_dialogue_to_bob();
            return;
        }
        break;
    case (3):
        /*ahora se pide acabar con el fantasma, despues se abre el link al piso de arriba*/
        if (character_get_health(game_get_character(game, GHOST_ID)) <= 0)
        {
            game_rules_mission_step(game, mission, step);
            show_next_dialogue_to_bob();
            link_set_is_open(game_get_link(game, LIVINGROOMTOHALL1), TRUE);
            return;
        }
        break;
    case (4):
        /*se pide subir al espacio de arriba, cuando suben, se llama a la cinematica de escaleras y se cambia de mision a la de curar a alice*/
        if (player_get_location(BOB_PLAYER) == HALL1 && player_get_location(ALICE_PLAYER) == HALL1)
        {
            /*llamar a la cinematica de alice haciendose daño*/
            game_set_current_cinematic(game, FIRST_STAIRS);
            game_set_current_mission(game, MEDKIT_MISSION);
            game_set_next_objective(game);
            game_set_next_dialogue(game, ALICE);
            game_set_show_message(game, TRUE, ALICE);
            game_set_message(game, game_get_message(game, ALICE), BOB);
            return;
        }
        break;

    default:
        break;
    }
    return;
}
void game_rules_medkit_mission(Game *game, Mission *mission)
{
    int step;
    if (!game || !mission)
        return;
    step = mission_get_current_step(mission);
    switch(step){
        case(0):
        /*en el primer paso se pide llegar al baño a buscar el medkit*/
            if(player_get_location(ALICE_PLAYER) == BATHROOM_SPACE){
                game_rules_mission_step(game, mission, step);
                show_next_dialogue_to_alice();
                return;
            }
        break;
        case(1):
        /*el segundo paso consiste en inspeccionar el medkit*/
            if(command_get_code(game_interface_data_get_cmd_in_pos(game, LAST)) == INSPECT && command_get_lastcmd_success(game_interface_data_get_cmd_in_pos(game, LAST)) == OK && !strcasecmp(command_get_argument(game_interface_data_get_cmd_in_pos(game, LAST)), MEDKIT_NAME)){
                /*metemos los objetos en el espacio(aparecen)*/
                space_add_objectId(game_get_space(game, BATHROOM_SPACE), BANDAIDS_ID);
                space_add_objectId(game_get_space(game, BATHROOM_SPACE), MEDICINE_ID);
                game_rules_mission_step(game, mission, step);
                show_next_dialogue_to_alice();
                return;
            }
        break;
        case(2):
            /*en el tercer paso, se pide a alice curarse, despues se termina la mision*/
            if(command_get_code(game_interface_data_get_cmd_in_pos(game, LAST)) == USE && command_get_lastcmd_success(game_interface_data_get_cmd_in_pos(game, LAST)) == OK && (!strcasecmp(command_get_argument(game_interface_data_get_cmd_in_pos(game, LAST)), BANDAIDS_NAME) || !strcasecmp(command_get_argument(game_interface_data_get_cmd_in_pos(game, LAST)), MEDICINE_NAME))){
                game_set_current_mission(game, BEDROOM_MISSION);
                /*Asignamos la misión a ambos personajes*/
                game_set_next_objective(game);
                game_interface_in_pos_set_objective(game, BOB_TURN, game_get_objective(game));
                game_set_next_dialogue(game, BOB);
                show_next_dialogue_to_bob();
                return;
            }
            break;
        default:
            break;
    }
    return;
}
void game_rules_bedroom_mission(Game *game, Mission *mission)
{
    int step;
    if (!game || !mission)
        return;
    step = mission_get_current_step(mission);
    switch(step){
        case(0):
        /*cuando bob llega a su habitacion, llamamos a la cinematica del dinosaurio pidiendo ayuda*/
        if(player_get_location(BOB_PLAYER) == BEDROOM){
            game_set_current_mission(game, REX_MISSION);
            game_set_next_objective(game);
            space_add_objectId(game_get_space(game, HALL2), DINOSAURLEG_ID);
            show_next_dialogue_to_bob();
            game_set_current_cinematic(game, BOBS_ROOM);    
            return;
        }
        break;
        default:
            break;
    }
    return;
}
void game_rules_REX_mission(Game *game, Mission *mission)
{
    int step;
    if (!game || !mission)
        return;
    step = mission_get_current_step(mission);
    switch(step){
        case(0):
            /*Bob and the leg in HALL2*/
            if(game_get_current_player_location(game) == game_get_object_location(game, DINOSAURLEG_ID)){
                game_rules_mission_step(game, mission, step);
                show_next_dialogue_to_bob();
                return;
            }
        break;
        case (1):
            /*Bob busca la pata del dinosaurio y la coge (TAKE)*/
            if (player_backpack_contains(BOB_PLAYER, DINOSAURLEG_ID))
            {
                game_rules_mission_step(game, mission, step);
                show_next_dialogue_to_bob();
                return;
            }
            break;
        case (2):
            /*Bob recluta al dinosaurio (RECRUIT) y acaba la misión; se llama a la siguiente misión: THIRD_FLOOR_MISSION, se abre el link al piso de arriba*/
            if (character_get_following(game_get_character(game, REX_ID)) == player_get_id(BOB_PLAYER))
            {
                link_set_is_open(game_get_link(game, HALL2TOHIDDENROOM), TRUE);

                game_set_current_mission(game, THIRD_FLOOR_MISSION);
                game_set_next_objective(game);
                game_interface_in_pos_set_objective(game, ALICE_TURN, game_get_objective(game));
                
                game_set_next_dialogue(game, BOB);
                game_set_message(game, game_get_message(game, BOB), ALICE);
                game_set_show_message(game , TRUE, BOB_TURN);
                game_set_show_message(game , TRUE, ALICE_TURN);
                return;
            }
            break;
        default:
            break;
    }
    return;
}
void game_rules_third_floor_mission(Game *game, Mission *mission)
{
    int step;
    if (!game || !mission)
        return;
    step = mission_get_current_step(mission);
    switch (step)
    {
    case (0):
        /*Both players go to the upper floor; mission ends when both get there*/
        /*HIDDEN_ROOM es la habitación a la que llegan cuando acceden al tercer piso desde el segundo*/
        if (player_get_location(ALICE_PLAYER) == HIDDENROOM && player_get_location(BOB_PLAYER) == HIDDENROOM)
        {
            /*We spawn the final boss*/
            game_rules_spawn_final_boss(game);
            /*We update the mission and objective*/
            game_set_current_mission(game, BOSS_MISSION);
            game_set_next_objective(game);
            /*We set the dialogues*/
            game_set_next_dialogue(game, ALICE);
            game_set_message(game, game_get_message(game, ALICE), BOB);
            game_set_show_message(game, TRUE, ALICE);
            game_set_show_message(game, TRUE, BOB);

            game_set_current_cinematic(game, FINAL_BOSS);
            return;
        }
        break;
    default:
        break;
    }
    
    return;
}

void game_rules_boss_mission(Game *game, Mission *mission)
{
    int step;
    if (!game || !mission)
        return;
    step = mission_get_current_step(mission);
    switch(step){
        case(0):
        /*cuando se acaba con el boss final, se pasa y spawneamos la llave*/
            if(character_get_health(game_get_character(game, BOSS_ID)) <= 0){
                game_rules_mission_step(game, mission, step);
                space_add_objectId(game_get_space(game,HIDDENROOM), KEY_ID);
                if(game_get_turn(game) == ALICE_TURN){
                    game_set_message(game, game_get_message(game, ALICE), BOB);
                }else if(game_get_turn(game) == BOB_TURN){
                    game_set_message(game, game_get_message(game, BOB), ALICE);
                }
                game_set_show_message(game, TRUE, ALICE);
                game_set_show_message(game, TRUE, BOB);
                return;
            }
        break;
        case(1):
        /*en el segundo paso se pide abrir el link con la llave*/
            if(link_get_is_open(game_get_link(game, HIDDENROOMTOTREASURE)) == TRUE){
                game_rules_mission_step(game, mission, step);
                return;
            }
        break;
        case(2):
            /*al final se pide abrir el cofre del tesoro, gift, despues aparece la foto familiar.*/
            if(command_get_code(game_interface_data_get_cmd_in_pos(game, LAST)) == INSPECT && command_get_lastcmd_success(game_interface_data_get_cmd_in_pos(game, LAST)) == OK && !strcasecmp(command_get_argument(game_interface_data_get_cmd_in_pos(game, LAST)), GIFTBOX_NAME))
            {
                space_add_objectId(game_get_space(game, TREASUREROOM), FAMILY_PIC_ID);
                game_rules_mission_step(game, mission, step);
            }
            return;
        break;
        case(3):
            /*ahora se pide coger la foto familiar*/
            if(player_backpack_contains(BOB_PLAYER, FAMILY_PIC_ID) || player_backpack_contains(ALICE, FAMILY_PIC_ID)){
                game_set_current_cinematic(game, TREASURE);
                return;
            }
            break;
        default:
            break;
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
    space_add_character(game_get_space(game, FIRST_STAIRS_ROOM), GHOST_ID);
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
    space_add_character(game_get_space(game, HIDDENROOM), BOSS_ID);
    return;
}


void game_rules_mission_step(Game *game, Mission *mission, int step)
{
    if (!game || !mission || step < 0)
        return;
    mission_set_current_step(mission, step + 1);
    game_set_next_dialogue(game, game_get_turn(game));
    game_set_next_objective(game);
    game_set_show_message(game, TRUE, game_get_turn(game));

    /*nos aseguramos de que el mensaje objetivo que hemos puesto le salga a ambos jugadores */
    if(game_get_turn(game) == BOB_TURN){
        game_interface_in_pos_set_objective(game, ALICE_TURN, game_get_objective(game));
        game_set_show_message(game , TRUE, ALICE_TURN);
    }else{
        game_interface_in_pos_set_objective(game, BOB_TURN, game_get_objective(game));
        game_set_show_message(game , TRUE, BOB_TURN);
    }


    return;
}