#ifndef ESPECIALCHAR_H
#define ESPECIALCHAR_H

#include "Arduino.h"

#define LCD_CHAR_UP 1
const byte flechaUp[8] = {0b00100, 0b01110, 0b10101, 0b00100,
                          0b00100, 0b00100, 0b00000, 0b00000};
#define LCD_CHAR_DOWN 2
const byte flechaDown[8] = {0b00000, 0b00000, 0b00100, 0b00100,
                            0b00100, 0b10101, 0b01110, 0b00100};
#define LCD_CHAR_BACK 3
const byte flechaBack[8] = {0b00001, 0b00011, 0b00111, 0b01111,
                            0b01111, 0b00111, 0b00011, 0b00001};

#endif // ESPECIALCHAR_H