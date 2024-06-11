#include "mbli_lexer.h"

#include <asm-generic/errno-base.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "mbli_error.h"

/** Initialize the lexer
 *
 * @param Lexer* the allocated pointer in which the data must be stored.
 * @param char* the input value of the lexer.
 *
 * @return an error code or 0 in case of success.
 */
int init_lexer(Lexer* lxr, char* value) {
    if (!lxr || !value) {
        return ENULLPTR;
    }

    lxr->length = strlen(value);
    if (!lxr->length) {
        return ENULLPTR;
    }

    lxr->input_buf = value;

    lxr->current_pos = 0;
    lxr->current_char = lxr->input_buf[lxr->current_pos];

    return SUCCESS;
}

/** Lexer's freer function
 *
 * @param lxr to be freed
 */
void free_lexer(Lexer* lxr) {
    if (lxr) {
        free(lxr);
    }
}

/** Move the buffer's lexer position to the next one if possible.
 *
 * @param lxr the lexer context
 *
 * @return an error code or 0 in case oof success.
 */
int forward_buf(Lexer* lxr) {
    if (!lxr) {
        return ENULLPTR;
    }

    lxr->current_pos++;
    if (lxr->current_pos < lxr->length) {
        lxr->current_char = lxr->input_buf[lxr->current_pos];
    } else {
        return EEBUF;
    }

    return SUCCESS;
}

