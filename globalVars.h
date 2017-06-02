#ifndef GLOBALVARS_H
#define GLOBALVARS_H

#include "Arduino.h"
#include <stdio.h>   
#include <stdlib.h>
#include "utils.h"
#include "config.h"
#include <Time.h>
#include <TimeLib.h>
#include <TimeAlarms.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(RS, EN, D4, D5, D6, D7); //    ( RS, EN, d4, d5, d6, d7)

volatile bool isInProceso = false;
volatile bool isEmergencia = false;
volatile bool isInEdit = false;
uint16_t cantBotellas = 0;
float cantLitros = 0.0
//<PANTALLAS>
#define UIMAIN 0

unsigned short currentUi = UIMAIN;
//</PANTALLAS>

#endif // GLOBALVARS_H