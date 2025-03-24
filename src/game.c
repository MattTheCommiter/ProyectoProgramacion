/**
 * @brief It implements the game structure
 *
 * @file game.c
 * @author Alvaro Inigo
 * @version 0.1
 * @date 12-02-2025
 * @copyright GNU Public License
 */

#include "game.h"
#include "gameReader.h"
#include "character.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _Game
{
  Object *objects[MAX_OBJECTS];          /*!<Pointer array to the objects that are present in the game*/
  int n_objects;                         /*!<Number of objects in the game*/
  Player *player;                        /*!<Pointer to the player that is present in the game*/
  Space *spaces[MAX_SPACES];             /*!<Array of Spaces*/
  int n_spaces;                          /*!<Number of spaces in the game*/
  Character *characters[MAX_CHARACTERS]; /*!<Number of spaces in the game*/
  int n_characters;                      /*!<Number of characters in the game*/
  Command *last_cmd;                     /*!<Pointer to the last command introduced by the user*/
  Status command_success;                /*!<Status that stablishes wheter the command was successful*/
  Bool finished;                         /*!<Boolean that establishes whether the game has ended or not*/
  char message[MAX_MESSAGE];             /*!<String that has the message of the character showed in the game*/
  char description[MAX_MESSAGE];         /*!<String that has the description of an object inspected in the game*/
};
/**
   Private functions
*/

/**
 * @brief returns the id of the space located in the position number "position" (it is an integer) of the array of spaces inside the "game" structure
 *
 * @param game a pointer to the structure with the game's main information
 * @param position the position of the space of which we want to get the id
 * @return Id the id of the space
 */
Id game_get_space_id_at(Game *game, int position);

/**
   Game interface implementation
*/

Status game_create(Game **game)
{
  int i;
  if (!game)
    return ERROR;
  (*game) = (Game *)calloc(1, sizeof(Game));
  if (!(*game))
    return ERROR;
  for (i = 0; i < MAX_SPACES; i++)
  {
    (*game)->spaces[i] = NULL;
  }

  /*initialize the game */
  (*game)->n_spaces = 0;
  (*game)->n_characters = 0;
  (*game)->n_objects = 0;
  (*game)->n_objects = 0;
  (*game)->last_cmd = command_create();
  (*game)->finished = FALSE;
  (*game)->command_success = OK;
  (*game)->message[0] = '\0';
  (*game)->description[0] = '\0';

  return OK;
}

Status game_create_from_file(Game **game, char *filename)
{

  if (game_create(game) == ERROR)
  {
    return ERROR;
  }

  if (gameReader_load_spaces((*game), filename) == ERROR)
  {
    return ERROR;
  }
  if (gameReader_load_objects((*game), filename) == ERROR)
  {
    return ERROR;
  }
  if(gameReader_load_players((*game), filename) == ERROR)
  {
    return ERROR;
  }
  if(gameReader_load_characters((*game), filename) == ERROR)
  {
    return ERROR;
  }

  return OK;
}

Status game_destroy(Game *game)
{
  int i = 0;

  for (i = 0; i < game->n_spaces; i++)
  {
    if (game->spaces[i])
    {
      space_destroy(game->spaces[i]);
    }
  }
  for (i = 0; i < game->n_objects; i++)
  {
    if (game->objects[i])
      object_destroy(game->objects[i]);
  }
  for (i = 0; i < 2; i++)
  {
    if (game->characters[i])
      character_destroy(game->characters[i]);
  }
  if (game->player)
    player_destroy(game->player);
  if (game->last_cmd)
    command_destroy(game->last_cmd);

  free(game);

  return OK;
}

Space *game_get_space(Game *game, Id id)
{
  int i = 0;

  if (id == NO_ID)
  {
    return NULL;
  }

  for (i = 0; i < game->n_spaces; i++)
  {
    if (id == space_get_id(game->spaces[i]))
    {
      return game->spaces[i];
    }
  }

  return NULL;
}

Id game_get_player_location(Game *game)
{
  return player_get_location(game->player);
}

Status game_set_player_location(Game *game, Id id)
{
  if (id == NO_ID)
  {
    return ERROR;
  }
  if (!player_set_location(game->player, id))
    return ERROR;

  return OK;
}

Id game_get_object_location(Game *game, Id objectId)
{
  int i;

  for (i = 0; i < game->n_spaces; i++)
  {
    if (space_object_belongs(game->spaces[i], objectId))
    {
      return space_get_id(game->spaces[i]);
    }
  }
  return NO_ID;
}

Status game_set_object_location(Game *game, Id id, Id objectId)
{

  if (id == NO_ID)
  {
    return ERROR;
  }
  if (!(space_add_objectId(game_get_space(game, id), objectId)))
    return ERROR;

  return OK;
}

Command *game_get_last_command(Game *game) { return game->last_cmd; }

Status game_set_last_command(Game *game, Command *command)
{
  if (!game || !command)
  {
    return ERROR;
    game->last_cmd = command;
  }

  return OK;
}

Bool game_get_finished(Game *game) { return game->finished; }

Status game_set_finished(Game *game, Bool finished)
{
  if (!game)
  {
    return ERROR;
  }
  game->finished = finished;

  return OK;
}

