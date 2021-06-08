#ifndef __SCC_POS_H__
#define __SCC_POS_H__

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

/* Represents a position in a file. */
struct pos {
    char const* filename;
    uint32_t line, col;
};
typedef struct pos pos_t;

/* 
 * Wraps a FILE* open for reading with methods that allow 
 * it to update the file position on each read. The pos field
 * can be accessed at any time to be examined. After a read call
 * by the reader of the rf field returns EOF, the pos field will
 * be in an undefined state.
 */
struct pos_reader {
    pos_t pos;
    FILE* rf;

    /*
     * true if the last character read was a newline character.
     * When a newline character is encountered, the line field
     * for pos is not immediately incremented, as it has not
     * actually reached the next line until the next read.
     * newline should be checked if it is true at the beginning
     * of each read call to update the position.
     */
    bool newline;
};
typedef struct pos_reader pos_reader_t;

/*
 * Opens filename for reading and initializes the reader. If
 * there was an error opening the file for reading, the rf field
 * of reader will be set to NULL and errno will be set.
 */
static inline
void pos_reader_init(pos_reader_t* reader, char const* const filename) {
    reader->pos.filename = filename;
    reader->pos.line = 0;
    reader->pos.col = 0;
    reader->rf = fopen(filename, "r");
    reader->newline = true;
}

int pos_reader_getc(pos_reader_t* reader);

#endif
