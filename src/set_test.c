/**
 * @brief It tests set module
 *
 * @file set_test.c
 * @author Matteo Artunedo, Guilherme Povedano
 * @version 0.1
 * @date 24-02-2025
 * @copyright GNU Public License
 */
#include "set_test.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TESTS 38    /*!<Total number of test functions for the Set module*/
#define ID_1 1          /*!<Id value that will be used to test set functions*/
#define ID_2 2          /*!<Id value that will be used to test set functions*/
#define ID_3 3          /*!<Id value that will be used to test set functions*/
#define ID_4 4          /*!<Id value that will be used to test set functions*/
#define INVALID_POS1 -1 /*!<Value that serves as an invalid position in the tests*/
#define INVALID_POS2 2  /*!<Value that serves as an invalid position in the tests*/
#define ERROR_CODE -1   /*!<Error code retruned by several of the functions that return integers*/
/**
 * @brief Main function for SET unit tests.
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
    printf("Running all test for module Set:\n");
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
    test1_set_create();
  if (all || test == 2)
    test2_set_create();
  if (all || test == 3)
    test1_set_destroy();
  if (all || test == 4)
    test2_set_destroy();
  if (all || test == 5)
    test1_set_add();
  if (all || test == 6)
    test2_set_add();
  if (all || test == 7)
    test3_set_add();
  if (all || test == 8)
    test4_set_add();
  if (all || test == 9)
    test1_set_del();
  if (all || test == 10)
    test2_set_del();
  if (all || test == 11)
    test3_set_del();
  if (all || test == 12)
    test4_set_del();
  if (all || test == 13)
    test1_set_print();
  if (all || test == 14)
    test2_set_print();
  if (all || test == 15)
    test3_set_print();
  if (all || test == 16)
    test1_set_belongs();
  if (all || test == 17)
    test2_set_belongs();
  if (all || test == 18)
    test3_set_belongs();
  if (all || test == 19)
    test4_set_belongs();
  if (all || test == 20)
    test1_set_is_empty();
  if (all || test == 21)
    test2_set_is_empty();
  if (all || test == 22)
    test3_set_is_empty();
  if (all || test == 23)
    test1_set_get_num_elements();
  if (all || test == 24)
    test2_set_get_num_elements();
  if (all || test == 25)
    test3_set_get_num_elements();
  if (all || test == 26)
    test1_set_get_Id_in_pos();
  if (all || test == 27)
    test2_set_get_Id_in_pos();
  if (all || test == 28)
    test3_set_get_Id_in_pos();
  if (all || test == 29)
    test4_set_get_Id_in_pos();
  if (all || test == 30)
    test5_set_get_Id_in_pos();
  if (all || test == 31)
    test6_set_get_Id_in_pos();
  if (all || test == 32)
    test1_set_get_pos_from_Id();
  if (all || test == 33)
    test2_set_get_pos_from_Id();
  if (all || test == 34)
    test3_set_get_pos_from_Id();
  if (all || test == 35)
    test4_set_get_pos_from_Id();
  if (all || test == 36)
    test1_set_is_full();
  if (all || test == 37)
    test2_set_is_full();
  if (all || test == 38)
    test3_set_is_full();

  PRINT_PASSED_PERCENTAGE;

  return EXIT_SUCCESS;
}

void test1_set_create()
{
  int result;
  Set *s;
  s = set_create();
  PRINT_TEST_RESULT(result = (s != NULL));
  set_destroy(s);
}

void test2_set_create()
{
  Set *s;
  s = set_create();
  PRINT_TEST_RESULT(set_is_empty(s) == TRUE);
  set_destroy(s);
}

void test1_set_destroy()
{
  int result;
  Set *s;
  s = set_create();
  PRINT_TEST_RESULT(result = (set_destroy(s) == OK));
}

void test2_set_destroy()
{
  int result;
  Set *s = NULL;
  PRINT_TEST_RESULT(result = (set_destroy(s) == ERROR));
}

void test1_set_add()
{
  int result;
  Set *s;
  s = set_create();
  PRINT_TEST_RESULT(result = (set_add(s, ID_1) == OK));
  set_destroy(s);
}

void test2_set_add()
{
  int result;
  Set *s;
  s = set_create();
  PRINT_TEST_RESULT(result = (set_add(s, NO_ID) == ERROR));
  set_destroy(s);
}

void test3_set_add()
{
  int result;
  Set *s;
  s = set_create();
  set_add(s, ID_1);
  PRINT_TEST_RESULT(result = (set_add(s, ID_1) == OK));
  set_destroy(s);
}

void test4_set_add()
{
  int result;
  Set *s = NULL;
  PRINT_TEST_RESULT(result = (set_add(s, ID_1) == ERROR));
  set_destroy(s);
}

void test1_set_del()
{
  int result;
  Set *s;
  s = set_create();
  set_add(s, ID_1);
  PRINT_TEST_RESULT(result = (set_del(s, ID_2) == ERROR));
  set_destroy(s);
}

void test2_set_del()
{
  int result;
  Set *s;
  s = set_create();
  set_add(s, ID_1);
  PRINT_TEST_RESULT(result = (set_del(s, ID_1) == OK));
  set_destroy(s);
}

void test3_set_del()
{
  int result;
  Set *s = NULL;
  PRINT_TEST_RESULT(result = (set_del(s, ID_1) == ERROR));
  set_destroy(s);
}

void test4_set_del()
{
  int result;
  Set *s = NULL;
  s = set_create();
  PRINT_TEST_RESULT(result = (set_del(s, NO_ID) == ERROR));
  set_destroy(s);
}

void test1_set_print()
{
  int result;
  Set *s = NULL;
  PRINT_TEST_RESULT(result = (set_print(s)) == ERROR_CODE);
}

void test2_set_print()
{
  int result;
  Set *s = NULL;
  s = set_create();
  set_add(s, ID_1);
  PRINT_TEST_RESULT(result = (set_print(s) == 1));
  set_destroy(s);
}

void test3_set_print()
{
  int result;
  Set *s = NULL;
  s = set_create();
  set_add(s, ID_1);
  set_add(s, ID_2);
  set_add(s, ID_3);
  set_add(s, ID_4);
  set_del(s, ID_1);
  PRINT_TEST_RESULT(result = (set_print(s) == 3));
  set_destroy(s);
}

void test1_set_belongs()
{
  int result;
  Set *s = NULL;
  PRINT_TEST_RESULT(result = (set_belongs(s, ID_1) == FALSE));
}

void test2_set_belongs()
{
  int result;
  Set *s;
  s = set_create();
  set_add(s, ID_1);
  PRINT_TEST_RESULT(result = (set_belongs(s, ID_2) == FALSE));
  set_destroy(s);
}

void test3_set_belongs()
{
  int result;
  Set *s;
  s = set_create();
  set_add(s, ID_1);
  PRINT_TEST_RESULT(result = (set_belongs(s, ID_1) == TRUE));
  set_destroy(s);
}

void test4_set_belongs()
{
  int result;
  Set *s;
  s = set_create();
  set_add(s, ID_1);
  PRINT_TEST_RESULT(result = (set_belongs(s, NO_ID) == FALSE));
  set_destroy(s);
}

void test1_set_is_empty()
{
  int result;
  Set *s = NULL;
  PRINT_TEST_RESULT(result = (set_is_empty(s) == TRUE));
}

void test2_set_is_empty()
{
  int result;
  Set *s;
  s = set_create();
  PRINT_TEST_RESULT(result = (set_is_empty(s) == TRUE));
  set_destroy(s);
}

void test3_set_is_empty()
{
  int result;
  Set *s;
  s = set_create();
  set_add(s, ID_1);
  PRINT_TEST_RESULT(result = (set_is_empty(s) == FALSE));
  set_destroy(s);
}

void test1_set_is_full()
{
  int result;
  Set *s = NULL;
  PRINT_TEST_RESULT(result = (set_is_full(s) == TRUE));
}

void test2_set_is_full()
{
  int result;
  Set *s;
  s = set_create();
  PRINT_TEST_RESULT(result = (set_is_full(s) == FALSE));
  set_destroy(s);
}

void test3_set_is_full()
{
  int result, i;
  Set *s;
  s = set_create();
  for (i = 0; i < MAX_ELEMENTS_IN_SET; i++)
  {
    set_add(s, (long)(i + 1));
  }
  PRINT_TEST_RESULT(result = (set_is_full(s) == TRUE));
  set_destroy(s);
}

void test1_set_get_num_elements()
{
  int result;
  Set *s = NULL;
  PRINT_TEST_RESULT(result = (set_get_num_elements(s) == ERROR_CODE));
}

void test2_set_get_num_elements()
{
  int result;
  Set *s;
  s = set_create();
  PRINT_TEST_RESULT(result = (set_get_num_elements(s) == 0));
  set_destroy(s);
}

void test3_set_get_num_elements()
{
  int result;
  Set *s;
  s = set_create();
  set_add(s, ID_1);
  set_add(s, ID_2);
  PRINT_TEST_RESULT(result = (set_get_num_elements(s) == 2));
  set_destroy(s);
}

void test1_set_get_Id_in_pos()
{
  int result;
  Set *s = NULL;
  PRINT_TEST_RESULT(result = (set_get_Id_in_pos(s, 1) == ERROR_CODE));
}

void test2_set_get_Id_in_pos()
{
  int result;
  Set *s;
  s = set_create();
  PRINT_TEST_RESULT(result = (set_get_Id_in_pos(s, 0) == ERROR_CODE));
  set_destroy(s);
}

void test3_set_get_Id_in_pos()
{
  int result;
  Set *s;
  s = set_create();
  set_add(s, ID_1);
  PRINT_TEST_RESULT(result = (set_get_Id_in_pos(s, 0) == ID_1));
  set_destroy(s);
}

void test4_set_get_Id_in_pos()
{
  int result;
  Set *s;
  s = set_create();
  set_add(s, ID_1);
  set_add(s, ID_2);
  PRINT_TEST_RESULT(result = (set_get_Id_in_pos(s, 1) == ID_2));
  set_destroy(s);
}

void test5_set_get_Id_in_pos()
{
  int result;
  Set *s;
  s = set_create();
  set_add(s, ID_1);
  PRINT_TEST_RESULT(result = (set_get_Id_in_pos(s, INVALID_POS1) == ERROR_CODE));
  set_destroy(s);
}

void test6_set_get_Id_in_pos()
{
  int result;
  Set *s;
  s = set_create();
  set_add(s, ID_1);
  set_add(s, ID_2);
  PRINT_TEST_RESULT(result = (set_get_Id_in_pos(s, INVALID_POS2) == ERROR_CODE));
  set_destroy(s);
}

void test1_set_get_pos_from_Id()
{
  int result;
  Set *s = NULL;
  PRINT_TEST_RESULT(result = (set_get_pos_from_Id(s, 0) == NO_ID));
}

void test2_set_get_pos_from_Id()
{
  int result;
  Set *s = NULL;
  s = set_create();
  PRINT_TEST_RESULT(result = (set_get_pos_from_Id(s, INVALID_POS2) == ERROR_CODE));
  set_destroy(s);
}

void test3_set_get_pos_from_Id()
{
  int result;
  Set *s = NULL;
  s = set_create();
  set_add(s, ID_1);
  PRINT_TEST_RESULT(result = (set_get_pos_from_Id(s, INVALID_POS2) == ERROR_CODE));
  set_destroy(s);
}

void test4_set_get_pos_from_Id()
{
  int result;
  Set *s = NULL;
  s = set_create();
  set_add(s, ID_1);
  set_add(s, ID_2);
  PRINT_TEST_RESULT(result = (set_get_pos_from_Id(s, ID_2) == 1));
  set_destroy(s);
}