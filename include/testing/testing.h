#ifndef __TESTING_TESTING_H__
#define __TESTING_TESTING_H__

#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static uint32_t test_total_tests = 0;
static uint32_t test_failed_tests = 0;


struct {
    char name[L_tmpnam+1];
    FILE* wf;
} test_tmp_fail_msgs;

#define TEST_FAIL(left_name, right_name, left, right, conversion_specifier) \
    fprintf(test_tmp_fail_msgs.wf, "%s:%d: assertion failed: (%s == %s)\n" \
            "   left: `%" conversion_specifier "`\n" \
            "  right: `%" conversion_specifier "`\n\n", \
            __FILE__, __LINE__, left_name, right_name, left, right)
#define TEST_END() return 0
#define TEST_CMP_NUM(left, right) (left == right)
#define TEST_CMP_STR(left, right) (strcmp(left, right) == 0)

#define TEST_ANY(left, right, cmp_func, conversion_specifier) \
    if (!cmp_func(left, right)) { \
        TEST_FAIL(#left, #right, left, right, conversion_specifier); \
        return 1; \
    }

#define TEST_UINT32(left, right) \
    TEST_ANY(left, right, TEST_CMP_NUM, "u")

#define TEST_STRING(left, right) \
    TEST_ANY(left, right, TEST_CMP_STR, "s")

#define TEST(test_name) \
    uint8_t test_name(void)

#define TEST_FAIL_STR "\033[91mFAILED\033[0m"
#define TEST_PASS_STR "\033[92mok\033[0m"

#define TEST_RUN(test_name) \
    do { \
        printf("running test " __FILE__ "::" #test_name " ... "); \
        ++test_total_tests; \
        if (test_name()) { \
            ++test_failed_tests; \
            puts(TEST_FAIL_STR); \
        } else { \
            puts(TEST_PASS_STR); \
        } \
    } while (0)

#define TEST_RUN_START() \
    do { \
        test_tmp_fail_msgs.name[0] = '.'; \
        tmpnam(test_tmp_fail_msgs.name+1); \
        test_tmp_fail_msgs.wf = fopen(test_tmp_fail_msgs.name, "w"); \
        if (!test_tmp_fail_msgs.wf) { \
            perror("failed to start test."); \
            exit(1); \
        } \
    } while (0)

#define TEST_RUN_END() \
    do { \
        fclose(test_tmp_fail_msgs.wf); \
        if (test_failed_tests) { \
            puts("\nfailures:\n"); \
            FILE* rf = fopen(test_tmp_fail_msgs.name, "r"); \
            if (!rf) { \
                perror("failed to open file with error messages."); \
                exit(1); \
            } \
            char buf[4096]; \
            size_t n; \
            while ((n = fread(buf, 1, sizeof buf, rf)) > 0) \
                fwrite(buf, 1, n, stdout); \
            fclose(rf); \
        } \
        remove(test_tmp_fail_msgs.name); \
        printf("\ntest result: "); \
        if (test_failed_tests) { \
            printf(TEST_FAIL_STR); \
        } else { \
            printf(TEST_PASS_STR); \
        } \
        printf(". %u passed; %u failed.\n", test_total_tests-test_failed_tests, test_failed_tests); \
    } while (0)

#endif
