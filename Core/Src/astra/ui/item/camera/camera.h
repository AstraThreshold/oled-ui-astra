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
class Camera : public Item, public Animation {
private:
  float xInit, yInit;

public:
  float x, y;

  bool moving = false;

  Camera(); //build an empty camera instance.
  Camera(float _x, float _y); //build a camera instance with position.

  unsigned char outOfView(float _x, float _y);
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
  void goToListItemPage(unsigned char _index);
  void goToListItemRolling(std::vector<float> _posSelector);
  void goToTileItem(unsigned char _index);

  bool isMoving();

  void reset();

  void update(Menu *_menu, Selector *_selector);
};

}

#endif //ASTRA_CORE_SRC_ASTRA_UI_ELEMENT_CAMERA_CAMERA_H_
