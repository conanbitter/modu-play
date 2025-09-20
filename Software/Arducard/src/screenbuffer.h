#ifndef _SCREENBUFFER_H_
#define _SCREENBUFFER_H_

#include <stdint.h>

void sb_init();
void sb_putpixel(int x, int y, int color);
uint8_t* sb_getpointer();

#endif