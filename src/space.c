/**
 * @brief It implements the space module
 *
 * @file space.c
 * @author Matteo Artuñedo, Alvaro Inigo, Araceli Gutierrez, Guilherme Povedano
 * @version 1.1
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#include "space.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief This struct stores all the information of a space: its id, graphical description, objects, character, name, and whether it is discovered or not
 *
 * This struct stores all the information of a space.
 */
struct _Space
{
  Id id;                    /*!< Id number of the space, it must be unique */
  char name[WORD_SIZE + 1]; /*!< Name of the space */
  Set *objects;             /*!< The set of objects present at the space */
  Set *characters;           /*!< Set of the character present in the space */
  char **gdesc;             /*!< The graphic description of the space */
  Bool discovered;          /*!< Boolean that describes if the space has been discovered by the players or not*/
};

Space *space_create(Id id)
{
  Space *newSpace = NULL;
  int i;
  /* Error control */
  if (id == NO_ID)
    return NULL;

  newSpace = (Space *)malloc(sizeof(Space));
  if (newSpace == NULL)
  {
    return NULL;
  }

  /* Initialization of an empty space*/
  newSpace->id = id;
  newSpace->name[0] = '\0';
  newSpace->objects = set_create();
  newSpace->characters = set_create();
  newSpace->discovered = FALSE;

  if (!(newSpace->gdesc = (char **)calloc(N_TOTAL_ROWS_IN_SQUARE, sizeof(char *))))
  {
    space_destroy(newSpace);
    return NULL;
  }
  if (!(newSpace->gdesc[0] = (char *)calloc((N_TOTAL_COLUMNS_IN_SQUARE ) * N_TOTAL_ROWS_IN_SQUARE, sizeof(char))))
  {
    space_destroy(newSpace);
    return NULL;
  }
  for (i = 1; i < N_TOTAL_ROWS_IN_SQUARE; i++)
  {
    newSpace->gdesc[i] = newSpace->gdesc[0] + (N_TOTAL_COLUMNS_IN_SQUARE) * i;
  }
  return newSpace;
}

Status space_destroy(Space *space)
{
  if (!space || !space->objects)
  {
    return ERROR;
  }
  if (space->gdesc)
  {
    if (space->gdesc[0])
    {
      free(space->gdesc[0]);
    }
    free(space->gdesc);
  }
  set_destroy(space->objects);
  set_destroy(space->characters);
  free(space);
  return OK;
}

Status space_set_id(Space *space, Id id){
  if(!space || id == NO_ID) return ERROR;

  space->id = id;
  return OK;

}

Id space_get_id(Space *space)
{
  if (space == NULL)
  {
    return NO_ID;
  }
  return space->id;
}

Status space_set_name(Space *space, char *name)
{
  if (!space || !name)
  {
    return ERROR;
  }

  if (!strcpy(space->name, name))
  {
    return ERROR;
  }
  return OK;
}

const char *space_get_name(Space *space)
{
  if (!space)
  {
    return NULL;
  }
  return space->name;
}

Status space_print(Space *space)
{
  int i;
  /*Id idaux = NO_ID;*/
  /* Error Control */
  if (!space)
  {
    return ERROR;
  }

  /* 1. Print the id and the name of the space */
  fprintf(stdout, "--> Space (Id: %ld; Name: %s)\n", space->id, space->name);

  
  if (set_is_empty(space->objects))
  {
    fprintf(stdout, "---> No objects in the space.\n");
  }
  else
  {
    fprintf(stdout, "---> Object id's: \n");
    if (set_print(space->objects) == -1)
    {
      return ERROR;
    }
  }
  if (set_is_empty(space->characters))
  {
    fprintf(stdout, "---> No characters in the space.\n");
  }
  else
  {
    fprintf(stdout, "---> Character id's: \n");
    if (set_print(space->characters) == -1)
    {
      return ERROR;
    }
  }
  fprintf(stdout, "\nGraphic description of the space: ");
  for (i = 0; i < N_TOTAL_ROWS_IN_SQUARE; i++)
  {
    printf("\n%s", space->gdesc[i]);
  }
  fprintf(stdout, "\nDiscovered state of space: ");
  if (space->discovered == TRUE)
  {
    fprintf(stdout, "TRUE");
  }
  else
  {
    fprintf(stdout, "FALSE");
  }

  return OK;
}

/*CHARACTER RELATED FUNCTIONS*/

Id space_get_character_in_pos(Space *space, int pos)
{
  if (!space)
    return NO_ID;
  return set_get_Id_in_pos(space->characters, pos);
}

Status space_add_character(Space *space, Id characterId)
{
  if (!space || characterId == NO_ID)
    return ERROR;
  return set_add(space->characters, characterId);
}

Status space_delete_character(Space *space, Id characterId)
{
  if (!space || characterId == NO_ID)
    return ERROR;
  return set_del(space->characters, characterId);
}

int space_get_n_characters(Space *space){
  if(!space) return -1;

  return set_get_num_elements(space->characters);
}

/*CHARACTER RELATED FUNCTIONS*/

/*GDESC RELATED FUNCTIONS*/

char **space_get_gdesc(Space *space)
{
  if (!space)
    return NULL;
  return space->gdesc;
}

Status space_set_gdesc(Space *space, char **space_gdescription)
{
  int i = 0;
  if (!space)
    return ERROR;
  for (i = 0; i < N_TOTAL_ROWS_IN_SQUARE; i++)
  {
    if (!strcpy(space->gdesc[i], space_gdescription[i]))
    {
      return ERROR;
    }
  }
  return OK;
}
/*END OF GDESC RELATED FUNCTIONS*/

/*OBJECT RELATED FUNCTIONS*/

Status space_add_objectId(Space *space, Id object_Id)
{
  if (!space || object_Id == NO_ID)
  {
    return ERROR;
  }
  return set_add(space->objects, object_Id);
}

Bool space_object_belongs(Space *space, Id object_Id)
{
  if (!space || object_Id == NO_ID)
  {
    return FALSE;
  }
  return set_belongs(space->objects, object_Id);
}

Status space_delete_object(Space *space, Id objectId)
{
  if (!space || !(space->objects) || objectId == NO_ID)
    return ERROR;

  return set_del(space->objects, objectId);
}

Bool space_has_no_objects(Space *space)
{
  if (!space)
  {
    return TRUE;
  }
  return set_is_empty(space->objects);
}

Bool space_set_of_objects_is_full(Space *space)
{
  if (!space)
  {
    return TRUE;
  }
  return set_is_full(space->objects);
}

int space_get_num_of_objects(Space *space)
{
  if (!space)
    return -1;

  return set_get_num_elements(space->objects);
}



/****** */
Id space_get_object_id_in_pos(Space *space, int pos)
{
  if (!space || pos >= space_get_num_of_objects(space))
    return NO_ID;
  return set_get_Id_in_pos(space->objects, pos);
}
/****** */

/*END OF OBJECT RELATED FUNCTIONS*/

Status space_set_discovered(Space *space, Bool discovered)
{
  if (!space || discovered < 0 || discovered > 1)
  {
    return ERROR;
  }
  space->discovered = discovered;
  return OK;
}

Bool space_get_discovered(Space *space)
{
  if (!space)
    return FALSE;

  return space->discovered;
}