//
// Created by Fir on 2024/2/11.
//

#pragma once
#ifndef ASTRA_CORE_SRC_HAL_HAL_DREAMCORE_HAL_DREAMCORE_H_
#define ASTRA_CORE_SRC_HAL_HAL_DREAMCORE_HAL_DREAMCORE_H_
#include "../hal.h"
#include "components/oled/graph_lib/u8g2/u8g2.h"

class HALDreamCore : public HAL {
private:
  void _stm32_hal_init();
  void _sys_clock_init();
  void _gpio_init();
  void _dma_init();
  void _timer_init();
  void _spi_init();

  void _ssd1306_init();
  void _key_init();
  void _buzzer_init();
  void _u8g2_init();

public:
  HALDreamCore() = default;

  inline void init() override {
    _stm32_hal_init();
    _sys_clock_init();
    _gpio_init();
    _dma_init();
    _timer_init();
    _spi_init();

    _ssd1306_init();
    _key_init();
    _buzzer_init();
    _u8g2_init();
  }

protected:
  void _ssd1306_reset(bool _state);
  void _ssd1306_transmit(uint8_t _data, bool _isCmd);

public:
  void _screenOn() override;
  void _screenOff() override;

protected:
  u8g2_t canvasBuffer;
  static uint8_t _u8x8_byte_hw_spi_callback(u8x8_t* _u8x8, uint8_t _msg, uint8_t _argInt, void* _argPtr);
  static uint8_t _u8x8_gpio_and_delay_callback(U8X8_UNUSED u8x8_t* _u8x8,
                                     U8X8_UNUSED uint8_t _msg,
                                     U8X8_UNUSED uint8_t _argInt,
                                     U8X8_UNUSED void* _argPtr);

public:
  void* _getCanvasBuffer() override;
  void _canvasUpdate() override;
  void _canvasClear() override;
  void _setFont(const uint8_t * _font) override;
  uint8_t _getFontWidth(std::string& _text) override;
  uint8_t _getFontHeight() override;
  void _setDrawType(uint8_t _type) override;
  void _drawPixel(uint8_t _x, uint8_t _y) override;
  void _drawEnglish(uint8_t _x, uint8_t _y, const std::string& _text) override;
  void _drawChinese(uint8_t _x, uint8_t _y, const std::string& _text) override;
  void _drawVDottedLine(uint8_t _x, uint8_t _y, uint8_t _h) override;
  void _drawHDottedLine(uint8_t _x, uint8_t _y, uint8_t _l) override;
  void _drawVLine(uint8_t _x, uint8_t _y, uint8_t _h) override;
  void _drawHLine(uint8_t _x, uint8_t _y, uint8_t _l) override;
  void _drawBMP(uint8_t _x, uint8_t _y, uint8_t _w, uint8_t _h, const uint8_t* _bitMap) override;
  void _drawBox(uint8_t _x, uint8_t _y, uint8_t _w, uint8_t _h) override;
  void _drawRBox(uint8_t _x, uint8_t _y, uint8_t _w, uint8_t _h, uint8_t _r) override;
  void _drawFrame(uint8_t _x, uint8_t _y, uint8_t _w, uint8_t _h) override;
  void _drawRFrame(uint8_t _x, uint8_t _y, uint8_t _w, uint8_t _h, uint8_t _r) override;

public:
  void _delay(unsigned long _mill) override;
  unsigned long _millis() override;

public:
  void _beep(float _freq) override;
  void _beepStop() override;
  void _setBeepVol(uint8_t _vol) override;

public:
  bool _getKey(key::KEY_INDEX _keyIndex) override;

public:
  void _updateConfig() override;
};

#endif //ASTRA_CORE_SRC_HAL_HAL_DREAMCORE_HAL_DREAMCORE_H_
