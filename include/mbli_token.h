#ifndef MBLI_TOKEN_H
#define MBLI_TOKEN_H

#include <stdlib.h>

#define QUEUE_MIN_COUNT 1

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
    literals,
    operators,
    delimiters,
    comment,
    whitespace,
} TokenType;

/**
 * @struct representing a Token.
 *
 * @var type represent the type of the token.
 * @var value the string of the token (\0 terminated)
 */
typedef struct {
    TokenType type;
    char *value;
} Token;

typedef struct {
    size_t count;
    size_t capacity;
    Token **tokens;
} TokenQueue;

Token *init_token(void);
int write_token(Token *tkn, const char *value, TokenType type);
void free_token(Token *tkn);

void init_token_queue(TokenQueue *queue);
void enqueue_token(TokenQueue *queue, Token *tkn);
Token *peek_token(TokenQueue *queue);
int is_token_queue_empty(const TokenQueue *queue);
void free_token_queue(TokenQueue *queue);

#endif
