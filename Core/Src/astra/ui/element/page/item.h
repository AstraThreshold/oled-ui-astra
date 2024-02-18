//
// Created by Fir on 2024/1/21.
//

#pragma once
#ifndef ASTRA_ASTRA__H
#define ASTRA_ASTRA__H

#include "cstdint"
#include "string"
#include <vector>
#include "functional"
#include "../element_i.h"
#include "../../../../hal/hal.h"
#include <cmath>

namespace astra {

class Item {
protected:
  sys::config systemConfig;
  config astraConfig;
  void updateConfig();

public:
  void *parent;
  std::vector<void *> child;
  uint8_t select;
};

class ListMenu : public Item {
protected:
  //存储其在父页面中的位置
  float y, yTrg;
  float yBar, yBarTrg;
  float yTemp;

private:

  inline void animation(float *_pos, float _posTrg, float _speed);

public:
  inline void render();  //render current menu.
  uint8_t getItemNum();
  uint8_t getItemPosition(uint8_t _index);

  bool addItem();

  std::string title;
};

class TileMenu : Item {
protected:
  float yText, yTextTrg;
  float yDottedLine;
  float yArrow;

private:
  std::vector<std::vector<uint8_t>> pic;
  std::string title;

  inline void animation(float *_pos, float _posTrg, float _speed);

public:
  inline void render();
  uint8_t getItemNum();

  bool addItem();
};

class Selector {
protected:
  float w, wTrg;
  float y, yTrg;

  ListMenu* currentPage;

  config astraConfig;
  void updateConfig();  //todo 记得在启动器循环里重复执行item和这个的update

private:
  inline void animation(float *_pos, float _posTrg, float _speed);

public:
  void setPage(ListMenu* _page);
  bool go(uint8_t _select);
  bool goNext();
  bool goPreview();

  bool open();
  bool close();
  inline void render();
};
}
#endif //ASTRA_ASTRA__H