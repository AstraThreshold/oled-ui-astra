//
// Created by Fir on 2024/1/21.
//

#pragma once
#ifndef ASTRA_ASTRA__H
#define ASTRA_ASTRA__H

#include "cstdint"
#include "string"
#include <vector>
#include "render/render.h"
#include "functional"

namespace astra {
/**
 * @brief 页面类 以树型数据结构来管理各页面
 */
class Page {
public:
  Page *parentPage;                 //指向父节点 根节点无父节点 此指针为空

  /**绘图域**/
  typedef std::function<void()> pageType;
  pageType selfType;
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

  Page* findPage(Page* _rootPage, const Page* _lookingFor);

  explicit Page(pageType _type);   //建立首页 即根节点
  Page(const std::string& _title, Page *_parentPage, pageType _type);    //列表页
  Page(const std::string& _title, const std::vector<uint8_t>& _pic, Page *_parentPage, pageType _type);  //磁贴页

  //判断两个std::function是否相等
  template <typename R, typename... Args>
  bool isSame(std::function<R(Args...)> const& _f1, std::function<R(Args...)> const& _f2)
  {
    // 检查两个std::function是否都有目标
    if(!_f1 || !_f2)
      return false;

    // 检查两个std::function的目标类型是否相同
    if(_f1.target_type() != _f2.target_type())
      return false;

    // 获取并比较两个std::function的目标
    typedef R(funcType)(Args...);
    funcType* _p1 = _f1.template target<funcType>();
    funcType* _p2 = _f2.template target<funcType>();
    if (_p1 == nullptr || _p2 == nullptr)
      return false; // 一个或者两个std::function没有目标
    return _p1 == _p2;
  }
};
}
#endif //ASTRA_ASTRA__H