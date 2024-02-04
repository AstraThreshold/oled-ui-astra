//
// Created by Fir on 2024/2/2.
//

#pragma once
#ifndef ASTRA_CORE_SRC_ASTRA_UI_WIDGET_H_
#include "page.h"
#define ASTRA_CORE_SRC_ASTRA_UI_WIDGET_H_


namespace astra {
class Widget {
public:
  Page *parentPage;                 //指向父节点

  typedef std::function<void()> widgetType;
  widgetType selfType;

  uint8_t value;    //控件控制的数值 由构造函数拷贝 传入构造函数的是system类中的数
  std::string title;
  std::vector<std::string> text;

  Widget(const std::string& _title, Page *_parentPage, uint8_t _value, widgetType _type);
  Widget(const std::string& _title, const std::vector<std::string>& _text, Page *_parentPage, uint8_t _value);

  //判断两个std::function是否相等
  template <typename R, typename... Args>
  bool isSame(std::function<R(Args...)> const& _f1, std::function<R(Args...)> const& _f2)
  {
    // 检查两个std::function是否都有目标
    if(!_f1 || !_f2)
      return false;

    // 检查两个std::function的目标类型是否相同
    if(_f1.target_type() != _f2.target_type())
      return false;

    // 获取并比较两个std::function的目标
    typedef R(funcType)(Args...);
    funcType* _p1 = _f1.template target<funcType>();
    funcType* _p2 = _f2.template target<funcType>();
    if (_p1 == nullptr || _p2 == nullptr)
      return false; // 一个或者两个std::function没有目标
    return _p1 == _p2;
  }
};
}
#endif //ASTRA_CORE_SRC_ASTRA_UI_WIDGET_H_
