#ifndef CONFIGSTORAGE_H
#define CONFIGSTORAGE_H

#include "Arduino.h"
#include "Botella.h"
#include "globalVars.h"
#include <EEPROM.h>

#define version 2

int eeAdress = 0;
void incAdress(int cantidad) { eeAdress += cantidad; }
void saveConfig() {
  eeAdress = 0;
  uint16_t tmpUint = 0;
  ulong_t tmpUlong = 0;
  EEPROM.put(eeAdress, version);
  incAdress(sizeof(int));
  EEPROM.get(eeAdress, tmpUint);
  if (tmpUint != cantBotellas) {
    EEPROM.put(eeAdress, cantBotellas);
  }
  incAdress(sizeof(cantBotellas));
  EEPROM.get(eeAdress, tmpUlong);
  if (tmpUlong != cantBeer) {
    EEPROM.put(eeAdress, cantBeer);
  }
  incAdress(sizeof(cantBeer));
  EEPROM.get(eeAdress, tmpUlong);
  if (tmpUlong != tBotellaToLlenado) {
    EEPROM.put(eeAdress, tBotellaToLlenado);
  }
  incAdress(sizeof(tBotellaToLlenado));
  EEPROM.get(eeAdress, tmpUlong);
  if (tmpUlong != tBotellaToTapado) {
    EEPROM.put(eeAdress, tBotellaToTapado);
  }
  incAdress(sizeof(tBotellaToTapado));
  EEPROM.get(eeAdress, tmpUlong);
  if (tmpUlong != tBajaLlenador) {
    EEPROM.put(eeAdress, tBajaLlenador);
  }
  incAdress(sizeof(tBajaLlenador));
  EEPROM.get(eeAdress, tmpUlong);
  if (tmpUlong != tSubeLlenador) {
    EEPROM.put(eeAdress, tSubeLlenador);
  }
  incAdress(sizeof(tSubeLlenador));
  EEPROM.get(eeAdress, tmpUlong);
  if (tmpUlong != tBarridoCO2In) {
    EEPROM.put(eeAdress, tBarridoCO2In);
  }
  incAdress(sizeof(tBarridoCO2In));
  EEPROM.get(eeAdress, tmpUlong);
  if (tmpUlong != tBarridoCO2Out) {
    EEPROM.put(eeAdress, tBarridoCO2Out);
  }
  incAdress(sizeof(tBarridoCO2Out));
  EEPROM.get(eeAdress, tmpUlong);
  if (tmpUlong != tPresurizado) {
    EEPROM.put(eeAdress, tPresurizado);
  }
  incAdress(sizeof(tPresurizado));
  EEPROM.get(eeAdress, tmpUlong);
  if (tmpUlong != tBajaTapador) {
    EEPROM.put(eeAdress, tBajaTapador);
  }
  incAdress(sizeof(tBajaTapador));
  EEPROM.get(eeAdress, tmpUlong);
  if (tmpUlong != tSubeTapador) {
    EEPROM.put(eeAdress, tSubeTapador);
  }
  incAdress(sizeof(tSubeTapador));
  TBotella tmpBotella;
  for (int i = 0; i < botellasTam; i++) {
    EEPROM.get(eeAdress, tmpBotella);
    if ((tmpBotella.capacidad != botellas[i].capacidad) ||
        (tmpBotella.tLlenado != botellas[i].tLlenado) ||
        (tmpBotella.tEstCO2 != botellas[i].tEstCO2)) {
      EEPROM.put(eeAdress, botellas[i]);
    }
    eeAdress += sizeof(TBotella);
  }
}

void readConfig() {
  eeAdress = 0;
  int eeVersion = 0;
  EEPROM.get(eeAdress, eeVersion);
  if (eeVersion == version) {
    incAdress(sizeof(int));
    EEPROM.get(eeAdress, cantBotellas);
    incAdress(sizeof(cantBotellas));
    EEPROM.get(eeAdress, cantBeer);
    incAdress(sizeof(cantBeer));
    EEPROM.get(eeAdress, tBotellaToLlenado);
    incAdress(sizeof(tBotellaToLlenado));
    EEPROM.get(eeAdress, tBotellaToTapado);
    incAdress(sizeof(tBotellaToTapado));
    EEPROM.get(eeAdress, tBajaLlenador);
    incAdress(sizeof(tBajaLlenador));
    EEPROM.get(eeAdress, tSubeLlenador);
    incAdress(sizeof(tSubeLlenador));
    EEPROM.get(eeAdress, tBarridoCO2In);
    incAdress(sizeof(tBarridoCO2In));
    EEPROM.get(eeAdress, tBarridoCO2Out);
    incAdress(sizeof(tBarridoCO2Out));
    EEPROM.get(eeAdress, tPresurizado);
    incAdress(sizeof(tPresurizado));
    EEPROM.get(eeAdress, tBajaTapador);
    incAdress(sizeof(tBajaTapador));
    EEPROM.get(eeAdress, tSubeTapador);
    incAdress(sizeof(tSubeTapador));

    for (int i = 0; i < botellasTam; i++) {
      EEPROM.get(eeAdress, botellas[i]);
      eeAdress += sizeof(TBotella);
    }
  }
}

#endif // CONFIGSTORAGE_H