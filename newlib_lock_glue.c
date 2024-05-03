/**
  ******************************************************************************
  * @file      newlib_lock_glue.c
  * @author    STMicroelectronics
  * @brief     Implementation of newlib lock interface
  *
  * @details   This file implements locking glue necessary to protect C library
  *            functions and initialization of local static objects in C++.
  *            Lock strategies are defined in stm32_lock.h that implements
  *            different level of thread-safety.
  *
  *            For more information about which C functions need which of these
  *            low level functions, please consult the newlib libc manual,
  *            see https://sourceware.org/newlib/libc.html
  *
  *            For more information about the one-time construction API for C++,
  *            see https://itanium-cxx-abi.github.io/cxx-abi/abi.html#once-ctor
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

#if !defined (__GNUC__) || defined (__CC_ARM)
#error "newlib_lock_glue.c" should be used with GNU Compilers only
#endif /* !defined (__GNUC__) || defined (__CC_ARM) */

/* Includes ------------------------------------------------------------------*/
#include <cmsis_compiler.h>

/* Private functions ---------------------------------------------------------*/

/**
  * @brief Global Error_Handler
  */
__WEAK void Error_Handler(void)
{
  /* Not used if it exists in project */
  while (1);
}

#ifdef __SINGLE_THREAD__
#warning C library is in single-threaded mode. Please take care when using C library functions in threaded contexts
#else

/* Includes ------------------------------------------------------------------*/
#include <newlib.h>
#include <stdatomic.h>
#include "stm32_lock.h"

/**
  * @defgroup _newlib_lock_functions newlib library locks
  * @see https://sourceware.org/newlib/libc.html
  * @{
  */

#if __NEWLIB__ >= 3 && defined (_RETARGETABLE_LOCKING)
#include <errno.h>
#include <stdlib.h>
#include <sys/lock.h>

/* Private macros ------------------------------------------------------------*/
/** See struct __lock definition */
#define STM32_LOCK_PARAMETER(lock) (&(lock)->lock_data)

/* Private variables ---------------------------------------------------------*/
struct __lock
{
  LockingData_t lock_data; /**< The STM32 lock instance */
};

/** Implementing mutex from <a href="https://sourceware.org/git/?p=newlib-cygwin.git;a=blob_plain;f=newlib/libc/misc/lock.c">newlib/libc/misc/lock.c</a> */
struct __lock __lock___sinit_recursive_mutex = { LOCKING_DATA_INIT };

/** Implementing mutex from <a href="https://sourceware.org/git/?p=newlib-cygwin.git;a=blob_plain;f=newlib/libc/misc/lock.c">newlib/libc/misc/lock.c</a> */
struct __lock __lock___sfp_recursive_mutex = { LOCKING_DATA_INIT };

/** Implementing mutex from <a href="https://sourceware.org/git/?p=newlib-cygwin.git;a=blob_plain;f=newlib/libc/misc/lock.c">newlib/libc/misc/lock.c</a> */
struct __lock __lock___atexit_recursive_mutex = { LOCKING_DATA_INIT };

/** Implementing mutex from <a href="https://sourceware.org/git/?p=newlib-cygwin.git;a=blob_plain;f=newlib/libc/misc/lock.c">newlib/libc/misc/lock.c</a> */
struct __lock __lock___at_quick_exit_mutex = { LOCKING_DATA_INIT };

/** Implementing mutex from <a href="https://sourceware.org/git/?p=newlib-cygwin.git;a=blob_plain;f=newlib/libc/misc/lock.c">newlib/libc/misc/lock.c</a> */
struct __lock __lock___malloc_recursive_mutex = { LOCKING_DATA_INIT };

/** Implementing mutex from <a href="https://sourceware.org/git/?p=newlib-cygwin.git;a=blob_plain;f=newlib/libc/misc/lock.c">newlib/libc/misc/lock.c</a> */
struct __lock __lock___env_recursive_mutex = { LOCKING_DATA_INIT };

/** Implementing mutex from <a href="https://sourceware.org/git/?p=newlib-cygwin.git;a=blob_plain;f=newlib/libc/misc/lock.c">newlib/libc/misc/lock.c</a> */
struct __lock __lock___tz_mutex = { LOCKING_DATA_INIT };

/** Implementing mutex from <a href="https://sourceware.org/git/?p=newlib-cygwin.git;a=blob_plain;f=newlib/libc/misc/lock.c">newlib/libc/misc/lock.c</a> */
struct __lock __lock___dd_hash_mutex = { LOCKING_DATA_INIT };

