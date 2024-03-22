//
// Created by Fir on 2024/2/12.
//
#include "../hal_dreamCore.h"
#include "main.h"
#include "dma.h"
#include "spi.h"
#include "gpio.h"
#include "adc.h"

void HALDreamCore::_stm32_hal_init() { //NOLINT
  HAL_Init();
}

void HALDreamCore::_sys_clock_init() { //NOLINT
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                                |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
    Error_Handler();
  }
}

void HALDreamCore::_gpio_init() { //NOLINT
  MX_GPIO_Init();
}

void HALDreamCore::_timer_init() { //NOLINT

}

void HALDreamCore::_spi_init() { //NOLINT
  MX_SPI2_Init();
}

void HALDreamCore::_dma_init() { //NOLINT
  MX_DMA_Init();
}

void HALDreamCore::_adc_init() { //NOLINT
  MX_ADC1_Init();
}

void HALDreamCore::_delay(unsigned long _mill) {
  HAL_Delay(_mill);
}

unsigned long HALDreamCore::_millis() {
  return HAL_GetTick();
}

unsigned long HALDreamCore::_getTick() {
  return (uwTick * 1000 + (SysTick->LOAD - SysTick->VAL) / (SystemCoreClock/1000000U));
}

unsigned long HALDreamCore::_getRandomSeed() {
  static uint32_t seed = 0;
  HAL_ADC_Start(&hadc1);//开启ADC1
  HAL_ADC_PollForConversion(&hadc1, 50);//表示等待转换完成
  if(HAL_IS_BIT_SET(HAL_ADC_GetState(&hadc1), HAL_ADC_STATE_REG_EOC)) {
    seed = HAL_ADC_GetValue(&hadc1);//读取ADC转换数据
  }

  return seed;
}



