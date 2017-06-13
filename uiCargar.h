#ifndef UICARGAR_H
#define UICARGAR_H

#include "Arduino.h"
#include "globalVars.h"
#include "processManager.h"

void uiCargarTecladoHandler(char &key) {
  switch (key) {
  case 'B': // Modo manual
    if (cEtapa <= LLENADO)
      isManual = true;

    break;
  case 'A': // Llenado Completo
    if (isManual && cEtapa == LLENADO)
      isLleno = true;
    break;
  case 'C': // Cancelar
    cancelar();
    break;
  }
}
void uiCargarPantallaHandler() {
  lcd.noAutoscroll();
  lcd.setCursor(0, 0);
  lcd.print((isManual) ? TXT_CARGAR_OPCIONES1 : TXT_CARGAR_OPCIONES);
  lcd.setCursor(0, 1);
  lcd.print(msgProceso);
}

#endif // UICARGAR_H