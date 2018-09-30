/***************************************************
 * Data Structure & Algorithm
 * wzhe ahuwang@163.com
***************************************************/

#pragma once

/*********************************************
 * BinNode:
 * ----------------------
 * |  lc  | parent | rc |
 * |         data       |
 * | hegit|  npl  |color|
 * ----------------------
*********************************************/

#define BinNodePosi(T) BinNode<T> *         //位置
#define stature(p) ((p) ? (p)->height : -1) //节点高度，约定空树高度为-1

typedef enum { RB_RED, RB_BLACK } RBColor; //节点颜色（红黑树使用）

template <typename T> struct BinNode {
  BinNodePosi(T) parent;
  BinNodePosi(T) lChild;
  BinNodePosi(T) rChild;
  T data;
  int height;
  int npl; // Null Path Length(左式堆，空节点通路长度，也可用height代替)
  RBColor color; //颜色（红黑树）

  //构造函数
  BinNode()
      : parent(NULL), lChild(NULL), rChild(NULL), height(0), npl(1),
        color(RB_RED) {}
  BinNode(T e, BinNodePosi(T) p = NULL, BinNodePosi(T) lc = NULL,
          BinNodePosi(T) rc = NULL, int h = 0, int l = 1, RBColor c = RB_RED)
      : data(e), parent(p), lChild(lc), rChild(rc), height(h), npl(l),
        color(c) {}

  //操作接口
  int size(); //当前节点后代总数，亦即一其为根的子树规模
  BinNodePosi(T) insertAsLC(T const &);
  BinNodePosi(T) insertAsRC(T const &);
  BinNodePosi(T) succ(); //取当前节点的直接后继

  template <typename VST> void travLevel(VST &); //子树层次遍历
  template <typename VST> void travPre(VST &);   //子树先序遍历
  template <typename VST> void travIn(VST &);    //子树中序遍历
  template <typename VST> void travPost(VST &);  //子树后序遍历
};

//在后续将频繁检查和判断二叉树结点的状态与性质，有时还需定位与之相关的（兄弟、叔叔等）特定节点
//为简化算法描述同时增强可读性。增加一下功能宏。

#define IsRoot(x) (!(x).parent)
#define IsLChild(x) (!IsRoot(x) && (&(x) == (x).parent->lChild))
#define IsRChild(x) (!IsRoot(x) && (&(x) == (x).parent->rChild))
#define HasParent(x) (!IsRoot(x))
#define HasLChild(x) ((x).lChild)
#define HasRChild(x) ((x).rChild)
#define HasChild(x) (HasLChild(x) || HasRChild(x))
#define HasBothChild(x) (HasLChild(x) && HasRChild(x))
#define IsLeaf(x) (!HasChild(x))

#define sibling(p)                                                             \
  (IsLChild(*(p)) ? (p)->parent->rChild : (p)->parent->lChild) //兄弟

#define uncle(x)                                                               \
  (IsLChild(*((x)->parent)) ? (x)->parent->parent->rChild                      \
                            : (x)->parent->parent->lChild)

#define FromParentTo(x)                                                        \
  IsRoot(x) ? _root : (IsLChild(x) ? (x).parent->lChild : (x).parent->rChild)
