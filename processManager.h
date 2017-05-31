#ifndef PROCESSMANAGER_H
#define PROCESSMANAGER_H

#include <Time.h>
#include <TimeLib.h>
#include <TimeAlarms.h>
#include "config.h"
#include "Botella.h"
#include "Piston.h"
#include "Electrovalvula.h"
#include "globalVars.h"

Piston PDesplazamiento = Piston(PIN_DESPLAZAMIENTO);
Piston PLlenado = Piston(PIN_LLENADO);
Piston PTapado = Piston(PIN_TAPADO);
Electrovalvula EBeer = Electrovalvula(PIN_ELECTRO_CERVEZA);
Electrovalvula ECO2_In = Electrovalvula(PIN_ELECTRO_CO2_IN);
Electrovalvula ECO2_Out1 = Electrovalvula(PIN_ELECTRO_CO2_OUT1); // Salida libre
Electrovalvula ECO2_Out2 =
    Electrovalvula(PIN_ELECTRO_CO2_OUT2); // Salida Regulada

void llenadorBajar() {
  if (!isEmergencia) {
    if (PDesplazamiento.isOn()) {
      PLlenado.on();
    } else {
      isEmergencia = true;
    }
  }
}
void llenadorSubir() { PLlenado.off(); }
void botellaToLlenado() {
  if (!isEmergencia) {
    if (!PTapado.isOn()) {
      PDesplazamiento.on();
    } else {
      isEmergencia = true;
    }
  }
}
void botellaToTapado() {
  if (!isEmergencia) {
    if (!PLlenado.isOn()) {
      PDesplazamiento.off();
    } else {
      isEmergencia = true;
    }
  }
}
void tapadorBajar() {
  if (!isEmergencia) {
    if (!PDesplazamiento.isOn()) {
      PTapado.on();
    } else {
      isEmergencia = true;
    }
  }
}
void tapadorSubir() { PTapado.off(); }
void co2InOn() { ECO2_In.on(); }
void co2InOff() { ECO2_In.off(); }
void co2Out1On() { ECO2_Out1.on(); }
void co2Out1Off() { ECO2_Out1.off(); }
void co2Out2On() { ECO2_Out2.on(); }
void co2Out2Off() { ECO2_Out2.off(); }
void beerOn() { EBeer.on(); }
void beerOff() { EBeer.off(); }
void finLlenado() { isInProceso = false; }

void llenarBotella(TBotella &b) {
  if (!isInProceso) {
    uint16_t ct = 0;
    isInProceso = true;
    botellaToLlenado();                 // Posicionar Botella en llenador
    ct += RPOS_BOTELLA;                 // Espera posicion botella
    Alarm.timerOnce(ct, llenadorBajar); // Baja el llenador
    ct += b.tBajadaLlenador;            // Espera Bajada llenador.
    Alarm.timerOnce(ct, co2InOn);       // Abre Carga CO2 en la botella.
    ct += b.tCargaCO2_Barrido;          // Espera carga CO2.
    Alarm.timerOnce(ct, co2InOff);      // Cierra Carga CO2.
    ct += RCOMUN;                       // Espera comun por seguridad
    Alarm.timerOnce(ct, co2Out1On);     // Abre Descarga CO2.
    ct += b.tDescargaCO2_Barrido;       // Espera descarga CO2.
    Alarm.timerOnce(ct, co2Out1Off);    // Cierra descarga CO2.
    ct += RCOMUN;                       // Espera comun por seguridad
    Alarm.timerOnce(ct, co2InOn);       // Abre Carga CO2 en la botella.
    ct += b.tCargaCO2_Barrido;          // Espara carga CO2.
    Alarm.timerOnce(ct, co2InOff);      // Cierra Carga CO2.
    ct += RCOMUN;                       // Espera comun por seguridad
    Alarm.timerOnce(ct, beerOn);        // Abre carga Beer.
    ct += RCOMUN;                       // Espera comun por seguridad
    Alarm.timerOnce(ct, co2Out2On);     // Abre descarga controlada CO2.
    ct += b.tCargaBeer;                 // Espera carga beer.
    Alarm.timerOnce(ct, co2Out2Off);    // Cierra descarga controlada CO2.
    ct += b.tEstBeer;                // Espera Estabilizacion de presion beer.
    Alarm.timerOnce(ct, beerOff);    // Cierra carga Beer.
    ct += RCOMUN;                    // Espera comun por seguridad
    Alarm.timerOnce(ct, co2Out2On);  // Abre descarga controlada CO2.
    ct += b.tEstCO2;                 // Espera Estabilizacion CO2.
    Alarm.timerOnce(ct, co2Out2Off); // Cierra descarga controlada CO2.
    ct += RCOMUN;                    // Espera comun por seguridad
    Alarm.timerOnce(ct, co2Out1On);  // Abre descarga CO2.
    ct += 2 * RCOMUN;                // Doble Espera comun por seguridad
    Alarm.timerOnce(ct, co2Out1Off); // Cierra descarga CO2.
    ct += RCOMUN;                    // Espera comun por seguridad
    Alarm.timerOnce(ct, llenadorSubir);   // Sube el llenador.
    ct += b.tBajadaLlenador;              // Espera Subida llenador.
    Alarm.timerOnce(ct, botellaToTapado); // Posicionar botella en tapador.
    ct += RPOS_BOTELLA;                   // Espera posicion botella.
    Alarm.timerOnce(ct, tapadorBajar);    // Baja Tapador.
    ct += b.tBajadaTapador;               // Espera bajada tapador.
    Alarm.timerOnce(ct, tapadorSubir);    // Sube Tapador.
    ct += b.tBajadaTapador;               // Espera subida tapador.
    Alarm.timerOnce(ct, finLlenado);      // Fin del ciclo.
  }
}

#endif // PROCESSMANAGER_H