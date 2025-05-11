/**
 * @brief It tests the Player module
 *
 * @file player_test.c
 * @author PPROG - Team 2101_D - AGL
 * @version 1.0.2
 * @date 26-03-2025
 * @copyright GNU Public License
 */

#include "player_test.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TESTS 50 /*!<Defines the total ammount of test functions*/

/**
 * @brief Main function for PLAYER unit tests.
 *
 * You may execute ALL or a SINGLE test
 *   1.- No parameter -> ALL test are executed
 *   2.- A number means a particular test (the one identified by that number)
 *       is executed
 *
 */
int main(int argc, char **argv)
{

    int test = 0;
    int all = 1;

    if (argc < 2)
    {
        printf("Running all test for module Player:\n");
    }
    else
    {
        test = atoi(argv[1]);
        all = 0;
        printf("Running test %d:\t", test);
        if (test < 1 && test > MAX_TESTS)
        {
            printf("Error: unknown test %d\t", test);
            exit(EXIT_SUCCESS);
        }
    }

    if (all || test == 1)
        test1_player_create();
    if (all || test == 2)
        test2_player_create();
    if (all || test == 3)
        test3_player_create();
    if (all || test == 4)
        test1_player_set_id();
    if (all || test == 5)
        test2_player_set_id();
    if (all || test == 6)
        test3_player_set_id();
    if (all || test == 7)
        test1_player_get_id();
    if (all || test == 8)
        test2_player_get_id();
    if (all || test == 9)
        test1_player_get_name();
    if (all || test == 10)
        test2_player_get_name();
    if (all || test == 11)
        test1_player_backpack_is_full();
    if (all || test == 12)
        test2_player_backpack_is_full();
    if (all || test == 13)
        test3_player_backpack_is_full();
    if (all || test == 14)
        test1_player_backpack_is_empty();
    if (all || test == 15)
        test2_player_backpack_is_empty();
    if (all || test == 16)
        test3_player_backpack_is_empty();
    if (all || test == 17)
        test1_player_add_object_to_backpack();
    if (all || test == 18)
        test2_player_add_object_to_backpack();
    if (all || test == 19)
        test3_player_add_object_to_backpack();
    if (all || test == 20)
        test1_player_remove_object_from_backpack();
    if (all || test == 21)
        test2_player_remove_object_from_backpack();
    if (all || test == 22)
        test3_player_remove_object_from_backpack();
    if (all || test == 23)
        test1_player_get_num_objects_in_backpack();
    if (all || test == 24)
        test2_player_get_num_objects_in_backpack();
    if (all || test == 25)
        test1_player_get_backpack_object_id_at();
    if (all || test == 26)
        test2_player_get_backpack_object_id_at();
    if (all || test == 27)
        test3_player_get_backpack_object_id_at();
    if (all || test == 28)
        test1_player_backpack_contains();
    if (all || test == 29)
        test2_player_backpack_contains();
    if (all || test == 30)
        test3_player_backpack_contains();
    if (all || test == 31)
        test1_player_set_location();
    if (all || test == 32)
        test2_player_set_location();
    if (all || test == 33)
        test3_player_set_location();
    if (all || test == 34)
        test1_player_get_location();
    if (all || test == 35)
        test2_player_get_location();
    if (all || test == 36)
        test3_player_get_location();
    if (all || test == 37)
        test1_player_set_health();
    if (all || test == 38)
        test2_player_set_health();
    if (all || test == 39)
        test3_player_set_health();
    if (all || test == 40)
        test1_player_get_health();
    if (all || test == 41)
        test2_player_get_health();
    if (all || test == 42)
        test3_player_get_health();

    if (all || test == 43)
        test1_player_get_inventory();
    if (all || test == 44)
        test2_player_get_inventory();
    if (all || test == 45)
        test1_player_set_max_objs();
    if (all || test == 46)
        test2_player_set_max_objs();
    if (all || test == 47)
        test1_player_get_team();
    if (all || test == 48)
        test2_player_get_team();
    if (all || test == 49)
        test1_player_set_team();
    if (all || test == 50)
        test2_player_set_team();

    PRINT_PASSED_PERCENTAGE;

    return 0;
}



