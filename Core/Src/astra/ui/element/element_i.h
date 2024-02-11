//
// Created by Fir on 2024/2/7.
//

#pragma once
#ifndef ASTRA_CORE_SRC_ASTRA_UI_ELEMENT_ELEMENT_I_H_
#define ASTRA_CORE_SRC_ASTRA_UI_ELEMENT_ELEMENT_I_H_

namespace astra {
class Element_i {
public:
  virtual bool render() = 0;
  virtual void getInput() = 0;
};
}

#endif //ASTRA_CORE_SRC_ASTRA_UI_ELEMENT_ELEMENT_I_H_
