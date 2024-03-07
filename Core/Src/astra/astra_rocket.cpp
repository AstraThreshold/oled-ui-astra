//
// Created by Fir on 2024/3/7 007.
//

#include "astra_rocket.h"

astra::Launcher* astraLauncher = new astra::Launcher();

void astraCoreInit(void) {
  astraLauncher->init(nullptr);
}

void astraCoreStart(void) {
  for (;;) {  //NOLINT
    astraLauncher->start();
  }
}
