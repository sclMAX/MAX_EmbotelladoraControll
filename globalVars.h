#ifndef GLOBALVARS_H
#define GLOBALVARS_H

#include "Arduino.h"
#include "config.h"
#include "utils.h"
#include <LiquidCrystal.h>
#include <Time.h>
#include <TimeAlarms.h>
#include <TimeLib.h>
#include <stdio.h>
#include <stdlib.h>
#include "specialChar.h"

LiquidCrystal lcd(RS, EN, D4, D5, D6, D7); //    ( RS, EN, d4, d5, d6, d7)

#define LCD_CHAR_UP 0
#define LCD_CHAR_DOWN 1

void lcdInit(){
    lcd.createChar(LCD_CHAR_UP, flechaUp);
    lcd.createChar(LCD_CHAR_DOWN, flechaDown);
}

volatile bool isInProceso = false;
volatile bool isEmergencia = false;
volatile bool isInEdit = false;
uint16_t cantBotellas = 0;
unsigned long cantBeer = 0;
String msgProcesoActual = "";
//<PANTALLAS>
#define UIMAIN 0
#define UIEDIT 1

unsigned short currentUi = UIMAIN;
//</PANTALLAS>

#endif // GLOBALVARS_H