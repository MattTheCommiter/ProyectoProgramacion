/**
 * @brief It tests character module
 *
 * @file character_test.c
 * @author Alvaro Inigo
 * @version 0.0
 * @date 17-03-2025
 */
#include "character_test.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TESTS 48 /*!< Maximum number of tests */

/**
 * @brief Main function for SPACE unit tests.
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
        printf("Running all test for module Character:\n");
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
        test01_character_create();
    if (all || test == 2)
        test01_character_destroy();
    if (all || test == 3)
        test01_character_set_id();
    if (all || test == 4)
        test01_character_set_name();
    if (all || test == 5)
        test01_character_set_gdesc();
    if (all || test == 6)
        test01_character_set_health();
    if (all || test == 7)
        test01_character_set_friendly();
    if (all || test == 8)
        test01_character_add_message();
    if (all || test == 9)
        test01_character_get_id();
    if (all || test == 10)
        test01_character_get_name();
    if (all || test == 11)
        test01_character_get_gdesc();
    if (all || test == 12)
        test01_character_get_health();
    if (all || test == 13)
        test01_character_get_friendly();
    if (all || test == 14)
        test01_character_get_message_in_pos();
    if (all || test == 15)
        test01_character_print();

    if (all || test == 16)
        test02_character_create();
    if (all || test == 17)
        test02_character_destroy();
    if (all || test == 18)
        test02_character_set_id();
    if (all || test == 19)
        test02_character_set_name();
    if (all || test == 20)
        test02_character_set_gdesc();
    if (all || test == 21)
        test02_character_set_health();
    if (all || test == 22)
        test02_character_set_friendly();
    if (all || test == 23)
        test02_character_add_message();
    if (all || test == 24)
        test02_character_get_id();
    if (all || test == 25)
        test02_character_get_name();
    if (all || test == 26)
        test02_character_get_gdesc();
    if (all || test == 27)
        test02_character_get_health();
    if (all || test == 28)
        test02_character_get_friendly();
    if (all || test == 29)
        test02_character_get_message_in_pos();
    if (all || test == 30)
        test02_character_print();
    if (all || test == 31)
        test01_character_set_following();
    if (all || test == 32)
        test02_character_set_following();
    if (all || test == 33)
        test01_character_get_following();
    if (all || test == 34)
        test02_character_get_following();
    if (all || test == 35)
        test01_character_set_location();
    if (all || test == 36)
        test02_character_set_location();
    if (all || test == 37)
        test01_character_get_location();
    if (all || test == 38)
        test02_character_get_location();
    if (all || test == 39)
        test01_character_set_dead_gdesc();
    if (all || test == 40)
        test02_character_set_dead_gdesc();
    if (all || test == 41)
        test01_character_get_dead_gdesc();
    if (all || test == 42)
        test02_character_get_dead_gdesc();
    if (all || test == 43)
        test02_character_get_n_messages();
    if (all || test == 44)
        test02_character_get_n_messages();
    if (all || test == 45)
        test01_character_get_message_turn();
    if (all || test == 46)
        test02_character_get_message_turn();
    if (all || test == 47)
        test01_character_chat();
    if (all || test == 48)
        test02_character_chat();

    PRINT_PASSED_PERCENTAGE;

    return EXIT_SUCCESS;
}

void test01_character_create()
{
    Character *c = character_create(1);
    PRINT_TEST_RESULT(c != NULL);
    character_destroy(c);
}

void test01_character_destroy()
{
    Character *c = character_create(1);
    PRINT_TEST_RESULT(character_destroy(c) == OK);
}

void test01_character_set_id()
{
    Character *c = character_create(1);
    PRINT_TEST_RESULT(character_set_id(c, 2) == OK && character_get_id(c) == 2);
    character_destroy(c);
}

void test01_character_set_name()
{
    Character *c = character_create(1);
    PRINT_TEST_RESULT(character_set_name(c, "Hero") == OK && strcmp(character_get_name(c), "Hero") == 0);
    character_destroy(c);
}

void test01_character_set_gdesc()
{
    Character *c = character_create(1);
    PRINT_TEST_RESULT(character_set_gdesc(c, "@") == OK && strcmp(character_get_gdesc(c), "@") == 0);
    character_destroy(c);
}

void test01_character_set_dead_gdesc()
{
    Character *c = character_create(1);
    PRINT_TEST_RESULT(character_set_dead_gdesc(c, "@") == OK && strcmp(character_get_dead_gdesc(c), "@") == 0);
    character_destroy(c);
}

void test01_character_set_health()
{
    Character *c = character_create(1);
    PRINT_TEST_RESULT(character_set_health(c, 100) == OK && character_get_health(c) == 100);
    character_destroy(c);
}

void test01_character_set_friendly()
{
    Character *c = character_create(1);
    PRINT_TEST_RESULT(character_set_friendly(c, TRUE) == OK && character_get_friendly(c) == TRUE);
    character_destroy(c);
}

void test01_character_add_message()
{
    Character *c = character_create(1);
    PRINT_TEST_RESULT(character_add_message(c, "Hello") == OK);
    character_destroy(c);
}

void test01_character_get_id()
{
    Character *c = character_create(5);
    PRINT_TEST_RESULT(character_get_id(c) == 5);
    character_destroy(c);
}

void test01_character_get_name()
{
    Character *c = character_create(1);
    character_set_name(c, "Alice");
    PRINT_TEST_RESULT(strcmp(character_get_name(c), "Alice") == 0);
    character_destroy(c);
}

void test01_character_get_gdesc()
{
    Character *c = character_create(1);
    character_set_gdesc(c, "*");
    PRINT_TEST_RESULT(strcmp(character_get_gdesc(c), "*") == 0);
    character_destroy(c);
}

void test01_character_get_dead_gdesc()
{
    Character *c = character_create(1);
    character_set_dead_gdesc(c, "*");
    PRINT_TEST_RESULT(strcmp(character_get_dead_gdesc(c), "*") == 0);
    character_destroy(c);
}

void test01_character_get_health()
{
    Character *c = character_create(1);
    character_set_health(c, 50);
    PRINT_TEST_RESULT(character_get_health(c) == 50);
    character_destroy(c);
}

void test01_character_get_friendly()
{
    Character *c = character_create(1);
    character_set_friendly(c, TRUE);
    PRINT_TEST_RESULT(character_get_friendly(c) == TRUE);
    character_destroy(c);
}

void test01_character_get_message_in_pos()
{
    Character *c = character_create(1);
    character_add_message(c, "Attack!");
    character_add_message(c, "Hello!");
    PRINT_TEST_RESULT(strcmp(character_get_message_in_pos(c, 1), "Hello!") == 0);
    character_destroy(c);
}

void test01_character_print()
{
    Character *c = character_create(1);
    PRINT_TEST_RESULT(character_print(c) == OK);
    character_destroy(c);
}

void test02_character_create()
{
    Character *c = character_create(1);
    PRINT_TEST_RESULT(character_get_id(c) == 1);
    character_destroy(c);
}

void test02_character_destroy()
{
    Character *c = NULL;
    PRINT_TEST_RESULT(character_destroy(c) == ERROR);
}

void test02_character_set_id()
{
    Character *c = NULL;
    PRINT_TEST_RESULT(character_set_id(c, 2) == ERROR);
}

void test02_character_set_name()
{
    Character *c = NULL;
    PRINT_TEST_RESULT(character_set_name(c, "Hero") == ERROR);
}

void test02_character_set_gdesc()
{
    Character *c = NULL;
    PRINT_TEST_RESULT(character_set_gdesc(c, "@") == ERROR);
}

void test02_character_set_dead_gdesc()
{
    Character *c = NULL;
    PRINT_TEST_RESULT(character_set_dead_gdesc(c, "@") == ERROR);
}

void test02_character_set_health()
{
    Character *c = NULL;
    PRINT_TEST_RESULT(character_set_health(c, 100) == ERROR);
}

void test02_character_set_friendly()
{
    Character *c = NULL;
    PRINT_TEST_RESULT(character_set_friendly(c, TRUE) == ERROR);
}

void test02_character_add_message()
{
    Character *c = NULL;
    PRINT_TEST_RESULT(character_add_message(c, "Hello") == ERROR);
}

void test02_character_get_id()
{
    Character *c = NULL;
    PRINT_TEST_RESULT(character_get_id(c) == NO_ID);
}

void test02_character_get_name()
{
    Character *c = NULL;
    PRINT_TEST_RESULT(character_get_name(c) == NULL);
}

void test02_character_get_gdesc()
{
    Character *c = NULL;
    PRINT_TEST_RESULT(character_get_gdesc(c) == NULL);
}

void test02_character_get_dead_gdesc()
{
    Character *c = NULL;
    PRINT_TEST_RESULT(character_get_dead_gdesc(c) == NULL);
}

void test02_character_get_health()
{
    Character *c = NULL;
    PRINT_TEST_RESULT(character_get_health(c) == NO_HP);
}

void test02_character_get_friendly()
{
    Character *c = NULL;
    PRINT_TEST_RESULT(character_get_friendly(c) == FALSE);
}

void test02_character_get_message_in_pos()
{
    Character *c = NULL;
    PRINT_TEST_RESULT(character_get_message_in_pos(c, 0) == NULL);
}

void test02_character_print()
{
    Character *c = NULL;
    PRINT_TEST_RESULT(character_print(c) == ERROR);
}

void test01_character_set_following()
{
    Character *c = NULL;
    PRINT_TEST_RESULT(character_set_following(c, 3) == ERROR);
}

void test02_character_set_following()
{
    Character *c = NULL;
    c = character_create(10);
    PRINT_TEST_RESULT(character_set_following(c, 3) == OK);
    character_destroy(c);
}

void test01_character_get_following()
{
    Character *c = NULL;
    PRINT_TEST_RESULT(character_get_following(c) == NO_ID);
}

void test02_character_get_following()
{
    Character *c = NULL;
    c = character_create(10);
    character_set_following(c, 5);
    PRINT_TEST_RESULT(character_get_following(c) == 5);
    character_destroy(c);
}

void test01_character_set_location()
{
    Character *c = NULL;
    PRINT_TEST_RESULT(character_set_location(c, 3) == ERROR);
}

void test02_character_set_location()
{
    Character *c = NULL;
    c = character_create(10);
    PRINT_TEST_RESULT(character_set_location(c, 3) == OK);
    character_destroy(c);
}

void test01_character_get_location()
{
    Character *c = NULL;
    PRINT_TEST_RESULT(character_get_location(c) == NO_ID);
}

void test02_character_get_location()
{
    Character *c = NULL;
    c = character_create(10);
    character_set_location(c, 5);
    PRINT_TEST_RESULT(character_get_location(c) == 5);
    character_destroy(c);
}

void test01_character_get_n_messages()
{
    Character *character = NULL;
    PRINT_TEST_RESULT(character_get_n_messages(character) == -1);
}

void test02_character_get_n_messages()
{
    Character *character = NULL;
    character = character_create(10);
    character_add_message(character, "hola");
    character_add_message(character, "hello");
    PRINT_TEST_RESULT(character_get_n_messages(character) == 2);
    character_destroy(character);
}

void test01_character_get_message_turn()
{
    Character *character = NULL;
    PRINT_TEST_RESULT(character_get_message_turn(character) == -1);
}

void test02_character_get_message_turn()
{
    Character *character = NULL;
    character = character_create(10);
    PRINT_TEST_RESULT(character_get_message_turn(character) == 0);
    character_destroy(character);
}

void test01_character_chat()
{
    Character *character = NULL;
    PRINT_TEST_RESULT(character_chat(character) == NULL);
}


void test02_character_chat()
{
    Character *character = NULL;
    character = character_create(10);
    character_add_message(character, "hola");
    character_add_message(character, "hello");
    PRINT_TEST_RESULT(strcmp(character_chat(character), "hola") == 0 && strcmp(character_chat(character), "hello") == 0 && strcmp(character_chat(character), "hola") == 0);
    character_destroy(character);
}
