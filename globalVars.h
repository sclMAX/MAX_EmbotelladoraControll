#ifndef GLOBALVARS_H
#define GLOBALVARS_H

#include "Arduino.h"
#include "config.h"
#include "textos.h"
#include "specialChar.h"
#include <LiquidCrystal.h>
#include <Key.h>
#include <Keypad.h>

typedef unsigned long ulong_t;
//<LCD>
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7); //    ( RS, EN, d4, d5, d6, d7)

void lcdInit() {
  lcd.createChar(LCD_CHAR_UP, flechaUp);
  lcd.createChar(LCD_CHAR_DOWN, flechaDown);
  lcd.createChar(LCD_CHAR_BACK, flechaBack);
  //<SPLASH>
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print(F(" EMBOTELLADORA  "));
  lcd.setCursor(0, 1);
  lcd.print(F("  v2.0 by MAX   "));
  delay(3000);
  lcd.clear();
  //</SPLASH>
}

#define UIMAIN 0
#define UIEDIT 1
#define UICARGAR 2
#define UICONTROLMANUAL 3
uint16_t currentUi = UIMAIN;
//</LCD>
//<TECLADO>
const byte rows = 4;
const byte cols = 4;
char keys[rows][cols] = {{'1', '2', '3', 'A'},
                         {'4', '5', '6', 'B'},
                         {'7', '8', '9', 'C'},
                         {'*', '0', '#', 'D'}};
byte rowPins[rows] = {PINS_TECLADO_ROW};
byte colPins[cols] = {PINS_TECLADO_COL};
Keypad Teclado = Keypad(makeKeymap(keys), rowPins, colPins, rows, cols);
//</TECLADO>
//<PROCESO>
volatile bool isInProceso = false;
volatile bool isManual = false;
volatile bool isLleno = false;
String msgProceso = "";
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

inline float getCantBeerLitros() { return (float)cantBeer / 1000; }
//</PROCESO>

#endif // GLOBALVARS_H