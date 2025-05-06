/**
 * @brief It defines the space module interface
 *
 * @file space.h
 * @author Matteo Artunedo, Alvaro Inigo, Araceli Gutierrez, Guilherme Povedano
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#ifndef SPACE_H
#define SPACE_H

#include "types.h"
#include "set.h"

#define N_TOTAL_ROWS_IN_SQUARE 58    /*!<Number of lines in one of the space squares*/
#define N_TOTAL_COLUMNS_IN_SQUARE 152/*!<Number of rows in one of the space squares*/

#define GENERATOR_SPACE 15              /*!<Space where the generator is at*/
#define GENERATOR_FLASH_SPACE 150       /*!<Space where the generator of the flashback is at*/
#define STORAGE_ROOM__FLASH_SPACE 160   /*!<Space where the storage room of the flashback is at*/
#define FIRST_STAIRS_ROOM 14            /*!<Space where the stairs is at*/
#define SECOND_STAIRS_ROOM 23            /*!<Space where the stairs is at*/
#define BATHROOM_SPACE 25                  /*!<Space for the bathroom*/
#define HALL1 21                        /*!<Space of the hall1*/
#define HIDDENROOM 31                     /*!<Space of the hidden room*/

/**
 * @brief specifies the type for the _Space structure
 */
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
 * @brief sets the id of the space
 * @author Alvaro Inigo
 * @param space a pointer to the space
 * @param id the new Id
 * @return Status OK of ERROR
 */
Status space_set_id(Space *space, Id id);

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
 * @brief It adds an object's id to the set of objects
 * @author Matteo Artunedo
 *
 * @param space a pointer to the space
 * @param object_Id an Id, specifying the Id of the new object.
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
 * @brief Returns whether the set of objects in the space is empty or not
 * @author Matteo Artunedo
 * @param space a pointer to the space
 * @return if space pointer is NULL or set is empty return TRUE, else return FALSE
 */
Bool space_has_no_objects(Space *space);

/**
 * @brief returns whether the set of objects in the space is full or not
 * @author Matteo Artunedo
 * @param space a pointer to the space
 * @return if space pointer is NULL or set is full return TRUE, else return FALSE
 */
Bool space_set_of_objects_is_full(Space *space);

/**
 * @brief returns the number of objects the space has
 * @author Matteo Artunedo
 * @param space a pointer to the space
 * @return int with the number of objects in the space
 */
int space_get_num_of_objects(Space *space);

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
 * @brief It gets the id of the character in a certain position of the space
 * @author Matteo Artunedo
 * @date 12-04-2025
 * @param space a pointer to the space
 * @param pos position the character holds in the set
 * @return the Id of the character in the space or NO_ID if the space pointer is NULL or the space has no character
 */
Id space_get_character_in_pos(Space *space, int pos);

/**
 * @brief Adds a character to the space
 * @author Matteo Artunedo
 * @date 12-04-2025
 * @param space a pointer to the space
 * @param characterId the Id of the character
 * @return Status Returns ERROR or OK.
 */
Status space_add_character(Space *space, Id characterId);

/**
 * @brief Deletes a character from the space
 * @author Matteo Artunedo
 * @date 12-04-2025
 * @param space a pointer to the space
 * @param characterId the Id of the character
 * @return Status Returns ERROR or OK.
 */
Status space_delete_character(Space *space, Id characterId);

/**
 * @brief returns the number of characters in the space
 * @author Matteo Artunedo
 * @param space pointer to the space
 * @return number of characters or -1 if the pointer to space is NULL
 */
int space_get_n_characters(Space *space);

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
Status space_set_gdesc(Space *space, char **space_gdescription);

/**
 * @brief Gets the object Id located in position 'pos' of the array of Id in the set of objects in space
 *
 * @author Matteo Artunedo
 * @param space a pointer to the space
 * @param pos int position in the array
 * @return Id the Id of that object located in the position asked, NO_ID if the position is too large or NULL as space.
 */
Id space_get_object_id_in_pos(Space *space, int pos);

/**
 * @brief sets whether a space has been discovered or not
 *
 * @author Matteo Artunedo
 * @date 20-3-25
 *
 * @param space a pointer to the space
 * @param discovered the new discovered state of the space (TRUE or FALSE)
 *
 * @return OK, if everything goes well or ERROR if an error occurred
 */
Status space_set_discovered(Space *space, Bool discovered);

/**
 * @brief returns whether a space has been discovered or not
 *
 * @author Matteo Artunedo
 * @date 20-03-25
 *
 * @param space pointer to the space
 * @return Bool: whether the space has been discovered or not
 */
Bool space_get_discovered(Space *space);
#endif
