#ifndef __SCC_BUFFER_H__
#define __SCC_BUFFER_H__

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

/*
 * A growable buffer with amortized linear complexity. If p is valid, it will
 * be terminated with a NUL byte so that it can be used in string operations.
 * If p is NULL, buc_c_str will return an empty string literal.
 * len includes the NUL byte, therefore for getting the length of the string
 * subtract 1.
 */
struct buf {
    uint32_t len, cap;
    char* ptr;
};
typedef struct buf buf_t;

 /* Initializes a new empty buffer. */
static inline
void buf_init(buf_t* const buf) {
    buf->len = 0, buf->cap = 0;
    buf->ptr = NULL;
}

/* Sets the capacity of the buffer to cap + 1. Can only be used for initializing. */
static inline
void buf_reserve(buf_t* const buf, uint32_t cap) {
    buf->len = 1, buf->cap = cap + 1;
    buf->ptr = malloc(sizeof *buf->ptr * buf->cap);
    *buf->ptr = 0;
}

/* Frees the buffer. The buffer should not be used after being freed. */
static inline
void buf_free(buf_t* const buf) {
    if (buf->cap > 0) {
        free(buf->ptr);
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
char const* buf_c_str(buf_t const* const buf) {
    return (!buf->ptr) ? "" : buf->ptr;
}

/* Appends a byte to the end of the buffer. */
void buf_append(buf_t* buf, char b);

/* Appends n bytes from src to buf. */
static inline
void buf_extend(buf_t *const buf, char const* const src, uint32_t const n) {
    for (uint32_t i = 0; i < n; ++i) {
        buf_append(buf, src[i]);
    }
}

#endif
