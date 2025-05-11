/**
 * @brief It tests space module
 *
 * @file space_test.c
 * @author Matteo Artunedo, Guilherme Povedano
 * @version 0.0
 * @date 17-02-2025
 * @copyright GNU Public License
 */
#include "space_test.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TESTS 51 /*!<Total number of test functions*/
#define SPACE_NAME "espacio" /*!<Name that will be given to the spaces created for the tests*/
#define SPACE_ID 5 /*!<Id that will be given to the spaces created for the tests*/
#define OBJECT_ID 3 /*!<Id that will be given to the objects created for the tests*/
#define CHARACTER_ID 4 /*!<Id that will be given to the objects created for the tests*/
#define NO_ELEMENTS 0 /*!<Number of elements of an empty set/array*/
#define ONE_ELEMENT 1 /*!<Size of a one-element set or array*/
#define INVALID_VALUE -1 /*!<Value used to test correct handling of incorrect arguments for certain functions*/

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
    printf("Running all test for module Space:\n");
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
    test1_space_create();
  if (all || test == 2)
    test2_space_create();
  if (all || test == 3)
    test1_space_set_name();
  if (all || test == 4)
    test2_space_set_name();
  if (all || test == 5)
    test3_space_set_name();
  if (all || test == 6)
    test1_space_get_id();
  if (all || test == 7)
    test2_space_get_id();
  if (all || test == 8)
    test1_space_get_name();
  if (all || test == 9)
    test2_space_get_name();
  if (all || test == 10)
    test1_space_add_objectId();
  if (all || test == 11)
    test2_space_add_objectId();
  if (all || test == 12)
    test3_space_add_objectId();
  if (all || test == 13)
    test1_space_object_belongs();
  if (all || test == 14)
    test2_space_object_belongs();
  if (all || test == 15)
    test3_space_object_belongs();
  if (all || test == 16)
    test4_space_object_belongs();
  if (all || test == 17)
    test5_space_object_belongs();
  if (all || test == 18)
    test1_space_has_no_objects();
  if (all || test == 19)
    test2_space_has_no_objects();
  if (all || test == 20)
    test3_space_has_no_objects();
  if (all || test == 21)
    test1_space_get_num_of_objects();
  if (all || test == 22)
    test2_space_get_num_of_objects();
  if (all || test == 23)
    test3_space_get_num_of_objects();
  if (all || test == 24)
    test1_space_get_character_in_pos();
  if (all || test == 25)
    test2_space_get_character_in_pos();
  if (all || test == 26)
    test3_space_get_character_in_pos();
  if (all || test == 27)
    test4_space_get_character_in_pos();
  if (all || test == 27)
    test1_space_add_character();
  if (all || test == 28)
    test2_space_add_character();
  if (all || test == 29)
    test3_space_add_character();
  if (all || test == 30)
    test4_space_add_character();
  if (all || test == 31)
    test1_space_delete_character();
  if (all || test == 32)
    test2_space_delete_character();
  if (all || test == 33)
    test3_space_delete_character();
  if (all || test == 34)
    test4_space_delete_character();
  if (all || test == 35)
    test1_space_set_of_objects_is_full();
  if (all || test == 36)
    test2_space_set_of_objects_is_full();
  if (all || test == 37)
    test3_space_set_of_objects_is_full();
  if (all || test == 38)
    test4_space_set_of_objects_is_full();
  if (all || test == 39)
    test1_space_delete_object();
  if (all || test == 40)
    test2_space_delete_object();
  if (all || test == 41)
    test3_space_delete_object();
  if (all || test == 42)
    test4_space_delete_object();
  if (all || test == 43)
    test5_space_delete_object();
  if (all || test == 44)
    test1_space_set_discovered();
  if (all || test == 45)
    test2_space_set_discovered();
  if (all || test == 46)
    test3_space_set_discovered();
  if (all || test == 47)
    test1_space_get_discovered();
  if (all || test == 48)
    test2_space_get_discovered();
  if (all || test == 49)
    test1_space_get_n_characters();
  if (all || test == 50)
    test2_space_get_n_characters();
  if (all || test == 51)
    test3_space_get_n_characters();

  PRINT_PASSED_PERCENTAGE;

  return EXIT_SUCCESS;
}

