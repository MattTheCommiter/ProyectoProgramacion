/** 
 * @brief It declares the tests for the space module
 * 
 * @file space_test.h
 * @author Profesores Pprog
 * @version 0.0 
 * @date 17-02-2025
 * @copyright GNU Public License
 */

#ifndef SPACE_TEST_H
#define SPACE_TEST_H

/**
 * @test Test space creation
 * @pre Space ID
 * @post Non NULL pointer to space
 */
void test1_space_create();

/**
 * @test Test space creation
 * @pre Space ID
 * @post Space_ID == Supplied Space Id
 */
void test2_space_create();

/**
 * @test Test function for space_name setting
 * @pre String with space name
 * @post Output==OK
 */
void test1_space_set_name();

/**
 * @test Test function for space_name setting
 * @pre pointer to space = NULL
 * @post Output==ERROR
 */
void test2_space_set_name();

/**
 * @test Test function for space_name setting with NULL name
 * @pre Space pointer != NULL, name = NULL
 * @post Output==ERROR
 */
void test3_space_set_name();

/**
 * @test Test function for space's north connection setting
 * @pre Space pointer != NULL, valid ID for north
 * @post Output==OK
 */
void test1_space_set_north();

/**
 * @test Test function for space's north connection setting with NULL space
 * @pre Space pointer == NULL
 * @post Output==ERROR
 */
void test2_space_set_north();

/**
 * @test Test function for space's north connection setting
 * @pre Space pointer != NULL, valid ID '3' for north
 * @post space_get_north returns 3, which corresponds to the set id
 */
void test3_space_set_north();

/**
 * @test Test function for space's north connection setting 
 * @pre Space pointer != NULL, valid ID 'NO_ID' for north
 * @post Output==ERROR
 */
void test4_space_set_north();

/**
 * @test Test function for space's south connection setting
 * @pre Space pointer != NULL, valid ID for south
 * @post Output==OK
 */
void test1_space_set_south();

/**
 * @test Test function for space's south connection setting with NULL space
 * @pre Space pointer == NULL
 * @post Output==ERROR
 */
void test2_space_set_south();

/**
 * @test Test function for space's south connection setting
 * @pre Space pointer != NULL, valid ID '3' for south
 * @post space_get_south returns 3, which corresponds to the set id
 */
void test3_space_set_south();

/**
 * @test Test function for space's south connection setting 
 * @pre Space pointer != NULL, valid ID 'NO_ID' for south
 * @post Output==ERROR
 */
void test4_space_set_south();

/**
 * @test Test function for space's east connection setting
 * @pre Space pointer != NULL, valid ID for east
 * @post Output==OK
 */
void test1_space_set_east();

/**
 * @test Test function for space's east connection setting with NULL space
 * @pre Space pointer == NULL
 * @post Output==ERROR
 */
void test2_space_set_east();

/**
 * @test Test function for space's east connection setting
 * @pre Space pointer != NULL, valid ID '3' for east
 * @post space_get_east returns 3, which corresponds to the set id
 */
void test3_space_set_east();

/**
 * @test Test function for space's east connection setting 
 * @pre Space pointer != NULL, valid ID 'NO_ID' for east
 * @post Output==ERROR
 */
void test4_space_set_east();

/**
 * @test Test function for space's west connection setting
 * @pre Space pointer != NULL, valid ID for west
 * @post Output==OK
 */
void test1_space_set_west();

/**
 * @test Test function for space's west connection setting with NULL space
 * @pre Space pointer == NULL
 * @post Output==ERROR
 */
void test2_space_set_west();

/**
 * @test Test function for space's west connection setting
 * @pre Space pointer != NULL, valid ID '3' for west
 * @post space_get_west returns 3, which corresponds to the set id
 */
void test3_space_set_west();

/**
 * @test Test function for space's west connection setting 
 * @pre Space pointer != NULL, valid ID 'NO_ID' for west
 * @post Output==ERROR
 */
void test4_space_set_west();

/**
 * @test Test adding object ID to space
 * @pre Space pointer != NULL, valid object ID
 * @post Output==OK
 */
void test1_space_add_objectId();

/**
 * @test Test adding object ID to NULL space
 * @pre Space pointer == NULL, valid object ID
 * @post Output==ERROR
 */
void test2_space_add_objectId();

/**
 * @test Test adding NO_ID to space
 * @pre Space pointer is valid, invalid object ID
 * @post Output==ERROR
 */
void test3_space_add_objectId();

/**
 * @test Test getting space name
 * @pre Space pointer != NULL, space has name "adios"
 * @post Returned name of space_get_name is "adios"
 */
void test1_space_get_name();

/**
 * @test Test getting name from NULL space
 * @pre Space pointer == NULL
 * @post Output==NULL
 */
void test2_space_get_name();

/**
 * @test Test getting north connection ID from space
 * @pre Space pointer != NULL, north connection set
 * @post Output==Set north connection ID
 */
void test1_space_get_north();

/**
 * @test Test getting north connection ID from NULL space
 * @pre Space pointer == NULL
 * @post Output==NO_ID
 */
void test2_space_get_north();

/**
 * @test Test getting south connection ID from space
 * @pre Space pointer != NULL, south connection set
 * @post Output==Set south connection ID
 */
void test1_space_get_south();

/**
 * @test Test getting south connection ID from NULL space
 * @pre Space pointer == NULL
 * @post Output==NO_ID
 */
void test2_space_get_south();

