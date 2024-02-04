//
// Created by Fir on 2024/2/2.
//
#pragma once
#ifndef ASTRA_CORE_SRC_OLED_H_
#define ASTRA_CORE_SRC_OLED_H_
#include <cstdint>
#include "oled_i.h"

namespace hardware {
class ScreenIC : hardware::IcDriver_i {
public:
  static void screenICWriteByteNoCommand(uint8_t _dat);
  static void screenICWriteByte(uint8_t _dat, uint8_t _cmd);
  static void screenSetPosition(uint8_t _x, uint8_t _y);

  void screenClear() override;

  void screenOn() override;
  void screenOff() override;

  void screenICInit() override;
};
}
#endif //ASTRA_CORE_SRC_OLED_H_