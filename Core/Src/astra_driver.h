//
// Created by Fir on 2024/1/22.
//

#ifndef ASTRA_CORE_SRC_ASTRA_DRIVER_H_
#define ASTRA_CORE_SRC_ASTRA_DRIVER_H_

namespace astra {

class Printer : driver::GraphicsLib {
public:
  void setColor(uint8_t _type);

  void printPixel(uint8_t _x, uint8_t _y);

  void printEnglish(uint8_t _x, uint8_t _y, const std::string& _text);
  void printChinese(uint8_t _x, uint8_t _y, const std::string& _text);

  void printVDottedLine(uint8_t _x, uint8_t _y, uint8_t _l);
  void printHDottedLine(uint8_t _x, uint8_t _y, uint8_t _h);

  void printVLine(uint8_t _x, uint8_t _y, uint8_t _l);
  void printHLine(uint8_t _x, uint8_t _y, uint8_t _h);

  void printImage(uint8_t _x, uint8_t _y, uint8_t _w, uint8_t _h, const uint8_t *_bitMap);

  void printBox(uint8_t _x, uint8_t _y, uint8_t _w, uint8_t _h);
  void printRBox(uint8_t _x, uint8_t _y, uint8_t _w, uint8_t _h, uint8_t _r);

  void printFrame(uint8_t _x, uint8_t _y, uint8_t _w, uint8_t _h);
  void printRFrame(uint8_t _x, uint8_t _y, uint8_t _w, uint8_t _h, uint8_t _r);
};

class KeyScanner : driver::KeyDriver {
public:
  void getKeyValue();
};

}

#endif //ASTRA_CORE_SRC_ASTRA_DRIVER_H_
