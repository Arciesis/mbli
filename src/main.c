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
    
    while (lxr->current_char != '\0') {
        //TODO: Tokenization logic goes here
        printf("%c", lxr->current_char);
        int move_res = move_on_char(lxr);
        if (ENULLPTR == move_res) {
            return move_res;
        }

        if (EEBUF == move_res) {
            break;
        }
    }

    free_source(reader);
    free_lexer(lxr);
    return SUCCESS;
}
