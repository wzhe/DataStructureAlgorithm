/***************************************************
 * Data Structure & Algorithm
 * wzhe ahuwang@163.com
***************************************************/

#pragma once

typedef int Rank;	//秩
#define DEFAULT_CAPACITY 7 	//默认初始容量（实际使用中可设置更大）

template <typename T> class Vector {
protected:
	Rank size_;			//规模
	int capacity_;		//容量
	T* elem_;			//数据区

	void copyFrom(T const* A, Rank lo, Rank hi);	//复制数组区间[lo，hi)
	void expand();	//空间不足时扩容
	void shrink();	//装填因子过小时压缩
	bool bubble(Rank lo, Rank hi);	//扫描交换
	void bubbleSort(Rank lo, Rank hi);	//起泡排序算法
	Rank max(Rank lo, Rank hi);	//选取最大元素
	void selectionSort(Rank lo, Rank hi);	//选择排序算法
	void merge(Rank lo, Rank mi, Rank hi);	//归并算法
	void mergeSort(Rank lo, Rank hi);		//归并排序算法
	Rank partition(Rank lo, Rank hi);		//轴点构造算法
	void quickSort(Rank lo, Rank hi);		//快速排序算法
	void heapSort(Rank lo, Rank hi);		//堆排序(结合完全堆理解)

public:
	//构造函数
	Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0)	//容量为c、规模为s、所有元素初始化为v
	{
		elem_ = new T[capacity_ = c];
		for ( size_ = 0; size_ < s; elem_[size_++] = v);
	}
	Vector(T const* A, Rank lo, Rank hi) { copyFrom(A, lo, hi); } 	//数组区间复制
	Vector(T const* A, Rank n) { copyFrom(A, 0, n); } 				//数组整体复制
	Vector(Vector<T> const& V, Rank lo, Rank hi) { copyFrom(V.elem_, lo, hi); }	//向量区间复制
	Vector(Vector<T> const& V) { copyFrom(V.elem_, 0, V.size_); }	//向量整体复制

	//析构函数
	~Vector() { delete [] elem_; } //释放内部空间

	//只读访问接口
	Rank size() const { return size_; } //规模
	bool empty() const { return !size_; }	//判空
	int disordered() const;			//判断向量是否已经有序
	Rank find(T const& e, Rank lo, Rank hi) const;	//无序向量区间查找
	Rank find(T const& e) const { return find(e, 0, size_); }
	Rank search(T const& e, Rank lo, Rank hi) const;	//有序向量区间查找
	Rank search(T const& e) const { return search(e, 0, size_); }

	//可写访问接口
	T& operator[](Rank r) const;	//重载下标操作符
	Vector<T> & operator=(Vector<T> const&);	//重载赋值操作符，以便直接克隆向量
	T remove(Rank r); 				//删除秩为r的元素
	int remove(Rank lo, Rank hi); 	//删除在区间[lo，hi）之间的元素
	Rank insert(Rank r, T const& e);	//插入元素
	Rank insert(T const& e) { return insert(size_, e); }	//默认作为末元素插入
	void sort(Rank lo, Rank hi);	//对[lo,hi)排序
	void sort() { sort(0, size_); } //整体排序
	void unsort(Rank lo, Rank hi);	//对[lo,hi)置乱
	void unsort() { unsort(0, size_); } 
	int deduplicate();	//无序去重
	int uniquify();		//有序去重

	//遍历
	void traverse(void (*)(T&));	//使用函数指针遍历，只读或局部性修改
	template <typename VST> void traverse(VST&); //使用函数对象遍历，可全局修改
}; // Vector

#include "vector_implementation.h"


