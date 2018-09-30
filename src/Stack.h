/***************************************************
 * Data Structure & Algorithm
 * wzhe ahuwang@163.com
***************************************************/

#pragma once

#include "Vector.h"

//以向量为基类，派生出栈模板类
template <typename T> class Stack : public Vector<T> {
public:
  void push(T const &e) { this->insert(this->size(), e); } //入栈
  T pop() { return this->remove(this->size() - 1); }       //出栈
  T &top() { return (*this)[this->size() - 1]; }           //取顶
};
