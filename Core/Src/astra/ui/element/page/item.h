//
// Created by Fir on 2024/1/21.
//

#pragma once
#ifndef ASTRA_ASTRA__H
#define ASTRA_ASTRA__H

#include "cstdint"
#include "string"
#include <vector>
#include "../../../../hal/hal.h"
#include "../../../../astra/config/config.h"
#include <cmath>

namespace astra {

class Item {
protected:
  sys::config systemConfig;
  config astraConfig;

  void updateConfig();
};

class Animation {
public:
  virtual void entryAnimation();
  virtual void exitAnimation();
  virtual void blur();
  virtual void animation(float *_pos, float _posTrg, float _speed);
};

inline void Animation::entryAnimation() { }

//todo 未实现功能
inline void Animation::exitAnimation() {
  static uint8_t fadeFlag = 1;
  static uint8_t bufferLen = 8 * HAL::getBufferTileHeight() * HAL::getBufferTileWidth();
  auto *bufferPointer = (uint8_t *) HAL::getCanvasBuffer();

  HAL::delay(getUIConfig().fadeAnimationSpeed);

  if (getUIConfig().lightMode)
    switch (fadeFlag) {
      case 1:
        for (uint16_t i = 0; i < bufferLen; ++i) if (i % 2 != 0) bufferPointer[i] = bufferPointer[i] & 0xAA;
        break;
      case 2:
        for (uint16_t i = 0; i < bufferLen; ++i) if (i % 2 != 0) bufferPointer[i] = bufferPointer[i] & 0x00;
        break;
      case 3:
        for (uint16_t i = 0; i < bufferLen; ++i) if (i % 2 == 0) bufferPointer[i] = bufferPointer[i] & 0x55;
        break;
      case 4:
        for (uint16_t i = 0; i < bufferLen; ++i) if (i % 2 == 0) bufferPointer[i] = bufferPointer[i] & 0x00;
        break;
      default:
        //放动画结束退出函数的代码
        fadeFlag = 0;
        break;
    }
  else
    switch (fadeFlag) {
      case 1:
        for (uint16_t i = 0; i < bufferLen; ++i) if (i % 2 != 0) bufferPointer[i] = bufferPointer[i] | 0xAA;
        break;
      case 2:
        for (uint16_t i = 0; i < bufferLen; ++i) if (i % 2 != 0) bufferPointer[i] = bufferPointer[i] | 0x00;
        break;
      case 3:
        for (uint16_t i = 0; i < bufferLen; ++i) if (i % 2 == 0) bufferPointer[i] = bufferPointer[i] | 0x55;
        break;
      case 4:
        for (uint16_t i = 0; i < bufferLen; ++i) if (i % 2 == 0) bufferPointer[i] = bufferPointer[i] | 0x00;
        break;
      default:
        fadeFlag = 0;
        break;
    }
  fadeFlag++;
}

inline void Animation::blur() {
  static uint8_t bufferLen = 8 * HAL::getBufferTileHeight() * HAL::getBufferTileWidth();
  static auto *bufferPointer = (uint8_t *) HAL::getCanvasBuffer();

  for (uint16_t i = 0; i < bufferLen; ++i) bufferPointer[i] = bufferPointer[i] & (i % 2 == 0 ? 0x55 : 0xAA);
}

inline void Animation::animation(float *_pos, float _posTrg, float _speed) {
  if (*_pos != _posTrg) {
    if (std::fabs(*_pos - _posTrg) < 0.15f) *_pos = _posTrg;
    else *_pos += (_posTrg - *_pos) / ((100 - _speed) / 1.0f);
  }
}

//todo 实现之前提到过的那个进场和退场动画的idea
class Menu : public Item, public Animation {
public:
  //存储其在父页面中的位置
  //list中就是每一项对应的坐标 tile中就是每一个图片的坐标
  typedef struct Position {
    //这里的坐标都是左上角的坐标 但是要记住绘制文字的时候是左下角的坐标 需要再减去字体的高度
    float x, xTrg;
    float y, yTrg;
  } Position;

