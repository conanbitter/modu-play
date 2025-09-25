#include "moduplay.h"
#include "mpcore.h"

uint8_t canvas[SCREEN_WIDTH * SCREEN_LINES];

void mp_clear() {
    memset(canvas, 0x00, sizeof(canvas));
}

void mp_putpixel(uint8_t x, uint8_t y, uint8_t color) {
    if (color == 0) {
        canvas[x + (y / 8) * SCREEN_WIDTH] &= ~(1 << (y % 8));
    } else {
        canvas[x + (y / 8) * SCREEN_WIDTH] |= 1 << (y % 8);
    }
}

void draw_simple(int x, int line, const uint8_t* image, int width, int height) {
    for (int yp = line;yp < line + height;yp++) {
        for (int xp = x;xp < x + width;xp++) {
            canvas[xp + yp * SCREEN_WIDTH] = image[xp - x + (yp - line) * width];
        }
    }
}

static void apply1to2(uint8_t* dst_top, uint8_t* dst_bottom, const uint8_t src, const uint8_t offset) {
    uint8_t mask_top = (1 << offset) - 1;
    uint8_t mask_bottom = ~mask_top;
    uint8_t shift_top = offset;
    uint8_t shift_bottom = 8 - offset;

    *dst_top = (*dst_top & mask_top) | (src << shift_top);
    *dst_bottom = (*dst_bottom & mask_bottom) | (src >> shift_bottom);
}

static void apply_top(uint8_t* dst_top, const uint8_t src, const uint8_t offset) {
    uint8_t mask = (1 << offset) - 1;
    uint8_t shift = offset;

    *dst_top = (*dst_top & mask) | (src << shift);
}

static uint8_t apply_bottom(uint8_t* dst_bottom, const uint8_t src, const uint8_t offset) {
    uint8_t mask = ~((1 << offset) - 1);
    uint8_t shift = 8 - offset;

    *dst_bottom = (*dst_bottom & mask) | (src >> shift);
}

static uint8_t apply2to1(const uint8_t src_top, const uint8_t src_bottom, const uint8_t offset) {
    uint8_t shift_top = 8 - offset;
    uint8_t shift_bottom = offset;

    return (src_top >> shift_top) | (src_bottom << shift_bottom);
}

void draw_oneline(int x, int line, const uint8_t* image, int width, int offset) {
    for (int xp = x;xp < x + width;xp++) {
        apply1to2(
            canvas + xp + line * SCREEN_WIDTH,
            canvas + xp + (line + 1) * SCREEN_WIDTH,
            image[xp - x],
            offset
        );
    }
}

void draw_multiline(int x, int line, const uint8_t* image, int width, int height, int offset) {
    int top_line = line;
    int bottom_line = line + height;
    for (int xp = x;xp < x + width;xp++) {
        apply_top(canvas + xp + top_line * SCREEN_WIDTH, image[xp - x], offset);

        for (int yp = top_line + 1;yp < bottom_line;yp++) {
            canvas[xp + yp * SCREEN_WIDTH] = apply2to1(
                image[xp - x + (yp - top_line - 1) * width],
                image[xp - x + (yp - top_line) * width],
                offset
            );
        }

        apply_bottom(canvas + xp + bottom_line * SCREEN_WIDTH, image[xp - x + (height - 1) * width], offset);
    }
}

void mp_draw(int x, int y, const uint8_t* image) {
    uint8_t width = image[0];
    uint8_t height = image[1];

    int line = y / 8;
    uint8_t offset = y % 8;

    if (offset == 0) {
        draw_simple(x, line, image + 2, width, height);
    } else if (height == 1) {
        draw_oneline(x, line, image + 2, width, offset);
    } else {
        draw_multiline(x, line, image + 2, width, height, offset);
    }
}