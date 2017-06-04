#ifndef UIEDIT_H
#define UIEDIT_H

#include "Botella.h"
#include "globalVars.h"
short currentItem = 0;
volatile bool isInEditItem = false;
String data = "";
void uiEditTecladoHandler(char &key) {
  switch (key) {
  case '0' ... '9':
    if (isInEditItem) {
      data.concat(key);
      switch (currentItem) {
      case 0: // capacidad
        data =
            (data.toInt() > 0) ? (data.toInt() < 2000 ? data : "2000") : data;
        break;
      case 1 ... 7: // tiempos
        data = (data.toInt() > 0) ? (data.toInt() < 99 ? data : "99") : data;
        break;
      }
    }
    break;
  case 'A':
    isInEditItem = true;
    break;
  case 'B':
    if (!isInEditItem) {
      currentItem = (currentItem > 0) ? currentItem-- : 0;
    }
    break;
  case 'C':
    if (!isInEditItem) {
      currentItem = (currentItem < 7) ? currentItem++ : 7;
    }
    break;
  case 'D':
    if (isInEditItem) {
      isInEditItem = false;
    } else {
      currentUi = UIMAIN;
    }
    break;
  case '*':
    if (isInEditItem) {
      data = "";
    }
    break;
  case '#':
    if (isInEditItem) {
      switch (currentItem) {
      case 0:
        botellas[currentBotella].capacidad = data.toInt();
        break;
      case 1:
        botellas[currentBotella].tMovLlenador = data.toInt();
        break;
      case 2:
        botellas[currentBotella].tMovTapador = data.toInt();
        break;
      case 3:
        botellas[currentBotella].tCargaCO2_Barrido = data.toInt();
        break;
      case 4:
        botellas[currentBotella].tDescargaCO2_Barrido = data.toInt();
        break;
      case 5:
        botellas[currentBotella].tCargaBeer = data.toInt();
        break;
      case 6:
        botellas[currentBotella].tEstBeer = data.toInt();
        break;
      case 7:
        botellas[currentBotella].tEstCO2 = data.toInt();
        break;
      }
    }
    break;
  }
}

void uiEditPantallaHandler() {
  lcd.setCursor(0, 0);
  lcd.print("A-Ed ");
  lcd.setCursor(5,0);
  lcd.print("B-");
  lcd.write(LCD_CHAR_UP);
  lcd.setCursor(9,0);
  lcd.print("C-");
  lcd.write(LCD_CHAR_DOWN);
}
#endif // UIEDIT_H