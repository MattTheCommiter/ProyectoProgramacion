/** 
 * @brief It tests the Inventory module
 * 
 * @file inventory_test.c
 * @author PPROG - Team 2101_D - AGL
 * @version 1.0.2 
 * @date 22-03-2025
 * @copyright GNU Public License
 */

#include "inventory_test.h"

 #include <stdio.h> 
 #include <stdlib.h> 
 #include <string.h> 
 
 #define MAX_TESTS 32
 
 /** 
  * @brief Main function for INVENTORY unit tests. 
  * 
  * You may execute ALL or a SINGLE test
  *   1.- No parameter -> ALL test are executed 
  *   2.- A number means a particular test (the one identified by that number) 
  *       is executed
  *  
  */
 int main(int argc, char** argv) {
 
   int test = 0;
   int all = 1;
 
   if (argc < 2) {
     printf("Running all test for module Inventory:\n");
   } else {
     test = atoi(argv[1]);
     all = 0;
     printf("Running test %d:\t", test);
     if (test < 1 && test > MAX_TESTS) {
       printf("Error: unknown test %d\t", test);
       exit(EXIT_SUCCESS);
     }
   }
 
 
   if (all || test == 1) test1_inventory_create();
   if (all || test == 2) test2_inventory_create();
   if (all || test == 3) test3_inventory_create();
   if (all || test == 4) test1_inventory_get_objs();
   if (all || test == 5) test2_inventory_get_objs();
   if (all || test == 6) test1_inventory_get_max_objs();
   if (all || test == 7) test2_inventory_get_max_objs();
   if (all || test == 8) test3_inventory_get_max_objs();
   if (all || test == 9) test1_inventory_contains();
   if (all || test == 10) test2_inventory_contains();
   if (all || test == 11) test3_inventory_contains();
   if (all || test == 12) test1_inventory_set_objs();
   if (all || test == 13) test2_inventory_set_objs();
   if (all || test == 14) test3_inventory_set_objs();
   if (all || test == 15) test1_inventory_set_max_objs();
   if (all || test == 16) test2_inventory_set_max_objs();
   if (all || test == 17) test3_inventory_set_max_objs();
   if (all || test == 18) test1_inventory_is_full();
   if (all || test == 19) test2_inventory_is_full();
   if (all || test == 20) test3_inventory_is_full();
   if (all || test == 21) test1_inventory_is_empty();
   if (all || test == 22) test2_inventory_is_empty();
   if (all || test == 23) test3_inventory_is_empty();
   if (all || test == 24) test1_inventory_get_object_id_at();
   if (all || test == 25) test2_inventory_get_object_id_at();
   if (all || test == 26) test3_inventory_get_object_id_at();
   if (all || test == 27) test1_inventory_add_object_id();
   if (all || test == 28) test2_inventory_add_object_id();
   if (all || test == 29) test3_inventory_add_object_id();
   if (all || test == 30) test1_inventory_del_object_id();
   if (all || test == 31) test2_inventory_del_object_id();
   if (all || test == 32) test3_inventory_del_object_id();


 
   PRINT_PASSED_PERCENTAGE;
 
   return 0;
 }
 
 
/**Test whether a new inventory is successfully created*/
void test1_inventory_create() {
    int result;
    Inventory* inventory = NULL;
    Set* objs = NULL;

    inventory = inventory_create(10);   /*Create a new inventory with a maximum of 10 objects*/
    if (inventory != NULL) {
        if (inventory_set_max_objs(inventory, 10) == OK) {
            objs = inventory_get_objs(inventory);
            if (objs != NULL) {
                result = 1;
            } else {
                result = 0;
            }
        } else {
            result = 0;
        }
    } else {
        result = 0;
    }
    PRINT_TEST_RESULT(result);
    inventory_destroy(inventory);
}


/**Test whether the function returns NULL for invalid input (negative max_objs)*/
void test2_inventory_create() {
    Inventory* inventory;
    inventory = inventory_create(-1);
    PRINT_TEST_RESULT(inventory == NULL);
}

/**creates an inventory with MAX_ELEMENTS_IN_SET as the maximum number of objects,
 * checks if it was created successfully and if max_objs is set correctly */
void test3_inventory_create() {
    Inventory* inventory;
    inventory = inventory_create(MAX_ELEMENTS_IN_SET);
    PRINT_TEST_RESULT(inventory != NULL && inventory_get_max_objs(inventory) == MAX_ELEMENTS_IN_SET);
    inventory_destroy(inventory);
}

/**test function for valid inventory */
void test1_inventory_get_objs() {
    Inventory* inventory = inventory_create(10);
    Set* objs = inventory_get_objs(inventory);
    PRINT_TEST_RESULT(objs != NULL);
    inventory_destroy(inventory);
}

