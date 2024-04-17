#include "widget.h"

namespace astra {
//渲染控件的时候启动器还要继续渲染menu
//同时控件的渲染不可以更新画布
//这样就可以实现控件在menu上方覆盖
CheckBox::CheckBox(bool &_value) {
  value = _value;
  this->type = WidgetType::CHECKBOX;
  this->parent = nullptr;
}

void CheckBox::init() {
//todo
}

bool CheckBox::check() {
  value = true;
  return value;
}

bool CheckBox::uncheck() {
  value = false;
  return value;
}

void CheckBox::render(float _x, float _y, std::vector<float> _camera) {
  Item::updateConfig();
  //绘制外框
  HAL::setDrawType(1);
  HAL::drawRFrame(_x + _camera[0],
                _y + _camera[1],
                astraConfig.checkBoxWidth,
                astraConfig.checkBoxHeight,
                astraConfig.checkBoxRadius);
  if (this->value) //绘制复选框内的点
    HAL::drawBox(_x + _camera[0] + astraConfig.checkBoxWidth / 4,
                  _y + _camera[1] + astraConfig.checkBoxHeight / 4,
                  astraConfig.checkBoxWidth / 2,
                  astraConfig.checkBoxHeight / 2);
}

bool CheckBox::toggle() {
  value = !value;
  return value;
}

PopUp::PopUp(unsigned char _direction, std::string _title, std::vector<std::string> _options, unsigned char &_value) : value(_value) {

}

void PopUp::init() {

}

void PopUp::open() {
  this->isOpen = true;
}

void PopUp::close() {
  this->isOpen = false;
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

void Slider::open() {
  this->isOpen = true;
}

void Slider::close() {
  this->isOpen = false;
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

