#include <scc/buffer.h>

#include <stdint.h>
#include <stdlib.h>

void buf_append(buf_t* const buf, char const b) {
    ++buf->len;
    if (buf->len > buf->cap) {
        if (buf->cap == 0) {
            buf->cap = ++buf->len;
            buf->p = malloc(sizeof *buf->p * buf->cap);
        } else {
            buf->cap *= 2;
            buf->p = realloc(buf->p, sizeof *buf->p * buf->cap);
        }
    }
    buf->p[buf->len-2] = b;
    buf->p[buf->len-1] = 0;
}
