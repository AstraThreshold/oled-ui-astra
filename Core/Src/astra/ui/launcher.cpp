//
// Created by Fir on 2024/2/2.
//

#include "launcher.h"

namespace astra {

void Launcher::init(Menu *_rootPage) {
  currentPage = _rootPage;
  _rootPage->init();

  camera = new Camera(0, 0);

  selector = new Selector();
  selector->inject(_rootPage);
  selector->go(_rootPage->selectIndex);

  currentPage->init();

  open();
}

/**
 * @brief 打开选中的页面
 *
 * @return 是否成功打开
 */
bool Launcher::open() {
  //todo 打开和关闭都还没写完 应该还漏掉了一部分内容

  //如果当前页面指向的当前item没有后继 那就返回false
  if (currentPage->getNext() == nullptr) return false;
  if (currentPage->getNext()->getItemNum() == 0) return false;

  currentPage->deInit();  //先析构（退场动画）再挪动指针

  currentPage = currentPage->getNext();
  selector->inject(currentPage);

  currentPage->init();
  selector->go(currentPage->selectIndex);

  return true;
}

/**
 * @brief 关闭选中的页面
 *
 * @return 是否成功关闭
 */
bool Launcher::close() {
  if (currentPage->getPreview() == nullptr) return false;
  if (currentPage->getPreview()->getItemNum() == 0) return false;

  currentPage->deInit();  //先析构（退场动画）再挪动指针
  currentPage = currentPage->getPreview();

  currentPage->init();

  selector->inject(currentPage);
  selector->go(currentPage->selectIndex);

  return true;
}

void Launcher::start() {
  HAL::canvasClear();

  currentPage->render(camera->getPosition());
  selector->render(camera->getPosition());
  camera->update(currentPage);

  //open();

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