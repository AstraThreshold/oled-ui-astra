//
// Created by Fir on 2024/2/8.
//

#include "hal.h"

HAL *HAL::hal = nullptr;

HAL *HAL::get() {
  return hal;
}

bool HAL::check() {
  return hal != nullptr;
}

bool HAL::inject(HAL *_hal) {
  if (hal != nullptr) {
    return false;
  }
  if (_hal == nullptr) {
    return false;
  }

  _hal->init();
  hal = _hal;
  return true;
}

void HAL::destroy() {
  if (hal == nullptr) return;

  delete hal;
  hal = nullptr;
}

/**
 * @brief 自动换行的日志输出
 *
 * @param _msg 要输出的信息
 */
void HAL::_printInfo(std::string _msg) {
  static std::vector<std::string> _infoCache = {};
  _infoCache.push_back(_msg);
  getGraphics()->canvasClear();
  getGraphics()->setDrawType(2); //反色显示
  getGraphics()->setFontType(u8g2_font_myfont);
  static const uint8_t _fontHeight = getGraphics()->getFontHeight();
  for (uint8_t i = 0; i < _infoCache.size(); i++) {
    getGraphics()->drawEnglish(0, 1 + i * (1 + _fontHeight), _infoCache[i]);
  }
  getGraphics()->canvasUpdate();
  getGraphics()->setDrawType(1); //回归实色显示
}

/**
 * @brief key scanner default. 默认按键扫描函数
 */
void HAL::_keyScan() {
  static uint8_t _timeCnt = 0;
  static uint8_t _lock = 0;
  switch (key::keyState) {

  }
}

/**
 * @brief default key tester. 默认按键测试函数
 */
void HAL::_keyTest() {

}
