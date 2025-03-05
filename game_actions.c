/**
 * @brief It implements the game update through user actions
 *
 * @file game.c
 * @author Matteo Artuñedo
 * @version 0.1
 * @date 10-02-2025
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
 * @date 27-01-2025
 * @author Profesores
 *
 * @param game
 */
void game_actions_unknown(Game **game);

/**
 * @brief doesn't carry out any actions
 *
 * @date 27-01-2025
 * @author Profesores
 *
 * @param game
 */
void game_actions_exit(Game **game);

/**
 * @brief moves the character to the space in the south, changing the id's accordingly
 *
 * @date 27-01-2025
 * @author Profesores
 * 
 * @param game a double pointer to the structure with the game's main information
 */
void game_actions_next(Game **game);

/**
 * @brief moves the character to the space in the north, changing the id's accordingly
 *
 * @date 27-01-2025
 * @author Profesores
 * 
 * @param game a double pointer to the structure with the game's main information
 */
void game_actions_back(Game **game);

/**
 * @brief takes the object in the space
 *
 * @date 10-02-2025
 * @author Matteo Artunedo
 * 
 * @param game a double pointer to the structure with the game's main information
 * @param arg a code which corresponds to the object being taken
 */
void game_actions_take(Game **game, ArgumentCode arg);

/**
 * @brief drops the object in the space
 *
 * @date 10-02-2025
 * @author Matteo Artunedo
 * 
 * @param game a double pointer to the structure with the game's main information
 */
void game_actions_drop(Game **game);

void game_actions_left(Game **game);

void game_actions_right(Game **game);

/**
 * @brief chats with a character in the same space, assigning the character's message to the message parameter in game
 *
 * @date 04-03-2025
 * @author Matteo Artunedo
 * 
 * @param game a double pointer to the structure with the game's main information
 */
void game_actions_chat(Game **game);

/**
   Game actions implementation
*/

Status game_actions_update(Game **game, Command *command)
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
    game_actions_take(game, command_get_argument(command));
    break;
  case DROP:
    game_actions_drop(game);
    break;
  case LEFT:
    game_actions_left(game);
    break;
  case RIGHT:
    game_actions_right(game);
    break;

  default:
    break;
  }

  return OK;
}

/**
   Calls implementation for each action
*/

void game_actions_unknown(Game **game) {}

void game_actions_exit(Game **game) {}

void game_actions_next(Game **game)
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

void game_actions_back(Game **game)
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

void game_actions_take(Game **game, ArgumentCode arg)
{ Id objectId=NO_ID;
  /*If the pointers are NULL or the player already has an object, nothing happens*/
  if (!game || player_get_object(game_get_player(game)) != NO_ID || arg==NO_ARG)
  {
    return;
  }
  switch(arg){
    case SEED:
      objectId = game_get_objectId_from_name(game, "Seed");
      break;
    case CRUMB:
      objectId = game_get_objectId_from_name(game, "Crumb");
      break;
    case GRAIN:
      objectId = game_get_objectId_from_name(game, "Grain");
      break;
    case LEAF:
      objectId = game_get_objectId_from_name(game, "Leaf");
      break;
    default:
      break;
  }

    /*We check that the player and the object are in the same space*/
  if (game_get_player_location(game) == game_get_object_location(game, objectId))
  { /*We change the id of the object that the player is carrying*/
    player_set_object(game_get_player(game), objectId);
    /*We change the objectId of the space where the object was located to NO_ID*/
    space_delete_object(game_get_space(game, game_get_player_location(game)), objectId);
  }
}

void game_actions_drop(Game **game)
{
  if (!game)
  {
    return;
  }
  /*We check that the player is carrying an object*/
  if (player_get_object(game_get_player(game)) != NO_ID)
  {
    /*We change the objectId of the space where the player is located to the Id of the object being dropped*/
    space_add_objectId(game_get_space(game, game_get_player_location(game)),game_get_objectId_from_name(game,"Seed"));
    /*We change the Id of the player's object to NO_ID*/
    player_set_object(game_get_player(game), NO_ID);
  }
}

void game_actions_left(Game **game){
  Id currentId = NO_ID, nextId = NO_ID;
  if(!game){
    return;
  }
  currentId = game_get_player_location(game);
  if(currentId == NO_ID){
    return;
  }
  nextId = space_get_west(game_get_space(game,currentId));
  if(nextId != NO_ID){
    game_set_player_location(game,nextId);
  }
  return;

}

void game_actions_right(Game **game){
  Id currentId = NO_ID;
  Id nextId = NO_ID;
  if(!game){
    return;
  }
  currentId = game_get_player_location(game);
  if(currentId == NO_ID){
    return;
  }
  nextId = space_get_east(game_get_space(game,currentId));
  if(nextId != NO_ID){
    game_set_player_location(game,nextId);
  }
}
void game_actions_chat(Game **game){
  if(!game) return;

  if(!character_get_friendly(game_get_character(game, space_get_character(game_get_space (game ,game_get_player_location(game)))))){
    return;
  }

  game_set_message(game, character_get_message(game_get_character(game, space_get_character(game_get_space (game ,game_get_player_location(game))))));
  return;
}