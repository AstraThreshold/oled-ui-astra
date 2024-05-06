//
// Created by Fir on 2024/2/8.
//
#pragma once
#ifndef ASTRA_CORE_SRC_HAL_HAL_H_
#define ASTRA_CORE_SRC_HAL_HAL_H_

#include <string>
#include <utility>
#include <array>
#include <vector>
#include "../astra/config/config.h"

namespace oled {

}

namespace key {
typedef enum keyFilter {
  CHECKING = 0,
  KEY_0_CONFIRM,
  KEY_1_CONFIRM,
  RELEASED,
} KEY_FILTER;

typedef enum keyAction {
  INVALID = 0,
  CLICK,
  PRESS,
} KEY_ACTION;

typedef enum KeyType {
  KEY_NOT_PRESSED = 0,
  KEY_PRESSED,
} KEY_TYPE;

typedef enum keyIndex {
  KEY_0 = 0,
  KEY_1,
  KEY_NUM,
} KEY_INDEX;
}

namespace buzzer {

}

namespace led {

}

namespace sys {
struct config {
  unsigned char screenWeight = 128;
  unsigned char screenHeight = 64;
  float screenBright = 255;
};

static config &getSystemConfig() {
  static config sysConfig;
  return sysConfig;
}
}

/**
 * @brief hardware abstraction layer.
 * @note provide a set of interfaces to access hardware.
 * @note provide some default implementation.
 */
class HAL {
private:
  static HAL *hal;

public:
  static HAL *get();    //get hal instance.
  static bool check();  //check if there is a hal instance.

  static bool inject(HAL *_hal);  //inject HAL instance and run hal_init.
  static void destroy();  //destroy HAL instance.

  virtual ~HAL() = default;

  virtual std::string type() { return "Base"; }

  virtual void init() {}

protected:
  sys::config config;

public:
  static void *getCanvasBuffer() { return get()->_getCanvasBuffer(); }

  virtual void *_getCanvasBuffer() { return nullptr; }

  static unsigned char getBufferTileHeight() { return get()->_getBufferTileHeight(); }

  virtual unsigned char _getBufferTileHeight() { return 0; }

  static unsigned char getBufferTileWidth() { return get()->_getBufferTileWidth(); }

  virtual unsigned char _getBufferTileWidth() { return 0; }

  static void canvasUpdate() { get()->_canvasUpdate(); }

  virtual void _canvasUpdate() {}

  static void canvasClear() { get()->_canvasClear(); }

  virtual void _canvasClear() {}

  static void setFont(const unsigned char *_font) { get()->_setFont(_font); }

  virtual void _setFont(const unsigned char *_font) {}

  static unsigned char getFontWidth(std::string &_text) { return get()->_getFontWidth(_text); }

  virtual unsigned char _getFontWidth(std::string &_text) { return 0; }

  static unsigned char getFontHeight() { return get()->_getFontHeight(); }

  virtual unsigned char _getFontHeight() { return 0; }

  static void setDrawType(unsigned char _type) { get()->_setDrawType(_type); }

  virtual void _setDrawType(unsigned char _type) {}

  static void drawPixel(float _x, float _y) { get()->_drawPixel(_x, _y); }

  virtual void _drawPixel(float _x, float _y) {}

  //notice: _x和_y是字体左下角的坐标 _x and _y is the coordinate the lower left corner of the font
  static void drawEnglish(float _x, float _y, const std::string &_text) { get()->_drawEnglish(_x, _y, _text); }

  virtual void _drawEnglish(float _x, float _y, const std::string &_text) {}

  static void drawChinese(float _x, float _y, const std::string &_text) { get()->_drawChinese(_x, _y, _text); }

  virtual void _drawChinese(float _x, float _y, const std::string &_text) {}

  static void drawVDottedLine(float _x, float _y, float _h) { get()->_drawVDottedLine(_x, _y, _h); }

  virtual void _drawVDottedLine(float _x, float _y, float _h) {}

  static void drawHDottedLine(float _x, float _y, float _l) { get()->_drawHDottedLine(_x, _y, _l); }

  virtual void _drawHDottedLine(float _x, float _y, float _l) {}

