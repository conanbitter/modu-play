#include <avr/io.h>
#include <util/delay.h>
#include "ioports.h"
#include "arduino.h"

int num;

#define LED D13

void blink_number(int count) {
    for (int i = 0; i < count; i++) {
        CSET(LED);
        _delay_ms(100);
        CCLEAR(LED);
        _delay_ms(200);
    }
}

int main(void) {
    COUTPUT(LED);
    CCLEAR(LED);
    num = 1;
    while (1) {
        blink_number(num);
        _delay_ms(700);
        num++;
        if (num > 8) num = 1;
    }

    return 0;
}