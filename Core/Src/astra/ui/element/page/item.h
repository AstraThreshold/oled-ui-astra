//
// Created by Fir on 2024/1/21.
//

#pragma once
#ifndef ASTRA_ASTRA__H
#define ASTRA_ASTRA__H

#include "cstdint"
#include "string"
#include <vector>
#include "functional"
#include "../element_i.h"
#include "../../../../hal/hal.h"
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
  virtual inline void animation(float *_pos, float _posTrg, float _speed);
};

//加入了摄像机 随着摄像机动而动
//其他的不动的元素 比如虚线和进度条 统称为前景 不受摄像机的控制
//这样一来元素本身的坐标并不会改变 只是在渲染的时候加入了摄像机的坐标而已

//磁贴类中 前景是虚线 标题 箭头和按钮图标 摄像机横向移动
//列表类中 前景是进度条 摄像机纵向移动
class Camera : public Item, public Animation {
public:
  float x, xTrg;
  float y, yTrg;

  Camera();

  //在启动器中新建selector和camera 然后注入menu render
  //在启动器中执行下述方法即可实现视角移动
  //启动器要判断是否超过视角范围 若超过则移动摄像机
  //所有过程中 渲染好的元素绝对坐标都是不变的 只有摄像机的坐标在变
  void go(uint8_t _x, uint8_t _y);
  void goDirect(uint8_t _x, uint8_t _y);
  void reset();
};

class Selector : public Item, public Animation {
public:
  float x, xTrg;
  float y, yTrg;
  float w, wTrg;

  Selector();

  inline void render();

  //在启动器中新建selector和camera 然后注入menu render
  //在启动器中执行下述方法即可实现选择
  //todo 当前选择的指针由启动器更改 然后get到对应的坐标给到selector
  void go(uint8_t _x, uint8_t _y);

};

class Menu : public Item, public Animation {
protected:
  //存储其在父页面中的位置
  //list中就是每一项对应的坐标 tile中就是每一个图片的坐标
  typedef struct Position {
    float x, xTrg;
    float y, yTrg;
  } Position;

  Position position{};

  std::string title;
  std::vector<std::vector<uint8_t>> pic;

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
  bool init;

  explicit Menu(std::string _title);
  Menu(std::string _title, std::vector<std::vector<uint8_t>> _pic);

  inline void render(Camera* _camera, Selector* _selector);  //render all child item.
  [[nodiscard]] uint8_t getItemNum() const;
  [[nodiscard]] Position getItemPosition(uint8_t _index) const;
  [[nodiscard]] Menu* getNext() const;  //启动器调用该方法来获取下一个页面
  [[nodiscard]] Menu* getPreview() const;

  bool addItem(Menu* _page);
};
}
#endif //ASTRA_ASTRA__H