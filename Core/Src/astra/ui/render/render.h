//
// Created by Fir on 2024/2/2.
//
#pragma once
#ifndef ASTRA_CORE_SRC_ASTRA_UI_RENDER_RENDER_H_
#define ASTRA_CORE_SRC_ASTRA_UI_RENDER_RENDER_H_
#include <cstdint>
#include <cmath>
#include "functional"

namespace astra::render {
class Render {
public:
  uint8_t pageInit{};
  uint8_t uiState{};
  uint8_t fadeFlag{};

  ///动画函数
  static void animation(float *_pos, const float *_posTrg);

  static void listCallBack();
  static void tileCallBack();
  static void listSideBarCallBack();
  static void listWindowCallBack();
  static void listCheckBoxCallBack();

  static void windowCallBack();
  static void checkBoxCallBack();
  static void sideBarCallBack();
};

extern std::function<void()> list;
extern std::function<void()> tile;
extern std::function<void()> listSideBar;
extern std::function<void()> listWindow;
extern std::function<void()> listCheckBox;

extern std::function<void()> window;
extern std::function<void()> checkBox;
extern std::function<void()> sideBar;

}
#endif //ASTRA_CORE_SRC_ASTRA_UI_RENDER_RENDER_H_