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
   if (all || test == 6) test2_set_add();
   if (all || test == 7) test1_set_del();
   if (all || test == 8) test2_set_del();
   if (all || test == 9) test1_set_print();
   if (all || test == 10) test2_set_print();
   if (all || test == 11) test3_set_print();
   if (all || test == 12) test1_set_belongs();
   if (all || test == 13) test2_set_belongs();
   if (all || test == 14) test3_set_belongs();
   if (all || test == 15) test1_set_is_empty();
   if (all || test == 16) test2_set_is_empty();
   if (all || test == 17) test3_set_is_empty();
   if (all || test == 18) test1_set_get_num_elements();
   if (all || test == 19) test2_set_get_num_elements();
   if (all || test == 20) test3_set_get_num_elements();
   if (all || test == 21) test1_set_get_Id_in_pos();
   if (all || test == 22) test2_set_get_Id_in_pos();
   if (all || test == 23) test3_set_get_Id_in_pos();
   if (all || test == 24) test4_set_get_Id_in_pos();
   if (all || test == 25) test5_set_get_Id_in_pos();
   if (all || test == 26) test6_set_get_Id_in_pos();
   if (all || test == 27) test1_set_get_pos_from_Id();
   if (all || test == 28) test2_set_get_pos_from_Id();
   if (all || test == 29) test3_set_get_pos_from_Id();
   if (all || test == 30) test4_set_get_pos_from_Id();











 
   PRINT_PASSED_PERCENTAGE;
 
   return 0;
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
  Set *s=NULL;
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
  PRINT_TEST_RESULT(result = (set_add(s, 5)==OK));
  set_destroy(s);
 }

 void test3_set_add(){
  int result;
  Set *s;
  s=set_create();
  set_add(s, 5);
  PRINT_TEST_RESULT(result = (set_add(s, 3)==OK));
  set_destroy(s);
 }

 void test4_set_add(){
  int result;
  Set *s=NULL;
  PRINT_TEST_RESULT(result = (set_add(s, 3)==ERROR));
  set_destroy(s);
 }

 void test1_set_del(){
  int result;
  Set *s;
  s=set_create();
  set_add(s,5);
  PRINT_TEST_RESULT(result = (set_del(s, 3)==OK));
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

 void test3_set_del(){
  int result;
  Set *s=NULL;
  PRINT_TEST_RESULT(result = (set_del(s, 5)==ERROR));
  set_destroy(s);
 }

 void test4_set_del(){
  int result;
  Set *s=NULL;
  s = set_create();
  PRINT_TEST_RESULT(result = (set_del(s, NO_ID)==ERROR));
  set_destroy(s);
 }
 
void test1_set_print(){
  int result;
  Set *s=NULL;
  PRINT_TEST_RESULT (result=(set_print(s)) == -1);
}

void test2_set_print(){
  int result;
  Set *s=NULL;
  s = set_create();
  set_add(s, 3);
  PRINT_TEST_RESULT (result=(set_print(s) == 1));
  set_destroy(s);
}

void test3_set_print(){
  int result;
  Set *s=NULL;
  s = set_create();
  set_add(s, 3);
  set_add(s, 5);
  set_add(s, 7);
  set_add(s, 6);
  set_del(s, 5);
  PRINT_TEST_RESULT (result=(set_print(s) == 3));
  set_destroy(s);
}

void test1_set_belongs(){
  int result;
  Set *s=NULL;
  PRINT_TEST_RESULT (result=(set_belongs(s, 3) == FALSE));
}

void test2_set_belongs(){
  int result;
  Set *s;
  s=set_create();
  set_add(s, 5);
  PRINT_TEST_RESULT(result = (set_belongs(s, 3)==FALSE));
  set_destroy(s); 
}

void test3_set_belongs(){
  int result;
  Set *s;
  s=set_create();
  set_add(s, 5);
  PRINT_TEST_RESULT(result = (set_belongs(s, 5)==TRUE));
  set_destroy(s); 
}

void test4_set_belongs(){
  int result;
  Set *s;
  s=set_create();
  set_add(s, 5);
  PRINT_TEST_RESULT(result = (set_belongs(s, NO_ID)==FALSE));
  set_destroy(s); 
}


void test1_set_is_empty(){
  int result;
  Set *s=NULL;
  PRINT_TEST_RESULT (result=(set_is_empty(s) == TRUE));
}

void test2_set_is_empty(){
  int result;
  Set *s;
  s=set_create();
  PRINT_TEST_RESULT(result = (set_is_empty(s)==TRUE));
  set_destroy(s); 
}

void test3_set_is_empty(){
  int result;
  Set *s;
  s=set_create();
  set_add(s, 5);
  PRINT_TEST_RESULT(result = (set_is_empty(s)==FALSE));
  set_destroy(s); 
}

void test1_set_is_full(){
  int result;
  Set *s=NULL;
  PRINT_TEST_RESULT (result=(set_is_full(s) == TRUE));
}

void test2_set_is_full(){
  int result;
  Set *s;
  s=set_create();
  PRINT_TEST_RESULT(result = (set_is_empty(s)==FALSE));
  set_destroy(s); 
}

void test3_set_is_full(){
  int result, i;
  Set *s;
  s=set_create();
  for(i=0;i<MAX_ELEMENTS_IN_SET;i++){
    set_add(s, (long)(i+1));
  }
  PRINT_TEST_RESULT(result = (set_is_full(s)==TRUE));
  set_destroy(s); 
}

void test1_set_get_num_elements(){
  int result;
  Set *s=NULL;
  PRINT_TEST_RESULT (result=(set_get_num_elements(s) == -1));
}

void test2_set_get_num_elements(){
  int result;
  Set *s;
  s=set_create();
  PRINT_TEST_RESULT(result = (set_get_num_elements(s)==0));
  set_destroy(s); 
}

void test3_set_get_num_elements(){
  int result;
  Set *s;
  s=set_create();
  set_add(s, 5);
  set_add(s, 3);
  PRINT_TEST_RESULT(result = (set_get_num_elements(s)==2));
  set_destroy(s); 
}

void test1_set_get_Id_in_pos(){
  int result;
  Set *s=NULL;
  PRINT_TEST_RESULT (result=(set_get_Id_in_pos(s, 1) == -1));
}

void test2_set_get_Id_in_pos(){
  int result;
  Set *s;
  s=set_create();
  PRINT_TEST_RESULT(result = (set_get_Id_in_pos(s, 0)==-1));
  set_destroy(s); 
}

void test3_set_get_Id_in_pos(){
  int result;
  Set *s;
  s=set_create();
  set_add(s, 5);
  PRINT_TEST_RESULT(result = (set_get_Id_in_pos(s, 0)==5));
  set_destroy(s); 
}

void test4_set_get_Id_in_pos(){
  int result;
  Set *s;
  s=set_create();
  set_add(s, 5);
  set_add(s, 3);
  PRINT_TEST_RESULT(result = (set_get_Id_in_pos(s, 1)==3));
  set_destroy(s); 
}

void test5_set_get_Id_in_pos(){
  int result;
  Set *s;
  s=set_create();
  set_add(s, 5);
  PRINT_TEST_RESULT(result = (set_get_Id_in_pos(s, -1)==-1));
  set_destroy(s); 
}

void test6_set_get_Id_in_pos(){
  int result;
  Set *s;
  s=set_create();
  set_add(s, 5);
  set_add(s, 3);
  PRINT_TEST_RESULT(result = (set_get_Id_in_pos(s, 2)==-1));
  set_destroy(s); 
}

void test1_set_get_pos_from_Id(){
  int result;
  Set *s=NULL;
  PRINT_TEST_RESULT(result = (set_get_pos_from_Id(s, 0)==NO_ID));
}

void test2_set_get_pos_from_Id(){
  int result;
  Set *s=NULL;
  s=set_create();
  PRINT_TEST_RESULT(result = (set_get_pos_from_Id(s, 2)==-1));
  set_destroy(s); 
}

void test3_set_get_pos_from_Id(){
  int result;
  Set *s=NULL;
  s=set_create();
  set_add(s, 5);
  PRINT_TEST_RESULT(result = (set_get_pos_from_Id(s, 2)==-1));
  set_destroy(s); 
}

void test4_set_get_pos_from_Id(){
  int result;
  Set *s=NULL;
  s=set_create();
  set_add(s, 5);
  set_add(s, 3);
  PRINT_TEST_RESULT(result = (set_get_pos_from_Id(s, 3)==1));
  set_destroy(s); 
}