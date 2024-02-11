//
// Created by Fir on 2024/2/11.
//

#pragma once
#ifndef ASTRA_CORE_SRC_HAL_HAL_DREAMCORE_HAL_DREAMCORE_H_
#define ASTRA_CORE_SRC_HAL_HAL_DREAMCORE_HAL_DREAMCORE_H_
#include "../hal.h"

class HALDreamCore : public HAL {
private:
  KEY_STATE keyState = KEY_CHECK;
  KEY_TYPE keyActionFlag = KEY_NOT_PRESSED;
  KEY_VALUE keyValue = KEY_NULL;

private:
  void _stm32_hal_init();
  void _sys_clock_init();
  void _gpio_init();
  void _timer_init();
  void _ssd1306_init();
  void _spi_init();
  void _dma_init();
  void _key_init();
  void _beep_init();
  void _u8g2_init();

public:
  HALDreamCore() = default;

  inline void init() override {
    _stm32_hal_init();
    _sys_clock_init();
    _gpio_init();
    _timer_init();
    _ssd1306_init();
    _spi_init();
    _dma_init();
    _key_init();
    _beep_init();
    _u8g2_init();
  }

  void* _getCanvasBuffer() override;
  void _delay(unsigned long _mill) override;
  unsigned long _millis() override;
  void _beep(float _freq) override;
  void _beepStop() override;
  void _setBeepVol(uint8_t _vol) override;
  void _canvasUpdate() override;
  bool _getKeyValue(key::KEY_INDEX _keyIndex) override;
  void _updateConfig() override;
};

#endif //ASTRA_CORE_SRC_HAL_HAL_DREAMCORE_HAL_DREAMCORE_H_
