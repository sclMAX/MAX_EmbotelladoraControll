
#include "Botella.h"
#include "config.h"
#include "globalVars.h"
#include "pantallaManager.h"
#include "processManager.h"
#include "teclado.h"

TBotella bot330;
void setup() {
  lcdInit();
  pantallaInit();
  botellas[0].capacidad = 330;
  botellas[1].capacidad = 450;
  botellas[2].capacidad = 500;
  botellas[3].capacidad = 710;
  botellas[4].capacidad = 740;
  botellas[5].capacidad = 970;
  botellas[6].capacidad = 1000;
}

void loop() {
  Alarm.delay(0);
  tecladoHandler();
  pantallaHandler();
}
