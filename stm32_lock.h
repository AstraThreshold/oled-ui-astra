/**
  ******************************************************************************
  * @file      stm32_lock.h
  * @author    STMicroelectronics
  * @brief     STMicroelectronics lock mechanisms
  *
  * @details
  * This implementation supports the following strategies for handling
  * thread-safe locks. The strategy can be explicitly selected by
  * defining <tt>\STM32_THREAD_SAFE_STRATEGY = \<number></tt> in the project.
  * Please look at the '<toolchain/library>_lock_glue.c' file for more details.
  *
  * 1. User defined thread-safe implementation.
  *    User defined solution for handling thread-safety.
  *    <br>
  *    <b>NOTE:</b> The stubs in stm32_lock_user.h needs to be implemented to gain
  *    thread-safety.
  *
  * 2. [<b>DEFAULT</b>] Allow lock usage from interrupts.
  *    This implementation will ensure thread-safety by disabling all interrupts
  *    during e.g. calls to malloc.
  *    <br>
  *    <b>NOTE:</b> Disabling all interrupts creates interrupt latency which
  *    might not be desired for this application!
  *
  * 3. Deny lock usage from interrupts.
  *    This implementation assumes single thread of execution.
  *    <br>
  *    <b>NOTE:</b> Thread-safety dependent functions will enter an infinity loop
  *    if used in interrupt context.
  *
  * 4. Allow lock usage from interrupts. Implemented using FreeRTOS locks.
  *    This implementation will ensure thread-safety by entering RTOS ISR capable
  *    critical sections during e.g. calls to malloc.
  *    By default this implementation supports 2 levels of recursive locking.
  *    Adding additional levels requires 4 bytes per lock per level of RAM.
  *    <br>
  *    <b>NOTE:</b> Interrupts with high priority are not disabled. This implies
  *    that the lock is not thread-safe from high priority interrupts!
  *
  * 5. Deny lock usage from interrupts. Implemented using FreeRTOS locks.
  *    This implementation will ensure thread-safety by suspending all tasks
  *    during e.g. calls to malloc.
  *    <br>
  *    <b>NOTE:</b> Thread-safety dependent functions will enter an infinity loop
  *    if used in interrupt context.
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
 */

#ifndef __STM32_LOCK_H__
#define __STM32_LOCK_H__

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stddef.h>
#include <cmsis_compiler.h>

#ifndef STM32_THREAD_SAFE_STRATEGY
#define STM32_THREAD_SAFE_STRATEGY 2 /**< Assume strategy 2 if not specified */
#endif /* STM32_THREAD_SAFE_STRATEGY */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Function prototypes -------------------------------------------------------*/
void Error_Handler(void);

/* Public macros -------------------------------------------------------------*/
/** Blocks execution */
#define STM32_LOCK_BLOCK()                      \
  do                                            \
  {                                             \
    __disable_irq();                            \
    Error_Handler();                            \
    while (1);                                  \
  } while (0)

/** Blocks execution if argument is NULL */
#define STM32_LOCK_BLOCK_IF_NULL_ARGUMENT(x)    \
  do                                            \
  {                                             \
    if ((x) == NULL)                            \
    {                                           \
      STM32_LOCK_BLOCK();                       \
    }                                           \
  } while (0)

/** Blocks execution if in interrupt context */
#define STM32_LOCK_BLOCK_IF_INTERRUPT_CONTEXT() \
  do                                            \
  {                                             \
    if (__get_IPSR())                           \
    {                                           \
      STM32_LOCK_BLOCK();                       \
    }                                           \
  } while (0)

/** Hide unused parameter warning from compiler */
#define STM32_LOCK_UNUSED(var) (void)var

/** Size of array */
#define STM32_LOCK_ARRAY_SIZE(array) (sizeof(array) / sizeof((array)[0]))

#if STM32_THREAD_SAFE_STRATEGY == 1
/*
 * User defined thread-safe implementation.
 */

/* Includes ----------------------------------------------------------------*/
/** STM32 lock API version */
#define STM32_LOCK_API 1
#include "stm32_lock_user.h"
#undef STM32_LOCK_API

#elif STM32_THREAD_SAFE_STRATEGY == 2
/*
 * Allow lock usage from interrupts.
 */

