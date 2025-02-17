/**
 * @brief It implements the player module
 *
 * @file player.c
 * @author Matteo Artuñedo
 * @version 0
 * @date 10-02-2025
 * @copyright GNU Public License
 */

#include "player.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Player
 * @author Matteo Artunedo
 * @date 12-02-2025
 * This struct stores all the information of a player.
 */
struct _Player
{
  Id id;                    /*!< Id number of the player, it must be unique */
  char name[WORD_SIZE + 1]; /*!< Name of the player */
  Id location;              /*!<Id of the space where the player is located*/
  Id object;                /*!< Whether the player has an object or not */
};

Player *player_create(Id id)
{
  Player *newPlayer = NULL;

  /* Error control */
  if (id == NO_ID)
    return NULL;

  newPlayer = (Player *)malloc(sizeof(Player));
  if (newPlayer == NULL)
  {
    return NULL;
  }

  /* Initialization of an empty player*/
  newPlayer->id = id;
  newPlayer->name[0] = '\0';
  newPlayer->location = NO_ID;
  newPlayer->object = NO_ID;

  return newPlayer;
}

Status player_destroy(Player *player)
{
  if (!player)
  {
    return ERROR;
  }

  free(player);
  return OK;
}

Status player_set_id(Player *player, Id playerId)
{
  if (!player || !playerId)
  {
    return ERROR;
  }
  player->id = playerId;
  return OK;
}

Id player_get_id(Player *player)
{
  if (!player)
  {
    return NO_ID;
  }
  return player->id;
}

Status player_set_name(Player *player, char *name)
{
  if (!player || !name)
  {
    return ERROR;
  }

  if (!strcpy(player->name, name))
  {
    return ERROR;
  }
  return OK;
}

const char *player_get_name(Player *player)
{
  if (!player)
  {
    return NULL;
  }
  return player->name;
}

Status player_set_object(Player *player, Id objectId)
{
  if (!player)
  {
    return ERROR;
  }
  player->object = objectId;
  return OK;
}

Id player_get_object(Player *player)
{
  if (!player)
  {
    return NO_ID;
  }
  return player->object;
}

Status player_set_location(Player *player, Id spaceId)
{
  if (!player)
  {
    return ERROR;
  }
  player->location = spaceId;
  return OK;
}

Id player_get_location(Player *player)
{
  if (!player)
  {
    return NO_ID;
  }
  return player->location;
}

Status player_print(Player *player)
{

  /* Error Control */
  if (!player)
  {
    return ERROR;
  }

  /* 1. Print the id and the name of the player */
  fprintf(stdout, "--> Player (Id: %ld; Name: %s)\n", player->id, player->name);
  if (player->object == NO_ID)
  {
    fprintf(stdout, "--> The player does not have an object");
  }
  else
  {
    fprintf(stdout, "--> Id of the player's object: %ld", player->object);
  }
  fprintf(stdout, "--> Id of the player's location: %ld", player->location);

  return OK;
}
