//
// Created by Fir on 2024/2/2.
//

#include "graph_lib.h"
#include "spi.h"

namespace graphLib {


void GraphicsLib::canvasUpdate(){
  u8g2_SendBuffer(canvasBuffer);
}

void GraphicsLib::canvasClear(){
  u8g2_ClearBuffer(canvasBuffer);
}

uint8_t GraphicsLib::byteCallBack(u8x8_t *u8x8, uint8_t msg, uint8_t argInt, void *argPtr) {
  switch (msg) {
    case U8X8_MSG_BYTE_SEND: /*通过SPI发送argInt个字节数据*/
      HAL_SPI_Transmit_DMA(&hspi2, (uint8_t *) argPtr, argInt);
      while (hspi2.TxXferCount);//DMA
      break;
    case U8X8_MSG_BYTE_INIT: /*初始化函数*/
      break;
    case U8X8_MSG_BYTE_SET_DC: /*设置DC引脚,表明发送的是数据还是命令*/
      HAL_GPIO_WritePin(OLED_DC_GPIO_Port, OLED_DC_Pin, argInt);
      break;
    case U8X8_MSG_BYTE_START_TRANSFER:u8x8_gpio_SetCS(u8x8, u8x8->display_info->chip_enable_level);
      u8x8->gpio_and_delay_cb(u8x8, U8X8_MSG_DELAY_NANO, u8x8->display_info->post_chip_enable_wait_ns, nullptr);
      break;
    case U8X8_MSG_BYTE_END_TRANSFER:
      u8x8->gpio_and_delay_cb(u8x8,
                              U8X8_MSG_DELAY_NANO,
                              u8x8->display_info->pre_chip_disable_wait_ns,
                              nullptr);
      u8x8_gpio_SetCS(u8x8, u8x8->display_info->chip_disable_level);
      break;
    default:return 0;
  }
  return 1;
}

uint8_t GraphicsLib::gpioAndDelayCallBack(u8x8_t *u8x8, uint8_t msg, uint8_t argInt, void *argPtr) {
  switch (msg) {
    case U8X8_MSG_GPIO_AND_DELAY_INIT: /*delay和GPIO的初始化，在main中已经初始化完成了*/
      break;
    case U8X8_MSG_DELAY_MILLI: /*延时函数*/
      HAL_Delay(argInt);
      break;
    case U8X8_MSG_GPIO_CS: /*片选信号*/
      HAL_GPIO_WritePin(OLED_CS_GPIO_Port, OLED_CS_Pin, argInt);
      break;
    case U8X8_MSG_GPIO_DC:
    case U8X8_MSG_GPIO_RESET:
    default: break;
  }
  return 1;
}

void GraphicsLib::graphicsLibInit() {
  u8g2_Setup_ssd1306_128x64_noname_f(canvasBuffer, U8G2_R0, byteCallBack, gpioAndDelayCallBack);
  u8g2_InitDisplay(canvasBuffer);
  u8g2_SetPowerSave(canvasBuffer, 0);   //open screen

  u8g2_SetFontMode(canvasBuffer, 1);      //set fonts code
  u8g2_SetFontDirection(canvasBuffer, 0);           //set fonts position
  u8g2_SetFont(canvasBuffer, u8g2_font_myfont);

  canvasClear();
}

void GraphicsLib::getFontWidth(std::string text) {
  auto *str = text.c_str();
  u8g2_GetUTF8Width(canvasBuffer, str);
}

void GraphicsLib::setDrawType(uint8_t _type) {
  u8g2_SetDrawColor(canvasBuffer, _type);
}

void GraphicsLib::drawPixel(uint8_t _x, uint8_t _y) {
  u8g2_DrawPixel(canvasBuffer, _x, _y);
}

void GraphicsLib::drawEnglish(uint8_t _x, uint8_t _y, const std::string &_text) {
  auto *str = _text.c_str();
  u8g2_DrawStr(canvasBuffer, _x, _y, str);
}

void GraphicsLib::drawChinese(uint8_t _x, uint8_t _y, const std::string &_text) {
  auto *str = _text.c_str();
  u8g2_DrawUTF8(canvasBuffer, _x, _y, str);
}

void GraphicsLib::drawVDottedLine(uint8_t _x, uint8_t _y, uint8_t _l) {
  for (int index = _x; index <= _x + _l; index += 1) {
    if (index % 8 == 0 | (index - 1) % 8 == 0 | (index - 2) % 8 == 0) continue;
    u8g2_DrawPixel(canvasBuffer, index, (int16_t) _y);  //绘制一条由像素点组成的虚线
  }
}

void GraphicsLib::drawHDottedLine(uint8_t _x, uint8_t _y, uint8_t _h) {
  for (int index = _y; index <= _y + _h; index += 1) {
    if (index % 8 == 0 | (index - 1) % 8 == 0 | (index - 2) % 8 == 0) continue;
    u8g2_DrawPixel(canvasBuffer, (int16_t) _x, index);  //绘制一条由像素点组成的虚线
  }
}

void GraphicsLib::drawVLine(uint8_t _x, uint8_t _y, uint8_t _l) {
  u8g2_DrawVLine(canvasBuffer, _x, _y, _l);
}

void GraphicsLib::drawHLine(uint8_t _x, uint8_t _y, uint8_t _h) {
  u8g2_DrawHLine(canvasBuffer, _x, _y, _h);
}

void GraphicsLib::drawBMP(uint8_t _x, uint8_t _y, uint8_t _w, uint8_t _h, const uint8_t *_bitMap) {
  u8g2_DrawXBMP(canvasBuffer, _x, _y, _w, _h, _bitMap);
}

void GraphicsLib::drawBox(uint8_t _x, uint8_t _y, uint8_t _w, uint8_t _h) {
  u8g2_DrawBox(canvasBuffer, _x, _y, _w, _h);
}

void GraphicsLib::drawRBox(uint8_t _x, uint8_t _y, uint8_t _w, uint8_t _h, uint8_t _r) {
  u8g2_DrawRBox(canvasBuffer, _x, _y, _w, _h, _r);
}

void GraphicsLib::drawFrame(uint8_t _x, uint8_t _y, uint8_t _w, uint8_t _h) {
  u8g2_DrawFrame(canvasBuffer, _x, _y, _w, _h);
}

void GraphicsLib::drawRFrame(uint8_t _x, uint8_t _y, uint8_t _w, uint8_t _h, uint8_t _r) {
  u8g2_DrawRFrame(canvasBuffer, _x, _y, _w, _h, _r);
}

GraphicsLib::GraphicsLib(u8g2_t *_canvasBuffer) {
  this->canvasBuffer = _canvasBuffer;
}

}