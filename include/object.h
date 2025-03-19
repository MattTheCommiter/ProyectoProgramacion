/**
 * @file object.h
 * @author Alvaro
 * @brief Defines the object characteristics
 * @version 0.1
 * @date 2025-02-10
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef OBJECT_H
#define OBJECT_H
#include "types.h"
typedef struct _Object Object;

/**
 * @brief Creates a new object given its Id
 * @date 2025-02-10
 * @author Alvaro Inigo
 * @param id the Id of the new object
 * @return Object * if everything was ok,
 *  or NULL it there was any problem with memory allocation
 */
Object *object_create(Id id);
/**
 * @brief Destroys a given object and frees the memory.
 * @date 2025-02-10
 * @author Alvaro Inigo
 * @param object a pointer to Object
 * @return Status
 */
Status object_destroy(Object *object);
/**
 * @brief Gets the Id of a given object.
 * @date 2025-02-10
 * @author Alvaro Inigo
 * @param object a pointer to Object
 * @return Id or NO_ID if there was a problem reading the pointer to object.
 */
Id object_get_id(Object *object);
/**
 * @brief gets the name of a given object and returns it as a string
 * @date 2025-02-10
 * @author Alvaro Inigo
 * @param object a pointer to Object
 * @return char*
 */
char *object_get_name(Object *object);
/**
 * @brief Sets the Id for a given object
 * @date 2025-02-10
 * @author Alvaro Inigo
 * @param object a pointer to Object
 * @param id the new Id for the object
 * @return Status OK or ERROR
 */
Status object_set_id(Object *object, Id id);
/**
 * @brief Sets the name for a given object
 * @date 2025-02-10
 * @author Alvaro Inigo
 * @param object a pointer to Object
 * @param name The new name for the object
 * @return Status OK or ERROR
 */
Status object_set_name(Object *object, char *name);
/**
 * @brief prints through the screen the Id and name of an object.
 * @date 2025-02-10
 * @author Alvaro Inigo
 * @param object a pointer to Object
 * @return Status , will return ERROR if not able to access the direction.
 */
Status object_print(Object *object);

#endif