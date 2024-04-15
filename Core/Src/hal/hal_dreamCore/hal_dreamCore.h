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
  void _adc_init();

  void _ssd1306_init();
  void _key_init();
  void _buzzer_init();
  void _u8g2_init();

public:
  HALDreamCore() = default;

protected:
  u8g2_t canvasBuffer {};
  static unsigned char _u8x8_byte_hw_spi_callback(u8x8_t* _u8x8, unsigned char _msg, unsigned char _argInt, void* _argPtr);

  static unsigned char _u8x8_gpio_and_delay_callback(U8X8_UNUSED u8x8_t* _u8x8,
                                               U8X8_UNUSED unsigned char _msg,
                                               U8X8_UNUSED unsigned char _argInt,
                                               U8X8_UNUSED void* _argPtr);

public:
  inline void init() override {
    _stm32_hal_init();
    _sys_clock_init();
    _gpio_init();
    _dma_init();
    _timer_init();
    _spi_init();
    _adc_init();

    _ssd1306_init();
    _key_init();
    _buzzer_init();
    _u8g2_init();
  }

protected:
  void _ssd1306_transmit_cmd(unsigned char _cmd);
  void _ssd1306_transmit_data(unsigned char _data, unsigned char _mode);
  void _ssd1306_reset(bool _state);
  void _ssd1306_set_cursor(unsigned char _x, unsigned char _y);
  void _ssd1306_fill(unsigned char _data);

public:
  void _screenOn() override;
  void _screenOff() override;

public:
  void* _getCanvasBuffer() override;
  unsigned char _getBufferTileHeight() override;
  unsigned char _getBufferTileWidth() override;
  void _canvasUpdate() override;
  void _canvasClear() override;
  void _setFont(const unsigned char * _font) override;
  unsigned char _getFontWidth(std::string& _text) override;
  unsigned char _getFontHeight() override;
  void _setDrawType(unsigned char _type) override;
  void _drawPixel(float _x, float _y) override;
  void _drawEnglish(float _x, float _y, const std::string& _text) override;
  void _drawChinese(float _x, float _y, const std::string& _text) override;
  void _drawVDottedLine(float _x, float _y, float _h) override;
  void _drawHDottedLine(float _x, float _y, float _l) override;
  void _drawVLine(float _x, float _y, float _h) override;
  void _drawHLine(float _x, float _y, float _l) override;
  void _drawBMP(float _x, float _y, float _w, float _h, const unsigned char* _bitMap) override;
  void _drawBox(float _x, float _y, float _w, float _h) override;
  void _drawRBox(float _x, float _y, float _w, float _h, float _r) override;
  void _drawFrame(float _x, float _y, float _w, float _h) override;
  void _drawRFrame(float _x, float _y, float _w, float _h, float _r) override;

public:
  void _delay(unsigned long _mill) override;
  unsigned long _millis() override;
  unsigned long _getTick() override;
  unsigned long _getRandomSeed() override;

public:
  void _beep(float _freq) override;
  void _beepStop() override;
  void _setBeepVol(unsigned char _vol) override;

public:
  bool _getKey(key::KEY_INDEX _keyIndex) override;

public:
  void _updateConfig() override;
};

#endif //ASTRA_CORE_SRC_HAL_HAL_DREAMCORE_HAL_DREAMCORE_H_
