#include "globalVars.h"
#include "configStorage.h"
#include "uiManager.h"

void setup() {
  readConfig();
  lcdInit();
}

void loop() {
  uiHandler();
  manageProcess();
}
