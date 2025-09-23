#include "moduplay.h"
#include "mpcore.h"

uint8_t canvas[SCREEN_WIDTH * SCREEN_LINES];

void mp_clear() {
    memset(canvas, 0x00, sizeof(canvas));
}

void mp_putpixel(uint8_t x, uint8_t y, uint8_t color) {
    if (color == 0) {
        canvas[x + (y / 8) * 128] &= ~(1 << (y % 8));
    } else {
        canvas[x + (y / 8) * 128] |= 1 << (y % 8);
    }
}