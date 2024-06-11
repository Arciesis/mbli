#include "mbli_token.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mbli_common.h"
#include "mbli_error.h"

/** Initialization function for the token struct,
 *
 * @param tkn the token to be initialized.
 * @param value the input char*.
 * @param type the type of input char (aka TokenType).
 *
 * @return a positive value in cvase of success and 0 otherwise.
 */
int init_token(Token* tkn, const char* value, TokenType type) {
    errno = 0;
    if (!value || !type) {
        return EINVAL;
    }

    size_t value_len = strlen(value);
    tkn->value = (char*)malloc(sizeof(char*) * value_len + sizeof(char*));
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
void free_token(Token* tkn) {
    if (tkn) {
        if (tkn->value) {
            free((void*)tkn->value);
        }
        free(tkn);
    }
}

/** Initialize a queue of tokens
 *
 * @param queue the queue's pointer to initialize.
 */
void init_token_queue(TokenQueue* queue) {
    queue->capacity = 0;
    queue->count = -1;
    queue->tokens = NULL;
}

/** Add a token at the end of the queue.
 *
 * @param queue the queue.
 * @param tkn the token to add to the queue.
 */
void enqueue_token(TokenQueue* queue, Token* tkn) {
    queue->count++;

    if (queue->count >= queue->capacity) {
        size_t new_capacity = GROW_CAPACITY(queue->capacity);
        queue->tokens = GROW_QUEUE(Token*, queue->tokens, new_capacity);
    }

    queue->tokens[queue->count] = tkn;
}

/** delete the first entry of the queue.
 *
 * @param queue the queue.
 *
 * @return 0 in case of failure and a positive value otherwise.
 */
static int dequeue_token(TokenQueue* queue) {
    if (is_token_queue_empty((const TokenQueue*)queue)) {
        return ENOTKN;
    }

    if (queue->count < 1) {
        queue->count--;
        return SUCCESS;
    }

    queue->tokens[0] = queue->tokens[1];
    queue->count--;

    if (queue->count < queue->capacity / 2) {
        // FIXME: Might be an error here but don't know for sure yet!
        GROW_QUEUE(Token*, queue, (queue->count));
    }

    return SUCCESS;
}

/** return the first element of the queue.
 *
 * @param queue the queue.
 *
 * @return the first Token* of the queue.
 */
Token* peek_token(TokenQueue* queue) {
    Token* first_token = queue->tokens[0];
    dequeue_token(queue);
    return first_token;
}

/** Tell whether the queue is empty or not.
 *
 * @param queue the queue.
 *
 * @return 1 if the queue is empty and 0 otherwise.
 */
int is_token_queue_empty(const TokenQueue* queue) { return (!queue->count); }

/** Free the entire queue.
 *
 * @param queue the queue.
 */
void free_token_queue(TokenQueue* queue) {
    while (!is_token_queue_empty(queue)) {
        Token* first_token = peek_token(queue);
        free_token(first_token);
    }
    FREE_QUEUE(TokenQueue, queue);
}
