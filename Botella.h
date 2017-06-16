#ifndef BOTELLA_H
#define BOTELLA_H

#include "Arduino.h"
#include "globalVars.h"

typedef struct {
  uint16_t capacidad = 330;     // (cc) Capacidad de la botella.
  ulong_t tLlenado = 40000; // (mseg.)Tiempo de Llenado.
  ulong_t tEstCO2 = 60000;  // (mseg.)Tiempo descompresion CO2.
} TBotella;
#define botellasTam 6
TBotella botellas[botellasTam];
unsigned short currentBotella = 0;
#endif // BOTELLA_H