/***************************************************
 * Data Structure & Algorithm
 * wzhe ahuwang@163.com
 ***************************************************/

#pragma once

#include "BinTree.h"

template<typename T> class BST : public BinTree<T> {
protected:
    BinNodePosi(T) hot_;		//search()最后访问的非空的节点位置
    BinNodePosi(T) connect34(
        BinNodePosi(T), BinNodePosi(T), BinNodePosi(T),
        BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T) );
    BinNodePosi(T) rotateAt( BinNodePosi(T) x);
public:
    virtual BinNodePosi(T) & search(const T& e);
    virtual BinNodePosi(T) insert(const T& e);
    virtual bool remove(const T& e);
};

#include "BinSearchTree_implementation.h"
