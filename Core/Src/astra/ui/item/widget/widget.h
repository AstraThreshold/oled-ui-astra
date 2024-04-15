#pragma once
#ifndef ASTRA_WIDGET__H
#define ASTRA_WIDGET__H

namespace astra {

class Widget {
public:
  void (*callback)(unsigned char);

  typedef enum WidgetType {
    CHECKBOX = 0,
    POPUP,
    SLIDER,
    SIDEBAR,
  } WidgetType;

  WidgetType type;

public:
  Widget() = default;

  void inject(void (*_callback)(unsigned char)) { this->callback = _callback; }

};

}

#endif //ASTRA_WIDGET__H