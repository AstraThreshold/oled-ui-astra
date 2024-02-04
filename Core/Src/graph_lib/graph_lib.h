//
// Created by Fir on 2024/2/2.
//
#pragma once
#ifndef ASTRA_CORE_SRC_GRAPH_LIB_H_
#define ASTRA_CORE_SRC_GRAPH_LIB_H_
#include "graph_lib_i.h"
#include "../../../3rdParty/u8g2/u8g2.h"

namespace graphLib {
class GraphicsLib : GraphicsLib_i {
public:
  u8g2_t *canvasBuffer{};
  void canvasUpdate() override;
  void canvasClear() override;

  static uint8_t byteCallBack(u8x8_t *u8x8, uint8_t msg, uint8_t argInt, void *argPtr);
  static uint8_t gpioAndDelayCallBack(U8X8_UNUSED u8x8_t *u8x8, U8X8_UNUSED uint8_t msg, U8X8_UNUSED uint8_t argInt, U8X8_UNUSED void *argPtr);
  void graphicsLibInit() override;

  void getFontWidth(std::string text) override;
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

  explicit GraphicsLib(u8g2_t *_canvasBuffer);
  GraphicsLib() = default;
  ~GraphicsLib() = default;
};
}
#endif //ASTRA_CORE_SRC_GRAPH_LIB_H_