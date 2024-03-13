//
// Created by Fir on 2024/2/2.
//
#pragma once
#ifndef ASTRA_CORE_SRC_ASTRA_UI_SCHEDULER_H_
#define ASTRA_CORE_SRC_ASTRA_UI_SCHEDULER_H_

#include "element/page/item.h"

namespace astra {

class Launcher {
private:
  Menu* currentPage;
  Selector* selector;
  Camera* camera;

public:
  void init(Menu* _rootPage);

  bool open();
  bool close();

  void start();

  Camera* getCamera() { return camera; }
  Selector* getSelector() { return selector; }
};
}

#endif //ASTRA_CORE_SRC_ASTRA_UI_SCHEDULER_H_