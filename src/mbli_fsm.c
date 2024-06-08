#include "mbli_fsm.h"
#include <ctype.h>
#include "mbli_error.h"
#include "mbli_lexer.h"

FSM_Event get_next_event(Lexer* lxr) {
    int forward_res = forward_buf(lxr);
    if (ENULLPTR == forward_res) {
        return ev_error;
    } else if (EEBUF == forward_res) {
        return ev_end;
    }

    if (!lxr->current_pos) {
        return ev_init;
    }

    if (isspace(lxr->current_char)) {
        return ev_space;
    }

    if (isdigit(lxr->current_char)) {
        return ev_number;
    }

    if (isalpha(lxr->current_char)) {
        return ev_alpha;
    }

    return ev_any;
}

int run_fsm(Lexer* lxr) {
    FSM_State state = st_start;
    while (state != st_end) {
        FSM_Event event = get_next_event(lxr);
        for (unsigned long i = 0; i < RULESET_COUNT; i++) {
            if ((state == ruleset[i].state) || (st_any == ruleset[i].state)) {
                if ((event == ruleset[i].event) || (ev_any == ruleset[i].event)) {
                    state = (ruleset[i].fn)();
                    break;
                }
            }
        }
    }

    return SUCCESS;
}
