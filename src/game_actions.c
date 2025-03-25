/**
 * @brief It implements the game update through user actions
 *
 * @file game.c
 * @author Matteo Artuñedo, AGL (modifications for updating Player to include a backpack)
 * @version 0.1
 * @date 22-03-2025
 * @copyright GNU Public License
 */

#include "../include/game_actions.h"
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
 * @author Matteo Artunedo, AGL (modifications to update to player's backpack)
 *
 * @param game a double pointer to the structure with the game's main information
 * @param arg the name of the object taken.
 */
void game_actions_take(Game *game, char *arg);

/**
 * @brief drops the object in the space
 *
 * @date 10-02-2025
 * @author Matteo Artunedo, AGL (modifications to update to player's backpack)
 *
 * @param game a double pointer to the structure with the game's main information
 */
void game_actions_drop(Game *game, char *arg);

/**
 * @brief Moves the player to the space on its left
 * @date 20-02-2025
 * @author Alvaro Inigo
 * @param game a pointer to the game
 */
void game_actions_left(Game *game);
/**
 * @brief Moves the player to the space on its right
 * @date 20-02-2025
 * @author Alvaro Inigo
 * @param game a pointer to the game
 */
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
/**
 * @brief Attack, both the player or a non friendly character at the same space loses health, if the character dies, it cannot be attacked anymore.
 * @date 25-02-2025
 * @author Alvaro Inigo
 * @param game a pointer to the game
 */
void game_actions_attack(Game *game);

/**
 * @brief The command that allows the player to inspect an object
 * @date 25-02-2025
 * @author Alvaro Inigo
 * @param game a pointer to the game
 */
void game_actions_inspect(Game *game, char *arg);
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
    game_actions_drop(game, command_get_argument(command));
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
  case INSPECT:
    game_actions_inspect(game, command_get_argument(command));
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
  if (!game)
  {
    game_set_last_command_success(game, ERROR);
    return;
  }
  space_id = game_get_current_player_location(game);
  if (space_id == NO_ID)
  {
    game_set_last_command_success(game, ERROR);
    return;
  }

  current_id = space_get_south(game_get_space(game, space_id));
  if (current_id != NO_ID)
  {
    game_set_current_player_location(game, current_id);
    space_set_discovered(game_get_space(game, current_id), TRUE);
    game_set_last_command_success(game, OK);
    return;
  }
  game_set_last_command_success(game, ERROR);
  return;
}

void game_actions_back(Game *game)
{
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_current_player_location(game);

  if (NO_ID == space_id || !game)
  {
    game_set_last_command_success(game, ERROR);
    return;
  }

  current_id = space_get_north(game_get_space(game, space_id));
  if (current_id != NO_ID)
  {
    game_set_current_player_location(game, current_id);
    space_set_discovered(game_get_space(game, current_id), TRUE);
    game_set_last_command_success(game, OK);
    return;
  }
  game_set_last_command_success(game, ERROR);
  return;
}

void game_actions_take(Game *game, char *arg)
{
  Id objectId = NO_ID;
  int i;
  Bool found = FALSE;

  /*If the arguments (pointers) are NULL or the bacpack of the current player is full, nothing happens*/
  if (!game || arg == NO_ARG || player_backpack_is_full(game_get_current_player(game)))
  {
    game_set_last_command_success(game, ERROR);
    return;
  }

  /*Find the object with the specified name "arg" in the game */
  for (i = 0; i < game_get_n_objects(game) && found == FALSE; i++)
  {
    if (strcasecmp(arg, object_get_name(game_get_object_in_pos(game, i))) == 0)
    {
      found = TRUE;
      i--;
    }
  }
  if (found == FALSE)
  {
    game_set_last_command_success(game, ERROR);
    return;
  }

  /*Now, that we have found the object with the name, we get its Id*/
  objectId = game_get_object_id_at(game, i);

  if (game_get_object_location(game, objectId) == NO_ID)
  {
    game_set_last_command_success(game, ERROR);
    return;
  }

  /*We check that the player and the object are in the same space*/
  if (game_get_current_player_location(game) == game_get_object_location(game, objectId))
  {
    /*We add the object to the player's backpack*/
    if (player_add_object_to_backpack(game_get_current_player(game), objectId) == OK)
    {
      /* We change the objectId of the space where the object was located to NO_ID */
      space_delete_object(game_get_space(game, game_get_current_player_location(game)), objectId);
      game_set_last_command_success(game, OK);
    }
    else
    {
      game_set_last_command_success(game, ERROR);
    }
    return;
  }
  game_set_last_command_success(game, ERROR);
  return;
}

