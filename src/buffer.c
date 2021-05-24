#include "buffer.h"

#include <stdlib.h>

void buf_append(buf_t* const buf, const u8 b) {
    ++buf->len;
    if (buf->len > buf->cap) {
        buf->cap *= 2;
        buf->p = realloc(buf->p, buf->cap);
    }
    buf->p[buf->len-2] = b;
    buf->p[buf->len-1] = 0;
}

void buf_extend(buf_t *const buf, const u8 * const src, const u32 n) {
    for (u32 i = 0; i < n; ++i) {
        buf_append(buf, src[i]);
    }
}
