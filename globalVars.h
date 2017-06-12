#ifndef GLOBALVARS_H
#define GLOBALVARS_H

#include "Arduino.h"
#include "config.h"
#include "specialChar.h"
#include <LiquidCrystal.h>

typedef unsigned long ulong_t;
//<LCD>
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7); //    ( RS, EN, d4, d5, d6, d7)

void lcdInit() {
  lcd.createChar(LCD_CHAR_UP, flechaUp);
  lcd.createChar(LCD_CHAR_DOWN, flechaDown);
  lcd.createChar(LCD_CHAR_SELECT, select);
  //<SPLASH>
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print(F(" EMBOTELLADORA  "));
  lcd.setCursor(0, 1);
  lcd.print(F("  v1.0 by MAX   "));
  delay(3000);
  lcd.clear();
  //</SPLASH>
}

#define UIMAIN 0
#define UIEDIT 1
uint16_t currentUi = UIMAIN;
//</LCD>
//<PROCESO>
volatile bool isInProceso = false;
uint16_t cantBotellas = 0;
ulong_t cantBeer = 0;
ulong_t tBotellaToLlenado = 500; //(mseg.) Tiempo botella a llenador.
ulong_t tBotellaToTapado = 250;  //(mseg.) Tiempo botella a tapador.
ulong_t tBajaLlenador = 1000;    // (mseg.) Tiempo bajada llenador.
ulong_t tSubeLlenador = 250;     // (mseg.) Tiempo bajada llenador.
ulong_t tBarridoCO2In = 2000;    //(mseg.) Tiempo Ingreso CO2 Barrido.
ulong_t tBarridoCO2Out = 2000;   //(mseg.) Tiempo Salida CO2 Barrido.
ulong_t tPresurizado = 4000;     //(mseg.) Tiempo ingreso CO2 presurizado.
ulong_t tBajaTapador = 4000;     //(mseg.) Tiempo bajada tapador.
ulong_t tSubeTapador = 500;      //(mseg.) Tiempo subida tapador.
//</PROCESO>

#endif // GLOBALVARS_H