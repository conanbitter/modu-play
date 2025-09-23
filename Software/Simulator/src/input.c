#include "moduplay.h"

static uint8_t buttons_pressed[9];
static uint8_t buttons_just_pressed[9];
static uint8_t buttons_just_released[9];

void _mpc_just_clear() {
    memset(buttons_just_pressed, 0, sizeof(buttons_just_pressed));
    memset(buttons_just_released, 0, sizeof(buttons_just_released));
}

void _mpc_buttons_init() {
    memset(buttons_pressed, 0, sizeof(buttons_pressed));
    _mpc_just_clear();
}

void _mpc_button_down(int button) {
    buttons_pressed[button] = 1;
    buttons_just_pressed[button] = 1;
}

void _mpc_button_up(int button) {
    buttons_pressed[button] = 0;
    buttons_just_released[button] = 1;
}

bool mp_is_pressed(uint8_t button) {
    return buttons_pressed[button] == 1;
}

bool mp_just_pressed(uint8_t button) {
    return buttons_just_pressed[button] == 1;
}

bool mp_just_released(uint8_t button) {
    return buttons_just_released[button] == 1;
}