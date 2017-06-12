#ifndef PROCESSMANAGER_H
#define PROCESSMANAGER_H

#include "Botella.h"
#include "Actuador.h"
#include "config.h"
#include "globalVars.h"
#include "configStorage.h"

Actuador PDesplazamiento = Actuador(PIN_DESPLAZAMIENTO);
Actuador PLlenado = Actuador(PIN_LLENADO);
Actuador PTapado = Actuador(PIN_TAPADO);
Actuador EBeer = Actuador(PIN_ELECTRO_CERVEZA);
Actuador ECO2_In = Actuador(PIN_ELECTRO_CO2_IN);
Actuador ECO2_Out = Actuador(PIN_ELECTRO_CO2_OUT1);

enum Etapas {
  INICIO,
  BAJALLENADOR,
  BARRIDOIN,
  BARRIDOOUT,
  PRESURIZADO,
  LLENADO,
  ESTCO2,
  SUBELLENADOR,
  MOVTOTAPADO,
  BAJATAPADOR,
  SUBETAPADOR,
  FIN
};
enum Etapas cEtapa = INICIO;
ulong_t tInicio = 0;
ulong_t tFaltante = 0;

bool chkEspera(const ulong_t &tEspera, const ulong_t &tNow) {
  if ((tInicio + tEspera) <= tNow) {
    tFaltante = tInicio = 0;
    return true;
  } else {
    tFaltante = (tInicio + tEspera) - tNow;
    return false;
  }
}

bool botellaToLlenado() {
  if (!PTapado.isOn()) {
    PDesplazamiento.on();
    return true;
  }
  return false;
}

bool botellaToTapado() {
  if (!PLlenado.isOn()) {
    PDesplazamiento.off();
    return true;
  }
  return false;
}

bool bajaLlenador() {
  if (PDesplazamiento.isOn()) {
    PLlenado.on();
    return true;
  }
  return false;
}

bool subeLlenador() {
  if (!EBeer.isOn()) {
    PLlenado.off();
    return true;
  }
  return false;
}

bool co2BarridoIn() {
  if (PLlenado.isOn()) {
    ECO2_In.on();
    return true;
  }
  return false;
}

bool co2BarridoOut() {
  ECO2_In.off();
  if (!ECO2_In.isOn()) {
    ECO2_Out.on();
    return true;
  }
  return false;
}

bool llenadoOn() {
  if (PLlenado.isOn()) {
    EBeer.on();
    ECO2_Out.on();
    return true;
  }
  return false;
}

void manageProcess() {
  if (isInProceso) {
    ulong_t tNow = millis();
    switch (cEtapa) {
    case INICIO:
      if (tInicio > 0) {
        if (chkEspera(tDesplazamiento, tNow)) {
          cEtapa = BAJALLENADOR;
        }
      } else {
        if (botellaToLlenado())
          tInicio = tNow;
      }
      break;
    case BAJALLENADOR:
      if (tInicio > 0) {
        if (chkEspera(tBajaLlenador, tNow)) {
          cEtapa = BARRIDOIN;
        }
      } else {
        if (bajaLlenador())
          tInicio = tNow;
      }
      break;
    case BARRIDOIN:
      if (tInicio > 0) {
        if (chkEspera(tBarridoCO2In, tNow)) {
          cEtapa = BARRIDOOUT;
        }
      } else {
        if (co2BarridoIn())
          tInicio = tNow;
      }
      break;
    case BARRIDOOUT:
      if (tInicio > 0) {
        if (chkEspera(tBarridoCO2Out, tNow)) {
          ECO2_Out.off();
          cEtapa = PRESURIZADO;
        }
      } else {
        if (co2BarridoOut())
          tInicio = tNow;
      }
      break;
    case PRESURIZADO:
      if (tInicio > 0) {
        if (chkEspera(tPresurizado, tNow)) {
          cEtapa = LLENADO;
        }
      } else {
        if (co2BarridoIn())
          tInicio = tNow;
      }
      break;
    case LLENADO:
      if (tInicio > 0) {
        if (chkEspera(botellas[currentBotella].tLlenado, tNow)) {
          cEtapa = ESTCO2;
        }
      } else {
        if (llenadoOn())
          tInicio = tNow;
      }
      break;
    case ESTCO2:
      if (tInicio > 0) {
        if (chkEspera(botellas[currentBotella].tEstCO2, tNow)) {
          cEtapa = SUBELLENADOR;
        }
      } else {
        EBeer.off();
        tInicio = tNow;
      }
      break;
    case SUBELLENADOR:
      if (tInicio > 0) {
        if (chkEspera(tSubeLlenador, tNow)) {
          cEtapa = MOVTOTAPADO;
        }
      } else {
        if (subeLlenador())
          tInicio = tNow;
      }
      break;
    case MOVTOTAPADO:
      if (tInicio > 0) {
        if (chkEspera(tBotellaToTapado, tNow)) {
          cEtapa = BAJATAPADOR;
        }
      } else {
        if (botellaToTapado)
          tInicio = tNow;
      }
      break;
    case BAJATAPADOR:
      if (tInicio > 0) {
        if (chkEspera(tBajaTapador, tNow)) {
          cEtapa = SUBETAPADOR;
        }
      } else {
        PTapado.on();
        tInicio = tNow;
      }
      break;
    case SUBETAPADOR:
      if (tInicio > 0) {
        if (chkEspera(tSubeTapador, tNow)) {
          cEtapa = FIN;
        }
      } else {
        PTapado.off();
        tInicio = tNow;
      }
      break;
    case FIN:
      ECO2_Out.off();
      cantBotellas++;
      cantBeer += botellas[currentBotella].capacidad;
      isInProceso = false;
      cEtapa = INICIO;
      saveConfig();
      break;
    }
  }
}

#endif // PROCESSMANAGER_H