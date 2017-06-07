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

void setEmergencia()
{
  isEmergencia = true;
  msgProcesoActual = F("EMERGENCIA!");
}
void llenadorBajar()
{
  initTime = now();
  if (!isEmergencia)
  {
    if (PDesplazamiento.isOn())
    {
      PLlenado.on();
      msgProcesoActual = F("BAJ. LLENAD");
    }
    else
    {
      isEmergencia = true;
      msgProcesoActual = F("EMERGENCIA!");
    }
  }
}
void llenadorSubir()
{
  if (!isEmergencia)
  {
    if (!EBeer.isOn() && !ECO2_In.isOn())
    {
      PLlenado.off();
      msgProcesoActual = F("SUB. LLENAD");
    }
    else
    {
      setEmergencia();
    }
  }
}
void botellaToLlenado()
{
  if (!isEmergencia)
  {
    if (!PTapado.isOn())
    {
      PDesplazamiento.on();
      msgProcesoActual = F("MOV BOTELLA");
    }
    else
    {
      setEmergencia();
    }
  }
}
void botellaToTapado()
{
  if (!isEmergencia)
  {
    if (!PLlenado.isOn())
    {
      PDesplazamiento.off();
      msgProcesoActual = F("MOV BOTELLA");
    }
    else
    {
      setEmergencia();
    }
  }
}
void tapadorBajar()
{
  initTime = now();
  if (!isEmergencia)
  {
    if (!PDesplazamiento.isOn())
    {
      PTapado.on();
      msgProcesoActual = F("BAJ. TAPADO");
    }
    else
    {
      setEmergencia();
    }
  }
}
void tapadorSubir()
{
  PTapado.off();
  msgProcesoActual = F("SUB. TAPADO");
}
void co2InOn()
{
  initTime = now();
  if (!isEmergencia)
  {
    if (PLlenado.isOn())
    {
      ECO2_In.on();
      msgProcesoActual = F("CO2 INGRESA");
    }
    else
    {
      setEmergencia();
    }
  }
}
void co2InOff()
{
  ECO2_In.off();
  msgProcesoActual = F("CO2 IN. OFF");
}
void co2Out1On()
{
  initTime = now();
  if (!isEmergencia)
  {
    if (PLlenado.isOn())
    {
      ECO2_Out1.on();
      if (!EBeer.isOn())
      {
        msgProcesoActual = F("CO2 LIBERAR");
      }
      else
      {
        msgProcesoActual = F("BEER >< CO2");
      }
    }
    else
    {
      setEmergencia();
    }
  }
}
void co2Out1Off()
{
  ECO2_Out1.off();
  msgProcesoActual = F("CO2 LI. OFF");
}
void beerOn()
{
  if (!isEmergencia)
  {
    if (PLlenado.isOn())
    {
      EBeer.on();
      msgProcesoActual = F("BEER INGRES");
    }
    else
    {
      setEmergencia();
    }
  }
}
void beerOff()
{
  EBeer.off();
  msgProcesoActual = F("BEER IN OFF");
}
void finLlenado()
{
  if (!isEmergencia)
  {
    isInProceso = false;
    cantBeer = cantBeer + (botellas[currentBotella].capacidad);
    cantBotellas++;
    msgProcesoActual = F("");
  }
}

void restaurarEmergencia()
{
  if (isEmergencia)
  {
    EBeer.off();
    ECO2_In.off();
    ECO2_Out1.off();
    PLlenado.off();
    PTapado.off();
    PDesplazamiento.off();
    isEmergencia = false;
    isInProceso = false;
    msgProcesoActual = F("");
  }
}

void etapaFinal(byte &ct, TBotella &b)
{
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

void cancelarAlarmas()
{
  for (uint8_t i = 0; i < Alarm.count(); i++)
  {
    Alarm.disable(i);
  }
}

void llenarBotella(TBotella &b)
{
  if (!isInProceso)
  {
    byte ct = 0;
    isInProceso = true;
    botellaToLlenado();                 // Posicionar Botella en llenador
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
    etapaFinal(ct, b);
  }
}

#endif // PROCESSMANAGER_H