#ifndef MBLI_FSM_H
#define MBLI_FSM_H

#include "mbli_lexer.h"
typedef enum {
	st_start,
	st_any,
	st_innumber,
	st_inkeyword,
	st_space,
	st_end,
} FSM_State;

typedef enum {
	ev_init,
	ev_number,
	ev_alpha,
	ev_space,
    ev_end,
	ev_any,
	ev_error,
} FSM_Event;

typedef struct {
	FSM_State state;
	FSM_Event event;
	FSM_State (*fn)(void);
} FSM_Transition;

FSM_State initialize_fsm(void);
FSM_State error(void);
FSM_State fatal_fsm_error(void);
FSM_State now_space(void);
FSM_State now_number(void);
FSM_State now_alpha(void);
FSM_State reach_end(void);

FSM_Transition ruleset[] = {
	{st_start, ev_init, &initialize_fsm},
    {st_start, ev_space, &now_space},
    {st_start, ev_number, &now_number},
    {st_start, ev_alpha, &now_alpha},
    {st_any, ev_end, &reach_end},
	{st_any, ev_error, &error},
	{st_any, ev_any, &fatal_fsm_error},
};

#define RULESET_COUNT (sizeof(ruleset)/sizeof(*ruleset))

int run_fsm(Lexer* lxr);
FSM_Event get_next_event(Lexer* lxr);


#endif
