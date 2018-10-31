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
BinNodePosi(T) & search(const T& e)
{
	return searchIn( root_, e, hot_ = NULL);
}

template <typename T>
static void removeAt(BinNodePosi(T) & x, BinNodePosi(T) & hot)
{
	BinNodePosi(T) w = x;
	BinNodePosi(T) succ = NULL;
	if (!HasLChild(*x))
		succ = x = x->rChild;
	else if (!HasRChild(*x))
		succ = x = x->lChild;
	else {
		w = w->succ();
		swap(x->data, w->data);
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
bool BST::remove(const T& e)
{
	BinNodePosi(T) & x = search(e);
	if (!x) return false;
	removeAt(x, hot_);
	size--;
	updateHeightAbove(hot_);
	return true;
}

template<typename T>
BinNodePosi(T) BST::connect34(
		BinNodePosi(T), BinNodePosi(T), BinNodePosi(T),
		BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T) )
{
}

template<typename T>
BinNodePosi(T) BST::rotateAt( BinNodePosi(T) x)
{
}

template<typename T>
BinNodePosi(T) insert(const T& e)
{
}
