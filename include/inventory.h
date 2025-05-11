/**
 * @brief It defines the space module interface
 *
 * @file inventory.h
 * @author PPROG - Team 2101_D - Araceli Gutiérrez
 * @version 
 * @date 21-03-2025
 * @copyright GNU Public License
 */

#ifndef INVENTORY_H
#define INVENTORY_H
 
#include "types.h"
#include "set.h"
 
/**
 * @brief Definition of the inventory type
 * 
 */
 typedef struct _Inventory Inventory;

/**
 * @brief This function creates a new inventory with a given maximum number of objects
 * @author PPROG Team 2101_D - AGL
 * @param max_objs The maximum number of objects that the inventory can hold. It must be a non-negative integer.
 * @return A pointer to the newly created Inventory structure, or NULL if memory allocation fails or if max_objs is negative.
 */
Inventory* inventory_create(int max_objs);

/**
* @brief This function destroys an inventory and frees the memory allocated for the Inventory structure and its associated Set of objects
* @author PPROG Team 2101_D - AGL
* @param inventory A pointer to the Inventory structure to be destroyed.
* @return OK if the inventory was successfully destroyed, ERROR if the inventory pointer is NULL.
*/
Status inventory_destroy(Inventory* inventory);

/**
* @brief This function returns a pointer to the set of objects contained in the inventory. If the inventory pointer is NULL, it returns NULL.
* @author PPROG Team 2101_D - AGL
* @param inventory A pointer to the Inventory structure.
* @return A pointer to the Set of objects in the inventory, or NULL if the inventory pointer is NULL.
*/
Set* inventory_get_objs(Inventory* inventory);


/**
* @brief Gets the maximum number of objects that the inventory can hold.
* @author PPROG Team 2101_D - AGL
* @param inventory A pointer to the Inventory structure.
* @return The maximum number of objects the inventory can hold, or -1 if the inventory pointer is NULL.
*/
int inventory_get_max_objs(Inventory* inventory);

/**
 * @brief Checks if the inventory contains a specific object.
 * @author PPROG Team 2101_D - AGL
 * @param inventory A pointer to the Inventory structure.
 * @param object_id The ID of the object to be checked.
 * @return TRUE if the object is present in the inventory, FALSE if it is not present or if the inventory pointer is NULL.
 */
Bool inventory_contains(Inventory *inventory, Id object_id);

/**
* @brief Sets the set of objects in the inventory.
* @author PPROG Team 2101_D - AGL
* @param inventory A pointer to the Inventory structure.
* @param objs A pointer to the Set structure to be assigned to the inventory.
* @return OK if the set of objects was successfully assigned, ERROR if either the inventory pointer or the set pointer is NULL.
*/
Status inventory_set_objs(Inventory* inventory, Set* objs);

/**
 * @brief Sets the maximum number of objects that the inventory can hold.
 * @author PPROG Team 2101_D - AGL
 * @param inventory A pointer to the Inventory structure.
 * @param max_objs The maximum number of objects to be set in the inventory. It must be a non-negative integer.
 * @return OK if the maximum number of objects was successfully set, ERROR if the inventory pointer is NULL or if max_objs is negative.
 */
Status inventory_set_max_objs(Inventory* inventory, int max_objs);

/**
 * @brief Checks if the inventory is full.
 * @author PPROG Team 2101_D - AGL
 * @param inventory A pointer to the Inventory structure.
 * @return TRUE if the inventory is full, FALSE if it is not full or if the inventory pointer is NULL.
 */
Bool inventory_is_full(Inventory* inventory);

/**
 * @brief Checks if the inventory is empty.
 * @author PPROG Team 2101_D - AGL
 * @param inventory A pointer to the Inventory structure.
 * @return TRUE if the inventory is empty and FALSE otherwise.
 */
Bool inventory_is_empty(Inventory *inventory);

/**
 * @brief Gets the object ID at a specific position in the inventory.
 * @author PPROG Team 2101_D - AGL
 * @param inventory A pointer to the Inventory structure.
 * @param position The position of the object in the inventory.
 * @return The ID of the object at the specified position, or NO_ID if the position is invalid.
 */
Id inventory_get_object_id_at(Inventory *inventory, int position);

/**
 * @brief Adds an object to the inventory (if there is space available).
 * @author PPROG Team 2101_D - AGL
 * @param inventory A pointer to the Inventory structure.
 * @param obj_id The ID of the object to be added.
 * @return OK if the object was successfully added, ERROR if the inventory is full or the input is invalid.
 */
Status inventory_add_object_id(Inventory* inventory, Id obj_id);

/**
 * @brief Removes an object from the inventory.
 * @author PPROG Team 2101_D - AGL
 * @param inventory A pointer to the Inventory structure.
 * @param obj_id The ID of the object to be removed.
 * @return OK if the object was successfully removed, ERROR if the object is not found or the input is invalid.
 */
Status inventory_del_object_id(Inventory* inventory, Id obj_id);

/**
 * @brief Prints the inventory (debugging purposes).
 * @author PPROG Team 2101_D - AGL
 * @param inventory A pointer to the Inventory structure.
 * @return OK if the inventory was successfully printed, ERROR if the inventory pointer is NULL.
 */
Status inventory_print(Inventory *inventory);


 
 #endif 
 