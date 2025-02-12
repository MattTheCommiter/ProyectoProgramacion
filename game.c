/**
 * @brief It implements the game structure
 *
 * @file game.c
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#include "game.h"
#include "GameReader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

Status game_create(Game *game) {
  int i;

  for (i = 0; i < MAX_SPACES; i++) {
    game->spaces[i] = NULL;
  }

  game->n_spaces = 0;
  game->player = player_create(ANT);
  game->object = object_create(SEED);
  game->last_cmd = command_create();
  game->finished = FALSE;

  return OK;
}

Status game_create_from_file(Game *game, char *filename) {
  if (game_create(game) == ERROR) {
    return ERROR;
  }

  if (gameReader_load_spaces(game, filename) == ERROR) {
    return ERROR;
  }

  /* The player and the object are located in the first space */
  game_set_player_location(game, game_get_space_id_at(game, 0));
  game_set_object_location(game, game_get_space_id_at(game, 0));

  return OK;
}

Status game_destroy(Game *game) {
  int i = 0;

  for (i = 0; i < game->n_spaces; i++) {
    space_destroy(game->spaces[i]);
  }
  if(game->object) object_destroy(game->object);
  player_destroy(game->player);
  command_destroy(game->last_cmd);

  return OK;
}

Space *game_get_space(Game *game, Id id) {
  int i = 0;

  if (id == NO_ID) {
    return NULL;
  }

  for (i = 0; i < game->n_spaces; i++) {
    if (id == space_get_id(game->spaces[i])) {
      return game->spaces[i];
    }
  }

  return NULL;
}

Id game_get_player_location(Game *game) { 
  return player_get_location(game->player);
  
  }

Status game_set_player_location(Game *game, Id id) {
  if (id == NO_ID ) {
    return ERROR;
  }
  if (!player_set_location(game->player,id)) return  ERROR;
  

  return OK;
}

Id game_get_object_location(Game *game) { 
  int i = 0;
  Id id = object_get_id(game->object);
  Id idEsp = space_get_objectId(game->spaces[0]);
  while(id != idEsp && i < game->n_spaces){
    i++;
    idEsp = space_get_objectId(game->spaces[i]);
  }
  if(id == idEsp) return space_get_id(game->spaces[i]);
  return NO_ID;
}

Status game_set_object_location(Game *game, Id id) {


  if (id == NO_ID) {
    return ERROR;
  }
  if(!(space_set_objectId(game_get_space(game, id), object_get_id(game->object)))) return ERROR;
  return OK;
}

Command* game_get_last_command(Game *game) { return game->last_cmd; }

Status game_set_last_command(Game *game, Command *command) {
  if(!game || !command) return ERROR;
  game->last_cmd = command;

  return OK;
}

Bool game_get_finished(Game *game) { return game->finished; }

Status game_set_finished(Game *game, Bool finished) {
  if(!game) return ERROR;
  game->finished = finished;

  return OK;
}

void game_print(Game *game) {
  int i = 0;

  printf("\n\n-------------\n\n");

  printf("=> Spaces: \n");
  for (i = 0; i < game->n_spaces; i++) {
    space_print(game->spaces[i]);
  }

  printf("=> Object location: %d\n", (int)game_get_object_location(game));
  printf("=> Player location: %d\n", (int)game_get_player_location(game));
}

Player* game_get_player(Game *game){
  if (!game) return NULL;
  return game->player;
}

Object* game_get_object(Game *game){
  if (!game) return NULL;
  return game->object;
}
/**
   Implementation of private functions
*/



Id game_get_space_id_at(Game *game, int position) {
  if (position < 0 || position >= game->n_spaces) {
    return NO_ID;
  }

  return space_get_id(game->spaces[position]);
}

/**
 * @brief adds a new space to the whole game, given a pointer to that space and the memory direction of game.
 * 
 * @param game 
 * @param space 
 * @return Status 
 */
Status game_add_space(Game *game, Space *space) {
  if ((space == NULL) || (game->n_spaces >= MAX_SPACES)) {
    return ERROR;
  }

  game->spaces[game->n_spaces] = space;
  game->n_spaces++;

  return OK;
}

