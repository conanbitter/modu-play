#include "moduplay.h"
#include "mpcore.h"

int x = 10;
int y = 10;

void setup() {
    mp_putpixel(x, y, WHITE);
}

void loop() {
    int newx = x;
    int newy = y;
    if (mp_just_pressed(UP_BUTTON) && newy > 0) newy--;
    if (mp_just_pressed(DOWN_BUTTON) && newy < SCREEN_HEIGHT - 1) newy++;
    if (mp_just_pressed(LEFT_BUTTON) && newx > 0) newx--;
    if (mp_just_pressed(RIGHT_BUTTON) && newx < SCREEN_WIDTH) newx++;
    if (newx != x || newy != y) {
        mp_putpixel(x, y, BLACK);
        mp_putpixel(newx, newy, WHITE);
        x = newx;
        y = newy;
    }
    mp_display();
}

MPCORE_MAIN