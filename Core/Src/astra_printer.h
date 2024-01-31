//
// Created by Fir on 2024/1/31.
//

#ifndef ASTRA_CORE_SRC_ASTRA_PRINTER_H_
#define ASTRA_CORE_SRC_ASTRA_PRINTER_H_

namespace astra {

class PagePrinter {
public:
  void list();
  void tile();
};

class WidgetPrinter {
public:
  void sideBar();
  void window();
  void checkBox();
};


}


#endif //ASTRA_CORE_SRC_ASTRA_PRINTER_H_
