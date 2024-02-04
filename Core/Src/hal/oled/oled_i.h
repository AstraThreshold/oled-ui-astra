//
// Created by Fir on 2024/2/2.
//
#pragma once
#ifndef ASTRA_CORE_SRC_OLED_I_H_
#define ASTRA_CORE_SRC_OLED_I_H_

namespace hardware {
class IcDriver_i {
public:
  virtual void screenClear() = 0;

  virtual void screenOn() = 0;
  virtual void screenOff() = 0;

  virtual void screenICInit() = 0;
};
}
#endif //ASTRA_CORE_SRC_OLED_I_H_