/** Implementing mutex from <a href="https://sourceware.org/git/?p=newlib-cygwin.git;a=blob_plain;f=newlib/libc/misc/lock.c">newlib/libc/misc/lock.c</a> */
struct __lock __lock___arc4random_mutex = { LOCKING_DATA_INIT };

/* Private functions ---------------------------------------------------------*/

/**
  * @brief Initialize lock
  * @param lock The lock
  */
void __retarget_lock_init(_LOCK_T *lock)
{
  __retarget_lock_init_recursive(lock);
}

/**
  * @brief Initialize recursive lock
  * @param lock The lock
  */
void __retarget_lock_init_recursive(_LOCK_T *lock)
{
  if (lock == NULL)
  {
    errno = EINVAL;
    return;
  }

  *lock = (_LOCK_T)malloc(sizeof(struct __lock));
  if (*lock != NULL)
  {
    stm32_lock_init(STM32_LOCK_PARAMETER(*lock));
    return;
  }

  /* Unable to allocate memory */
  STM32_LOCK_BLOCK();
}

/**
  * @brief Close lock
  * @param lock The lock
  */
void __retarget_lock_close(_LOCK_T lock)
{
  __retarget_lock_close_recursive(lock);
}

/**
  * @brief Close recursive lock
  * @param lock The lock
  */
void __retarget_lock_close_recursive(_LOCK_T lock)
{
  free(lock);
}

/**
  * @brief Acquire lock
  * @param lock The lock
  */
void __retarget_lock_acquire(_LOCK_T lock)
{
  STM32_LOCK_BLOCK_IF_NULL_ARGUMENT(lock);
  stm32_lock_acquire(STM32_LOCK_PARAMETER(lock));
}

/**
  * @brief Acquire recursive lock
  * @param lock The lock
  */
void __retarget_lock_acquire_recursive(_LOCK_T lock)
{
  STM32_LOCK_BLOCK_IF_NULL_ARGUMENT(lock);
  stm32_lock_acquire(STM32_LOCK_PARAMETER(lock));
}

/**
  * @brief Try acquire lock
  * @param lock The lock
  * @return 0 always
  */
int __retarget_lock_try_acquire(_LOCK_T lock)
{
  __retarget_lock_acquire(lock);
  return 0;
}

/**
  * @brief Try acquire recursive lock
  * @param lock The lock
  * @return 0 always
  */
int __retarget_lock_try_acquire_recursive(_LOCK_T lock)
{
  __retarget_lock_acquire_recursive(lock);
  return 0;
}

/**
  * @brief Release lock
  * @param lock The lock
  */
void __retarget_lock_release(_LOCK_T lock)
{
  STM32_LOCK_BLOCK_IF_NULL_ARGUMENT(lock);
  stm32_lock_release(STM32_LOCK_PARAMETER(lock));
}

/**
  * @brief Release recursive lock
  * @param lock The lock
  */
void __retarget_lock_release_recursive(_LOCK_T lock)
{
  STM32_LOCK_BLOCK_IF_NULL_ARGUMENT(lock);
  stm32_lock_release(STM32_LOCK_PARAMETER(lock));
}

#else
#warning This makes malloc, env, and TZ calls thread-safe, not the entire newlib

/* Includes ------------------------------------------------------------------*/
#include <reent.h>

/* Private variables ---------------------------------------------------------*/
/** Mutex used in __malloc_lock and __malloc_unlock */
static LockingData_t __lock___malloc_recursive_mutex = LOCKING_DATA_INIT;

/** Mutex used in __env_lock and __env_unlock */
static LockingData_t __lock___env_recursive_mutex = LOCKING_DATA_INIT;

/** Mutex used in __tz_lock and __tz_unlock */
static LockingData_t __lock___tz_mutex = LOCKING_DATA_INIT;

/* Private functions ---------------------------------------------------------*/

#if __STD_C

/**
  * @brief Acquire malloc lock
  * @param reent The reentrance struct
  */
void __malloc_lock(struct _reent *reent)
{
  STM32_LOCK_UNUSED(reent);
  stm32_lock_acquire(&__lock___malloc_recursive_mutex);
}

/**
  * @brief Release malloc lock
  * @param reent The reentrance struct
  */
