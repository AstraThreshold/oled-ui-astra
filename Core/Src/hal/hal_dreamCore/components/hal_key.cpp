//
// Created by Fir on 2024/2/11.
//
#include "../hal_dreamCore.h"
#include "main.h"

void HALDreamCore::_key_init() {

}

bool HALDreamCore::_getKey(key::KEY_INDEX _keyIndex) {
  if (_keyIndex == key::KEY_0) return !HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin);
  if (_keyIndex == key::KEY_1) return !HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin);
}