void test1_space_create()
{
  int result;
  Space *s;
  s = space_create(SPACE_ID);
  result = (s != NULL);
  PRINT_TEST_RESULT(result);
  space_destroy(s);
}

void test2_space_create()
{
  Space *s;
  s = space_create(SPACE_ID);
  PRINT_TEST_RESULT(space_get_id(s) == SPACE_ID);
  space_destroy(s);
}

void test1_space_set_name()
{
  Space *s;
  s = space_create(SPACE_ID);
  PRINT_TEST_RESULT(space_set_name(s, SPACE_NAME) == OK);
  space_destroy(s);
}

void test2_space_set_name()
{
  Space *s = NULL;
  PRINT_TEST_RESULT(space_set_name(s, SPACE_NAME) == ERROR);
}

void test3_space_set_name()
{
  Space *s;
  s = space_create(SPACE_ID);
  PRINT_TEST_RESULT(space_set_name(s, NULL) == ERROR);
  space_destroy(s);
}

void test1_space_add_objectId()
{
  Space *s;
  s = space_create(SPACE_ID);
  PRINT_TEST_RESULT(space_add_objectId(s, OBJECT_ID) == OK);
  space_destroy(s);
}

void test2_space_add_objectId()
{
  Space *s = NULL;
  PRINT_TEST_RESULT(space_add_objectId(s, OBJECT_ID) == ERROR);
}

void test3_space_add_objectId()
{
  Space *s = NULL;
  s = space_create(SPACE_ID);
  PRINT_TEST_RESULT(space_add_objectId(s, NO_ID) == ERROR);
  space_destroy(s);
}

void test1_space_get_name()
{
  Space *s=NULL;
  s = space_create(SPACE_ID);
  space_set_name(s, SPACE_NAME);
  PRINT_TEST_RESULT(strcmp(space_get_name(s), SPACE_NAME) == 0);
  space_destroy(s);
}

void test2_space_get_name()
{
  Space *s = NULL;
  PRINT_TEST_RESULT(space_get_name(s) == NULL);
}

void test1_space_get_id()
{
  Space *s;
  s = space_create(SPACE_ID);
  PRINT_TEST_RESULT(space_get_id(s) == SPACE_ID);
  space_destroy(s);
}

void test2_space_get_id()
{
  Space *s = NULL;
  PRINT_TEST_RESULT(space_get_id(s) == NO_ID);
}

void test1_space_object_belongs()
{
  Space *s = NULL;
  PRINT_TEST_RESULT(space_object_belongs(s, OBJECT_ID) == FALSE);
  space_destroy(s);
}

void test2_space_object_belongs()
{
  Space *s = NULL;
  s = space_create(SPACE_ID);
  space_add_objectId(s, OBJECT_ID);
  PRINT_TEST_RESULT(space_object_belongs(s, SPACE_ID) == FALSE);
  space_destroy(s);
}

void test3_space_object_belongs()
{
  Space *s = NULL;
  s = space_create(SPACE_ID);
  PRINT_TEST_RESULT(space_object_belongs(s, OBJECT_ID) == FALSE);
  space_destroy(s);
}

void test4_space_object_belongs()
{
  Space *s = NULL;
  s = space_create(SPACE_ID);
  space_add_objectId(s, OBJECT_ID);
  PRINT_TEST_RESULT(space_object_belongs(s, NO_ID) == FALSE);
  space_destroy(s);
}

void test5_space_object_belongs()
{
  Space *s = NULL;
  s = space_create(SPACE_ID);
  space_add_objectId(s, OBJECT_ID);
  PRINT_TEST_RESULT(space_object_belongs(s, OBJECT_ID) == TRUE);
  space_destroy(s);
}

void test1_space_has_no_objects()
{
  Space *s = NULL;
  PRINT_TEST_RESULT(space_has_no_objects(s) == TRUE);
  space_destroy(s);
}

