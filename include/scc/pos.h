#ifndef __SCC_POS_H__
#define __SCC_POS_H__

#include <stdint.h>

/* Represents a position in a file. */
struct pos {
    char const* filename;
    uint32_t line, col;
};
typedef struct pos pos_t;

#endif
