#include "mbli_token.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mbli_common.h"
#include "mbli_error.h"

/** Initialize a token.
 * Since a comment is not takken into account it's the initial state of the token.
 */
Token *init_token(void) {
    Token *tkn = (Token *)malloc(sizeof(Token));
    tkn->type = comment;
    tkn->value = NULL;
    return tkn;

}

/** write a token.
 *
 * @param tkn the token to be initialized.
 * @param value the input char*.
 * @param type the type of input char (aka TokenType).
 *
 * @return a positive value in cvase of success and 0 otherwise.
 */
int write_token(Token *tkn, const char *value, TokenType type) {
    errno = 0;
    // FIXME: Do I need toc heck type ?
    if (!value || !type) {
        return EINVAL;
    }

    size_t value_len = strlen(value);
    tkn->value = (char *)malloc(sizeof(char *) * value_len + sizeof(char *));
    if (errno) {
        return errno;
    }

    tkn->value = strcpy(tkn->value, value);
    tkn->type = type;

    return SUCCESS;
}

/** Freer function for the token struct
 *
 * @param tkn the token to free.
 */
void free_token(Token *tkn) {
    if (tkn) {
        if (tkn->value) {
            free((void *)tkn->value);
        }
        free(tkn);
    }
}

/** Initialize a queue of tokens
 *
 * @param queue the queue's pointer to initialize.
 */
void init_token_queue(TokenQueue *queue) {
    queue->capacity = 0;
    queue->count = 0;
    queue->tokens = NULL;
}

/** Add a token at the end of the queue.
 *
 * @param queue the queue.
 * @param tkn the token to add to the queue.
 */
void enqueue_token(TokenQueue *queue, Token *tkn) {
    queue->count++;

    // TODO: Opti: > || >= ???
    if (queue->count >= queue->capacity) {
        size_t new_capacity = GROW_CAPACITY(queue->capacity);
        queue->tokens = GROW_QUEUE(Token *, queue->tokens, new_capacity);
    }

    queue->tokens[queue->count] = tkn;
}

/** delete the first entry of the queue.
 *
 * @param queue the queue.
 *
 * @return 0 in case of failure and a positive value otherwise.
 */
static int dequeue_token(TokenQueue *queue) {
    if (is_token_queue_empty((const TokenQueue *)queue)) {
        return ENOTKN;
    }

    if (1 == queue->count) {
        queue->count--;
        return SUCCESS;
    }

    for (size_t i = QUEUE_MIN_COUNT; i < queue->count; i++) {
        queue->tokens[i] = queue->tokens[i + 1];
    }

    queue->count--;

    // if the allocate space is larger than 2 times of the taken space then reduce it by a factor 2
    if (queue->count < queue->capacity / 2) {
        GROW_QUEUE(Token *, queue, (queue->count));
    }

    return SUCCESS;
}

/** return the first element of the queue.
 *
 * @param queue the queue.
 *
 * @return the first Token* of the queue.
 */
Token *peek_token(TokenQueue *queue) {
    if (queue->count >= QUEUE_MIN_COUNT) {
        Token *first_token = queue->tokens[QUEUE_MIN_COUNT];
        dequeue_token(queue);
        return first_token;
    }

    return NULL;
}

/** Tell whether the queue is empty or not.
 *
 * @param queue the queue.
 *
 * @return 1 if the queue is empty and 0 otherwise.
 */
int is_token_queue_empty(const TokenQueue *queue) { return (!queue->count); }

/** Free the entire queue.
 *
 * @param queue the queue.
 */
void free_token_queue(TokenQueue *queue) {
    while (!is_token_queue_empty(queue)) {
        Token *first_token = peek_token(queue);
        free_token(first_token);
    }
    FREE_QUEUE(TokenQueue, queue);
    init_token_queue(queue);
}
