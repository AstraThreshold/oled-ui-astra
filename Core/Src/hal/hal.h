//
// Created by Fir on 2024/2/8.
//
#pragma once
#ifndef ASTRA_CORE_SRC_HAL_HAL_H_
#define ASTRA_CORE_SRC_HAL_HAL_H_

#include <string>
#include <vector>
#include "graph_lib.h"
#include "../astra/config/config.h"

namespace oled {

}

namespace key {
typedef enum {
  KEY_CHECK = 0,
  KEY0_CONFIRM,
  KEY1_CONFIRM,
  KEY_RELEASE,
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

typedef enum {
  KEY_0 = 0,
  KEY_1,
} KEY_INDEX;
}

namespace buzzer {

}

namespace led {

}

namespace sys {
struct config {
  uint8_t screenWeight = 128;
  uint8_t screenHeight = 64;
  uint8_t screenBright = 255;
  //todo place other param of system
};
}

/**
 * @brief hardware abstraction layer.
 * @note provide a set of interfaces to access hardware.
 * @note provide some default implementation.
 */
class HAL {
private:
  static HAL* hal;

public:
  static HAL* get();
  static bool check();
  static bool inject(HAL *_hal);
  static void destroy();

  virtual ~HAL() {}
  virtual std::string type() { return "Base"; }
  virtual void init() {}

protected:
  sys::config config;

  //todo: may-be unused.
  void* canvasBuffer = nullptr;

public:
  static void* getCanvasBuffer() { return get()->_getCanvasBuffer(); }
  virtual void* _getCanvasBuffer() { return nullptr; }

  static void canvasUpdate() { get()->_canvasUpdate(); }
  virtual void _canvasUpdate() {}

  static void canvasClear() { get()->_canvasClear(); }
  virtual void _canvasClear() {}

  static void setFont(const uint8_t * _font) { get()->_setFont(_font); }
  virtual void _setFont(const uint8_t * _font) {}

  static void getFontWidth(std::string& _text) { get()->_getFontWidth(_text); }
  virtual void _getFontWidth(std::string& _text) {}

  static void getFontHeight() { get()->_getFontHeight(); }
  virtual void _getFontHeight() {}

  static void setDrawType(uint8_t _type) { get()->_setDrawType(_type); }
  virtual void _setDrawType(uint8_t _type) {}

  static void drawPixel(uint8_t _x, uint8_t _y) { get()->_drawPixel(_x, _y); }
  virtual void _drawPixel(uint8_t _x, uint8_t _y) {}

  static void drawEnglish(uint8_t _x, uint8_t _y, const std::string& _text) { get()->_drawEnglish(_x, _y, _text); }
  virtual void _drawEnglish(uint8_t _x, uint8_t _y, const std::string& _text) {}

  static void drawChinese(uint8_t _x, uint8_t _y, const std::string& _text) { get()->_drawChinese(_x, _y, _text); }
  virtual void _drawChinese(uint8_t _x, uint8_t _y, const std::string& _text) {}

  static void drawVDottedLine(uint8_t _x, uint8_t _y, uint8_t _l) { get()->_drawVDottedLine(_x, _y, _l); }
  virtual void _drawVDottedLine(uint8_t _x, uint8_t _y, uint8_t _l) {}

  static void drawHDottedLine(uint8_t _x, uint8_t _y, uint8_t _h) { get()->_drawHDottedLine(_x, _y, _h); }
  virtual void _drawHDottedLine(uint8_t _x, uint8_t _y, uint8_t _h) {}

  static void drawVLine(uint8_t _x, uint8_t _y, uint8_t _l) { get()->_drawVLine(_x, _y, _l); }
  virtual void _drawVLine(uint8_t _x, uint8_t _y, uint8_t _l) {}

  static void drawHLine(uint8_t _x, uint8_t _y, uint8_t _h) { get()->_drawHLine(_x, _y, _h); }
  virtual void _drawHLine(uint8_t _x, uint8_t _y, uint8_t _h) {}

  static void drawBMP(uint8_t _x, uint8_t _y, uint8_t _w, uint8_t _h, const uint8_t* _bitMap) { get()->_drawBMP(_x, _y, _w, _h, _bitMap); }
  virtual void _drawBMP(uint8_t _x, uint8_t _y, uint8_t _w, uint8_t _h, const uint8_t* _bitMap) {}

  static void drawBox(uint8_t _x, uint8_t _y, uint8_t _w, uint8_t _h) { get()->_drawBox(_x, _y, _w, _h); }
  virtual void _drawBox(uint8_t _x, uint8_t _y, uint8_t _w, uint8_t _h) {}

  static void drawRBox(uint8_t _x, uint8_t _y, uint8_t _w, uint8_t _h, uint8_t _r) { get()->_drawRBox(_x, _y, _w, _h, _r); }
  virtual void _drawRBox(uint8_t _x, uint8_t _y, uint8_t _w, uint8_t _h, uint8_t _r) {}

  static void drawFrame(uint8_t _x, uint8_t _y, uint8_t _w, uint8_t _h) { get()->_drawFrame(_x, _y, _w, _h); }
  virtual void _drawFrame(uint8_t _x, uint8_t _y, uint8_t _w, uint8_t _h) {}

  static void drawRFrame(uint8_t _x, uint8_t _y, uint8_t _w, uint8_t _h, uint8_t _r) { get()->_drawRFrame(_x, _y, _w, _h, _r); }
  virtual void _drawRFrame(uint8_t _x, uint8_t _y, uint8_t _w, uint8_t _h, uint8_t _r) {}

  static void printInfo(std::string _msg) { get()->_printInfo(_msg); }
  virtual void _printInfo(std::string _msg);

  /**
   * @brief system timers.
   */
public:
  static void delay(unsigned long _mill) { get()->_delay(_mill); }
  virtual void _delay(unsigned long _mill) {}

  static unsigned long millis() { return get()->_millis(); }
  virtual unsigned long _millis() { return 0; }

  /**
   * @brief buzzer.
   * */
public:
  static void beep(float _freq) { get()->_beep(_freq); }
  virtual void _beep(float _freq) {}

  static void beepStop() { get()->_beepStop(); }
  virtual void _beepStop() {}

  static void setBeepVol(uint8_t _vol) { get()->_setBeepVol(_vol); }
  virtual void _setBeepVol(uint8_t _vol) {}

  static void screenOn() { get()->_screenOn(); }
  virtual void _screenOn() {}

  static void screenOff() { get()->_screenOff(); }
  virtual void _screenOff() {}

  /**
   * @brief key.
   */
public:
  static bool getKeyValue(key::KEY_INDEX _keyIndex) { return get()->_getKeyValue(_keyIndex); }
  virtual bool _getKeyValue(key::KEY_INDEX _keyIndex) { return false; }

  static void keyScan() { return get()->_keyScan(); }
  virtual void _keyScan();

  static void keyTest() { return get()->_keyTest(); }
  virtual void _keyTest();

  /**
   * @brief system config.
   */
public:
  static sys::config& getSystemConfig() { return get()->config; }
  static void setSystemConfig(sys::config _cfg) { get()->config = _cfg; }

  static void updateConfig() { get()->_updateConfig(); }
  virtual void _updateConfig() {}
};

#endif //ASTRA_CORE_SRC_HAL_HAL_H_
