
#ifndef memory_h
#define memory_h

#include "common.h"

#define GROW_CAPACITY(capacity) \
    ((capacity) < 8 ? 8 : (capacity) * 2)

#define GROW_ARRAY(type, pointer, newCount) \
    (type*)reallocate(pointer, \
        sizeof(type) * (newCount))

#define FREE_ARRAY(type, pointer) \
    reallocate(pointer, 0)

void* reallocate(void* ptr, size_t newSize);

#endif
