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

std::vector<float> Camera::getPositionTrg() {
  return {xTrg, yTrg};
}

void Camera::init(const std::string &_type) {
  if (_type == "List") {
    this->goDirect(0, static_cast<float>((0 - sys::getSystemConfig().screenHeight) * 10));
    //this->render();
  }
  else if (_type == "Tile") {
    this->goDirect(static_cast<float>((0 - sys::getSystemConfig().screenWeight) * 10), 0);
    //this->render();
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

void Camera::move(float _x, float _y) {
  this->xTrg -= _x;
  this->yTrg -= _y;
}

void Camera::moveDirect(float _x, float _y) {
  this->x -= _x;
  this->y -= _y;
  this->xTrg -= _x;
  this->yTrg -= _y;
}

void Camera::moveHorizontal(float _x) {
  this->xTrg -= _x;
}

void Camera::moveVertical(float _y) {
  this->yTrg -= _y;
}

void Camera::goToNextPageItem() {
  this->yTrg = y - systemConfig.screenHeight;
}

void Camera::goToPreviewPageItem() {
  this->yTrg = y + systemConfig.screenHeight;
}

void Camera::goToListItemRolling(const std::vector<float>& _posSelector) {
  static unsigned char linesNeedToMove = 0;

  //if (outOfView(_posSelector) == 0) return;

  linesNeedToMove = static_cast<unsigned char>((_posSelector[1] + y) / astraConfig.listLineHeight);
  if (outOfView(_posSelector) == 1) {
    //todo 需要移动的行数等于selector与camera的距离差对行高取整
    go(0, 0 - linesNeedToMove * astraConfig.listLineHeight);
    return;
  }
  else if (outOfView(_posSelector) == 2) {
    go(0, linesNeedToMove * astraConfig.listLineHeight);
    return;
  }
}

void Camera::goToTileItem(unsigned char _index) {
  go(_index * (astraConfig.tilePicWidth + astraConfig.tilePicMargin), 0);
}

bool Camera::isMoving() const {
  if ((this->x == this->xTrg) and (this->y == this->yTrg)) return false;
  else return true;
}

bool Camera::isReached(float _x, float _y) const {
  if (this->x == 0 - _x and this->y == 0 - _y) return true;
  else return false;
}

bool Camera::isReached(const std::vector<float> &_pos) const {
  if (this->x == 0 - _pos[0] and this->y == 0 - _pos[1]) return true;
  else return false;
}

void Camera::reset() {
  go(this->xInit, this->yInit);
}

void Camera::resetDirect() {
  goDirect(this->xInit, this->yInit);
}

void Camera::render() {
  Animation::move(&this->x, this->xTrg, astraConfig.cameraAnimationSpeed);
  Animation::move(&this->y, this->yTrg, astraConfig.cameraAnimationSpeed);
}

void Camera::update(Menu *_menu, Selector *_selector) {

  if (_menu->getType() == "List") goToListItemRolling(_selector->getPosition());
  else if (_menu->getType() == "Tile") goToTileItem(_menu->selectIndex);

  //todo 考虑是_menu发生了变化导致的
//  if (_menu->cameraPosMemoryFlag) {
//    go(_menu->getCameraMemoryPos());
//    //if (this->isReached(_menu->getCameraMemoryPos())) _menu->cameraPosMemoryFlag = false;
//  } else {
//    //do sth
//  }

  this->render();
}
}