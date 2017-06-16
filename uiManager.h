#ifndef UIMANAGER_H
#define UIMANAGER_H

#include "globalVars.h"
#include "uiMain.h"
#include "uiCargar.h"
#include "uiEdit.h"
#include "uiControlManual.h"

void tecladoHandler() {
  char key = Teclado.getKey();
  if (key) {
    switch (currentUi) {
    case UIMAIN:
      uiMainTecladoHandler(key);
      break;
    case UIEDIT:
      uiEditTecladoHandler(key);
      break;
    case UICARGAR:
      uiCargarTecladoHandler(key);
      break;
    case UICONTROLMANUAL:
      uiControlManualTecladoHandler(key);
      break;
    }
  }
}
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
  case UICONTROLMANUAL:
    uiControlManualPantallaHandler();
    break;
  }
}

void uiHandler() {
  tecladoHandler();
  pantallaHandler();
}
#endif // UIMANAGER_H