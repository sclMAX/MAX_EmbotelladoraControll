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

enum Etapas
{
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

bool chkEspera(const ulong_t &tEspera, const ulong_t &tNow)
{
  if ((tInicio + tEspera) <= tNow)
  {
    tFaltante = 0;
    tInicio = 0;
    return true;
  }
  else
  {
    tFaltante = (tInicio + tEspera) - tNow;
    tFaltante = (tFaltante > 0) ? tFaltante : 0;
    return false;
  }
}

bool botellaToLlenado()
{
  if (!PTapado.isOn())
  {
    PDesplazamiento.on();
    return true;
  }
  return false;
}

bool botellaToTapado()
{
  if (!PLlenado.isOn())
  {
    PDesplazamiento.off();
    return true;
  }
  return false;
}

bool bajaLlenador()
{
  if (PDesplazamiento.isOn())
  {
    PLlenado.on();
    return true;
  }
  return false;
}

bool subeLlenador()
{
  if (!EBeer.isOn())
  {
    PLlenado.off();
    return true;
  }
  return false;
}

bool co2BarridoIn()
{
  if (PLlenado.isOn())
  {
    ECO2_In.on();
    return true;
  }
  return false;
}

bool co2BarridoOut()
{
  ECO2_In.off();
  if (!ECO2_In.isOn())
  {
    ECO2_Out.on();
    return true;
  }
  return false;
}

bool llenadoOn()
{
  if (PLlenado.isOn())
  {
    if (isContrapresion)
    {
      EBeer.on();
      ECO2_Out.on();
    }else{
      EBeer.on();
      ECO2_In.on();
    }
    return true;
  }
  return false;
}

void cancelar()
{
  isInProceso = false;
  tInicio = 0;
  tFaltante = 0;
  EBeer.off();
  ECO2_In.off();
  PLlenado.off();
  ECO2_Out.off();
  PTapado.off();
  delay(500);
  PDesplazamiento.off();
  isLleno = false;
  isManual = false;
  cEtapa = INICIO;
  currentUi = UIMAIN;
}
void generarMsg(const __FlashStringHelper *s, bool showTime = false)
{
  msgProceso = String(s);
  if (showTime)
  {
    msgProceso += String(tFaltante);
  }
  for (int i = msgProceso.length(); i < 16; i++)
  {
    msgProceso.concat(" ");
  }
}
void manageProcess()
{
  if (isInProceso)
  {
    ulong_t tNow = millis();
    switch (cEtapa)
    {
    case INICIO:
      if (tInicio > 0)
      {
        if (chkEspera(tBotellaToLlenado, tNow))
        {
          cEtapa = BAJALLENADOR;
        }
        generarMsg(TXT_MOVTOLLENADO, true);
      }
      else
      {
        if (botellaToLlenado())
          tInicio = tNow;
      }
      break;
    case BAJALLENADOR:
      if (tInicio > 0)
      {
        if (chkEspera(tBajaLlenador, tNow))
        {
          cEtapa = BARRIDOIN;
        }
        generarMsg(TXT_BAJALLENADOR, true);
      }
      else
      {
        if (bajaLlenador())
          tInicio = tNow;
      }
      break;
    case BARRIDOIN:
      if (tInicio > 0)
      {
        if (chkEspera(tBarridoCO2In, tNow))
        {
          cEtapa = BARRIDOOUT;
        }
        generarMsg(TXT_CO2IN, true);
      }
      else
      {
        if (co2BarridoIn())
          tInicio = tNow;
      }
      break;
    case BARRIDOOUT:
      if (tInicio > 0)
      {
        if (chkEspera(tBarridoCO2Out, tNow))
        {
          ECO2_Out.off();
          cEtapa = PRESURIZADO;
        }
        generarMsg(TXT_CO2OUT, true);
      }
      else
      {
        if (co2BarridoOut())
          tInicio = tNow;
      }
      break;
    case PRESURIZADO:
      if (tInicio > 0)
      {
        if (chkEspera(tPresurizado, tNow))
        {
          cEtapa = LLENADO;
        }
        generarMsg(TXT_CO2IN, true);
      }
      else
      {
        if (co2BarridoIn())
          tInicio = tNow;
      }
      break;
    case LLENADO:
      if (tInicio > 0)
      {
        if (isManual)
        {
          if (isLleno)
          {
            cEtapa = ESTCO2;
            isLleno = false;
            isManual = false;
            botellas[currentBotella].tLlenado = tFaltante;
            tInicio = 0;
            tFaltante = 0;
          }
          else
          {
            tFaltante = tNow - tInicio;
          }
        }
        else
        {
          if (chkEspera(botellas[currentBotella].tLlenado, tNow))
          {
            cEtapa = ESTCO2;
          }
        }
        generarMsg(TXT_LLENADO, true);
      }
      else
      {
        if (llenadoOn())
          tInicio = tNow;
      }
      break;
    case ESTCO2:
      if (tInicio > 0)
      {
        if (chkEspera(botellas[currentBotella].tEstCO2, tNow))
        {
          cEtapa = SUBELLENADOR;
        }
        generarMsg(TXT_ESTCO2, true);
      }
      else
      {
        EBeer.off();
        if(!isContrapresion){
          ECO2_In.off();
          ECO2_Out.on();
        }
        tInicio = tNow;
      }
      break;
    case SUBELLENADOR:
      if (tInicio > 0)
      {
        if (chkEspera(tSubeLlenador, tNow))
        {
          ECO2_Out.off();
          cEtapa = MOVTOTAPADO;
        }
        generarMsg(TXT_SUBELLENADOR, true);
      }
      else
      {
        if (subeLlenador())
          tInicio = tNow;
      }
      break;
    case MOVTOTAPADO:
      if (tInicio > 0)
      {
        if (chkEspera(tBotellaToTapado, tNow))
        {
          cEtapa = BAJATAPADOR;
        }
        generarMsg(TXT_MOVTOTAPADO, true);
      }
      else
      {
        if (botellaToTapado())
          tInicio = tNow;
      }
      break;
    case BAJATAPADOR:
      if (tInicio > 0)
      {
        if (chkEspera(tBajaTapador, tNow))
        {
          cEtapa = SUBETAPADOR;
        }
        generarMsg(TXT_BAJATAPADOR, true);
      }
      else
      {
        PTapado.on();
        tInicio = tNow;
      }
      break;
    case SUBETAPADOR:
      if (tInicio > 0)
      {
        if (chkEspera(tSubeTapador, tNow))
        {
          cEtapa = FIN;
        }
        generarMsg(TXT_SUBETAPADOR, true);
      }
      else
      {
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
      tInicio = 0;
      saveConfig();
      lcd.clear();
      currentUi = UIMAIN;
      break;
    }
  }
}

#endif // PROCESSMANAGER_H