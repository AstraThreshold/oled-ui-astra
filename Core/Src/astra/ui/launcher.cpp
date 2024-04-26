//
// Created by Fir on 2024/2/2.
//

#include "launcher.h"

namespace astra {

void Launcher::popInfo(std::string _info, uint16_t _time) {
  static const uint64_t beginTime = this->time;
  static bool onRender = true;

  while (onRender) {
    time++;

    static float wPop = HAL::getFontWidth(_info) + 2 * getUIConfig().popMargin;  //宽度
    static float hPop = HAL::getFontHeight() + 2 * getUIConfig().popMargin;  //高度

    static float yPop = 0 - hPop - 8; //从屏幕上方滑入
    static float yPopTrg = 0;
    if (time - beginTime < _time) yPopTrg = (HAL::getSystemConfig().screenHeight - hPop) / 3;  //目标位置 中间偏上
    else yPopTrg = 0 - hPop - 8;  //滑出

    static float xPop = (HAL::getSystemConfig().screenWeight - wPop) / 2;  //居中

    HAL::canvasClear();
    /*渲染一帧*/
    currentMenu->render(camera->getPosition());
    selector->render(camera->getPosition());
    camera->update(currentMenu, selector);
    /*渲染一帧*/

    HAL::setDrawType(0);
    HAL::drawRBox(xPop - 4, yPop - 4, wPop + 8, hPop + 8, getUIConfig().popRadius + 2);
    HAL::setDrawType(1);  //反色显示
    HAL::drawRFrame(xPop - 1, yPop - 1, wPop + 2, hPop + 2, getUIConfig().popRadius);  //绘制一个圆角矩形
    HAL::drawEnglish(xPop + getUIConfig().popMargin, yPop + getUIConfig().popMargin + HAL::getFontHeight(), _info);  //绘制文字

    HAL::canvasUpdate();

    Animation::move(&yPop, yPopTrg, getUIConfig().popSpeed);  //动画

    //这里条件可以加上一个如果按键按下 就退出
    if (time - beginTime >= _time && yPop == 0 - hPop - 8) onRender = false;  //退出条件
  }
}

void Launcher::init(Menu *_rootPage) {
  currentMenu = _rootPage;

  camera = new Camera(0, 0);
  _rootPage->childPosInit(camera->getPosition());
  selector = new Selector();
  selector->inject(_rootPage);
  //selector->go(_rootPage->selectIndex);

  selector->go(3);

  //open();
}

/**
 * @brief 打开选中的页面
 *
 * @return 是否成功打开
 * @warning 仅可调用一次
 */
bool Launcher::open() {

  //如果当前页面指向的当前item没有后继 那就返回false
  if (currentMenu->getNextMenu() == nullptr) { popInfo("unreferenced page!", 600); return false; }
  if (currentMenu->getNextMenu()->getItemNum() == 0) { popInfo("empty page!", 600); return false; }

  currentMenu->deInit();  //先析构（退场动画）再挪动指针

  currentMenu = currentMenu->getNextMenu();
  currentMenu->childPosInit(camera->getPosition());

  selector->inject(currentMenu);
  //selector->go(currentPage->selectIndex);

  return true;
}

/**
 * @brief 关闭选中的页面
 *
 * @return 是否成功关闭
 * @warning 仅可调用一次
 */
bool Launcher::close() {
  if (currentMenu->getPreview() == nullptr) { popInfo("unreferenced page!", 600); return false; }
  if (currentMenu->getPreview()->getItemNum() == 0) { popInfo("empty page!", 600); return false; }

  currentMenu->deInit();  //先析构（退场动画）再挪动指针

  currentMenu = currentMenu->getPreview();
  currentMenu->childPosInit(camera->getPosition());

  selector->inject(currentMenu);
  //selector->go(currentPage->selectIndex);

  return true;
}

void Launcher::update() {
  HAL::canvasClear();

//  currentMenu->render(camera->getPosition());
//  if (currentWidget != nullptr) currentWidget->render(camera->getPosition());
//  selector->render(camera->getPosition());
//  camera->update(currentMenu, selector);
//
//  if (time == 500) selector->go(3);  //test
//  if (time == 800) open();  //test
//  if (time == 1200) selector->go(1);  //test
//  if (time == 1500) selector->goNext();  //test
//  if (time == 1800) selector->goPreview();  //test
//  if (time == 2100) selector->go(1);  //test
//  if (time == 2300) selector->go(0);  //test
//  if (time == 2500) open();  //test
//  if (time == 2900) close();
//  if (time == 3200) selector->go(0);  //test
//  if (time >= 3250) time = 0;  //test

  HAL::keyScan();
  if (HAL::getAnyKey()) HAL::drawEnglish(30, 30, "any key pressed");  //test
  else HAL::drawEnglish(30, 30, "no key pressed");  //test

  HAL::canvasUpdate();

  time++;

//  if (HAL::getAnyKey()) {
//    for (unsigned char i = 0; i < key::KEY_NUM; i++) {
//      if (HAL::getKeyMap()[i] == key::CLICK) {
//        if (i == 0) { selector->go(currentMenu->selectIndex--); }//selector去到上一个项目
//        if (i == 1) { selector->go(currentMenu->selectIndex++); }//selector去到下一个项目
//      } else if (HAL::getKeyMap()[i] == key::PRESS) {
//        if (i == 0) { close(); }//退出当前项目
//        if (i == 1) { open(); }//打开当前项目
//      }
//    }
//
//    std::fill(HAL::getKeyMap(), HAL::getKeyMap() + key::KEY_NUM, key::RELEASE);
//  }
}
}