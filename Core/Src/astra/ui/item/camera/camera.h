//
// Created by Fir on 2024/4/14 014.
//

#pragma once
#ifndef ASTRA_CORE_SRC_ASTRA_UI_ELEMENT_CAMERA_CAMERA_H_
#define ASTRA_CORE_SRC_ASTRA_UI_ELEMENT_CAMERA_CAMERA_H_

#include "../selector/selector.h"

namespace astra {

//加入了摄像机 随着摄像机动而动
//其他的不动的元素 比如虚线和进度条 统称为前景 不受摄像机的控制
//这样一来元素本身的坐标并不会改变 只是在渲染的时候加入了摄像机的坐标而已

//磁贴类中 前景是虚线 标题 箭头和按钮图标 摄像机横向移动
//列表类中 前景是进度条 摄像机纵向移动
class Camera : public Item {
private:
  float xInit, yInit;

public:
  float x, y;
  float xTrg, yTrg;

  Camera(); //build an empty camera instance.
  Camera(float _x, float _y); //build a camera instance with position.

  unsigned char outOfView(float _x, float _y);
  unsigned char outOfView(std::vector<float> _pos) { return outOfView(_pos[0], _pos[1]); }
  [[nodiscard]] std::vector<float> getPosition();
  [[nodiscard]] std::vector<float> getPositionTrg();

  void init(const std::string &_type);

  //在启动器中新建selector和camera 然后注入menu render
  //在启动器中执行下述方法即可实现视角移动
  //启动器要判断是否超过视角范围 若超过则移动摄像机
  //所有过程中 渲染好的元素绝对坐标都是不变的 只有摄像机的坐标在变

  //go to a position.
  void go(float _x, float _y);
  void go(const std::vector<float> &_pos); //go to a position.
  void goDirect(float _x, float _y);

  //move to a position.
  void move(float _x, float _y);
  void moveDirect(float _x, float _y);

  void goToListItemRolling(List *_menu);
  void goToTileItem(unsigned char _index);

  void reset();
  void resetDirect();

  void update(Menu *_menu, Selector *_selector);
  void render();
};

}

#endif //ASTRA_CORE_SRC_ASTRA_UI_ELEMENT_CAMERA_CAMERA_H_
