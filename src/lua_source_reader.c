#include "lua_source_reader.h"

#include <asm-generic/errno-base.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/**
 * Check whether the argument passed as input of the program is indeed a lua source file.
 * The program only accept one argument, it cannot interpret multi source code, to do that use lua's lib.
 *
 * @param argc the number of argument passed to the program
 * @param argv the array of arguments
 *
 *  @return int 0 in case of success and a positive int in case of error
 */
int check_extension(int argc, const char** argv) {
    // since argv[1] is the first arg of the prog and argv[0] the name of the program.
    if (argc != 2) {
        return EINVAL;
    }

    const char* extension = ".lua";
    size_t ext_len = (size_t)strlen(extension);

    size_t input_len = strlen(argv[1]);
    if (input_len <= ext_len) {
        return EINVAL;
    }

    char prog_name[input_len];
    strcpy(prog_name, argv[1]);

    // Pointer arithmetic to point to the lasts char of the argument of the prog
    const char* file_format = prog_name + input_len - ext_len;
    size_t ff_len = (size_t)strlen(file_format);

    if (ext_len != ff_len) {
        return EINVAL;
    }

    int result = strcmp(file_format, extension);

    if (result == 0) {
        printf("result: %d, file format is: %s", result, file_format);
    } else {
        return EINVAL;
    }

    return 0;
}
