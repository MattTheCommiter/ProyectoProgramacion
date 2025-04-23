/**
 * @brief It implements the player module
 *
 * @file player.c
 * @author Matteo Artuñedo, Araceli Gutierrez, Alvaro Inigo, Guilherme Povedano 
 * @version 0
 * @date 22-03-2025
 * @copyright GNU Public License
 */

#include "player.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Player
 * @author PPROG - Team 2101_D - Matteo Artunedo, AGL (modifications to include backpack)
 * @date 22-03-2025
 * This struct stores all the information of a player.
 */
struct _Player
{
  Id id;                    /*!< Id number of the player, it must be unique */
  char name[WORD_SIZE + 1]; /*!< Name of the player */
  Id location;              /*!<Id of the   where the player is located*/
  int health;               /*!< Hp points of the player*/
  char Gdesc[GDESCTAM];     /*!< The graphic description of the player*/
  Inventory *backpack;      /*!< Backpack to carry multiple objects */
};

/**This function creates a new player with the given ID and initializes its fields. */
Player *player_create(Id id, int inventory_size){
  Player *newPlayer = NULL;

  /* Error control */
  if (id == NO_ID || inventory_size < 0)
    return NULL;

  newPlayer = (Player *)malloc(sizeof(Player));
  if (newPlayer == NULL){
    return NULL;
  }

  /* Initialization of an empty player*/
  newPlayer->id = id;
  newPlayer->name[0] = '\0';
  newPlayer->location = NO_ID;
  newPlayer->backpack = inventory_create(inventory_size); /* Initialize backpack with BACKPACK_CAPACITY objects */
  newPlayer->health = 5;
  newPlayer->Gdesc[0] = '\0';

  return newPlayer;
}

/** This function destroys a player and frees the allocated memory */
Status player_destroy(Player *player){
  if (!player){
    return ERROR;
  }

  inventory_destroy(player->backpack); /* Destroy the backpack */
  free(player);
  return OK;
}

/**This function sets the ID of the player */
Status player_set_id(Player *player, Id playerId){
  if (!player || playerId == NO_ID){
    return ERROR;
  }
  player->id = playerId;
  return OK;
}

/** Gets the ID of the player */
Id player_get_id(Player *player){
  if (!player){
    return NO_ID;
  }
  return player->id;
}

/**Sets the name of the player */
Status player_set_name(Player *player, char *name){
  if (!player || !name){
    return ERROR;
  }

  if (!strcpy(player->name, name)){
    return ERROR;
  }
  return OK;
}

/** This function returns the name of the player */
const char *player_get_name(Player *player){
  if (!player){
    return NULL;
  }
  return player->name;
}

/**This function checks if the player's backpack is full */
Bool player_backpack_is_full(Player *player) {
  if (!player || !player->backpack) {
    return FALSE;
  }
  return inventory_is_full(player->backpack);
}

/**This function checks if the player's backpack is empty */
Bool player_backpack_is_empty(Player *player) {
  if (!player || !player->backpack) {
    return TRUE;
  }
  return inventory_is_empty(player->backpack);
}


/**This function adds an object to the player's backpack if the player and the backpack are valid.
 * It uses the inventory_add_object_id function to add the object to the backpack. */
Status player_add_object_to_backpack(Player *player, Id obj_id){
  if (player ==NULL || player->backpack == NULL){
    return ERROR;
  }

   /* Check if the backpack is full */
   if (player_backpack_is_full(player)) {
    return ERROR;
  }
  
  if(inventory_add_object_id(player->backpack, obj_id) == ERROR){
    return ERROR;
  }

  return OK;
}

/**This function removes an object from the player's backpack by using the inventory_del_object_id function. */
Status player_remove_object_from_backpack(Player *player, Id obj_id){
  if (player == NULL || player->backpack == NULL){
    return ERROR;
  }

  if(inventory_del_object_id(player->backpack, obj_id) == ERROR){
    return ERROR;
  }

  return OK;
}

/** This function returns the number of objects in the player's backpack */
int player_get_num_objects_in_backpack(Player *player){
  int n= -1;

  if (player == NULL || player->backpack == NULL){
    return -1;
  }

  n= set_get_num_elements(inventory_get_objs(player ->backpack));

  return n;
}

/**This function returns the object ID at the specified position in the player's backpack*/
Id player_get_backpack_object_id_at(Player *player, int position){
  if (player == NULL || player->backpack == NULL || position < 0 || position >=  player_get_num_objects_in_backpack(player)){
    return NO_ID;
  }

  return inventory_get_object_id_at(player->backpack, position);
}

/** This function checks if the player's backpack contains the specified object ID */
Bool player_backpack_contains(Player *player, Id obj_id){
  if (!player || !player->backpack){
    return FALSE;
  }
  return inventory_contains(player->backpack, obj_id);
}

/**This function sets the location of the player */
Status player_set_location(Player *player, Id spaceId){
  if (!player){
    return ERROR;
  }
  player->location = spaceId;
  return OK;
}

/**This function returns the location of the player */
Id player_get_location(Player *player){
  if (!player){
    return NO_ID;
  }
  return player->location;
}

/**This function prints the details of the player,
 * including the ID, name, location, health, and backpack contents */
Status player_print(Player *player){

  /* Error Control */
  if (!player){
    return ERROR;
  }

  /* Print the id and the name of the player */
  fprintf(stdout, "--> Player (Id: %ld; Name: %s)\n", player->id, player->name);

  /* Print the player's location */
  fprintf(stdout, "--> Id of the player's location: %ld", player->location);

  /* Print the player's health */
  fprintf(stdout, "--> Player's health: %d\n", player->health);

  /* Print the backpack details */
  if (player->backpack != NULL){
    inventory_print(player->backpack);
  } else {
    fprintf(stdout, "--> The player does not have a backpack\n");
  }

  return OK;
}

Status player_set_health(Player *p, int hp){
  if (!p)
    return ERROR;
  p->health = hp;
  return OK;
}

int player_get_health(Player *p){
  if (!p)
    return NO_HP;
  return p->health;
}

Status player_set_gdesc(Player *player, char *gdesc)
{
  if (!player || !gdesc)
  {
    return ERROR;
  }

  strcpy(player->Gdesc, gdesc);

  return OK;
}

char *player_get_gdesc(Player *player)
{
  if(!player)
  {
    return NULL;
  }
  return player->Gdesc;
}

Bool player_object_is_in_backpack(Player *player, Id objectId){
  if(!player)
  {
    return FALSE;
  }
  return inventory_contains(player->backpack, objectId);
}

Inventory *player_get_inventory(Player *player){
  if(!player) return NULL;
  return player->backpack;
}

Status player_set_max_objs(Player *player, int max){
  if(!player || max < 0) return ERROR;
  return inventory_set_max_objs(player->backpack, max);
}