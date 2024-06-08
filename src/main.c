#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lua_source_reader.h"
#include "mbli_error.h"
#include "mbli_lexer.h"

int main(int argc, const char** argv) {
    int ext_res = check_extension(argc, argv);
    if (ext_res) {
        if (errno) {
            printf("ERROR: %s\n", strerror(errno));
        }
        return ext_res;
    }

    SourceReader* reader = (SourceReader*)malloc(sizeof(SourceReader));
    int init_source_res = init_source_code(reader, argv[1]);
    if (init_source_res) {
        free_source(reader);
        if (errno) {
            printf("Error: %s\n", strerror(errno));
            return errno;
        }
        return init_source_res;
    }

    int read_src_res = read_src_to_buf(reader);
    if (read_src_res) {
        free_source(reader);
        if (errno) {
            printf("Error: %s\n", strerror(errno));
            return errno;
        }
        return read_src_res;
    }

    Lexer* lxr = (Lexer*)malloc(sizeof(Lexer));
    int lxr_init_res = init_lexer(lxr, reader->buf);
    if (lxr_init_res) {
        return lxr_init_res;
    }

    /* char lexeme[256] = ""; */
    /* size_t cpt_char = 0; */
    /* int forward_res = 0; */
    /* while (lxr->current_char != '\0') { */
        /* if (isspace(lxr->current_char)) { */
            /* lexeme[cpt_char] = '\0'; */
            /* // printf("%s\n", lexeme);  // Tokenzie here ! */
            /* cpt_char = 0; */
            /* forward_res = forward_buf(lxr); */
            /* if (ENULLPTR == forward_res) { */
                /* return forward_res; */
            /* } */
            /* if (EEBUF == forward_res) { */
                /* break; */
            /* } */
            /* continue; */
        /* } */
        /* lexeme[cpt_char] = lxr->current_char; */
        /* cpt_char++; */
        /* forward_res = forward_buf(lxr); */
        /* if (ENULLPTR == forward_res) { */
            /* return forward_res; */
        /* } */
        /* if (EEBUF == forward_res) { */
            /* break; */
        /* } */
    /* } */

    free_source(reader);
    free_lexer(lxr);
    return SUCCESS;
}
