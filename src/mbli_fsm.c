#include "mbli_fsm.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "mbli_error.h"
#include "mbli_lexer.h"

/** Initialize a FiniteStateMachine component with all the values that are
 * needed.
 *
 * @param Lexer* a pointer to the lexer in use
 *
 * @return the FiniteStateMachine's pointer
 */
FiniteStateMachine* init_fsm(Lexer* lxr) {
    FiniteStateMachine* fsm = (FiniteStateMachine*)malloc(sizeof(FiniteStateMachine));
    fsm->actual_st = st_start;
    fsm->lxr = lxr;
    fsm->line = 0;
    fsm->column = 0;
    *fsm->lexeme = ' ';
    fsm->lexeme_pos = 0;

    return fsm;
}

/** Freer function of the FiniteSateMachine
 *
 * @param FiniteSateMachine to free.
 */
void free_fsm(FiniteStateMachine* fsm) {
    if (fsm) {
        free(fsm);
    }
}

// TODO: Modify this function, I don't like it as it is !

/** get the next event in a FSM context, aka the next input char.
 *
 * @param Lexer* the lexer i use.
 *
 * @return FSM_Event the event that needs to be process.
 */
FSM_Event get_next_event(Lexer* lxr) {
    if (lxr->current_char == '\n') {
        int forward_res = forward_buf(lxr);
        if (ENULLPTR == forward_res) {
            printf("NULLPTR");
            return ev_error;
        } else if (EEBUF == forward_res) {
            return ev_end;
        }
        return ev_newl;
    }

    if (isspace(lxr->current_char)) {
        int forward_res = forward_buf(lxr);
        if (ENULLPTR == forward_res) {
            printf("NULLPTR");
            return ev_error;
        } else if (EEBUF == forward_res) {
            return ev_end;
        }
        return ev_space;
    }

    if (isdigit(lxr->current_char)) {
        int forward_res = forward_buf(lxr);
        if (ENULLPTR == forward_res) {
            printf("NULLPTR");
            return ev_error;
        } else if (EEBUF == forward_res) {
            return ev_end;
        }
        return ev_number;
    }

    if (isalpha(lxr->current_char)) {
        int forward_res = forward_buf(lxr);
        if (ENULLPTR == forward_res) {
            printf("NULLPTR");
            return ev_error;
        } else if (EEBUF == forward_res) {
            return ev_end;
        }
        return ev_alpha;
    }
    return ev_any;
}

/** handle the error's while running a fsm.
 *
 * @param FiniteStateMachine the fsm in use.
 */
void error(FiniteStateMachine* fsm) {
    printf("Error while processing the file: %ld:%ld", fsm->line, fsm->column);
    fsm->actual_st = st_end;
}

/** fatal error handling while run ing the fsm, if it occurs then there is a bug
 * !
 *
 * @param FiniteStateMachine the fsm in use.
 */
void fatal_fsm_error(FiniteStateMachine* fsm) {
    printf("Should not append !\nThe issue occurred in %ld:%ld", fsm->line, fsm->column);
    fsm->actual_st = st_end;
}

/**
 *
 * @param which_var tell the function if i'ts a new line (2), a space (1), or a
 * regular char (0) in order to set the affected values properly.
 */
void process_char(FiniteStateMachine* fsm, int which_var, const char processing_char) {
    switch (which_var) {
        case 0:
            fsm->lexeme[fsm->lexeme_pos] = processing_char;
            fsm->lexeme_pos++;
            fsm->column++;
            break;
        case 1:
            fsm->lexeme_pos = 0;
            fsm->lexeme[fsm->lexeme_pos] = processing_char;
            fsm->lexeme_pos = 1;
            fsm->line++;
            fsm->column = 0;
            break;
        case 2:
            fsm->lexeme[fsm->lexeme_pos] = '\0';
            fsm->lexeme_pos = 0;
            fsm->column = 0;
            fsm->line++;
            break;
        default:
            printf("Programming error!");
            exit(EXIT_FAILURE);
    }
}

/** handle all type of number event (aka: input).
 *
 * @param FiniteStaeMachine in use.
 */
