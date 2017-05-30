#include <LiquidCrystal.h>
#include <Time.h>
#include <TimeLib.h>
#include <TimeAlarms.h>
#include "config.h"

LiquidCrystal lcd(RS, EN, D4, D5, D6, D7); //    ( RS, EN, d4, d5, d6, d7)

void setup() {
    lcd.begin(16,2);
    lcd.print("Hola Mundo!");
}

void loop() { Alarm.delay(0); }
