//
// Created by Fir on 2024/2/2.
//

#include "render.h"

#include <cmath>

namespace astra::render {
std::function<void()> list = &Render::listCallBack;
std::function<void()> tile = &Render::tileCallBack;
std::function<void()> listSideBar = &Render::listSideBarCallBack;
std::function<void()> listWindow = &Render::listWindowCallBack;
std::function<void()> listCheckBox = &Render::listCheckBoxCallBack;
std::function<void()> window = &Render::windowCallBack;
std::function<void()> checkBox = &Render::checkBoxCallBack;
std::function<void()> sideBar = &Render::sideBarCallBack;

void Render::listCallBack() {

}
void Render::tileCallBack() {

}
void Render::listSideBarCallBack() {

}
void Render::listWindowCallBack() {

}
void Render::listCheckBoxCallBack() {

}
void Render::windowCallBack() {

}
void Render::checkBoxCallBack() {

}
void Render::sideBarCallBack() {

}

void Render::animation(float *_pos, const float *_posTrg) {
  if (*_pos != *_posTrg)
  {
    if (std::fabs(*_pos - *_posTrg) < 0.15f) *_pos = *_posTrg;
    else *_pos += (*_posTrg - *_pos) / (50.0f / 10.0f);
  }
}

}