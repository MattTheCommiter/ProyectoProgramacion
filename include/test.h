/**
 * @brief It defines common test functions for the whole project
 *
 * @file test.h
 * @author PROFESORES PPROG
 * @version 1.0.0
 * @date Unknown
 * @copyright GNU Public License
*/

#ifndef _TEST_H
#define _TEST_H

#pragma GCC diagnostic ignored "-Wpedantic"

#ifndef NOCOLOR
#define KRED  "\x1B[31m"  /*!<Code for red color*/
#define KGRN  "\x1B[32m"  /*!<Code for green color*/
#define KYEL  "\x1B[33m"  /*!<Code for yellow color*/
#define KCYN  "\x1B[36m"  /*!<Code for cyan color*/
#define RESET "\033[0m"   /*!<Code for resetting color*/
#else
#define KRED
#define KGRN
#define KYEL
#define KCYN
#define RESET
#endif

/**
 * @brief Prints the result of a test and updates test counters.
 *
 * This macro increments the test counter, evaluates the test result, updates the count of passed tests, and prints the test result.
 *
 * @param x The expression to evaluate as the test result.
 */
#define PRINT_TEST_RESULT(x) do{					\
    __test_counter++;							\
    __pass = (x);							\
    __test_passed = (__pass)? __test_passed + 1 : __test_passed;	\
    printf(KYEL "%s" RESET " line "  "%d " KCYN "%s" RESET ": %s\n",	\
	   __FILE__, __LINE__ , __FUNCTION__,				\
	   ((!__pass) ? KRED "NOT PASS" RESET : KGRN "PASS" RESET));	\
  } while (0)

  /**
 * @brief Prints the percentage of tests passed.
 *
 * This macro prints the percentage of tests passed based on the number of tests passed and the total number of tests.
 */
#define PRINT_PASSED_PERCENTAGE printf("Tests passed %d%%\n", ((__test_passed * 100) / __test_counter))
      
static int __test_counter = 0;
static int __test_passed  = 0;
static int __pass = 0;

#endif
