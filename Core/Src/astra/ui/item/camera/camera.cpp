//
// Created by Fir on 2024/4/14 014.
//

#include "camera.h"

#include <cmath>

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

void Camera::goToListItemRolling(unsigned char _index) {
  //如果当前选择的index大于屏幕能容纳的 那就向下移动index-最大index行
  //如果当前选择的index小于屏幕能容纳的 那就向上移动index-最小index行
  //两个端点值最开始是0 : screenHeight/行高
  //当index越界时 更新端点值 端点值的间距永远是screenHeight/行高

  static unsigned char lBoundary = this->yTrg / astraConfig.listLineHeight;
  static unsigned char rBoundary = (systemConfig.screenHeight / astraConfig.listLineHeight) - 1;
  static bool init = false;

  //第一次进入的时候初始化 退出页面记住坐标 再次进入就OK了
  if (!init) {
    go(0,0);
    init = true;
  }

  //todo 第二次进来的时候 go到了记忆中的位置 继续move也是在记忆中的位置的基础上进行move
  //todo 所以具体要move多少 还需要改变

  if (_index < lBoundary) {
    //注意这里是go不是move
    move(0, (_index - lBoundary) * astraConfig.listLineHeight);
    lBoundary = _index;
    rBoundary = lBoundary + systemConfig.screenHeight / astraConfig.listLineHeight - 1;
    return;
  }
  else if (_index > rBoundary) {
    move(0, (_index - rBoundary) * astraConfig.listLineHeight);
    rBoundary = _index;
    lBoundary = rBoundary - systemConfig.screenHeight / astraConfig.listLineHeight + 1;
    return;
  }
  else return;
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

  if (_menu->cameraPosMemoryFlag) {
    go(0 - _menu->getCameraMemoryPos()[0], 0 - _menu->getCameraMemoryPos()[1]);
    _menu->cameraPosMemoryFlag = false;
    _menu->resetCameraMemoryPos();
  }
    //if (this->isReached(_menu->getCameraMemoryPos())) _menu->cameraPosMemoryFlag = false;
  if (_menu->getType() == "List") goToListItemRolling(_menu->selectIndex);
  else if (_menu->getType() == "Tile") goToTileItem(_menu->selectIndex);

  this->render();
}
}