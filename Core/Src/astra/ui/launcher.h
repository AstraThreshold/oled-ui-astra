//
// Created by Fir on 2024/2/2.
//
#pragma once
#ifndef ASTRA_CORE_SRC_ASTRA_UI_SCHEDULER_H_
#define ASTRA_CORE_SRC_ASTRA_UI_SCHEDULER_H_

#include "element/page/item.h"

namespace astra {
/**
 * @brief UI调度器 决定该显示哪个 显示来自哪里的
 * @brief page创建完毕后负责梳理出来指向架构
 * @brief **ui的index是树模式 从后面添加 从前面显示**
 * 主菜单是根结点
 */

class Launcher {
private:
  void *node = nullptr;    //page displaying right now

  uint8_t pageInit{};
  uint8_t uiState{};
  uint8_t fadeFlag{};

public:
  Selector* selector;
  explicit Launcher(Page *_rootPage);

  void start();

  bool addItem(const std::string &_title, Page *_page); //list
  bool addItem(const std::string &_title, const std::vector<uint8_t> &_pic, Page *_page); //tile
  bool addItem(); //widget
};
}
#endif //ASTRA_CORE_SRC_ASTRA_UI_SCHEDULER_H_