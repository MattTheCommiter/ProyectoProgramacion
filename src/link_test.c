/**
 * @brief it implements all tests for the link module 
 * 
 * @file link_test.c
 * @author Guilherme Povedano 
 * @version 0.0.1
 * @date 19-03-2025
 * @copyright GNU Public License 
*/

#include "link_test.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TESTS 35

int main(int argc, char *argv[]) {
    int test = 0; 
    int all = 1;

    if (argc < 2) {
        fprintf(stdout, "Running all tests for module Link:\n");
    } else {
        test = atoi(argv[1]);
        all = 0;
        fprintf(stdout, "Running test: %d\n", test);
            if (test < 1 || test > MAX_TESTS) {
                fprintf(stdout, "ERROR. Unknown test %d\n", test);
                exit(EXIT_FAILURE);
            } 
    }

    if (all || test == 1) test01_link_create();
    if (all || test == 2) test02_link_create();
    if (all || test == 3) test03_link_create();
    if (all || test == 4) test01_link_set_origin_id();
    if (all || test == 5) test02_link_set_origin_id();
    if (all || test == 6) test03_link_set_origin_id();
    if (all || test == 7) test04_link_set_origin_id();
    if (all || test == 8) test01_link_set_destination_id();
    if (all || test == 9) test02_link_set_destination_id();
    if (all || test == 10) test03_link_set_destination_id();
    if (all || test == 11) test04_link_set_destination_id();
    if (all || test == 12) test01_link_set_direction();
    if (all || test == 13) test02_link_set_direction();
    if (all || test == 14) test03_link_set_direction();
    if (all || test == 15) test04_link_set_direction();
    if (all || test == 16) test01_link_set_is_open();
    if (all || test == 17) test02_link_set_is_open();
    if (all || test == 18) test03_link_set_is_open();
    if (all || test == 19) test04_link_set_is_open();
    if (all || test == 20) test04_link_set_is_open();
    if (all || test == 21) test01_link_set_name(); 
    if (all || test == 22) test02_link_set_name(); 
    if (all || test == 23) test03_link_set_name(); 
    if (all || test == 24) test04_link_set_name(); 
    if (all || test == 25) test01_link_get_is_open();
    if (all || test == 26) test02_link_get_is_open();
    if (all || test == 27) test01_link_get_direction();
    if (all || test == 28) test02_link_get_direction();
    if (all || test == 29) test01_link_get_id();
    if (all || test == 30) test02_link_get_id();
    if (all || test == 31) test01_link_get_origin_id();
    if (all || test == 32) test02_link_get_origin_id();
    if (all || test == 33) test01_link_get_destination_id();
    if (all || test == 34) test02_link_get_destination_id();
    if (all || test == 35) test01_link_get_name(); 
    if (all || test == 36) test02_link_get_name(); 


 
    PRINT_PASSED_PERCENTAGE;

    return EXIT_SUCCESS;
}

void test01_link_create() {
    Link *l = NULL;
    PRINT_TEST_RESULT((l = link_create(NO_ID)) == NULL);
}

void test02_link_create() {
    Link *l = link_create(1);
    PRINT_TEST_RESULT(l != NULL);
    link_destroy(l);
}

void test03_link_create() {
    Link *l = link_create(1);
    PRINT_TEST_RESULT(link_get_id(l) == 1);
    link_destroy(l);
}

void test01_link_set_origin_id() {
    Link *l=NULL;
    PRINT_TEST_RESULT(link_set_origin_id(l, 10) == ERROR);
}
 
void test02_link_set_origin_id() {
    Link *l = link_create(1);
    PRINT_TEST_RESULT(link_set_origin_id(l, NO_ID) == ERROR);
    link_destroy(l);
}

void test03_link_set_origin_id() {
    Link *l = link_create(1);
    PRINT_TEST_RESULT(link_set_origin_id(l, 1) == OK);
    link_destroy(l);
}

void test04_link_set_origin_id() {
    Link *l = link_create(1);
    link_set_origin_id(l, 10);
    PRINT_TEST_RESULT(link_get_origin_id(l) == 10);
    link_destroy(l);
}

void test01_link_set_destination_id() {
    Link *l = NULL;
    PRINT_TEST_RESULT(link_set_destination_id(l, 10) == ERROR);
}
 
void test02_link_set_destination_id() {
    Link *l = link_create(1);
    PRINT_TEST_RESULT(link_set_destination_id(l, NO_ID) == ERROR);
    link_destroy(l);
}

void test03_link_set_destination_id() {
    Link *l = link_create(1);
    PRINT_TEST_RESULT(link_set_destination_id(l, 10) == OK);
    link_destroy(l);
}

