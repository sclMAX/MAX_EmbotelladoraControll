#ifndef GLOBALVARS_H
#define GLOBALVARS_H

#include "Arduino.h"
#include "config.h"
#include "utils.h"
#include <LiquidCrystal.h>
#include <Time.h>
#include <TimeAlarms.h>
#include <TimeLib.h>
#include "specialChar.h"

LiquidCrystal lcd(RS, EN, D4, D5, D6, D7); //    ( RS, EN, d4, d5, d6, d7)

#define LCD_CHAR_UP 1
#define LCD_CHAR_DOWN 2
#define LCD_CHAR_SELECT 3

void lcdInit() {
  lcd.createChar(LCD_CHAR_UP, flechaUp);
  lcd.createChar(LCD_CHAR_DOWN, flechaDown);
  lcd.createChar(LCD_CHAR_SELECT, select);
}

bool isInProceso = false;
bool isEmergencia = false;
uint16_t cantBotellas = 0;
unsigned long cantBeer = 0;
__FlashStringHelper *msgProcesoActual = 0;
time_t initTime = 0;
byte *currentVar = 0;

//<PANTALLAS>
#define UIMAIN 0
#define UIEDIT 1
#define UIAUTOSETUP 2

uint16_t currentUi = UIMAIN;
//</PANTALLAS>

#endif // GLOBALVARS_H