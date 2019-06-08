/***************************************************
 * Data Structure & Algorithm
 * wzhe ahuwang@163.com
 ***************************************************/

#pragma once

#include "BinSearchTree.h"

template<typename T> class AVL : public BST<T> {
public:
    BinNodePosi(T) insert (const T& e) override;
    bool remove (const T& e) override;
    //BST::search()等其余接口可直接沿用
};

#define Balanced(x) (stature((x).lChild) == stature((x).rChild)) //理想平衡条件
#define BalFac(x) (stature((x).lChild) - stature((x).rChild)) //平衡因子
#define AvlBalanced(x) ((-2 < BalFac(x)) && (BalFac(x) < 2)) //AVL平衡条件
/***************************************************
 * 在左、右孩子中取更高者，若等高，则与父亲p同侧者优先
 * 在AVL平衡调整前，借此确定重构方案
 ***************************************************/
#define tallerChild(x) ( \
    stature((x)->lChild) > stature((x)->rChild) ? (x)->lChild : ( \
    stature((x)->rChild) > stature((x)->lChild) ? (x)->rChild : ( \
    IsLChild(*(x)) ? (x)->lChild : (x)->rChild \
    ) \
    ) \
)
#include "AVLTree_implementation.h"