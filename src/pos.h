#ifndef __SCC_POS_H__
#define __SCC_POS_H__

#include "types.h"

/* Represents a position in a file. */
struct pos {
    const u8* filename;
    u32 line, col;
};
typedef struct pos pos_t;

#endif
