/**
 * @brief It implements the space module
 *
 * @file space.c
 * @author Matteo Artuñedo
 * @version 1.1
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#include "space.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Space
 *
 * This struct stores all the information of a space.
 */
struct _Space
{
  Id id;                                              /*!< Id number of the space, it must be unique */
  char name[WORD_SIZE + 1];                           /*!< Name of the space */
  Id north;                                           /*!< Id of the space at the north */
  Id south;                                           /*!< Id of the space at the south */
  Id east;                                            /*!< Id of the space at the east */
  Id west;                                            /*!< Id of the space at the west */
  Set *objects;                                       /*!< The set of objects present at the space */
  Id character;                                       /*!< The Id of the character present at the space */
  char **gdesc;                                       /*!< The graphic description of the space */
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
  newSpace->north = NO_ID;
  newSpace->south = NO_ID;
  newSpace->east = NO_ID;
  newSpace->west = NO_ID;
  newSpace->objects = set_create();
  newSpace->character = NO_ID;
  if(!(newSpace->gdesc = (char **)calloc(N_LINES_IN_GDESC, sizeof(char *)))){
    return NULL;
  }
  if(!(newSpace->gdesc[0] = (char *)calloc((N_ROWS_IN_GDESC + 1)*N_LINES_IN_GDESC, sizeof(char)))){
    free(newSpace->gdesc);
    return NULL;
  }
  for(i=1;i<N_LINES_IN_GDESC;i++){
      newSpace->gdesc[i] = newSpace->gdesc[0] + (N_ROWS_IN_GDESC + 1)*i;
  }
  return newSpace;
}

Status space_destroy(Space *space)
{
  if (!space || !space->objects)
  {
    return ERROR;
  }
  if(space->gdesc){
    if(space->gdesc[0]){
      free(space->gdesc[0]);
    free(space->gdesc);
    }
  }
  set_destroy(space->objects);
  free(space);
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

/*NORTH AND SOUTH RELATED FUNCTIONS*/
Status space_set_north(Space *space, Id id)
{
  if (!space || id == NO_ID)
  {
    return ERROR;
  }
  space->north = id;
  return OK;
}

Id space_get_north(Space *space)
{
  if (!space)
  {
    return NO_ID;
  }
  return space->north;
}

Status space_set_south(Space *space, Id id)
{
  if (!space || id == NO_ID)
  {
    return ERROR;
  }
  space->south = id;
  return OK;
}

Id space_get_south(Space *space)
{
  if (!space)
  {
    return NO_ID;
  }
  return space->south;
}

Status space_set_east(Space *space, Id id)
{
  if (!space || id == NO_ID)
  {
    return ERROR;
  }
  space->east = id;
  return OK;
}

Id space_get_east(Space *space)
{
  if (!space)
  {
    return NO_ID;
  }
  return space->east;
}

Status space_set_west(Space *space, Id id)
{
  if (!space || id == NO_ID)
  {
    return ERROR;
  }
  space->west = id;
  return OK;
}

Id space_get_west(Space *space)
{
  if (!space)
  {
    return NO_ID;
  }
  return space->west;
}
/*END OF NORTH AND SOUTH RELATED FUNCTIONS*/

Status space_print(Space *space)
{
  int i;
  Id idaux = NO_ID;
  /* Error Control */
  if (!space)
  {
    return ERROR;
  }

  /* 1. Print the id and the name of the space */
  fprintf(stdout, "--> Space (Id: %ld; Name: %s)\n", space->id, space->name);

  /* 2. For each direction, print its link */
  idaux = space_get_north(space);
  if (idaux != NO_ID)
  {
    fprintf(stdout, "---> North link: %ld.\n", idaux);
  }
  else
  {
    fprintf(stdout, "---> No north link.\n");
  }
  idaux = space_get_south(space);
  if (idaux != NO_ID)
  {
    fprintf(stdout, "---> South link: %ld.\n", idaux);
  }
  else
  {
    fprintf(stdout, "---> No south link.\n");
  }
  idaux = space_get_east(space);
  if (idaux != NO_ID)
  {
    fprintf(stdout, "---> East link: %ld.\n", idaux);
  }
  else
  {
    fprintf(stdout, "---> No east link.\n");
  }
  idaux = space_get_west(space);
  if (idaux != NO_ID)
  {
    fprintf(stdout, "---> West link: %ld.\n", idaux);
  }
  else
  {
    fprintf(stdout, "---> No west link.\n");
  }

  /* 3. Print if there is an object in the space or not */
  if (set_is_empty(space->objects))
  {
    fprintf(stdout, "---> No objects in the space.\n");
    
  }
  else
  {
    fprintf(stdout, "---> Object id's: \n");
    if(set_print(space->objects)==-1){
      return ERROR;
    }

  }
  fprintf(stdout, "\nGraphic description of the space: ");
  for(i=0;i<N_LINES_IN_GDESC;i++){
    printf("\n%s", space->gdesc[i]);
  }

  return OK;
}

/*CHARACTER RELATED FUNCTIONS*/
Id space_get_character(Space *space){
  if(!space) return NO_ID;
  return space->character;
}

Status space_set_character(Space *space, Id characterId){
  if(!space) return ERROR;
  if(space->character == NO_ID){
    space->character = characterId;}
  else{
    return ERROR;
  }
  
  return OK;
}
/*CHARACTER RELATED FUNCTIONS*/

/*GDESC RELATED FUNCTIONS*/
char **space_get_gdesc(Space *space){
  if(!space) return NULL;
  return space->gdesc;
}

Status space_set_gdesc(Space *space, char**space_gdescription){
  int i=0;
  if(!space) return ERROR;
  for(i=0;i<N_LINES_IN_GDESC;i++){
    if(!strcpy(space->gdesc[i], space_gdescription[i])){
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
  set_add(space->objects, object_Id);
  return OK;
}

Bool space_object_belongs(Space *space, Id object_Id)
{
  if (!space || object_Id == NO_ID)
  {
    return FALSE;
  }
  return set_belongs(space->objects, object_Id);
}

Status space_delete_object(Space *space, Id objectId){
  if(!space || !space->objects) return ERROR;

  if(!set_del(space->objects, objectId)){
    return ERROR;
  }else{
    return OK;
  }
}

Bool space_has_no_objects(Space *space){
  if(!space){
    return TRUE;
  }
  return set_is_empty(space->objects);
}

Bool space_set_of_objects_is_full(Space *space){
  if(!space){
    return TRUE;
  }
  return set_is_full(space->objects);
}

int space_get_num_of_objects(Space *space){
  if(!space) return 0;

  return set_get_num_elements(space->objects);
}
/*END OF OBJECT RELATED FUNCTIONS*/