void test2_space_has_no_objects()
{
  Space *s = NULL;
  s = space_create(SPACE_ID);
  PRINT_TEST_RESULT(space_has_no_objects(s) == TRUE);
  space_destroy(s);
}

void test3_space_has_no_objects()
{
  Space *s = NULL;
  s = space_create(SPACE_ID);
  space_add_objectId(s, OBJECT_ID);
  PRINT_TEST_RESULT(space_has_no_objects(s) == FALSE);
  space_destroy(s);
}

void test1_space_get_num_of_objects()
{
  Space *s = NULL;
  PRINT_TEST_RESULT(space_get_num_of_objects(s) == INVALID_VALUE);
  space_destroy(s);
}

void test2_space_get_num_of_objects()
{
  Space *s = NULL;
  s = space_create(SPACE_ID);
  PRINT_TEST_RESULT(space_get_num_of_objects(s) == NO_ELEMENTS);
  space_destroy(s);
}

void test3_space_get_num_of_objects()
{
  Space *s = NULL;
  s = space_create(SPACE_ID);
  space_add_objectId(s, OBJECT_ID);
  PRINT_TEST_RESULT(space_get_num_of_objects(s) == ONE_ELEMENT);
  space_destroy(s);
}

void test1_space_get_character_in_pos()
{
  Space *s = NULL;
  PRINT_TEST_RESULT(space_get_character_in_pos(s, OBJECT_ID) == NO_ID);
}

void test2_space_get_character_in_pos()
{
  Space *s = NULL;
  s = space_create(SPACE_ID);
  space_add_character(s, CHARACTER_ID);
  PRINT_TEST_RESULT(space_get_character_in_pos(s, 0) == CHARACTER_ID);
  space_destroy(s);
}

void test3_space_get_character_in_pos()
{
  Space *s = NULL;
  s = space_create(SPACE_ID);
  PRINT_TEST_RESULT(space_get_character_in_pos(s, 0) == NO_ID);
  space_destroy(s);
}

void test4_space_get_character_in_pos()
{
  Space *s = NULL;
  s = space_create(SPACE_ID);
  space_add_character(s, CHARACTER_ID);
  PRINT_TEST_RESULT(space_get_character_in_pos(s, 1) == NO_ID);
  space_destroy(s);
}

void test1_space_add_character()
{
  Space *s = NULL;
  PRINT_TEST_RESULT(space_add_character(s, CHARACTER_ID) == ERROR);
}

void test2_space_add_character()
{
  Space *s = NULL;
  s = space_create(SPACE_ID);
  space_add_character(s, CHARACTER_ID);
  PRINT_TEST_RESULT(space_add_character(s, CHARACTER_ID) == OK);
  space_destroy(s);
}

void test3_space_add_character()
{
  Space *s = NULL;
  s = space_create(SPACE_ID);
  PRINT_TEST_RESULT(space_add_character(s, CHARACTER_ID) == OK);
  space_destroy(s);
}

void test4_space_add_character()
{
  Space *s = NULL;
  s = space_create(SPACE_ID);
  PRINT_TEST_RESULT(space_add_character(s, NO_ID) == ERROR);
  space_destroy(s);
}


void test1_space_delete_character()
{
  Space *s = NULL;
  PRINT_TEST_RESULT(space_delete_character(s, CHARACTER_ID) == ERROR);
}

void test2_space_delete_character()
{
  Space *s = NULL;
  s = space_create(SPACE_ID);
  space_add_character(s, CHARACTER_ID);
  PRINT_TEST_RESULT(space_delete_character(s, CHARACTER_ID) == OK);
  space_destroy(s);
}

void test3_space_delete_character()
{
  Space *s = NULL;
  s = space_create(SPACE_ID);
  PRINT_TEST_RESULT(space_delete_character(s, CHARACTER_ID) == ERROR);
  space_destroy(s);
}

void test4_space_delete_character()
{
  Space *s = NULL;
  s = space_create(SPACE_ID);
  space_add_character(s, CHARACTER_ID);
  PRINT_TEST_RESULT(space_delete_character(s, NO_ID) == ERROR);
  space_destroy(s);
}

