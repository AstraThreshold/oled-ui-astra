//
// Created by Fir on 2024/2/2.
//

#include "launcher.h"

namespace astra {

void Launcher::init(Menu *_rootPage) {
  currentPage = _rootPage;
  selector = new Selector();
  camera = new Camera();
}

bool Launcher::open() {
  //todo 打开和关闭都还没写完 应该还漏掉了一部分内容
  currentPage = currentPage->getNext();
}

bool Launcher::close() {
  currentPage = currentPage->getPreview();
}

void Launcher::start() {
  currentPage->render(camera);

//  //todo 不知道此处需不需要声明一个按键
//  //todo 复盘一下HAL的代码 看看需不需要单独声明一个按键
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