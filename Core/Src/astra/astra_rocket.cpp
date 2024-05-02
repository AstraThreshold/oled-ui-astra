//
// Created by Fir on 2024/3/7 007.
//

//todo warning flash used age >= 90.93%, will be damaged soon

#include <vector>
#include "astra_rocket.h"
#include "astra_logo.h"

astra::Launcher *astraLauncher = new astra::Launcher();
astra::Menu *rootPage = new astra::Tile("root");

bool test = false;

astra::Menu *secondPage = new astra::Tile("secondPage");
astra::Menu *thirdPage = new astra::List("thirdPage");
//astra::Menu *fourthPage = new astra::List("fourthPage");

void astraCoreInit(void) {
  HAL::inject(new HALDreamCore);

  HAL::delay(350);
  astra::drawLogo(1000);

  rootPage->addItem(new astra::List("test1"));
  rootPage->addItem(new astra::List("测试2"));
  rootPage->addItem(new astra::List("测试测试3"));
  rootPage->addItem(new astra::List("测试测试测试4"));
  rootPage->addItem(secondPage);

  secondPage->addItem(new astra::List());
  secondPage->addItem(new astra::List("-测试2"), new astra::CheckBox(test));
  secondPage->addItem(new astra::Tile("-测试测试3"));
  secondPage->addItem(thirdPage);

  thirdPage->addItem(new astra::Tile());
//  thirdPage->addItem(new astra::List("测试1"));
//  thirdPage->addItem(new astra::List("测试2"));


  //todo 考虑是new太多了引发的问题
//  fourthPage->addItem(new astra::List("测试2"));

  astraLauncher->init(rootPage);
}

void astraCoreStart(void) {
  for (;;) {  //NOLINT
    astraLauncher->update();
//    astraCoreTest();
  }
}

void astraCoreTest(void) {
  HAL::canvasClear();
  HAL::setDrawType(1);
  HAL::drawEnglish(50, 20, "Hello, World!");
  HAL::canvasUpdate();
}

void astraCoreDestroy(void) {
  HAL::destroy();
  delete astraLauncher;
}