void test1_space_set_of_objects_is_full()
{
  Space *s = NULL;
  PRINT_TEST_RESULT(space_set_of_objects_is_full(s) == TRUE);
  space_destroy(s);
}

void test2_space_set_of_objects_is_full()
{
  Space *s = NULL;
  int i;
  s = space_create(SPACE_ID);
  for (i = 0; i < MAX_ELEMENTS_IN_SET; i++)
  {
    space_add_objectId(s, (long)(i + 1));
  }
  PRINT_TEST_RESULT(space_set_of_objects_is_full(s) == TRUE);
  space_destroy(s);
}

void test3_space_set_of_objects_is_full()
{
  Space *s = NULL;
  s = space_create(SPACE_ID);
  PRINT_TEST_RESULT(space_set_of_objects_is_full(s) == FALSE);
  space_destroy(s);
}

void test4_space_set_of_objects_is_full()
{
  Space *s = NULL;
  s = space_create(SPACE_ID);
  space_add_objectId(s, OBJECT_ID);
  PRINT_TEST_RESULT(space_set_of_objects_is_full(s) == FALSE);
  space_destroy(s);
}

void test1_space_delete_object()
{
  Space *s;
  s = space_create(SPACE_ID);
  PRINT_TEST_RESULT(space_delete_object(s, OBJECT_ID) == ERROR);
  space_destroy(s);
}

void test2_space_delete_object()
{
  Space *s = NULL;
  PRINT_TEST_RESULT(space_delete_object(s, OBJECT_ID) == ERROR);
}

void test3_space_delete_object()
{
  Space *s = NULL;
  s = space_create(SPACE_ID);
  space_add_objectId(s, OBJECT_ID);
  PRINT_TEST_RESULT(space_delete_object(s, NO_ID) == ERROR);
  space_destroy(s);
}

void test4_space_delete_object()
{
  Space *s = NULL;
  s = space_create(SPACE_ID);
  space_add_objectId(s, OBJECT_ID);
  PRINT_TEST_RESULT(space_delete_object(s, SPACE_ID) == ERROR);
  space_destroy(s);
}

void test5_space_delete_object()
{
  Space *s = NULL;
  s = space_create(SPACE_ID);
  space_add_objectId(s, OBJECT_ID);
  PRINT_TEST_RESULT(space_delete_object(s, OBJECT_ID) == OK);
  space_destroy(s);
}

void test1_space_set_discovered()
{
  Space *s = space_create(SPACE_ID);
  PRINT_TEST_RESULT(space_set_discovered(s, FALSE) == OK);
  space_destroy(s);
}

void test2_space_set_discovered()
{
  Space *s = NULL;
  PRINT_TEST_RESULT(space_set_discovered(s, TRUE) == ERROR);
}

void test3_space_set_discovered()
{
  Space *s = space_create(SPACE_ID);
  PRINT_TEST_RESULT(space_set_discovered(s, INVALID_VALUE) == ERROR);
  space_destroy(s);
}

void test1_space_get_discovered()
{
  Space *s = space_create(SPACE_ID);
  space_set_discovered(s, TRUE);
  PRINT_TEST_RESULT(space_get_discovered(s) == TRUE);
  space_destroy(s);
}

void test2_space_get_discovered()
{
  Space *s = NULL;
  PRINT_TEST_RESULT(space_get_discovered(s) == FALSE);
}

void test1_space_get_n_characters()
{
  Space *s = NULL;
  PRINT_TEST_RESULT(space_get_n_characters(s) == INVALID_VALUE);
}

void test2_space_get_n_characters()
{
  Space *s = space_create(SPACE_ID);
  space_add_character(s, CHARACTER_ID);
  PRINT_TEST_RESULT(space_get_n_characters(s) == ONE_ELEMENT);
  space_destroy(s);
}

void test3_space_get_n_characters()
{
  Space *s = space_create(SPACE_ID);
  PRINT_TEST_RESULT(space_get_n_characters(s) == NO_ELEMENTS);
  space_destroy(s);
}