/* Private defines ---------------------------------------------------------*/
/** Initialize members in instance of <code>LockingData_t</code> structure */
#define LOCKING_DATA_INIT { 0, 0 }

/* Private typedef ---------------------------------------------------------*/
typedef struct
{
  uint8_t flag; /**< Backup of PRIMASK.PM at nesting level 0 */
  uint8_t counter; /**< Nesting level */
} LockingData_t;

/* Private functions -------------------------------------------------------*/

/**
  * @brief Initialize STM32 lock
  * @param lock The lock to init
  */
static inline void stm32_lock_init(LockingData_t *lock)
{
  STM32_LOCK_BLOCK_IF_NULL_ARGUMENT(lock);
  lock->flag = 0;
  lock->counter = 0;
}

/**
  * @brief Acquire STM32 lock
  * @param lock The lock to acquire
  */
static inline void stm32_lock_acquire(LockingData_t *lock)
{
  uint8_t flag = (uint8_t)(__get_PRIMASK() & 0x1); /* PRIMASK.PM */
  __disable_irq();
  __DSB();
  __ISB();
  STM32_LOCK_BLOCK_IF_NULL_ARGUMENT(lock);
  if (lock->counter == 0)
  {
    lock->flag = flag;
  }
  else if (lock->counter == UINT8_MAX)
  {
    STM32_LOCK_BLOCK();
  }
  lock->counter++;
}

/**
  * @brief Release STM32 lock
  * @param lock The lock to release
  */
static inline void stm32_lock_release(LockingData_t *lock)
{
  STM32_LOCK_BLOCK_IF_NULL_ARGUMENT(lock);
  if (lock->counter == 0)
  {
    STM32_LOCK_BLOCK();
  }
  lock->counter--;
  if (lock->counter == 0 && lock->flag == 0)
  {
    __enable_irq();
  }
}

#elif STM32_THREAD_SAFE_STRATEGY == 3
/*
 * Deny lock usage from interrupts.
 */

/* Private defines ---------------------------------------------------------*/
/** Initialize members in instance of <code>LockingData_t</code> structure */
#define LOCKING_DATA_INIT 0

/* Private typedef ---------------------------------------------------------*/
typedef uint8_t LockingData_t;  /**< Unused */

/* Private functions -------------------------------------------------------*/

/**
  * @brief Initialize STM32 lock
  * @param lock The lock to init
  */
static inline void stm32_lock_init(LockingData_t *lock)
{
  STM32_LOCK_BLOCK_IF_NULL_ARGUMENT(lock);
}

/**
  * @brief Acquire STM32 lock
  * @param lock The lock to acquire
  */
static inline void stm32_lock_acquire(LockingData_t *lock)
{
  STM32_LOCK_BLOCK_IF_NULL_ARGUMENT(lock);
  STM32_LOCK_BLOCK_IF_INTERRUPT_CONTEXT();
}

/**
  * @brief Release ST lock
  * @param lock The lock to release
  */
static inline void stm32_lock_release(LockingData_t *lock)
{
  STM32_LOCK_BLOCK_IF_NULL_ARGUMENT(lock);
  STM32_LOCK_BLOCK_IF_INTERRUPT_CONTEXT();
}

#elif STM32_THREAD_SAFE_STRATEGY == 4
/*
 * Allow lock usage from interrupts. Implemented using FreeRTOS locks.
 */

/* Includes ----------------------------------------------------------------*/
#include <FreeRTOS.h>
#include <task.h>

#if defined (__GNUC__) && !defined (__CC_ARM) && configUSE_NEWLIB_REENTRANT == 0
#warning Please set configUSE_NEWLIB_REENTRANT to 1 in FreeRTOSConfig.h, otherwise newlib will not be thread-safe
#endif /* defined (__GNUC__) && !defined (__CC_ARM) && configUSE_NEWLIB_REENTRANT == 0 */

/* Private defines ---------------------------------------------------------*/
/** Initialize members in instance of <code>LockingData_t</code> structure */
#define LOCKING_DATA_INIT { {0, 0}, 0 }
#define STM32_LOCK_MAX_NESTED_LEVELS 2 /**< Max nesting level of interrupts */
typedef struct
{
  uint32_t basepri[STM32_LOCK_MAX_NESTED_LEVELS];
  uint8_t nesting_level;
} LockingData_t;

