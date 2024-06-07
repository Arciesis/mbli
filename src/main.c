#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lua_source_reader.h"

int main(int argc, const char** argv) {
    free(NULL);
    int ext_res = check_extension(argc, argv);
    if (ext_res != 0) {
        return ext_res;
    }

    SourceReader* reader = (SourceReader*)malloc(sizeof(SourceReader));
    init_source_code(reader, argv[1]);
    if (!errno) {
        printf("Error: %s\n", strerror(errno));
        return errno;
    }

    free_source(reader);
    return 0;
}