void __malloc_unlock(struct _reent *reent)
{
  STM32_LOCK_UNUSED(reent);
  stm32_lock_release(&__lock___malloc_recursive_mutex);
}

#else

/**
  * @brief Acquire malloc lock
  */
void __malloc_lock()
{
  stm32_lock_acquire(&__lock___malloc_recursive_mutex);
}

/**
  * @brief Release malloc lock
  */
void __malloc_unlock()
{
  stm32_lock_release(&__lock___malloc_recursive_mutex);
}
#endif /* __STD_C */

/**
  * @brief Acquire env lock
  * @param reent The reentrance struct
  */
void __env_lock(struct _reent *reent)
{
  STM32_LOCK_UNUSED(reent);
  stm32_lock_acquire(&__lock___env_recursive_mutex);
}

/**
  * @brief Release env lock
  * @param reent The reentrance struct
  */
void __env_unlock(struct _reent *reent)
{
  STM32_LOCK_UNUSED(reent);
  stm32_lock_release(&__lock___env_recursive_mutex);
}

/**
  * @brief Acquire tz lock
  */
void __tz_lock()
{
  stm32_lock_acquire(&__lock___tz_mutex);
}

/**
  * @brief Release tz lock
  */
void __tz_unlock()
{
  stm32_lock_release(&__lock___tz_mutex);
}

#endif /* __NEWLIB__ >= 3 && defined (_RETARGETABLE_LOCKING) */

/**
  * @}
  */


/**
  * @defgroup __cxa_guard_ GNU C++ one-time construction API
  * @see https://itanium-cxx-abi.github.io/cxx-abi/abi.html#once-ctor
  *
  * When building for C++, please make sure that <tt>-fno-threadsafe-statics</tt> is not passed to the compiler
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/** The guard object is created by the C++ compiler and is 32 bit for ARM EABI. */
typedef struct
{
  atomic_uchar initialized; /**< Indicate if object is initialized */
  uint8_t acquired; /**< Ensure non-recursive lock */
  uint16_t unused; /**< Padding */
} __attribute__((packed)) CxaGuardObject_t;

/* Private variables ---------------------------------------------------------*/
/** Mutex used in __cxa_guard_acquire, __cxa_guard_release and __cxa_guard_abort */
static LockingData_t __cxa_guard_mutex = LOCKING_DATA_INIT;

/* Private functions ---------------------------------------------------------*/

/**
  * @brief Acquire __cxa_guard mutex
  * @param guard_object Guard object
  * @return 0 if object is initialized, else initialization of object required
  */
int __cxa_guard_acquire(CxaGuardObject_t *guard_object)
{
  STM32_LOCK_BLOCK_IF_NULL_ARGUMENT(guard_object);

  if (atomic_load(&guard_object->initialized) == 0)
  {
    /* Object needs initialization, lock threading context */
    stm32_lock_acquire(&__cxa_guard_mutex);
    if (atomic_load(&guard_object->initialized) == 0)
    {
      /* Object needs initialization */
      if (guard_object->acquired)
      {
        /* Object initialization already in progress */
        STM32_LOCK_BLOCK();
      }

      /* Lock acquired */
      guard_object->acquired = 1;
      return 1;
    }
    else
    {
      /* Object initialized in another thread */
      stm32_lock_release(&__cxa_guard_mutex);
    }
  }

  /* Object already initialized */
  return 0;
}

/**
  * @brief Abort __cxa_guard mutex
  * @param guard_object Guard object
  */
void __cxa_guard_abort(CxaGuardObject_t *guard_object)
{
  STM32_LOCK_BLOCK_IF_NULL_ARGUMENT(guard_object);

  if (guard_object->acquired)
  {
    /* Release lock */
    guard_object->acquired = 0;
    stm32_lock_release(&__cxa_guard_mutex);
  }
  else
  {
    /* Trying to release non-acquired lock */
    STM32_LOCK_BLOCK();
  }
}

/**
  * @brief Release __cxa_guard mutex
  * @param guard_object Guard object
  */
void __cxa_guard_release(CxaGuardObject_t *guard_object)
{
  STM32_LOCK_BLOCK_IF_NULL_ARGUMENT(guard_object);

  /* Object initialized */
  atomic_store(&guard_object->initialized, 1);

  /* Release lock */
  __cxa_guard_abort(guard_object);
}

/**
  * @}
  */

#endif /* __SINGLE_THREAD__ */
