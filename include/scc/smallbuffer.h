#ifndef __SCC_SMALLBUFFER_H__
#define __SCC_SMALLBUFFER_H__

#include "buffer.h"

#include <stdint.h>

/* Size of the local buffer. */
#define SBUF_SIZE 16

/*
 * Small buffer optimization. If the buffer length exceeds SBUF_SIZE,
 * the whole buffer (all of its contents) will be moved to the buf_t.
 * Like buf_t, len includes the NUL byte.
 */
struct sbuf {
    uint8_t len;              /* Current ammount of small buffer being used. */
    /* If len < SBUF_SIZE, small should be accessed. Otherwise buf. */
    union {
        char small[SBUF_SIZE];
        buf_t buf;
    };
};
typedef struct sbuf sbuf_t;

/* Initialize a new buffer. */
static inline
void sbuf_init(sbuf_t* const sbuf) {
    sbuf->len = 1;
    sbuf->small[0] = 0;
}

/* Free the buffer. The buffer should not be used after being freed. */
static inline
void sbuf_free(sbuf_t* const sbuf) {
    if (sbuf->len > SBUF_SIZE) {
        buf_free(&sbuf->buf);
    }
}

static inline
void sbuf_clear(sbuf_t* const sbuf) {
    sbuf_free(sbuf);
    sbuf_init(sbuf);
}

/*
 * Returns a pointer to a null-terminated character array with data
 * equivalent to those stored in the buffer.
 */
static inline
char const* sbuf_c_str(sbuf_t const* const sbuf) {
    if (sbuf->len <= SBUF_SIZE) {
        return sbuf->small;
    }
    return buf_c_str(&sbuf->buf);
}

void sbuf_append(sbuf_t* sbuf, char b);

#endif
