/** 
 * @brief  test functions  for the Player module
 * 
 * @file player_test.h
 * @author PPROG - Team 2101_D - AGL
 * @version 1.0.2
 * @date 22-03-2025
 * @copyright GNU Public License
 */

 #ifndef PLAYER_TEST_H
 #define PLAYER_TEST_H
 
#include "inventory.h"
#include "test.h"
#include "player.h"
 
  /**
 * @test Test whether the function returns a valid player for valid input
 * @pre A valid ID and a positive backpack capacity
 * @post A non-null pointer to a player with the specified ID and backpack capacity
 */
void test1_player_create();

/**
 * @test Test whether the function returns NULL for invalid input 
 * @pre A negative ID and a positive backpack capacity
 * @post A null pointer
 */
void test2_player_create();

/**
 * @test Test whether the function returns NULL for invalid input (negative backpack capacity)
 * @pre A valid ID and a negative backpack capacity
 * @post A null pointer
 */
void test3_player_create();

/**
 * @test Test whether the function sets the ID of the player correctly
 * @pre A valid player and a valid ID
 * @post The player's ID is set to the given value
 */
void test1_player_set_id();

/**
 * @test Test whether the function returns ERROR for invalid player
 * @pre A NULL player and a valid ID
 * @post The function returns ERROR
 */
void test2_player_set_id();

/**
 * @test Test whether the function returns ERROR for invalid ID
 * @pre A valid player and an invalid ID (NO_ID)
 * @post The function returns ERROR
 */
void test3_player_set_id();

/**
 * @test Test whether the function returns the correct ID for a valid player
 * @pre A valid player with a specific ID
 * @post The function returns the correct ID
 */
void test1_player_get_id();

/**
 * @test Test whether the function returns NO_ID for a NULL player
 * @pre A NULL player
 * @post The function returns NO_ID
 */
void test2_player_get_id();

/**
 * @test Test whether the function returns the correct name for a valid player
 * @pre A valid player with a specific name
 * @post The function returns the correct name
 */
void test1_player_get_name();

/**
 * @test Test whether the function returns NULL for a NULL player
 * @pre A NULL player
 * @post The function returns NULL
 */
void test2_player_get_name();

/**
 * @test Test whether the function returns FALSE for a NULL player
 * @pre A NULL player
 * @post The function returns FALSE
 */
void test1_player_backpack_is_full();

/**
 * @test Test whether the function returns TRUE for a player with a full backpack
 * @pre A valid player with a full backpack
 * @post The function returns TRUE
 */
void test2_player_backpack_is_full();

/**
 * @test Test whether the function returns FALSE for a player with a non-full backpack
 * @pre A valid player with a non-full backpack
 * @post The function returns FALSE
 */
void test3_player_backpack_is_full();

/**
 * @test Test whether the function returns TRUE for a NULL player
 * @pre A NULL player
 * @post The function returns TRUE
 */
void test1_player_backpack_is_empty();

/**
 * @test Test whether the function returns TRUE for a player with an empty backpack
 * @pre A player with an empty backpack
 * @post The function returns TRUE
 */
void test2_player_backpack_is_empty();

/**
 * @test Test whether the function returns FALSE for a player with a non-empty backpack
 * @pre A player with a non-empty backpack
 * @post The function returns FALSE
 */
void test3_player_backpack_is_empty();
 
/**
 * @test Test whether the function returns ERROR for a NULL player
 * @pre A NULL player
 * @post The function returns ERROR
 */
void test1_player_add_object_to_backpack();

/**
 * @test Test whether the function returns ERROR for a player with a full backpack
 * @pre A player with a full backpack
 * @post The function returns ERROR
 */
void test2_player_add_object_to_backpack();

/**
 * @test Test whether the function returns OK for a player with a non-full backpack
 * @pre A player with a non-full backpack
 * @post The function returns OK
 */
void test3_player_add_object_to_backpack();

/**
 * @test Test whether the function returns ERROR for a NULL player.
 * @pre The player pointer is NULL.
 * @post The function returns ERROR.
 */
void test1_player_remove_object_from_backpack();

/**
* @test Test whether the function returns ERROR for a player trying to remove an object not in the backpack.
* @pre The player is created with a valid ID and backpack capacity, but the backpack does not contain the object.
* @post The function returns ERROR.
*/
void test2_player_remove_object_from_backpack();

/**
* @test Test whether the function returns OK for a player successfully removing an object from the backpack.
* @pre The player is created with a valid ID and backpack capacity, and the object is added to the backpack.
* @post The function returns OK.
*/
void test3_player_remove_object_from_backpack();

