
#include "globalVars.h"
#include "pantallaManager.h"
#include "teclado.h"
#include "Botella.h"
#include "config.h"
#include "processManager.h"

TBotella bot330;
void setup() {
  pantallaInit();
  llenarBotella(bot330); //######### PRUEBAS SOLAMENTE #####
  delay(3000);           //######### PRUEBAS SOLAMENTE #####
}

void loop() {
  Alarm.delay(0);
  tecladoHandler();
  pantallaHandler();
}