/**Test whether the function returns a valid player for valid input */
void test1_player_create()
{
    Player *player;
    player = player_create(1, 10);
    PRINT_TEST_RESULT(player != NULL);
    if (player != NULL)
    {
        PRINT_TEST_RESULT(player_get_id(player) == 1);
        player_destroy(player);
    }
}

/**Test whether the function returns NULL for invalid input ID  */
void test2_player_create()
{
    Player *player;
    player = player_create(NO_ID, 10);
    PRINT_TEST_RESULT(player == NULL);
}

/**checks if player_create returns NULL when given a valid ID but a negative backpack capacity (-1) */
void test3_player_create()
{
    Player *player;
    player = player_create(1, -1);
    PRINT_TEST_RESULT(player == NULL);
}

/**checks if the function sets the player's ID correctly */
void test1_player_set_id()
{
    Player *player;
    player = player_create(1, 10);
    PRINT_TEST_RESULT(player != NULL);
    if (player != NULL)
    {
        PRINT_TEST_RESULT(player_set_id(player, 2) == OK);
        PRINT_TEST_RESULT(player_get_id(player) == 2);
        player_destroy(player);
    }
}

/** player_set_id handles the case where the player is NULL correctly by returning ERROR */
void test2_player_set_id()
{
    PRINT_TEST_RESULT(player_set_id(NULL, 2) == ERROR);
}

/**checks if the function returns ERROR for an invalid ID (NO_ID) */
void test3_player_set_id()
{
    Player *player;
    player = player_create(1, 10);
    PRINT_TEST_RESULT(player != NULL);
    if (player != NULL)
    {
        PRINT_TEST_RESULT(player_set_id(player, NO_ID) == ERROR);
        player_destroy(player);
    }
}

/**checks if the function returns the correct ID for a valid player. */
void test1_player_get_id()
{
    Player *player;
    player = player_create(1, 10);
    PRINT_TEST_RESULT(player != NULL);
    if (player != NULL)
    {
        PRINT_TEST_RESULT(player_get_id(player) == 1);
        player_destroy(player);
    }
}
/**checks if the function returns NO_ID for a NULL player */
void test2_player_get_id()
{
    PRINT_TEST_RESULT(player_get_id(NULL) == NO_ID);
}

/**checks if the function returns the correct name for a valid player. */
void test1_player_get_name()
{
    Player *player;
    player = player_create(1, 10);
    PRINT_TEST_RESULT(player != NULL);
    if (player != NULL)
    {
        player_set_name(player, "Name");
        PRINT_TEST_RESULT(strcmp(player_get_name(player), "Name") == 0);
        player_destroy(player);
    }
}

/**Test whether the function returns NULL for a NULL player */
void test2_player_get_name()
{
    PRINT_TEST_RESULT(player_get_name(NULL) == NULL);
}

/**checks if the function returns FALSE for a NULL player. */
void test1_player_backpack_is_full()
{
    PRINT_TEST_RESULT(player_backpack_is_full(NULL) == FALSE);
}

/** checks if the function returns TRUE for a player with a full backpack */
void test2_player_backpack_is_full()
{
    Player *player;
    player = player_create(1, 2);
    PRINT_TEST_RESULT(player != NULL);
    if (player != NULL)
    {
        player_add_object_to_backpack(player, 1);
        player_add_object_to_backpack(player, 2);
        PRINT_TEST_RESULT(player_backpack_is_full(player) == TRUE);
        player_destroy(player);
    }
}

/**checks if the function returns FALSE for a player with a non-full backpack. */
void test3_player_backpack_is_full()
{
    Player *player;
    player = player_create(1, 2);
    PRINT_TEST_RESULT(player != NULL);
    if (player != NULL)
    {
        player_add_object_to_backpack(player, 1);
        PRINT_TEST_RESULT(player_backpack_is_full(player) == FALSE);
        player_destroy(player);
    }
}

