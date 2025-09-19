#include <avr/io.h>
#include <util/delay.h>
#include "arduino.h"
#include "screen.h"

#define SCREEN_MOSI D11
#define SCREEN_MISO D12
#define SCREEN_SCK D13
#define SCREEN_CS D6
#define SCREEN_DC D7
#define SCREEN_RES D4

#define SCREEN_DUMMY_CS D10

static void spi_init() {
    COUTPUT(SCREEN_MOSI);
    COUTPUT(SCREEN_SCK);
    COUTPUT(SCREEN_CS);
    COUTPUT(SCREEN_DC);
    COUTPUT(SCREEN_DUMMY_CS); //make SS pin to output so SPI don't switch to slave

    CINPUT(SCREEN_MISO);

    CSET(SCREEN_CS);
    CSET(SCREEN_MOSI);
    CSET(SCREEN_MISO);
    CCLEAR(SCREEN_DC);
    CCLEAR(SCREEN_SCK);

    SPCR = (1 << SPE) | (1 << MSTR);
}

static uint8_t spi_send(uint8_t data) {
    SPDR = data;
    while (!(SPSR & (1 << SPIF)));
    /*
        // Software SPI
        for (uint8_t i = 0; i < 8; i++) {
        if (data & 0x80) {
            CSET(SCREEN_MOSI);
        } else {
            CCLEAR(SCREEN_MOSI);
        }
        CSET(SCREEN_SCK);
        data <<= 1;
        CCLEAR(SCREEN_SCK);
    }*/
}

static inline void oled_enable() {
    CCLEAR(SCREEN_CS);
}

static inline void oled_disable() {
    CSET(SCREEN_CS);
}

void oled_init() {
    spi_init();

    COUTPUT(SCREEN_RES);
    CSET(SCREEN_RES);

    oled_enable();

    CSET(SCREEN_RES);
    _delay_ms(1);
    CCLEAR(SCREEN_RES);
    _delay_ms(10);
    CSET(SCREEN_RES);

    //startup sequence

    CCLEAR(SCREEN_DC);
    spi_send(0xAE);
    spi_send(0xD5);
    spi_send(0x80);
    spi_send(0xA8);
    spi_send(0x3F);
    spi_send(0xD3);
    spi_send(0x00);
    spi_send(0x40);
    //spi_send(0x8D);
    //spi_send(0x14);
    spi_send(0x20);
    spi_send(0x00);//spi_send(0b10);
    spi_send(0xA1);
    spi_send(0xC8);
    spi_send(0xDA);
    spi_send(0x12);
    spi_send(0x81);
    spi_send(0xCF);
    spi_send(0xD9);
    spi_send(0xF1);
    spi_send(0xDB);
    spi_send(0x3C);
    spi_send(0x2E);
    spi_send(0xA4);
    spi_send(0xA6);
    spi_send(0xAF);

    oled_disable();
}

static uint8_t data = 0;

void oled_test() {
    oled_enable();
    CCLEAR(SCREEN_DC);
    spi_send(0x21);
    spi_send(0);
    spi_send(127);
    spi_send(0x22);
    spi_send(0);
    spi_send(7);
    CSET(SCREEN_DC);
    uint8_t block = 1 << data;
    for (int x = 0; x < 128 * 8; x++) {
        spi_send(block);
    }
    oled_disable();
    data++;
    if (data > 7) data = 0;
}