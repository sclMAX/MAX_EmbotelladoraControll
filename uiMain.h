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
  case 'A': // Iniciar Carga
    lcd.clear();
    currentUi = UICARGAR;
    cEtapa = INICIO;
    isInProceso = true;
    break;
  case 'B': // Editar
    lcd.clear();
    currentUi = UIEDIT;
    break;
  case 'D': // Reset Contadores
    cantBeer = 0;
    cantBotellas = 0;
    break;
  }
}

void uiMainPantallaHandler() {
  lcd.noAutoscroll();
  lcd.setCursor(0, 0);
  lcd.print(TXT_MAIN_OPCIONES);
  lcd.setCursor(0, 1);
  String txt = "B" + String(currentBotella + 1) + "-" +
               String(botellas[currentBotella].capacidad) + " U" +
               String(cantBotellas) + " L" + String(getCantBeerLitros());
  lcd.print(txt);
}
#endif // UIMAIN_H