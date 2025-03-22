/**
 * @brief it defines all tests for the link module 
 * 
 * @file link_test.h
 * @author Guilherme Povedano 
 * @version 0.0.2
 * @date 19-03-2025
 * @copyright GNU Public License 
*/
#ifndef LINK_TEST_H
#define LINK_TEST_H

#include "link.h"
#include "types.h"
#include "test.h"


/**
 * @test link creation with invalid id
 * @pre invalid id parameter (NO_ID)
 * @post link is not created, returns NULL
*/
void test01_link_create();

/**
 * @test link creation with a valid id 
 * @pre valid id param (Id = 1)
 * @post link is created, returns poninter != NULL
*/
void test02_link_create();

/**
 * @test link creation with correct id assignment 
 * @pre valid id parameter (Id = 1)
 * @post creates link and retrieves the link_id assigned at creation
*/
void test03_link_create();

/**
 * @test set the origin id on a NULL link 
 * @pre link pointer is NULL, Id is not NO_ID
 * @post function returns ERROR
*/
void test01_link_set_origin_id();

/**
 * @test sets the origin id on a valid link to NO_ID
 * @pre valid link, invalid Id (NO_ID)
 * @post fuction returns ERROR
*/
void test02_link_set_origin_id();

/**
 * @test sets a valid id on a valid link
 * @pre valid link, valid id
 * @post function returns OK
*/
void test03_link_set_origin_id();

/**
 * @test sets a valid id on a valid link, checks result 
 * @pre valid id and link, link_get_origin_id function
 * @post function returns link->origin_id, compared with id
*/
void test04_link_set_origin_id();

/**
 * @test set the destination id on a NULL link 
 * @pre link pointer is NULL, Id is not NO_ID
 * @post function returns ERROR
*/
void test01_link_set_destination_id();

/**
 * @test sets the destination id on a valid link to NO_ID
 * @pre valid link, invalid Id (NO_ID)
 * @post fuction returns ERROR
*/
void test02_link_set_destination_id();

/**
 * @test sets a valid id on a valid link
 * @pre valid link, valid id
 * @post function returns OK
*/
void test03_link_set_destination_id();

/**
 * @test sets a valid id on a valid link, checks result 
 * @pre valid id and link, link_get_destination_id function
 * @post function returns link->origin_id, compared with id
*/
void test04_link_set_destination_id();

/**
 * @test sets direction on a NULL link
 * @pre NULL link, valid direction
 * @post function returns ERROR
*/
void test01_link_set_direction();

/**
 * @test test for setting invalid direction
 * @pre valid link, invalid direction
 * @post function returns ERROR
*/
void test02_link_set_direction();

/**
 * @test test for setting valid direction 
 * @pre valid link, valid direction (N)
 * @post function returns OK
*/
void test03_link_set_direction();

/**
 * @test checks correct direction assignment
 * @pre valink link and direction, link_get_direction function
 * @post function returns link->direction, compared with direction
*/
void test04_link_set_direction();

/**
 * @test sets is_open on a NULL link
 * @pre invalid link, valid boolean
 * @post function returns ERROR
*/
void test01_link_set_is_open();

/**
 * @test sets is_open on a valid link
 * @pre valid link
 * @post function returns OK
*/
void test02_link_set_is_open();

/**
 * @test sets and checks is_open on a valid link
 * @pre valid link and link_get_is_open function
 * @post function returns link->is_open = TRUE and compares to is_open
*/
void test03_link_set_is_open();

/**
 * @test sets and checks is_open on a valid link
 * @pre valid link and link_get_is_open function
 * @post function returns link->is_open = FALSE and compares to is_open
*/
void test04_link_set_is_open();

/**
 * @test sets name on a NULL link
 * @pre valid name, invalid link
 * @post function returns ERROR
*/
void test01_link_set_name();

/**
 * @test sets NULL name on a valid link
 * @pre valid link, NULL name
 * @post function returns ERROR
*/
void test02_link_set_name();

/**
 * @test sets valid name on a valid link
 * @pre valid name and link
 * @post function returns OK
*/
void test03_link_set_name();

/**
 * @test sets and compares valid name and link
 * @pre valid name, link and link_get_name function
 * @post function returns link->name and compares it to name 
*/
void test04_link_set_name();

/**
 * @test fetches is_open on NULL link
 * @pre NULL link
 * @post function returns ERROR
*/
void test01_link_get_is_open();

/**
 * @test fetches is_open on a valid link
 * @pre valid link
 * @post function returns is_open, default value in link_create (FALSE)
*/
void test02_link_get_is_open();

/**
 * @test fetches direction on a NULL link
 * @pre invalid link
 * @post function returns UNKNOWN_DIR
*/
void test01_link_get_direction();

/**
 * @test fetches direction on a valid link
 * @pre valid link structure
 * @post function returns default direction
*/
void test02_link_get_direction();

/**
 * @test fetches id from NULL link
 * @pre NULL link
 * @post function returns NO_ID
*/
void test01_link_get_id();

/**
 * @test fetches id from valid link
 * @pre valid link, (valid id)
 * @post function returns id set to link (1)
*/
void test02_link_get_id();

/**
 * @test fetches origin_id from invalid link
 * @pre NULL link
 * @post function returns NO_ID
*/
void test01_link_get_origin_id();

/**
 * @test fetches origin_id from valid link 
 * @pre valid link
 * @post function returns default value, NO_ID
*/
void test02_link_get_origin_id();

/**
 * @test fetches destination_id from NULL link
 * @pre NULL link
 * @post function returns NO_ID
*/
void test01_link_get_destination_id();

/**
 * @test fetches destination_id from valid link
 * @pre valid link
 * @post function returns default value, NO_ID
*/
void test02_link_get_destination_id();

/**
 * @test fetches name form NULL link
 * @pre NULL link
 * @post function returns NULL
*/
void test01_link_get_name();

/**
 * @test fetches name on a valid link
 * @pre valid link
 * @post function returns char *name != NULL
*/
void test02_link_get_name();

#endif