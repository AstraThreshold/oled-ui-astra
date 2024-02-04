//
// Created by Fir on 2024/2/2.
//

#include "oled.h"
#include "spi.h"

namespace hardware {
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
}