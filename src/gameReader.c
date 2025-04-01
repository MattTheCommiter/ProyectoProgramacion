/**
 * @file It implements the reading and loading of spaces
 * @author Alvaro Inigo
 * @version 0.2
 * @date 2025-03-014
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* Se incluyen los archivos .h pertinentes para el funcionamiento del programa*/
#include "gameReader.h"
#include "game.h"
#include "player.h"
#include "character.h"
#include "link.h"

Status gameReader_load_spaces(Game *game, char *filename)
{
  /*#s:11|Entry| _ | ___ | mo'_| @ _ | __/ __|*/
  /*#s:11| Entry|-1|-1|121|-1|   -     |\ \_ _ _ |\   mo'\_|\ @  _   | \__/ \__|*/
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char **read_gdesc;
  char *toks = NULL;
  int i;
  Id id;
  Space *space = NULL;
  Status status = OK;

  if (!filename || !game)
  {
    return ERROR;
  }

  if (!(read_gdesc = (char **)calloc(N_LINES_IN_GDESC, sizeof(char *))))
  {
    return ERROR;
  }
  if (!(read_gdesc[0] = (char *)calloc(N_LINES_IN_GDESC * (N_ROWS_IN_GDESC + 1), sizeof(char))))
  {
    free(read_gdesc);
    return ERROR;
  }
  for (i = 1; i < 5; i++)
  {
    read_gdesc[i] = read_gdesc[0] + (N_ROWS_IN_GDESC + 1) * i;
  }

  

  file = fopen(filename, "r");
  if (file == NULL)
  {
    return ERROR;
  }
  /**
   * @brief reads the file and load each data individually.
   *
   */

  while (fgets(line, WORD_SIZE, file)) /*Reads all the lines in the text file and saves the provided information*/
  {
    if (strncmp("#s:", line, 3) == 0)
    /*#s:11|Entry| _ | ___ | mo'_| @ _ | __/ __|*/
  /*#s:11| Entry|-1|-1|121|-1|   -     |\ \_ _ _ |\   mo'\_|\ @  _   | \__/ \__|*/
    {
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);

      /*Si hay una descripción gráfica, la leemos y la copiamos a nuetra matriz read_gdesc*/
      if ((toks = strtok(NULL, "|\n\r")) != NULL)
      {
        strcpy(read_gdesc[0], toks);
        toks = strtok(NULL, "|");
        if (toks)
        {
          strcpy(read_gdesc[1], toks);
        }
        else
        {
          game_set_finished(game, TRUE);
          fprintf(stdout, "\nInvalid graphic description\n");
        }
        toks = strtok(NULL, "|");
        if (toks)
        {
          strcpy(read_gdesc[2], toks);
        }
        else
        {
          game_set_finished(game, TRUE);
          fprintf(stdout, "\nInvalid graphic description\n");
        }
        toks = strtok(NULL, "|");
        if (toks)
        {
          strcpy(read_gdesc[3], toks);
        }
        else
        {
          game_set_finished(game, TRUE);
          fprintf(stdout, "\nInvalid graphic description\n");
        }
        toks = strtok(NULL, "|");
        if (toks)
        {
          strcpy(read_gdesc[4], toks);
        }
        else
        {
          game_set_finished(game, TRUE);
          fprintf(stdout, "\nInvalid graphic description\n");
        }
      }
      else
      {
        /*Si no hay una descripción gráfica, copiamos espacios en blanco a la descripción del espacio*/
        strcpy(read_gdesc[0], "         ");
        strcpy(read_gdesc[1], "         ");
        strcpy(read_gdesc[2], "         ");
        strcpy(read_gdesc[3], "         ");
        strcpy(read_gdesc[4], "         ");
      }

#ifdef DEBUG
      printf("Leido: %ld|%s|%ld|%ld|%ld|%ld\n", id, name, north, east, south, west);
#endif
      /*
       * It creates the space with the data that has been read
       */
      space = space_create(id); /*calls to space_create providing the id written in the file*/
      if (space != NULL)
      { /*Sets the information related to the space and adds it to the game*/
        space_set_name(space, name);
        game_add_space(game, space);
        space_set_gdesc(space, read_gdesc);
      }
      else
      {
        fclose(file);
        free(read_gdesc[0]);
        free(read_gdesc);
        return ERROR;
      }
    }
  }
  free(read_gdesc[0]);
  free(read_gdesc);
  if (ferror(file))
  {
    status = ERROR;
  }

  fclose(file);

  return status;
}

