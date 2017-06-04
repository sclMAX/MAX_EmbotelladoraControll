#include "Piston.h"
#include "config.h"

Piston::Piston(uint16_t pin) : pin(pin) {
  pinMode(pin, OUTPUT);
  off();
};

void Piston::on() {
  digitalWrite(pin, LOW);
  onOff = true;
};

void Piston::off() {
  digitalWrite(pin, HIGH);
  onOff = false;
};

bool Piston::isOn() { return onOff; }