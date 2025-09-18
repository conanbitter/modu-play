#include <avr/io.h>
#include <util/delay.h>
#include "ioports.h"
#include "arduino.h"
#include "screen.h"

int main(void) {
    oled_init();

    while (1) {
        oled_test();
        _delay_ms(1000);
    }

    return 0;
}