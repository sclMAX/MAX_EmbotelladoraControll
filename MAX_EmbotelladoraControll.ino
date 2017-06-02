
#include "globalVars.h"
#include "pantallaManager.h"
#include "teclado.h"
#include "Botella.h"
#include "config.h"
#include "processManager.h"

TBotella bot330;
void setup() {
  pantallaInit();
}

void loop() {
  Alarm.delay(0);
  tecladoHandler();
  pantallaHandler();
}
