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
  std::vector<float> cameraPosMemory = {};
  void rememberCameraPos(const std::vector<float> &_camera) {
    cameraPosMemory = _camera;
    cameraPosMemoryFlag = true;
  }
  [[nodiscard]] std::vector<float> getCameraMemoryPos() const { return cameraPosMemory; }
  void resetCameraMemoryPos() { cameraPosMemory = {0, 0}; }
  //编写一个变量 指示该页面到底有没有记忆
  bool cameraPosMemoryFlag = false;

public:
  //存储其在父页面中的位置
  //list中就是每一项对应的坐标 tile中就是每一个图片的坐标
  typedef struct Position {
    float x, xTrg;
    float y, yTrg;
  } Position;

  Position position{};

  [[nodiscard]] Position getItemPosition(unsigned char _index) const;
  virtual void childPosInit(const std::vector<float> &_camera) {}
  virtual void forePosInit() {}

public:
  std::string title;
  std::vector<unsigned char> pic;

protected:
  std::vector<unsigned char> picDefault = {};
  [[nodiscard]] std::vector<unsigned char> generateDefaultPic();

public:
  Menu *parent{};
  std::vector<Menu *> childMenu; //allow widget and menu.
  std::vector<Widget *> childWidget;
  unsigned char selectIndex{};

  [[nodiscard]] unsigned char getItemNum() const;
  [[nodiscard]] Menu *getNextMenu() const;  //启动器调用该方法来获取下一个页面
  [[nodiscard]] Menu *getPreview() const;

public:
  bool initFlag = false;

public:
  Menu() = default;
  ~Menu() = default;

public:
  void init(const std::vector<float>& _camera); //每次打开页面都要调用一次
  void deInit(); //每次关闭页面都要调用一次

public:
  virtual void render(const std::vector<float> &_camera) {}  //render all child item.

public:
  bool addItem(Menu *_page);
  bool addItem(Menu *_page, Widget* _anyWidget); //新建一个带有控件的列表项
};

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
  std::vector<unsigned char> boundary = {0, static_cast<unsigned char>(systemConfig.screenHeight / astraConfig.listLineHeight - 1)};
  [[nodiscard]] std::vector<unsigned char> getBoundary() const { return boundary; }
  void refreshBoundary(unsigned char _l, unsigned char _r) { boundary = {_l, _r}; }

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