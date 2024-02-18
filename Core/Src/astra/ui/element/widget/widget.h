//
// Created by Fir on 2024/2/2.
//

#pragma once
#ifndef ASTRA_CORE_SRC_ASTRA_UI_WIDGET_H_
#include "../page/item.h"
#define ASTRA_CORE_SRC_ASTRA_UI_WIDGET_H_


namespace astra {
class Widget {
public:
  Page *parentPage;                 //指向父节点

  uint8_t selfType;

  uint8_t value;    //控件控制的数值 由构造函数拷贝 传入构造函数的是system类中的数
  std::string title;
  std::vector<std::string> text;

  Widget(const std::string& _title, Page *_parentPage, uint8_t _value);
  Widget(const std::string& _title, const std::vector<std::string>& _text, Page *_parentPage, uint8_t _value);
  Widget() = default;
};
}
#endif //ASTRA_CORE_SRC_ASTRA_UI_WIDGET_H_
