#ifndef _SCREEN_H_
#define _SCREEN_H_

#include <stddef.h>
#include <avr/pgmspace.h>

void oled_init();
void oled_test();

//void oled_setxy(int x, int y);
//void oled_cmd(uint8_t command);
//void oled_cmd1a(uint8_t command, uint8_t arg);
//void oled_cmd2a(uint8_t command, uint8_t arg1, uint8_t arg2);
//void oled_cmdv(uint8_t* commands, size_t count);
//void oled_cmdp(PGM_P commands, size_t count);

//void oled_data(uint8_t value);
//void oled_datav(uint8_t* values, size_t count);
//void oled_datap(PGM_P values, size_t count);

//void oled_start_cmd();
//void oled_start_data();
//void oled_send();

#endif