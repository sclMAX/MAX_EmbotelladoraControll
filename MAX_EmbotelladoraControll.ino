#include <LiquidCrystal.h>
#include <Time.h>
#include <TimeLib.h>
#include <TimeAlarms.h>
#include "Botella.h"
#include "config.h"
#include "processManager.h"

LiquidCrystal lcd(RS, EN, D4, D5, D6, D7); //    ( RS, EN, d4, d5, d6, d7)
TBotella bot330;
void setup() {
    lcd.begin(16,2);
    lcd.print("Hola Mundo!");
    llenarBotella(bot330);

}

void loop() { Alarm.delay(0); }
