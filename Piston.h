#ifndef PISTON_H
#define PISTON_H

#include "Arduino.h"

volatile bool isEmergencia = false;

class Piston {
private:
  uint16_t pin;
  volatile bool onOff;

public:
  Piston(uint16_t pin);
  static void on();
  static void off();
  bool isOn();
};
#endif