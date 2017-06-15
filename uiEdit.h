#ifndef UIEDIT_H
#define UIEDIT_H

#include "Botella.h"
#include "globalVars.h"
#include "configStorage.h"

enum items { CAPACIDAD, TLLENADO, TESTCO2 };
#define itemsTam 3
enum items currentItem = CAPACIDAD;
volatile bool isInEditItem = false;
String data = "";
void uiEditTecladoHandler(char &key) {
  switch (key) {
  case '0' ... '9':
    data.concat(key);
    if (currentItem == CAPACIDAD) { // capacidad
      data =
          (data.toInt() > 0) ? ((data.toInt() < 2000) ? data : "3000") : data;
    }
    break;
  case 'A':
    if (!isInEditItem) {
      currentItem--;
      currentItem = (currentItem > 0) ? currentItem : itemsTam - 1;
      lcd.clear();
    }
    break;
  case 'B':
    if (!isInEditItem) {
      currentItem++;
      currentItem = (currentItem < itemsTam) ? currentItem : 0;
      lcd.clear();
    }
    break;
  case 'C':
    if (isInEditItem) {
      isInEditItem = false;
    } else {
      lcd.clear();
      currentUi = UIMAIN;
    }
    break;
  case '*':
    if (isInEditItem) {
      data = "";
      lcd.clear();
    }
    break;
  case '#':
    if (isInEditItem) {
      isInEditItem = false;
      switch (currentItem) {
      case CAPACIDAD:
        botellas[currentBotella].capacidad = data.toInt();
        break;
      case TLLENADO:
        botellas[currentBotella].tLlenado = data.toInt();
        break;
      case TESTCO2:
        botellas[currentBotella].tEstCO2 = data.toInt();
        break;
      }
      saveConfig();
      data = "";
    } else {
      isInEditItem = true;
    }
    break;
  }
}

void drawItem(uint8_t pos, bool sel, const __FlashStringHelper *txt,
              ulong_t &item) {
  lcd.setCursor(0, pos);
  if (sel) {
    lcd.write(LCD_CHAR_SELECT);
  }
  lcd.setCursor(1, pos);
  lcd.print(txt);
  lcd.setCursor(12, pos);
  if ((isInEditItem) && (sel)) {
    lcd.print(data);
    lcd.cursor();
  } else {
    lcd.print(item);
  }
}
void drawItemCapacidad(uint8_t pos, bool sel, uint16_t &item) {
  lcd.setCursor(0, pos);
  if (sel) {
    lcd.write(LCD_CHAR_SELECT);
  }
  lcd.setCursor(1, pos);
  lcd.print(F("Capacidad:"));
  lcd.setCursor(12, pos);
  if ((isInEditItem) && (sel)) {
    lcd.print(data);
    lcd.cursor();
  } else {
    lcd.print(item);
  }
}

void drawAyuda() {
  lcd.setCursor(0, 0);
  if (isInEditItem) {
    lcd.print(F("*-Bor #-Guar D-<"));
  } else {
    lcd.print(F("A-Edt B-"));
    lcd.write(LCD_CHAR_UP);
    lcd.setCursor(9, 0);
    lcd.print(F("C-"));
    lcd.write(LCD_CHAR_DOWN);
    lcd.setCursor(13, 0);
    lcd.print(F("D-<"));
  }
}

void uiEditPantallaHandler() {
  drawAyuda();
  switch (currentItem) {
  case CAPACIDAD: // capacidad
    drawItemCapacidad(1, true, botellas[currentBotella].capacidad);
    break;
  case TLLENADO:
    drawItem(1, true, F("TMov Llen:"), botellas[currentBotella].tLlenado);
    break;
  case TESTCO2:
    drawItem(1, true, F("TMov Tapa:"), botellas[currentBotella].tEstCO2);
    break;
  }
}
#endif // UIEDIT_H