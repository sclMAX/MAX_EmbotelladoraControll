#ifndef UIMAIN_H
#define UIMAIN_H

#include "globalVars.h"
#include "Botella.h"

void uiMainTecladoHandler(char &key) {
  switch (key) {
  case '0' ... '9':
    currentBotella = String(key).toInt();
    break;
  }
}

void uiMainPantallaHandler() {
  lcd.setCursor(0,0);
  lcd.print("B");
  lcd.setCursor(1,0);
  lcd.print(currentBotella);
  lcd.setCursor(2,0);
  lcd.print(" C");
  lcd.setCursor(4,0);
  lcd.print(itostr4sign(botellas[currentBotella].capacidad));
  lcd.setCursor(8,0);
}
#endif // UIMAIN_H