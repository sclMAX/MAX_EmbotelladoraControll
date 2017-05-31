#ifndef PROCESSMANAGER_H
#define PROCESSMANAGER_H

#include <Time.h>
#include <TimeLib.h>
#include <TimeAlarms.h>
#include "config.h"
#include "Botella.h"
#include "Piston.h"
#include "Electrovalvula.h"

Piston PDesplazamiento = Piston(PIN_DESPLAZAMIENTO);
Piston PLlenado = Piston(PIN_LLENADO);
Piston PTapado = Piston(PIN_TAPADO);
Electrovalvula EBeer = Electrovalvula(PIN_ELECTRO_CERVEZA);
Electrovalvula ECO2_In = Electrovalvula(PIN_ELECTRO_CO2_IN);
Electrovalvula ECO2_Out1 = Electrovalvula(PIN_ELECTRO_CO2_OUT1); // Salida libre
Electrovalvula ECO2_Out2 =
    Electrovalvula(PIN_ELECTRO_CO2_OUT2); // Salida Regulada
volatile bool isInProceso = false;

void finLlenado() { isInProceso = false; }

void llenarBotella(TBotella &b) {
  if (!isInProceso) {
    uint16_t ct = 0;
    isInProceso = true;
    PDesplazamiento.on();               // Posicionar Botella en llenador
    ct += RPOS_BOTELLA;                 // Espera posicion botella
    Alarm.timerOnce(ct, PLlenado.on);   // Baja el llenador
    ct += b.tBajadaLlenador;            // Espera Bajada llenador.
    Alarm.timerOnce(ct, ECO2_In.on);    // Abre Carga CO2 en la botella.
    ct += b.tCargaCO2_Barrido;          // Espera carga CO2.
    Alarm.timerOnce(ct, ECO2_In.off);   // Cierra Carga CO2.
    ct += RCOMUN;                       // Espera comun por seguridad
    Alarm.timerOnce(ct, ECO2_Out1.on);  // Abre Descarga CO2.
    ct += b.tDescargaCO2_Barrido;       // Espera descarga CO2.
    Alarm.timerOnce(ct, ECO2_Out1.off); // Cierra descarga CO2.
    ct += RCOMUN;                       // Espera comun por seguridad
    Alarm.timerOnce(ct, ECO2_In.on);    // Abre Carga CO2 en la botella.
    ct += b.tCargaCO2_Barrido;          // Espara carga CO2.
    Alarm.timerOnce(ct, ECO2_In.off);   // Cierra Carga CO2.
    ct += RCOMUN;                       // Espera comun por seguridad
    Alarm.timerOnce(ct, EBeer.on);      // Abre carga Beer.
    ct += RCOMUN;                       // Espera comun por seguridad
    Alarm.timerOnce(ct, ECO2_Out2.on);  // Abre descarga controlada CO2.
    ct += b.tCargaBeer;                 // Espera carga beer.
    Alarm.timerOnce(ct, ECO2_Out2.off); // Cierra descarga controlada CO2.
    ct += b.tEstBeer;                  // Espera Estabilizacion de presion beer.
    Alarm.timerOnce(ct, EBeer.off);    // Cierra carga Beer.
    ct += RCOMUN;                      // Espera comun por seguridad
    Alarm.timerOnce(ct, ECO2_Out2.on); // Abre descarga controlada CO2.
    ct += b.tEstCO2;                   // Espera Estabilizacion CO2.
    Alarm.timerOnce(ct, ECO2_Out2.off); // Cierra descarga controlada CO2.
    ct += RCOMUN;                       // Espera comun por seguridad
    Alarm.timerOnce(ct, ECO2_Out1.on);  // Abre descarga CO2.
    ct += 2 * RCOMUN;                   // Doble Espera comun por seguridad
    Alarm.timerOnce(ct, ECO2_Out1.off); // Cierra descarga CO2.
    ct += RCOMUN;                       // Espera comun por seguridad
    Alarm.timerOnce(ct, PLlenado.off);  // Sube el llenador.
    ct += b.tBajadaLlenador;            // Espera Subida llenador.
    Alarm.timerOnce(ct, PDesplazamiento.off); // Posicionar botella en tapador.
    ct += RPOS_BOTELLA;                       // Espera posicion botella.
    Alarm.timerOnce(ct, PTapado.on);          // Baja Tapador.
    ct += b.tBajadaTapador;                   // Espera bajada tapador.
    Alarm.timerOnce(ct, PTapado.off);         // Sube Tapador.
    ct += b.tBajadaTapador;                   // Espera subida tapador.
    Alarm.timerOnce(ct, finLlenado);          // Fin del ciclo.
  }
}

#endif // PROCESSMANAGER_H