/**
 * @brief It implements the game update through user actions
 *
 * @file game.c
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#include "game_actions.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
   Private functions
*/

/**
 * @brief doesn't carry out any actions
 *
 * @param game
 */
void game_actions_unknown(Game *game);

/**
 * @brief doesn't carry out any actions
 *
 * @param game
 */
void game_actions_exit(Game *game);

/**
 * @brief moves the character to the space in the south, changing the id's accordingly
 *
 * @param game a pointer to the structure with the game's main information
 */
void game_actions_next(Game *game);

/**
 * @brief moves the character to the space in the north, changing the id's accordingly
 *
 * @param game a pointer to the structure with the game's main information
 */
void game_actions_back(Game *game);



/**
 * @brief takes the object in the space
 * 
 * @param game a pointer to the structure with the game's main information
 */
void game_actions_take(Game *game);

/**
 * @brief drops the object in the space
 * 
 * @param game a pointer to the structure with the game's main information
 */
void game_actions_drop(Game *game);



/**
   Game actions implementation
*/

Status game_actions_update(Game *game, Command *command)
{
  CommandCode cmd;

  game_set_last_command(game, command);

  cmd = command_get_code(command);

  switch (cmd)
  {
  case UNKNOWN:
    game_actions_unknown(game);
    break;

  case EXIT:
    game_actions_exit(game);
    break;

  case NEXT:
    game_actions_next(game);
    break;

  case BACK:
    game_actions_back(game);

    break;
  case TAKE:
    game_actions_take(game);

    break;
  case DROP:
    game_actions_drop(game);
    break;

  default:
    break;
  }

  return OK;
}

/**
   Calls implementation for each action
*/

void game_actions_unknown(Game *game) {}

void game_actions_exit(Game *game) {}

void game_actions_next(Game *game)
{
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);
  if (space_id == NO_ID)
  {
    return;
  }

  current_id = space_get_south(game_get_space(game, space_id));
  if (current_id != NO_ID)
  {
    game_set_player_location(game, current_id);
  }

  return;
}

void game_actions_back(Game *game)
{
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);

  if (NO_ID == space_id)
  {
    return;
  }

  current_id = space_get_north(game_get_space(game, space_id));
  if (current_id != NO_ID)
  {
    game_set_player_location(game, current_id);
  }

  return;
}

void game_actions_take(Game *game)
{
  if (!game)
  {
    return;
  }

  if (game_get_player_location(game) == game_get_object_location(game))
  {
    player_set_object(game_get_player(game), object_get_id(game_get_object(game))); /*Cambiamos el id del objeto del jugador*/
    space_set_objectId(game_get_space(game, game_get_player_location(game)), NO_ID); /*Cambiamos el object Id del espacio que tenía el objeto a NO_ID*/
    
  }
}

void game_actions_drop(Game *game)
{
  if (!game)
  {
    return;
  }

  if (player_get_object(game_get_player(game)) != NO_ID)
  {
    
    space_set_objectId(game_get_space(game, game_get_player_location(game)), object_get_id(game_get_object(game))); /*Cambiamos el object Id del espacio a la del objeto*/
    player_set_object(game_get_player(game), NO_ID); /*Cambiamos el id del objeto del jugador a NO_ID*/
  }
}