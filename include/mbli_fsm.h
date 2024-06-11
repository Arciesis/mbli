#ifndef MBLI_FSM_H
#define MBLI_FSM_H
#define MAX_LEXEME_BUF_SIZE 512

#include "mbli_lexer.h"

typedef enum {
    st_start,
    st_innumber,
    st_inkeyword,
    st_inspace,
    st_newl,
    st_inidentifier,
    st_any,
    st_end,
} FSM_State;

typedef enum {
    ev_number,
    ev_alpha,
    ev_space,
    ev_newl,
    ev_end,
    ev_any,
    ev_error,
} FSM_Event;

typedef struct {
    FSM_State actual_st;
    char lexeme[512];
    Lexer* lxr;
    size_t line;
    size_t column;
    size_t lexeme_pos;
    // TODO: Maybe add a queue here for the token implementation !
} FiniteStateMachine;

typedef void (*stateFunction)(FiniteStateMachine* fsm);

typedef struct {
    FSM_State state;
    FSM_Event event;
    stateFunction fn;
} FSM_Transition;

void process_char(FiniteStateMachine* fsm, int which_var, const char processing_char);

void handle_number(FiniteStateMachine* fsm);
void handle_alpha(FiniteStateMachine* fsm);
void handle_space(FiniteStateMachine* fsm);
void handle_newl(FiniteStateMachine* fsm);
void handle_end(FiniteStateMachine* fsm);
void error(FiniteStateMachine* fsm);
void fatal_fsm_error(FiniteStateMachine* fsm);

extern FSM_Transition ruleset[];

#define RULESET_COUNT (sizeof(ruleset) / sizeof(*ruleset))

void run_fsm(Lexer* lxr);
FSM_Event get_next_event(Lexer* lxr);
FiniteStateMachine* init_fsm(Lexer* lxr);
void free_fsm(FiniteStateMachine* fsm);

#endif
