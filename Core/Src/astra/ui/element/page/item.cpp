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

#include <utility>

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

void Animation::animation(float *_pos, float _posTrg, float _speed) {
  if (*_pos != _posTrg) {
    if (std::fabs(*_pos - _posTrg) < 0.15f) *_pos = _posTrg;
    else *_pos += (_posTrg - *_pos) / (_speed / 10.0f);
  }
}

Camera::Camera() {
  this->x = 0;
  this->xTrg = 0;
  this->y = 0;
  this->yTrg = 0;
}

void Camera::go(uint8_t _x, uint8_t _y) {
  animation(&x, _x, astraConfig.cameraAnimationSpeed);
  animation(&y, _y, astraConfig.cameraAnimationSpeed);
}

void Camera::reset() {
  animation(&x, 0, astraConfig.cameraAnimationSpeed);
  animation(&y, 0, astraConfig.cameraAnimationSpeed);
}

void Camera::goDirect(uint8_t _x, uint8_t _y) {
  x = _x;
  y = _y;
}

Menu::Menu(std::string _title) {
  this->title = std::move(_title);
  this->selfType = LIST;
  this->position.x = 0;
  this->position.y = 0;
  this->position.xTrg = 0;
  this->position.yTrg = 0;
  this->selectIndex = 0;
  this->init = false;
  this->parent = nullptr;
  this->child.clear();
  this->pic.clear();
}

Menu::Menu(std::string _title, std::vector<std::vector<uint8_t>> _pic) {
  this->title = std::move(_title);
  this->pic = std::move(_pic);
  this->selfType = TILE;
  this->position.x = 0;
  this->position.y = 0;
  this->position.xTrg = 0;
  this->position.yTrg = 0;
  this->selectIndex = 0;
  this->init = false;
  this->parent = nullptr;
  this->child.clear();
}

