//
// Created by Fir on 2024/1/21.
//

#pragma once
#ifndef ASTRA_ASTRA__H
#define ASTRA_ASTRA__H

#include "cstdint"
#include "string"
#include <vector>
#include "../item.h"
#include "../widget/widget.h"

namespace astra {

class Menu : public Item {
public:
  [[nodiscard]] virtual std::string getType() const { return "Base"; }

public:
  //存储其在父页面中的位置
  //list中就是每一项对应的坐标 tile中就是每一个图片的坐标
  typedef struct Position {
    float x, xTrg;
    float y, yTrg;
  } Position;

  Position position{};

public:
  virtual void childPosInit(const std::vector<float> &_camera) {}
  virtual void forePosInit() {}

public:
  std::string title;
  std::vector<unsigned char> pic;

public:
  Menu *parent;
  std::vector<Menu *> childMenu; //allow widget and menu.
  std::vector<Widget *> childWidget;
  unsigned char selectIndex;

  Menu() = default;

  void init(std::vector<float> _camera); //每次打开页面都要调用一次
  void deInit(); //每次关闭页面都要调用一次

  //todo 后续再整理一下这些函数声明的位置 分分组

  virtual void render(const std::vector<float> &_camera) {}  //render all child item.
  [[nodiscard]] unsigned char getItemNum() const;

  [[nodiscard]] Position getItemPosition(unsigned char _index) const;

  [[nodiscard]] Menu *getNextMenu() const;  //启动器调用该方法来获取下一个页面
  [[nodiscard]] Menu *getPreview() const;

  bool addItem(Menu *_page);

  //新建一个带有控件的列表项
  bool addItem(Menu *_page, Widget* _anyWidget);
};

//todo 正确的原理
//rootPage = new List();
//tilePage = new Tile("test2");
//tilePage1 = new Tile("test4", pic);
//tilePage->addItem(new List("fuck", pic));

//rootPage->addItem(new List("test1"));
//rootPage->addItem(tilePage);
//rootPage->addItem(new List("test3"));
//rootPage->addItem(tilePage1);
//todo 以上123都是list的形式 但是打开test2之后是磁贴页
//这样的话就不需要判断childType了 也不需要在add的时候改变childType了
//它本身是什么类型的页面 就会强制将所有子页面显示为它本身的类型
//这就要求所有子页面都需要具有pic和title 哪怕是空的也行
//基类和各个派生类的render函数依然是负责渲染所有子页面 渲染的类型取决于自身
//如 List类 仅会将所有子元素渲染为list项 不管子元素打开之后是啥页面
//同样的一堆元素 add到Tile类实例上 它会将他们都渲染为磁贴项 如果没有图片就用默认图片代替

class List : public Menu {
public:
  [[nodiscard]] std::string getType() const override { return "List"; }

public:
  //前景元素的坐标
  typedef struct PositionForeground {
    float hBar, hBarTrg;  //进度条高度
    float xBar, xBarTrg;  //进度条x坐标
  } PositionForeground;

  PositionForeground positionForeground{};

public:
  void childPosInit(const std::vector<float> &_camera) override;
  void forePosInit() override;

  List();
  explicit List(const std::string &_title);
  explicit List(const std::vector<unsigned char>& _pic);
  List(const std::string &_title, const std::vector<unsigned char>& _pic);

public:
  void render(const std::vector<float> &_camera) override;
};

class Tile : public Menu {
public:
  [[nodiscard]] std::string getType() const override { return "Tile"; }

public:
  //前景元素的坐标
  typedef struct PositionForeground {
    float wBar, wBarTrg;  //进度条宽度
    float yBar, yBarTrg;  //进度条y坐标
    float yArrow, yArrowTrg;
    float yDottedLine, yDottedLineTrg;
  } PositionForeground;

  PositionForeground positionForeground{};

public:
  void childPosInit(const std::vector<float> &_camera) override;
  void forePosInit() override;

  Tile();
  explicit Tile(const std::string &_title);
  explicit Tile(const std::vector<unsigned char> &_pic);
  Tile(const std::string &_title, const std::vector<unsigned char> &_pic);

public:
  void render(const std::vector<float> &_camera) override;
};

}

#endif //ASTRA_ASTRA__H