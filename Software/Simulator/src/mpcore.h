#ifndef _MPCORE_H_
#define _MPCORE_H_

#include <stdint.h>
#include <stdbool.h>

#define SCREEN_LINES (8)

extern uint8_t canvas[];

void _mpc_buttons_init();
void _mpc_button_down(int button);
void _mpc_button_up(int button);

#endif