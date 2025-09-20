#include "buttons.h"
#include <avr/io.h>
#include "arduino.h"

#define BTN_UP A0
#define BTN_DOWN A1
#define BTN_LEFT A2
#define BTN_RIGHT A3
#define BTN_A D3
#define BTN_B D2

void btn_init()
{
    CINPUT(BTN_UP);
    CINPUT(BTN_DOWN);
    CINPUT(BTN_LEFT);
    CINPUT(BTN_RIGHT);
    CINPUT(BTN_A);
    CINPUT(BTN_B);
}

int btn_get(int button)
{
    switch (button)
    {
    case 0:return !CREAD(BTN_UP);
    case 1:return !CREAD(BTN_DOWN);
    case 2:return !CREAD(BTN_LEFT);
    case 3:return !CREAD(BTN_RIGHT);
    case 4:return !CREAD(BTN_A);
    case 5:return !CREAD(BTN_B);
    }

}
