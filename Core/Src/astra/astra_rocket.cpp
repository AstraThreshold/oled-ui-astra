//
// Created by Fir on 2024/3/7 007.
//

#include <vector>
#include "astra_rocket.h"

astra::Launcher* astraLauncher = new astra::Launcher();
astra::Menu* rootPage = new astra::Menu("root");
astra::Camera* camera = new astra::Camera();

void astraCoreInit(void) {
  HAL::inject(new HALDreamCore);

  HAL::delay(100);
  HAL::printInfo("loading.");
  HAL::delay(500);
  HAL::printInfo("astra ui by dcfsswindy.");
  HAL::delay(100);
  HAL::printInfo("welcome.");
  HAL::delay(100);
  HAL::printInfo("welcome.");

  rootPage->addItem(new astra::Menu("测试1"));
  rootPage->addItem(new astra::Menu("测试2"));
  rootPage->addItem(new astra::Menu("测试3"));
  rootPage->addItem(new astra::Menu("测试4"));

  astraLauncher->init(rootPage);
}

void astraCoreStart(void) {
  for (;;) {  //NOLINT
    HAL::setDrawType(1);
    HAL::canvasClear();
    rootPage->render(camera); //这样就ok
    //astraLauncher->start(); //todo camera的问题 如果给camera赋值为00 就可以了
    HAL::canvasUpdate();
    //astraCoreTest();
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
