#ifndef _MODUPLAY_H_
#define _MODUPLAY_H_

#include <stdint.h>
#include <stdbool.h>

#define SCREEN_WIDTH (128)
#define SCREEN_HEIGHT (64)
#define BLACK (0)
#define WHITE (1)

void mp_begin();
void mp_display();
void mp_clear();
void mp_putpixel(uint8_t x, uint8_t y, uint8_t color);

bool _mpc_process_events();
void _mpc_present();
void _mpc_finish();

#define MPCORE_MAIN                 \
int main(int argc, char** argv) {   \
    mp_begin();                     \
    setup();                        \
    while (_mpc_process_events()) { \
        loop();                     \
        _mpc_present();             \
    }                               \
    _mpc_finish();                  \
    return 0;                       \
}

#endif