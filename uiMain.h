#ifndef UIMAIN_H
#define UIMAIN_H

#include "globalVars.h"

void uiMainTecladoHandler(char &key) {
  lcd.clear();
  lcd.print(key);
}

void uiMainPantallaHandler() {}
#endif // UIMAIN_H