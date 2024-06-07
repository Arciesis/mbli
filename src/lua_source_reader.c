#include "lua_source_reader.h"

#include <asm-generic/errno-base.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mbli_error.h"

/**
 * Check whether the argument passed as input of the program is indeed a lua
 * source file. The program only accept one argument, it cannot interpret multi
 * source code, to do that use lua's lib.
 *
 * @param argc the number of argument passed to the program
 * @param argv the array of arguments
 *
 *  @return int 0 in case of success and a positive int in case of error
 */
int check_extension(int argc, const char** argv) {
    errno = 0;
    // since argv[1] is the first arg of the prog and argv[0] the name of the
    // program.
    if (argc != 2) {
        return EINVAL;
    }

    const char* extension = ".lua";
    size_t ext_len = (size_t)strlen(extension);

    size_t input_len = strlen(argv[1]);
    if (input_len <= ext_len) {
        return EINVAL;
    }

    char prog_name[input_len + 1];
    strcpy(prog_name, argv[1]);

    // Pointer arithmetic to point to the lasts char of the argument of the prog
    const char* file_format = prog_name + input_len - ext_len;
    size_t ff_len = (size_t)strlen(file_format);

    if (ext_len != ff_len) {
        return EINVAL;
    }

    int result = strcmp(file_format, extension);

    if (result != 0) {
        return EINVAL;
    }

    return SUCCESS;
}

// TODO: use the freer function instead of manually do it
/**
 * Initialize the Source Reader.
 *
 * @param reader The SourceReader pointer.
 * @param filename the source code filename to read.
 */
int init_source_code(SourceReader* reader, const char* filename) {
    errno = 0;
    reader->file = fopen(filename, "r");
    if (!reader->file) {
        return ENULLPTR;
    }

    int seek_res = (size_t)fseek(reader->file, 0, SEEK_END);
    if (seek_res) {
        if (errno) {
            printf("ERROR: %s\n", strerror(errno));
            return errno;
        }
        return ESEEK;
    }

    long file_size = ftell(reader->file);
    if (-1L == file_size) {
        if (errno) {
            printf("ERROR: %s\n", strerror(errno));
            return errno;
        }
        return ESEEK;
    }
    reader->buf_size = (size_t)(file_size + 1);

    rewind(reader->file);
    if (errno) {
        printf("ERROR: %s\n", strerror(errno));
        return errno;
    }

    reader->buf = (char*)malloc(sizeof(char*) * reader->buf_size);
    if (!reader->buf) {
        if (errno) {
            printf("ERROR: %s\n", strerror(errno));
            return errno;
        }
        return EMALLOC;
    }

    return SUCCESS;
}

/**
 * Free all resources on the Source reader
 *
 * @param reader the pointer to the SourceReader
 */
void free_source(SourceReader* reader) {
    if (reader) {
        if (reader->file) {
            fclose(reader->file);
        }
        if (reader->buf) {
            free((void*)reader->buf);
        }
        free(reader);
    }
}

/**
 * Fill in the Buffer off of the source code.
 *
 * @param reader the source code reader
 *
 * @return error code or 0 in case of success
 */
int read_src_to_buf(SourceReader* reader) {
    errno = 0;
    if (!reader->file) {
        return ENULLPTR;
    }

    for (size_t i = 0; i < reader->buf_size; i++) {
        int c = fgetc(reader->file);
        if (feof(reader->file)) {
            break;
        }
        reader->buf[i] = c;
    }
    reader->buf[reader->buf_size] = '\0';

    return SUCCESS;
}
