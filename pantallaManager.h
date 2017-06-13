#ifndef PANTALLAMANAGER_H
#define PANTALLAMANAGER_H

#include "globalVars.h"
#include "uiCargar.h"
#include "uiEdit.h"
#include "uiMain.h"

void pantallaHandler() {
  switch (currentUi) {
  case UIMAIN:
    uiMainPantallaHandler();
    break;
  case UIEDIT:
    uiEditPantallaHandler();
    break;
  case UICARGAR:
    uiCargarPantallaHandler();
    break;
  }
}
#endif // PANTALLAMANAGER_H