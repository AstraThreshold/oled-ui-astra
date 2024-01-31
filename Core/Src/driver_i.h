//
// Created by Fir on 2024/1/23.
//

#ifndef ASTRA_CORE_SRC_DRIVER_I_H_
#define ASTRA_CORE_SRC_DRIVER_I_H_

#include "../../3rdParty/u8g2/u8g2.h"
#include "main.h"
#include <string>
#include "spi.h"

namespace driver {

class IcDriver_i {
public:
  virtual void screenClear() = 0;

  virtual void screenOn() = 0;
  virtual void screenOff() = 0;

  virtual void screenICInit() = 0;
};

class GraphicsLib_i{
public:
  //interface
  virtual void canvasUpdate() = 0;
  virtual void canvasClear() = 0;

  virtual void graphicsLibInit() = 0;

  virtual void setDrawType(uint8_t _type) = 0;

  virtual void drawPixel(uint8_t _x, uint8_t _y) = 0;

  virtual void drawEnglish(uint8_t _x, uint8_t _y, const std::string &_text) = 0;
  virtual void drawChinese(uint8_t _x, uint8_t _y, const std::string &_text) = 0;

  virtual void drawVDottedLine(uint8_t _x, uint8_t _y, uint8_t _l) = 0;
  virtual void drawHDottedLine(uint8_t _x, uint8_t _y, uint8_t _h) = 0;

  virtual void drawVLine(uint8_t _x, uint8_t _y, uint8_t _l) = 0;
  virtual void drawHLine(uint8_t _x, uint8_t _y, uint8_t _h) = 0;

  virtual void drawBMP(uint8_t _x, uint8_t _y, uint8_t _w, uint8_t _h, const uint8_t *_bitMap) = 0;

  virtual void drawBox(uint8_t _x, uint8_t _y, uint8_t _w, uint8_t _h) = 0;
  virtual void drawRBox(uint8_t _x, uint8_t _y, uint8_t _w, uint8_t _h, uint8_t _r) = 0;

  virtual void drawFrame(uint8_t _x, uint8_t _y, uint8_t _w, uint8_t _h) = 0;
  virtual void drawRFrame(uint8_t _x, uint8_t _y, uint8_t _w, uint8_t _h, uint8_t _r) = 0;
};

/**
 * @param keyActionFlag if it equal to KEY_PRESSED, begin process the value.
 * @param keyValue the value of key, throw it to switch case.
 * @warning remember to reset the keyActionFlag to KEY_NOT_PRESSED, after if-else.
 * @post reset the keyActionFlag to KEY_NOT_PRESSED
 */
class KeyDriver_i {
public:
  virtual void keyScan() = 0;
  virtual void keyTest() = 0;
};

}

#endif //ASTRA_CORE_SRC_DRIVER_I_H_
