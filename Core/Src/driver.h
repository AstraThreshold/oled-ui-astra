//
// Created by Fir on 2024/1/23.
//

#ifndef ASTRA_CORE_SRC_DRIVER_H_
#define ASTRA_CORE_SRC_DRIVER_H_

#include "../../3rdParty/u8g2/u8g2.h"
#include "main.h"

namespace driver {

class IcDriver {
public:

  void screenICWriteByteNoCommand(uint8_t _dat);
  void screenICWriteByte(uint8_t _dat, uint8_t _cmd);

  void screenClear();
  void screenSetPosition(uint8_t _x, uint8_t _y);

  void screenOn();
  void screenOff();

  void screenICInit();
};

class GraphicsLibDriver {
public:
  u8g2_t *canvasBuffer;

  explicit GraphicsLibDriver(u8g2_t *_canvasBuffer);

  void canvasUpdate();
  void canvasClear();

  static uint8_t byteCallBack(u8x8_t *u8x8, uint8_t msg, uint8_t argInt, void *argPtr);

  static uint8_t gpioAndDelayCallBack(U8X8_UNUSED u8x8_t *u8x8, U8X8_UNUSED uint8_t msg, U8X8_UNUSED uint8_t argInt, U8X8_UNUSED void *argPtr);

  //移植时也可直接继承后重载
  virtual void graphicsLibInit();
};

class GraphicsLib : GraphicsLibDriver {
public:
  //移植时也可直接继承后重载
  virtual void setDrawType(uint8_t _type);

  virtual void drawPixel(uint8_t _x, uint8_t _y);

  virtual void drawEnglish(uint8_t _x, uint8_t _y, const std::string &_text);
  virtual void drawChinese(uint8_t _x, uint8_t _y, const std::string &_text);

  virtual void drawVDottedLine(uint8_t _x, uint8_t _y, uint8_t _l);
  virtual void drawHDottedLine(uint8_t _x, uint8_t _y, uint8_t _h);

  virtual void drawVLine(uint8_t _x, uint8_t _y, uint8_t _l);
  virtual void drawHLine(uint8_t _x, uint8_t _y, uint8_t _h);

  virtual void drawBMP(uint8_t _x, uint8_t _y, uint8_t _w, uint8_t _h, const uint8_t *_bitMap);

  virtual void drawBox(uint8_t _x, uint8_t _y, uint8_t _w, uint8_t _h);
  virtual void drawRBox(uint8_t _x, uint8_t _y, uint8_t _w, uint8_t _h, uint8_t _r);

  virtual void drawFrame(uint8_t _x, uint8_t _y, uint8_t _w, uint8_t _h);
  virtual void drawRFrame(uint8_t _x, uint8_t _y, uint8_t _w, uint8_t _h, uint8_t _r);
};

/**
 * @param keyActionFlag if it equal to KEY_PRESSED, begin process the value.
 * @param keyValue the value of key, throw it to switch case.
 * @warning remember to reset the keyActionFlag to KEY_NOT_PRESSED, after if-else.
 * @post reset the keyActionFlag to KEY_NOT_PRESSED
 */
class KeyDriver {
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

  virtual void keyScan();
  virtual void keyTest();
};

}

#endif //ASTRA_CORE_SRC_DRIVER_H_
