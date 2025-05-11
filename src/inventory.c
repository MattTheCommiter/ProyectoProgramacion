/**
 * @brief It implements the inventory module
 *
 * @file inventory.c
 * @author PPROG - Equipo 2101_D - Araceli Gutiérrez
 * @version 2.0.7
 * @date 21-03-2025
 * @copyright GNU Public License
 */

#include "inventory.h"

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 
/**
* @brief This struct stores all the information of an inventory: the number of objects and the set that contains the objects
*
* 
*/
struct _Inventory {
  Set *objs;               /*!< Set of objects in the player's backpack */
  int max_objs;             /*!< max number of objects in the player's backpack */
};
 

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


Set* inventory_get_objs(Inventory* inventory) {
  if (!inventory) {
    return NULL;
  }
  return inventory->objs;
}




int inventory_get_max_objs(Inventory* inventory) {
  if (!inventory) {
    return -1;  
  }
  return inventory->max_objs;
}

Bool inventory_contains(Inventory *inventory, Id object_id) {
  if (!inventory || !inventory->objs || object_id == NO_ID) {
    return FALSE;
  }

  return set_belongs(inventory->objs, object_id);
}

Status inventory_set_objs(Inventory* inventory, Set* objs) {
  if (!inventory || !objs) {
    return ERROR;
  }
  inventory->objs = objs;
  return OK;
}



Status inventory_set_max_objs(Inventory* inventory, int max_objs) {
  if (!inventory || max_objs < 0) {
    return ERROR;
  }
  inventory->max_objs = max_objs;
  return OK;
}


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


Bool inventory_is_empty(Inventory *inventory){


  if (!inventory) {
    return TRUE; 
  }
  return set_is_empty(inventory->objs);
}


Id inventory_get_object_id_at(Inventory *inventory, int position){
  if (inventory == NULL || position < 0 || position >= set_get_num_elements(inventory->objs)){
    return NO_ID;
  }

  return set_get_Id_in_pos(inventory->objs, position);
}


Status inventory_add_object_id(Inventory* inventory, Id obj_id) {
  if (inventory == NULL || obj_id == NO_ID) {
    return ERROR;
  }

  if (inventory_is_full(inventory) == TRUE) {
    return ERROR;
  }

  return set_add(inventory->objs, obj_id);
}


Status inventory_del_object_id(Inventory* inventory, Id obj_id) {
  if (!inventory || obj_id == NO_ID) {
    return ERROR;
  }


  return set_del(inventory->objs, obj_id);
}


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


