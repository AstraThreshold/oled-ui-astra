//
// Created by Fir on 2024/2/2.
//

#include "key.h"

namespace hardware {

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
