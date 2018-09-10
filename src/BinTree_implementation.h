/***************************************************
 * Data Structure & Algorithm
 * wzhe ahuwang@163.com
***************************************************/

#pragma once

template <typename T>
int BinTree<T>::updateHeight(BinNodePosi(T) x)
{
	return x->height = 1 + max(stature(x->lChild), stature(x->rChild));
}

template <typename T>
void BinTree<T>::updateHeightAbove(BinNodePosi(T) x)
{
	while(x) { 
		updateHeight(x);
		x = x->parent;
	}		//可优化：一旦高度未变，即可终止
}

//二叉树子树接入算法：将S当作节点x的左子树接入，S本身置空
template <typename T>
BinNodePosi(T) BinTree<T>::attachAsLC(BinNodePosi(T) x, BinTree<T>* &S)
{
	if (x->lChild = S->root_) {
		x->lChild->parent = x;	//接入
	}
	size_ += S->size_;
	updateHeightAbove(x);
	S->root_ = NULL;
	S->size_ = 0;
	release(S);
	S = NULL;
	return x;
}


//二叉树子树接入算法：将S当作节点x的右子树接入，S本身置空
template <typename T>
BinNodePosi(T) BinTree<T>::attachAsRC(BinNodePosi(T) x, BinTree<T>* &S)
{
	if (x->rChild = S->root_) {
		x->rChild->parent = x;	//接入
	}
	size_ += S->size_;
	updateHeightAbove(x);
	S->root_ = NULL;
	S->size_ = 0;
	release(S);
	S = NULL;
	return x;
}

//删除二叉树中位置x处的节点及其后代，返回被删除节点的个数
template <typename T>
int BinTree<T>::remove(BinNodePosi(T) x)
{
	FromParentTo(*x) = NULL;	//切断来自父节点的指针
	updateHeightAbove(x->parent);	//更新祖先高度
	int n = removeAt(x);
	size_ -= n;
	return n;
}

template <typename T>
static int removeAt(BinNodePosi(T) x)
{
	if (!x) return 0;	//递归基：空树
	int n = 1 + removeAt(x->lChild) + removeAt(x->rChild);	//递归释放左右子树
	release(x->data);
	release(x);
	return ;
}
