#ifndef __TESTING_TESTING_H__
#define __TESTING_TESTING_H__

#include <math.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static uint32_t test_total_tests = 0;
static uint32_t test_failed_tests = 0;

/* Always terminated with a null character. */
struct test_buf {
    uint32_t cap;
    char* p;
};
typedef struct test_buf test_buf_t;

test_buf_t test_fail_out;

static inline
void test_buf_init(test_buf_t* buf) {
    buf->cap = 1;
    buf->p = malloc(sizeof *buf->p * buf->cap);
    buf->p[0] = '\0';
}

static
void test_bprintf(test_buf_t* buf, char const* fmt, ...) {
    /* Calculate extra amount of space that needs to be reserved. */
    va_list args;
    va_start(args, fmt);
    uint32_t extra = 0;
    for (char const* it = fmt; *it; ++it) {
        if (*it != '%') {
            ++extra;
            continue;
        }
        switch (*++it) {
            case '%':
                ++extra;
                break;
            case 'd':
                ;
                int const x = va_arg(args, int);
                extra += (x < 0) ? 1 : 0;
                extra += (uint32_t)log10(x) + 1;
                break;
            case 'u':
                extra += (uint32_t)log10(va_arg(args, uint32_t)) + 1;
                break;
            case 's':
                extra += strlen(va_arg(args, char const*));
        }
    }
    va_end(args);
    buf->p = realloc(buf->p, sizeof *buf->p * (buf->cap + extra));

    va_start(args, fmt);
    vsnprintf(buf->p+buf->cap-1, extra+1, fmt, args);
    va_end(args);
    buf->cap += extra;
}

#define TEST_RUN_FAIL(left_name, right_name, left, right, conversion_specifier) \
    test_bprintf(&test_fail_out, "%s:%d: assertion failed: (%s == %s)\n" \
            "   left: `%" conversion_specifier "`\n" \
            "  right: `%" conversion_specifier "`\n\n", \
            __FILE__, __LINE__, left_name, right_name, left, right)

#define TEST_END() return 0

#define TEST_CMP_NUM(left, right) (left == right)
#define TEST_CMP_STR(left, right) (strcmp(left, right) == 0)

#define TEST_ANY(left, right, cmp_func, conversion_specifier) \
    if (!cmp_func(left, right)) { \
        TEST_RUN_FAIL(#left, #right, left, right, conversion_specifier); \
        return 1; \
    }

#define TEST_UINT32(left, right) \
    TEST_ANY(left, right, TEST_CMP_NUM, "u")

#define TEST_STRING(left, right) \
    TEST_ANY(left, right, TEST_CMP_STR, "s")

#define TEST(test_name) \
    uint8_t test_name(void)

#define TEST_RUN_FAIL_STR "\033[91mFAILED\033[0m"
#define TEST_RUN_PASS_STR "\033[92mok\033[0m"

#define TEST_RUN(test_name) \
    do { \
        printf("running test " __FILE__ "::" #test_name " ... "); \
        ++test_total_tests; \
        if (test_name()) { \
            ++test_failed_tests; \
            puts(TEST_RUN_FAIL_STR); \
        } else { \
            puts(TEST_RUN_PASS_STR); \
        } \
    } while (0)

#define TEST_RUN_START() \
    test_buf_init(&test_fail_out)

#define TEST_RUN_END() \
    do { \
        if (test_failed_tests) { \
            printf("\nfailures:\n\n%s", test_fail_out.p); \
        } \
        printf("\ntest result: "); \
        if (test_failed_tests) { \
            printf(TEST_RUN_FAIL_STR); \
        } else { \
            printf(TEST_RUN_PASS_STR); \
        } \
        printf(". %u passed; %u failed.\n", test_total_tests-test_failed_tests, test_failed_tests); \
    } while (0)

#define TEST_ERROR(s) \
    { \
        test_bprintf(&test_fail_out, "%s:%d: error: %s\n\n", __FILE__, __LINE__, s); \
        return 1; \
    }

#endif
