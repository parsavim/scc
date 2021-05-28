#include <testing/testing.h>

#include <scc/smallbuffer.h>

TEST(empty) {
    sbuf_t sbuf;
    sbuf_init(&sbuf);

    TEST_STRING(sbuf_c_str(&sbuf), "");
    
    TEST_END();
}

TEST(appending) {
    sbuf_t sbuf;
    sbuf_init(&sbuf);

    sbuf_append(&sbuf, '\n');
    TEST_STRING(sbuf_c_str(&sbuf), "\n");

    TEST_END();
}

TEST(stack) {
    sbuf_t sbuf;
    sbuf_init(&sbuf);
    char buf[SBUF_SIZE];
    for (uint32_t i = 0; i < (sizeof buf)-1; ++i) {
        buf[i] = 32+i;
        sbuf_append(&sbuf, 32+i);
    }
    buf[SBUF_SIZE-1] = '\0';
    TEST_STRING(sbuf_c_str(&sbuf), buf);

    TEST_END();
}

TEST(heap) {
    sbuf_t sbuf;
    sbuf_init(&sbuf);
    char buf[SBUF_SIZE+2];
    for (uint32_t i = 0; i < (sizeof buf)-1; ++i) {
        buf[i] = 32+i;
        sbuf_append(&sbuf, 32+i);
    }
    buf[SBUF_SIZE+1] = '\0';
    TEST_STRING(sbuf_c_str(&sbuf), buf);

    TEST_END();
}

int main() {
    TEST_RUN_START();

    TEST_RUN(empty);
    TEST_RUN(appending);
    TEST_RUN(stack);
    TEST_RUN(heap);

    TEST_RUN_END();
}
