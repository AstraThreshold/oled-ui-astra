//
// Created by Fir on 2024/2/11.
//
#include "../../hal_dreamCore.h"
#include "graph_lib/u8g2/u8g2.h"
#include "spi.h"
#include "main.h"

void HALDreamCore::_ssd1306_reset(bool _state) { //NOLINT
  if (_state) HAL_GPIO_WritePin(OLED_RST_GPIO_Port, OLED_RST_Pin, 1);
  else HAL_GPIO_WritePin(OLED_RST_GPIO_Port, OLED_RST_Pin, 0);
}

/**
 * @brief transmit token to OLED.
 *
 * @param _data data to transmit.
 * @param _cmd command, if 1, transmit command, else transmit data.
 */
void HALDreamCore::_ssd1306_transmit(uint8_t _data, bool _isCmd) { //NOLINT
  if (_isCmd) HAL_GPIO_WritePin(OLED_DC_GPIO_Port, OLED_DC_Pin, 1);
  else HAL_GPIO_WritePin(OLED_DC_GPIO_Port, OLED_DC_Pin, 0);

  HAL_SPI_Transmit_DMA(&hspi2, &_data, 1);
}

void HALDreamCore::_screenOn() {
  _ssd1306_transmit(0X8D, true);  //set dc-dc command.
  _ssd1306_transmit(0X14, true);  //dc-dc enable.
  _ssd1306_transmit(0XAF, true);  //display on.
}

void HALDreamCore::_screenOff() {
  _ssd1306_transmit(0X8D, true);  //set dc-dc command.
  _ssd1306_transmit(0X10, true);  //dc-dc disable.
  _ssd1306_transmit(0XAE, true);  //display off.
}

void HALDreamCore::_ssd1306_init() {
  _ssd1306_reset(true);
  HAL_Delay(100);
  _ssd1306_reset(false);
  HAL_Delay(100);
  _ssd1306_reset(true);

  _ssd1306_transmit(0xAE, true);   //display off
  _ssd1306_transmit(0x20, true);   //Set Memory Addressing Mode
  _ssd1306_transmit(0x10,
                    true);   //00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET,0);11,Invalid
  _ssd1306_transmit(0xb0, true);   //Set Page Start Address for Page Addressing Mode,0-7
  _ssd1306_transmit(0xc8, true);   //Set COM Output Scan Direction
  _ssd1306_transmit(0x00, true);   //---set low column address
  _ssd1306_transmit(0x10, true);   //---set high column address
  _ssd1306_transmit(0x40, true);   //--set start line address
  _ssd1306_transmit(0x81, true);   //--set contrast control register调整亮度 初始为最高亮度
  _ssd1306_transmit(0x7f, true);
  _ssd1306_transmit(0xa1, true);   //--set segment re-map 0 to 127
  _ssd1306_transmit(0xa6, true);   //--set normal display
  _ssd1306_transmit(0xa8, true);   //--set multiplex ratio(1 to 64)
  _ssd1306_transmit(0x3F, true);   //
  _ssd1306_transmit(0xa4, true);   //0xa4,Output follows RAM content;0xa5,Output ignores RAM content
  _ssd1306_transmit(0xd3, true);   //-set display offset
  _ssd1306_transmit(0x00, true);   //-not offset
  _ssd1306_transmit(0xd5, true);   //--set display clock divide ratio/oscillator frequency
  _ssd1306_transmit(0xf0, true);   //--set divide ratio
  _ssd1306_transmit(0xd9, true);   //--set pre-charge period
  _ssd1306_transmit(0x22, true);   //
  _ssd1306_transmit(0xda, true);   //--set com pins hardware configuration
  _ssd1306_transmit(0x12, true);
  _ssd1306_transmit(0xdb, true);   //--set v_comh
  _ssd1306_transmit(0x20, true);   //0x20,0.77xVcc
  _ssd1306_transmit(0x8d, true);   //--set DC-DC enable
  _ssd1306_transmit(0x14, true);   //
  _ssd1306_transmit(0xaf, true);   //--turn on oled panel
  _ssd1306_transmit(0xAF, true);    /*display ON*/

  uint8_t i, n;
  for (i = 0; i < 8; i++) {
    _ssd1306_transmit(0xb0 + i, true);     //设置页地址（0~7）
    _ssd1306_transmit(0x02, true);         //设置显示位置—列低地址
    _ssd1306_transmit(0x10, true);         //设置显示位置—列高地址
    for (n = 0; n < 128; n++) _ssd1306_transmit(0, false);
  } //更新显示

  /*set oled position*/
  _ssd1306_transmit(0xb0, true);
  _ssd1306_transmit(((2 & 0xf0) >> 4) | 0x10, true);
  _ssd1306_transmit((2 & 0x0f), true);
}

