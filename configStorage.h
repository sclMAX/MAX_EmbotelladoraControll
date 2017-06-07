#ifndef CONFIGSTORAGE_H
#define CONFIGSTORAGE_H

#include "Arduino.h"
#include "Botella.h"
#include "globalVars.h"
#include <EEPROM.h>

#define version  3
int eeAdress = 0;

void saveConfig() {
  eeAdress = 0;
  EEPROM.put(eeAdress, version);
  eeAdress += sizeof(int);
  for (int i = 0; i < botellasTam; i++) {
    EEPROM.put(eeAdress, botellas[i]);
    eeAdress += sizeof(TBotella);
  }
}

void readConfig() {
  eeAdress = 0;
  int eeVersion = 0;
  EEPROM.get(eeAdress, eeVersion);
  if (eeVersion == version) {
    eeAdress += sizeof(int);
    for (int i = 0; i < botellasTam; i++) {
      EEPROM.put(eeAdress, botellas[i]);
      eeAdress += sizeof(TBotella);
    }
  }else{
    botellas[0].capacidad = 330;
    botellas[1].capacidad = 450;
    botellas[2].capacidad = 500;
    botellas[3].capacidad = 710;
    botellas[4].capacidad = 740;
    botellas[5].capacidad = 970;
  }
}

#endif // CONFIGSTORAGE_H