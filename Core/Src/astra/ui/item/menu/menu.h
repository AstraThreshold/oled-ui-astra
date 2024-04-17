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
  std::vector<unsigned char> pic;

  typedef enum PageType {
    TILE = 0,
    LIST,
    CHECKBOX,
    POPUP,
    SLIDER,
  } PageType;

  PageType selfType;
  PageType childType; //在add第一个元素的时候确定 之后不可更改 只能加入相同类型的元素

public:
  Menu *parent;
  std::vector<void *> child; //allow widget and menu.
  unsigned char selectIndex;

  explicit Menu(std::string _title);

  Menu(std::string _title, std::vector<unsigned char> _pic);

  void init(std::vector<float> _camera); //每次打开页面都要调用一次
  void deInit(); //每次关闭页面都要调用一次

  void render(std::vector<float> _camera);  //render all child item.
  [[nodiscard]] unsigned char getItemNum() const;

  [[nodiscard]] Position getItemPosition(unsigned char _index) const;

  [[nodiscard]] void *getNext() const;  //启动器调用该方法来获取下一个页面
  [[nodiscard]] Menu *getNextMenu() const;  //启动器调用该方法来获取下一个页面
  [[nodiscard]] Menu *getPreview() const;

  //selector是启动器中修改的

  bool addItem(Menu *_page);

  //新建一个带有控件的列表项
  bool addItem(Menu *_page, CheckBox* _checkBox);
  bool addItem(Menu *_page, PopUp* _popUp);
  bool addItem(Menu *_page, Slider* _slider);
};

}

#endif //ASTRA_ASTRA__H