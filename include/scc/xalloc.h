#ifndef __SCC_XALLOC_H__
#define __SCC_XALLOC_H__

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

static inline
void* xmalloc(size_t size) {
    void* ptr = malloc(size);
    if (!ptr) {
        perror("malloc: ");
        exit(2);
    }
    return ptr;
}

static inline
void* xrealloc(void* ptr, size_t new_size) {
    ptr = realloc(ptr, new_size);
    if (!ptr) {
        perror("realloc: ");
        exit(2);
    }
    return ptr;
}

#endif
