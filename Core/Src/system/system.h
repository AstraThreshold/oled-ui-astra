//
// Created by Fir on 2024/1/25.
//

#pragma once
#ifndef ASTRA_CORE_SRC_SYSTEM_H_
#define ASTRA_CORE_SRC_SYSTEM_H_

#include "cstdint"

namespace sys {

/**
 * @brief global class of all system param.
 */
class System {
public:
  uint8_t screenBright;
  uint8_t tileAnimationSpeed;
  uint8_t menuAnimationSpeed;
  uint8_t windowAnimationSpeed;
  uint8_t sideBatAnimationSpeed;
  uint8_t fadeAnimationSpeed;

  uint8_t tileUnfold;
  uint8_t menuUnfold;

  uint8_t tileLoop;
  uint8_t menuLoop;

  uint8_t backgroundBlur;
  uint8_t darkMode;

  //todo place other param of system
};
}

#endif //ASTRA_CORE_SRC_SYSTEM_H_