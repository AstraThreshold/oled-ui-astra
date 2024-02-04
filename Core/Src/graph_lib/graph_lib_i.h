//
// Created by Fir on 2024/2/2.
//

#pragma once
#ifndef ASTRA_CORE_SRC_GRAPH_LIB_I_H_
#define ASTRA_CORE_SRC_GRAPH_LIB_I_H_
#include <string>

namespace graphLib {
class GraphicsLib_i{
public:
  ///interface
  virtual void canvasUpdate() = 0;
  virtual void canvasClear() = 0;

  virtual void graphicsLibInit() = 0;

  virtual void getFontWidth(std::string text) = 0;
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
}
#endif //ASTRA_CORE_SRC_GRAPH_LIB_I_H_