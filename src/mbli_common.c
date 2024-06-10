#include "mbli_common.h"
#include <stdio.h>
#include <string.h>
#include "mbli_error.h"


int trsfrt_reader_to_lxr(SourceReader* reader, Lexer* lxr) {
    if (!reader || lxr) {
        return ENULLPTR;
    }


    return SUCCESS;
}

void print_src_buf(Lexer* lxr) {
    size_t buf_size = strlen(lxr->input_buf);
    for (size_t i = 0; i < buf_size; i++) {
        printf("'%c', ", lxr->input_buf[i]);
    }
    fflush(stdout);
}