void handle_number(FiniteStateMachine* fsm) {
    switch (fsm->actual_st) {
        case st_start:
            process_char(fsm, 0, (const char)fsm->lxr->current_pos);
            fsm->actual_st = st_innumber;
            break;
        case st_innumber:
            process_char(fsm, 0, (const char)fsm->lxr->current_pos);
            fsm->actual_st = st_innumber;
            break;
        case st_inidentifier:
            process_char(fsm, 0, (const char)fsm->lxr->current_pos);
            fsm->actual_st = st_inidentifier;
            break;
        case st_inspace:
            process_char(fsm, 0, (const char)fsm->lxr->current_pos);
            fsm->actual_st = st_innumber;
            break;
        case st_inkeyword:
            fsm->actual_st = st_any;
            break;
        case st_newl:
            process_char(fsm, 2, (const char)fsm->lxr->current_pos);
            fsm->actual_st = st_innumber;
            break;
        case st_any:
            printf("State not taken to account right now !\n");
            fsm->actual_st = st_end;
            break;
        case st_end:
            printf("Error, that should not happen !\n");
            fsm->actual_st = st_end;
            break;
        default:
            fsm->actual_st = st_any;
            break;
    }
}

/** handle all type of alphanumerical event (aka input char),
 *
 * @param FiniteStateMachine the fsm in use.
 */
void handle_alpha(FiniteStateMachine* fsm) {
    switch (fsm->actual_st) {
        case st_start:

            break;
        case st_innumber:

            break;
        case st_inidentifier:

            break;
        case st_inspace:

            break;
        case st_inkeyword:

            break;
        case st_newl:

            break;
        case st_any:

            break;
        case st_end:

            break;
        default:
            fsm->actual_st = st_any;
            break;
    }
}

/** Handle all spaces event (aka input char).
 *
 * @param FiniteStateMachine in use/
 */
void handle_space(FiniteStateMachine* fsm) {
    switch (fsm->actual_st) {
        case st_start:
            process_char(fsm, 1, (const char)fsm->lxr->current_pos);
            fsm->actual_st = st_inspace;
            break;
        case st_innumber:
            fsm->lexeme[fsm->lexeme_pos] = '\0';
            printf("%s\n", fsm->lexeme);  // Tokenisation goes here.
            fsm->lexeme_pos = 0;
            fsm->column++;
            fsm->actual_st = st_inspace;
            break;
        case st_inidentifier:
            fsm->lexeme[fsm->lexeme_pos] = '\0';
            printf("%s\n", fsm->lexeme);  // Tokenisation goes here.
            fsm->lexeme_pos = 0;
            fsm->column++;
            fsm->actual_st = st_inspace;
            break;
        case st_inspace:
            process_char(fsm, 1, (const char)fsm->lxr->current_pos);
            break;
        case st_inkeyword:
            fsm->lexeme[fsm->lexeme_pos] = '\0';
            printf("%s\n", fsm->lexeme);  // Tokenisation goes here.
            fsm->lexeme_pos = 0;
            fsm->column++;
            fsm->actual_st = st_inspace;
            break;
        case st_newl:
            process_char(fsm, 1, (const char)fsm->lxr->current_pos);
            fsm->actual_st = st_inspace;
            break;
        case st_any:
            printf("State not taken to account right now !\n");
            fsm->actual_st = st_end;
            break;
        case st_end:
            printf("ERROR: that should not happen !\n");
            fsm->actual_st = st_end;
            break;
        default:
            fsm->actual_st = st_any;
            break;
    }
}

/** handle the end of the file event (aka input char).
 *
 * @param FiniteStateMachine in use.
 */
void handle_end(FiniteStateMachine* fsm) {
    fsm->lexeme[0] = '\0';
    fsm->actual_st = st_end;
}

/** handle each new line event (aka input char).
 *
 * @param FiniteStateMachine in use.
 */
void handle_newl(FiniteStateMachine* fsm) {
    switch (fsm->actual_st) {
        case st_start:
            fsm->line++;
            fsm->actual_st = st_newl;
            break;
        case st_innumber:
            process_char(fsm, 2, (const char)fsm->lxr->current_char);
            fsm->actual_st = st_newl;
            break;
        case st_inidentifier:
            process_char(fsm, 2, (const char)fsm->lxr->current_char);
            fsm->actual_st = st_newl;
            break;
        case st_inspace:
            process_char(fsm, 2, (const char)fsm->lxr->current_char);
            fsm->actual_st = st_newl;
            break;
        case st_inkeyword:
            process_char(fsm, 2, (const char)fsm->lxr->current_char);
            fsm->actual_st = st_newl;
            break;
        case st_newl:
            process_char(fsm, 2, (const char)fsm->lxr->current_char);
            fsm->actual_st = st_newl;
            break;
        case st_any:
            printf("ERROR: should not happen !");
            fsm->actual_st = st_end;
            break;
        case st_end:
            printf("ERROR: permutation should not happen !");
            fsm->actual_st = st_end;
            break;
        default:
            printf("ERROR: permutation should not happen ! Returning any");
            fsm->actual_st = st_any;
            break;
    }
}

