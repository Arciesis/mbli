#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lua_source_reader.h"

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

    free_source(reader);
    return 0;
}
