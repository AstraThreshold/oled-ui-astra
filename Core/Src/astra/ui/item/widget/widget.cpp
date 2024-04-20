#include "widget.h"

namespace astra {

CheckBox::CheckBox(bool &_value) {
  value = _value;
  if (value) isCheck = true;
  else isCheck = false;
  this->type = WidgetType::CHECKBOX;
  this->parent = nullptr;
}

bool CheckBox::check() {
  value = true;
  isCheck = true;
  return isCheck;
}

bool CheckBox::uncheck() {
  value = false;
  isCheck = false;
  return isCheck;
}

bool CheckBox::toggle() {
  value = !value;
  isCheck = !isCheck;
  return isCheck;
}

void CheckBox::init() {
  if (value) isCheck = true;
  else isCheck = false;
}

void CheckBox::deInit() {
  delete this;
}

void CheckBox::renderIndicator(float _x, float _y, const std::vector<float> &_camera) {
  Item::updateConfig();
  //绘制外框
  HAL::setDrawType(1);
  HAL::drawRFrame(_x + _camera[0],
                  _y + _camera[1],
                  astraConfig.checkBoxWidth,
                  astraConfig.checkBoxHeight,
                  astraConfig.checkBoxRadius);
  if (isCheck) //绘制复选框内的点
    HAL::drawBox(_x + _camera[0] + astraConfig.checkBoxWidth / 4,
                 _y + _camera[1] + astraConfig.checkBoxHeight / 4,
                 astraConfig.checkBoxWidth / 2,
                 astraConfig.checkBoxHeight / 2);
}

void CheckBox::render(const std::vector<float> &_camera) {
  //todo 选中复选框后弹出消息提醒
}

}