/**
 * Represent each permutation of state and event
 */
FSM_Transition ruleset[] = {
    // Start state transitions
    {st_start, ev_number, &handle_number},
    {st_start, ev_alpha, &handle_alpha},
    {st_start, ev_space, &handle_space},
    {st_start, ev_newl, &handle_newl},
    {st_start, ev_end, &handle_end},
    {st_start, ev_any, &fatal_fsm_error},
    {st_start, ev_error, &error},

    // In number state transitions
    {st_innumber, ev_number, &handle_number},
    {st_innumber, ev_alpha, &handle_alpha},
    {st_innumber, ev_space, &handle_space},
    {st_innumber, ev_newl, &handle_newl},
    {st_innumber, ev_end, &handle_end},
    {st_innumber, ev_any, &fatal_fsm_error},
    {st_innumber, ev_error, &error},

    // In Identifier state transition
    {st_inidentifier, ev_number, &handle_number},
    {st_inidentifier, ev_alpha, &handle_alpha},
    {st_inidentifier, ev_space, &handle_space},
    {st_inidentifier, ev_newl, &handle_newl},
    {st_inidentifier, ev_end, &handle_end},
    {st_inidentifier, ev_any, &fatal_fsm_error},
    {st_inidentifier, ev_error, &error},

    // In keyword state transitions
    {st_inkeyword, ev_number, &handle_number},
    {st_inkeyword, ev_alpha, &handle_alpha},
    {st_inkeyword, ev_space, &handle_space},
    {st_inkeyword, ev_newl, &handle_newl},
    {st_inkeyword, ev_end, &handle_end},
    {st_inkeyword, ev_any, &fatal_fsm_error},
    {st_inkeyword, ev_error, &error},

    // In space state transitions
    {st_inspace, ev_number, &handle_number},
    {st_inspace, ev_alpha, &handle_alpha},
    {st_inspace, ev_space, &handle_space},
    {st_inspace, ev_newl, &handle_newl},
    {st_inspace, ev_end, &handle_end},
    {st_inspace, ev_any, &fatal_fsm_error},
    {st_inspace, ev_error, &error},

    // Any state transitions
    {st_any, ev_number, &handle_number},
    {st_any, ev_alpha, &handle_alpha},
    {st_any, ev_space, &handle_space},
    {st_any, ev_newl, &handle_newl},
    {st_any, ev_end, &handle_end},
    {st_any, ev_any, &fatal_fsm_error},
    {st_any, ev_error, &error},

    // End state transitions (might just be terminal, no real transitions
    // needed)
    {st_end, ev_number, &fatal_fsm_error},
    {st_end, ev_alpha, &fatal_fsm_error},
    {st_end, ev_space, &fatal_fsm_error},
    {st_end, ev_newl, &handle_newl},
    {st_end, ev_end, &fatal_fsm_error},
    {st_end, ev_any, &fatal_fsm_error},
    {st_end, ev_error, &fatal_fsm_error},
};

/** The actual loop that represent the FiniteStateMachine algorithm.
 * it iterate through the ruleset searching for a match, in the case it run the
 * associated function.
 *
 * @param Lexer* the context in which the fsm must be run.
 */
void run_fsm(Lexer* lxr) {
    FiniteStateMachine* fsm = init_fsm(lxr);
    while (st_end != fsm->actual_st) {
        FSM_Event event = get_next_event(lxr);
        for (unsigned long i = 0; i < RULESET_COUNT; i++) {
            if ((fsm->actual_st == ruleset[i].state) || (st_any == ruleset[i].state)) {
                if ((event == ruleset[i].event) || (ev_any == ruleset[i].event)) {
                    (ruleset[i].fn)(fsm);
                    break;
                }
            }
        }
    }

    free_fsm(fsm);
}