/**Test whether the function returns TRUE for a NULL player */
void test1_player_backpack_is_empty()
{
    PRINT_TEST_RESULT(player_backpack_is_empty(NULL) == TRUE);
}

/**Test whether the function returns TRUE for a player with an empty backpack */
void test2_player_backpack_is_empty()
{
    Player *player;
    player = player_create(1, 10);
    PRINT_TEST_RESULT(player != NULL);
    if (player != NULL)
    {
        PRINT_TEST_RESULT(player_backpack_is_empty(player) == TRUE);
        player_destroy(player);
    }
}

/**Test whether the function returns FALSE for a player with a non-empty backpack */
void test3_player_backpack_is_empty()
{
    Player *player;
    player = player_create(1, 10);
    PRINT_TEST_RESULT(player != NULL);
    if (player != NULL)
    {
        player_add_object_to_backpack(player, 1);
        PRINT_TEST_RESULT(player_backpack_is_empty(player) == FALSE);
        player_destroy(player);
    }
}

/**Test whether the function returns ERROR for a NULL player */
void test1_player_add_object_to_backpack()
{
    PRINT_TEST_RESULT(player_add_object_to_backpack(NULL, 1) == ERROR);
}

/**Test whether the function returns ERROR for a player with a full backpack */
void test2_player_add_object_to_backpack()
{
    Player *player;
    player = player_create(1, 2);
    PRINT_TEST_RESULT(player != NULL);
    if (player != NULL)
    {
        player_add_object_to_backpack(player, 1);
        player_add_object_to_backpack(player, 2);
        PRINT_TEST_RESULT(player_add_object_to_backpack(player, 3) == ERROR);
        player_destroy(player);
    }
}

/**Test whether the function returns OK for a player with a non-full backpack */
void test3_player_add_object_to_backpack()
{
    Player *player;
    player = player_create(1, 2);
    PRINT_TEST_RESULT(player != NULL);
    if (player != NULL)
    {
        PRINT_TEST_RESULT(player_add_object_to_backpack(player, 1) == OK);
        player_destroy(player);
    }
}

/** Test whether the function returns ERROR for a NULL player */
void test1_player_remove_object_from_backpack()
{
    PRINT_TEST_RESULT(player_remove_object_from_backpack(NULL, 1) == ERROR);
}

/** Test whether the function returns ERROR for a player trying to remove an object not in the backpack */
void test2_player_remove_object_from_backpack()
{
    Player *player;
    player = player_create(1, 10);
    PRINT_TEST_RESULT(player != NULL);
    if (player != NULL)
    {
        PRINT_TEST_RESULT(player_remove_object_from_backpack(player, 1) == ERROR);
        player_destroy(player);
    }
}

/** Test whether the function returns OK for a player successfully removing an object from the backpack */
void test3_player_remove_object_from_backpack()
{
    Player *player;
    player = player_create(1, 10);
    PRINT_TEST_RESULT(player != NULL);
    if (player != NULL)
    {
        player_add_object_to_backpack(player, 1);
        PRINT_TEST_RESULT(player_remove_object_from_backpack(player, 1) == OK);
        player_destroy(player);
    }
}

/**Test whether the function returns -1 for a NULL player */
void test1_player_get_num_objects_in_backpack()
{
    PRINT_TEST_RESULT(player_get_num_objects_in_backpack(NULL) == -1);
}

/**Test whether the function returns the correct number of objects in the player's backpack */
void test2_player_get_num_objects_in_backpack()
{
    Player *player;
    player = player_create(1, 10);
    PRINT_TEST_RESULT(player != NULL);
    if (player != NULL)
    {
        player_add_object_to_backpack(player, 1);
        player_add_object_to_backpack(player, 2);
        PRINT_TEST_RESULT(player_get_num_objects_in_backpack(player) == 2);
        player_destroy(player);
    }
}

/**Test whether the function returns NO_ID for a NULL player.*/
void test1_player_get_backpack_object_id_at()
{
    PRINT_TEST_RESULT(player_get_backpack_object_id_at(NULL, 0) == NO_ID);
}

