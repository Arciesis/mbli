#ifndef MBLI_LEXER_H
#define MBLI_LEXER_H

#include <stdlib.h>

/**
 * @struct representing the lexer process.
 *
 * @var input_buf the line which is being process.
 * @var current_pos the current position on the input_line.
 * @var current_char the value of the current char.
 * @var length the length of the input_buf containing an \0 char at the end.
 */
typedef struct {
    char current_char;
    size_t current_pos;
    size_t length;
    char* input_buf;
} Lexer;



int init_lexer(Lexer* lxr, char* value);
void free_lexer(Lexer* lxr);
int forward_buf(Lexer* lxr);



#endif
