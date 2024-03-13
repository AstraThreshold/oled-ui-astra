//
// Created by Fir on 2024/3/7 007.
//

#include "astra_rocket.h"

astra::Launcher* astraLauncher = new astra::Launcher();

void astraCoreInit(void) {
  HAL::inject(new HALDreamCore);
  astraLauncher->init(nullptr);

  HAL::printInfo("loading.");
  HAL::printInfo("astra ui by dcfsswindy.");
  HAL::printInfo("welcome.");
  HAL::printInfo("welcome.");
}

void astraCoreStart(void) {
  for (;;) {  //NOLINT
    //astraLauncher->start();
    astraCoreTest();
  }
}

void astraCoreTest(void) {
//  HAL::canvasClear();
//  HAL::setDrawType(1);
//  HAL::drawEnglish(0, 0, "ok.");
//  HAL::drawChinese(0, 16, "门");
//  HAL::drawHLine(2, 0, 47);
//  HAL::drawVLine(0, 35, 47);
//  HAL::drawVLine(0, 32, 12);
//  HAL::canvasUpdate();
}

void astraCoreDestroy(void) {
  HAL::destroy();
  delete astraLauncher;
}