void Menu::render(Camera* _camera) {
  if (selfType == TILE) {
    Item::updateConfig();

    animation(&positionForeground.yDottedLine, astraConfig.tileDottedLineMargin, astraConfig.tileAnimationSpeed);
    animation(&positionForeground.yArrow, astraConfig.tileArrowTopMargin, astraConfig.tileAnimationSpeed);

    HAL::setDrawType(1);

    //draw pic.
    for (auto _iter : child) {
      if (astraConfig.tileUnfold) {
        if (!init) {
          _iter->position.x = 0 - astraConfig.tilePicWidth; //unfold from left.
          init = true;
        }
      }

      HAL::drawBMP(_iter->position.x + _camera->x, astraConfig.tilePicTopMargin + _camera->y, astraConfig.tilePicWidth, astraConfig.tilePicHeight, _iter->pic[0].data());
      animation(&_iter->position.x, _iter->position.xTrg, astraConfig.tileAnimationSpeed);

    }

    //draw left arrow.
    HAL::drawHLine(astraConfig.tileArrowMargin, positionForeground.yArrow, astraConfig.tileArrowWidth);
    HAL::drawPixel(astraConfig.tileArrowMargin + 1, positionForeground.yArrow + 1);
    HAL::drawPixel(astraConfig.tileArrowMargin + 2, positionForeground.yArrow + 2);
    HAL::drawPixel(astraConfig.tileArrowMargin + 1, positionForeground.yArrow - 1);
    HAL::drawPixel(astraConfig.tileArrowMargin + 2, positionForeground.yArrow - 2);

    //draw right arrow.
    HAL::drawHLine(systemConfig.screenWeight - astraConfig.tileArrowWidth - astraConfig.tileArrowMargin, positionForeground.yArrow, astraConfig.tileArrowWidth);
    HAL::drawPixel(systemConfig.screenWeight - astraConfig.tileArrowWidth, positionForeground.yArrow + 1);
    HAL::drawPixel(systemConfig.screenWeight - astraConfig.tileArrowWidth - 1, positionForeground.yArrow + 2);
    HAL::drawPixel(systemConfig.screenWeight - astraConfig.tileArrowWidth, positionForeground.yArrow - 1);
    HAL::drawPixel(systemConfig.screenWeight - astraConfig.tileArrowWidth - 1, positionForeground.yArrow - 2);

    //draw left button.
    HAL::drawHLine(astraConfig.tileBtnMargin, positionForeground.yArrow + 2, 9);
    HAL::drawBox(astraConfig.tileBtnMargin + 2, positionForeground.yArrow + 2 - 4, 5, 4);

    //draw right button.
    HAL::drawHLine(systemConfig.screenWeight - astraConfig.tileBtnMargin - 9, positionForeground.yArrow + 2, 9);
    HAL::drawBox(systemConfig.screenWeight - astraConfig.tileBtnMargin - 9 + 2, positionForeground.yArrow + 2 - 4, 5, 4);

    //draw dotted line.
    HAL::drawHDottedLine(0, (int16_t) positionForeground.yDottedLine, systemConfig.screenWeight);

  } else if (selfType == LIST) {
    Item::updateConfig();

    HAL::setDrawType(1);

    //allow x > screen height, y > screen weight.
    for (auto _iter : child) {
      if (astraConfig.listUnfold) {
        if (!init) {
          _iter->position.y = 0; //unfold from top.
          init = true;
        }
      }

      HAL::drawChinese(_iter->position.x + _camera->x, _iter->position.y + _camera->y, _iter->title);
      animation(&_iter->position.y, _iter->position.yTrg, astraConfig.menuAnimationSpeed);
    }

    //todo draw bar.
    HAL::drawHLine(systemConfig.screenWeight - astraConfig.listBarWeight, 0, astraConfig.listBarWeight);
    HAL::drawHLine(systemConfig.screenWeight - astraConfig.listBarWeight, systemConfig.screenHeight - 1, astraConfig.listBarWeight);
    HAL::drawVLine(systemConfig.screenWeight - ceil((float) astraConfig.listBarWeight / 2.0f), 0, systemConfig.screenHeight);
    //HAL::drawBox(systemConfig.screenWeight - astraConfig.listBarWeight, 0, astraConfig.listBarWeight, yBar);

    //light mode.
    HAL::setDrawType(2);
    if (astraConfig.lightMode) HAL::drawBox(0, 0, systemConfig.screenWeight, systemConfig.screenHeight);
    HAL::setDrawType(1);
  }
}

uint8_t Menu::getItemNum() const {
  return child.size();
}

Menu::Position Menu::getItemPosition(uint8_t _index) const {
  return child[_index]->position;
}

Menu *Menu::getNext() const {
  return child[selectIndex];
}

Menu *Menu::getPreview() const {
  return parent;
}

bool Menu::addItem(Menu *_page) {
  if (_page == nullptr) return false;
  else {
    //加入的第一个元素的类型决定了当前节点所有子元素的类型
    if (this->child.empty()) this->childType = _page->selfType;

    if (this->childType == _page->selfType) {
      _page->parent = this;
      this->child.push_back(_page);
      if (_page->selfType == LIST) {
        _page->position.x = astraConfig.listTextMargin;
        _page->position.xTrg = astraConfig.listTextMargin;
        _page->position.y = astraConfig.listTextMargin + this->getItemNum() * astraConfig.listLineHeight;
        _page->position.yTrg = astraConfig.listTextMargin + this->getItemNum() * astraConfig.listLineHeight;
      }
      if (_page->selfType == TILE) {
        _page->position.x = astraConfig.tilePicMargin + this->getItemNum() * astraConfig.tilePicWidth;
        _page->position.xTrg = astraConfig.tilePicMargin + this->getItemNum() * astraConfig.tilePicWidth;
        _page->position.y = astraConfig.tilePicTopMargin;
        _page->position.yTrg = astraConfig.tilePicTopMargin;
      }
      return true;
    } else return false;
  }
}

