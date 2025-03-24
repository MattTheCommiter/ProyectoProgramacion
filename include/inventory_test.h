/** 
 * @brief  test functions  for the Inventary module
 * 
 * @file inventory_test.h
 * @author PPROG - Team 2101_D - AGL
 * @version 1.0.2
 * @date 22-03-2025
 * @copyright GNU Public License
 */

 #ifndef INVENTORY_TEST_H
 #define INVENTORY_TEST_H
 
 #include "set.h"
 #include "inventory.h"
 #include "test.h"
 
/**
 * @test Test whether a new inventory is successfully created
 * @pre Inventory is created with a maximum of 10 objects
 * @post Non-NULL pointer to the set of objects in the inventory
 */
void test1_inventory_create();
 
/**
 * @test Test whether the function returns NULL for invalid input (negative max_objs)
 * @pre Inventory is created with a negative maximum number of objects
 * @post Function returns NULL
 */
void test2_inventory_create(); 

/**
 * @test Creates an inventory with MAX_ELEMENTS_IN_SET as the maximum number of objects
 * @pre Inventory is created with MAX_ELEMENTS_IN_SET as the maximum number of objects
 * @post Inventory is successfully created and max_objs is set correctly
 */
void test3_inventory_create();

/**
 * @test Test function for valid inventory
 * @pre Inventory is created with a maximum of 10 objects
 * @post The set of objects in the inventory is not NULL
 */
void test1_inventory_get_objs();

/**
 * @test Tests if inventory_get_objs correctly returns NULL when the inventory pointer is NULL
 * @pre Inventory pointer is NULL
 * @post Function returns NULL
 */
void test2_inventory_get_objs();

/**
 * @test Tests if it correctly returns the maximum number of objects for a valid inventory
 * @pre Inventory is created with a maximum of 10 objects
 * @post Function returns the correct maximum number of objects (10)
 */
void test1_inventory_get_max_objs();

/**
 * @test Tests if it correctly returns -1 when the inventory pointer is NULL
 * @pre Inventory pointer is NULL
 * @post Function returns -1
 */
void test2_inventory_get_max_objs();

/**
 * @test Test for the maximum number of objects of an inventory
 * @pre Inventory is created with MAX_ELEMENTS_IN_SET as the maximum number of objects
 * @post Function returns the correct maximum number of objects (MAX_ELEMENTS_IN_SET)
 */
void test3_inventory_get_max_objs();


/**
 * @test Tests if inventory_contains correctly identifies an object that exists in the inventory
 * @pre Inventory is created with a maximum of 10 objects and object 1 is added to the inventory
 * @post Function returns TRUE indicating the object exists in the inventory
 */
void test1_inventory_contains();

/**
 * @test Tests if inventory_contains correctly identifies an object that does not exist in the inventory
 * @pre Inventory is created with a maximum of 10 objects and no objects are added to the inventory
 * @post Function returns FALSE indicating the object does not exist in the inventory
 */
void test2_inventory_contains();

/**
 * @test Tests if inventory_contains correctly returns FALSE when the inventory pointer is NULL
 * @pre Inventory pointer is NULL
 * @post Function returns FALSE
 */
void test3_inventory_contains();

/**
 * @test Tests if inventory_set_objs correctly updates the set of objects in a valid inventory
 * @pre Inventory is created with a maximum of 10 objects and a new set of objects is created
 * @post Function updates the inventory with the new set of objects and returns OK
 */
void test1_inventory_set_objs();

/**
 * @test Tests if inventory_set_objs correctly returns ERROR when the inventory pointer is NULL
 * @pre Inventory pointer is NULL and a new set of objects is created
 * @post Function returns ERROR
 */
void test2_inventory_set_objs();

/**
 * @test Tests if inventory_set_objs correctly returns ERROR when the set pointer is NULL
 * @pre Inventory is created with a maximum of 10 objects and the set pointer is NULL
 * @post Function returns ERROR
 */
void test3_inventory_set_objs();

/**
 * @test Tests if inventory_set_max_objs correctly sets the maximum number of objects for a valid inventory
 * @pre Inventory is created with a maximum of 10 objects
 * @post Function sets the maximum number of objects to 20 and returns OK
 */
void test1_inventory_set_max_objs();

/**
 * @test Tests if it correctly returns ERROR when the inventory pointer is NULL
 * @pre Inventory pointer is NULL
 * @post Function returns ERROR
 */
void test2_inventory_set_max_objs();

