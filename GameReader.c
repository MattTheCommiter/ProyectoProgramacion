/**
 * @file It implements the reading and loading of spaces
 * @author Alvaro Inigo
 * @version 0.1
 * @date 2025-02-08
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* Se incluyen los archivos .h pertinentes para el funcionamiento del programa*/
#include "GameReader.h"
#include "game.h"

Status gameReader_load_spaces(Game *game, char *filename)
{
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char *toks = NULL;
  Id id = NO_ID, north = NO_ID, east = NO_ID, south = NO_ID, west = NO_ID;
  Space *space = NULL;
  Status status = OK;

  if (!filename)
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
    if (strncmp("#s:", line, 3) == 0)
    {
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      north = atol(toks);
      toks = strtok(NULL, "|");
      east = atol(toks);
      toks = strtok(NULL, "|");
      south = atol(toks);
      toks = strtok(NULL, "|");
      west = atol(toks);
#ifdef DEBUG
      printf("Leido: %ld|%s|%ld|%ld|%ld|%ld\n", id, name, north, east, south, west);
#endif
      /**
       * @brief It finally creates the space with the read data.
       *
       */
      space = space_create(id); /*creates a new space with the id written in the file*/
      if (space != NULL)
      { /*Sets the information related to the space and adds it to the game*/
        space_set_name(space, name);
        space_set_north(space, north);
        space_set_east(space, east);
        space_set_south(space, south);
        space_set_west(space, west);
        game_add_space(game, space);
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
