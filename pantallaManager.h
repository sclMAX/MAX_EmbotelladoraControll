#ifndef PANTALLAMANAGER_H
#define PANTALLAMANAGER_H

#include "globalVars.h"
//#include "uiEdit.h"
#include "uiMain.h"

void pantallaHandler() {
  switch (currentUi) {
  case UIMAIN:
    uiMainPantallaHandler();
    break;
  }
}
#endif // PANTALLAMANAGER_H