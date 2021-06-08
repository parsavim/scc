#include <scc/buffer.h>

#include <stdint.h>
#include <stdlib.h>

void buf_append(buf_t* const buf, char const b) {
    ++buf->len;
    if (buf->len > buf->cap) {
        if (buf->cap == 0) {
            buf->cap = ++buf->len;
            buf->ptr = malloc(sizeof *buf->ptr * buf->cap);
        } else {
            buf->cap *= 2;
            buf->ptr = realloc(buf->ptr, sizeof *buf->ptr * buf->cap);
        }
    }
    buf->ptr[buf->len-2] = b;
    buf->ptr[buf->len-1] = 0;
}
