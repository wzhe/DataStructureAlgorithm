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

template <typename T> BinNodePosi(T) BinNode<T>::insertAsLC(T const &e) {
    return lChild = new BinNode<T>(e, this);
}

template <typename T> BinNodePosi(T) BinNode<T>::insertAsRC(T const &e) {
    return rChild = new BinNode<T>(e, this);
}

//先序遍历（递归版）
template <typename T, typename VST>
void travPre_R(BinNodePosi(T) x, VST &visit) {
    if (!x)
        return;
    visit(x->data);
    travPre_R(x->lChild);
    travPre_R(x->rChild);
}

//后序遍历（递归版）
template <typename T, typename VST>
void travPost_R(BinNodePosi(T) x, VST &visit) {
    if (!x)
        return;
    travPre_R(x->lChild);
    travPre_R(x->rChild);
    visit(x->data);
}

//中序遍历（递归版）
template <typename T, typename VST>
void travIn_R(BinNodePosi(T) x, VST &visit) {
    if (!x)
        return;
    travPre_R(x->lChild);
    visit(x->data);
    travPre_R(x->rChild);
}

#include "Stack.h"
template <typename T, typename VST>
void travPre_I1(BinNodePosi(T) x, VST &visit) {
    Stack<BinNodePosi(T)> S; //辅助栈
    if (x) {
        S.push(x);
    }
    while (!S.empty()) {
        x = S.pop();
        visit(x->data);
        if (HasRChild(*x)) {
            S.push(x->rChild);
        }
        if (HasLChild(*x)) {
            S.push(x->lChild);
        }
    }
}

template <typename T, typename VST>
static void visitAlongLeftBranch(BinNodePosi(T) x, VST &visit,
                                 Stack<BinNodePosi(T)> &S) {
    while (x) {
        visit(x->data);
        if (HasRChild(*x)) {
            S.push(x->rChild);
        }
        x = x->lChild;
    }
}
template <typename T, typename VST>
void travPre_I2(BinNodePosi(T) x, VST &visit) {
    Stack<BinNodePosi(T)> S;
    while (true) {
        visitAlongLeftBranch(x, visit, S);
        if (S.empty())
            break;
        x = S.pop();
    }
}

template <typename T, typename VST>
static void goAlongLeftBranch(BinNodePosi(T) x, VST &visit,
                              Stack<BinNodePosi(T)> &S) {
    while (x) {
        S.push(x);
        x = x->lChild;
    }
}
template <typename T, typename VST>
void travIn_I1(BinNodePosi(T) x, VST &visit) {
    Stack<BinNodePosi(T)> S;
    while (true) {
        goAlongLeftBranch(x, visit, S);
        if (S.empty())
            break;
        x = S.pop();
        visit(x->data);
        x = x->rChild;
    }
}

template <typename T> BinNodePosi(T) BinNode<T>::succ() {
    BinNodePosi(T) s = this; //记录后继的临时变量
    if (rChild) {
        s = rChild;
        while (HasLChild(*s)) {
            s = s->lChild;
        }
    } else {
        while (IsRChild(*s)) {
            s = s->parent;
        }              //逆向地沿向右分支，不断朝左上方移动
        s = s->parent; //最后再朝右上方移动一步，即可抵达直接后继
    }
    return s;
}

// travIn_I1的等价形式。
template <typename T, typename VST>
void travIn_I2(BinNodePosi(T) x, VST &visit) {
    Stack<BinNodePosi(T)> S; //辅助栈
    while (true) {
        if (x) {
            S.push(x);
            x = x->lChild;
        } else if (!S.empty()) {
            x = S.pop();
            visit(x->data);
            x = x->rChild;
        } else {
            break;
        }
    }
}

//借助版本2和succ接口实现的版本3
//不需要辅助栈，仅需O(1)的辅助空间
template <typename T, typename VST>
void travIn_I3(BinNodePosi(T) x, VST &visit) {
    bool backtrack = false; //前一步是刚从右子树回溯
    while (true) {
        if (!backtrack && HasLChild(*x)) { //若有左子树且不是刚刚回溯，则
            x = x->lChild;                   //深入遍历左子树
        } else { //否则--无左子树或刚刚回溯(相当于无左子树）
            visit(x->data);      //访问该节点
            if (HasRChild(*x)) { //若其右树非空，则
                x = x->rChild;     //深入右子树继续遍历
                backtrack = false; //并关闭回溯标识
            } else {             //若右树空，则
                if (!(x = x->succ()))
                    break; //回溯。（含抵达末节点时的退出）
                backtrack = true;
            }
        }
    }
}

template <typename T> static void gotoHLVFL(Stack<BinNodePosi(T)> &S) {
    while (BinNodePosi(T) x = S.top()) {
        if (HasLChild(*x)) { //尽可能左
            if (HasRChild(*x)) {
                S.push(x->rChild);
            } //若有右孩子，优先入栈
            S.push(x->lChild);
        } else {             //实不得已
            S.push(x->rChild); //才向右
        }
    }
    S.pop(); //返回之前，弹出栈顶的空节点
}

template <typename T, typename VST>
void travPost_I(BinNodePosi(T) x, VST &visit) {
    Stack<BinNodePosi(T)> S;
    if (x) {
        S.push(x);
    }
    while (!S.empty()) {
        if (S.top() != x->parent) { //若栈顶非当前节点之父（则必为其右兄）
            gotoHLVFL(S); //以其右兄为根之子树，找到HLVFL（相当于递归深入其中)
        }
        x = S.pop();
        visit(x->data);
    }
}

#include "Queue.h"
template <typename T>
template <typename VST>
void BinNode<T>::travLevel(VST &visit) {
    Queue<BinNodePosi(T)> Q; //辅助队列
    Q.enqueue(this);         //根节点入队
    while (!Q.empty()) {
        BinNodePosi(T) x = Q.dequeue();
        visit(x->data);
        if (HasLChild(*x)) {
            Q.enqueue(x->lChild);
        }
        if (HasRChild(*x)) {
            Q.enqueue(x->rChild);
        }
    }
}