Selector::Selector() {
  this->x = 0;
  this->xTrg = 0;
  this->y = 0;
  this->yTrg = 0;
  this->w = 0;
  this->wTrg = 0;
}

bool Selector::inject(Menu *_menu) {
  if (_menu == nullptr) return false;
  if (this->menu != nullptr) return false;
}

bool Selector::destroy() {
  if (this->menu == nullptr) return false;

  delete this->menu;
  this->menu = nullptr;
}

void Selector::render(Camera* _camera) {
  Item::updateConfig();

  ////todo 未来可以做一个从磁贴大框向列表选择框的过渡动画 画的大框逐渐变小 最终变成选择框那么大 全过程都是没有R角 过渡完成后直接画R角的选择框即可
  ////todo 从列表到磁贴同理
  ////todo 判断依据 当目前进入的页面类型不等于前级页面类型时 执行过渡动画
  ////todo 如此这般的话 就需要增加两个坐标变量分别代表大框的长和宽 绘制时就不能直接从config中取了
  animation(&x, xTrg, astraConfig.selectorAnimationSpeed);
  animation(&y, yTrg, astraConfig.selectorAnimationSpeed);

  if (menu->selfType == Menu::TILE) {
    animation(&yText, yTextTrg, astraConfig.selectorAnimationSpeed);
    //animation(&wFrame, wFrameTrg, astraConfig.selectorAnimationSpeed);
    //animation(&hFrame, hFrameTrg, astraConfig.selectorAnimationSpeed);

    //draw text.
    //文字不受摄像机的影响
    HAL::setDrawType(1);
    HAL::drawChinese((systemConfig.screenWeight - HAL::getFontWidth(menu->child[menu->selectIndex]->title)) / 2, yText, menu->child[menu->selectIndex]->title);

    //draw box.
    //大框需要受摄像机的影响
    HAL::setDrawType(2);
    HAL::drawFrame(x + _camera->x, y + _camera->y, astraConfig.tileSelectBoxWeight, astraConfig.tileSelectBoxHeight);
    //HAL::drawFrame(x + _camera->x, y + _camera->y, wFrame, hFrame);

  } else if (menu->selfType == Menu::LIST) {
    animation(&w, wTrg, astraConfig.selectorAnimationSpeed);
    //animation(&h, hTrg, astraConfig.selectorAnimationSpeed);

    //draw select box.
    //受摄像机的影响
    HAL::setDrawType(2);
    HAL::drawRBox(x + _camera->x, y + _camera->y, w, astraConfig.listLineHeight, astraConfig.selectorRadius);
    //HAL::drawRBox(x + _camera->x, y + _camera->y, w, h, astraConfig.selectorRadius);
    HAL::setDrawType(1);
  }
}

void Selector::go(uint8_t _index) {
  Item::updateConfig();

  ////todo 在go的时候改变trg的值

  if (menu->selfType == Menu::TILE) {

    if (menu->selfType != menu->child[_index]->selfType) { /*todo 过渡动画 从大框到选择框*/ }

    xTrg = menu->child[_index]->position.x - (astraConfig.tileSelectBoxWeight - astraConfig.tilePicWidth) / 2;
    yTrg = menu->child[_index]->position.y - (astraConfig.tileSelectBoxHeight - astraConfig.tilePicHeight) / 2;

    yText = systemConfig.screenHeight; //给磁贴文字归零 从屏幕外滑入


  } else if (menu->selfType == Menu::LIST) {

    if (menu->selfType != menu->child[_index]->selfType) { /*todo 过渡动画 从选择框到大框*/ }

    xTrg = menu->child[_index]->position.x - astraConfig.selectorMargin;
    yTrg = menu->child[_index]->position.y - astraConfig.selectorTopMargin;
    wTrg = HAL::getFontWidth(menu->child[_index]->title) + astraConfig.listTextMargin * 2;
  }
}
}