/* Private macros ----------------------------------------------------------*/
/** Blocks execution if reached max nesting level */
#define STM32_LOCK_ASSERT_VALID_NESTING_LEVEL(lock)                   \
  do                                                                  \
  {                                                                   \
    if (lock->nesting_level >= STM32_LOCK_ARRAY_SIZE(lock->basepri))  \
    {                                                                 \
      STM32_LOCK_BLOCK();                                             \
    }                                                                 \
  } while (0)

/* Private functions -------------------------------------------------------*/

/**
  * @brief Initialize STM32 lock
  * @param lock The lock to init
  */
static inline void stm32_lock_init(LockingData_t *lock)
{
  STM32_LOCK_BLOCK_IF_NULL_ARGUMENT(lock);
  for (size_t i = 0; i < STM32_LOCK_ARRAY_SIZE(lock->basepri); i++)
  {
    lock->basepri[i] = 0;
  }
  lock->nesting_level = 0;
}

/**
  * @brief Acquire STM32 lock
  * @param lock The lock to acquire
  */
static inline void stm32_lock_acquire(LockingData_t *lock)
{
  STM32_LOCK_BLOCK_IF_NULL_ARGUMENT(lock);
  STM32_LOCK_ASSERT_VALID_NESTING_LEVEL(lock);
  lock->basepri[lock->nesting_level++] = taskENTER_CRITICAL_FROM_ISR();
}

/**
  * @brief Release STM32 lock
  * @param lock The lock to release
  */
static inline void stm32_lock_release(LockingData_t *lock)
{
  STM32_LOCK_BLOCK_IF_NULL_ARGUMENT(lock);
  lock->nesting_level--;
  STM32_LOCK_ASSERT_VALID_NESTING_LEVEL(lock);
  taskEXIT_CRITICAL_FROM_ISR(lock->basepri[lock->nesting_level]);
}

#undef STM32_LOCK_ASSERT_VALID_NESTING_LEVEL
#undef STM32_LOCK_MAX_NESTED_LEVELS

#elif STM32_THREAD_SAFE_STRATEGY == 5
/*
 * Deny lock usage from interrupts. Implemented using FreeRTOS locks.
 */

/* Includes ----------------------------------------------------------------*/
#include <FreeRTOS.h>
#include <task.h>
#if defined (__GNUC__) && !defined (__CC_ARM) && configUSE_NEWLIB_REENTRANT == 0
#warning Please set configUSE_NEWLIB_REENTRANT to 1 in FreeRTOSConfig.h, otherwise newlib will not be thread-safe
#endif /* defined (__GNUC__) && !defined (__CC_ARM) && configUSE_NEWLIB_REENTRANT == 0 */

/* Private defines ---------------------------------------------------------*/
/** Initialize members in instance of <code>LockingData_t</code> structure */
#define LOCKING_DATA_INIT 0

/* Private typedef ---------------------------------------------------------*/
typedef uint8_t LockingData_t;  /**< Unused */

/* Private functions -------------------------------------------------------*/

/**
  * @brief Initialize STM32 lock
  * @param lock The lock to init
  */
static inline void stm32_lock_init(LockingData_t *lock)
{
  STM32_LOCK_BLOCK_IF_NULL_ARGUMENT(lock);
}

/**
  * @brief Acquire STM32 lock
  * @param lock The lock to acquire
  */
static inline void stm32_lock_acquire(LockingData_t *lock)
{
  STM32_LOCK_BLOCK_IF_NULL_ARGUMENT(lock);
  STM32_LOCK_BLOCK_IF_INTERRUPT_CONTEXT();
  vTaskSuspendAll();
}

/**
  * @brief Release STM32 lock
  * @param lock The lock to release
  */
static inline void stm32_lock_release(LockingData_t *lock)
{
  STM32_LOCK_BLOCK_IF_NULL_ARGUMENT(lock);
  STM32_LOCK_BLOCK_IF_INTERRUPT_CONTEXT();
  xTaskResumeAll();
}

#else
#error Invalid STM32_THREAD_SAFE_STRATEGY specified
#endif /* STM32_THREAD_SAFE_STRATEGY */

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* __STM32_LOCK_H__ */
