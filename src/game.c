/**
 * @brief It implements the game structure
 *
 * @file game.c
 * @author Alvaro Inigo, Matteo Artunedo (multiplayer implementation and command history), Guilherme Povedano (link implementation)
 * @version 0.1
 * @date 12-02-2025
 * @copyright GNU Public License
 */

#include "game.h"
#include "gameReader.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
 * @brief Private structure that saves the 3 last commands of a player and the messages and descriptions of object they chat with and inspect respectively
 * 
 */
typedef struct _InterfaceData{
  Command *lastCmd;               /*!<Pointer to the last command that have been saved*/
  Command *second_to_lastCmd;     /*!<Pointer to the second-to-last command that have been saved*/
  Command *third_to_lastCmd;      /*!<Pointer to the third-to-last command that have been saved*/
  char message[MAX_MESSAGE];      /*!<String that has the message of the character the player last talked to*/
  char description[MAX_MESSAGE];  /*!<String that has the description of the object the player last inspected in the game*/
}InterfaceData;

/**
 * @brief Structure where all the game's main information is stored (players, objects, links, spaces...)
 * 
 */
struct _Game
{
  Object *objects[MAX_OBJECTS];                 /*!<Pointer array to the objects that are present in the game*/
  int n_objects;                                /*!<Number of objects in the game*/
  Player *players[MAX_PLAYERS];                 /*!<Array of the different players in the game*/
  int n_players;                                /*!<Number of players in the game*/
  int turn;                                     /*!<Integer that describes in which turn the game is currently in (the integer corresponds to the position in the array of players of the player whose turn it is to play)*/
  Space *spaces[MAX_SPACES];                    /*!<Array of Spaces*/
  int n_spaces;                                 /*!<Number of spaces in the game*/
  Character *characters[MAX_CHARACTERS];        /*!<Array of characters in the game*/
  int n_characters;                             /*!<Number of characters in the game*/
  Link *links[MAX_LINKS];                       /*!<Array of links*/
  int n_links;                                  /*!<Number of links in the game*/
  Bool finished;                                /*!<Boolean that establishes whether the game has ended or not*/
  InterfaceData *playerGraphicInformation[MAX_PLAYERS]; /*!<Array of pointers to InterfaceData for each player, where the command history of the player is strored as well as information related to displayed messages*/
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
 * @brief Creates a pointer to an InterfaceData structure with all commands set to NO_CMD and all text set to empty
 * @author Matteo Artunedo
 * @return pointer to InterfaceData
 */
InterfaceData *game_interface_data_create();

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
  (*game)->n_links = 0;
  (*game)->finished = FALSE;

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
  if(gameReader_load_links((*game), filename) == ERROR)
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
  for (i = 0; i < game->n_links; i++)
  {
    if (game->links[i])
      link_destroy(game->links[i]);
  }
  for (i = 0; i < game->n_characters; i++)
  {
    if (game->characters[i])
      character_destroy(game->characters[i]);
  }
  for(i = 0;i < game->n_players; i++){
    if(game->players[i]){
      player_destroy(game->players[i]);
    }
    command_destroy(game->playerGraphicInformation[i]->lastCmd);
    command_destroy(game->playerGraphicInformation[i]->second_to_lastCmd);
    command_destroy(game->playerGraphicInformation[i]->third_to_lastCmd);
    free(game->playerGraphicInformation[i]);
  }
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

Id game_get_current_player_location(Game *game)
{
  return player_get_location(game->players[game->turn]);
}

Status game_set_current_player_location(Game *game, Id id)
{
  if (id == NO_ID)
  {
    return ERROR;
  }
  if (!player_set_location(game->players[game->turn], id))
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

  fprintf(stdout, "=> Links:\n");
  for (i = 0 ; i < game->n_links ; i++) 
  {
    link_print(game->links[i]);
  }

  for (i = 0; i < game->n_objects; i++)
  {
    object_print(game->objects[i]);
  }
  for(i=0;i < game->n_players; i++){
    player_print(game_get_current_player(game));
    game->turn = (game ->turn + 1)%(game->n_players);
  }
}

Player *game_get_current_player(Game *game)
{
  if (!game)
    return NULL;
  return game->players[game->turn];
}

Object *game_get_object_in_pos(Game *game, int pos)
{
  if ((game == NULL) || pos > game->n_objects)
    return NULL;
  return game->objects[pos];
}

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

Object *game_get_object(Game *game, Id id)
{
  int i;
  Object *object = NULL;
  if (!game || id == NO_ID)
    return NULL;
  for (i = 0; i < game_get_n_objects(game); i++)
  {
    object = game_get_object_in_pos(game, i);
    if (object_get_id(object) == id)
    {
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

  return game->playerGraphicInformation[game->turn]->message;
}

Status game_set_message(Game *game, char *msg)
{
  if (!game || !msg)
    return ERROR;

  strcpy(game->playerGraphicInformation[game->turn]->message, msg);
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
  for (i = 0; i < game->n_characters; i++)
  {
    if(character_get_id(game->characters[i]) == character_id){
      return character_get_location(game->characters[i]);
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

Status game_move_followers(Game *game, Id new_space_id){
  int i;
  Space *current_space=NULL, *new_space=NULL;
  Character *ch=NULL;

  if(!game || new_space_id == NO_ID){
    return ERROR;
  }

  new_space = game_get_space(game, new_space_id);
  if(!new_space) return ERROR;

  current_space = game_get_space(game, game_get_current_player_location(game));

  for(i=0;i<space_get_n_characters(current_space);i++){
    ch = game_get_character(game, space_get_character_in_pos(current_space, i));
    if(character_get_following(ch) == player_get_id(game_get_current_player(game))){
      character_set_location(ch, new_space_id);
      space_delete_character(current_space, character_get_id(ch));
      space_add_character(new_space, character_get_id(ch));
      i--;
    }
  }

  return OK;
}
/*LINK RELATED FUNCTIONS*/

Status game_add_link(Game *game, Link *link) 
{
  Direction aux_dir = link_get_direction(link);
  Id aux_id = link_get_origin_id(link);

  /* error checking */
  if (!game || !link || game_get_connection(game, aux_id, aux_dir) != NO_ID) /* third condition checks if a link in that space and direction already exists */
  {
    return ERROR;
  }

  /* add link to game's array */
  game->links[game->n_links] = link;
  game->n_links++;

  /* correct exit */
  return OK;
}

Id game_get_connection(Game *game, Id current_space, Direction link_direction)
{
  int i;

  /* error checking */
  if (!game || current_space == NO_ID || link_direction == UNKNOWN_DIR)
  {
    return NO_ID;
  }

  /* look for link from the current space pointing in the given direction */
  for (i = 0; i < game->n_links; i++)
  {
    if (link_get_origin_id(game->links[i]) == current_space) /*check this condition first for efficiency, less probable*/
    {
      if (link_get_direction(game->links[i]) == link_direction) /*check second condition for matching link*/
      {
        return link_get_destination_id(game->links[i]); /*return link destination*/
      }
    }
  }

  /*no matching link found, return NO_ID*/
  return NO_ID;
}

Bool game_connection_is_open(Game *game, Id current_space, Direction link_direction)
{
  int i;

  /* error checking */
  if (!game || current_space == NO_ID || link_direction == UNKNOWN_DIR)
    return FALSE;

  /* look for the link matching input arguments in the game->links array */
  for (i = 0; i < game->n_links; i++)
  {
    if (current_space == link_get_origin_id(game->links[i])) /*check this condition first for efficiency, less probable*/
    {
      if (link_direction == link_get_direction(game->links[i])) /*check second condition for matching link*/
      {
        return link_get_is_open(game->links[i]);
      }
    }
  }

  /* link not found, return false to prevent undefined behaviour */
  return FALSE;
}

int game_get_n_links(Game *game) 
{
  if (!game) 
    return -1;

  return game->n_links;
}

/*END OF LINK RELATED FUNCTIONS*/
Status game_set_description(Game *game, char *desc)
{

  if(!game || !desc){
    return ERROR;
  }
  strcpy(game->playerGraphicInformation[game->turn]->description, desc);
  return OK;
}

char *game_get_description(Game *game)
{
  if(!game)
  {
    return NULL;
  }
  return game->playerGraphicInformation[game->turn]->description;
}

Status game_add_player(Game *game, Player *player){
  if(!game || !player)
  {
    return ERROR;
  }

  game->players[game->n_players] = player;
  game->playerGraphicInformation[game->n_players] = game_interface_data_create();
  game->n_players++;
  
  return OK;
}

void game_next_turn(Game *game){
  game->turn= (game->turn + 1)%(game->n_players);
}

int game_get_turn(Game *game){
  if(!game){
    return -1;
  }
  return game->turn;
}

int game_get_n_players(Game *game){
  return game->n_players;
}

Status game_delete_player(Game *game){
  int i;

  if (!game) return ERROR;

  if(!(player_destroy(game->players[game->turn]))){
    return ERROR;
  }
  command_destroy(game->playerGraphicInformation[game->turn]->lastCmd);
  game->playerGraphicInformation[game->turn]->lastCmd = NULL;
  command_destroy(game->playerGraphicInformation[game->turn]->second_to_lastCmd);
  command_destroy(game->playerGraphicInformation[game->turn]->third_to_lastCmd);
  free(game->playerGraphicInformation[game->turn]);
  game->n_players--;

  for(i = game->turn; i<game->n_players; i++){
    game->players[i] = game->players[i+1];
    game->playerGraphicInformation[i] = game->playerGraphicInformation[i+1];
  }
  game->players[game->n_players] = NULL;
  game->playerGraphicInformation[i] = NULL;

  return OK;
}

InterfaceData *game_interface_data_create(){
  InterfaceData *data=NULL;

  data = (InterfaceData *)malloc(sizeof(InterfaceData));
  if(!data){
    return NULL;
  }
  data->lastCmd = command_create();
  data->second_to_lastCmd = command_create();
  data->third_to_lastCmd = command_create();
  if (!data->lastCmd || !data->second_to_lastCmd || !data->third_to_lastCmd) {
    free(data);
    return NULL;
  }
  command_set_code(data->lastCmd, NO_CMD);
  command_set_code(data->second_to_lastCmd, NO_CMD);
  command_set_code(data->third_to_lastCmd, NO_CMD);

  data->description[0] = '\0';
  data->message[0] = '\0';
  return data;
}

Status game_interface_data_set_last_command(Game *game, Command *last_cmd){
  if(!game || !last_cmd) return ERROR;
  command_destroy(game->playerGraphicInformation[game->turn]->third_to_lastCmd);
  game->playerGraphicInformation[game->turn]->third_to_lastCmd = game->playerGraphicInformation[game->turn]->second_to_lastCmd;
  game->playerGraphicInformation[game->turn]->second_to_lastCmd = game->playerGraphicInformation[game->turn]->lastCmd;
  game->playerGraphicInformation[game->turn]->lastCmd = last_cmd;

  return OK;
}

Command *game_interface_data_get_cmd_in_pos(Game *game, CommandPosition pos) {
  if (!game) return NULL;
  if(!game->playerGraphicInformation[game->turn]){
    return NULL;
  }
  switch(pos){
    case LAST:
      return game->playerGraphicInformation[game->turn]->lastCmd; 
    case SECOND_TO_LAST:
      return game->playerGraphicInformation[game->turn]->second_to_lastCmd;
    case THIRD_TO_LAST:
      return game->playerGraphicInformation[game->turn]->third_to_lastCmd;
    default:
      return NULL;
  }
}
