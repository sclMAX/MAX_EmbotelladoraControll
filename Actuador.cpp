#include "Actuador.h"

Actuador::Actuador(byte pin) : pin(pin) {
  pinMode(pin, OUTPUT);
  off();
};

void Actuador::on() {
  digitalWrite(pin, LOW);
  onOff = true;
};

void Actuador::off() {
  digitalWrite(pin, HIGH);
  onOff = false;
};

bool Actuador::isOn() { return onOff; }