/**
 * @test Test whether the function returns -1 for a NULL player.
 * @pre The player pointer is NULL.
 * @post The function returns -1.
 */
void test1_player_get_num_objects_in_backpack();

/**
 * @test Test whether the function returns the correct number of objects in the player's backpack.
 * @pre The player is created with a valid ID and backpack capacity, and objects are added to the backpack.
 * @post The function returns the correct number of objects in the backpack.
 */
void test2_player_get_num_objects_in_backpack();

/**
 * @test Test whether the function returns NO_ID for a NULL player.
 * @pre The player pointer is NULL.
 * @post The function returns NO_ID.
 */
void test1_player_get_backpack_object_id_at();

/**
 * @test Test whether the function returns NO_ID for an invalid position.
 * @pre The player is created with a valid ID and backpack capacity, but the position is invalid (negative or greater than the number of objects).
 * @post The function returns NO_ID.
 */
void test2_player_get_backpack_object_id_at();

/**
 * @test Test whether the function returns the correct object ID at the specified position in the player's backpack.
 * @pre The player is created with a valid ID and backpack capacity, and objects are added to the backpack.
 * @post The function returns the correct object ID at the specified position.
 */
void test3_player_get_backpack_object_id_at();

/**
 * @test Test whether the function returns FALSE for a NULL player.
 * @pre The player pointer is NULL.
 * @post The function returns FALSE.
 */
void test1_player_backpack_contains();

/**
 * @test Test whether the function returns FALSE for a player whose backpack does not contain the specified object ID.
 * @pre The player is created with a valid ID and backpack capacity, but the specified object ID is not added to the backpack.
 * @post The function returns FALSE.
 */
void test2_player_backpack_contains();

/**
 * @test Test whether the function returns TRUE for a player whose backpack contains the specified object ID.
 * @pre The player is created with a valid ID and backpack capacity, and the specified object ID is added to the backpack.
 * @post The function returns TRUE.
 */
void test3_player_backpack_contains();


/**
 * @test Test whether the function returns ERROR for a NULL player
 * @pre A NULL player
 * @post The function returns ERROR
 */
void test1_player_set_location();

/**
 * @test Test whether the function returns OK for a valid player and location
 * @pre A valid player and a valid location ID
 * @post The function returns OK
 */
void test2_player_set_location();

/**
 * @test Test whether the function correctly sets the location of the player
 * @pre A valid player and a valid location ID
 * @post The player's location is set to the specified ID
 */
void test3_player_set_location();

/**
 * @test Test whether the function returns NO_ID for a NULL player
 * @pre A NULL player
 * @post The function returns NO_ID
 */
void test1_player_get_location();

/**
 * @test Test whether the function returns the correct location for a valid player
 * @pre A valid player with a set location
 * @post The function returns the correct location ID
 */
void test2_player_get_location();

/**
 * @test Test whether the function returns NO_ID for a player with no set location
 * @pre A valid player with no set location
 * @post The function returns NO_ID
 */
void test3_player_get_location();

/**
 * @test Test whether the function returns ERROR for a NULL player
 * @pre A NULL player
 * @post The function returns ERROR
 */
void test1_player_set_health();

/**
 * @test Test whether the function returns OK for a valid player and health value
 * @pre A valid player and a valid health value
 * @post The function returns OK
 */
void test2_player_set_health();

/**
 * @test Test whether the function correctly sets the health of the player
 * @pre A valid player and a valid health value
 * @post The player's health is set to the specified value
 */
void test3_player_set_health();

/**
 * @test Test whether the function returns NO_HP for a NULL player
 * @pre A NULL player
 * @post The function returns NO_HP
 */
void test1_player_get_health();

/**
 * @test Test whether the function returns the correct health for a valid player
 * @pre A valid player with a set health value
 * @post The function returns the correct health value
 */
void test2_player_get_health();

/**
 * @test Test whether the function returns the default health for a newly created player
 * @pre A newly created player
 * @post The function returns the default health value
 */
void test3_player_get_health();



/**
 * @brief inventory of a NULL pointer to player
 * @pre NULL pointer
 * @post NULL
 */
void test1_player_get_inventory();

/**
 * @brief gets right the inventory, the same object belongs to it
 * @pre player with a specific object
 * @post the object belongs to its inventory
 */
void test2_player_get_inventory();


/**
 * @brief set max objects in the inventory of a NULL pointer
 * @pre a NULL pointer
 * @post ERROR
 */
void test1_player_set_max_objs();


/**
 * @brief sets a number as maximun objects
 * @pre pointer to a player with 3 elements
 * @post TRUE
 */
void test2_player_set_max_objs();




 
 #endif
 