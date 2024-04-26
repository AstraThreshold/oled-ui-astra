//
// Created by Fir on 2024/4/14 014.
//

#pragma once
#ifndef ASTRA_CORE_SRC_ASTRA_UI_ELEMENT_SELECTOR_SELECTOR_H_
#define ASTRA_CORE_SRC_ASTRA_UI_ELEMENT_SELECTOR_SELECTOR_H_
#include "../menu/menu.h"

namespace astra {
class Selector : public Item {
private:
  Menu *menu;

public:
  //列表页中就是选择框的坐标 磁贴页中就是大框的坐标
  float x, xTrg;
  float y, yTrg;

  /*LIST*/
  float w, wTrg;
  float h, hTrg;
  /*LIST*/

  /*TILE*/
  float yText, yTextTrg;  //磁贴页标题坐标
  /*TILE*/

  Selector() = default;
  //最牛逼的来了 在磁贴中 文字和大框就是selector
  //这样就可以弄磁贴的文字出现动画了

  std::vector<float> getPosition();
  void setPosition();

  void go(unsigned char _index);
  void goNext();
  void goPreview();

  bool inject(Menu *_menu); //inject menu instance to prepare for render.
  bool destroy(); //destroy menu instance.

  void render(std::vector<float> _camera);
};
}
#endif //ASTRA_CORE_SRC_ASTRA_UI_ELEMENT_SELECTOR_SELECTOR_H_
