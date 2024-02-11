//
// Created by Fir on 2024/1/21.
//

#pragma once
#ifndef ASTRA_ASTRA__H
#define ASTRA_ASTRA__H

#include "cstdint"
#include "string"
#include <vector>
#include "functional"
#include "../element_i.h"
#include "../../../../hal/hal.h"
#include <cmath>

namespace astra {
/**
 * @brief 页面类 以树型数据结构来管理各页面
 */
class Page : Element_i {
private:
  static graphLib::GraphicsLib* graphLib;

  enum {
    LIST = 0,
    TILE = 1,
  };

  float xSelectBox, xSelectBoxTrg;
  float ySelectBox, ySelectBoxTrg;
  float yBar, yBarTrg;
  float yText, yTextTrg;
  bool loop;
  void animation(float *_pos, const float *_posTrg);

public:
  Page *parentPage;                 //指向父节点 根节点无父节点 此指针为空
  uint8_t selfType;

  //uint8_t num;
  //uint8_t select;
  std::vector<std::vector<uint8_t>> pic;  //图片内容
  std::vector<std::string> text;    //文本内容

  std::vector<void *> childPage;     //包含指向子节点的指针的容器
  //bool isMainMenu;

  Page *findPage(Page *_rootPage, const Page *_lookingFor);

  Page(uint8_t _type);  //首页
  Page(const std::string &_title, Page *_parentPage);    //列表页
  Page(const std::string &_title, const std::vector<uint8_t> &_pic, Page *_parentPage);  //磁贴页
  Page() = default;

  bool render() override;
  void getInput() override;
};
}
#endif //ASTRA_ASTRA__H