/**
 * @test Tests if inventory_set_max_objs correctly returns ERROR when the max_objs value is negative
 * @pre Inventory is created with a maximum of 10 objects and max_objs value is set to -5
 * @post Function returns ERROR
 */
void test3_inventory_set_max_objs();

/**
 * @test Tests if inventory_is_full correctly identifies a full inventory
 * @pre Inventory is created with a maximum of 2 objects and 2 objects are added to the inventory
 * @post Function returns TRUE indicating the inventory is full
 */
void test1_inventory_is_full();

/**
 * @test Tests if inventory_is_full correctly identifies an inventory that is not full
 * @pre Inventory is created with a maximum of 2 objects and only 1 object is added to the inventory
 * @post Function returns FALSE indicating the inventory is not full
 */
void test2_inventory_is_full();

/**
 * @test Tests if inventory_is_full correctly returns FALSE when the inventory pointer is NULL
 * @pre Inventory pointer is NULL
 * @post Function returns FALSE
 */
void test3_inventory_is_full();

/**
 * @test Tests if inventory_is_empty correctly identifies an empty inventory
 * @pre Inventory is created with a maximum of 10 objects and no objects are added to the inventory
 * @post Function returns TRUE indicating the inventory is empty
 */
void test1_inventory_is_empty();

/**
 * @test Tests if inventory_is_empty correctly identifies an inventory that is not empty
 * @pre Inventory is created with a maximum of 10 objects and object 1 is added to the inventory
 * @post Function returns FALSE indicating the inventory is not empty
 */
void test2_inventory_is_empty();

/**
 * @test Tests if inventory_is_empty correctly returns TRUE when the inventory pointer is NULL
 * @pre Inventory pointer is NULL
 * @post Function returns TRUE
 */
void test3_inventory_is_empty();

/**
 * @test Tests if inventory_get_object_id_at correctly returns the object ID at a valid position in the inventory
 * @pre Inventory is created with a maximum of 10 objects and objects 1 and 2 are added to the inventory
 * @post Function returns the object ID at position 1, which is 2
 */
void test1_inventory_get_object_id_at();

/**
 * @test Tests if inventory_get_object_id_at correctly returns NO_ID when there is no object at the position passed
 * @pre Inventory is created with a maximum of 10 objects and object 1 is added to the inventory
 * @post Function returns NO_ID when querying position 10, where no object exists
 */
void test2_inventory_get_object_id_at();

/**
 * @test Tests if inventory_get_object_id_at correctly returns NO_ID when the inventory pointer is NULL
 * @pre Inventory pointer is NULL
 * @post Function returns NO_ID
 */
void test3_inventory_get_object_id_at();

/**
 * @test Tests if inventory_add_object_id correctly adds an object to an inventory that has space available
 * @pre Inventory is created with a maximum of 10 objects and object 1 is added to the inventory
 * @post Function returns OK and the inventory contains object 1
 */
void test1_inventory_add_object_id();

/**
 * @test Tests if inventory_add_object_id correctly returns ERROR when trying to add an object to a full inventory
 * @pre Inventory is created with a maximum of 1 object and object 1 is added to the inventory
 * @post Function returns ERROR and the inventory does not contain object 2
 */
void test2_inventory_add_object_id();

/**
 * @test Tests if inventory_add_object_id correctly returns ERROR when the inventory pointer is NULL
 * @pre Inventory pointer is NULL
 * @post Function returns ERROR
 */
void test3_inventory_add_object_id();

/**
 * @test Tests if inventory_del_object_id correctly removes an existing object from the inventory.
 * @pre An inventory is created with a capacity of 10 and an object with ID 1 is added to it.
 * @post The object with ID 1 is removed from the inventory, and the function returns OK status.
 */
void test1_inventory_del_object_id();

/**
 * @test Tests if inventory_del_object_id correctly returns ERROR when trying to remove an object that does not exist in the inventory.
 * @pre An inventory is created with a capacity of 10, but no objects are added to it.
 * @post The function attempts to remove an object with ID 1, which does not exist in the inventory, and returns ERROR status.
 */
void test2_inventory_del_object_id();

/**
 * @test Tests if inventory_del_object_id correctly returns ERROR when the inventory pointer is NULL.
 * @pre The inventory pointer is set to NULL.
 * @post The function attempts to remove an object with ID 1 from a NULL inventory pointer and returns ERROR status.
 */
void test3_inventory_del_object_id();


 
 #endif
 