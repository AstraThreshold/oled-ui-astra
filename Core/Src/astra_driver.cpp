//
// Created by Fir on 2024/1/22.
//

#include <string>
#include "driver.h"
#include "astra_driver.h"

//ui驱动和底层驱动解耦 方便移植
namespace astra {
void Printer::setColor(uint8_t _type) {
  driver::GraphicsLib::setDrawType(_type);
}

void Printer::printPixel(uint8_t _x, uint8_t _y) {
  driver::GraphicsLib::drawPixel(_x, _y);
}

void Printer::printEnglish(uint8_t _x, uint8_t _y, const std::string &_text) {
  driver::GraphicsLib::drawEnglish(_x, _y, _text);
}

void Printer::printChinese(uint8_t _x, uint8_t _y, const std::string &_text) {
  driver::GraphicsLib::drawChinese(_x, _y, _text);
}

void Printer::printVDottedLine(uint8_t _x, uint8_t _y, uint8_t _l) {
  driver::GraphicsLib::drawVDottedLine(_x, _y, _l);
}

void Printer::printHDottedLine(uint8_t _x, uint8_t _y, uint8_t _h) {
  driver::GraphicsLib::drawHDottedLine(_x, _y, _h);
}

void Printer::printVLine(uint8_t _x, uint8_t _y, uint8_t _l) {
  driver::GraphicsLib::drawVLine(_x, _y, _l);
}

void Printer::printHLine(uint8_t _x, uint8_t _y, uint8_t _h) {
  driver::GraphicsLib::drawHLine(_x, _y, _h);
}

void Printer::printImage(uint8_t _x, uint8_t _y, uint8_t _w, uint8_t _h, const uint8_t *_bitMap) {
  driver::GraphicsLib::drawBMP(_x, _y, _w, _h, _bitMap);
}

void Printer::printBox(uint8_t _x, uint8_t _y, uint8_t _w, uint8_t _h) {
  driver::GraphicsLib::drawBox(_x, _y, _w, _h);
}

void Printer::printRBox(uint8_t _x, uint8_t _y, uint8_t _w, uint8_t _h, uint8_t _r) {
  driver::GraphicsLib::drawRBox(_x, _y, _w, _h, _r);
}

void Printer::printFrame(uint8_t _x, uint8_t _y, uint8_t _w, uint8_t _h) {
  driver::GraphicsLib::drawFrame(_x, _y, _w, _h);
}

void Printer::printRFrame(uint8_t _x, uint8_t _y, uint8_t _w, uint8_t _h, uint8_t _r) {
  driver::GraphicsLib::drawRFrame(_x, _y, _w, _h, _r);
}

void KeyScanner::getKeyValue() {
  driver::KeyDriver::keyScan();
}
}

