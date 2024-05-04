//
// Created by Fir on 2024/3/7 007.
//

//todo warning flash used age >= 90.93%, will be damaged soon

#include <vector>
#include "astra_rocket.h"
#include "astra_logo.h"

void *operator new(size_t size) {
  void *res;
  if (size == 0)
    size = 1;
  res = malloc(size);
  while (true) {
    if (res) break;
  }
  return res;
}

void operator delete(void *p) { free(p); }

auto *astraLauncher = new astra::Launcher();
auto *rootPage = new astra::Tile("root");

bool test = false;
unsigned char testIndex = 0;

auto *secondPage = new astra::List("secondPage");

void astraCoreInit(void) {
  HAL::inject(new HALDreamCore);

  HAL::delay(350);
  astra::drawLogo(1000);

  rootPage->addItem(new astra::List("test1"));
  rootPage->addItem(new astra::List("测试2"));
  rootPage->addItem(new astra::List("测试测试3"));
  rootPage->addItem(new astra::List("测试测试3"));
  rootPage->addItem(secondPage);

  secondPage->addItem(new astra::List());
  secondPage->addItem(new astra::List("-测试2"), new astra::CheckBox(test));
  secondPage->addItem(new astra::Tile("-测试测试3"), new astra::PopUp(1, "测试", {"测试"}, testIndex));
  secondPage->addItem(new astra::Tile("-测试测试测试4"));
  secondPage->addItem(new astra::List("-测试测试测试5"));
//  secondPage->addItem(new astra::List("-测试测试测试6"));
//  secondPage->addItem(new astra::List("-测试测试测试6"));

  //todo 考虑是堆栈溢出

  astraLauncher->init(rootPage);
}

void astraCoreStart(void) {
  for (;;) {  //NOLINT
    astraLauncher->update();
//    astraCoreTest();
  }
}

void astraCoreDestroy(void) {
  HAL::destroy();
  delete astraLauncher;
}
