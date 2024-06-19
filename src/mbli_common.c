#include "mbli_common.h"
#include <stdio.h>
#include <string.h>
#include "mbli_token.h"

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

const char *tkntype_to_string(TokenType type) {
    
}

void print_token(Token *tkn) {
    if (!tkn) {
        return;
    }

    if (!tkn->value || tkn->type) {
        return;
    }

    printf("[%s => %s]\n", tkn->value, tkntype_to_string(tkn->type));
}

void print_token_queue(TokenQueue *queue) {
    if (queue->count < QUEUE_MIN_COUNT) {
        return;
    }

    for (size_t i = QUEUE_MIN_COUNT; i <= queue->count; i++) {
        print_token(queue->tokens[i]);
    }
}
