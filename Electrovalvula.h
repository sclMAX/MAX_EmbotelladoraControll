#ifndef ELECTROVALVULA_H
#define ELECTROVALVULA_H

#include "Arduino.h"
class Electrovalvula{
    private:
        uint16_t pin;
        volatile bool onOff;
    public:
        Electrovalvula(uint16_t pin);
        void on();
        void off();
        bool isOn();
};

#endif //ELECTROVALVULA_H