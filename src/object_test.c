/**
 * @brief It tests object module
 *
 * @file object_test.c
 * @author Alvaro Inigo, Guilherme Povedano
 * @version 1.0
 * @date 04-04-2025
 */
#include "object_test.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TESTS 35 /*!<Defines the total ammount of test functions*/

/**
 * @brief in the main function all tests can be executated
 *
 * @param argc
 * @param argv
 * @return int
 */
int main(int argc, char **argv)
{
    int test = 0;
    int all = 1;

    if (argc < 2)
    {
        printf("Running all tests for module Object:\n");
    }
    else
    {
        test = atoi(argv[1]);
        all = 0;
        printf("Running test %d:\n", test);
        if (test < 1 || test > MAX_TESTS)
        {
            printf("Error: unknown test %d\n", test);
            exit(EXIT_SUCCESS);
        }
    }

    if (all || test == 1)
        test1_object_create();
    if (all || test == 2)
        test1_object_destroy();
    if (all || test == 3)
        test1_object_get_id();
    if (all || test == 4)
        test1_object_set_id();
    if (all || test == 5)
        test1_object_get_name();
    if (all || test == 6)
        test1_object_set_name();
    if (all || test == 7)
        test1_object_print();
    if (all || test == 8)
        test1_object_set_description();
    if (all || test == 9)
        test1_object_get_description();
    if (all || test == 10)
        test2_object_create();
    if (all || test == 11)
        test2_object_destroy();
    if (all || test == 12)
        test2_object_get_id();
    if (all || test == 13)
        test2_object_set_id();
    if (all || test == 14)
        test2_object_get_name();
    if (all || test == 15)
        test2_object_set_name();
    if (all || test == 16)
        test2_object_print();
    if (all || test == 17)
        test2_object_set_description();
    if (all || test == 18)
        test2_object_get_description();
    if (all || test == 19)
        test1_object_set_health();
    if (all || test == 20)
        test2_object_set_health();
    if (all || test == 21)
        test1_object_get_health();
    if (all || test == 22)
        test2_object_get_health();
    if (all || test == 23)
        test1_object_set_open();
    if (all || test == 24)
        test2_object_set_open();
    if (all || test == 25)
        test1_object_get_open();
    if (all || test == 26)
        test2_object_get_open();
    if (all || test == 27)
        test1_object_set_dependency();
    if (all || test == 28)
        test2_object_set_dependency();
    if (all || test == 29)
        test1_object_get_dependency();
    if (all || test == 30)
        test2_object_get_dependency();
    if (all || test == 31)
        test1_object_set_movable();
    if (all || test == 32)
        test2_object_set_movable();
    if (all || test == 33)
        test3_object_set_movable();
    if (all || test == 34)
        test1_object_get_movable();
    if (all || test == 35)
        test2_object_get_movable();

    PRINT_PASSED_PERCENTAGE;

    return EXIT_SUCCESS;
}

/* === Tests === */

void test1_object_create()
{
    Object *o = object_create(1);
    PRINT_TEST_RESULT(o != NULL);
    object_destroy(o);
}

void test1_object_destroy()
{
    Object *o = object_create(1);
    PRINT_TEST_RESULT(object_destroy(o) == OK);
}

void test1_object_get_id()
{
    Object *o = object_create(123);
    PRINT_TEST_RESULT(object_get_id(o) == 123);
    object_destroy(o);
}

void test1_object_set_id()
{
    Object *o = object_create(1);
    object_set_id(o, 456);
    PRINT_TEST_RESULT(object_get_id(o) == 456);
    object_destroy(o);
}

void test1_object_get_name()
{
    Object *o = object_create(1);
    object_set_name(o, "Sword");
    PRINT_TEST_RESULT(strcmp(object_get_name(o), "Sword") == 0);
    object_destroy(o);
}

void test1_object_set_name()
{
    Object *o = object_create(1);
    PRINT_TEST_RESULT(object_set_name(o, "Shield") == OK);
    object_destroy(o);
}

void test1_object_print()
{
    Object *o = object_create(1);
    object_set_name(o, "Map");
    PRINT_TEST_RESULT(object_print(o) == OK);
    object_destroy(o);
}

void test1_object_set_description()
{
    Object *o = object_create(1);
    PRINT_TEST_RESULT(object_set_description(o, "A very old scroll.") == OK);
    object_destroy(o);
}

