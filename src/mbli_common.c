#include "mbli_common.h"
#include <stdio.h>
#include <string.h>

//TODO: must be in a debug file !
void print_src_buf(Lexer* lxr) {
    size_t buf_size = strlen(lxr->input_buf);
    for (size_t i = 0; i < buf_size; i++) {
        printf("'%c', ", lxr->input_buf[i]);
    }
    fflush(stdout);
}


void* reallocate(void* pointer, size_t new_size) {
    if (new_size == 0) {
        free(pointer);
        return NULL;
    }

    void* result = realloc(pointer, new_size);
    if (result == NULL) exit(1);
    return result;
}
