/**
 * @brief It implements the space module
 *
 * @file space.c
 * @author PPROG - Equipo 2101_D - AGL
 * @version 2.0.7
 * @date 27-01-2025
 * @copyright GNU Public License
 */

 #include "../include/inventory.h"
  #include "../include/set.h"

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 
/**
* @brief inventory.c
*
* This struct stores all the information of an inventory.
*/
struct _Inventory {
  Set *objs;               /*!< Set of objects in the player's backpack */
  int max_objs;             /*!< max number of objects in the player's backpack */
};
 
  /** This function creates a new inventory with a given maximum number of objects  */
  Inventory* inventory_create(int max_objs) {
    Inventory* new_inventory = NULL;

    /*ensure valid input*/
    if(max_objs < 0){
      return NULL;
    }
 
    /*allocate for the new inventory and if allocation successful*/
    new_inventory = (Inventory*)malloc(sizeof(Inventory));
    if (new_inventory == NULL) {
      return NULL;
    }

    /*Initialize the set of objects*/
    new_inventory-> objs = set_create();  
    if(new_inventory-> objs == NULL){
      inventory_destroy(new_inventory);
      return NULL;
    }

    /*set the maximum number of objects*/
    new_inventory->max_objs = max_objs;
 
    return new_inventory;
  }
 
  /** This function destroys an inventory and frees the memory allocated for
   * the Inventory structure and its associated Set of objects  */
  Status inventory_destroy(Inventory* inventory) {
    if (!inventory) {
      return ERROR;
    }
 
    if(inventory->objs != NULL){
      set_destroy(inventory->objs);
    }

    free(inventory);
    return OK;
  }
 
  /**This function returns a pointer to the set of objects contained in the 
   * inventory. If the inventory pointer is NULL, it returns NULL. */
  Set* inventory_get_objs(Inventory* inventory) {
    if (!inventory) {
      return NULL;
    }
    return inventory->objs;
  }

  /**This function returns the maximum number of objects that the inventory can
  * hold. If the inventory pointer is NULL, it returns -1. */
  int inventory_get_max_objs(Inventory* inventory) {
    if (!inventory) {
      return -1;  
    }
    return inventory->max_objs;
  }

  /** This function checks if the inventory contains a specific object by
  * using the set_belongs function to check for the presence of the object ID in the set */
  Bool inventory_contains(Inventory *inventory, Id object_id) {
    if (!inventory || !inventory->objs || object_id == NO_ID) {
      return FALSE;
    }
  
    if(set_belongs(inventory->objs, object_id) == FALSE){
      return FALSE;
    }
  
    return TRUE;
  }

  /*** This function sets the set of objects contained in the inventory. It updates
  * the inventory's set of objects to the given set. If either the inventory
  * pointer or the set pointer is NULL, it returns ERROR. */
  Status inventory_set_objs(Inventory* inventory, Set* objs) {
    if (!inventory || !objs) {
      return ERROR;
    }
    inventory->objs = objs;
    return OK;
  }

  /**This function sets the maximum number of objects that the inventory can hold
  * to the value passed as argument. If the inventory pointer is NULL or if max_objs is
  * negative, it returns ERROR. */
  Status inventory_set_max_objs(Inventory* inventory, int max_objs) {
    if (!inventory || max_objs < 0) {
      return ERROR;
    }
    inventory->max_objs = max_objs;
    return OK;
  }

  /**This function checks if the inventory has reached its maximum capacity by
  * using the set_get_num_elements function to get the number of elements in the set. */
  Bool inventory_is_full(Inventory* inventory) {

    int num_objects = 0;

    if (!inventory) {
      return FALSE;
    }

   num_objects = set_get_num_elements(inventory->objs);
    if (num_objects == -1) {
      return FALSE;
    }
    return num_objects >= inventory->max_objs;
  }

  /**This function checks if the inventory is empty by using the set_get_num_elements
  * function to get the number of elements in the set. */
  Bool inventory_is_empty(Inventory *inventory){

    int num_objects = 0;

    if (!inventory) {
      return TRUE; 
    }

    num_objects = set_get_num_elements(inventory->objs);
    if(num_objects == 0 || num_objects == -1){
      return TRUE;
    }

    return FALSE;
  }

  /**This function returns the object ID at the specified position in the inventory. */
  Id inventory_get_object_id_at(Inventory *inventory, int position){
    if (inventory == NULL || position < 0 || position >= set_get_num_elements(inventory->objs)){
      return NO_ID;
    }

    return set_get_Id_in_pos(inventory->objs, position);
  }

  /**This function adds an object to the inventory if there is space available. */
  Status inventory_add_object_id(Inventory* inventory, Id obj_id) {
    if (inventory == NULL || obj_id == NO_ID) {
      return ERROR;
    }

    if (inventory_is_full(inventory) == TRUE) {
      return ERROR;
    }

    if(set_add(inventory->objs, obj_id) == ERROR){
      return ERROR;
    }

    return OK;
  }

  /** This function removes an object from the inventory */
  Status inventory_del_object_id(Inventory* inventory, Id obj_id) {
    if (!inventory || obj_id == NO_ID) {
      return ERROR;
    }

    /*set_del checks first if the object belogs to the set, and then removes it*/
    if(set_del(inventory->objs, obj_id) == ERROR){
      return ERROR;
    }

    return OK;
  }

  /**This function prints the details of the inventory, including the maximum
 * number of objects and the IDs of the objects currently in the inventory. */
  Status inventory_print(Inventory *inventory) {

    int i;
    int num_objects = -1;
    Id obj_id_aux = NO_ID;

    if (!inventory) {
      return ERROR;
    }

    fprintf(stdout, "Inventory:\n");
    fprintf(stdout, "Max objects: %d\n", inventory->max_objs);

    num_objects = set_get_num_elements(inventory->objs);
    if (num_objects != -1) {
      fprintf(stdout, "Number of objects: %d\n", num_objects);
      /*Print ID of every object in the inventory*/
      fprintf(stdout, "Object IDs: ");
      for (i = 0; i < num_objects; i++) {
        obj_id_aux = set_get_Id_in_pos(inventory->objs, i);
        if (obj_id_aux != NO_ID) {
          fprintf(stdout, "%ld ", obj_id_aux);
        }
      }
    }else{
      fprintf(stdout, "No objects in the inventary");
    }
  
    fprintf(stdout, "\n");

    return OK;
  }
 
 
 