//
// Created by Fir on 2024/1/22.
//

#include <string>
#include "driver_i.h"
#include "astra_driver.h"

//ui驱动和底层驱动解耦 方便移植
namespace astra {
void ScreenIC::screenICWriteByteNoCommand(uint8_t _data) {
  HAL_SPI_Transmit_DMA(&hspi2, &_data, 1);
}

/**
 * @brief send data/command to spi bus
 *
 * @param _data
 * @param _cmd 0 -> write command | 1 -> write data
 */
void ScreenIC::screenICWriteByte(uint8_t _data, uint8_t _cmd) {
  if (_cmd == 1) HAL_GPIO_WritePin(OLED_DC_GPIO_Port, OLED_DC_Pin, GPIO_PIN_SET);
  else HAL_GPIO_WritePin(OLED_DC_GPIO_Port, OLED_DC_Pin, GPIO_PIN_RESET);
  HAL_SPI_Transmit_DMA(&hspi2, &_data, 1);
}

void ScreenIC::screenSetPosition(uint8_t _x, uint8_t _y) {
  screenICWriteByte(0xb0 + _y, 0);
  screenICWriteByte((((_x + 2) & 0xf0) >> 4) | 0x10, 0);
  screenICWriteByte(((_x + 2) & 0x0f), 0);
}

void ScreenIC::screenClear() {
  uint8_t i, n;
  for (i = 0; i < 8; i++) {
    screenICWriteByte(0xb0 + i, 0);     //设置页地址（0~7）
    screenICWriteByte(0x02, 0);         //设置显示位置—列低地址
    screenICWriteByte(0x10, 0);         //设置显示位置—列高地址
    for (n = 0; n < 128; n++) screenICWriteByte(0, 1);
  } //更新显示
}

void ScreenIC::screenOn() {
  screenICWriteByte(0X8D, 0);  //set DC-DC command
  screenICWriteByte(0X14, 0);  //DC-DC on
  screenICWriteByte(0XAF, 0);  //screen on
}

void ScreenIC::screenOff() {
  screenICWriteByte(0X8D, 0);  //set DC-DC command
  screenICWriteByte(0X10, 0);  //DC-DC off
  screenICWriteByte(0XAE, 0);  //screen off
}

void ScreenIC::screenICInit() {
  HAL_GPIO_WritePin(OLED_DC_GPIO_Port, OLED_DC_Pin, GPIO_PIN_SET);
  HAL_Delay(100);
  HAL_GPIO_WritePin(OLED_DC_GPIO_Port, OLED_DC_Pin, GPIO_PIN_RESET);
  HAL_Delay(100);
  HAL_GPIO_WritePin(OLED_DC_GPIO_Port, OLED_DC_Pin, GPIO_PIN_SET);

  screenICWriteByte(0xAE, 0);     //display off
  screenICWriteByte(0x20, 0);     //set memory addressing mode
  screenICWriteByte(0x10, 0);     //00: horizontal addressing mode
  //01: vertical addressing mode
  //10: page addressing mode (RESET,0)
  //11: invalid
  screenICWriteByte(0xb0, 0);     //set page start address for page addressing mode, 0-7
  screenICWriteByte(0xc8, 0);     //set COM output scan direction
  screenICWriteByte(0x00, 0);     //set low column address
  screenICWriteByte(0x10, 0);     //set high column address
  screenICWriteByte(0x40, 0);     //set start line address
  screenICWriteByte(0x81, 0xCF);  //set contrast control register
  screenICWriteByte(0x7f, 0);
  screenICWriteByte(0xa1, 0);     //set segment re-map 0 to 127
  screenICWriteByte(0xa6, 0);     //set normal display
  screenICWriteByte(0xa8, 0);     //set multiplex ratio(1 to 64)
  screenICWriteByte(0x3F, 0);
  screenICWriteByte(0xa4, 0);     //0xa4: output follows RAM content
  //0xa5: output ignores RAM content
  screenICWriteByte(0xd3, 0);     //set display offset
  screenICWriteByte(0x00, 0);     //not offset
  screenICWriteByte(0xd5, 0);     //set display clock divide ratio/oscillator frequency
  screenICWriteByte(0xf0, 0);     //set divide ratio
  screenICWriteByte(0xd9, 0);     //set pre-charge period
  screenICWriteByte(0x22, 0);
  screenICWriteByte(0xda, 0);     //set com pins hardware configuration
  screenICWriteByte(0x12, 0);
  screenICWriteByte(0xdb, 0);     //set v_comh
  screenICWriteByte(0x20, 0);     //0x20: 0.77xVcc
  screenICWriteByte(0x8d, 0);     //set DC-DC enable
  screenICWriteByte(0x14, 0);
  screenICWriteByte(0xaf, 0);     //turn on oled panel

  screenClear();
  screenSetPosition(0, 0);
}

void ScreenPrinter::canvasUpdate(){
  u8g2_SendBuffer(canvasBuffer);
}

void ScreenPrinter::canvasClear(){
  u8g2_ClearBuffer(canvasBuffer);
}

uint8_t ScreenPrinter::byteCallBack(u8x8_t *u8x8, uint8_t msg, uint8_t argInt, void *argPtr) {
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

uint8_t ScreenPrinter::gpioAndDelayCallBack(u8x8_t *u8x8, uint8_t msg, uint8_t argInt, void *argPtr) {
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

void ScreenPrinter::graphicsLibInit() {
  u8g2_Setup_ssd1306_128x64_noname_f(canvasBuffer, U8G2_R0, byteCallBack, gpioAndDelayCallBack);
  u8g2_InitDisplay(canvasBuffer);
  u8g2_SetPowerSave(canvasBuffer, 0);   //open screen

  u8g2_SetFontMode(canvasBuffer, 1);      //set fonts code
  u8g2_SetFontDirection(canvasBuffer, 0);           //set fonts position
  u8g2_SetFont(canvasBuffer, u8g2_font_myfont);

  canvasClear();
}

void ScreenPrinter::setDrawType(uint8_t _type) {
  u8g2_SetDrawColor(canvasBuffer, _type);
}

void ScreenPrinter::drawPixel(uint8_t _x, uint8_t _y) {
  u8g2_DrawPixel(canvasBuffer, _x, _y);
}

void ScreenPrinter::drawEnglish(uint8_t _x, uint8_t _y, const std::string &_text) {
  auto *str = _text.c_str();
  u8g2_DrawStr(canvasBuffer, _x, _y, str);
}

void ScreenPrinter::drawChinese(uint8_t _x, uint8_t _y, const std::string &_text) {
  auto *str = _text.c_str();
  u8g2_DrawUTF8(canvasBuffer, _x, _y, str);
}

void ScreenPrinter::drawVDottedLine(uint8_t _x, uint8_t _y, uint8_t _l) {
  for (int index = _x; index <= _x + _l; index += 1) {
    if (index % 8 == 0 | (index - 1) % 8 == 0 | (index - 2) % 8 == 0) continue;
    u8g2_DrawPixel(canvasBuffer, index, (int16_t) _y);  //绘制一条由像素点组成的虚线
  }
}

void ScreenPrinter::drawHDottedLine(uint8_t _x, uint8_t _y, uint8_t _h) {
  for (int index = _y; index <= _y + _h; index += 1) {
    if (index % 8 == 0 | (index - 1) % 8 == 0 | (index - 2) % 8 == 0) continue;
    u8g2_DrawPixel(canvasBuffer, (int16_t) _x, index);  //绘制一条由像素点组成的虚线
  }
}

void ScreenPrinter::drawVLine(uint8_t _x, uint8_t _y, uint8_t _l) {
  u8g2_DrawVLine(canvasBuffer, _x, _y, _l);
}

void ScreenPrinter::drawHLine(uint8_t _x, uint8_t _y, uint8_t _h) {
  u8g2_DrawHLine(canvasBuffer, _x, _y, _h);
}

void ScreenPrinter::drawBMP(uint8_t _x, uint8_t _y, uint8_t _w, uint8_t _h, const uint8_t *_bitMap) {
  u8g2_DrawXBMP(canvasBuffer, _x, _y, _w, _h, _bitMap);
}

void ScreenPrinter::drawBox(uint8_t _x, uint8_t _y, uint8_t _w, uint8_t _h) {
  u8g2_DrawBox(canvasBuffer, _x, _y, _w, _h);
}

void ScreenPrinter::drawRBox(uint8_t _x, uint8_t _y, uint8_t _w, uint8_t _h, uint8_t _r) {
  u8g2_DrawRBox(canvasBuffer, _x, _y, _w, _h, _r);
}

void ScreenPrinter::drawFrame(uint8_t _x, uint8_t _y, uint8_t _w, uint8_t _h) {
  u8g2_DrawFrame(canvasBuffer, _x, _y, _w, _h);
}

void ScreenPrinter::drawRFrame(uint8_t _x, uint8_t _y, uint8_t _w, uint8_t _h, uint8_t _r) {
  u8g2_DrawRFrame(canvasBuffer, _x, _y, _w, _h, _r);
}

ScreenPrinter::ScreenPrinter(u8g2_t *_canvasBuffer) {
  this->canvasBuffer = _canvasBuffer;
}

/**
 * @brief this function needs to run per 5ms/10ms.
 */
void KeyScanner::keyScan() {
  static uint8_t timeCnt = 0;
  static uint8_t lock = 0;
  switch (keyState) {
    //按键未按下状态，此时判断Key的值
    case KEY_CHECK:
      if (!key) {
        if (1 == key1) keyState = KEY0_CONFIRM;  //如果按键Key值为0，说明按键开始按下，进入下一个状态
        if (1 == key2) keyState = KEY1_CONFIRM;  //如果按键Key值为0，说明按键开始按下，进入下一个状态
      }
      timeCnt = 0;                  //计数复位
      lock = 0;
      break;

    case KEY0_CONFIRM:
    case KEY1_CONFIRM:
      //无论是KEY0还是KEY1 都代表有按键按下了 需要进一步处理
      if (!key) {
        //查看当前Key是否还是0，再次确认是否按下
        if (!lock) lock = 1;

        timeCnt++;

        /*按键时长判断*/
        if (timeCnt > 100) {
          // 长按 1 s
          keyActionFlag = KEY_PRESSED;
          //判断按键依然按下
          if (0 == key1) keyValue = KEY_0_PRESS;
          if (0 == key2) keyValue = KEY_1_PRESS;
          timeCnt = 0;
          lock = 0;               //重新检查
          keyState = KEY_RELEASE;    // 需要进入按键释放状态
        }
      } else {
        if (1 == lock) {
          // 不是第一次进入，  释放按键才执行
          //所以这里要判断按键被释放才行
          if (keyState == KEY0_CONFIRM) keyValue = KEY_0_CLICK;
          if (keyState == KEY1_CONFIRM) keyValue = KEY_1_CLICK;
          keyActionFlag = KEY_PRESSED;          // 短按
          keyState = KEY_RELEASE;    // 需要进入按键释放状态
        } else {
          // 当前Key值为1，确认为抖动，则返回上一个状态
          keyState = KEY_CHECK;      // 返回上一个状态
          keyValue = KEY_NULL;
        }
      }
      break;

    case KEY_RELEASE:if (key) keyState = KEY_CHECK;    //当前Key值为1，说明按键已经释放，返回开始状态
      break;

    default:break;
  }
}

void KeyScanner::keyTest() {
  switch (keyValue)
  {
    case KEY_0_CLICK: //NOLINT
      /*
        执行短按对应的事件
      */
      //HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_12);
      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
      keyActionFlag = KEY_NOT_PRESSED;    //状态回到空
      keyValue = KEY_NULL;
      break;

    case KEY_0_PRESS: //NOLINT
      /*
        执行长按对应的事件
      */
      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
      keyActionFlag = KEY_NOT_PRESSED;    //状态回到空
      keyValue = KEY_NULL;
      break;

    case KEY_1_CLICK: //NOLINT
      /*
        执行短按对应的事件
      */
      //HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_12);
      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
      keyActionFlag = KEY_NOT_PRESSED;    //状态回到空
      keyValue = KEY_NULL;
      break;

    case KEY_1_PRESS: //NOLINT
      /*
     执行长按对应的事件
     */
      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
      keyActionFlag = KEY_NOT_PRESSED;    //状态回到空
      keyValue = KEY_NULL;
      break;

    case KEY_NULL: break;
  }
}
}

