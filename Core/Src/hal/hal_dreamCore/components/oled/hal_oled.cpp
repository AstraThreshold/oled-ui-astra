//
// Created by Fir on 2024/2/11.
//
#include <cmath>
#include "../../hal_dreamCore.h"
#include "graph_lib/u8g2/u8g2.h"
#include "spi.h"
#include "main.h"

void HALDreamCore::_ssd1306_transmit_cmd(unsigned char _cmd) { //NOLINT
  unsigned char rxData = 0;
  HAL_GPIO_WritePin(OLED_CS_GPIO_Port, OLED_CS_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(OLED_DC_GPIO_Port, OLED_DC_Pin, GPIO_PIN_RESET);
  HAL_SPI_TransmitReceive(&hspi2, &_cmd, &rxData, 1, 1000);
  HAL_GPIO_WritePin(OLED_CS_GPIO_Port, OLED_CS_Pin, GPIO_PIN_SET);
}

void HALDreamCore::_ssd1306_transmit_data(unsigned char _data, unsigned char _mode) { //NOLINT
  if (!_mode) _data = ~_data;
  unsigned char rxData = 0;
  HAL_GPIO_WritePin(OLED_CS_GPIO_Port, OLED_CS_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(OLED_DC_GPIO_Port, OLED_DC_Pin, GPIO_PIN_SET);
  HAL_SPI_TransmitReceive(&hspi2, &_data, &rxData, 1, 1000);
  HAL_GPIO_WritePin(OLED_CS_GPIO_Port, OLED_CS_Pin, GPIO_PIN_SET);
}

void HALDreamCore::_ssd1306_reset(bool _state) { //NOLINT
  if (_state) HAL_GPIO_WritePin(OLED_RST_GPIO_Port, OLED_RST_Pin, GPIO_PIN_SET);
  else HAL_GPIO_WritePin(OLED_RST_GPIO_Port, OLED_RST_Pin, GPIO_PIN_RESET);
}

void HALDreamCore::_ssd1306_set_cursor(unsigned char _x, unsigned char _y) {
  _ssd1306_transmit_cmd(0xB0 | _y);
  _ssd1306_transmit_cmd(0x10 | ((_x & 0xF0) >> 4));
  _ssd1306_transmit_cmd(0x00 | (_x & 0x0F));
}

void HALDreamCore::_ssd1306_fill(unsigned char _data) {
  unsigned char i, j;
  for (j = 0; j < 8; j++) {
    _ssd1306_set_cursor(j, 0);
    for(i = 0; i < 128; i++) {
      _ssd1306_transmit_data(_data, 1);
    }
  }
}

/**
 * @brief transmit token to OLED.
 *
 * @param _data data to transmit.
 * @param _cmd command, if 1, transmit command, else transmit data.
 */

void HALDreamCore::_screenOn() {
  _ssd1306_transmit_cmd(0X8D);  //set dc-dc command.
  _ssd1306_transmit_cmd(0X14);  //dc-dc enable.
  _ssd1306_transmit_cmd(0XAF);  //display on.
}

void HALDreamCore::_screenOff() {
  _ssd1306_transmit_cmd(0X8D);  //set dc-dc command.
  _ssd1306_transmit_cmd(0X10);  //dc-dc disable.
  _ssd1306_transmit_cmd(0XAE);  //display off.
}

void HALDreamCore::_ssd1306_init() {
  _ssd1306_fill(0x00);

  uint32_t i, j;

  for (i = 0; i < 1000; i++) {
    for (j = 0; j < 1000; j++);
  }

  _ssd1306_transmit_cmd(0xAE);
  _ssd1306_transmit_cmd(0xD5);
  _ssd1306_transmit_cmd(0x80);
  _ssd1306_transmit_cmd(0xA8);
  _ssd1306_transmit_cmd(0x3F);
  _ssd1306_transmit_cmd(0xD3);
  _ssd1306_transmit_cmd(0x00);
  _ssd1306_transmit_cmd(0x40);
  _ssd1306_transmit_cmd(0xA1);
  _ssd1306_transmit_cmd(0xC8);
  _ssd1306_transmit_cmd(0xDA);
  _ssd1306_transmit_cmd(0x12);
  _ssd1306_transmit_cmd(0x81);
  _ssd1306_transmit_cmd(0xCF);
  _ssd1306_transmit_cmd(0xD9);
  _ssd1306_transmit_cmd(0xF1);
  _ssd1306_transmit_cmd(0xDB);
  _ssd1306_transmit_cmd(0x30);
  _ssd1306_transmit_cmd(0xA4);
  _ssd1306_transmit_cmd(0xA6);
  _ssd1306_transmit_cmd(0x8D);
  _ssd1306_transmit_cmd(0x14);
  _ssd1306_transmit_cmd(0xAF);

  //_ssd1306_fill(0x00);
}

unsigned char HALDreamCore::_u8x8_byte_hw_spi_callback(u8x8_t *_u8x8, unsigned char _msg, unsigned char _argInt, void *_argPtr) { //NOLINT
  switch (_msg) {
    case U8X8_MSG_BYTE_SEND: /*通过SPI发送arg_int个字节数据*/
      HAL_SPI_Transmit_DMA(&hspi2, (unsigned char *) _argPtr, _argInt);
      while (hspi2.TxXferCount);//DMA
      break;
    case U8X8_MSG_BYTE_INIT: /*初始化函数*/
      break;
    case U8X8_MSG_BYTE_SET_DC: /*设置DC引脚,表明发送的是数据还是命令*/
      HAL_GPIO_WritePin(OLED_DC_GPIO_Port, OLED_DC_Pin, static_cast<GPIO_PinState>(_argInt));
      break;
    case U8X8_MSG_BYTE_START_TRANSFER:
      u8x8_gpio_SetCS(_u8x8, _u8x8->display_info->chip_enable_level);
      _u8x8->gpio_and_delay_cb(_u8x8, U8X8_MSG_DELAY_NANO, _u8x8->display_info->post_chip_enable_wait_ns, nullptr);
      break;
    case U8X8_MSG_BYTE_END_TRANSFER:
      _u8x8->gpio_and_delay_cb(_u8x8,
                               U8X8_MSG_DELAY_NANO,
                               _u8x8->display_info->pre_chip_disable_wait_ns,
                               nullptr);
      u8x8_gpio_SetCS(_u8x8, _u8x8->display_info->chip_disable_level);
      break;
    default:return 0;
  }
  return 1;
}

unsigned char HALDreamCore::_u8x8_gpio_and_delay_callback(__attribute__((unused)) u8x8_t *_u8x8,
                                                    __attribute__((unused)) unsigned char _msg,
                                                    __attribute__((unused)) unsigned char _argInt,
                                                    __attribute__((unused)) void *_argPtr) { //NOLINT
  switch (_msg) {
    case U8X8_MSG_GPIO_AND_DELAY_INIT: /*delay和GPIO的初始化，在main中已经初始化完成了*/
      break;
    case U8X8_MSG_DELAY_MILLI: /*延时函数*/
      HAL_Delay(_argInt);
      break;
    case U8X8_MSG_GPIO_CS: /*片选信号*/
      HAL_GPIO_WritePin(OLED_CS_GPIO_Port, OLED_CS_Pin, static_cast<GPIO_PinState>(_argInt));
      break;
    case U8X8_MSG_GPIO_DC:
    case U8X8_MSG_GPIO_RESET:
    default: break;
  }
  return 1;
}

void HALDreamCore::_u8g2_init() {
  u8g2_Setup_ssd1306_128x64_noname_f(&canvasBuffer,
                                     U8G2_R0,
                                     _u8x8_byte_hw_spi_callback,
                                     _u8x8_gpio_and_delay_callback);  // 初始化 u8g2 结构体
  u8g2_InitDisplay(&canvasBuffer); // 根据所选的芯片进行初始化工作，初始化完成后，显示器处于关闭状态
  u8g2_SetPowerSave(&canvasBuffer, 0); // 打开显示器
  u8g2_ClearBuffer(&canvasBuffer);

  //delay(100);

  u8g2_SetFontMode(&canvasBuffer, 1); /*字体模式选择*/
  u8g2_SetFontDirection(&canvasBuffer, 0); /*字体方向选择*/
  u8g2_SetFont(&canvasBuffer, u8g2_font_myfont); /*字库选择*/
}

void *HALDreamCore::_getCanvasBuffer() {
  return u8g2_GetBufferPtr(&canvasBuffer);
}

unsigned char HALDreamCore::_getBufferTileHeight() {
  return u8g2_GetBufferTileHeight(&canvasBuffer);
}

unsigned char HALDreamCore::_getBufferTileWidth() {
  return u8g2_GetBufferTileWidth(&canvasBuffer);
}

void HALDreamCore::_canvasUpdate() {
  u8g2_SendBuffer(&canvasBuffer);
}

void HALDreamCore::_canvasClear() {
  u8g2_ClearBuffer(&canvasBuffer);
}

void HALDreamCore::_setFont(const unsigned char *_font) {
  u8g2_SetFontMode(&canvasBuffer, 1); /*字体模式选择*/
  u8g2_SetFontDirection(&canvasBuffer, 0); /*字体方向选择*/
  u8g2_SetFont(&canvasBuffer, _font);
}

unsigned char HALDreamCore::_getFontWidth(std::string &_text) {
  return u8g2_GetUTF8Width(&canvasBuffer, _text.c_str());
}

unsigned char HALDreamCore::_getFontHeight() {
  return u8g2_GetMaxCharHeight(&canvasBuffer);
}

void HALDreamCore::_setDrawType(unsigned char _type) {
  u8g2_SetDrawColor(&canvasBuffer, _type);
}

void HALDreamCore::_drawPixel(float _x, float _y) {
  u8g2_DrawPixel(&canvasBuffer, (int16_t)std::round(_x), (int16_t)std::round(_y));
}

void HALDreamCore::_drawEnglish(float _x, float _y, const std::string &_text) {
  u8g2_DrawStr(&canvasBuffer, (int16_t)std::round(_x), (int16_t)std::round(_y), _text.c_str());
}

void HALDreamCore::_drawChinese(float _x, float _y, const std::string &_text) {
  u8g2_DrawUTF8(&canvasBuffer, (int16_t)std::round(_x), (int16_t)std::round(_y), _text.c_str());
}

void HALDreamCore::_drawVDottedLine(float _x, float _y, float _h) {
  for (unsigned char i = 0; i < (unsigned char)std::round(_h); i++) {
    if (i % 8 == 0 | (i - 1) % 8 == 0 | (i - 2) % 8 == 0) continue;
    u8g2_DrawPixel(&canvasBuffer, (int16_t)std::round(_x), (int16_t)std::round(_y) + i);
  }
}

void HALDreamCore::_drawHDottedLine(float _x, float _y, float _l) {
  for (unsigned char i = 0; i < _l; i++) {
    if (i % 8 == 0 | (i - 1) % 8 == 0 | (i - 2) % 8 == 0) continue;
    u8g2_DrawPixel(&canvasBuffer, (int16_t)std::round(_x) + i, (int16_t)std::round(_y));
  }
}

void HALDreamCore::_drawVLine(float _x, float _y, float _h) {
  u8g2_DrawVLine(&canvasBuffer, (int16_t)std::round(_x), (int16_t)std::round(_y), (int16_t)std::round(_h));
}

void HALDreamCore::_drawHLine(float _x, float _y, float _l) {
  u8g2_DrawHLine(&canvasBuffer, (int16_t)std::round(_x), (int16_t)std::round(_y), (int16_t)std::round(_l));
}

void HALDreamCore::_drawBMP(float _x, float _y, float _w, float _h, const unsigned char *_bitMap) {
  u8g2_DrawXBMP(&canvasBuffer, (int16_t)std::round(_x), (int16_t)std::round(_y), (int16_t)std::round(_w), (int16_t)std::round(_h), _bitMap);
}

void HALDreamCore::_drawBox(float _x, float _y, float _w, float _h) {
  u8g2_DrawBox(&canvasBuffer, (int16_t)std::round(_x), (int16_t)std::round(_y), (int16_t)std::round(_w), (int16_t)std::round(_h));
}

void HALDreamCore::_drawRBox(float _x, float _y, float _w, float _h, float _r) {
  u8g2_DrawRBox(&canvasBuffer, (int16_t)std::round(_x), (int16_t)std::round(_y), (int16_t)std::round(_w), (int16_t)std::round(_h), (int16_t)std::round(_r));
}

void HALDreamCore::_drawFrame(float _x, float _y, float _w, float _h) {
  u8g2_DrawFrame(&canvasBuffer, (int16_t)std::round(_x), (int16_t)std::round(_y), (int16_t)std::round(_w), (int16_t)std::round(_h));
}

void HALDreamCore::_drawRFrame(float _x, float _y, float _w, float _h, float _r) {
  u8g2_DrawRFrame(&canvasBuffer, (int16_t)std::round(_x), (int16_t)std::round(_y), (int16_t)std::round(_w), (int16_t)std::round(_h), (int16_t)std::round(_r));
}