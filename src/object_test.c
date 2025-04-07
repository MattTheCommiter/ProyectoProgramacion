/**
 * @brief It tests object module
 *
 * @file object_test.c
 * @author TuNombre
 * @version 1.0
 * @date 04-04-2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "test.h"
#include "object_test.h"
#include "object.h"

#define MAX_TESTS 18 /*!<Defines the total ammount of test functions*/

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