Status gameReader_load_objects(Game *game, char *filename)
{
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char description[WORD_SIZE] = "";
  char *toks = NULL;
  Id id = NO_ID, spaceId = NO_ID;
  Object *object = NULL;
  Status status = OK;

  if (!filename || !game)
  {
    return ERROR;
  }

  file = fopen(filename, "r");
  if (file == NULL)
  {
    return ERROR;
  }
  /**
   * @brief reads the file and load each data individually.
   *
   */
  while (fgets(line, WORD_SIZE, file)) /*Reads all the lines in the text file and saves the provided information*/
  {
    if (strncmp("#o:", line, 3) == 0)
    {
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      spaceId = atol(toks);
      toks = strtok(NULL, "|\n\r");
      strcpy(description, toks);

#ifdef DEBUG
      printf("Leido: %ld|%s|%ld\n", id, name, spaceId);
#endif
      /*
       * It creates the space with the data that has been read
       */
      object = object_create(id); /*calls to object_create providing the id written in the file*/
      if (object != NULL)
      { /*Sets the information related to the object and adds it to the game*/
        object_set_name(object, name);
        object_set_description(object, description);
        space_add_objectId(game_get_space(game, spaceId), id);
        game_add_object(game, object);
      }
    }
  }

  if (ferror(file))
  {
    status = ERROR;
  }

  fclose(file);

  return status;
}


Status gameReader_load_players(Game *game, char *filename)
{
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char gdesc[GDESCTAM] = "";
  char *toks = NULL;
  Id id = NO_ID, spaceId = NO_ID;
  Player *player = NULL;
  Status status = OK;
  int hp = 0;
  int inventory_size = 0;

  if (!filename || !game)
  {
    return ERROR;
  }

  file = fopen(filename, "r");
  if (file == NULL)
  {
    return ERROR;
  }
  /**
   * @brief reads the file and load each data individually.
   *
   */
  while (fgets(line, WORD_SIZE, file)) /*Reads all the lines in the text file and saves the provided information*/
  {
    if (strncmp("#p:", line, 3) == 0)
    {
      toks = strtok(line + 3, "|\r\n");
      id = atol(toks);
      toks = strtok(NULL, "|\r\n"); 
      strcpy(name, toks);
      toks = strtok(NULL, "|\r\n");
      strcpy(gdesc,toks);
      toks = strtok(NULL, "|\r\n");
      spaceId = atol(toks);
      toks = strtok(NULL, "|\r\n");
      hp = atoi(toks);
      toks = strtok(NULL, "|\n\r");
      inventory_size = atoi(toks);

/*
#p: id|name|GDESC|idSpace|HP|INVENTORY|
*/
#ifdef DEBUG
      printf("Leido: %ld|%s|%s|%ld|%d|%d|\n", id, name, gdesc, spaceId, hp, inventory_size);
#endif
 
      /*
       * It creates the player with the data that has been read
       */
      player = player_create(id, inventory_size); /*calls to player_create providing the id written in the file*/
      if (player != NULL)
      { /*Sets the information related to the object and adds it to the game*/
        player_set_name(player, name);
        player_set_gdesc(player, gdesc);
        player_set_location(player, spaceId);
        space_set_discovered(game_get_space(game, spaceId), TRUE);
        player_set_health(player, hp);
        game_add_player(game, player);
      }
    }
  }

  if (ferror(file))
  {
    status = ERROR;
  }

  fclose(file);

  return status;
}


