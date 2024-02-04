//
// Created by Fir on 2024/2/2.
//
#pragma once
#ifndef ASTRA_CORE_SRC_ASTRA_UI_SCHEDULER_H_
#define ASTRA_CORE_SRC_ASTRA_UI_SCHEDULER_H_
#include "page.h"
#include "../../hal/key/key.h"

namespace astra {
/**
 * @brief UI调度器 决定该显示哪个 显示来自哪里的
 * @brief page创建完毕后负责梳理出来指向架构
 * @brief **ui的index是树模式 从后面添加 从前面显示**
 * 主菜单是根结点
 */
class AstraLauncher : hardware::KeyScanner{
private:
  render::Render* render;
  Page* pageDisplay = nullptr;    //page displaying right now

  uint8_t pageInit{};
  uint8_t uiState{};
  uint8_t fadeFlag{};

public:
  explicit AstraLauncher(Page* _rootPage);

  void launch();

};
}
#endif //ASTRA_CORE_SRC_ASTRA_UI_SCHEDULER_H_