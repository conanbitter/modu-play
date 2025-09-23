#include "moduplay.h"
#include "mpcore.h"

void setup() {
    mp_putpixel(10, 10, WHITE);
}

void loop() {
    mp_display();
}

MPCORE_MAIN