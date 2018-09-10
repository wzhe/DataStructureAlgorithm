/***************************************************
 * Data Structure & Algorithm
 * wzhe ahuwang@163.com
***************************************************/

#pragma once

//列表初始化,在创建列表时统一调用
//链表对外的有效部分初始为空，头尾哨兵对外不可见
//此后引入的新节点都将陆续插入这一对哨兵之间
template <typename T>
void List<T>::init()
{
	header = new ListNode<T>;
	trailer = new ListNode<T>;
	header->succ = trailer; header->pred = NULL;
	trailer->pred = header; trailer->succ = NULL;
	size_ = 0;
}

//重载下标操作符，以通过秩直接访问列表节点（虽方便，效率低，慎用）
//O(r+1)复杂度。诚然，当r大于n/2时，从trailer出发沿pred指针逆行查找
//可在一定程度上减少迭代次数。但就总体的平均效率而言，这一改进并无实质意义
template <typename T>
T& List<T>::opertaor[](int r) const
{
	ListNodePosi(T) p = first();	//从首节点出发
	while (0 < r--) p = p->succ;	//顺数第r个节点
	return p->data;					//目标节点,返回其中所存元素
}

//在无序列表内节点p(可能是tariler)的n个（真）前缀中，找到等于e的最后者
template <typename T>
ListNodePosi(T) List<T>::find(T const& e, int n, ListNodePosi(T) p) const
{
	while (0 < n--) {
		if ( e == (p = p->pred)->data) {
			return p;
		}
	}
	return NULL;	//p越出左边界意味着区间内不含e，查找失败
}


template <typename T>
ListNodePosi(T) List<T>::insertAsFirst(T const& e)
{
	size_++;
	return header->insertAsSucc(e);
}

template <typename T>
ListNodePosi(T) List<T>::insertAsLast(T const& e)
{
	size_++;
	return trailer->insertAsPred(e);
}

template <typename T>
ListNodePosi(T) List<T>::insertBefore(ListNodePosi(T) p, T const& e)
{
	size_++;
	return p->insertAsPred(e);
}

template <typename T>
ListNodePosi(t) List<T>::insertAfter(ListNodePosi(T) p, T const& e)
{
	size_++;
	return p->insertAsSucc(e);
}

template <typename T>
void List<T>:: copyNodes(ListNodePosi(T) p, int n)
{
	init();
	while (n--) {
		insertAsLast(p->data);
		p = p->succ;
	}
}

template <typename T>
List<T>::List(ListNodePosi(T) p, int n)
{
	copyNodes(p, n);
}

template <typename T>
List<T>::List(List<T> const& L)
{
	copyNodes(L.first(), L.size_);
}

template <typename T>
List<T>::List(List<T> const& L, int r, int n)
{
	copyNodes(L[r], n);
}

template <typename T>
T List<T>::remove(ListNodePosi(T) p)
{
	T e = p->data;
	p->pred->succ = p->succ;
	p->succ->pred = p->pred;
	delete p;
	size_--;
	return e;
}

template <typename T>
List<T>::~List()
{
	clear();
	delete header;
	delete tariler;
}

template <typename T>
int List<T>::clear()
{
	int oldSize = size_;
	while ( 0 < size_) {
		remove(header->succ);	//反复删除首节点，直至列表为空
	}
	return oldSize;
}

template <typename T>
int List<T>::deduplicate()
{
	if (size_ < 2) return 0;	//平凡列表自然无重复
	int oldSize = size_;
	ListNodePosi(T) p = header;
	Rank r = 0;
	while (trailer != (p = p->succ)) {
		ListNodePosi(T) q = find(p->data, r, q);
		q ? remove(q) : r++;
	}
	return oldSize - size_;
}

template <typename T>
void List<T>::traverse(void (*visit)(T&))
{
	for (ListNodePosi(T) p = header->succ; p != trailer; p = p->succ) {
		visit(p->data);
	}
}

template <typename T> template <typename VST>
void List<T>::traverse(VST& visit)
{
	for (ListNodePosi(T) p = header->succ; p != trailer; p = p->succ) {
		visit(p->data);
	}
}

template <typename T>
int List<T>::uniquify()
{
	if (size_ < 2) return 0;		//平凡列表自然无重复
	int oldSize  = size_;
	//依次指向紧邻的各队节点
	ListNodePosi(T) p;
	ListNodePosi(T) q;
	for (p = header, q = p->succ; trailer != q; p = q, q = q->succ) {
		if (p->data = q->data) { remove(q); q = p; }
	}
	return oldSize - size_;
}

template <typename T>
ListNodePosi(T) List<T>::search(T const& e, int n, ListNodePosi(T) p) const 
{
	while (0 <= n--) {							//对于p的n个前驱，从右往左逐个比较
		if (((p = p->pred)->data) < e) break;	//直至命中、数值越界或范围越界
	}
	return p;				//失败时返回区间左边界（可能是header），可通过valid()判断成功与否
}

template <typename T>
void List<T>::sort(ListNodePosi(T) p, int n) {
	switch (rand() % 3) {
		case 1: insertionSort(p, n); break;		//插入排序
		case 2: selectionSort(p, n); break;		//选择排序
		default: mergeSort(p, n); break;		//归并排序
	}
}

template <typename T>
void List<T>::insertionSort(ListNodePosi(T) p, int n)
{
	for (int r = 0; r < n; r++) {
		insertAsSucc(search(p->data, r, p), p->data);
		p = p->succ;
		remove(p->pred);
	}
}

template <typename T>
void List<T>::selectionSort(ListNodePosi(T) p, int n)
{
	ListNodePosi(T) head = p->pred;
	ListNodePosi(T) tail = p;
	for (int i = 0; i < n; i++) { tail = tail->succ; }
	while (1 < n) {
		ListNodePosi(T) max = selectMax(head->succ, n);
		insertBefore(tail, remove(max));
		tail = tail->pred;
		n--;
	}
}

template <typename T>
ListNodePosi(T) List<T>::selectMax(ListNodePosi(T) p, int n)
{
	ListNodePosi(T) max = p;
	for (ListNodePosi(T) cur = p; 1 < n; n--) {
		if (!((cur = cur->succ)->data < max->data)) {
			max = cur;
		}
	}
	return max;
}

//有序列表归并：当前列表中自p起的n个元素，与列表L中自q起的m个元素归并
template <typename T>
void List<T>::merge(ListNodePosi(T)& p, int n, List<T>& L, ListNodePosi(T) q, int m)
{
	ListNodePosi(T) pp = p->pred;	//借助前驱，以便返回
	while (0 < m) {					//在q尚未移除区间之前
		if ((0 < n) && (p->data <= q->data)) {	//若p仍在区间内且v(p) <= v(q)
			if (q == (p = p->succ)) {			//将p替换为其直接后继(等效于将p归入合并的列表)
				break;
			}
			n--;
		} else {					//若p已超出右界或v(q) < v(p)
			insertBefore(p, L.remove((q = q->succ)->pred));		//将q转移至p之前
			m--;
		}
	}
	p = pp->succ;					//确定归并后区间的（新）起点
}

//对起始于位置p的n个元素排序
template <typename T>
void List<T>::mergerSort(ListNodePosi(T) p, int n)
{
	if (n < 2) return;
	int m = n >> 1;	//以中点为界
	ListNodePost(T) q = p;
	for (int i = 0; i < m; i++) {
		q = q->succ;
	}
	mergeSort(p, m);		//对前、后子列表分别排序
	mergeSort(q, n-m);		
	merge(p, m, *this, q, n-m);	//归并
}