/**Test whether the function returns NO_ID for an invalid position.*/
void test2_player_get_backpack_object_id_at()
{
    Player *player;
    player = player_create(1, 10);
    PRINT_TEST_RESULT(player != NULL);
    if (player != NULL)
    {
        PRINT_TEST_RESULT(player_get_backpack_object_id_at(player, -1) == NO_ID);
        player_destroy(player);
    }
}

/**Test whether the function returns the correct object ID at the specified position in the player's backpack*/
void test3_player_get_backpack_object_id_at()
{
    Player *player;
    player = player_create(1, 10);
    PRINT_TEST_RESULT(player != NULL);
    if (player != NULL)
    {
        player_add_object_to_backpack(player, 1);
        player_add_object_to_backpack(player, 2);
        PRINT_TEST_RESULT(player_get_backpack_object_id_at(player, 0) == 1);
        PRINT_TEST_RESULT(player_get_backpack_object_id_at(player, 1) == 2);
        player_destroy(player);
    }
}

/**Test whether the function returns FALSE for a NULL player */
void test1_player_backpack_contains()
{
    PRINT_TEST_RESULT(player_backpack_contains(NULL, 1) == FALSE);
}

/**Test whether the function returns FALSE for a player whose backpack does not contain the specified object ID. */
void test2_player_backpack_contains()
{
    Player *player;
    player = player_create(1, 10);
    PRINT_TEST_RESULT(player != NULL);
    if (player != NULL)
    {
        PRINT_TEST_RESULT(player_backpack_contains(player, 1) == FALSE);
        player_destroy(player);
    }
}

/**Test whether the function returns TRUE for a player whose backpack contains the specified object ID */
void test3_player_backpack_contains()
{
    Player *player;
    player = player_create(1, 10);
    PRINT_TEST_RESULT(player != NULL);
    if (player != NULL)
    {
        player_add_object_to_backpack(player, 1);
        PRINT_TEST_RESULT(player_backpack_contains(player, 1) == TRUE);
        player_destroy(player);
    }
}

/**This test checks if the player_set_location function correctly handles a NULL player */
void test1_player_set_location()
{
    PRINT_TEST_RESULT(player_set_location(NULL, 1) == ERROR);
}

/**This test checks if the player_set_location function correctly sets the location for a valid player. */
void test2_player_set_location()
{
    Player *player;
    player = player_create(1, 10);
    PRINT_TEST_RESULT(player != NULL);
    if (player != NULL)
    {
        PRINT_TEST_RESULT(player_set_location(player, 2) == OK);
        player_destroy(player);
    }
}

/** This test checks if the player_set_location function correctly updates the player's location. */
void test3_player_set_location()
{
    Player *player;
    player = player_create(1, 10);
    PRINT_TEST_RESULT(player != NULL);
    if (player != NULL)
    {
        player_set_location(player, 2);
        PRINT_TEST_RESULT(player_get_location(player) == 2);
        player_destroy(player);
    }
}

/** This test checks the case where the player is NULL. */
void test1_player_get_location()
{
    PRINT_TEST_RESULT(player_get_location(NULL) == NO_ID);
}

/**  This test checks a valid player's location */
void test2_player_get_location()
{
    Player *player;
    player = player_create(1, 10);
    PRINT_TEST_RESULT(player != NULL);
    if (player != NULL)
    {
        player_set_location(player, 2);
        PRINT_TEST_RESULT(player_get_location(player) == 2);
        player_destroy(player);
    }
}

/**This test checks the case where the player's location is not set*/
void test3_player_get_location()
{
    Player *player;
    player = player_create(1, 10);
    PRINT_TEST_RESULT(player != NULL);
    if (player != NULL)
    {
        PRINT_TEST_RESULT(player_get_location(player) == NO_ID);
        player_destroy(player);
    }
}

/*** This test checks the case where the player is NULL */
void test1_player_set_health()
{
    PRINT_TEST_RESULT(player_set_health(NULL, 10) == ERROR);
}

