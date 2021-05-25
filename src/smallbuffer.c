#include <scc/buffer.h>
#include <scc/smallbuffer.h>

#include <stdint.h>

void sbuf_append(sbuf_t* const sbuf, char const b) {
    ++sbuf->len;
    if (sbuf->len <= SBUF_SIZE) {
        sbuf->small[sbuf->len-2] = b;
        sbuf->small[sbuf->len-1] = 0;
    } else {
        if (sbuf->len == SBUF_SIZE+1) {
            buf_init(&sbuf->buf);
            buf_extend(&sbuf->buf, sbuf->small, SBUF_SIZE);
        }
        buf_append(&sbuf->buf, b);
    }
}
