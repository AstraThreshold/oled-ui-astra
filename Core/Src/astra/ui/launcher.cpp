//
// Created by Fir on 2024/2/2.
//

#include "launcher.h"

namespace astra {

Launcher::Launcher(Page *_rootPage) {
  this->node = _rootPage;
}

void Launcher::start() {

}

bool Launcher::addItem(const std::string &_title, Page *_page) {
  return false;
}

bool Launcher::addItem(const std::string &_title,
                       const std::vector<uint8_t> &_pic,
                       Page *_page) {
  return false;
}
}
