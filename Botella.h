#ifndef BOTELLA_H
#define BOTELLA_H

#include "Arduino.h"

typedef struct {
  uint16_t capacidad = 330;          // (cc) Capacidad de la botella.
  uint16_t tMovLlenador = 3;         // (Seg.) Espera movimiento llenador.
  uint16_t tMovTapador = 3;          // (Seg.) Espera movimiento Tapador.
  uint16_t tCargaCO2_Barrido = 2;    // (Seg.) carga CO2 Barrido inicial.
  uint16_t tDescargaCO2_Barrido = 1; // (Seg.) descarga CO2 Barrido incial.
  uint16_t tCargaBeer = 10;          // (Seg.) carga de cerveza.
  uint16_t tEstBeer = 2;             // (Seg.) Estabilizacion presion beer.
  uint16_t tEstCO2 = 2;              // (Seg.) Estabilizacion presion CO2.
} TBotella;
#define botellasTam 6
TBotella botellas[botellasTam];
unsigned short currentBotella = 0;
#endif // BOTELLA_H