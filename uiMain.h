#ifndef UIMAIN_H
#define UIMAIN_H

#include "Botella.h"
#include "globalVars.h"
#include "processManager.h"

void uiMainTecladoHandler(char &key) {
  switch (key) {
  case '1' ... '6':
    if (!isInProceso) {
      lcd.clear();
      currentBotella = String(key).toInt() - 1;
    }
    break;
  case '#':
    if (isInProceso && EBeer.isOn()) {
      co2Out1Off();
      botellas[currentBotella].tCargaBeer = getTiempo();
      cancelarAlarmas();
      byte ct = 0;
      etapaFinal(ct, botellas[currentBotella]);
      saveConfig();
    }
    break;
  case 'A':
    lcd.clear();
    llenarBotella(botellas[currentBotella]);
    break;
  case 'B':
    if (!isInProceso) {
      lcd.clear();
      currentUi = UIEDIT;
    }
    break;
  case 'C':
    isEmergencia = true;
    break;
  case 'D':
    restaurarEmergencia();
    break;
  }
}

void uiMainPantallaHandler() {
  lcd.setCursor(0, 0);
  lcd.print(F("B"));
  lcd.setCursor(1, 0);
  lcd.print((currentBotella + 1));
  lcd.setCursor(2, 0);
  lcd.print(" C");
  lcd.setCursor(4, 0);
  lcd.print(botellas[currentBotella].capacidad);
  lcd.setCursor(8, 0);
  lcd.print(" L");
  lcd.setCursor(10, 0);
  float cbeer = 0.00;
  cbeer = cantBeer;
  cbeer = cbeer / 1000;
  lcd.print(ftostr32(cbeer));
  lcd.setCursor(0, 1);
  if (isInProceso) {
    lcd.print(msgProcesoActual);
  } else {
    lcd.print(F("A-i B-e #-g "));
  }
  lcd.setCursor(12, 1);
  lcd.print(F("U"));
  lcd.setCursor(13, 1);
  lcd.print(cantBotellas);
}
#endif // UIMAIN_H