  static void drawVLine(float _x, float _y, float _h) { get()->_drawVLine(_x, _y, _h); }

  virtual void _drawVLine(float _x, float _y, float _h) {}

  static void drawHLine(float _x, float _y, float _l) { get()->_drawHLine(_x, _y, _l); }

  virtual void _drawHLine(float _x, float _y, float _l) {}

  static void drawBMP(float _x, float _y, float _w, float _h, const unsigned char *_bitMap) {
    get()->_drawBMP(_x,
                    _y,
                    _w,
                    _h,
                    _bitMap);
  }

  virtual void _drawBMP(float _x, float _y, float _w, float _h, const unsigned char *_bitMap) {}

  static void drawBox(float _x, float _y, float _w, float _h) { get()->_drawBox(_x, _y, _w, _h); }

  virtual void _drawBox(float _x, float _y, float _w, float _h) {}

  static void drawRBox(float _x, float _y, float _w, float _h, float _r) {
    get()->_drawRBox(_x,
                     _y,
                     _w,
                     _h,
                     _r);
  }

  virtual void _drawRBox(float _x, float _y, float _w, float _h, float _r) {}

  static void drawFrame(float _x, float _y, float _w, float _h) { get()->_drawFrame(_x, _y, _w, _h); }

  virtual void _drawFrame(float _x, float _y, float _w, float _h) {}

  static void drawRFrame(float _x, float _y, float _w, float _h, float _r) {
    get()->_drawRFrame(_x,
                       _y,
                       _w,
                       _h,
                       _r);
  }

  virtual void _drawRFrame(float _x, float _y, float _w, float _h, float _r) {}

  static void printInfo(std::string _msg) { get()->_printInfo(std::move(_msg)); }

  virtual void _printInfo(std::string _msg);

  /**
   * @brief system timers.
   */
public:
  static void delay(unsigned long _mill) { get()->_delay(_mill); }

  virtual void _delay(unsigned long _mill) {}

  static unsigned long millis() { return get()->_millis(); }

  virtual unsigned long _millis() { return 0; }

  static unsigned long getTick() { return get()->_getTick(); }

  virtual unsigned long _getTick() { return 0; }

  static unsigned long getRandomSeed() { return get()->_getRandomSeed(); }

  /**optional**/
  virtual unsigned long _getRandomSeed() { return 0; }

  /**
   * @brief buzzer.
   * */
public:
  static void beep(float _freq) { get()->_beep(_freq); }

  virtual void _beep(float _freq) {}

  static void beepStop() { get()->_beepStop(); }

  virtual void _beepStop() {}

  static void setBeepVol(unsigned char _vol) { get()->_setBeepVol(_vol); }

  virtual void _setBeepVol(unsigned char _vol) {}

  static void screenOn() { get()->_screenOn(); }

  virtual void _screenOn() {}

  static void screenOff() { get()->_screenOff(); }

  virtual void _screenOff() {}

  /**
   * @brief key.
   */

public:
  key::KEY_ACTION key[key::KEY_NUM] = {static_cast<key::keyAction>(0)};
  key::KEY_TYPE keyFlag { static_cast<key::KEY_TYPE>(0) };

public:
  static bool getKey(key::KEY_INDEX _keyIndex) { return get()->_getKey(_keyIndex); }

  virtual bool _getKey(key::KEY_INDEX _keyIndex) { return false; }

  static bool getAnyKey() { return get()->_getAnyKey(); }

  virtual bool _getAnyKey();

  static key::KEY_ACTION *getKeyMap() { return get()->key; }

  static key::KEY_TYPE *getKeyFlag() { return &get()->keyFlag; }

public:
  static void keyScan() { get()->_keyScan(); }

  virtual void _keyScan();

  static void keyTest() { return get()->_keyTest(); }

  virtual void _keyTest();

  /**
   * @brief system config.
   */
public:
  static sys::config &getSystemConfig() { return get()->config; }

  static void setSystemConfig(sys::config _cfg) { get()->config = _cfg; }

  static void updateConfig() { get()->_updateConfig(); }

  virtual void _updateConfig() {}
};

#endif //ASTRA_CORE_SRC_HAL_HAL_H_
