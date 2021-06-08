#include <testing/testing.h>

#include <scc/pos.h>

#include <errno.h>
#include <string.h>

TEST(lines) {
    pos_reader_t reader;
    char const* const f = "tests/data/multiline.txt";
    pos_reader_init(&reader, f);
    TEST_STRING(reader.pos.filename, f);
    if (!reader.rf) {
        TEST_ERROR(strerror(errno));
    }

    char const* chars = "This\n";
    for (uint32_t i = 0; i < strlen(chars); ++i) {
        TEST_UINT32(pos_reader_getc(&reader), chars[i]);
        TEST_UINT32(reader.pos.col, i+1);
        TEST_UINT32(reader.pos.line, 1);
    }
    TEST_UINT32(pos_reader_getc(&reader), 'i');
    TEST_UINT32(reader.pos.col, 1);
    TEST_UINT32(reader.pos.line, 2);

    TEST_END();
}

int main(void) {
    TEST_RUN_START();

    TEST_RUN(lines);

    TEST_RUN_END();
}
