#ifndef AUTOSETUP_H
#define AUTOSETUP_H

#include "Arduino.h"
#include "Botella.h"
#include "globalVars.h"
#include "processManager.h"
#include "configStorage.h"

time_t initTime = 0;
byte *currentVar;
byte etapa = 0;
void setTiempo() {
  int t = second(now() - initTime);
  currentVar = (t > 0) ? t : 1;
  initTime = 0;
}
void uiAutoSetupTecladoHandler(char &key) {
  switch (key) {
  case '1':
    if (etapa == 0) {
      botellaToLlenado();
      delay((RPOS_BOTELLA * 1000));
      initTime = now();
      *currentVar = &botellas[currentBotella].tMovLlenador;
      llenadorBajar();
      etapa = 1;
    }
    break;
  case '2':
    if (etapa == 1) {
      setTiempo();
      initTime = now();
      *currentVar = &botellas[currentBotella].tCargaCO2_Barrido;
      co2InOn();
      etapa = 2;
    }
    break;
  case '3':
    if (etapa == 2) {
      setTiempo();
      co2InOff();
      delay(RCOMUN * 1000);
      initTime = now();
      *currentVar = &botellas[currentBotella].tDescargaCO2_Barrido;
      co2Out1On();
      etapa = 3;
    }
    break;
  case '4':
    if (etapa == 3) {
      setTiempo();
      co2Out1Off();
      delay(RCOMUN * 1000);
      co2InOn();
      delay(botellas[currentBotella].tCargaCO2_Barrido * 1000);
      co2InOff();
      delay(RCOMUN * 1000);
      beerOn();
      delay(RCOMUN * 1000);
      initTime = now();
      *currentVar = &botellas[currentBotella].tCargaBeer;
      co2Out1On();
      etapa = 4;
    }
    break;
  case '5':
    if (etapa == 4) {
      setTiempo();
      co2Out1Off();
      delay(RCOMUN * 1000);
      initTime = now();
      *currentVar = &botellas[currentBotella].tEstBeer;
      etapa = 5;
    }
    break;
  case '6':
    if (etapa == 5) {
      setTiempo();
      beerOff();
      delay(RCOMUN * 1000);
      initTime = now();
      *currentVar = &botellas[currentBotella].tEstCO2;
      co2Out1On();
      etapa = 6;
    }
    break;
  case '7':
    if (etapa == 6) {
      setTiempo();
      co2Out1Off();
      delay(RCOMUN * 1000);
      llenadorSubir();
      delay(botellas[currentBotella].tMovLlenador * 1000);
      botellaToTapado();
      delay((RPOS_BOTELLA * 1000));
      initTime = now();
      *currentVar = &botellas[currentBotella].tMovTapador;
      tapadorBajar();
      etapa = 7;
    }
    break;
  case '8':
    if (etapa == 7) {
      setTiempo();
      tapadorSubir();
      delay(botellas[currentBotella].tMovTapador * 1000);
      finLlenado();
      etapa = 8;
    }
    break;
  case 'A':
    if (etapa == 8) {
      saveConfig();
      etapa = 0;
      currentUi = UIEDIT;
      lcd.clear();
    }
    break;
  case 'D':
    currentUi = UIEDIT;
    lcd.clear();
    break;
  }
}

void uiAutoSetupPantallaHandler() {
  lcd.setCursor(0, 0);
  lcd.print(F("1-8 Pro A Gu D <"));
  lcd.setCursor(0, 1);
  lcd.print(msgProcesoActual);
}

#endif // AUTOSETUP_H