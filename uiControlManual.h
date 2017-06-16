#ifndef CONTROLMANUAL_H
#define CONTROLMANUAL_H

#include "globalVars.h"
#include "processManager.h"

void uiControlManualTecladoHandler(char &key) {
  switch (key) {
  case '1':
    if (PDesplazamiento.isOn()) {
      PDesplazamiento.off();
    } else {
      PDesplazamiento.on();
    }
    break;
  case '2':
    if (PLlenado.isOn()) {
      PLlenado.off();
    } else {
      PLlenado.on();
    }
    break;
  case '3':
    if (PTapado.isOn()) {
      PTapado.off();
    } else {
      PTapado.on();
    }
    break;
  case '4':
    if (ECO2_In.isOn()) {
      ECO2_In.off();
    } else {
      ECO2_In.on();
    }
    break;
  case '5':
    if (ECO2_Out.isOn()) {
      ECO2_Out.off();
    } else {
      ECO2_Out.on();
    }
    break;
  case '6':
    if (EBeer.isOn()) {
      EBeer.off();
    } else {
      EBeer.on();
    }
    break;
  case 'C':
    lcd.clear();
    cancelar();
    break;
  }
}

void uiControlManualPantallaHandler() {
  lcd.setCursor(0, 0);
  lcd.print(F("1:Pd 2:Pll 3:Pt "));
  lcd.setCursor(0, 1);
  lcd.print(F("4:COi 5:COo 6:Be"));
}
#endif // CONTROLMANUAL_H