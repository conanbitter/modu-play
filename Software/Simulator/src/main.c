#include "moduplay.h"
#include "mpcore.h"
#include "assets.h"

int x = 10;
int y = 8;

void setup() {
    //draw_simple(x, y, IMG_TEST_PATTERN + 2, 8, 1);
}

void loop() {
    int newx = x;
    int newy = y;
    if (mp_just_pressed(UP_BUTTON) && newy > 0) newy--;
    if (mp_just_pressed(DOWN_BUTTON) && newy < SCREEN_HEIGHT - 1) newy++;
    if (mp_just_pressed(LEFT_BUTTON) && newx > 0) newx--;
    if (mp_just_pressed(RIGHT_BUTTON) && newx < SCREEN_WIDTH) newx++;
    if (newx != x || newy != y) {
        x = newx;
        y = newy;
        mp_clear();
        mp_draw(x, y, IMG_LOGO_FRAME);
        //draw_simple(x, y, IMG_TEST_PATTERN + 2, 8, 1);
        //int line = y / 8;
        //int offset = y % 8;
        //draw_oneline(x, line, IMG_TEST_PATTERN + 2, 8, offset);
        //draw_multiline(x, line, IMG_BALLOON + 2, 16, 2, offset);
    }
    mp_display();
}

MPCORE_MAIN