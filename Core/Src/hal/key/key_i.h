//
// Created by Fir on 2024/2/2.
//

#pragma once
#ifndef ASTRA_CORE_SRC_KEY_I_H_
#define ASTRA_CORE_SRC_KEY_I_H_

#endif //ASTRA_CORE_SRC_KEY_I_H_

namespace hardware {

/**
 * @param keyActionFlag if it equal to KEY_PRESSED, begin process the value.
 * @param keyValue the value of key, throw it to switch case.
 * @warning remember to reset the keyActionFlag to KEY_NOT_PRESSED, after if-else.
 * @post reset the keyActionFlag to KEY_NOT_PRESSED
 */
class KeyDriver_i {
public:
  virtual void keyScan() = 0;
  virtual void keyTest() = 0;
};

}