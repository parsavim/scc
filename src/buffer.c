#include <scc/buffer.h>

#include <stdint.h>
#include <stdlib.h>

void buf_append(buf_t* const buf, char const b) {
    ++buf->len;
    if (buf->len > buf->cap) {
        buf->cap *= 2;
        buf->p = realloc(buf->p, buf->cap);
    }
    buf->p[buf->len-2] = b;
    buf->p[buf->len-1] = 0;
}

void buf_extend(buf_t *const buf, char const* const src, uint32_t const n) {
    for (uint32_t i = 0; i < n; ++i) {
        buf_append(buf, src[i]);
    }
}
