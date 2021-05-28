#include <testing/testing.h>

#include <scc/buffer.h>

#include <string.h>

TEST(empty) {
    buf_t buf;
    buf_init(&buf);

    TEST_STRING(buf_c_str(&buf), "");

    TEST_END();
}

TEST(reserving) {
    buf_t buf;
    char const* const s = "reserve";
    char const* const t = " more";
    buf_reserve(&buf, strlen(s));

    /* Empty. */
    TEST_STRING(buf_c_str(&buf), "");

    /* Using amount reserved. */
    buf_extend(&buf, s, strlen(s));
    TEST_STRING(buf_c_str(&buf), s);

    /* Using more. */
    buf_extend(&buf, t, strlen(t));
    TEST_STRING(buf_c_str(&buf), "reserve more");

    TEST_END();
}

TEST(appending) {
    buf_t buf;
    buf_init(&buf);
    char const* const s = "these words";
    
    buf_extend(&buf, s, strlen(s));
    TEST_STRING(buf_c_str(&buf), s);

    buf_append(&buf, '.');
    TEST_STRING(buf_c_str(&buf), "these words.");

    TEST_END();
}

int main(void) {
    TEST_RUN_START();

    TEST_RUN(empty);
    TEST_RUN(reserving);
    TEST_RUN(appending);

    TEST_RUN_END();
}
