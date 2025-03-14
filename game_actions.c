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
#include <time.h>
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
void game_actions_unknown(Game *game);

/**
 * @brief doesn't carry out any actions
 *
 * @date 27-01-2025
 * @author Profesores
 *
 * @param game
 */
void game_actions_exit(Game *game);

/**
 * @brief moves the character to the space in the south, changing the id's accordingly
 *
 * @date 27-01-2025
 * @author Profesores
 *
 * @param game a double pointer to the structure with the game's main information
 */
void game_actions_next(Game *game);

/**
 * @brief moves the character to the space in the north, changing the id's accordingly
 *
 * @date 27-01-2025
 * @author Profesores
 *
 * @param game a double pointer to the structure with the game's main information
 */
void game_actions_back(Game *game);

/**
 * @brief takes the object in the space
 *
 * @date 10-02-2025
 * @author Matteo Artunedo
 *
 * @param game a double pointer to the structure with the game's main information
 * @param arg a code which corresponds to the object being taken
 */
void game_actions_take(Game *game, char *arg);

/**
 * @brief drops the object in the space
 *
 * @date 10-02-2025
 * @author Matteo Artunedo
 *
 * @param game a double pointer to the structure with the game's main information
 */
void game_actions_drop(Game *game);

void game_actions_left(Game *game);

void game_actions_right(Game *game);

/**
 * @brief chats with a character in the same space, assigning the character's message to the message parameter in game
 *
 * @date 04-03-2025
 * @author Matteo Artunedo
 *
 * @param game a double pointer to the structure with the game's main information
 */
void game_actions_chat(Game *game);

void game_actions_attack(Game *game);
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
    game_actions_take(game, command_get_argument(command));
    break;
  case CHAT:
    game_actions_chat(game);
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
  case ATTACK:
    game_actions_attack(game);
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
  if(!game){
    game_set_last_command_success(game ,ERROR);
    return;
  }
  space_id = game_get_player_location(game);
  if (space_id == NO_ID)
  {
    game_set_last_command_success(game ,ERROR);
    return;
  }

  current_id = space_get_south(game_get_space(game, space_id));
  if (current_id != NO_ID)
  {
    game_set_player_location(game, current_id);
    game_set_last_command_success(game ,OK);
    return;
  }
  game_set_last_command_success(game ,ERROR);
  return;
}

void game_actions_back(Game *game)
{
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);

  if (NO_ID == space_id || !game)
  {
    game_set_last_command_success(game ,ERROR);
    return;
  }

  current_id = space_get_north(game_get_space(game, space_id));
  if (current_id != NO_ID)
  {
    game_set_player_location(game, current_id);
    game_set_last_command_success(game ,OK);
    return;
  }
  game_set_last_command_success(game ,ERROR);
  return;
}

void game_actions_take(Game *game, char *arg)
{
  Id objectId = NO_ID;
  int i;
  Bool found = FALSE;

  /*If the pointers are NULL or the player already has an object, nothing happens*/
  if (!game || player_get_object(game_get_player(game)) != NO_ID || arg == NO_ARG)
  {
    game_set_last_command_success(game ,ERROR);
    return;
  }
  
  /*first, we find the object with the name "arg" */

  for(i = 0; i < game_get_n_objects(game) && found == FALSE; i++){
    if(strcasecmp(arg, object_get_name(game_get_object_in_pos(game, i))) == 0){
      found = TRUE;
      i--;
    }
  }
  if(found == FALSE){
    game_set_last_command_success(game ,ERROR);
    return;
  }
  
  /*Now, that we have found the object with the name, we get its Id*/
  objectId = game_get_object_id_at(game, i);


  if(game_get_object_location(game, objectId) == NO_ID){
    game_set_last_command_success(game ,ERROR);
    return;
  }
  /*We check that the player and the object are in the same space*/
  if (game_get_player_location(game) == game_get_object_location(game, objectId))
  { /*We change the id of the object that the player is carrying*/
    player_set_object(game_get_player(game), objectId);
    /*We change the objectId of the space where the object was located to NO_ID*/
    space_delete_object(game_get_space(game, game_get_player_location(game)), objectId);
    game_set_last_command_success(game ,OK);
    return;
  }
  game_set_last_command_success(game ,ERROR);
  return;
}

void game_actions_drop(Game *game)
{
  if (!game)
  {
    game_set_last_command_success(game ,ERROR);
    return;
  }
  /*We check that the player is carrying an object*/
  if (player_get_object(game_get_player(game)) != NO_ID)
  {
    /*We change the objectId of the space where the player is located to the Id of the object being dropped*/
    space_add_objectId(game_get_space(game, game_get_player_location(game)),player_get_object(game_get_player(game)));
    /*We change the Id of the player's object to NO_ID*/
    player_set_object(game_get_player(game), NO_ID);
    game_set_last_command_success(game ,OK);
    return;
  }
  game_set_last_command_success(game ,ERROR);
  return;
}

void game_actions_left(Game *game)
{
  Id currentId = NO_ID, nextId = NO_ID;
  if (!game)
  {
    game_set_last_command_success(game ,ERROR);
    return;
  }
  currentId = game_get_player_location(game);
  if (currentId == NO_ID)
  {
    game_set_last_command_success(game ,ERROR);
    return;
  }
  nextId = space_get_west(game_get_space(game, currentId));
  if (nextId != NO_ID)
  {
    game_set_player_location(game, nextId);
    game_set_last_command_success(game ,OK);
    return;
  }
  game_set_last_command_success(game ,ERROR);
  return;
}

void game_actions_right(Game *game)
{
  Id currentId = NO_ID;
  Id nextId = NO_ID;
  if (!game)
  {
    game_set_last_command_success(game ,ERROR);
    return;
  }
  currentId = game_get_player_location(game);
  if (currentId == NO_ID)
  {
    game_set_last_command_success(game ,ERROR);
    return;
  }
  nextId = space_get_east(game_get_space(game, currentId));
  if (nextId != NO_ID)
  {
    game_set_player_location(game, nextId);
    game_set_last_command_success(game ,OK);
    return;
  }
  game_set_last_command_success(game ,ERROR);
  return;
}
void game_actions_chat(Game *game)
{
  if (!game){
    game_set_last_command_success(game ,ERROR);
    return;
  }
  if (!character_get_friendly(game_get_character(game, space_get_character(game_get_space(game, game_get_player_location(game))))))
  {
    game_set_last_command_success(game ,ERROR);
    return;
  }

  game_set_message(game, character_get_message(game_get_character(game, space_get_character(game_get_space(game, game_get_player_location(game))))));
  game_set_last_command_success(game ,OK);
  return;
}

void game_actions_attack(Game *game)
{
  
  int num;
  Character *cha = NULL;
  Id cha_Id = NO_ID;
  srand(time(NULL));
  num = rand() % 10;
  if (!game){
    return;
  }
  cha_Id = space_get_character(game_get_space(game, game_get_player_location(game)));
  if(cha_Id == NO_ID){
    game_set_last_command_success(game ,ERROR);
    return;
  }
  cha = game_get_character(game, cha_Id);
  if(cha == NULL){
    game_set_last_command_success(game ,ERROR);
    return;
  }
  if(character_get_friendly(cha) == TRUE || character_get_health(cha) == 0){
    game_set_last_command_success(game ,ERROR);
    return;
  }
  if(num <= 4){
    player_set_health(game_get_player(game), player_get_health(game_get_player(game)) - 1);
    game_set_last_command_success(game ,OK);
  }else{
    character_set_health(cha, character_get_health(cha) - 1);
    game_set_last_command_success(game ,OK);
  }
  return;


  
}