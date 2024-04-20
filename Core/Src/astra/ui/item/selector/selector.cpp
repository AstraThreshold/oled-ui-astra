//
// Created by Fir on 2024/4/14 014.
//

#include "selector.h"

namespace astra {

/**
 * @brief
 *
 * @param _index
 * @note selector接管了移动选择指针的功能
 * @warning not support in loop. 不支持在循环内执行
 */
void Selector::go(unsigned char _index) {
  Item::updateConfig();

  menu->selectIndex = _index;

  //在go的时候改变trg的值
  if (menu->childType == Menu::TILE) {
//    xTrg = menu->child[_index]->position.xTrg - (astraConfig.tileSelectBoxWeight - astraConfig.tilePicWidth) / 2;
//    yTrg = menu->child[_index]->position.yTrg - (astraConfig.tileSelectBoxHeight - astraConfig.tilePicHeight) / 2;
    xTrg = menu->childMenu[_index]->position.xTrg - astraConfig.tileSelectBoxMargin;
    yTrg = menu->childMenu[_index]->position.yTrg - astraConfig.tileSelectBoxMargin;

    yText = systemConfig.screenHeight; //给磁贴文字归零 从屏幕外滑入
    yTextTrg = systemConfig.screenHeight - astraConfig.tileTextBottomMargin;

    wTrg = astraConfig.tileSelectBoxWidth;
    hTrg = astraConfig.tileSelectBoxHeight;
  } else if (menu->childType == Menu::LIST) {
    xTrg = menu->childMenu[_index]->position.xTrg - astraConfig.selectorMargin;
    yTrg = menu->childMenu[_index]->position.yTrg;

    wTrg = (float) HAL::getFontWidth(menu->childMenu[_index]->title) + astraConfig.listTextMargin * 2;
    hTrg = astraConfig.listLineHeight;
  }
}

bool Selector::inject(Menu *_menu) {
  if (_menu == nullptr) return false;

  //if (this->menu != nullptr) return false;
  this->menu = _menu;

  go(this->menu->selectIndex);  //注入之后要初始化选择框的位置

  return true;
}

bool Selector::destroy() {
  if (this->menu == nullptr) return false;

  delete this->menu;
  this->menu = nullptr;
}

void Selector::render(std::vector<float> _camera) {
  Item::updateConfig();

  //实际上 这里已经实现过渡动画了
  animation(&x, xTrg, astraConfig.selectorXAnimationSpeed);
  animation(&y, yTrg, astraConfig.selectorYAnimationSpeed);
  animation(&h, hTrg, astraConfig.selectorHeightAnimationSpeed);
  animation(&w, wTrg, astraConfig.selectorWidthAnimationSpeed);

  if (menu->childType == Menu::TILE) {
    animation(&yText, yTextTrg, astraConfig.selectorYAnimationSpeed);

    //draw text.
    //文字不受摄像机的影响
    HAL::setDrawType(1);
    HAL::drawChinese((systemConfig.screenWeight -
                      (float) HAL::getFontWidth(menu->childMenu[menu->selectIndex]->title)) / 2.0,
                     yText + astraConfig.tileTitleHeight,
                     menu->childMenu[menu->selectIndex]->title);

    //draw box.
    //大框需要受摄像机的影响
    HAL::setDrawType(2);
    HAL::drawPixel(x + _camera[0], y + _camera[1]);
    //左上角
    HAL::drawHLine(x + _camera[0], y + _camera[1], astraConfig.tileSelectBoxLineLength + 1);
    HAL::drawVLine(x + _camera[0], y + _camera[1], astraConfig.tileSelectBoxLineLength + 1);
    //左下角
    HAL::drawHLine(x + _camera[0], y + _camera[1] + h - 1, astraConfig.tileSelectBoxLineLength + 1);
    HAL::drawVLine(x + _camera[0],
                   y + _camera[1] + h - astraConfig.tileSelectBoxLineLength - 1,
                   astraConfig.tileSelectBoxLineLength);
    //右上角
    HAL::drawHLine(x + _camera[0] + w - astraConfig.tileSelectBoxLineLength - 1,
                   y + _camera[1],
                   astraConfig.tileSelectBoxLineLength);
    HAL::drawVLine(x + _camera[0] + w - 1, y + _camera[1], astraConfig.tileSelectBoxLineLength + 1);
    //右下角
    HAL::drawHLine(x + _camera[0] + w - astraConfig.tileSelectBoxLineLength - 1,
                   y + _camera[1] + h - 1,
                   astraConfig.tileSelectBoxLineLength);
    HAL::drawVLine(x + _camera[0] + w - 1,
                   y + _camera[1] + h - astraConfig.tileSelectBoxLineLength - 1,
                   astraConfig.tileSelectBoxLineLength);

    HAL::drawPixel(x + _camera[0] + w - 1, y + _camera[1] + h - 1);
  } else if (menu->childType == Menu::LIST) {
    //animation(&h, hTrg, astraConfig.selectorAnimationSpeed);

    //draw select box.
    //受摄像机的影响
    HAL::setDrawType(2);
    HAL::drawRBox(x + _camera[0], y + _camera[1], w, h - 1, astraConfig.selectorRadius);
    //HAL::drawRBox(x, y, w, astraConfig.listLineHeight, astraConfig.selectorRadius);
    HAL::setDrawType(1);
  }
}

std::vector<float> Selector::getPosition() {
  return {xTrg, yTrg};
}

}