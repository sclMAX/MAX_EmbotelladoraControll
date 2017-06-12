#ifndef ESPECIALCHAR_H
#define ESPECIALCHAR_H

#include "Arduino.h"

#define LCD_CHAR_UP 1
const byte flechaUp[8] = {0b00100, 0b01110, 0b10101, 0b00100,
                          0b00100, 0b00100, 0b00000, 0b00000};
#define LCD_CHAR_DOWN 2
const byte flechaDown[8] = {0b00000, 0b00000, 0b00100, 0b00100,
                            0b00100, 0b10101, 0b01110, 0b00100};
#define LCD_CHAR_SELECT 3
const byte select[8] = {0b10000, 0b11000, 0b11100, 0b11110,
                        0b11110, 0b11100, 0b11000, 0b10000};

#endif // ESPECIALCHAR_H