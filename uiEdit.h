#ifndef UIEDIT_H
#define UIEDIT_H

#include "Botella.h"
#include "globalVars.h"
#include "configStorage.h"

enum items {
  CAPACIDAD,
  TLLENADO,
  TESTCO2,
  TMOVTOLLENADO,
  TMOVTOTAPADO,
  TBAJALLENADOR,
  TSUBELLENADOR,
  TBARRIDOCO2IN,
  TBARRIDOCO2OUT,
  TPRESURIZADO,
  TBAJATAPADOR,
  TSUBETAPADOR
};
#define itemsTam 12
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
  case 'A': // Arriba
    if (!isInEditItem) {
      currentItem = currentItem - 1;
      currentItem = (currentItem > 0) ? currentItem : itemsTam - 1;
      lcd.clear();
    }
    break;
  case 'B': // Abajo
    if (!isInEditItem) {
      currentItem = currentItem + 1;
      currentItem = (currentItem < itemsTam) ? currentItem : 0;
      lcd.clear();
    }
    break;
  case 'C': // Atras
    if (isInEditItem) {
      isInEditItem = false;
    } else {
      lcd.clear();
      currentUi = UIMAIN;
    }
    break;
  case '*': // Borrar
    if (isInEditItem) {
      data = "";
      lcd.clear();
    }
    break;
  case '#': // Editar o Guardar
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
      case TMOVTOLLENADO:
        tBotellaToLlenado = data.toInt();
        break;
      case TMOVTOTAPADO:
        tBotellaToTapado = data.toInt();
        break;
      case TBAJALLENADOR:
        tBajaLlenador = data.toInt();
        break;
      case TSUBELLENADOR:
        tSubeLlenador = data.toInt();
        break;
      case TBARRIDOCO2IN:
        tBarridoCO2In = data.toInt();
        break;
      case TBARRIDOCO2OUT:
        tBarridoCO2Out = data.toInt();
        break;
      case TPRESURIZADO:
        tPresurizado = data.toInt();
        break;
      case TBAJATAPADOR:
        tBajaTapador = data.toInt();
        break;
      case TSUBETAPADOR:
        tSubeTapador = data.toInt();
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
  lcd.print(txt);
  lcd.setCursor(10, pos);
  if ((isInEditItem) && (sel)) {
    lcd.print(data);
  } else {
    lcd.print(item);
  }
}
void drawItemCapacidad(uint8_t pos, bool sel, uint16_t &item) {
  lcd.setCursor(0, pos);
  lcd.print(F("Capacidad:"));
  lcd.setCursor(10, pos);
  if ((isInEditItem) && (sel)) {
    lcd.print(data);
  } else {
    lcd.print(item);
  }
}

void drawAyuda() {
  lcd.setCursor(0, 0);
  if (isInEditItem) {
    lcd.print(F("*-Borr #-Guar C"));
    lcd.write(LCD_CHAR_BACK);
  } else {
    lcd.print(F("A"));
    lcd.write(LCD_CHAR_UP);
    lcd.setCursor(3, 0);
    lcd.print(F("B"));
    lcd.write(LCD_CHAR_DOWN);
    lcd.setCursor(5, 0);
    lcd.print(F(" #-Editar C"));
    lcd.write(LCD_CHAR_BACK);
  }
}

void uiEditPantallaHandler() {
  drawAyuda();
  switch (currentItem) {
  case CAPACIDAD: // capacidad
    drawItemCapacidad(1, true, botellas[currentBotella].capacidad);
    break;
  case TLLENADO:
    drawItem(1, true, F("T Llenado:"), botellas[currentBotella].tLlenado);
    break;
  case TESTCO2:
    drawItem(1, true, F("T Est CO2:"), botellas[currentBotella].tEstCO2);
    break;
  case TMOVTOLLENADO:
    drawItem(1, true, F("T Mov Lle:"), tBotellaToLlenado);
    break;
  case TMOVTOTAPADO:
    drawItem(1, true, F("T Mov Tap:"), tBotellaToTapado);
    break;
  case TBAJALLENADOR:
    drawItem(1, true, F("T Baj Lle:"), tBajaLlenador);
    break;
  case TSUBELLENADOR:
    drawItem(1, true, F("T Sub Lle:"), tSubeLlenador);
    break;
  case TBARRIDOCO2IN:
    drawItem(1, true, F("T CO2 Ing:"), tBarridoCO2In);
    break;
  case TBARRIDOCO2OUT:
    drawItem(1, true, F("T CO2 Out:"), tBarridoCO2Out);
    break;
  case TPRESURIZADO:
    drawItem(1, true, F("T Presuri:"), tPresurizado);
    break;
  case TBAJATAPADOR:
    drawItem(1, true, F("T Baj Tap:"), tBajaTapador);
    break;
  case TSUBETAPADOR:
    drawItem(1, true, F("T Sub Tap:"), tSubeTapador);
    break;
  }
}
#endif // UIEDIT_H