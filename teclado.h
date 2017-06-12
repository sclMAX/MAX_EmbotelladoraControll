#ifndef TECLADO_H
#define TECLADO_H

#include "config.h"
#include "globalVars.h"
//#include "uiEdit.h"
#include <Key.h>
#include <Keypad.h>

const byte rows = 4;
const byte cols = 4;

char keys[rows][cols] = {{'1', '2', '3', 'A'},
                         {'4', '5', '6', 'B'},
                         {'7', '8', '9', 'C'},
                         {'*', '0', '#', 'D'}};
byte rowPins[rows] = {PINS_TECLADO_ROW};
byte colPins[cols] = {PINS_TECLADO_COL};
Keypad Teclado = Keypad(makeKeymap(keys), rowPins, colPins, rows, cols);

void tecladoHandler() {
  char key = Teclado.getKey();
  if (key) {
    switch (currentUi) {
    case UIMAIN:
      uiMainTecladoHandler(key);
      break;
    }
  }
}
#endif // TECLADO_H