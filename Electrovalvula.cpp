#include "Electrovalvula.h"

Electrovalvula::Electrovalvula(uint16_t pin): pin(pin){
    pinMode(pin, OUTPUT);
    off();
};

void Electrovalvula::on(){
    digitalWrite(pin, HIGH);
    onOff = true;
};

void Electrovalvula::off(){
    digitalWrite(pin, LOW);
    onOff = false;
};

bool Electrovalvula::isOn(){
    return onOff;
}