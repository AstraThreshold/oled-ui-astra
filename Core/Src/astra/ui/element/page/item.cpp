//
// Created by Fir on 2024/1/21.
//

//每个列表应该有 1. 文本（需要显示的内容） 2. 跳转向量表（对应1，每一行都要跳转到哪里）
//其中文本以string形式 向量表以vector形式 以类的形式整合在一起 编写相应的构造函数 调用构造函数即是新建一个页面
//通过最后一项跳转向量表可以判断其类型 比如跳转至下一页 或者返回上一级 或者是复选框 或者是弹窗 或者是侧边栏弹窗 等等
//做一个astra类作为总的框架 在ui命名空间里

//分为
//驱动层 - 界面层（包括各种列表 磁铁 复选框 侧边栏 弹窗等） - 处理层（各种坐标的变换等）

//传进去的有三个东西 第一个是文字（要显示的东西） 第二个是类别（普通列表 跳转列表 复选框） 第三个是特征向量（指向复选框和弹窗对应的参数 要跳转的地方等）
#include "item.h"

/**
 *     ·  ·     ·   ·
 *  ·   ·  ·  ·   ·
 *  循此苦旅，直抵群星。
 *  ad astra per aspera.
 * happy Chinese new year!
 *      新年快乐！
 * ·   ·   ·      ·
 *   ·   ·    · ·   ·
 */

