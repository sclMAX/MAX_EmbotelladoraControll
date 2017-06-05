#ifndef PROCESSMANAGER_H
#define PROCESSMANAGER_H

#include "Botella.h"
#include "Electrovalvula.h"
#include "Piston.h"
#include "config.h"
#include "globalVars.h"
#include <Time.h>
#include <TimeAlarms.h>
#include <TimeLib.h>

Piston PDesplazamiento = Piston(PIN_DESPLAZAMIENTO);
Piston PLlenado = Piston(PIN_LLENADO);
Piston PTapado = Piston(PIN_TAPADO);
Electrovalvula EBeer = Electrovalvula(PIN_ELECTRO_CERVEZA);
Electrovalvula ECO2_In = Electrovalvula(PIN_ELECTRO_CO2_IN);
Electrovalvula ECO2_Out1 =
    Electrovalvula(PIN_ELECTRO_CO2_OUT1); // Salida Regulada

void llenadorBajar() {
  if (!isEmergencia) {
    if (PDesplazamiento.isOn()) {
      PLlenado.on();
      msgProcesoActual = "BAJ. LLENAD";
    } else {
      isEmergencia = true;
    }
  }
}
void llenadorSubir() {
  PLlenado.off();
  msgProcesoActual = "SUB. LLENAD";
}
void botellaToLlenado() {
  if (!isEmergencia) {
    if (!PTapado.isOn()) {
      PDesplazamiento.on();
      msgProcesoActual = "MOV BOTELLA";
    } else {
      isEmergencia = true;
    }
  }
}
void botellaToTapado() {
  if (!isEmergencia) {
    if (!PLlenado.isOn()) {
      PDesplazamiento.off();
      msgProcesoActual = "MOV BOTELLA";
    } else {
      isEmergencia = true;
    }
  }
}
void tapadorBajar() {
  if (!isEmergencia) {
    if (!PDesplazamiento.isOn()) {
      PTapado.on();
      msgProcesoActual = "BAJ. TAPADO";
    } else {
      isEmergencia = true;
    }
  }
}
void tapadorSubir() {
  PTapado.off();
  msgProcesoActual = "SUB. TAPADO";
}
void co2InOn() {
  ECO2_In.on();
  msgProcesoActual = "CO2 INGRESA";
}
void co2InOff() {
  ECO2_In.off();
  msgProcesoActual = "CO2 IN. OFF";
}
void co2Out1On() {
  ECO2_Out1.on();
  if (!(msgProcesoActual == "BEER INGRES")) {
    msgProcesoActual = "CO2 LIBERAR";
  } else {
    msgProcesoActual = "BEER >< CO2";
  }
}
void co2Out1Off() {
  ECO2_Out1.off();
  msgProcesoActual = "CO2 LI. OFF";
}
void beerOn() {
  EBeer.on();
  msgProcesoActual = "BEER INGRES";
}
void beerOff() {
  EBeer.off();
  msgProcesoActual = "BEER IN OFF";
}
void finLlenado() {
  isInProceso = false;
  cantBeer = cantBeer + (botellas[currentBotella].capacidad);
  cantBotellas++;
}

void llenarBotella(TBotella &b) {
  if (!isInProceso) {
    uint16_t ct = 0;
    isInProceso = true;
    botellaToLlenado(); // Posicionar Botella en llenador
    ct += RPOS_BOTELLA;                 // Espera posicion botella
    Alarm.timerOnce(ct, llenadorBajar); // Baja el llenador
    ct += b.tMovLlenador;               // Espera Bajada llenador.
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
    Alarm.timerOnce(ct, co2Out1On);     // Abre descarga controlada CO2.
    ct += b.tCargaBeer;                 // Espera carga beer.
    Alarm.timerOnce(ct, co2Out1Off);    // Cierra descarga controlada CO2.
    ct += b.tEstBeer;                // Espera Estabilizacion de presion beer.
    Alarm.timerOnce(ct, beerOff);    // Cierra carga Beer.
    ct += RCOMUN;                    // Espera comun por seguridad
    Alarm.timerOnce(ct, co2Out1On);  // Abre descarga controlada CO2.
    ct += b.tEstCO2;                 // Espera Estabilizacion CO2.
    Alarm.timerOnce(ct, co2Out1Off); // Cierra descarga controlada CO2.
    ct += RCOMUN;
    Alarm.timerOnce(ct, llenadorSubir);   // Sube el llenador.
    ct += b.tMovLlenador;                 // Espera Subida llenador.
    Alarm.timerOnce(ct, botellaToTapado); // Posicionar botella en tapador.
    ct += RPOS_BOTELLA;                   // Espera posicion botella.
    Alarm.timerOnce(ct, tapadorBajar);    // Baja Tapador.
    ct += b.tMovTapador;                  // Espera bajada tapador.
    Alarm.timerOnce(ct, tapadorSubir);    // Sube Tapador.
    ct += b.tMovTapador;                  // Espera subida tapador.
    Alarm.timerOnce(ct, finLlenado);      // Fin del ciclo.
  }
}

#endif // PROCESSMANAGER_H