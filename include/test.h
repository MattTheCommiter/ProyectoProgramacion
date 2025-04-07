/**
 * @brief It defines common test functions for the whole project
 *
 * @file test.h
 * @author Araceli Gutierrez, Matteo Artunedo, Guilherme Povedano
 * @version 1.0.0
 * @date Unknown
 * @copyright GNU Public License
*/

#ifndef _TEST_H
#define _TEST_H

#pragma GCC diagnostic ignored "-Wpedantic"

#ifndef NOCOLOR
#define KRED  "\x1B[31m" /*!< defines the code corresponding to the colour red */
#define KGRN  "\x1B[32m" /*!< defines the code corresponding to the colour green */ 
#define KYEL  "\x1B[33m" /*!< defines the code corresponding to the colour yellow */
#define KCYN  "\x1B[36m" /*!< defines the code corresponding to the colour cyan */
#define RESET "\033[0m" /*!< defines the code corresponding to the reset colour (white) */
#else
#define KRED /*!< defines the code corresponding to the colour red - in case NOCOLOR is defined */
#define KGRN /*!< defines the code corresponding to the colour green - in case NOCOLOR is defined */ 
#define KYEL /*!< defines the code corresponding to the colour yellow - in case NOCOLOR is defined */
#define KCYN /*!< defines the code corresponding to the colour cyan - in case NOCOLOR is defined */
#define RESET /*!< defines the code corresponding to the reset colour (white) - in case NOCOLOR is defined */
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
      
static int __test_counter = 0; /*!< Macro definition for keeping track of the number of tests performed in a module */
static int __test_passed  = 0; /*!< Macro definition for keeping track of the number of tests passed in a module */
static int __pass = 0; /*!< Macro definition for whether a test was passed or not */

#endif