namespace astra {

void Item::updateConfig() {
  this->systemConfig = HAL::getSystemConfig();
  this->astraConfig = getUIConfig();
}

void ListMenu::animation(float *_pos, float _posTrg, float _speed) {
  if (*_pos != _posTrg) {
    if (std::fabs(*_pos - _posTrg) < 0.15f) *_pos = _posTrg;
    else *_pos += (_posTrg - *_pos) / (_speed / 10.0f);
  }
}

inline void ListMenu::render() {
  Item::updateConfig();
  static uint8_t listMaxIndexPerPage = systemConfig.screenHeight / astraConfig.listLineHeight;

  HAL::setDrawType(1);

  //draw bar.
  HAL::drawHLine(systemConfig.screenWeight - astraConfig.listBarWeight, 0, astraConfig.listBarWeight);
  HAL::drawHLine(systemConfig.screenWeight - astraConfig.listBarWeight, systemConfig.screenHeight - 1, astraConfig.listBarWeight);
  HAL::drawVLine(systemConfig.screenWeight - ceil((float) astraConfig.listBarWeight / 2.0f), 0, systemConfig.screenHeight);
  HAL::drawBox(systemConfig.screenWeight - astraConfig.listBarWeight, 0, astraConfig.listBarWeight, yBar);

  //light mode.
  HAL::setDrawType(2);
  if (astraConfig.lightMode) HAL::drawBox(0, 0, systemConfig.screenWeight, systemConfig.screenHeight);
  HAL::setDrawType(1);
}

uint8_t ListMenu::getItemPosition(uint8_t _index) {
  return (int16_t) ((ListMenu*)child[_index])->y;
}

void TileMenu::animation(float *_pos, float _posTrg, float _speed) {
  if (*_pos != _posTrg) {
    if (std::fabs(*_pos - _posTrg) < 0.15f) *_pos = _posTrg;
    else *_pos += (_posTrg - *_pos) / (_speed / 10.0f);
  }
}

inline void TileMenu::render() {
  Item::updateConfig();

  animation(&yText, yTextTrg, astraConfig.tileAnimationSpeed);
  animation(&yDottedLine, astraConfig.tileDottedLineMargin, astraConfig.tileAnimationSpeed);
  animation(&yArrow, astraConfig.tileArrowTopMargin, astraConfig.tileAnimationSpeed);

  HAL::setDrawType(1);

  HAL::drawChinese((systemConfig.screenWeight - HAL::getFontWidth(((TileMenu*)child[select])->title)) / 2, yText, ((TileMenu*)child[select])->title);

  //draw left arrow.
  HAL::drawHLine(astraConfig.tileArrowMargin, yArrow, astraConfig.tileArrowWidth);
  HAL::drawPixel(astraConfig.tileArrowMargin + 1, yArrow + 1);
  HAL::drawPixel(astraConfig.tileArrowMargin + 2, yArrow + 2);
  HAL::drawPixel(astraConfig.tileArrowMargin + 1, yArrow - 1);
  HAL::drawPixel(astraConfig.tileArrowMargin + 2, yArrow - 2);

  //draw right arrow.
  HAL::drawHLine(systemConfig.screenWeight - astraConfig.tileArrowWidth - astraConfig.tileArrowMargin, yArrow, astraConfig.tileArrowWidth);
  HAL::drawPixel(systemConfig.screenWeight - astraConfig.tileArrowWidth, yArrow + 1);
  HAL::drawPixel(systemConfig.screenWeight - astraConfig.tileArrowWidth - 1, yArrow + 2);
  HAL::drawPixel(systemConfig.screenWeight - astraConfig.tileArrowWidth, yArrow - 1);
  HAL::drawPixel(systemConfig.screenWeight - astraConfig.tileArrowWidth - 1, yArrow - 2);

  //draw left button.
  HAL::drawHLine(astraConfig.tileBtnMargin, yArrow + 2, 9);
  HAL::drawBox(astraConfig.tileBtnMargin + 2, yArrow + 2 - 4, 5, 4);

  //draw right button.
  HAL::drawHLine(systemConfig.screenWeight - astraConfig.tileBtnMargin - 9, yArrow + 2, 9);
  HAL::drawBox(systemConfig.screenWeight - astraConfig.tileBtnMargin - 9 + 2, yArrow + 2 - 4, 5, 4);

  //draw dotted line.
  HAL::drawHDottedLine(0, (int16_t) yDottedLine, systemConfig.screenWeight);

  //light mode.
  HAL::setDrawType(2);
  if (astraConfig.lightMode) HAL::drawBox(0, 0, systemConfig.screenWeight, systemConfig.screenHeight);
  HAL::setDrawType(1);
}

void Selector::updateConfig() {
  astraConfig = getUIConfig();
}

void Selector::animation(float *_pos, float _posTrg, float _speed) {
  if (*_pos != _posTrg) {
    if (std::fabs(*_pos - _posTrg) < 0.15f) *_pos = _posTrg;
    else *_pos += (_posTrg - *_pos) / (_speed / 10.0f);
  }
}

void Selector::setPage(ListMenu *_page) {
  currentPage = _page;
  //todo 考虑修改此部分为pointToAMenu方法
  //想清楚选择器的功能 做一个函数get到当前选择器选择的指针即可 在启动器内进行处理
}

bool Selector::go(uint8_t _select) {
  currentPage->select = _select;  //todo 确认此处是否可以修改select的值
}

bool Selector::goNext() {
  if (currentPage->select <= 0) {
    if (astraConfig.menuLoop) currentPage->select = currentPage->getItemNum() - 1;
    else currentPage->select = 0;
  }
}

bool Selector::goPreview() {
  if (currentPage->select >= (currentPage->getItemNum() - 1)) {
    if (astraConfig.menuLoop) currentPage->select = 0;
    else currentPage->select = currentPage->getItemNum() - 1;
  }
}

bool Selector::open() {
  currentPage = (ListMenu*)(currentPage->child)[currentPage->select];
  //todo 不知道这b玩意放在启动器里还是放在这里 而且不知道这
}

bool Selector::close() {
  return false;
}

inline void Selector::render() {
  yTrg = currentPage->getItemPosition(currentPage->select);
  wTrg = HAL::getFontWidth(((ListMenu*)(currentPage->child)[currentPage->select])->title);

  animation(&w, wTrg, astraConfig.selectorAnimationSpeed);
  animation(&y, yTrg, astraConfig.selectorAnimationSpeed);

  //draw selector.
  HAL::setDrawType(2);
  HAL::drawRBox(0, y, w, astraConfig.listLineHeight, astraConfig.selectorRadius);
  HAL::setDrawType(1);
}




}
