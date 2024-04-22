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

////todo 小组件下个版本更新

#include "menu.h"

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

Menu::Menu(std::string _title) {
  this->title = std::move(_title);
  this->selfType = LIST;
  this->childType = {};
  this->position.x = astraConfig.listTextMargin;
  this->position.y = 0;
  this->position.xTrg = astraConfig.listTextMargin;
  this->position.yTrg = 0;  //这里暂时无法计算trg 需要在addItem的时候计算 因为那时候才能拿到所有元素的数量
  this->selectIndex = 0;
  this->parent = nullptr;
  this->childMenu.clear();
  this->pic.clear();
}

Menu::Menu(std::string _title, std::vector<unsigned char> _pic) {
  this->title = std::move(_title);
  this->pic = std::move(_pic);
  this->selfType = TILE;
  this->childType = {};
  this->position.x = 0;
  this->position.y = 0;
  this->position.xTrg = 0;  //这里暂时无法计算trg 需要在addItem的时候计算 因为那时候才能拿到所有元素的数量
  this->position.yTrg = astraConfig.tilePicTopMargin;
  this->selectIndex = 0;
  this->parent = nullptr;
  this->childMenu.clear();
}

void Menu::init(std::vector<float> _camera) {
  Animation::entry();

  if (childType == TILE) {
    //受展开开关影响的坐标初始化
    if (astraConfig.tileUnfold) {
      for (auto _iter : childMenu)
        _iter->position.x = _camera[0] - astraConfig.tilePicWidth; //unfold from left.
      positionForeground.wBar = 0;  //bar unfold from left.

    } else {
      for (auto _iter : childMenu) _iter->position.x = _iter->position.xTrg;
      positionForeground.wBar = positionForeground.wBarTrg;
    }

    //position.y = -astraConfig.tilePicHeight * 2;

    //始终执行的坐标初始化
    //底部箭头和虚线的初始化
    positionForeground.yArrow = systemConfig.screenHeight;
    positionForeground.yDottedLine = systemConfig.screenHeight;

    //顶部进度条的从上方滑入的初始化
    positionForeground.yBar = 0 - astraConfig.tileBarHeight; //注意这里是坐标从屏幕外滑入 而不是height从0变大

  } else if (childType == LIST) {
    //受展开开关影响的坐标初始化
    if (astraConfig.listUnfold) {
      for (auto _iter : childMenu)
        _iter->position.y = _camera[1] - astraConfig.listLineHeight; //text unfold from top.
      positionForeground.hBar = 0;  //bar unfold from top.
    } else {
      for (auto _iter : childMenu) _iter->position.y = _iter->position.yTrg;
      positionForeground.hBar = positionForeground.hBarTrg;
    }

    //始终执行的坐标初始化
    positionForeground.xBar = systemConfig.screenWeight;
  }
}

void Menu::deInit() {
  //todo 未实现完全
  Animation::exit();
}

