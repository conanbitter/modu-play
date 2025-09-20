#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "ioports.h"
#include "arduino.h"
#include "oled.h"
#include "buttons.h"

const uint8_t button_off[8] PROGMEM = {
    0b00111100,
    0b01000010,
    0b10000001,
    0b10000001,
    0b10000001,
    0b10000001,
    0b01000010,
    0b00111100,
};

const uint8_t button_on[8] PROGMEM = {
    0b00111100,
    0b01000010,
    0b10111101,
    0b10111101,
    0b10111101,
    0b10111101,
    0b01000010,
    0b00111100,
};

volatile uint8_t frames = 0;

void draw_button(int x, int y, int enabled) {
    oled_set_window(x, x + 7, y, y);
    oled_datap(enabled ? button_on : button_off, 8);
}

void timer_init() {
    // Init timer 1 to 60 Hz
    TCCR1B |= (1 << WGM12) | (1 << CS11);
    TIMSK1 |= (1 << OCIE1A);
    OCR1AH = 0x41;
    OCR1AL = 0x1B;
}

ISR(TIMER1_COMPA_vect) {
    frames++;
}

int main(void) {
    //oled_init();
    //btn_init();

    COUTPUT(D13);
    timer_init();
    CCLEAR(D13);

    sei();
    while (1) {
        /*oled_begin();
        draw_button(12, 1, btn_get(0));
        draw_button(5, 2, btn_get(2));
        draw_button(20, 2, btn_get(3));
        draw_button(12, 3, btn_get(1));

        draw_button(52, 2, btn_get(5));
        draw_button(44, 3, btn_get(4));
        oled_end();
        //oled_test();
        _delay_ms(1000.0 / 60.0);*/
        if (frames >= 60) {
            CTOGGLE(D13);
            frames -= 60;
        }
    }

    return 0;
}