void test1_object_get_description()
{
    Object *o = object_create(1);
    object_set_description(o, "Ancient artifact");
    PRINT_TEST_RESULT(strcmp(object_get_description(o), "Ancient artifact") == 0);
    object_destroy(o);
}

void test2_object_create()
{
    Object *o = object_create(NO_ID);
    PRINT_TEST_RESULT(o == NULL);
}

void test2_object_destroy()
{
    PRINT_TEST_RESULT(object_destroy(NULL) == ERROR);
}

void test2_object_get_id()
{
    PRINT_TEST_RESULT(object_get_id(NULL) == NO_ID);
}

void test2_object_set_id()
{
    PRINT_TEST_RESULT(object_set_id(NULL, 10) == ERROR);
}

void test2_object_get_name()
{
    PRINT_TEST_RESULT(object_get_name(NULL) == NULL);
}

void test2_object_set_name()
{
    Object *o = object_create(1);
    PRINT_TEST_RESULT(object_set_name(o, "") == OK);
    object_destroy(o);
}

void test2_object_print()
{
    PRINT_TEST_RESULT(object_print(NULL) == ERROR);
}

void test2_object_set_description()
{
    Object *o = object_create(1);
    PRINT_TEST_RESULT(object_set_description(o, "") == OK);
    object_destroy(o);
}

void test2_object_get_description()
{
    PRINT_TEST_RESULT(object_get_description(NULL) == NULL);
}

void test1_object_set_health()
{
    Object *o = object_create(1);
    PRINT_TEST_RESULT(object_set_health(o, 100) == OK);
    object_destroy(o);
}

void test2_object_set_health()
{
    PRINT_TEST_RESULT(object_set_health(NULL, 100) == ERROR);
}

void test1_object_get_health()
{
    Object *o = object_create(1);
    object_set_health(o, 75);
    PRINT_TEST_RESULT(object_get_health(o) == 75);
    object_destroy(o);
}

void test2_object_get_health()
{
    PRINT_TEST_RESULT(object_get_health(NULL) == NO_ID);
}

void test1_object_set_open()
{
    Object *o = object_create(1);
    PRINT_TEST_RESULT(object_set_open(o, 42) == OK);
    object_destroy(o);
}

void test2_object_set_open()
{
    PRINT_TEST_RESULT(object_set_open(NULL, 42) == ERROR);
}

void test1_object_get_open()
{
    Object *o = object_create(1);
    object_set_open(o, 99);
    PRINT_TEST_RESULT(object_get_open(o) == 99);
    object_destroy(o);
}

void test2_object_get_open()
{
    PRINT_TEST_RESULT(object_get_open(NULL) == NO_ID);
}

void test1_object_set_dependency()
{
    Object *o = object_create(1);
    PRINT_TEST_RESULT(object_set_dependency(o, 10) == OK);
    object_destroy(o);
}

void test2_object_set_dependency()
{
    PRINT_TEST_RESULT(object_set_dependency(NULL, 10) == ERROR);
}

void test1_object_get_dependency()
{
    Object *o = object_create(1);
    object_set_dependency(o, 20);
    PRINT_TEST_RESULT(object_get_dependency(o) == 20);
    object_destroy(o);
}

void test2_object_get_dependency()
{
    PRINT_TEST_RESULT(object_get_dependency(NULL) == NO_ID);
}

void test1_object_set_movable()
{
    Object *o = object_create(1);
    PRINT_TEST_RESULT(object_set_movable(o, TRUE) == OK);
    object_destroy(o);
}

void test2_object_set_movable()
{
    PRINT_TEST_RESULT(object_set_movable(NULL, TRUE) == ERROR);
}

void test3_object_set_movable()
{
    Object *o = object_create(1);
    PRINT_TEST_RESULT(object_set_movable(o, 3) == ERROR); // Invalid Bool
    object_destroy(o);
}

void test1_object_get_movable()
{
    Object *o = object_create(1);
    object_set_movable(o, TRUE);
    PRINT_TEST_RESULT(object_get_movable(o) == TRUE);
    object_destroy(o);
}

void test2_object_get_movable()
{
    PRINT_TEST_RESULT(object_get_movable(NULL) == NO_ID);
}
