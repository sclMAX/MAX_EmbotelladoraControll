#ifndef UIEDIT_H
#define UIEDIT_H

#include "Botella.h"
#include "globalVars.h"
#include "configStorage.h"

short currentItem = 0;
volatile bool isInEditItem = false;
String data = "";
void uiEditTecladoHandler(char &key) {
  switch (key) {
  case '0' ... '9':
    data.concat(key);
    switch (currentItem) {
    case 0: // capacidad
      data =
          (data.toInt() > 0) ? ((data.toInt() < 2000) ? data : "2000") : data;
      break;
    case 1 ... 7: // tiempos
      data = (data.toInt() > 0) ? ((data.toInt() < 254) ? data : "254") : data;
      break;
    }
    break;
  case 'A':
    if (currentItem == 8) {
      currentUi = UIAUTOSETUP;
      lcd.clear();
    } else {
      isInEditItem = true;
      lcd.clear();
    }
    break;
  case 'B':
    if (!isInEditItem) {
      currentItem--;
      currentItem = (currentItem > 0) ? currentItem : 0;
      lcd.clear();
    }
    break;
  case 'C':
    if (!isInEditItem) {
      currentItem++;
      currentItem = (currentItem < 8) ? currentItem : 8;
      lcd.clear();
    }
    break;
  case 'D':
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
      saveConfig();
    }
    break;
  }
}

void drawItem(uint8_t pos, bool sel, const __FlashStringHelper *txt,
              byte &item) {
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

void uiEditPantallaHandler() {
  switch (currentItem) {
  case 0: // capacidad
    lcd.setCursor(0, 0);
    lcd.print(F("A-Ed "));
    lcd.setCursor(5, 0);
    lcd.print(F("B-"));
    lcd.write(LCD_CHAR_UP);
    lcd.setCursor(9, 0);
    lcd.print(F("C-"));
    lcd.write(LCD_CHAR_DOWN);
    lcd.setCursor(13, 0);
    lcd.print(F("D-<"));
    drawItemCapacidad(1, true, botellas[currentBotella].capacidad);
    break;
  case 1:
    drawItemCapacidad(0, false, botellas[currentBotella].capacidad);
    drawItem(1, true, F("TMov Llen:"), botellas[currentBotella].tMovLlenador);
    break;
  case 2:
    drawItem(0, false, F("TMov Llen:"), botellas[currentBotella].tMovLlenador);
    drawItem(1, true, F("TMov Tapa:"), botellas[currentBotella].tMovTapador);
    break;
  case 3:
    drawItem(0, false, F("TMov Tapa:"), botellas[currentBotella].tMovTapador);
    drawItem(1, true, F("TCO2 Carg:"),
             botellas[currentBotella].tCargaCO2_Barrido);
    break;
  case 4:
    drawItem(0, false, F("TCO2 Carg:"),
             botellas[currentBotella].tCargaCO2_Barrido);
    drawItem(1, true, F("TCO2 Desc:"),
             botellas[currentBotella].tDescargaCO2_Barrido);
    break;
  case 5:
    drawItem(0, false, F("TCO2 Desc:"),
             botellas[currentBotella].tDescargaCO2_Barrido);
    drawItem(1, true, F("T Llenado:"), botellas[currentBotella].tCargaBeer);
    break;
  case 6:
    drawItem(0, false, F("T Llenado:"), botellas[currentBotella].tCargaBeer);
    drawItem(1, true, F("T Es Beer:"), botellas[currentBotella].tEstBeer);
    break;
  case 7:
    drawItem(0, false, F("T Es Beer:"), botellas[currentBotella].tEstBeer);
    drawItem(1, true, F("T Est CO2:"), botellas[currentBotella].tEstCO2);
    break;
  case 8:
    drawItem(0, false, F("T Est CO2:"), botellas[currentBotella].tEstCO2);
    lcd.setCursor(0, 1);
    lcd.write(LCD_CHAR_SELECT);
    lcd.setCursor(1, 1);
    lcd.print(F("AUTO CONFIGURAR"));
    break;
  }
}
#endif // UIEDIT_H