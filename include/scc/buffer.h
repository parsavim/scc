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

 /* Initializes a new empty buffer. */
static inline
void buf_init(buf_t* const buf) {
    /* Assume that the caller will append at least one time to preallocate. */
    buf->len = 1, buf->cap = 2;
    buf->p = malloc(sizeof (u8) * buf->cap);
    *buf->p = 0;
}

/* Frees the buffer. The buffer should not be used after being freed. */
static inline
void buf_free(buf_t* const buf) {
    if (buf->cap > 0) {
        free(buf->p);
    }
}

/* Frees the buffer but allows it to be reused. */
static inline
void buf_clear(buf_t* const buf) {
    buf_free(buf);
    buf_init(buf);
}

/*
 * Returns a pointer to a null-terminated character array with data
 * equivalent to those stored in the buffer.
 */
static inline
const char* buf_c_str(const buf_t* const buf) {
    return (const char*)buf->p;
}

/* Appends a byte to the end of the buffer. */
void buf_append(buf_t* buf, u8 b);

/* Appends n bytes from src to buf. */
void buf_extend(buf_t* buf, const u8* src, u32 n);

#endif
