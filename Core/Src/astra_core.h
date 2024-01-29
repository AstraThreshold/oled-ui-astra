//
// Created by Fir on 2024/1/21.
//

#ifndef ASTRA_ASTRA__H
#define ASTRA_ASTRA__H

#include "astra_driver.h"
#include "cstdint"
#include "string"

namespace astra {
/**
 * @brief 页面类 以树型数据结构来管理各页面
 */
class Page : Printer {
private:

  //std::string id;                 //位置序号 格式: 深度+当前深度从左至右的次序
  std::vector<void*> childPage;     //包含指向子节点的指针的容器
  std::vector<uint8_t> childType;   //存储子节点的类型 与childPage数组一一对应
  Page *parentPage;                 //指向父节点 根节点无父节点 此指针为空
  //Page *currentPage;              //指向当前节点（this指针）
  //Page *rootPage;                 //首页 即根节点的地址

  uint8_t num;

  uint8_t select;

  std::vector<std::vector<uint8_t>> pic;  //图片内容
  std::vector<std::string> text;    //文本内容
  //todo 此处需要修改结构 详见work-log

public:
  //构造函数可以有很多种 相当于多态
  //driver类是此类的父类
  Page* findPage(Page* _rootPage, const Page* _lookingFor);

  Page(std::vector<std::string> _text, Page *_parentPage);

  Page(std::vector<std::string> _text, std::vector<std::vector<uint8_t>> _pic);  //首页

  void addWidget(Page *_page, const std::string& _text, uint8_t _widgetType, uint8_t &_value);

};

class Widget {

};

/**
 * @brief UI调度器 决定该显示哪个 显示来自哪里的
 * @brief page创建完毕后负责梳理出来指向架构
 * @brief **ui的index是树模式 从后面添加 从前面显示**
 * 主菜单是根结点
 */
class UIScheduler : public Page {
private:
  Page* pageDisplay = nullptr;    //page displaying right now

  uint8_t pageInit;
  uint8_t uiState;
  uint8_t fadeFlag;

public:
  void init();

  void astraKernelStart(Page *_root);

};
}

#endif //ASTRA_ASTRA__H
