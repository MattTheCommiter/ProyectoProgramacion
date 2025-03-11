/**
 * @brief It defines the space module interface
 *
 * @file space.h
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#ifndef SPACE_H
#define SPACE_H

#include "types.h"
#include "set.h"
#include "character.h"

#define N_LINES_IN_GDESC 5
#define N_ROWS_IN_GDESC 9
#define N_TOTAL_LINES_IN_GDESC 9
#define N_TOTAL_ROWS_IN_GDESC 59
#define N_TOTAL_LINES_IN_SQUARE 9
#define N_TOTAL_ROWS_IN_SQUARE 17

typedef struct _Space Space;

/**
 * @brief It creates a new space, allocating memory and initializing its members
 * @author Profesores PPROG
 *
 * @param id the identification number for the new space
 * @return a new space, initialized
 */
Space *space_create(Id id);

/**
 * @brief It destroys a space, freeing the allocated memory
 * @author Profesores PPROG
 *
 * @param space a pointer to the space that must be destroyed
 * @return OK, if everything goes well or ERROR if an error occurred
 */
Status space_destroy(Space *space);

/**
 * @brief It gets the id of a space
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @return the id of space
 */
Id space_get_id(Space *space);

/**
 * @brief It sets the name of a space
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @param name a string with the name to store
 * @return OK, if everything goes well or ERROR if an error occurred
 */
Status space_set_name(Space *space, char *name);

/**
 * @brief It gets the name of a space
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @return  a string with the name of the space
 */
const char *space_get_name(Space *space);

/**
 * @brief It sets the id of the space located at the north
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @param id the id number of the space located at the north
 * @return OK, if everything goes well or ERROR if an error occurred
 */

Status space_set_north(Space *space, Id id);

/**
 * @brief It gets the id of the space located at the north
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @return the id number of the space located at the north
 */
Id space_get_north(Space *space);

/**
 * @brief It sets the id of the space located at the south
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @param id the id number of the space located at the south
 * @return OK, if everything goes well or ERROR if an error occurred
 */
Status space_set_south(Space *space, Id id);

/**
 * @brief It gets the id of the space located at the south
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @return the id number of the space located at the south
 */
Id space_get_south(Space *space);

/**
 * @brief It sets the id of the space located at the east
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @param id the id number of the space located at the east
 * @return OK, if everything goes well or ERROR if an error occurred
 */
Status space_set_east(Space *space, Id id);

/**
 * @brief It gets the id of the space located at the east
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @return the id number of the space located at the east
 */
Id space_get_east(Space *space);

/**
 * @brief It sets the id of the space located at the west
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @param id the id number of the space located at the west
 * @return OK, if everything goes well or ERROR if an error occurred
 */
Status space_set_west(Space *space, Id id);

/**
 * @brief It gets the id of the space located at the west
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @return the id number of the space located at the west
 */
Id space_get_west(Space *space);

/**
 * @brief It adds an object's id to the set of objects
 * @author Matteo Artunedo
 *
 * @param space a pointer to the space
 * @param object_iD an Id, specifying the Id of the new object.
 * @return OK, if everything goes well or ERROR if an error occurred
 */
Status space_add_objectId(Space *space, Id object_Id);

/**
 * @brief It gets whether an object belongs to a space or not
 * @author Matteo Artunedo
 *
 * @param space a pointer to the space
 * @param object_Id the id of the object we will look for
 * @return TRUE if the object is in the space and FALSE if it is not
 */
Bool space_object_belongs(Space *space, Id object_Id);

/**
 * @brief It gets the set of objects in a space
 * @author Matteo Artunedo
 *
 * @param space a pointer to the space
 * @return pointer to the set where the objects are stored
 */
Set *space_get_set_of_objects(Space *space);

/**
 * @brief It deletes an Id from the space's set of object id's
 * @author Matteo Artunedo
 *
 * @param space a pointer to the space
 * @param objectId the Id we want to delete from the set
 * @return OK if the function was compelted succesfully or ERROR if an error occurred
 */
Status space_delete_object(Space *space, Id objectId);


/**
 * @brief It prints the space information
 * @author Matteo Artunedo
 *
 * This fucntion shows the id and name of the space, the spaces that surrounds it and wheter it has an object or not.
 * @param space a pointer to the space
 * @return OK, if everything goes well or ERROR if an error occurred
 */
Status space_print(Space *space);

/**
 * @brief It gets the id of the character present in the space
 * @author Matteo Artunedo
 *
 * @param space a pointer to the space
 * @return the Id of the character in the space or NO_ID if the space pointer is NULL or the space has no character
 */
Id space_get_character(Space *space);

/**
 * @brief It gets the graphical description of the space
 * @author Matteo Artunedo
 *
 * @param space a pointer to the space
 * @return a pointer to the graphical description of the space
 */
char **space_get_gdesc(Space *space);

/**
 * @brief It sets the graphical description of the space
 * @author Matteo Artunedo
 *
 * @param space a pointer to the space
 * @param space_gdescription a double pointer to the incoming graphical description to set
 * @return OK, if everything goes well or ERROR if an error occurred
 */
Status space_set_gdesc(Space *space, char**space_gdescription);
#endif
