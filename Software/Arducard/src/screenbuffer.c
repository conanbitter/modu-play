#include "screenbuffer.h"

static uint8_t buffer[128 * 8];

void sb_init() {
    memset(buffer, 0, sizeof(buffer));
}

void sb_putpixel(int x, int y, int color) {
    if (color == 0) {
        buffer[x + (y / 8) * 128] &= ~(1 << (y % 8));
    } else {
        buffer[x + (y / 8) * 128] |= 1 << (y % 8);
    }
}

uint8_t* sb_getpointer() {
    return buffer;
}