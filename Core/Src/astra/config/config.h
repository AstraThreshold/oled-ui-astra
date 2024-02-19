//
// Created by Fir on 2024/1/25.
//

#pragma once
#ifndef ASTRA_CORE_SRC_SYSTEM_H_
#define ASTRA_CORE_SRC_SYSTEM_H_

#include "cstdint"

namespace astra {
/**
 * @brief config of astra ui. astra ui的配置结构体
 */
struct config {
  uint8_t tileAnimationSpeed = 50.0f;
  uint8_t menuAnimationSpeed = 50.0f;
  uint8_t selectorAnimationSpeed = 50.0f;
  uint8_t windowAnimationSpeed;
  uint8_t sideBarAnimationSpeed;
  uint8_t fadeAnimationSpeed;
  uint8_t cameraAnimationSpeed;

  bool tileUnfold = true;
  bool listUnfold = true;

  bool tileLoop = true;
  bool menuLoop = true;

  uint8_t backgroundBlur;
  uint8_t lightMode;

  uint8_t listBarWeight = 5;
  uint8_t listTextHeight = 8;
  uint8_t listTextMargin = 4; //文字边距
  uint8_t listLineHeight = 16;
  float selectorRadius = 0.5f;

  uint8_t tilePicWidth = 30;
  uint8_t tilePicHeight = 30;
  uint8_t tilePicMargin = 38;
  uint8_t tilePicTopMargin = 7; //图标上边距
  uint8_t tileArrowWidth = 6;
  uint8_t tileArrowMargin = 4; //箭头边距
  uint8_t tileDottedLineMargin = 46; //虚线上边距
  uint8_t tileArrowTopMargin = 46; //箭头上边距
  uint8_t tileTextTopMargin = ; //标题上边距

  uint8_t tileBtnMargin = 16; //按钮边距
};

static config &getUIConfig() {
  static config astraConfig;
  return astraConfig;
}
}
#endif //ASTRA_CORE_SRC_SYSTEM_H_