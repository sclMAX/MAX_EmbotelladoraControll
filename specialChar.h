#ifndef ESPECIALCHAR_H
#define ESPECIALCHAR_H

#include "Arduino.h"
byte flechaUp[8] = {
	0b00100,
	0b01110,
	0b10101,
	0b00100,
	0b00100,
	0b00100,
	0b00000,
	0b00000
};
byte flechaDown[8] = {
	0b00000,
	0b00000,
	0b00100,
	0b00100,
	0b00100,
	0b10101,
	0b01110,
	0b00100
};

#endif //ESPECIALCHAR_H