void game_print(Game *game)
{
  int i = 0;

  printf("\n\n-------------\n\n");

  printf("=> Spaces: \n");
  for (i = 0; i < game->n_spaces; i++)
  {
    space_print(game->spaces[i]);
  }

  for (i = 0; i < game->n_objects; i++)
  {
    printf("=> Object '%s' location: %ld", object_get_name(game_get_object_in_pos(game, i)), game_get_object_location(game, object_get_id(game->objects[i])));
  }
  printf("=> Player location: %d\n", (int)game_get_player_location(game));
}

Player *game_get_player(Game *game)
{
  if (!game)
    return NULL;
  return game->player;
}

Object *game_get_object_in_pos(Game *game, int pos)
{
  if ((game == NULL) || pos > game->n_objects)
    return NULL;
  return game->objects[pos];
}
/**
   Implementation of private functions
*/

Id game_get_space_id_at(Game *game, int position)
{
  if (position < 0 || position >= game->n_spaces)
  {
    return NO_ID;
  }

  return space_get_id(game->spaces[position]);
}

Status game_add_space(Game *game, Space *space)
{
  if ((space == NULL) || (game->n_spaces >= MAX_SPACES))
  {
    return ERROR;
  }

  game->spaces[game->n_spaces] = space;
  game->n_spaces++;

  return OK;
}

Status game_add_object(Game *game, Object *object)
{
  if ((object == NULL) || (game->n_objects >= MAX_OBJECTS))
  {
    return ERROR;
  }

  game->objects[game->n_objects] = object;
  game->n_objects++;

  return OK;
}

Object *game_get_object(Game *game, Id id){
  int i;
  Object *object = NULL;
  if(!game || id == NO_ID) return NULL;
  for(i = 0; i < game_get_n_objects(game); i++){
    object = game_get_object_in_pos(game, i);
    if(object_get_id(object) == id){
      return object;
    }
  }
  return NULL;
}

Id game_get_object_id_at(Game *game, int position)
{
  if (position < 0 || position >= game->n_objects)
  {
    return NO_ID;
  }

  return object_get_id(game->objects[position]);
}

Status game_add_character(Game *game, Character *character)
{
  if ((character == NULL) || (game->n_characters >= MAX_CHARACTERS))
  {
    return ERROR;
  }

  game->characters[game->n_characters] = character;
  game->n_characters++;

  return OK;
}

Id game_get_character_id_at(Game *game, int position)
{
  if (position < 0 || position >= game->n_characters)
  {
    return NO_ID;
  }

  return character_get_id(game->characters[position]);
}

Character *game_get_character(Game *game, Id id)
{
  int i;
  if ((game == NULL) || id == NO_ID)
    return NULL;
  for (i = 0; i < game->n_characters; i++)
  {
    if (id == game_get_character_id_at(game, i))
    {
      return game->characters[i];
    }
  }
  return NULL;
}

Id game_get_objectId_from_name(Game *game, char *name)
{
  int i;
  if (!game || !name)
  {
    return NO_ID;
  }
  for (i = 0; i < game->n_objects; i++)
  {
    if (strcmp(object_get_name(game->objects[i]), name) == 0)
    {
      return object_get_id(game->objects[i]);
    }
  }
  return NO_ID;
}

char *game_get_message(Game *game)
{
  if (!game)
    return NULL;

  return game->message;
}

Status game_set_message(Game *game, char *msg)
{
  if (!game || !msg)
    return ERROR;

  strcpy(game->message, msg);
  return OK;
}

int game_get_n_objects(Game *game)
{
  if (!game)
  {
    return -1;
  }
  return game->n_objects;
}

int game_get_n_characters(Game *game)
{
  if (!game)
  {
    return -1;
  }
  return game->n_characters;
}

Id game_get_character_location(Game *game, Id character_id)
{
  int i;
  if (!game)
    return NO_ID;
  for (i = 0; i < game->n_spaces; i++)
  {
    if (space_get_character(game_get_space(game, game_get_space_id_at(game, i))) == character_id)
    {
      return game_get_space_id_at(game, i);
    }
  }
  return NO_ID;
}

Character *game_get_character_from_name(Game *game, char *name)
{
  int i;
  if (!game || !name)
  {
    return NULL;
  }
  for (i = 0; i < game->n_characters; i++)
  {
    if (strcmp(character_get_name(game->characters[i]), name) == 0)
    {
      return game->characters[i];
    }
  }
  return NULL;
}


Status game_set_last_command_success(Game *game, Status success)
{
  if (!game)
  {
    return ERROR;
  }
  game->command_success = success;
  return OK;
}

Status game_get_last_command_success(Game *game)
{
  if (!game)
  {
    return ERROR;
  }
  return game->command_success;
}

Status game_set_description(Game *game, char *desc)
{

  if(!game || !desc){
    return ERROR;
  }
  strcpy(game->description, desc);
  return OK;
}
char *game_get_description(Game *game)
{
  if(!game)
  {
    return NULL;
  }
  return game->description;
}

/*Funcion temporal, hasta que cambiemos player por un array de jugadores
necesaria por ahora para el modulo de game reader
*/

Status game_set_player(Game *game, Player *player){
  if(!game || !player)
  {
    return ERROR;
  }
  game->player = player;
  return OK;
}