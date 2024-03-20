//
// Created by Fir on 2024/3/7 007.
//

#include <vector>
#include "astra_rocket.h"

astra::Launcher* astraLauncher = new astra::Launcher();
astra::Menu* rootPage = new astra::Menu("root");

std::vector<uint8_t> pic = {
    0xFF, 0xFF, 0xFF, 0x3F, 0xFF, 0xFF, 0xFF, 0x3F, 0xFF, 0xFF, 0xFF, 0x3F, 0xFF, 0xFF, 0xF1, 0x3F,
    0xFF, 0xFF, 0xC3, 0x3F, 0xFF, 0xFF, 0x87, 0x3F, 0xFF, 0xFF, 0x07, 0x3F, 0xFF, 0xFF, 0x0F, 0x3E,
    0xFF, 0xFF, 0x0F, 0x3E, 0xFF, 0xFF, 0x0F, 0x3C, 0xFF, 0xFF, 0x0F, 0x3C, 0xFF, 0xFF, 0x0F, 0x38,
    0xFF, 0xFF, 0x0F, 0x38, 0xFF, 0xFF, 0x0F, 0x38, 0xFF, 0xFF, 0x07, 0x38, 0xFF, 0xFF, 0x07, 0x38,
    0xFF, 0xFF, 0x03, 0x38, 0xF7, 0xFF, 0x01, 0x38, 0xE7, 0xFF, 0x00, 0x3C, 0x87, 0x3F, 0x00, 0x3C,
    0x0F, 0x00, 0x00, 0x3E, 0x0F, 0x00, 0x00, 0x3E, 0x1F, 0x00, 0x00, 0x3F, 0x3F, 0x00, 0x80, 0x3F,
    0x7F, 0x00, 0xC0, 0x3F, 0xFF, 0x01, 0xF0, 0x3F, 0xFF, 0x07, 0xFC, 0x3F, 0xFF, 0xFF, 0xFF, 0x3F,
    0xFF, 0xFF, 0xFF, 0x3F, 0xFF, 0xFF, 0xFF, 0x3F
};

astra::Menu* secondPage = new astra::Menu("secondPage");
//astra::Menu* secondPage = new astra::Menu("secondPage", pic);

void astraCoreInit(void) {
  HAL::inject(new HALDreamCore);

  HAL::delay(100);
  HAL::printInfo("loading...");
  HAL::delay(500);
  HAL::printInfo("astra UI by dcfsswindy.");
  HAL::delay(100);
  HAL::printInfo("If stuck on this page,");
  HAL::delay(100);
  HAL::printInfo("check your program!");
  HAL::delay(100);

  rootPage->addItem(new astra::Menu("test1", pic));
  rootPage->addItem(new astra::Menu("测试2", pic));
  rootPage->addItem(new astra::Menu("测试测试3", pic));
  rootPage->addItem(secondPage);

//  rootPage->addItem(new astra::Menu("test1"));
//  rootPage->addItem(new astra::Menu("测试2"));
//  rootPage->addItem(new astra::Menu("测试测试3"));
//  rootPage->addItem(new astra::Menu("测试测试测试4"));
//  rootPage->addItem(new astra::Menu("测试测试测试5"));
//  rootPage->addItem(secondPage);

  secondPage->addItem(new astra::Menu("test1"));
  secondPage->addItem(new astra::Menu("测试2"));
  secondPage->addItem(new astra::Menu("测试测试3"));
  secondPage->addItem(new astra::Menu("测试测试测试4"));
  secondPage->addItem(new astra::Menu("测试测试测试5"));
  secondPage->addItem(new astra::Menu("测试测试测试6"));

  astraLauncher->init(rootPage);
}

void astraCoreStart(void) {
  for (;;) {  //NOLINT
    HAL::setDrawType(1);

    astraLauncher->start();

    //astraCoreTest();
  }
}

void astraCoreTest(void) {
  HAL::canvasClear();
  HAL::setDrawType(1);
  HAL::drawEnglish(0, 0, "ok.");
  HAL::drawChinese(0, 16, "门");
  HAL::drawHLine(2, 0, 47);
  HAL::drawVLine(0, 35, 47);
  HAL::drawVLine(0, 32, 12);
  HAL::canvasUpdate();
}

void astraCoreDestroy(void) {
  HAL::destroy();
  delete astraLauncher;
}