  Position position{};

  //前景元素的坐标
  typedef struct PositionForeground {
    float hBar, hBarTrg;  //进度条高度 通用
    float wBar, wBarTrg;  //进度条宽度 通用
    float xBar, xBarTrg;  //进度条x坐标 通用
    float yBar, yBarTrg;  //进度条y坐标 通用

    /*TILE*/
    float yArrow, yArrowTrg;
    float yDottedLine, yDottedLineTrg;
    /*TILE*/
  } PositionForeground;

  PositionForeground positionForeground{};

  std::string title;
  std::vector<uint8_t> pic;

  typedef enum PageType {
    TILE = 0,
    LIST,
  } PageType;

  PageType selfType;
  PageType childType; //在add第一个元素的时候确定 之后不可更改 只能加入相同类型的元素

public:
  Menu *parent;
  std::vector<Menu *> child;
  uint8_t selectIndex;

  explicit Menu(std::string _title);
  Menu(std::string _title, std::vector<uint8_t> _pic);

  void init(std::vector<float> _camera); //每次打开页面都要调用一次
  void deInit(); //每次关闭页面都要调用一次

  void render(std::vector<float> _camera);  //render all child item.
  [[nodiscard]] uint8_t getItemNum() const;
  [[nodiscard]] Position getItemPosition(uint8_t _index) const;
  [[nodiscard]] Menu* getNext() const;  //启动器调用该方法来获取下一个页面
  [[nodiscard]] Menu* getPreview() const;

  //selector是启动器中修改的

  bool addItem(Menu* _page);
};

class Selector : public Item, public Animation {
private:
  Menu* menu;

public:
  //列表页中就是选择框的坐标 磁贴页中就是大框的坐标
  float x, xTrg;
  float y, yTrg;

  /*LIST*/
  float w, wTrg;
  float h, hTrg;
  /*LIST*/

  /*TILE*/
  float yText, yTextTrg;  //磁贴页标题坐标
  /*TILE*/

  Selector() = default;
  //最牛逼的来了 在磁贴中 文字和大框就是selector
  //这样就可以弄磁贴的文字出现动画了
  ////todo 在磁贴中 选择的时候 摄像机和selector都要移动 磁贴的selector是一个空心方框 + 底部的字体

  std::vector<float> getPosition();

  void go(uint8_t _index);

  bool inject(Menu* _menu); //inject menu instance to prepare for render.
  bool destroy(); //destroy menu instance.

  void render(std::vector<float> _camera);
};

//加入了摄像机 随着摄像机动而动
//其他的不动的元素 比如虚线和进度条 统称为前景 不受摄像机的控制
//这样一来元素本身的坐标并不会改变 只是在渲染的时候加入了摄像机的坐标而已

//磁贴类中 前景是虚线 标题 箭头和按钮图标 摄像机横向移动
//列表类中 前景是进度条 摄像机纵向移动
class Camera : public Item, public Animation {
private:
  float xInit, yInit;

public:
  float x, y;

  bool moving = false;

  Camera(); //build an empty camera instance.
  Camera(float _x, float _y); //build a camera instance with position.

  uint8_t outOfView(float _x, float _y);
  std::vector<float> getPosition();

  //在启动器中新建selector和camera 然后注入menu render
  //在启动器中执行下述方法即可实现视角移动
  //启动器要判断是否超过视角范围 若超过则移动摄像机
  //所有过程中 渲染好的元素绝对坐标都是不变的 只有摄像机的坐标在变
  void go(float _x, float _y);
  void goDirect(float _x, float _y);
  void goHorizontal(float _x);
  void goVertical(float _y);

  void goToNextPageItem();
  void goToPreviewPageItem();
  void goToListItemPage(uint8_t _index);
  void goToListItemRolling(std::vector<float> _posSelector);
  void goToTileItem(uint8_t _index);

  bool isMoving();

  void reset();

  void update(Menu *_menu, Selector *_selector);
};

}

#endif //ASTRA_ASTRA__H