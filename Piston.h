#ifndef PISTON_H
#define PISTON_H

#include "Arduino.h"


class Piston {
private:
  byte pin;
  volatile bool onOff;

public:
  Piston(byte pin);
  void on();
  void off();
  bool isOn();
};
#endif