#ifndef PANTALLAMANAGER_H
#define PANTALLAMANAGER_H

#include "Arduino.h"
#include "globalVars.h"
#include "uiMain.h"
#include "uiEdit.h"

void pantallaInit() {
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print(" EMBOTELLADORA  ");
  lcd.setCursor(0, 1);
  lcd.print("  v1.0 by MAX   ");
  delay(3000);
  lcd.clear();
}
void pantallaHandler() {
  switch (currentUi) {
  case UIMAIN:
    uiMainPantallaHandler();
    break;
  case UIEDIT:
    uiEditPantallaHandler();
    break;
  }
}
#endif // PANTALLAMANAGER_H