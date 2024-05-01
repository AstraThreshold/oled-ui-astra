//
// Created by Fir on 2024/4/14 014.
//

#include "camera.h"

namespace astra {
Camera::Camera() {
  this->xInit = 0;
  this->yInit = 0;

  this->x = 0;
  this->y = 0;

  this->xTrg = 0;
  this->yTrg = 0;
}

//这里的坐标应该都是负的 因为最终渲染的时候是加上摄像机的坐标
//所以说比如想显示下一页 应该是item本身的坐标减去摄像机的坐标 这样才会让item向上移动
//一个办法是用户传进来正的坐标 但是在摄像机内部 所有坐标都取其相反数 负的

Camera::Camera(float _x, float _y) {
  this->xInit = 0 - _x;
  this->yInit = 0 - _y;

  this->x = 0 - _x;
  this->y = 0 - _y;

  this->xTrg = 0 - _x;
  this->yTrg = 0 - _y;
}

/**
 *
 * @param _x
 * @param _y
 * @return 0: in view, 1: upper, 2: lower
 */
unsigned char Camera::outOfView(float _x, float _y) {
  if (_x < 0 - this->x | _y < 0 - this->y) return 1;
  if (_x > (0 - this->x) + systemConfig.screenWeight - 1 | _y > (0 - this->y) + systemConfig.screenHeight - 1) return 2;
  return 0;
}

std::vector<float> Camera::getPosition() {
  return {x, y};
}

void Camera::init(const std::string &_type) {
  if (_type == "List") {
    this->goDirect(0, static_cast<float>((0 - sys::getSystemConfig().screenHeight) * 10));
    this->render();
  }
  else if (_type == "Tile") {
    this->goDirect(static_cast<float>((0 - sys::getSystemConfig().screenWeight) * 10), 0);
    this->render();
  }
}

/**
 * @brief
 * @param _pos
 * @param _posTrg
 * @param _speed
 *
 * @note only support in loop. 仅支持在循环内执行
 */
void Camera::go(float _x, float _y) {
  this->xTrg = 0 - _x;
  this->yTrg = 0 - _y;
}

void Camera::go(const std::vector<float> &_pos) {
  this->xTrg = 0 - _pos[0];
  this->yTrg = 0 - _pos[1];
}

void Camera::goDirect(float _x, float _y) {
  this->x = 0 - _x;
  this->y = 0 - _y;
  this->xTrg = 0 - _x;
  this->yTrg = 0 - _y;
}

void Camera::goHorizontal(float _x) {
  this->xTrg = 0 - _x;
}

void Camera::goVertical(float _y) {
  this->yTrg = 0 - _y;
}

void Camera::goToNextPageItem() {
  this->yTrg = y - systemConfig.screenHeight;
}

void Camera::goToPreviewPageItem() {
  this->yTrg = y + systemConfig.screenHeight;
}

void Camera::goToListItemPage(unsigned char _index) {
  static const unsigned char maxItemPerScreen = systemConfig.screenHeight / astraConfig.listLineHeight;
  unsigned char _page = 0;

  if (_index == 0) _page = 0;
  else if (_index % maxItemPerScreen == 0) _page = _index / maxItemPerScreen;
  else _page = floor(_index / maxItemPerScreen);
  go(0, _page * systemConfig.screenHeight);
}

void Camera::goToListItemRolling(std::vector<float> _posSelector) {

  //这是一个让页面在一定情况下向下或向上滚动一行的函数
  //当index向上超越了一个屏幕可以显示的内容 就要向上滚动一行 滚动到以当前选择项为第一项的页面
  //当index向下超越了一个屏幕可以显示的内容 就要向下滚动一行 滚动到以当前选择项为最后一项的页面
  //正常情况下 不移动

  //如果不碰边界 不更新端点
  //端点惰性赋值
  //计算出每页第一行的index和最后一行的index
  //碰到下边界就向下滚动 碰到上边界就向上滚动

  //最开始左端点是0 右端点是max-1
  //index超过右端点 就向下滚动index-右端点行 同时左右端点都加上index-右端点

  static unsigned char direction = 0; //0: no roll, 1: up, 2: down

  if (outOfView(_posSelector[0], _posSelector[1]) == 1) direction = 1;
  else if (outOfView(_posSelector[0], _posSelector[1]) == 2) direction = 2;

  if (direction == 1) {
    go(_posSelector[0], _posSelector[1]);
    if (this->x == 0 - _posSelector[0] && this->y == 0 - _posSelector[1]) direction = 0;
  }
  if (direction == 2) {
    go(_posSelector[0], _posSelector[1] + astraConfig.listLineHeight - systemConfig.screenHeight);
    //go到selector的左下角
    if (this->x == 0 - _posSelector[0] && this->y == 0 - (_posSelector[1] + astraConfig.listLineHeight - systemConfig.screenHeight)) direction = 0;
  }
}

void Camera::goToTileItem(unsigned char _index) {
  go(_index * (astraConfig.tilePicWidth + astraConfig.tilePicMargin), 0);
}

bool Camera::isMoving() {
  return moving;
}

void Camera::reset() {
  go(this->xInit, this->yInit);
}

void Camera::resetDirect() {
  goDirect(this->xInit, this->yInit);
}

void Camera::render() {
  moving = true;
  Animation::move(&this->x, this->xTrg, astraConfig.cameraAnimationSpeed);
  Animation::move(&this->y, this->yTrg, astraConfig.cameraAnimationSpeed);
  if (this->x == this->xTrg && this->y == this->yTrg) moving = false;
}

void Camera::update(Menu *_menu, Selector *_selector) {
  //todo 这里还需要处理一下
  if (_menu->cameraPosMemoryFlag) {

  }

  this->render();

  if (_menu->getType() == "List") {
    if (astraConfig.listPageTurningMode == 0) goToListItemPage(_menu->selectIndex);
    else if (astraConfig.listPageTurningMode == 1) goToListItemRolling(_selector->getPosition());
  }
  else if (_menu->getType() == "Tile") goToTileItem(_menu->selectIndex);
}
}