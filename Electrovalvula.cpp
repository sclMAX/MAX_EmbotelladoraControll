#include "Electrovalvula.h"

Electrovalvula::Electrovalvula(byte pin) : pin(pin) {
  pinMode(pin, OUTPUT);
  off();
};

void Electrovalvula::on() {
    digitalWrite(pin, LOW);
    onOff = true;
};

void Electrovalvula::off() {
  digitalWrite(pin, HIGH);
  onOff = false;
};

bool Electrovalvula::isOn() { return onOff; }