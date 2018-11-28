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
BinNodePosi(T) BST<T>::connect34(
    BinNodePosi(T), BinNodePosi(T), BinNodePosi(T),
    BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T) )
{
}

template<typename T>
BinNodePosi(T) BST<T>::rotateAt( BinNodePosi(T) x)
{
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
