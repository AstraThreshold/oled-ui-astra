//
// Created by Fir on 2024/3/7 007.
// 此文件的作用是引导STM32进入astra UI 基于C++
// this file is used to guide STM32 into astra UI based on C++
//

#ifndef ASTRA_CORE_SRC_ASTRA_ASTRA_ROCKET_H_
#define ASTRA_CORE_SRC_ASTRA_ASTRA_ROCKET_H_

#ifdef __cplusplus
extern "C" {
#endif

/*---- C ----*/

void astraCoreInit(void);
void astraCoreStart(void);
void astraCoreDestroy(void);

/*---- C ----*/

#ifdef __cplusplus
}

/*---- Cpp ----*/
#include "../astra/ui/launcher.h"
#include "../hal/hal_dreamCore/hal_dreamCore.h"

/*---- Cpp ----*/

#endif
#endif //ASTRA_CORE_SRC_ASTRA_ASTRA_ROCKET_H_
