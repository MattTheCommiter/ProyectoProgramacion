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

#define MAX_TESTS 43 /*!<Total number of test functions*/

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
    test1_space_get_character();
  if (all || test == 25)
    test2_space_get_character();
  if (all || test == 26)
    test3_space_get_character();
  if (all || test == 27)
    test1_space_set_character();
  if (all || test == 28)
    test2_space_set_character();
  if (all || test == 29)
    test3_space_set_character();
  if (all || test == 30)
    test1_space_set_of_objects_is_full();
  if (all || test == 31)
    test2_space_set_of_objects_is_full();
  if (all || test == 32)
    test3_space_set_of_objects_is_full();
  if (all || test == 33)
    test4_space_set_of_objects_is_full();
  if (all || test == 34)
    test1_space_delete_object();
  if (all || test == 35)
    test2_space_delete_object();
  if (all || test == 36)
    test3_space_delete_object();
  if (all || test == 37)
    test4_space_delete_object();
  if (all || test == 38)
    test5_space_delete_object();
  if (all || test == 39)
    test1_space_set_discovered();
  if (all || test == 40)
    test2_space_set_discovered();
  if (all || test == 41)
    test3_space_set_discovered();
  if (all || test == 42)
    test1_space_get_discovered();
  if (all || test == 43)
    test2_space_get_discovered();

  PRINT_PASSED_PERCENTAGE;

  return EXIT_SUCCESS;
}

void test1_space_create()
{
  int result;
  Space *s;
  s = space_create(5);
  result = (s != NULL);
  PRINT_TEST_RESULT(result);
  space_destroy(s);
}

void test2_space_create()
{
  Space *s;
  s = space_create(4);
  PRINT_TEST_RESULT(space_get_id(s) == 4);
  space_destroy(s);
}

void test1_space_set_name()
{
  Space *s;
  s = space_create(5);
  PRINT_TEST_RESULT(space_set_name(s, "hola") == OK);
  space_destroy(s);
}

void test2_space_set_name()
{
  Space *s = NULL;
  PRINT_TEST_RESULT(space_set_name(s, "hola") == ERROR);
}

void test3_space_set_name()
{
  Space *s;
  s = space_create(5);
  PRINT_TEST_RESULT(space_set_name(s, NULL) == ERROR);
  space_destroy(s);
}

void test1_space_add_objectId()
{
  Space *s;
  s = space_create(5);
  PRINT_TEST_RESULT(space_add_objectId(s, 1) == OK);
  space_destroy(s);
}

void test2_space_add_objectId()
{
  Space *s = NULL;
  PRINT_TEST_RESULT(space_add_objectId(s, 1) == ERROR);
}

void test3_space_add_objectId()
{
  Space *s = NULL;
  s = space_create(5);
  PRINT_TEST_RESULT(space_add_objectId(s, NO_ID) == ERROR);
  space_destroy(s);
}

void test1_space_get_name()
{
  Space *s;
  s = space_create(1);
  space_set_name(s, "adios");
  PRINT_TEST_RESULT(strcmp(space_get_name(s), "adios") == 0);
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
  s = space_create(25);
  PRINT_TEST_RESULT(space_get_id(s) == 25);
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
  PRINT_TEST_RESULT(space_object_belongs(s, 3) == FALSE);
  space_destroy(s);
}

void test2_space_object_belongs()
{
  Space *s = NULL;
  s = space_create(25);
  space_add_objectId(s, 3);
  PRINT_TEST_RESULT(space_object_belongs(s, 5) == FALSE);
  space_destroy(s);
}

void test3_space_object_belongs()
{
  Space *s = NULL;
  s = space_create(25);
  PRINT_TEST_RESULT(space_object_belongs(s, 5) == FALSE);
  space_destroy(s);
}

void test4_space_object_belongs()
{
  Space *s = NULL;
  s = space_create(25);
  space_add_objectId(s, 3);
  PRINT_TEST_RESULT(space_object_belongs(s, NO_ID) == FALSE);
  space_destroy(s);
}

void test5_space_object_belongs()
{
  Space *s = NULL;
  s = space_create(25);
  space_add_objectId(s, 5);
  PRINT_TEST_RESULT(space_object_belongs(s, 5) == TRUE);
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
  s = space_create(25);
  PRINT_TEST_RESULT(space_has_no_objects(s) == TRUE);
  space_destroy(s);
}

