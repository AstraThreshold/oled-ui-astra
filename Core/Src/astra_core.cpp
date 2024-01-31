//
// Created by Fir on 2024/1/21.
//

//每个列表应该有 1. 文本（需要显示的内容） 2. 跳转向量表（对应1，每一行都要跳转到哪里）
//其中文本以string形式 向量表以vector形式 以类的形式整合在一起 编写相应的构造函数 调用构造函数即是新建一个页面
//通过最后一项跳转向量表可以判断其类型 比如跳转至下一页 或者返回上一级 或者是复选框 或者是弹窗 或者是侧边栏弹窗 等等
//做一个astra类作为总的框架 在ui命名空间里

//分为
//驱动层 - 界面层（包括各种列表 磁铁 复选框 侧边栏 弹窗等） - 处理层（各种坐标的变换等）

//传进去的有三个东西 第一个是文字（要显示的东西） 第二个是类别（普通列表 跳转列表 复选框） 第三个是特征向量（指向复选框和弹窗对应的参数 要跳转的地方等）

#include "vector"
#include "astra_core.h"

#include "string"

/**
 *     ·  ·     ·   ·
 *  ·   ·  ·  ·   ·
 * 循此苦旅，直抵群星。
 * ad astra per aspera.
 * ·   ·   ·      ·
 *   ·   ·    · ·   ·
 */

namespace astra {

/**
 * @brief preorder traversal to find certain page(node)
 *
 * @param _rootPage current page point
 * @param _lookingFor the page looking for
 * @return pointer of the page we looking for
 */
Page* Page::findPage(Page* _rootPage, const Page* _lookingFor) {  //NOLINT
  if (nullptr ==_rootPage) return nullptr;
  if (_rootPage == _lookingFor) return _rootPage;

  //search in all child page
  for (auto _childPage:_rootPage->childPage) {
    auto _result = findPage((Page*)_childPage, _lookingFor);
    if (_result != nullptr) return _result;
  }

  return nullptr;
}

/**
 * @brief init a new root node(main menu).
 */
Page::Page(pageType _type) {
  printer = new PagePrinter;
  this->selfType = _type;

  this->parentPage = nullptr;

  this->num = 0;
  this->select = 0;
  this->pic = {};
  this->text = {};

  this->childPage = {};
  this->isMainMenu = true;
}

/**
 * @brief init a new list page and connect it to parent page.
 *
 * @param _title the title of itself.
 * @param _parentPage the parent(previous) page of new page.
 * @note the title will show in the _parentPage.
 */
Page::Page(const std::string& _title, Page *_parentPage, pageType _type) {
  if (_parentPage->selfType == &PagePrinter::list) {
    printer = new PagePrinter;
    this->selfType = _type;

    this->parentPage = _parentPage;
    _parentPage->childPage.push_back(this);   //connect each other.

    _parentPage->text.push_back(_title);

    this->num = 0;
    this->select = 0;
    this->pic = {};
    this->text = {};

    this->childPage = {};
    this->isMainMenu = false;
  }
}

/**
 * @brief init a new tile page and connect it to parent page.
 *
 * @param _title
 * @param _pic
 * @param _parentPage the parent(previous) page of new page.
 */
Page::Page(const std::string& _title, const std::vector<uint8_t>& _pic, Page *_parentPage, pageType _type) {
  if (_parentPage->selfType == &PagePrinter::tile) {
    printer = new PagePrinter;
    this->selfType = _type;

    this->parentPage = _parentPage;
    _parentPage->childPage.push_back(this);   //connect each other.

    _parentPage->text.push_back(_title);
    _parentPage->pic.push_back(_pic);

    this->num = 0;
    this->select = 0;
    this->pic = {};
    this->text = {};

    this->childPage = {};
    this->isMainMenu = false;
  }
}

/**
 * @brief add widget for certain item.
 * @todo waiting to be realized
 *
 * @param _page pointer to the page needs to add widget.
 * @param _text the item needs to add widget.
 * @param _widgetType 1: check box | 2: window | 3: side bar
 * @param _value the value widget will change.
 */
//Widget Widget::widget() {
//  //_page->
//}


/**
 * @brief init the framework
 */
void UIScheduler::init() {

}

/**
 * @brief start astra ui framework.
 *
 * @todo 找之前firmware的各种proc的共同点 转而使用指针等来实现
 * @param _root pointer to root node of page tree.
 */
void UIScheduler::astraKernelStart(Page *_root) {

}
}
