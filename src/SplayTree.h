/***************************************************
 * Data Structure & Algorithm
 * wzhe ahuwang@163.com
 ***************************************************/

#pragma once

#include "BinSearchTree.h"

template<typename T> class Splay : public BST<T> {
protected:
    BinNodePosi(T) splay(BinNodePosi(T) v); //将节点v伸展至根
public:
    BinNodePosi(T) & search (const T& e) override; //查找
    BinNodePosi(T) insert (const T& e) override; //插入
    bool remove (const T& e) override;           //删除
};

#include "SplayTree_implementation.h"