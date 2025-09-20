#include <avr/io.h>
#include <util/delay.h>
#include "arduino.h"
#include "oled.h"

// OLED SSD1309 driver

#define SCREEN_MOSI D11
#define SCREEN_MISO D12
#define SCREEN_SCK D13
#define SCREEN_CS D6
#define SCREEN_DC D7
#define SCREEN_RES D4

#define SCREEN_DUMMY_CS D10

static const size_t oled_startup_sequence_size = 23;

static const uint8_t oled_startup_sequence[24] PROGMEM = {
    0xAE,       // display off
    0xD5, 0x80, // clock
    0xA8, 0x3F, //
    0xD3, 0x00, // offset
    0x40,       // start line
    0x20, 0x00, // adressing mode = horizontal
    0xA1,       //
    0xC8,       //
    0xDA, 0x12, //
    0x81, 0xCF, // contrast
    0xD9, 0xF1, //
    0xDB, 0x3C, //
    0x2E,       // scroll disable
    0xA4,       //
    0xA6,       // inverse off
    0xAF,       // display on
};

static void spi_init() {
    COUTPUT(SCREEN_MOSI);
    COUTPUT(SCREEN_SCK);
    COUTPUT(SCREEN_CS);
    COUTPUT(SCREEN_DC);
    COUTPUT(SCREEN_DUMMY_CS); //make SS pin to output so SPI don't autoswitch to slave

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

static  __attribute__((always_inline)) inline void oled_select() {
    CCLEAR(SCREEN_CS);
}

static  __attribute__((always_inline)) inline void oled_deselect() {
    CSET(SCREEN_CS);
}

static __attribute__((always_inline)) inline void oled_start_com() {
    CCLEAR(SCREEN_DC);
}

static __attribute__((always_inline)) inline void oled_start_data() {
    CSET(SCREEN_DC);
}

static void oled_sendp(PGM_P values, const size_t count) {
    for (size_t i = 0;i < count;i++) {
        spi_send(pgm_read_byte(values));
        values++;
    }
}

static void oled_cmdp(PGM_P values, const size_t count) {
    oled_start_com();
    oled_sendp(values, count);
}

void oled_datap(PGM_P values, const size_t count) {
    oled_start_data();
    oled_sendp(values, count);
}

void oled_init() {
    spi_init();

    COUTPUT(SCREEN_RES);
    CSET(SCREEN_RES);

    oled_select();

    // Reset

    CSET(SCREEN_RES);
    _delay_ms(1);
    CCLEAR(SCREEN_RES);
    _delay_ms(10);
    CSET(SCREEN_RES);

    // Startup sequence

    oled_cmdp(oled_startup_sequence, oled_startup_sequence_size);

    // clear display
    oled_start_data();
    for (int x = 0; x < 128 * 8; x++) {
        spi_send(0xCC);
    }

    // display on

    oled_start_com();
    spi_send(0xAF);

    oled_deselect();
}

void oled_set_window(int left, int right, int top, int bottom) {
    oled_start_com();
    spi_send(0x21);
    spi_send(left);
    spi_send(right);
    spi_send(0x22);
    spi_send(top);
    spi_send(bottom);
}

void oled_reset_window() {
    oled_start_com();
    spi_send(0x21);
    spi_send(0);
    spi_send(127);
    spi_send(0x22);
    spi_send(0);
    spi_send(7);
}

void oled_send(const uint8_t* values, const size_t count) {
    for (size_t i = 0;i < count;i++) {
        spi_send(*values);
        values++;
    }
}

void oled_data(const uint8_t* values, const size_t count) {
    oled_start_data();
    oled_send(values, count);
}

static uint8_t data = 0;

void oled_test() {
    oled_select();
    oled_reset_window();
    oled_start_data();
    uint8_t block = 1 << data;
    for (int x = 0; x < 128 * 8; x++) {
        spi_send(block);
    }
    oled_deselect();
    data++;
    if (data > 7) data = 0;
}

void oled_begin() {
    oled_select();
}

void oled_end() {
    oled_deselect();
}

void oled_update(uint8_t* buffer) {
    oled_select();
    oled_data(buffer, 128 * 8);
    oled_deselect();
}