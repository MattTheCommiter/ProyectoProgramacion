/** 
 * @brief It defines the link module interface 
 * 
 * @file link.h
 * @author Guilherme Povedano 
 * @version 0.0.1
 * @date 19-03-2025
 * @copyright GNU Public License 
*/
#ifndef LINK_H
#define LINK_H

#include "types.h"

#define HIDDENROOMTOTREASURE 3132 
#define LIVINGROOMTOHALL1  1421
#define HALL2TOHIDDENROOM 2331

/** @brief public alias for the opaque _Link structure */
typedef struct _Link Link;

/**
 * @brief Allocates memory and initializes a new link structure 
 * @author Guilherme Povedano 
 * @date 19-03-2025
 * @param link_id the unique id for the newly created link
 * @return A pointer to the new link or NULL in case of error  
*/
Link *link_create(Id link_id);

/**
 * @brief frees any allocated memory for a given link 
 * @author Guilherme Povedano 
 * @date 19-03-2025
 * @param l a pointer to the link structure to be freed
*/
void link_destroy(Link *l);

/**
 * @brief sets the id of the link
 * @author Alvaro Inigo
 * @param link the link wohse Id wants to be set
 * @param id the new id
 * @return Status OK or ERROR
 */
Status link_set_id(Link *link, Id id);
/**
 * @brief Sets the name filed in a given link structure
 * @author Guilherme Povedano 
 * @date 20-03-2025
 * @param l the link structure to be modified 
 * @param name the name that will be assigned to l
 * @return OK if everything went well or ERROR otherwise
*/
Status link_set_name(Link *l, char *name);

/**
 * @brief Sets the origin_id field in a given link structure
 * @author Guilherme Povedano 
 * @date 19-03-2025
 * @param l the link structure to me modified
 * @param origin_id the origin_id that must be assigned to link's field
 * @return OK if everything went well or ERROR in case of error
*/
Status link_set_origin_id(Link *l, Id origin_id);

/**
 * @brief Sets the destination_id field in a given link structure
 * @author Guilherme Povedano 
 * @date 19-03-2025
 * @param l the link structure to me modified
 * @param destination_id the destination_id that must be assigned to link's field
 * @return OK if everything went well or ERROR in case of error
*/
Status link_set_destination_id(Link *l, Id destination_id);

/**
 * @brief Sets the direction field in a given link structure
 * @author Guilherme Povedano 
 * @date 19-03-2025
 * @param l the link structure to me modified
 * @param dir Direction enum that must be assigned to link's field 
 * @return OK if everything went well or ERROR in case of error
*/
Status link_set_direction(Link *l, Direction dir);

/**
 * @brief Sets whether a link is open/unlocked or not
 * @author Guilherme Povedano 
 * @date 19-03-2025
 * @param l the link structure to me modified
 * @param is_open the boolean variable that must be assigned to link's field 
 * @return OK if everything went well or ERROR in case of error
*/
Status link_set_is_open(Link *l, Bool is_open);

/**
 * @brief fetches the id of a given link
 * @author Guilherme Povedano 
 * @date 19-03-2025
 * @param l a pointer to the link structure whose data will be fecthed 
 * @return The id of the given link or NO_ID in case of error 
*/
Id link_get_id(Link *l);

/**
 * @brief fetches the name of a given link 
 * @author Guilherme Povedano
 * @date 20-03-2025
 * @param l the link whose data will be retrieved 
 * @return the name of the given link 
*/
const char *link_get_name(Link *l);

/**
 * @brief fetches the origin id of a given link
 * @author Guilherme Povedano 
 * @date 19-03-2025
 * @param l a pointer to the link structure whose data will be fecthed 
 * @return The id of the given link's origin space or NO_ID in case of error 
*/
Id link_get_origin_id(Link *l);

/**
 * @brief fetches the destination id of a given link
 * @author Guilherme Povedano 
 * @date 19-03-2025
 * @param l a pointer to the link structure whose data will be fecthed 
 * @return The id of the given link's destination space or NO_ID in case of error 
*/
Id link_get_destination_id(Link *l);

/**
 * @brief fetches the direction of a given link
 * @author Guilherme Povedano 
 * @date 19-03-2025
 * @param l a pointer to the link structure whose data will be fecthed 
 * @return the direction field in link or UNKNOWN_DIR in case of error 
*/
Direction link_get_direction(Link *l);

/**
 * @brief fetches whether a given link is open/unlocked or not 
 * @author Guilherme Povedano 
 * @date 19-03-2025
 * @param l a pointer to the link structure whose data will be fecthed 
 * @return the is_open field in link or FALSE in case of error 
*/
Bool link_get_is_open(Link *l);

/**
 * @brief prints the link structure and its data to stdout, for debugging purposes
 * @author Guilherme Povedano 
 * @date 19-03-2025
 * @param l a pointer to the link structure to be displayed
*/
void link_print(Link *l);

#endif
