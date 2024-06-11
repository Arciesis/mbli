#ifndef MBLI_COMMON_H
#define MBLI_COMMON_H

#include "lua_source_reader.h"
#include "mbli_lexer.h"

#define GROW_CAPACITY(capacity) \
    ((capacity) < 8 ? 8 : (capacity) * 2)

#define GROW_QUEUE(type, pointer, newCount) \
    (type*)reallocate(pointer, \
        sizeof(type) * (newCount))

#define FREE_QUEUE(type, pointer) \
    reallocate(pointer, 0)

int trsfrt_reader_to_lxr(SourceReader* reader, Lexer* lxr);
void print_src_buf(Lexer* lxr);

void* reallocate(void* pointer, size_t new_size);

#endif
