//
// Created by Fir on 2024/2/2.
//

#include "launcher.h"

namespace astra {

void Launcher::init(Menu *_rootPage) {
  currentPage = _rootPage;
  _rootPage->init();

  camera = new Camera(0, 0);
  if (currentPage->selfType == Menu::LIST)
    camera->go(currentPage->getItemPosition(currentPage->selectIndex).xTrg - getUIConfig().listTextMargin,
               currentPage->getItemPosition(currentPage->selectIndex).yTrg - getUIConfig().listTextMargin);
  else if (currentPage->selfType == Menu::TILE) //todo 想一想磁贴页的摄像机初始化在哪里
    camera->go(currentPage->getItemPosition(currentPage->selectIndex).xTrg,
               currentPage->getItemPosition(currentPage->selectIndex).yTrg);

  selector = new Selector();
  selector->inject(_rootPage);
  selector->go(2);
}

bool Launcher::open() {
  //todo 打开和关闭都还没写完 应该还漏掉了一部分内容
  if (currentPage->getNext() == nullptr) return false;

  currentPage->deInit();  //先析构（退场动画）再挪动指针
  currentPage = currentPage->getNext();

  currentPage->init();

  selector->inject(currentPage);
  selector->go(currentPage->selectIndex);

  if (currentPage->selfType == Menu::LIST)
    camera->go(currentPage->getItemPosition(currentPage->selectIndex).xTrg - getUIConfig().listTextMargin,
               currentPage->getItemPosition(currentPage->selectIndex).yTrg);
  else if (currentPage->selfType == Menu::TILE) //todo 想一想磁贴页的摄像机初始化在哪里
    camera->go(currentPage->getItemPosition(currentPage->selectIndex).xTrg,
               currentPage->getItemPosition(currentPage->selectIndex).yTrg);

  return true;
}

bool Launcher::close() {
  if (currentPage->getPreview() == nullptr) return false;

  currentPage->deInit();  //先析构（退场动画）再挪动指针
  currentPage = currentPage->getPreview();

  currentPage->init();

  selector->inject(currentPage);
  selector->go(currentPage->selectIndex);

  if (currentPage->selfType == Menu::LIST)
    camera->go(currentPage->getItemPosition(currentPage->selectIndex).xTrg - getUIConfig().listTextMargin,
               currentPage->getItemPosition(currentPage->selectIndex).yTrg);
  else if (currentPage->selfType == Menu::TILE) //todo 想一想磁贴页的摄像机初始化在哪里
    camera->go(currentPage->getItemPosition(currentPage->selectIndex).xTrg,
               currentPage->getItemPosition(currentPage->selectIndex).yTrg);

  return true;
}

void Launcher::start() {
  HAL::canvasClear();
  currentPage->render(camera);
  selector->render(camera); //todo 这里有问题
  HAL::canvasUpdate();
//todo 看一下Rachel的按键扫描函数是怎么实现的

//  if (HAL::getAnyKey()) {
//    for (uint8_t i = 0; i < key::KEY_NUM; i++) {
//      if (key[i] == key::CLICK) {
//        if (i == 0) {}//selector去到上一个项目
//        if (i == 1) {}//selector去到下一个项目
//      } else if (key[i] == key::PRESS) {
//        if (i == 0) {}//退出当前项目
//        if (i == 1) {}//打开当前项目
//      }
//    }
//    memset(key, key::RELEASE, sizeof(key));
//  }
}
}