Status gameReader_load_characters(Game *game, char *filename)
{
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char gdesc[GDESCTAM] = "";
  char message[WORD_SIZE] = "";
  char *toks = NULL;
  Id id = NO_ID, spaceId = NO_ID;
  Character *character = NULL;
  Status status = OK;
  int hp = 0;
  Bool friendliness = FALSE;

  if (!filename || !game)
  {
    return ERROR;
  }

  file = fopen(filename, "r");
  if (file == NULL)
  {
    return ERROR;
  }
  /**
   * @brief reads the file and load each data individually.
   *
   */
  while (fgets(line, WORD_SIZE, file)) /*Reads all the lines in the text file and saves the provided information*/
  {
    if (strncmp("#c:", line, 3) == 0)
    {
      toks = strtok(line + 3, "|\r\n");
      id = atol(toks);
      toks = strtok(NULL, "|\r\n"); 
      strcpy(name, toks);
      toks = strtok(NULL, "|\r\n");
      strcpy(gdesc,toks);
      toks = strtok(NULL, "|\r\n");
      spaceId = atol(toks);
      toks = strtok(NULL, "|\r\n");
      hp = atoi(toks);
      toks = strtok(NULL, "|\r\n");
      friendliness = atoi(toks);
      toks = strtok(NULL, "|\r");
      strcpy(message, toks);

/*
#c:3|ant friend|    ^0m|122|5|0|Hey ant friend!
*/

#ifdef DEBUG
      printf("Leido: %ld|%s|%s|%ld|%d|%d|%s|\n", id, name, gdesc, spaceId, hp, friendliness, message);
#endif

      /*
       * It creates the character with the data that has been read
       */
      character = character_create(id); /*calls to character_create providing the id written in the file*/
      if (character != NULL)
      { /*Sets the information related to the character and adds it to the game*/
        character_set_name(character, name);
        character_set_gdesc(character, gdesc);
        space_set_character(game_get_space(game, spaceId), id);
        character_set_health(character, hp);
        character_set_message(character, message);
        character_set_friendly(character, friendliness);
        game_add_character(game, character);
      }
    }
  }

  if (ferror(file))
  {
    status = ERROR;
  }

  fclose(file);

  return status;
}


Status gameReader_load_links(Game *game, char *filename)
{
  FILE *file = NULL;
  Status status = OK;
  char line[WORD_SIZE] = "";
  char *toks = NULL;
  Link *link= NULL;
  Id id = NO_ID;
  char name[WORD_SIZE] = "";
  Id idOrigin = NO_ID, idDest = NO_ID;
  Direction direccion = UNKNOWN_DIR;
  Bool open = FALSE;

  if (!filename || !game)
  {
    return ERROR;
  }

  file = fopen(filename, "r");
  if (file == NULL)
  {
    return ERROR;
  }
  /**
   * @brief reads the file and load each data individually.
   *
   */
  while (fgets(line, WORD_SIZE, file)) /*Reads all the lines in the text file and saves the provided information*/
  {
    /*#l:31|Entry|11|121|1|1| Id,Nombre,Idsalida,Iddest,direccion,open*/
    if (strncmp("#l:", line, 3) == 0)
    {
      toks = strtok(line + 3, "|\r\n");
      id = atol(toks);
      toks = strtok(NULL, "|\r\n"); 
      strcpy(name, toks);
      toks = strtok(NULL, "|\r\n");
      idOrigin = atol(toks);
      toks = strtok(NULL, "|\r\n");
      idDest = atol(toks);
      toks = strtok(NULL, "|\r\n");
      direccion = atol(toks);
      toks = strtok(NULL, "|\r\n");
      open = atol(toks);


#ifdef DEBUG
      printf("Leido: %ld|%s|%ld|%ld|%d|%d|\n", id, name, idOrigin, idDest, direccion, open);
#endif

      /*
       * It creates the link with the data that has been read
       */
      link = link_create(id); /*calls to link_create providing the id written in the file*/
      if (link != NULL)
      { /*Sets the information related to the link and adds it to the game*/
        link_set_name(link, name);
        link_set_origin_id(link, idOrigin);
        link_set_destination_id(link, idDest);
        link_set_direction(link, direccion);
        link_set_is_open(link, open);
        game_add_link(game, link);
      }
    }
  }

  if (ferror(file))
  {
    status = ERROR;
  }

  fclose(file);

  return status;
}