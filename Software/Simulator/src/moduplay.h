#ifndef _MODUPLAY_H_
#define _MODUPLAY_H_

#include <stdint.h>
#include <stdbool.h>

#define SCREEN_WIDTH (128)
#define SCREEN_HEIGHT (64)
#define BLACK (0)
#define WHITE (1)

#define UP_BUTTON (0)
#define DOWN_BUTTON (1)
#define LEFT_BUTTON (2)
#define RIGHT_BUTTON (3)
#define A_BUTTON (4)
#define B_BUTTON (5)
#define X_BUTTON (6)
#define Y_BUTTON (7)
#define MENU_BUTTON (8)

void mp_begin();
void mp_display();
void mp_clear();
void mp_putpixel(uint8_t x, uint8_t y, uint8_t color);
bool mp_is_pressed(uint8_t button);
bool mp_just_pressed(uint8_t button);
bool mp_just_released(uint8_t button);

bool _mpc_process_events();
void _mpc_present();
void _mpc_finish();
void _mpc_just_clear();

#define MPCORE_MAIN                         \
int main(int argc, char** argv) {           \
    mp_begin();                             \
    setup();                                \
    bool is_running = true;                 \
    while (is_running) {                    \
        _mpc_just_clear();                  \
        is_running = _mpc_process_events(); \
        loop();                             \
        _mpc_present();                     \
    }                                       \
    _mpc_finish();                          \
    return 0;                               \
}                                           \

#endif