#ifndef __SCC_BUFFER_H__
#define __SCC_BUFFER_H__

#include "types.h"

#include <stddef.h>
#include <stdlib.h>

/*
 * A growable buffer with amortized linear complexity. If p is valid, it will
 * be terminated with a NUL byte so that it can be used in string operations.
 * len includes the NUL byte, therefore for getting the length of the string
 * subtract 1.
 */
struct buf {
    u32 len, cap;
    u8* p;
};
typedef struct buf buf_t;

/* 
 * Initialize a new empty buffer. p will be set to point to the string literal
 * '\0' so that it can be used in string operations. 
 */
static inline
buf_t buf_new() {
    /* Assume that the caller will append at least one time to preallocate. */
    buf_t buf = { .len=1, .cap=2 };
    buf.p = malloc(sizeof (u8) * buf.cap);
    *buf.p = 0;
    return buf;
}

/* Free the buffer. The buffer should not be used after being freed. */
static inline
void buf_free(buf_t buf) {
    if (buf.cap > 0) {
        free(buf.p);
    }
}

/* Append a byte to the end of the buffer. */
void buf_append(buf_t* buf, u8 b);

#endif
