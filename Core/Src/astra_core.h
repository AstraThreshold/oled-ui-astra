//
// Created by Fir on 2024/1/21.
//

#ifndef ASTRA_ASTRA__H
#define ASTRA_ASTRA__H

#include "astra_driver.h"
#include "cstdint"
#include "string"
#include "astra_printer.h"
#include <vector>

namespace astra {
/**
 * @brief 页面类 以树型数据结构来管理各页面
 */
class Page : PagePrinter {
private:
  Page *parentPage;                 //指向父节点 根节点无父节点 此指针为空

  /**绘图域**/
  PagePrinter* printer;
  typedef void (PagePrinter::*pageType)();  //指向PagePrinter类中的无形参void型函数的指针类型
  pageType selfType;
  //void (PagePrinter::*selfType)();
  /**绘图域**/

  /**数据域**/
  uint8_t num;
  uint8_t select;
  std::vector<std::vector<uint8_t>> pic;  //图片内容
  std::vector<std::string> text;    //文本内容
  /**数据域**/

  /**识别域**/
  std::vector<void*> childPage;     //包含指向子节点的指针的容器
  bool isMainMenu;
  /**识别域**/

public:
  //构造函数可以有很多种 相当于多态
  //driver类是此类的父类
  Page* findPage(Page* _rootPage, const Page* _lookingFor);

  explicit Page(pageType _type);   //建立首页 即根节点

  Page(const std::string& _title, Page *_parentPage, pageType _type);    //列表页
  Page(const std::string& _title, const std::vector<uint8_t>& _pic, Page *_parentPage, pageType _type);  //磁贴页
};

class Widget : WidgetPrinter {
public:
  typedef void (WidgetPrinter::*pageType)();
};

/**
 * @brief UI调度器 决定该显示哪个 显示来自哪里的
 * @brief page创建完毕后负责梳理出来指向架构
 * @brief **ui的index是树模式 从后面添加 从前面显示**
 * 主菜单是根结点
 */
class UIScheduler {
private:
  Page* pageDisplay = nullptr;    //page displaying right now

  uint8_t pageInit{};
  uint8_t uiState{};
  uint8_t fadeFlag{};

public:

  void init();

  void astraKernelStart(Page *_root);

};
}

#endif //ASTRA_ASTRA__H
