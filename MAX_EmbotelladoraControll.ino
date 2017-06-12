#include "globalVars.h"
#include "pantallaManager.h"
#include "teclado.h"
#include "configStorage.h"

void setup() {
  readConfig();
  lcdInit();
}

void loop() {
  tecladoHandler();
  pantallaHandler();
  manageProcess();
}