/*** This test sets the health for a valid player */
void test2_player_set_health()
{
    Player *player;
    player = player_create(1, 10);
    PRINT_TEST_RESULT(player != NULL);
    if (player != NULL)
    {
        PRINT_TEST_RESULT(player_set_health(player, 10) == OK);
        player_destroy(player);
    }
}

/** This test checks if the player_set_health function correctly updates the player's health */
void test3_player_set_health()
{
    Player *player;
    player = player_create(1, 10);
    PRINT_TEST_RESULT(player != NULL);
    if (player != NULL)
    {
        player_set_health(player, 10);
        PRINT_TEST_RESULT(player_get_health(player) == 10);
        player_destroy(player);
    }
}

/** This test checks the case where the player is NULL */
void test1_player_get_health()
{
    PRINT_TEST_RESULT(player_get_health(NULL) == NO_HP);
}

/** This test checks if the player_get_health function correctly returns the health for a valid player*/
void test2_player_get_health()
{
    Player *player;
    player = player_create(1, 10);
    PRINT_TEST_RESULT(player != NULL);
    if (player != NULL)
    {
        player_set_health(player, 10);
        PRINT_TEST_RESULT(player_get_health(player) == 10);
        player_destroy(player);
    }
}

/**This test checks if the player_get_health function correctly returns the default health for a newly created player*/
void test3_player_get_health()
{
    Player *player;
    player = player_create(1, 10);
    PRINT_TEST_RESULT(player != NULL);
    if (player != NULL)
    {
        PRINT_TEST_RESULT(player_get_health(player) == 5); /*Assuming default health is 5*/
        player_destroy(player);
    }
}

/**This test checks if the player_get_inventory functions correctly when there is no player passed */
void test1_player_get_inventory(){
    Player *player = NULL;
    PRINT_TEST_RESULT(player_get_inventory(player) == NULL);
}

/**tests if player get inventory works fine when returning the inventory */
void test2_player_get_inventory(){
    Player *player = NULL;
    player = player_create(1,1);
    player_add_object_to_backpack(player, 5);
    PRINT_TEST_RESULT(inventory_contains(player_get_inventory(player), 5) == TRUE);
    player_destroy(player);
}

/**this test checks if it works when NULL pointer is passed */
void test1_player_set_max_objs(){
    Player *player = NULL;
    PRINT_TEST_RESULT(player_set_max_objs(player, 2) == ERROR);
}

/**this test checks if the function actually sets the max ammount of objects */
void test2_player_set_max_objs(){
    Player *player = NULL;
    player = player_create(1,1);
    player_set_max_objs(player, 3);
    PRINT_TEST_RESULT(inventory_get_max_objs(player_get_inventory(player)) == 3);
    player_destroy(player);

}

/**Test whether the function returns NO_ID for a NULL player */
void test1_player_get_team() {
    Player *player = NULL;
    PRINT_TEST_RESULT(player_get_team(player) == NO_ID);
}

/**Test whether the function returns the correct team ID for a valid player */
void test2_player_get_team() {
    Player *player = NULL;
    player = player_create(1, 3); /*Create a player with ID 1 and inventory size 3*/
    PRINT_TEST_RESULT(player != NULL);
    if (player != NULL) {
    player_set_team(player, 5); 
    PRINT_TEST_RESULT(player_get_team(player) == 5);
    player_destroy(player);
    }
}


/**Test whether the function returns ERROR for a NULL player */
void test1_player_set_team() {
    Player *player = NULL;
    PRINT_TEST_RESULT(player_set_team(player, 5) == ERROR); 
}

/**Test whether the function sets the team ID correctly for a valid player */
void test2_player_set_team() {
    Player *player = player_create(1, 3); /* Create a player with ID 1 and inventory size 3 */
    PRINT_TEST_RESULT(player != NULL);
    if (player != NULL) {
        PRINT_TEST_RESULT(player_set_team(player, 5) == OK);
        PRINT_TEST_RESULT(player_get_team(player) == 5);
        player_destroy(player);
    }
}



