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

class Menu : public Item, public Animation {
public:
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

  inline void render(Camera* _camera);  //render all child item.
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
  float x, xTrg;
  float y, yTrg;
  float w, wTrg;

  Selector();
  ////todo!!!!!!! 最牛逼的来了 在磁贴中 文字和大框就是selector
  ////todo 这样就可以弄磁贴的文字出现动画了
  ////todo 在磁贴中 选择的时候 摄像机和selector都要移动 磁贴的selector是一个空心方框 + 底部的字体

  bool inject(Menu* _menu); //inject menu instance to prepare for render.
  bool destroy(); //destroy menu instance.

  inline void render(Camera* _camera);

  //在启动器中新建selector和camera 然后注入menu render
  //在启动器中执行下述方法即可实现选择
  //todo 当前选择的指针由启动器更改 然后get到对应的坐标给到selector

  ////todo 但是不知道磁贴页的selector是怎么显示的
  ////todo 想想怎么以更优雅的方式获取到磁贴页的标题
  ////todo 想想怎么以更优雅的方式获取到各种坐标 看看能不能传个结构体进去

  ////todo 考虑在Menu后面声明这一坨 然后在启动器里单独渲染selector
  ////todo 而且selector的坐标也是相对于摄像机的坐标的
  void go(uint8_t _x, uint8_t _y);
};
}
#endif //ASTRA_ASTRA__H