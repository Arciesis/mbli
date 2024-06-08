#include "mbli_lexer.h"

#include <asm-generic/errno-base.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mbli_error.h"

int init_lexer(Lexer* lxr, char* value) {
    if (!lxr || !value) {
        return ENULLPTR;
    }

    lxr->length = strlen(value);
    if (!lxr->length) {
        return ENULLPTR;
    }

    lxr->input_buf = value;

    lxr->current_pos = 0;
    lxr->current_char = lxr->input_buf[lxr->current_pos];

    return SUCCESS;
}

void free_lexer(Lexer* lxr) {
    if (lxr) {
        free(lxr);
    }
}

int forward_buf(Lexer* lxr) {
    if (!lxr) {
        return ENULLPTR;
    }

    lxr->current_pos++;
    if (lxr->current_pos < lxr->length) {
        lxr->current_char = lxr->input_buf[lxr->current_pos];
    } else {
        return EEBUF;
    }

    return SUCCESS;
}


int init_token(Token* tkn, const char* value, TokenType type) {
    errno = 0;
    if (!tkn || !value || !type) {
        errno = EINVAL;
        return errno;
    }

    size_t value_len = strlen(value);
    tkn->value = (char*)malloc(sizeof(char*) * value_len + sizeof(char*));
    if (errno) {
        return errno;
    }

    tkn->value = strcpy(tkn->value, value);

    return SUCCESS;
}

void free_token(Token* tkn) {
    if (tkn) {
        if (tkn->value) {
            free((void*)tkn->value);
        }
        free(tkn);
    }
}
