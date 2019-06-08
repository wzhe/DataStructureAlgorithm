/***************************************************
 * Data Structure & Algorithm
 * wzhe ahuwang@163.com
 ***************************************************/

template<typename T>
static BinNodePosi(T) & searchIn (BinNodePosi(T)& v, const T& e, BinNodePosi(T) & hot)
{
    if (!v || (e == v->data)) return v;
    hot = v;
    return searchIn((( e < v->data ) ? v->lChild : v->rChild), e, hot);
}

template<typename T>
BinNodePosi(T) & BST<T>::search(const T& e)
{
    return searchIn(this->root_, e, hot_ = nullptr);
}

template <typename T>
static BinNodePosi(T) removeAt(BinNodePosi(T) & x, BinNodePosi(T) & hot)
{
    BinNodePosi(T) w = x;
    BinNodePosi(T) succ = nullptr;
    if (!HasLChild(*x))
        succ = x = x->rChild;
    else if (!HasRChild(*x))
        succ = x = x->lChild;
    else {
        w = w->succ();
        std::swap(x->data, w->data);
        BinNodePosi(T) u = w->parent;
        ((u == x) ? u->rChild : u->lChild) = succ = w->rChild;
    }
    hot = w->parent;
    if (succ) succ->parent = hot;
    release(w->data);
    release(w);
    return succ;
}

template<typename T>
bool BST<T>::remove(const T& e)
{
    BinNodePosi(T) & x = search(e);
    if (!x) return false;
    removeAt(x, hot_);
    this->size_--;
    this->updateHeightAbove(hot_);
    return true;
}

template<typename T>
BinNodePosi(T) BST<T>::insert(const T& e)
{
    BinNodePosi(T) & x = search(e);
    if (x) return x; //不存在时才插入
    x = new BinNode<T>(e, hot_);
    this->size_++;
    this->updateHeightAbove(x);
    return x;
}

/******************************************************************************************
* 按照“3 + 4”结构联接3个节点及其四棵子树，返回重组之后的局部子树根节点位置（即b）
* 子树根节点与上层节点之间癿双向联接，均须由上层调用者完成
* 可用于AVL和RedBlack局部平衡调整
******************************************************************************************/
template<typename T> BinNodePosi(T) BST<T>::connect34(
    BinNodePosi(T) a, BinNodePosi(T) b, BinNodePosi(T) c,
    BinNodePosi(T) T0, BinNodePosi(T) T1, BinNodePosi(T) T2, BinNodePosi(T) T3
) {
    a->lChild = T0; if (T0) T0->parent = a;
    a->rChild = T1; if (T1) T1->parent = a; this->updateHeight(a);

    c->lChild = T2; if (T2) T2->parent = c;
    c->rChild = T3; if (T3) T3->parent = c; this->updateHeight(c);

    b->lChild = a; a->parent = b;
    b->rChild = c; c->parent = b; this->updateHeight(b);
    return b;       //返回子树的根节点
}

/******************************************************************************************
* BST节点旋转变换统一算法（3节点 + 4子树），返回调整之后局部子树根节点的位置
* 注意：尽管子树根会正确指向上层节点（如果存在），但反向的联接须由上层函数完成
******************************************************************************************/
template <typename T> BinNodePosi(T) BST<T>::rotateAt(BinNodePosi(T) v) { //v为非空癿孙辈节点
	BinNodePosi(T) p = v->parent; BinNodePosi(T) g = p->parent; //规v、p和g相对位置分四种情况
	if (IsLChild(*p)) /* zig */
		if (IsLChild(*v)) { /* zig-zig */
			p->parent = g->parent; //向上联接
			return connect34(v, p, g, v->lChild, v->rChild, p->rChild, g->rChild);
		} else { /* zig-zag */
			v->parent = g->parent; //向上联接
			return connect34(p, v, g, p->lChild, v->lChild, v->rChild, g->rChild);
		}
		else /* zag */
			if (IsRChild(*v)) { /* zag-zag */
				p->parent = g->parent; //向上联接
				return connect34(g, p, v, g->lChild, p->lChild, v->lChild, v->rChild);
			} else { /* zag-zig */
				v->parent = g->parent; //向上联接
				return connect34(g, v, p, g->lChild, v->lChild, v->rChild, p->rChild);
			}
}