/**
 * @test Test getting east connection ID from space
 * @pre Space pointer != NULL, east connection set
 * @post Output==Set east connection ID
 */
void test1_space_get_east();

/**
 * @test Test getting east connection ID from NULL space
 * @pre Space pointer == NULL
 * @post Output==NO_ID
 */
void test2_space_get_east();

/**
 * @test Test getting west connection ID from space
 * @pre Space pointer != NULL, west connection set
 * @post Output==Set west connection ID
 */
void test1_space_get_west();

/**
 * @test Test getting west connection ID from NULL space
 * @pre Space pointer == NULL
 * @post Output==NO_ID
 */
void test2_space_get_west();

/**
 * @test Test getting space ID
 * @pre Space pointer != NULL
 * @post Output==set Space ID
 */
void test1_space_get_id();

/**
 * @test Test getting ID from NULL space
 * @pre Space pointer == NULL
 * @post Output==NO_ID
 */
void test2_space_get_id();

/**
 * @test Test if object belongs to null space
 * @pre Space pointer == NULL, object ID to check
 * @post Output==FALSE
 */
void test1_space_object_belongs();

/**
 * @test Test if object belongs to space with objects(object ID not in space)
 * @pre Space pointer != NULL, object ID not in space
 * @post Output==FALSE
 */
void test2_space_object_belongs();

/**
 * @test Test if object belongs to space with no objects
 * @pre Space pointer != NULL, object ID not in space
 * @post Output==FALSE
 */
void test3_space_object_belongs();

/**
 * @test Test if object with id NO_ID belongs to space (NO_ID cannot be inserted as an object)
 * @pre Space pointer != NULL, object ID = NO_ID
 * @post Output==FALSE
 */
void test4_space_object_belongs();

/**
 * @test Test if object belongs to space (object ID in space)
 * @pre Space pointer != NULL, object ID is valid and is found in the space
 * @post Output==TRUE
 */
void test5_space_object_belongs();

/**
 * @test Test if null space has no objects
 * @pre Space pointer == NULL
 * @post Output==TRUE
 */
void test1_space_has_no_objects();

/**
 * @test Test if space has no objects (space created but no objects)
 * @pre Space pointer != NULL, no objects added
 * @post Output==TRUE
 */
void test2_space_has_no_objects();

/**
 * @test Test if a non-empty space has no objects
 * @pre Space pointer != NULL, object added
 * @post Output==FALSE
 */
void test3_space_has_no_objects();

/**
 * @test Test getting number of objects in null space
 * @pre Space pointer == NULL
 * @post Output==0
 */
void test1_space_get_num_of_objects();

/**
 * @test Test getting number of objects in space (no objects)
 * @pre Space pointer != NULL, no objects added
 * @post Output==0
 */
void test2_space_get_num_of_objects();

/**
 * @test Test getting number of objects in space (3 objects present)
 * @pre Space pointer != NULL, objects added
 * @post Output==3
 */
void test3_space_get_num_of_objects();

/**
 * @test Test getting id of character in null space
 * @pre Space pointer == NULL
 * @post Output==NO_ID
 */
void test1_space_get_character();

/**
 * @test Test getting id of character that is present in space
 * @pre Space pointer != NULL, character with id 10 present in space
 * @post Output==10
 */
void test2_space_get_character();

/**
 * @test Test getting id of a space with no characters
 * @pre Space pointer != NULL, no characters added
 * @post Output==NO_ID
 */
void test3_space_get_character();

/**
 * @test Test setting id of character in null space
 * @pre Space pointer == NULL
 * @post Output==ERROR
 */
void test1_space_set_character();

/**
 * @test Test setting id of character in a valid space that already has a character
 * @pre Space pointer != NULL, character id 10
 * @post Output==ERROR
 */
void test2_space_set_character();

/**
 * @test Test setting id of character in a valid space with no characters
 * @pre Space pointer != NULL, character id 10
 * @post Output==OK
 */
void test3_space_set_character();

/**
 * @test Test checking if a null space's set of objects is full 
 * @pre Space pointer is NULL
 * @post Output==TRUE
 */
void test1_space_set_of_objects_is_full();

/**
 * @test Test checking if a space with full of objects is full 
 * @pre Space pointer != NULL
 * @post Output==TRUE
 */
void test2_space_set_of_objects_is_full();

/**
 * @test Test checking if a space with no objects is full
 * @pre Space pointer != NULL
 * @post Output==FALSE
 */
void test3_space_set_of_objects_is_full();

/**
 * @test Test checking if a space with one object is full
 * @pre Space pointer != NULL
 * @post Output==FALSE
 */
void test4_space_set_of_objects_is_full();

/**
 * @test Test deleting an object from a space with no objects
 * @pre Space pointer != NULL, id of object 5
 * @post Output==ERROR
 */
void test1_space_delete_object();

/**
 * @test Test deleting an object from a null space
 * @pre Space pointer == NULL
 * @post Output==ERROR
 */
void test2_space_delete_object();
 
/**
 * @test Test deleting a NO_ID object from a created space
 * @pre Space pointer != NULL, object id NO_ID
 * @post Output==ERROR
 */
void test3_space_delete_object();
 
/**
 * @test Test deleting an object not present in space
 * @pre Space pointer != NULL and object id 5 (not present in space)
 * @post Output==ERROR
 */
void test4_space_delete_object();
 
/**
 * @test Test deleting object present in space
 * @pre Space pointer != NULL and object id 5 (the one present in space)
 * @post Output==OK
 */
void test5_space_delete_object();
#endif
