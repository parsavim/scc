#include "buffer.h"

#include <stdlib.h>

void buf_append(buf_t* buf, u8 b) {
    ++buf->len;
    if (buf->len > buf->cap) {
        buf->cap *= 2;
        buf->p = realloc(buf->p, buf->cap);
    }
    buf->p[buf->len-1] = b;
    buf->p[buf->len] = 0;
}