uint8_t HALDreamCore::_u8x8_byte_hw_spi_callback(u8x8_t *_u8x8, uint8_t _msg, uint8_t _argInt, void *_argPtr) { //NOLINT
  switch (_msg) {
    case U8X8_MSG_BYTE_SEND: /*通过SPI发送arg_int个字节数据*/
      HAL_SPI_Transmit_DMA(&hspi2, (uint8_t *) _argPtr, _argInt);
      while (hspi2.TxXferCount);//DMA
      break;
    case U8X8_MSG_BYTE_INIT: /*初始化函数*/
      break;
    case U8X8_MSG_BYTE_SET_DC: /*设置DC引脚,表明发送的是数据还是命令*/
      HAL_GPIO_WritePin(OLED_DC_GPIO_Port, OLED_DC_Pin, _argInt);
      break;
    case U8X8_MSG_BYTE_START_TRANSFER:u8x8_gpio_SetCS(_u8x8, _u8x8->display_info->chip_enable_level);
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

uint8_t HALDreamCore::_u8x8_gpio_and_delay_callback([[maybe_unused]]u8x8_t *_u8x8,
                                                    uint8_t _msg,
                                                    uint8_t _argInt,
                                                    [[maybe_unused]]void *_argPtr) { //NOLINT
  switch (_msg) {
    case U8X8_MSG_GPIO_AND_DELAY_INIT: /*delay和GPIO的初始化，在main中已经初始化完成了*/
      break;
    case U8X8_MSG_DELAY_MILLI: /*延时函数*/
      HAL_Delay(_argInt);
      break;
    case U8X8_MSG_GPIO_CS: /*片选信号*/
      HAL_GPIO_WritePin(OLED_CS_GPIO_Port, OLED_CS_Pin, _argInt);
      break;
    case U8X8_MSG_GPIO_DC:
    case U8X8_MSG_GPIO_RESET:
    default: break;
  }
  return 1;
}

void HALDreamCore::_u8g2_init() {
  u8g2_t u8g2Buffer;
  canvasBuffer = u8g2Buffer;
  u8g2_Setup_ssd1306_128x64_noname_f(&canvasBuffer,
                                     U8G2_R0,
                                     _u8x8_byte_hw_spi_callback,
                                     _u8x8_gpio_and_delay_callback);  // 初始化 u8g2 结构体
  u8g2_InitDisplay(&canvasBuffer); // 根据所选的芯片进行初始化工作，初始化完成后，显示器处于关闭状态
  u8g2_SetPowerSave(&canvasBuffer, 0); // 打开显示器

  u8g2_SetFontMode(&canvasBuffer, 1); /*字体模式选择*/
  u8g2_SetFontDirection(&canvasBuffer, 0); /*字体方向选择*/
  u8g2_SetFont(&canvasBuffer, u8g2_font_myfont); /*字库选择*/

  u8g2_ClearBuffer(&canvasBuffer);
}

void *HALDreamCore::_getCanvasBuffer() {
  return u8g2_GetBufferPtr(&canvasBuffer);
}

uint8_t HALDreamCore::_getBufferTileHeight() {
  return u8g2_GetBufferTileHeight(&canvasBuffer);
}

uint8_t HALDreamCore::_getBufferTileWidth() {
  return u8g2_GetBufferTileWidth(&canvasBuffer);
}

void HALDreamCore::_canvasUpdate() {
  u8g2_SendBuffer(&canvasBuffer);
}

void HALDreamCore::_canvasClear() {
  u8g2_ClearBuffer(&canvasBuffer);
}

void HALDreamCore::_setFont(const uint8_t *_font) {
  u8g2_SetFont(&canvasBuffer, _font);
}

uint8_t HALDreamCore::_getFontWidth(std::string &_text) {
  return u8g2_GetStrWidth(&canvasBuffer, _text.c_str());
}

uint8_t HALDreamCore::_getFontHeight() {
  return u8g2_GetMaxCharHeight(&canvasBuffer);
}

void HALDreamCore::_setDrawType(uint8_t _type) {
  u8g2_SetDrawColor(&canvasBuffer, _type);
}

void HALDreamCore::_drawPixel(uint8_t _x, uint8_t _y) {
  u8g2_DrawPixel(&canvasBuffer, _x, _y);
}

void HALDreamCore::_drawEnglish(uint8_t _x, uint8_t _y, const std::string &_text) {
  u8g2_DrawStr(&canvasBuffer, _x, _y, _text.c_str());
}

void HALDreamCore::_drawChinese(uint8_t _x, uint8_t _y, const std::string &_text) {
  u8g2_DrawUTF8(&canvasBuffer, _x, _y, _text.c_str());
}

void HALDreamCore::_drawVDottedLine(uint8_t _x, uint8_t _y, uint8_t _h) {
  for (uint8_t i = 0; i < _h; i++) {
    if (i % 8 == 0 | (i - 1) % 8 == 0 | (i - 2) % 8 == 0) continue;
    u8g2_DrawPixel(&canvasBuffer, _x, _y + i);
  }
}

void HALDreamCore::_drawHDottedLine(uint8_t _x, uint8_t _y, uint8_t _l) {
  for (uint8_t i = 0; i < _l; i++) {
    if (i % 8 == 0 | (i - 1) % 8 == 0 | (i - 2) % 8 == 0) continue;
    u8g2_DrawPixel(&canvasBuffer, _x + i, _y);
  }
}

void HALDreamCore::_drawVLine(uint8_t _x, uint8_t _y, uint8_t _h) {
  u8g2_DrawVLine(&canvasBuffer, _x, _y, _h);
}

void HALDreamCore::_drawHLine(uint8_t _x, uint8_t _y, uint8_t _l) {
  u8g2_DrawHLine(&canvasBuffer, _x, _y, _l);
}

void HALDreamCore::_drawBMP(uint8_t _x, uint8_t _y, uint8_t _w, uint8_t _h, const uint8_t *_bitMap) {
  u8g2_DrawXBMP(&canvasBuffer, _x, _y, _w, _h, _bitMap);
}

void HALDreamCore::_drawBox(uint8_t _x, uint8_t _y, uint8_t _w, uint8_t _h) {
  u8g2_DrawBox(&canvasBuffer, _x, _y, _w, _h);
}

void HALDreamCore::_drawRBox(uint8_t _x, uint8_t _y, uint8_t _w, uint8_t _h, uint8_t _r) {
  u8g2_DrawRBox(&canvasBuffer, _x, _y, _w, _h, _r);
}

void HALDreamCore::_drawFrame(uint8_t _x, uint8_t _y, uint8_t _w, uint8_t _h) {
  u8g2_DrawFrame(&canvasBuffer, _x, _y, _w, _h);
}

void HALDreamCore::_drawRFrame(uint8_t _x, uint8_t _y, uint8_t _w, uint8_t _h, uint8_t _r) {
  u8g2_DrawRFrame(&canvasBuffer, _x, _y, _w, _h, _r);
}