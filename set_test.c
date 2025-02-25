/** 
 * @brief It tests set module
 * 
 * @file set_test.c
 * @author Matteo Artunedo
 * @version 0.1 
 * @date 24-02-2025
 * @copyright GNU Public License
 */

 #include <stdio.h> 
 #include <stdlib.h> 
 #include <string.h> 
 #include "set.h"
 #include "set_test.h"
 #include "test.h"
 
 #define MAX_TESTS 30
 
 /** 
  * @brief Main function for SET unit tests. 
  * 
  * You may execute ALL or a SINGLE test
  *   1.- No parameter -> ALL test are executed 
  *   2.- A number means a particular test (the one identified by that number) 
  *       is executed
  *  
  */
 int main(int argc, char** argv) {
 
   int test = 0;
   int all = 1;
 
   if (argc < 2) {
     printf("Running all test for module Set:\n");
   } else {
     test = atoi(argv[1]);
     all = 0;
     printf("Running test %d:\t", test);
     if (test < 1 && test > MAX_TESTS) {
       printf("Error: unknown test %d\t", test);
       exit(EXIT_SUCCESS);
     }
   }
 
 
   if (all || test == 1) test1_set_create();
   if (all || test == 2) test1_set_destroy();
   if (all || test == 3) test2_set_destroy();
   if (all || test == 4) test1_set_add();
   if (all || test == 5) test2_set_add();
   if (all || test == 6) test1_set_del();
   if (all || test == 7) test2_set_del();
   /*if (all || test == 8) test1_set_print();
   if (all || test == 9) test2_set_print();*/


 
   PRINT_PASSED_PERCENTAGE;
 
   return 1;
 }
 
 void test1_set_create() {
   int result;
   Set *s;
   s = set_create();
   PRINT_TEST_RESULT(result=(s!=NULL));
   set_destroy(s);
 }
 
 void test1_set_destroy() {
   int result;
   Set *s;
   s = set_create();
   PRINT_TEST_RESULT(result=(set_destroy(s) == OK));
 }

 void test2_set_destroy() {
  int result;
  Set *s;
  s = set_create();
  set_destroy(s);
  s=NULL;
  PRINT_TEST_RESULT(result=(set_destroy(s)==ERROR));
}
 
 void test1_set_add(){
    int result;
    Set *s;
    s=set_create();
    PRINT_TEST_RESULT(result = (set_add(s, 3)==OK));
    set_destroy(s);
 }

 void test2_set_add(){
  int result;
  Set *s;
  s=set_create();
  set_add(s, 5);
  PRINT_TEST_RESULT(result = (set_add(s, 3)==OK));
  set_destroy(s);
 }

 void test1_set_del(){
  int result;
  Set *s;
  s=set_create();
  set_add(s,5);
  PRINT_TEST_RESULT(result = (set_del(s, 3)==ERROR));
  set_destroy(s);
 }

 void test2_set_del(){
  int result;
  Set *s;
  s=set_create();
  set_add(s,5);
  PRINT_TEST_RESULT(result = (set_del(s, 5)==OK));
  set_destroy(s);
 }

 void test1_set_print(){
  int result;
  Set *s;
  s=set_create();
  set_add(s,5);
  PRINT_TEST_RESULT(result = (set_print(s)==OK));
  set_destroy(s);
 }

 void test2_set_print(){
  int result;
  Set *s;
  s=set_create();
  set_add(s,5);
  set_destroy(s);
  PRINT_TEST_RESULT(result = (set_print(s)==ERROR));
 }
 