void game_actions_drop(Game *game, char *arg)
{
  Id objectId = NO_ID;
  int i;
  Bool found = FALSE;
  Player *player = NULL;
  /* If the arguments (pointers) are NULL, nothing happens */
  if (!game || arg == NO_ARG)
  {
    game_set_last_command_success(game, ERROR);
    return;
  }

  /* Check if the player's backpack is empty */
  if (player_backpack_is_empty(game_get_current_player(game)))
  {
    game_set_last_command_success(game, ERROR);
    return;
  }
  /* Find the object with the given name in the game */
  player = game_get_current_player(game);
  for (i = 0; i < player_get_num_objects_in_backpack(player) && found == FALSE; i++)
  {

    objectId = player_get_backpack_object_id_at(player, i);
    if (strcasecmp(arg, object_get_name(game_get_object(game, objectId))) == 0)
    {
      found = TRUE;
      i--;
    }
  }
  if (found == FALSE)
  {
    game_set_last_command_success(game, ERROR);
    return;
  }

  /* We add the object to the space where the player is located */
  if (space_add_objectId(game_get_space(game, game_get_current_player_location(game)), objectId) == OK)
  {
    /* We remove the object from the player's backpack */
    player_remove_object_from_backpack(game_get_current_player(game), objectId);
    game_set_last_command_success(game, OK);
  }
  else
  {
    game_set_last_command_success(game, ERROR);
  }
  return;
}

void game_actions_left(Game *game)
{
  Id currentId = NO_ID, nextId = NO_ID;
  if (!game)
  {
    game_set_last_command_success(game, ERROR);
    return;
  }
  currentId = game_get_current_player_location(game);
  if (currentId == NO_ID)
  {
    game_set_last_command_success(game, ERROR);
    return;
  }
  nextId = space_get_west(game_get_space(game, currentId));
  if (nextId != NO_ID)
  {
    game_set_current_player_location(game, nextId);
    space_set_discovered(game_get_space(game, nextId), TRUE);
    game_set_last_command_success(game, OK);
    return;
  }
  game_set_last_command_success(game, ERROR);
  return;
}

void game_actions_right(Game *game)
{
  Id currentId = NO_ID;
  Id nextId = NO_ID;
  if (!game)
  {
    game_set_last_command_success(game, ERROR);
    return;
  }
  currentId = game_get_current_player_location(game);
  if (currentId == NO_ID)
  {
    game_set_last_command_success(game, ERROR);
    return;
  }
  nextId = space_get_east(game_get_space(game, currentId));
  if (nextId != NO_ID)
  {
    game_set_current_player_location(game, nextId);
    space_set_discovered(game_get_space(game, nextId), TRUE);
    game_set_last_command_success(game, OK);
    return;
  }
  game_set_last_command_success(game, ERROR);
  return;
}
void game_actions_chat(Game *game)
{
  if (!game)
  {
    game_set_last_command_success(game, ERROR);
    return;
  }
  if (!character_get_friendly(game_get_character(game, space_get_character(game_get_space(game, game_get_current_player_location(game))))))
  {
    game_set_last_command_success(game, ERROR);
    return;
  }

  game_set_message(game, character_get_message(game_get_character(game, space_get_character(game_get_space(game, game_get_current_player_location(game))))));
  game_set_last_command_success(game, OK);
  return;
}

void game_actions_attack(Game *game)
{
  /*Generate a random number, it determinates who loses health*/
  int num;
  Character *cha = NULL;
  Id cha_Id = NO_ID;
  srand(time(NULL));
  num = rand() % 10;
  if (!game)
  {
    return;
  }
  /*first we get the character at the space*/
  cha_Id = space_get_character(game_get_space(game, game_get_current_player_location(game)));
  if (cha_Id == NO_ID)
  {
    game_set_last_command_success(game, ERROR);
    return;
  }
  cha = game_get_character(game, cha_Id);
  if (cha == NULL)
  {
    game_set_last_command_success(game, ERROR);
    return;
  }
  /*We check if the character is friendly or not, if its friendly , we cannot attack him*/
  if (character_get_friendly(cha) == TRUE || character_get_health(cha) == 0)
  {
    game_set_last_command_success(game, ERROR);
    return;
  }
  /*Depending on the number genered, character of player lose health*/
  if (num <= 4)
  {
    player_set_health(game_get_current_player(game), player_get_health(game_get_current_player(game)) - 1);
    game_set_last_command_success(game, OK);
  }
  else
  {
    character_set_health(cha, character_get_health(cha) - 1);
    game_set_last_command_success(game, OK);
  }
  return;
}

void game_actions_inspect(Game *game, char *arg)
{
  Id objectId = NO_ID;
  Space *current_space = NULL;
  int i;
  Object *object = NULL;
  Bool found = FALSE;

  if (!game || !arg)
  {
    game_set_last_command_success(game, ERROR);
    return;
  }
  /*We find the object with tha name arg*/
  for (i = 0; i < game_get_n_objects(game); i++)
  {
    object = game_get_object_in_pos(game, i);
    if (strcasecmp(object_get_name(object), arg) == 0)
    {
      found = TRUE;
      break;
    }
  }

  if (found == FALSE)
  {
    game_set_last_command_success(game, ERROR);
    return;
  }
  objectId = object_get_id(object);
  current_space = game_get_space(game, game_get_current_player_location(game));
  if (current_space == NULL)
  {
    game_set_last_command_success(game, ERROR);
    return;
  }
  if (space_object_belongs(current_space, objectId) == FALSE && player_backpack_contains(game_get_current_player(game), objectId) == FALSE)
  {
    game_set_last_command_success(game, ERROR);
    return;
  }

  game_set_description(game, object_get_description(game_get_object(game, objectId)));
  game_set_last_command_success(game, OK);
  return;
}