void test04_link_set_destination_id() {
    Link *l = link_create(1);
    link_set_destination_id(l, 10);
    PRINT_TEST_RESULT(link_get_destination_id(l) == 10);
    link_destroy(l);
}

void test01_link_set_direction() {
    Link *l = NULL;
    PRINT_TEST_RESULT(link_set_direction(l, N) == ERROR);
}

void test02_link_set_direction() {
    Link *l = link_create(1);
    PRINT_TEST_RESULT(link_set_direction(l, UNKNOWN_DIR) == ERROR);
    link_destroy(l);
}

void test03_link_set_direction() {
    Link *l = link_create(1);
    PRINT_TEST_RESULT(link_set_direction(l, N) == OK);
    link_destroy(l);
}

void test04_link_set_direction() {
    Link *l = link_create(1);
    link_set_direction(l, N);
    PRINT_TEST_RESULT(link_get_direction(l) == N);
    link_destroy(l);
}

void test01_link_set_is_open() {
    Link *l = NULL;
    PRINT_TEST_RESULT(link_set_is_open(l, TRUE) == ERROR);
}

void test02_link_set_is_open() {
    Link *l = link_create(1);
    PRINT_TEST_RESULT(link_set_is_open(l, TRUE) == OK);
    link_destroy(l);
}

void test03_link_set_is_open() {
    Link *l = link_create(1);
    link_set_is_open(l, TRUE);
    PRINT_TEST_RESULT(link_get_is_open(l) == TRUE);
    link_destroy(l);
}

void test04_link_set_is_open() {
    Link *l = link_create(1);
    link_set_is_open(l, FALSE);
    PRINT_TEST_RESULT(link_get_is_open(l) == FALSE);
    link_destroy(l);
}

void test05_link_set_is_open() {
    Link *l = link_create(1);
    PRINT_TEST_RESULT(link_set_is_open(l, -1) == ERROR);
    link_destroy(l);
}

void test01_link_set_name() {
    Link *l = NULL;
    PRINT_TEST_RESULT(link_set_name(l, "hi!") == ERROR);
}

void test02_link_set_name() {
    Link *l = link_create(1);
    char *name = NULL;
    PRINT_TEST_RESULT(link_set_name(l, name) == ERROR);
    link_destroy(l);
}

void test03_link_set_name() {
    Link *l = link_create(1);
    char name[] = "hi!";
    PRINT_TEST_RESULT(link_set_name(l, name) == OK);
    link_destroy(l);
}

void test04_link_set_name() {
    Link *l = link_create(1);
    char name[] = "hi!";
    link_set_name(l, name);
    PRINT_TEST_RESULT(strcmp(link_get_name(l), name) == 0);
    link_destroy(l);
}

void test01_link_get_is_open() {
    Link *l = NULL;
    PRINT_TEST_RESULT(link_get_is_open(l) == FALSE);
}

void test02_link_get_is_open() {
    Link *l = link_create(1);
    PRINT_TEST_RESULT(link_get_is_open(l) == FALSE);  /* Default value is FALSE */
    link_destroy(l);
}

void test01_link_get_direction() {
    Link *l = NULL;
    PRINT_TEST_RESULT(link_get_direction(l) == UNKNOWN_DIR);
}

void test02_link_get_direction() {
    Link *l = link_create(1);
    PRINT_TEST_RESULT(link_get_direction(l) == UNKNOWN_DIR);  /* Default value is UNKNOWN_DIR */
    link_destroy(l);
}

void test01_link_get_id() {
    Link *l = NULL;
    PRINT_TEST_RESULT(link_get_id(l) == NO_ID);
}

void test02_link_get_id() {
    Link *l = link_create(1);
    PRINT_TEST_RESULT(link_get_id(l) == 1);
    link_destroy(l);
}

void test01_link_get_origin_id() {
    Link *l = NULL;
    PRINT_TEST_RESULT(link_get_origin_id(l) == NO_ID);
}

void test02_link_get_origin_id() {
    Link *l = link_create(1);
    PRINT_TEST_RESULT(link_get_origin_id(l) == NO_ID);  /* Default value is NO_ID */
    link_destroy(l);
}

void test01_link_get_destination_id() {
    Link *l = NULL;
    PRINT_TEST_RESULT(link_get_destination_id(l) == NO_ID);
}

void test02_link_get_destination_id() {
    Link *l = link_create(1);
    PRINT_TEST_RESULT(link_get_destination_id(l) == NO_ID);  /* Default value is NO_ID */
    link_destroy(l);
}

void test01_link_get_name() {
    Link *l = NULL;
    PRINT_TEST_RESULT(link_get_name(l) == NULL);
}

void test02_link_get_name() {
    Link *l = link_create(1);
    PRINT_TEST_RESULT(link_get_name(l) != NULL);
    link_destroy(l);
}