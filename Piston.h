#ifndef PISTON_H
#define PISTON_H

#include "Arduino.h"


class Piston {
private:
  uint16_t pin;
  volatile bool onOff;

public:
  Piston(uint16_t pin);
  void on();
  void off();
  bool isOn();
};
#endif