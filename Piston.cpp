#include "Piston.h"
#include "config.h"

Piston::Piston(uint16_t pin) : pin(pin) {
  pinMode(pin, OUTPUT);
  off();
};

void Piston::on() {
  {
    if (!isEmergencia) {
      digitalWrite(pin, HIGH);
      onOff = true;
    }
  };

  void Piston::off() {
    digitalWrite(pin, LOW);
    onOff = false;
  };

  bool Piston::isOn() { return onOff; }