/**tests if inventory_get_objs correctly returns NULL when the inventory pointer is NULL */
void test2_inventory_get_objs() {
    Set* objs = inventory_get_objs(NULL);
    PRINT_TEST_RESULT(objs == NULL);
}

/** tests if it correctly returns the maximum number of objects for a valid inventory */
void test1_inventory_get_max_objs() {
    Inventory* inventory = inventory_create(10);
    int max_objs = inventory_get_max_objs(inventory);
    PRINT_TEST_RESULT(max_objs == 10);
    inventory_destroy(inventory);
}

/**Tests if it correctly returns -1 when the inventory pointer is NULL */
void test2_inventory_get_max_objs() {
    int max_objs = inventory_get_max_objs(NULL);
    PRINT_TEST_RESULT(max_objs == -1);
}

/**test for the maximum number of objects of an inventory */
void test3_inventory_get_max_objs() {
    Inventory* inventory = inventory_create(MAX_ELEMENTS_IN_SET);
    int max_objs = inventory_get_max_objs(inventory);
    PRINT_TEST_RESULT(max_objs == MAX_ELEMENTS_IN_SET);
    inventory_destroy(inventory);
}

/**tests if inventory_contains correctly identifies an object that exists in the inventory */
void test1_inventory_contains() {
    Inventory* inventory = NULL;
    Bool result;
    inventory = inventory_create(10);
    set_add(inventory_get_objs(inventory), 1);
    result = inventory_contains(inventory, 1);
    PRINT_TEST_RESULT(result == TRUE);
    inventory_destroy(inventory);
}

/**tests if inventory_contains correctly identifies an object that does not exist in the inventory */
void test2_inventory_contains() {
    Inventory* inventory = inventory_create(10);
    Bool result = inventory_contains(inventory, 1);
    PRINT_TEST_RESULT(result == FALSE);
    inventory_destroy(inventory);
}

/** tests if inventory_contains correctly returns FALSE when the inventory pointer is NULL */
void test3_inventory_contains() {
    Bool result = inventory_contains(NULL, 1);
    PRINT_TEST_RESULT(result == FALSE);
}

/** tests if inventory_set_objs correctly updates the set of objects in a valid inventory */
void test1_inventory_set_objs() {
    Inventory* inventory = NULL;
    Set* new_objs = NULL;
    Status result;
    inventory = inventory_create(10);
    new_objs = inventory_get_objs(inventory);
    result = inventory_set_objs(inventory, new_objs);
    PRINT_TEST_RESULT(result == OK && inventory_get_objs(inventory) == new_objs); 
    inventory_destroy(inventory);
}

/** tests if inventory_set_objs correctly returns ERROR when the inventory pointer is NULL */
void test2_inventory_set_objs() {
    Set* new_objs = set_create();
    Status result = inventory_set_objs(NULL, new_objs);
    PRINT_TEST_RESULT(result == ERROR);
    set_destroy(new_objs);
}

/** tests if inventory_set_objs correctly returns ERROR when the set pointer is NULL */
void test3_inventory_set_objs() {
    Inventory* inventory = inventory_create(10);
    Status result = inventory_set_objs(inventory, NULL);
    PRINT_TEST_RESULT(result == ERROR);
    inventory_destroy(inventory);
}

/** tests if inventory_set_max_objs correctly sets the maximum number of objects for a valid inventory */
void test1_inventory_set_max_objs() {
    Inventory* inventory = inventory_create(10);
    Status result = inventory_set_max_objs(inventory, 20);
    PRINT_TEST_RESULT(result == OK && inventory_get_max_objs(inventory) == 20);
    inventory_destroy(inventory);
}

/**Test if it correctly returns ERROR when the inventory pointer is NULL */
void test2_inventory_set_max_objs() {
    Status result = inventory_set_max_objs(NULL, 20);
    PRINT_TEST_RESULT(result == ERROR);
}

/** tests if inventory_set_max_objs correctly returns ERROR when the max_objs value is negative */
void test3_inventory_set_max_objs() {
    Inventory* inventory = inventory_create(10);
    Status result = inventory_set_max_objs(inventory, -5);
    PRINT_TEST_RESULT(result == ERROR);
    inventory_destroy(inventory);
}

/** tests if inventory_is_full correctly identifies a full inventory */
void test1_inventory_is_full() {
    Inventory* inventory = NULL;
    Bool result;
    inventory = inventory_create(2);;
    set_add(inventory_get_objs(inventory), 1);
    set_add(inventory_get_objs(inventory), 2);
    result = inventory_is_full(inventory);
    PRINT_TEST_RESULT(result == TRUE);
    inventory_destroy(inventory);
}

/** tests if inventory_is_full correctly identifies an inventory that is not full */
void test2_inventory_is_full() {
    Inventory* inventory = NULL;
    Bool result ;
    inventory = inventory_create(2);
    set_add(inventory_get_objs(inventory), 1);
    result = inventory_is_full(inventory);
    PRINT_TEST_RESULT(result == FALSE);
    inventory_destroy(inventory);
}

