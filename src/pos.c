#include <scc/pos.h>

#include <stdbool.h>
#include <stdio.h>

int pos_reader_getc(pos_reader_t* reader) {
    if (reader->newline) {
        ++reader->pos.line;
        reader->pos.col = 0;
        reader->newline = false;
    }
    int c = getc(reader->rf);
    if (c == '\n') {
        reader->newline = true;
    }
    ++reader->pos.col;
    return c;
}
