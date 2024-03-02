////
//// Created by Fir on 2024/2/2.
////
//
//#include "widget.h"
//
//namespace astra {
///**
// * @brief widget constructor of window and check-box.
// *
// * @param _title
// * @param _parentPage
// * @param _value
// * @param _type
// */
//Widget::Widget(const std::string &_title, Page *_parentPage, uint8_t _value) {
////  if (isSame(_parentPage->selfType, render::listCheckBox) | isSame(_parentPage->selfType, render::listWindow)) {
////    //this->printer = new WidgetPrinter;
////    this->selfType = std::move(_type);
////
////    this->parentPage = _parentPage;
////    _parentPage->childPage.push_back(this);   //connect each other.
////
////    this->title = _title;
////    this->text = {};
////
////    this->value = _value;
////  }
//}
//
///**
// * @brief widget constructor of side-bar.
// *
// * @param _title
// * @param _text
// * @param _parentPage
// * @param _value
// * @note this function does not need to be passed the type.
// */
//Widget::Widget(const std::string &_title, const std::vector<std::string>& _text, Page *_parentPage, uint8_t _value) {
////  if (isSame(_parentPage->selfType, render::listSideBar)) {
////    this->selfType = render::sideBar;
////
////    this->parentPage = _parentPage;
////    _parentPage->childPage.push_back(this);   //connect each other.
////
////    this->title = _title;
////    this->text = _text;
////
////    this->value = _value;
////  }
//}
//}