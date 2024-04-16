#include "widget.h"

namespace astra {
//渲染控件的时候启动器还要继续渲染menu
//同时控件的渲染不可以更新画布
//这样就可以实现控件在menu上方覆盖
CheckBox::CheckBox(unsigned char &_value) : value(_value) {
  this->type = WidgetType::CHECKBOX;
  this->parent = nullptr;
}

void CheckBox::init() {

}

bool CheckBox::check() {
  return false;
}

bool CheckBox::uncheck() {
  return false;
}

void CheckBox::render() {

}

bool CheckBox::toggle() {

  return false;
}

PopUp::PopUp(unsigned char _direction, std::string _title, std::vector<std::string> _options, unsigned char &_value) : value(_value) {

}

void PopUp::init() {

}

bool PopUp::open() {
  return false;
}

bool PopUp::close() {
  return false;
}

bool PopUp::selectNext() {
  return false;
}

bool PopUp::selectPreview() {
  return false;
}

bool PopUp::select(unsigned char _index) {
  return false;
}

void PopUp::render() {

}

Slider::Slider(std::string _title, unsigned char _min, unsigned char _max, unsigned char _step, unsigned char &_value) : value(_value) {

}

void Slider::init() {

}

bool Slider::open() {
  return false;
}

bool Slider::close() {
  return false;
}

unsigned char Slider::add() {
  return 0;
}

unsigned char Slider::sub() {
  return 0;
}

void Slider::render() {

}
}

