#include "buffer.h"
#include "smallbuffer.h"
#include "types.h"

void sbuf_append(sbuf_t* const sbuf, const u8 b) {
    ++sbuf->len;
    if (sbuf->len <= SBUF_SIZE) {
        sbuf->small[sbuf->len-2] = b;
        sbuf->small[sbuf->len-1] = 0;
    } else {
        if (sbuf->len == SBUF_SIZE+1) {
            buf_extend(&sbuf->buf, sbuf->small, SBUF_SIZE);
        }
        buf_append(&sbuf->buf, b);
    }
}
