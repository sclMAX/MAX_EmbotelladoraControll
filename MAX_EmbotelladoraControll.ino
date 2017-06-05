#include "Botella.h"
#include "config.h"
#include "globalVars.h"
#include "pantallaManager.h"
#include "processManager.h"
#include "teclado.h"
#include "configStorage.h"

void setup() {
  readConfig();
  lcdInit();
  pantallaInit();
}

void loop() {
  Alarm.delay(0);
  tecladoHandler();
  pantallaHandler();
}
