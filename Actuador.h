#ifndef ACTUADOR_H
#define ACTUADOR_H

#include "Arduino.h"

class Actuador {
private:
  byte pin;
  volatile bool onOff;

public:
  Actuador(byte pin);
  void on();
  void off();
  bool isOn();
};
#endif // ACTUADOR_H