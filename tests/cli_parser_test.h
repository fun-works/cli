#ifndef CLI_PARSER_TEST_H
#define CLI_PARSER_TEST_H

#include <stdio.h>
#include <string.h>

#define TEST_CASE(name) \
    printf("Running test: %s\n", name);

#define ASSERT_TRUE(condition) \
    if (!(condition)) { \
        printf("Assertion failed: %s (line %d)\n", #condition, __LINE__); \
        return 1; \
    }

#define ASSERT_FALSE(condition) \
    if ((condition)) { \
        printf("Assertion failed: %s (line %d)\n", #condition, __LINE__); \
        return 1; \
    }

#define TEST_SUITE_BEGIN() int main() { \
    int failed_tests = 0;

#define TEST_SUITE_END() \
    if (failed_tests == 0) { \
        printf("All tests passed!\n"); \
    } else { \
        printf("%d test(s) failed.\n", failed_tests); \
    } \
    return failed_tests; \
    }

#define RUN_TEST(test) \
    if (test() != 0) { \
        printf("Test failed: %s\n\n", #test); \
        failed_tests++; \
    } else { \
        printf("Test passed: %s\n\n", #test); \
    }

#endif // CLI_PARSER_TEST_H
