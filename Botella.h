#ifndef BOTELLA_H
#define BOTELLA_H

#include "Arduino.h"

typedef struct {
  uint16_t capacidad = 330;          // (cc) Capacidad de la botella.
  byte tMovLlenador = 3;         // (Seg.) Espera movimiento llenador.
  byte tMovTapador = 3;          // (Seg.) Espera movimiento Tapador.
  byte tCargaCO2_Barrido = 2;    // (Seg.) carga CO2 Barrido inicial.
  byte tDescargaCO2_Barrido = 1; // (Seg.) descarga CO2 Barrido incial.
  byte tCargaBeer = 30;          // (Seg.) carga de cerveza.
  byte tEstBeer = 5;             // (Seg.) Estabilizacion presion beer.
  byte tEstCO2 = 10;              // (Seg.) Estabilizacion presion CO2.
} TBotella;
#define botellasTam 6
TBotella botellas[botellasTam];
unsigned short currentBotella = 0;
#endif // BOTELLA_H