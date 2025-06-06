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

#define BATTERIES_ID 1  /*!<The id of the batteries, used for checking missions*/
#define LANTERN_ID 2    /*!<The id of the lantern, used for checking missions*/
#define WRENCH_ID 102   /*!<The id of the wrench, used for checking missions*/
#define KNIFE_ID 12       /*!<The id of the knife, used for checking missions*/
#define BANDAIDS_ID 9   /*!<The id of the band-aids, used for checking and applying missions*/
#define MEDICINE_ID 10  /*!<The id of the medicine, used for checking and applying missions*/
#define DINOSAURLEG_ID 11           /*!<The id of the dinosaur led, used for checking missions*/
#define KEY_ID 7                    /*!<The id of the key, used for checking missions*/
#define FAMILY_PIC_ID 13              /*!<The id of the Family picture, used for checking missions*/
#define WATER_GUN_ID 15                 /*!<The id of the Water Gun, used for checking missions*/
#define BACKPACK_ID 16                 /*!<The id of the backpack, used for checking game actions*/
#define GENERATOR_NAME "Old Generator" /*!<The name of the old generator, used for checking missions*/
#define GENERATOR_FLASH_NAME "Generator" /*!<The name of the generator, used for checking missions*/
#define TOOLBOX_NAME "tool box"     /*!<The name of the tool box, used for checking missions*/
#define MEDKIT_NAME "MedKit"        /*!<The name of the Medkit, used for checking missions*/
#define BANDAIDS_NAME "Band-aids"        /*!<The name of the band-aids, used for checking missions*/
#define MEDICINE_NAME "Medicine"        /*!<The name of the medicine, used for checking missions*/
#define DINOSAUR_LEG_NAME "DinosaurLeg" /*!<The name of the dinosaur leg, used for checking missions*/
#define GIFTBOX_NAME "WrappedGift"      /*!<The name of the Wrapped box, used for checking missions*/


#define BACKPACK_SIZE 3             /*!<Size of the inventory that grows when taking the backpack*/

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