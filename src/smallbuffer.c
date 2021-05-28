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
            /*
             * Since the small and buf fields of sbuf_t are unioned,
             * buf_init with the buf field causes small to be overwritten,
             * so a temporary buffer has to be created first.
             */
            buf_t tmp;
            buf_init(&tmp);
            buf_extend(&tmp, sbuf->small, SBUF_SIZE-1);
            sbuf->buf = tmp;
        }
        buf_append(&sbuf->buf, b);
    }
}
