/***************************************************
 * Data Structure & Algorithm
 * wzhe ahuwang@163.com
***************************************************/

#pragma once

#include "listNode.h"
typedef int Rank

template <typename T> class List {
private:
	int size_;						//规模
	ListNodePosi(T) hearder;		//头哨兵
	ListNodePosi(T) trailer;		//尾哨兵

protected:
	void init();					//列表创建初始化
	int clear();					//清除所有节点
	void copyNodes(ListNodePosi(T), int);	//复制列表中自位置p起的n项
	void merge(ListNodePosi(T)&, int, list<T>&, ListNodePosi(T), int);
	void mergeSort(ListNodePosi(T)&, int);	//对从p开始的连续n个节点归并排序
	void selectionSort(ListNodePosi(T), int);	//对从p开始连续的n个节点选择排序
	void insertionSort(ListNodePosi(T), int);	//对从p开始的n个节点插入排序

public:
	//构造函数
	List() { init(); }			//默认
	List(List<T> const& L);		//整体复制列表L
	List(List<T> const& L, Rank r, int n);	//复制列表L中自第r项起的n项
	List(ListNodePosi(T) p, int n);			//复制列表中自位置p起的n项

	//析构函数
	~List();					//释放（包含头、尾哨兵在内的）所有节点

	//只读访问接口
	Rank size() const { return size_; }
	bool empty() const { return !size_; }
	T& operator[](int r) const;			//重载，支持循秩访问（效率低）
	ListNodePosi(T) first() const { return header->succ; }
	ListNodePosi(T) last() const { return trailer->pred; }
	bool valid(ListNodePosi(T) p)		//判断位置p是否对外合法
	{ return p && (header != p) && (trailer != p); }
	int disordered() const;				//判断列表是否有序
	ListNodePosi(T) find(T const& e) const	//无序列表查找
	{ return find(e, size_, trailer); }
	ListNodePosi(T) find(T const& e, int n, ListNodePosi(T) p) const;
	ListNodePosi(T) search(T const& e) const	//有序区间查找
	{ return search(e, size_, trailer); }
	ListNodePosi(T) search(T const& e, int n, ListNodePosi(T) p) const;
	ListNodePosi(T) selectMax(ListNodePosi(T) p, int n);	//在p及其n-1个后继中选出最大者
	ListNodePosi(T) selectMax()					//选出整体最大者
	{ return selectMax(header->succ, size_); }

	//可写访问接口
	ListNodePosi(T) insertAsFirst(T const& e);	//将e当作首节点插入
	ListNodePosi(T) insertAsLast(T const& e);	//将e当作末节点插入
	ListNodePosi(T) insertBefore(ListNodePosi(T) p, T const& e);
	ListNodePosi(T) insertAfter(ListNodePosi(T) p, T const& e);
	T remove(ListNodePosi(T) p);				//删除合法位置p处节点，返回被删除节点
	void merge(List<T>& L)						//全列表归并
	{ merge(first(), size_, L, L.first(), L.size_); }
	void sort(ListNodePosi(T) p, int n);		//列表区间排序
	void sort()
	{ sort(first(), size_); }
	int deduplicate();							//无序去重
	int uniquify();								//有序去重
	void reverse();								//前后倒置

	//遍历
	void traverse(void (*)(T&));
	template <typename VST> void traverse(VST&);
};	//List

#include "list_implementation.h"

