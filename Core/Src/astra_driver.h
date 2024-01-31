//
// Created by Fir on 2024/1/22.
//

#ifndef ASTRA_CORE_SRC_ASTRA_DRIVER_H_
#define ASTRA_CORE_SRC_ASTRA_DRIVER_H_

#include <cstdint>
#include "driver_i.h"

namespace astra {
class ScreenIC : driver::IcDriver_i {
public:
  static void screenICWriteByteNoCommand(uint8_t _dat);
  static void screenICWriteByte(uint8_t _dat, uint8_t _cmd);
  static void screenSetPosition(uint8_t _x, uint8_t _y);

  void screenClear() override;

  void screenOn() override;
  void screenOff() override;

  void screenICInit() override;
};

class Printer : driver::GraphicsLib_i {
public:
  u8g2_t *canvasBuffer;
  void canvasUpdate() override;
  void canvasClear() override;

  static uint8_t byteCallBack(u8x8_t *u8x8, uint8_t msg, uint8_t argInt, void *argPtr);
  static uint8_t gpioAndDelayCallBack(U8X8_UNUSED u8x8_t *u8x8, U8X8_UNUSED uint8_t msg, U8X8_UNUSED uint8_t argInt, U8X8_UNUSED void *argPtr);
  void graphicsLibInit() override;

  void setDrawType(uint8_t _type) override;
  void drawPixel(uint8_t _x, uint8_t _y) override;
  void drawEnglish(uint8_t _x, uint8_t _y, const std::string &_text) override;
  void drawChinese(uint8_t _x, uint8_t _y, const std::string &_text) override;
  void drawVDottedLine(uint8_t _x, uint8_t _y, uint8_t _l) override;
  void drawHDottedLine(uint8_t _x, uint8_t _y, uint8_t _h) override;
  void drawVLine(uint8_t _x, uint8_t _y, uint8_t _l) override;
  void drawHLine(uint8_t _x, uint8_t _y, uint8_t _h) override;
  void drawBMP(uint8_t _x, uint8_t _y, uint8_t _w, uint8_t _h, const uint8_t *_bitMap) override;
  void drawBox(uint8_t _x, uint8_t _y, uint8_t _w, uint8_t _h) override;
  void drawRBox(uint8_t _x, uint8_t _y, uint8_t _w, uint8_t _h, uint8_t _r) override;
  void drawFrame(uint8_t _x, uint8_t _y, uint8_t _w, uint8_t _h) override;
  void drawRFrame(uint8_t _x, uint8_t _y, uint8_t _w, uint8_t _h, uint8_t _r) override;

  explicit Printer(u8g2_t *_canvasBuffer);
  ~Printer();
};

class KeyScanner : driver::KeyDriver_i {
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

  void keyScan() override;
  void keyTest() override;
};

}

#endif //ASTRA_CORE_SRC_ASTRA_DRIVER_H_
