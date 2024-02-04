//
// Created by Fir on 2024/2/2.
//

#include "launcher.h"

namespace astra {

AstraLauncher::AstraLauncher(Page *_rootPage) {
  this->render = new render::Render;
  this->pageDisplay = _rootPage;
}

void AstraLauncher::launch() {



  hardware::KeyScanner::keyScan();
  hardware::KeyScanner::keyValue;
}

}
