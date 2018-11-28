/***************************************************
 * Data Structure & Algorithm
 * wzhe ahuwang@163.com
 ***************************************************/

#pragma once

 //列表节点位置
#define ListNodePosi(T) ListNode<T>*

//列表节点模板类(以双向链表形式实现)
template <typename T> struct ListNode {
    T data;               //数据
    ListNodePosi(T) pred; //前驱
    ListNodePosi(T) succ; //后继

    //构造函数
    ListNode() {} //针对header和trailer的构造
    ListNode(T e, ListNodePosi(T) p = nullptr, ListNodePosi(T) s = nullptr)
        : data(e), pred(p), succ(s) {} //默认构造

    //操作接口
    ListNodePosi(T) insertAsPred(T const &e); //紧靠当前节点之前插入
    ListNodePosi(T) insertAsSucc(T const &e); //紧靠当前节点之后插入
};

template <typename T> ListNodePosi(T) ListNode<T>::insertAsPred(T const &e) {
    ListNodePosi(T) x = new ListNode<T>(e, pred, this); //创建新节点
    pred->succ = x;
    pred = x;
    return x;
}

template <typename T> ListNodePosi(T) ListNode<T>::insertAsSucc(T const &e) {
    ListNodePosi(T) x = new ListNode<T>(e, this, succ); //创建新节点
    succ->pred = x;
    succ = x;
    return x;
}
