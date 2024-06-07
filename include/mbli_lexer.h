#ifndef MBLI_LEXER_H
#define MBLI_LEXER_H

#include <stdlib.h>
#include <string.h>

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

/**
 * @enum representing the different token types.
 *
 * @var keyword.
 * @var identifiers.
 * @var operator.
 * @var delimiter.
 * @var comment.
 */
typedef enum {
    keyword,
    identifiers,
    literal,
    operator,
    delimiter,
    comment,
} TokenType;

/**
 * @struct representing a Token.
 *
 * @var type represent the type of the token.
 * @var value the string of the token (\0 terminated)
 */
typedef struct {
    TokenType type;
    char* value;
} Token;

int init_lexer(Lexer* lxr, char* value);
void free_lexer(Lexer* lxr);
int move_on_char(Lexer* lxr);


int init_token(Token* tkn, const char* value, TokenType type);
void free_token(Token* tkn);

#endif
