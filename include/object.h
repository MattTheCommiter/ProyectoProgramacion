/**
 * @file object.h
 * @author Alvaro, Guilherme Povedano, Matteu Artunedo
 * @brief Defines the object characteristics
 * @version 0.1
 * @date 2025-02-10
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef OBJECT_H
#define OBJECT_H

#include "player.h"
#include "types.h"

/**
 * @brief Defines a new type for the Object structure.
 */
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

/**
 * @brief sets the description of an object
 * @date 2025-03-24
 * @author Alvaro Inigo
 * @param object a pointer to the object
 * @param desc the string of the description
 * @return Status OK of ERROR
 */
Status object_set_description(Object *object, char *desc);


/**
 * @brief gets the description of an object
 * @date 2025-03-24
 * @author Alvaro Inigo
 * @param object a pointer to the object
 * @return char * the description
 */
char *object_get_description(Object *object);

/**
 * @brief Sets the health given or taken away by an object
 * @date 15-04-25
 * @author Guilherme Povedano
 * @param object the object whose data will be modified 
 * @param health health to be added or taken by the object 
 * @return  OK if everything went well or ERROR 
*/
Status object_set_health(Object *object, int health);

/**
 * @brief Sets the id of the link the object can open 
 * @date 15-04-25
 * @author Guilherme Povedano
 * @param object object pointer that will be modified 
 * @param link id of the link that can be opened using the object 
 * @return  OK if everything went well or ERROR 
*/
Status object_set_open(Object *object, Id link);

/**
 * @brief Sets the id of the object that depends on this one to be picked up
 * @date 15-04-25
 * @author Guilherme Povedano
 * @param object object pointer that will be modified
 * @param dep the id of the object that depends on this 
 * @return  OK if everything went well or ERROR 
*/
Status object_set_dependency(Object *object, Id dep);

/**
 * @brief Sets whether an object is movable or not 
 * @date 15-04-25
 * @author Guilherme Povedano
 * @param object the object whose data is modified
 * @param movable whether the object is movable or not 
 * @return  OK if everything went well or ERROR 
*/
Status object_set_movable(Object *object, Bool movable);

/**
 * @brief Fetches the id of the object that depends on this one to be picked up
 * @date 15-04-25
 * @author Guilherme Povedano
 * @param object the object whose data is fetched
 * @return The Id of the object's dependency, NO_ID in case of failure
*/
Id object_get_dependency(Object *object);

/**
 * @brief Fetches whether an object is movable
 * @date 15-04-25
 * @author Guilherme Povedano
 * @param object the object whose data is fetched
 * @return TRUE/FALSE for whether object is movable   
*/
Bool object_get_movable(Object *object);

/**
 * @brief Fetches the id of the link that can be opened using this object 
 * @date 15-04-25
 * @author Guilherme Povedano
 * @param object the object whose data is fetched
 * @return The id of the link an object opens, NO_ID in case of failure 
*/
Id object_get_open(Object *object);

/**
 * @brief Fetches the amount of health given or taken by the object
 * @date 15-04-25
 * @author Guilherme Povedano
 * @param object the object whose data is fetched
 * @return The object's health field, or -1 in case of error
*/
int object_get_health(Object *object);

/**
 * @brief gets the gdesc of an object
 * @date 4-05-2025
 * @author Matteo Artunedo
 * @param object a pointer to the object
 * @return char * the graphical description
 */
char *object_get_gdesc(Object *object);
/**
 * @brief Sets the graphical description of an object
 * @date 2025-04-25
 * @author Matteo Artunedo
 * @param object a pointer to the object
 * @param gdesc the new gdesc of the object
 * @return Status: OK or ERROR
 */
Status object_set_gdesc(Object *object, char *gdesc);

#endif