/***************************************************
 * Data Structure & Algorithm
 * wzhe ahuwang@163.com
***************************************************/

#pragma once

#include "BinNode.h"

template <typename T> class BinTree {
protected:
  int size_;
  BinNodePosi(T) root_;
  virtual int updateHeight(BinNodePosi(T) x); //更新节点x的高度
  void updateHeightAbove(BinNodePosi(T) x);   //更新节点x及其祖先高度

public:
  //构造函数
  BinNode() : size_(0), root_(NULL) {}
  ~BinNode() : {
    if (0 < size_)
      remove(root);
  }

  int size() { return size_; }
  bool empty() { return !root_; }
  BinNodePosi(T) root() const { return root_; }

  BinNodePosi(T) insertAsRoot(T const &);                  //插入跟节点
  BinNodePosi(T) insertAsLC(BinNodePosi(T) x, T const &e); // e作为左孩子插入
  BinNodePosi(T) insertAsRC(BinNodePosi(T) x, T const &e);
  BinNodePosi(T) attachAsLC(BinNodePosi(T) x, BinTree<T> *&T);
  BinNodePosi(T) attachAsRC(BinNodePosi(T) x, BinTree<T> *&T);

  int remove(BinNodePosi(T) x); //删除以x节点为根的子树，返回原先该子树的规模
  BinTree<T> *secede(BinNodePosi(T)
                         x); //将子树x从当前树中摘除，并将其转换为一颗独立子树

  template <typename VST> //层次遍历
  void travLevel(VST &visit) {
    if (root_)
      root_->travLevel(visit);
  }

  template <typename VST> //先序遍历
  void travPre(VST &visit) {
    if (root_)
      root_->travPre(visit);
  }

  template <typename VST> //中序遍历
  void travIn(VST &visit) {
    if (root_)
      root_->travIn(visit);
  }

  template <typename VST> //后序遍历
  void travPost(VST &visit) {
    if (root_)
      root_->travPost(visit);
  }
};
