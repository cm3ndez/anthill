/**
 * @brief It defines the test assertions
 *
 * @file test.h
 * @author Profes PPROG
 * @version 2.0
 * @date 12-03-2025
 * @copyright GNU Public License
 */

#ifndef _TEST_H
#define _TEST_H

#pragma GCC diagnostic ignored "-Wpedantic"

#ifndef NOCOLOR
/**
 * @def KRED
 * @brief Red font color
 * */
#define KRED "\x1B[31m"
/**
 * @def KGRN
 * @brief Green font color
 * */
#define KGRN "\x1B[32m"
/**
 * @def KYEL
 * @brief Yellow font color
 * */
#define KYEL "\x1B[33m"
/**
 * @def KCYN
 * @brief Cyan font color
 * */
#define KCYN "\x1B[36m"
/**
 * @def RESET
 * @brief Default font color
 * */
#define RESET "\033[0m"
#else
/**
 * @def KRED
 * @brief No value
 * */
#define KRED
/**
 * @def KGRN
 * @brief No value
 * */
#define KGRN
/**
 * @def KYEL
 * @brief No value
 * */
#define KYEL
/**
 * @def KCYN
 * @brief No value
 * */
#define KCYN
/**
 * @def RESET
 * @brief No value
 * */
#define RESET
#endif

/**
 * @def PRINT_TEST_RESULT(x)
 * @brief Prints the results of the tests
 * @param x The number of tests
 * */
#define PRINT_TEST_RESULT(x)                                                                                       \
        do {                                                                                                       \
                __test_counter++;                                                                                  \
                __pass = (x);                                                                                      \
                __test_passed = (__pass) ? __test_passed + 1 : __test_passed;                                      \
                printf(KYEL "%s" RESET                                                                             \
                            " line "                                                                               \
                            "%d " KCYN "%s" RESET ": %s\n",                                                        \
                       __FILE__, __LINE__, __FUNCTION__, ((!__pass) ? KRED "NOT PASS" RESET : KGRN "PASS" RESET)); \
        } while (0)

/**
 * @def PRINT_PASSED_PERCENTAGE
 * @brief Prints the percentage
 * */
#define PRINT_PASSED_PERCENTAGE printf("Tests passed %d%%\n", ((__test_passed * 100) / __test_counter))

static int __test_counter = 0;
static int __test_passed = 0;
static int __pass = 0;

#endif
