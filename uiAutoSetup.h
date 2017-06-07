#ifndef AUTOSETUP_H
#define AUTOSETUP_H

#include "Arduino.h"
#include "Botella.h"
#include "configStorage.h"
#include "globalVars.h"
#include "processManager.h"

byte etapa = 0;

void uiAutoSetupTecladoHandler(char &key) {
  switch (key) {
  case '1':
    if (etapa == 0) {
      botellaToLlenado();
      delay((RPOS_BOTELLA * 1000));
      llenadorBajar();
      etapa = 1;
    }
    break;
  case '2':
    if (etapa == 1) {
      botellas[currentBotella].tMovLlenador = getTiempo();
      co2InOn();
      etapa = 2;
    }
    break;
  case '3':
    if (etapa == 2) {
      botellas[currentBotella].tCargaCO2_Barrido = getTiempo();
      co2InOff();
      delay(RCOMUN * 1000);
      co2Out1On();
      etapa = 3;
    }
    break;
  case '4':
    if (etapa == 3) {
      botellas[currentBotella].tDescargaCO2_Barrido = getTiempo();
      co2Out1Off();
      delay(RCOMUN * 1000);
      co2InOn();
      delay(botellas[currentBotella].tCargaCO2_Barrido * 1000);
      co2InOff();
      delay(RCOMUN * 1000);
      beerOn();
      delay(RCOMUN * 1000);
      co2Out1On();
      etapa = 4;
    }
    break;
  case '5':
    if (etapa == 4) {
      botellas[currentBotella].tCargaBeer = getTiempo();
      co2Out1Off();
      delay(RCOMUN * 1000);
      initTime = now();
      etapa = 5;
    }
    break;
  case '6':
    if (etapa == 5) {
      botellas[currentBotella].tEstBeer = getTiempo();
      beerOff();
      delay(RCOMUN * 1000);
      co2Out1On();
      etapa = 6;
    }
    break;
  case '7':
    if (etapa == 6) {
      botellas[currentBotella].tEstCO2 = getTiempo();
      co2Out1Off();
      delay(RCOMUN * 1000);
      llenadorSubir();
      delay(botellas[currentBotella].tMovLlenador * 1000);
      botellaToTapado();
      delay((RPOS_BOTELLA * 1000));
      tapadorBajar();
      etapa = 7;
    }
    break;
  case '8':
    if (etapa == 7) {
      botellas[currentBotella].tMovTapador = getTiempo();
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