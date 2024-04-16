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

public:
  void init(); //初始化控件
  void render(); //控件都是前景 所以无需摄像机

public:
  Widget() = default;

  explicit Widget(unsigned char _value);  //check box.
  // 0: left 1: top 2: right 3: bottom
  Widget(unsigned char _direction,
         std::string _title,
         std::vector<std::string> _options,
         unsigned char _value);  //pop up.
  Widget(std::string _title,
         unsigned char _min,
         unsigned char _max,
         unsigned char _step,
         unsigned char _value);  //slider.
};

}

#endif //ASTRA_WIDGET__H