#ifndef LUA_SOURCE_READER_H
#define LUA_SOURCE_READER_H

#include <stdio.h>

typedef struct {
    FILE* file;
    size_t buf_size;
    char* buf;
} SourceReader;

int check_extension(int argc, const char **argv);
int init_source_code(SourceReader* reader, const char* filename);
void free_source(SourceReader* reader);
int read_src_to_buf(SourceReader* reader);

#endif