/** tests if inventory_is_full correctly returns FALSE when the inventory pointer is NULL */
void test3_inventory_is_full() {
    Bool result = inventory_is_full(NULL);
    PRINT_TEST_RESULT(result == FALSE);
}

/** tests if inventory_is_empty correctly identifies an empty inventory */
void test1_inventory_is_empty() {
    Inventory* inventory = NULL;
    Bool result;
    inventory = inventory_create(10);
    result = inventory_is_empty(inventory);
    PRINT_TEST_RESULT(result == TRUE);
    inventory_destroy(inventory);
}

/**tests if inventory_is_empty correctly identifies an inventory that is not empty */
void test2_inventory_is_empty() {
    Inventory* inventory = NULL;
    Bool result;
    inventory = inventory_create(10);
    set_add(inventory_get_objs(inventory), 1);
    result = inventory_is_empty(inventory);
    PRINT_TEST_RESULT(result == FALSE);
    inventory_destroy(inventory);
}

/** tests if inventory_is_empty correctly returns TRUE when the inventory pointer is NULL */
void test3_inventory_is_empty() {
    Bool result = inventory_is_empty(NULL);
    PRINT_TEST_RESULT(result == TRUE);
}

/** tests if inventory_get_object_id_at correctly returns the object ID at a valid position in the inventory */
void test1_inventory_get_object_id_at() {
    Inventory* inventory = NULL;
    Id object_id = NO_ID;
    inventory = inventory_create(10);
    set_add(inventory_get_objs(inventory), 1);
    set_add(inventory_get_objs(inventory), 2);
    object_id = inventory_get_object_id_at(inventory, 1);
    PRINT_TEST_RESULT(object_id == 2);
    inventory_destroy(inventory);
}

/** tests if inventory_get_object_id_at correctly returns NO_ID when there is no object at the position passed */
void test2_inventory_get_object_id_at() {
    Inventory* inventory = NULL;
    Id object_id = NO_ID;
    inventory = inventory_create(10);
    set_add(inventory_get_objs(inventory), 1);
    object_id = inventory_get_object_id_at(inventory, 10);
    PRINT_TEST_RESULT(object_id == NO_ID);
    inventory_destroy(inventory);
}

/**tests if inventory_get_object_id_at correctly returns NO_ID when the inventory pointer is NULL */
void test3_inventory_get_object_id_at() {
    Id object_id = NO_ID;
    object_id = inventory_get_object_id_at(NULL, 1);
    PRINT_TEST_RESULT(object_id == NO_ID);
}

/** tests if inventory_add_object_id correctly adds an object to an inventory that has space available */
void test1_inventory_add_object_id() {
    Inventory* inventory = NULL;
    Status result;
    inventory = inventory_create(10);
    result = inventory_add_object_id(inventory, 1);
    PRINT_TEST_RESULT(result == OK && inventory_contains(inventory, 1) == TRUE);
    inventory_destroy(inventory);
}

/** tests if inventory_add_object_id correctly returns ERROR when trying to add an object to a full inventory */
void test2_inventory_add_object_id() {
    Inventory* inventory = NULL;
    Status result;
    inventory = inventory_create(1);
    set_add(inventory_get_objs(inventory), 1);
    result = inventory_add_object_id(inventory, 2);
    PRINT_TEST_RESULT(result == ERROR && inventory_contains(inventory, 2) == FALSE);
    inventory_destroy(inventory);
}

/**tests if inventory_add_object_id correctly returns ERROR when the inventory pointer is NULL */
void test3_inventory_add_object_id() {
    Status result = inventory_add_object_id(NULL, 1);
    PRINT_TEST_RESULT(result == ERROR);
}

/** tests if inventory_del_object_id correctly removes an existing object from the inventory */
void test1_inventory_del_object_id() {
    Inventory* inventory = NULL;
    Status result;
    inventory = inventory_create(10);
    set_add(inventory_get_objs(inventory), 1);
    result = inventory_del_object_id(inventory, 1);
    PRINT_TEST_RESULT(result == OK && inventory_contains(inventory, 1) == FALSE);
    inventory_destroy(inventory);
}

/** tests if inventory_del_object_id correctly returns ERROR
 * when trying to remove an object that does not exist in the inventory */
void test2_inventory_del_object_id() {
    Inventory* inventory = NULL;
    Status result;
    inventory = inventory_create(10);
    result = inventory_del_object_id(inventory, 1);
    PRINT_TEST_RESULT(result == ERROR && inventory_contains(inventory, 1) == FALSE);
    inventory_destroy(inventory);
}

/**tests if inventory_del_object_id correctly returns ERROR when the inventory pointer is NULL */
void test3_inventory_del_object_id() {
    Status result;
    result = inventory_del_object_id(NULL, 1);
    PRINT_TEST_RESULT(result == ERROR);
}