void Menu::render(std::vector<float> _camera) {
  if (childType == TILE) {
    Item::updateConfig();

    HAL::setDrawType(1);

    //draw pic.
    for (auto _iter : childMenu) {
      HAL::drawBMP(_iter->position.x + _camera[0],
                   astraConfig.tilePicTopMargin + _camera[1],
                   astraConfig.tilePicWidth,
                   astraConfig.tilePicHeight,
                   _iter->pic.data());
      //这里的xTrg在addItem的时候就已经确定了
      Animation::move(&_iter->position.x,
           _iter->position.xTrg,
           astraConfig.tileAnimationSpeed);
    }

    //draw bar.
    //在屏幕最上方 两个像素高
    positionForeground.wBarTrg = (selectIndex + 1) * ((float) systemConfig.screenWeight / getItemNum());
    HAL::drawBox(0, positionForeground.yBar, positionForeground.wBar, astraConfig.tileBarHeight);

    //draw left arrow.
    HAL::drawHLine(astraConfig.tileArrowMargin, positionForeground.yArrow, astraConfig.tileArrowWidth);
    HAL::drawPixel(astraConfig.tileArrowMargin + 1, positionForeground.yArrow + 1);
    HAL::drawPixel(astraConfig.tileArrowMargin + 2, positionForeground.yArrow + 2);
    HAL::drawPixel(astraConfig.tileArrowMargin + 1, positionForeground.yArrow - 1);
    HAL::drawPixel(astraConfig.tileArrowMargin + 2, positionForeground.yArrow - 2);

    //draw right arrow.
    HAL::drawHLine(systemConfig.screenWeight - astraConfig.tileArrowWidth - astraConfig.tileArrowMargin,
                   positionForeground.yArrow,
                   astraConfig.tileArrowWidth);
    HAL::drawPixel(systemConfig.screenWeight - astraConfig.tileArrowWidth, positionForeground.yArrow + 1);
    HAL::drawPixel(systemConfig.screenWeight - astraConfig.tileArrowWidth - 1, positionForeground.yArrow + 2);
    HAL::drawPixel(systemConfig.screenWeight - astraConfig.tileArrowWidth, positionForeground.yArrow - 1);
    HAL::drawPixel(systemConfig.screenWeight - astraConfig.tileArrowWidth - 1, positionForeground.yArrow - 2);

    //draw left button.
    HAL::drawHLine(astraConfig.tileBtnMargin, positionForeground.yArrow + 2, 9);
    HAL::drawBox(astraConfig.tileBtnMargin + 2, positionForeground.yArrow + 2 - 4, 5, 4);

    //draw right button.
    HAL::drawHLine(systemConfig.screenWeight - astraConfig.tileBtnMargin - 9, positionForeground.yArrow + 2, 9);
    HAL::drawBox(systemConfig.screenWeight - astraConfig.tileBtnMargin - 9 + 2,
                 positionForeground.yArrow + 2 - 4,
                 5,
                 4);

    //draw dotted line.
    HAL::drawHDottedLine(0, positionForeground.yDottedLine, systemConfig.screenWeight);

    Animation::move(&positionForeground.yDottedLine, positionForeground.yDottedLineTrg, astraConfig.tileAnimationSpeed);
    Animation::move(&positionForeground.yArrow, positionForeground.yArrowTrg, astraConfig.tileAnimationSpeed);

    Animation::move(&positionForeground.wBar, positionForeground.wBarTrg, astraConfig.tileAnimationSpeed);
    Animation::move(&positionForeground.yBar, positionForeground.yBarTrg, astraConfig.tileAnimationSpeed);
  } else if (childType == LIST) {
    Item::updateConfig();

    HAL::setDrawType(1);

    //allow x > screen height, y > screen weight.
    //scan all child, draw text and widget on list.
    for (auto _iter : childMenu) {
      //绘制控件在列表中的指示器
      if (_iter->childType == WIDGET) {
        for (auto _widget : _iter->childWidget) {
          _widget->renderIndicator(systemConfig.screenWeight - astraConfig.checkBoxRightMargin - astraConfig.checkBoxWidth,
                                   _iter->position.y + astraConfig.checkBoxTopMargin,
                                   _camera);
        }
      }
      //绘制文字
      HAL::drawChinese(_iter->position.x + _camera[0],
                       _iter->position.y + astraConfig.listTextHeight +
                       astraConfig.listTextMargin + _camera[1],
                       _iter->title);
      //这里的yTrg在addItem的时候就已经确定了
      Animation::move(&_iter->position.y,
           _iter->position.yTrg,
           astraConfig.listAnimationSpeed);
    }

    //draw bar.
    positionForeground.hBarTrg = (selectIndex + 1) * ((float) systemConfig.screenHeight / getItemNum());
    //画指示线
    HAL::drawHLine(systemConfig.screenWeight - astraConfig.listBarWeight, 0, astraConfig.listBarWeight);
    HAL::drawHLine(systemConfig.screenWeight - astraConfig.listBarWeight,
                   systemConfig.screenHeight - 1,
                   astraConfig.listBarWeight);
    HAL::drawVLine(systemConfig.screenWeight - ceil((float) astraConfig.listBarWeight / 2.0f),
                   0,
                   systemConfig.screenHeight);
    //draw bar.
    HAL::drawBox(positionForeground.xBar, 0, astraConfig.listBarWeight, positionForeground.hBar);

    //light mode.
    if (astraConfig.lightMode) {
      HAL::setDrawType(2);
      HAL::drawBox(0, 0, systemConfig.screenWeight, systemConfig.screenHeight);
      HAL::setDrawType(1);
    }

    Animation::move(&positionForeground.hBar, positionForeground.hBarTrg, astraConfig.listAnimationSpeed);
    Animation::move(&positionForeground.xBar, positionForeground.xBarTrg, astraConfig.listAnimationSpeed);
  }
}

unsigned char Menu::getItemNum() const {
  return childMenu.size();
}

Menu::Position Menu::getItemPosition(unsigned char _index) const {
  childMenu[_index]->position;
}

Menu *Menu::getNextMenu() const {
  return childMenu[selectIndex];
}

Menu *Menu::getPreview() const {
  return parent;
}

bool Menu::addItem(Menu *_page) {
  if (this->childType == WIDGET) return false;
  if (_page == nullptr) return false;
  else {
    //加入的第一个元素的类型决定了当前节点所有子元素的类型
    if (this->childMenu.empty()) this->childType = _page->selfType;

    if (this->childType == _page->selfType) {
      _page->parent = this;
      this->childMenu.push_back(_page);
      if (this->childType == LIST) {
        _page->position.xTrg = astraConfig.listTextMargin;
        _page->position.yTrg = (getItemNum() - 1) * astraConfig.listLineHeight;

        positionForeground.xBarTrg = systemConfig.screenWeight - astraConfig.listBarWeight;
      }
      if (this->childType == TILE) {
        _page->position.xTrg = systemConfig.screenWeight / 2 - astraConfig.tilePicWidth / 2 +
                               (this->getItemNum() - 1) * (astraConfig.tilePicMargin + astraConfig.tilePicWidth);
        _page->position.yTrg = astraConfig.tilePicTopMargin;

        positionForeground.yBarTrg = 0;
        positionForeground.yArrowTrg = systemConfig.screenHeight - astraConfig.tileArrowBottomMargin;
        positionForeground.yDottedLineTrg = systemConfig.screenHeight - astraConfig.tileDottedLineBottomMargin;
      }
      return true;
    } else return false;
  }
}

bool Menu::addItem(Menu *_page, Widget *_anyWidget) {
  if (_anyWidget == nullptr) return false;
  if (this->addItem(_page)) {
    _page->childType = WIDGET;
    _page->childWidget.push_back(_anyWidget);
    _anyWidget->parent = _page;
    _anyWidget->init();
    return true;
  } else return false;
}
}
