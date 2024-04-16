#pragma once
#ifndef ASTRA_WIDGET__H
#define ASTRA_WIDGET__H

#include "../item.h"

namespace astra {

class Widget : public Item {
public:
  void* parent;

public:
  typedef enum WidgetType {
    CHECKBOX = 0,
    POPUP,
    SLIDER,
  } WidgetType;

  WidgetType type;
};

class CheckBox : public Widget {
private:
  unsigned char &value;

public:
  explicit CheckBox(unsigned char &_value);  //check box.
  void init(); //初始化控件

public:
  bool check();
  bool uncheck();
  bool toggle();

public:
  void render(); //控件都是前景 所以无需摄像机
};

class PopUp : public Widget {
public:
  typedef struct Position {
    float x, xTrg;
    float y, yTrg;
  } Position;

  Position position{};

private:
  unsigned char &value;
  std::string title;
  std::vector<std::string> options;
  unsigned char direction;

public:
  // 0: left 1: top 2: right 3: bottom
  PopUp(unsigned char _direction,
         std::string _title,
         std::vector<std::string> _options,
         unsigned char &_value);  //pop up.
  void init(); //初始化控件

public:
  bool open();
  bool close();
  bool selectNext();
  bool selectPreview();
  bool select(unsigned char _index);

public:
  void render(); //控件都是前景 所以无需摄像机
};

class Slider : public Widget {
public:
  typedef struct Position {
    float x, xTrg;
    float y, yTrg;

    float l, lTrg; //slider
  } Position;

  Position position{};

private:
  unsigned char &value;
  unsigned char min;
  unsigned char max;
  unsigned char step;

public:
  Slider(std::string _title,
         unsigned char _min,
         unsigned char _max,
         unsigned char _step,
         unsigned char &_value);  //slider.
  void init(); //初始化控件

public:
  bool open();
  bool close();
  unsigned char add();
  unsigned char sub();

public:
  void render(); //控件都是前景 所以无需摄像机
};

}

#endif //ASTRA_WIDGET__H