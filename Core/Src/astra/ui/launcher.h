//
// Created by Fir on 2024/2/2.
//
#pragma once
#ifndef ASTRA_CORE_SRC_ASTRA_UI_SCHEDULER_H_
#define ASTRA_CORE_SRC_ASTRA_UI_SCHEDULER_H_

#include "element/page/page.h"
#include "element/widget/widget.h"
#include "../../hal/key/key.h"
#include <cmath>

namespace astra {

typedef std::function<void(void *)> itemType;

/**
 * @brief UI调度器 决定该显示哪个 显示来自哪里的
 * @brief page创建完毕后负责梳理出来指向架构
 * @brief **ui的index是树模式 从后面添加 从前面显示**
 * 主菜单是根结点
 */
class Launcher : Page, Widget, hardware::KeyScanner {
private:
  void *node = nullptr;    //page displaying right now

  uint8_t pageInit{};
  uint8_t uiState{};
  uint8_t fadeFlag{};

//  //判断两个std::function是否相等
//  template<typename R, typename... Args>
//  static bool isSame(std::function<R(Args...)> const &_f1, std::function<R(Args...)> const &_f2) {
//    // 检查两个std::function是否都有目标
//    if (!_f1 || !_f2)
//      return false;
//
//    // 检查两个std::function的目标类型是否相同
//    if (_f1.target_type() != _f2.target_type())
//      return false;
//
//    // 获取并比较两个std::function的目标
//    typedef R(funcType)(Args...);
//    funcType *_p1 = _f1.template target<funcType>();
//    funcType *_p2 = _f2.template target<funcType>();
//    if (_p1 == nullptr || _p2 == nullptr)
//      return false; // 一个或者两个std::function没有目标
//    return _p1 == _p2;
//  }

public:

  explicit Launcher(Page *_rootPage);

  void launcherStart();

  bool addItem(const std::string &_title, Page *_page); //list
  bool addItem(const std::string &_title, const std::vector<uint8_t> &_pic, Page *_page); //tile
  bool addItem(); //widget
};
}
#endif //ASTRA_CORE_SRC_ASTRA_UI_SCHEDULER_H_