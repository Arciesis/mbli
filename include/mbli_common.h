#ifndef MBLI_COMMON_H
#define MBLI_COMMON_H

#include "lua_source_reader.h"
#include "mbli_lexer.h"

int trsfrt_reader_to_lxr(SourceReader* reader, Lexer* lxr);

#endif
