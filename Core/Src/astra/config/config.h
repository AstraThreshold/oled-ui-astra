//
// Created by Fir on 2024/1/25.
//

#pragma once
#ifndef ASTRA_CORE_SRC_SYSTEM_H_
#define ASTRA_CORE_SRC_SYSTEM_H_

#include "cstdint"

namespace astra {
/**
 * @brief config of astra ui. astra ui的配置结构体
 */
struct config {
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
};
}

#endif //ASTRA_CORE_SRC_SYSTEM_H_