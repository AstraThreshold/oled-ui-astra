//
// Created by Fir on 2024/2/2.
//

#pragma once
#ifndef ASTRA_CORE_SRC_KEY_H_
#define ASTRA_CORE_SRC_KEY_H_
#include <cstdint>
#include "main.h"
#include "key_i.h"

namespace hardware {
class KeyScanner : hardware::KeyDriver_i {
public:
  typedef enum {
    KEY_CHECK = 0,
    KEY0_CONFIRM,
    KEY1_CONFIRM,
    KEY_RELEASE
  } KEY_STATE;

  typedef enum {
    KEY_NOT_PRESSED = 0,
    KEY_PRESSED,
  } KEY_TYPE;

  typedef enum {
    KEY_NULL = 0,
    KEY_0_CLICK,  //轻击
    KEY_0_PRESS,  //长按
    KEY_1_CLICK,
    KEY_1_PRESS,
  } KEY_VALUE;

  uint8_t key1 = HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin);
  uint8_t key2 = HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin);
  uint8_t key = key1 | key2;

  KEY_STATE keyState = KEY_CHECK;
  KEY_TYPE keyActionFlag = KEY_NOT_PRESSED;
  KEY_VALUE keyValue = KEY_NULL;

  void keyScan() override;
  void keyTest() override;
};
}
#endif //ASTRA_CORE_SRC_KEY_H_