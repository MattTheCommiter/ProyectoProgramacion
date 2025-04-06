/** 
 * @brief Test functions for the object module
 * 
 * @file object_test.h
 * @author Alvaro Inigo
 * @version 1.0
 * @date 04-04-2025
 * @copyright GNU Public License
 */

#ifndef OBJECT_TEST
#define OBJECT_TEST

#include "test.h"
#include "object.h"

/**
 * @test Test object_create with valid ID
 * @pre The ID is a valid number (not NO_ID)
 * @post The returned pointer is not NULL
 */
void test1_object_create();

/**
 * @test Test object_destroy with a valid object
 * @pre A valid object is created
 * @post The function returns OK
 */
void test1_object_destroy();

/**
 * @test Test object_get_id with a valid object
 * @pre The object is created with a specific ID
 * @post The returned ID matches the one used in creation
 */
void test1_object_get_id();

/**
 * @test Test object_set_id with a valid object
 * @pre A valid object is created and a new ID is set
 * @post The new ID is correctly stored in the object
 */
void test1_object_set_id();

/**
 * @test Test object_get_name after setting a valid name
 * @pre A valid object is created and a name is set
 * @post The function returns a pointer to the correct name
 */
void test1_object_get_name();

/**
 * @test Test object_set_name with a valid name
 * @pre A valid object is created, a non-empty name is passed
 * @post The function returns OK
 */
void test1_object_set_name();

/**
 * @test Test object_print with a valid object
 * @pre A valid object is created and given a name
 * @post The function prints and returns OK
 */
void test1_object_print();

/**
 * @test Test object_set_description with a valid description
 * @pre A valid object is created and a description is passed
 * @post The function returns OK
 */
void test1_object_set_description();

/**
 * @test Test object_get_description after setting it
 * @pre A valid object is created and a description is set
 * @post The returned description matches the one set
 */
void test1_object_get_description();




/**
 * @test Test object_create with invalid ID
 * @pre The ID is NO_ID
 * @post The returned pointer is NULL
 */
void test2_object_create();

/**
 * @test Test object_destroy with NULL pointer
 * @pre The input object pointer is NULL
 * @post The function returns ERROR
 */
void test2_object_destroy();

/**
 * @test Test object_get_id with NULL object
 * @pre The input object is NULL
 * @post The function returns NO_ID
 */
void test2_object_get_id();

/**
 * @test Test object_set_id with NULL object
 * @pre The object is NULL, ID is valid
 * @post The function returns ERROR
 */
void test2_object_set_id();

/**
 * @test Test object_get_name with NULL object
 * @pre The object is NULL
 * @post The function returns NULL
 */
void test2_object_get_name();

/**
 * @test Test object_set_name with an empty string
 * @pre A valid object is created, an empty name is passed
 * @post The function returns OK
 */
void test2_object_set_name();

/**
 * @test Test object_print with NULL object
 * @pre The object pointer is NULL
 * @post The function returns ERROR
 */
void test2_object_print();

/**
 * @test Test object_set_description with an empty string
 * @pre A valid object is created, an empty description is passed
 * @post The function returns OK
 */
void test2_object_set_description();

/**
 * @test Test object_get_description with NULL object
 * @pre The object is NULL
 * @post The function returns NULL
 */
void test2_object_get_description();





#endif