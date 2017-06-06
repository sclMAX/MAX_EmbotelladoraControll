#ifndef ELECTROVALVULA_H
#define ELECTROVALVULA_H

#include "Arduino.h"
class Electrovalvula {
private:
  byte pin;
  volatile bool onOff;

public:
  Electrovalvula(byte pin);
  void on();
  void off();
  bool isOn();
};

#endif // ELECTROVALVULA_H