void test3_space_has_no_objects()
{
  Space *s = NULL;
  s = space_create(25);
  space_add_objectId(s, 3);
  PRINT_TEST_RESULT(space_has_no_objects(s) == FALSE);
  space_destroy(s);
}

void test1_space_get_num_of_objects()
{
  Space *s = NULL;
  PRINT_TEST_RESULT(space_get_num_of_objects(s) == 0);
  space_destroy(s);
}

void test2_space_get_num_of_objects()
{
  Space *s = NULL;
  s = space_create(25);
  PRINT_TEST_RESULT(space_get_num_of_objects(s) == 0);
  space_destroy(s);
}

void test3_space_get_num_of_objects()
{
  Space *s = NULL;
  s = space_create(25);
  space_add_objectId(s, 3);
  PRINT_TEST_RESULT(space_get_num_of_objects(s) == 1);
  space_destroy(s);
}

void test1_space_get_character()
{
  Space *s = NULL;
  PRINT_TEST_RESULT(space_get_character(s) == NO_ID);
  space_destroy(s);
}

void test2_space_get_character()
{
  Space *s = NULL;
  s = space_create(25);
  space_set_character(s, 10);
  PRINT_TEST_RESULT(space_get_character(s) == 10);
  space_destroy(s);
}

void test3_space_get_character()
{
  Space *s = NULL;
  s = space_create(25);
  PRINT_TEST_RESULT(space_get_character(s) == NO_ID);
  space_destroy(s);
}

void test1_space_set_character()
{
  Space *s = NULL;
  PRINT_TEST_RESULT(space_set_character(s, 10) == ERROR);
  space_destroy(s);
}

void test2_space_set_character()
{
  Space *s = NULL;
  s = space_create(25);
  space_set_character(s, 5);
  PRINT_TEST_RESULT(space_set_character(s, 10) == ERROR);
  space_destroy(s);
}

void test3_space_set_character()
{
  Space *s = NULL;
  s = space_create(25);
  PRINT_TEST_RESULT(space_set_character(s, 10) == OK);
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
  s = space_create(25);
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
  s = space_create(25);
  PRINT_TEST_RESULT(space_set_of_objects_is_full(s) == FALSE);
  space_destroy(s);
}

void test4_space_set_of_objects_is_full()
{
  Space *s = NULL;
  s = space_create(25);
  space_add_objectId(s, 3);
  PRINT_TEST_RESULT(space_set_of_objects_is_full(s) == FALSE);
  space_destroy(s);
}

void test1_space_delete_object()
{
  Space *s;
  s = space_create(5);
  PRINT_TEST_RESULT(space_delete_object(s, 1) == ERROR);
  space_destroy(s);
}

void test2_space_delete_object()
{
  Space *s = NULL;
  PRINT_TEST_RESULT(space_delete_object(s, 1) == ERROR);
}

void test3_space_delete_object()
{
  Space *s = NULL;
  s = space_create(5);
  space_add_objectId(s, 6);
  PRINT_TEST_RESULT(space_delete_object(s, NO_ID) == ERROR);
  space_destroy(s);
}

void test4_space_delete_object()
{
  Space *s = NULL;
  s = space_create(5);
  space_add_objectId(s, 6);
  PRINT_TEST_RESULT(space_delete_object(s, 5) == ERROR);
  space_destroy(s);
}

void test5_space_delete_object()
{
  Space *s = NULL;
  s = space_create(5);
  space_add_objectId(s, 5);
  PRINT_TEST_RESULT(space_delete_object(s, 5) == OK);
  space_destroy(s);
}

void test1_space_set_discovered()
{
  Space *s = space_create(5);
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
  Space *s = space_create(5);
  PRINT_TEST_RESULT(space_set_discovered(s, -1) == ERROR);
  space_destroy(s);
}

void test1_space_get_discovered()
{
  Space *s = space_create(5);
  space_set_discovered(s, TRUE);
  PRINT_TEST_RESULT(space_get_discovered(s) == TRUE);
  space_destroy(s);
}

void test2_space_get_discovered()
{
  Space *s = NULL;
  PRINT_TEST_RESULT(space_get_discovered(s) == FALSE);
}