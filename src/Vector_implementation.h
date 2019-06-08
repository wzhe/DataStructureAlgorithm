/***************************************************
 * Data Structure & Algorithm
 * wzhe ahuwang@163.com
 ***************************************************/

#pragma once

/******************************************************************************************
 * 将vector各方法的实现部分，简洁地引入vector.h
 * 效果等同于将这些实现直接汇入vector.h
 * 在export尚未被编译器支持前，如此可将定义与实现分离
 ******************************************************************************************/
#include <assert.h>
#include <stdlib.h>

#include <utility>

template <typename T>
void Vector<T>::copyFrom(T const *A, Rank lo,
                         Rank hi) { //以数组A[lo,hi)为蓝本复制向量
    elem_ = new T[capacity_ = 2 * (hi - lo)]; //分配空间
    size_ = 0;                                //规模清零
    while (lo < hi) {                         // A[lo,hi)内元素
        elem_[size_++] = A[lo++];               //逐一复制到elem[0,hi-lo);
    }
}

template <typename T>
Vector<T> &Vector<T>::operator=(Vector<T> const &V) { //重载赋值运算符
    if (elem_)
        delete elem_;           //释放原有内容
    copyFrom(V, 0, V.size()); //整体复制
    return *this;
}

template <typename T> void Vector<T>::expand() {
    if (size_ < capacity_)
        return;                           //尚未满员时，无需扩容
    if (capacity_ < DEFAULT_CAPACITY) { //不低于最小容量
        capacity_ = DEFAULT_CAPACITY;
    }
    T *oldElem = elem_;
    elem_ = new T[capacity_ <<= 1]; //容量加倍
    for (int i = 0; i < size_; i++) {
        elem_[i] = oldElem[i]; //复制原有内容,T为基本类型或已重载'=”运算符
    }
    delete[] oldElem;
}

template <typename T> void Vector<T>::shrink() { //装填因子过小时，压缩
    if (capacity_ < DEFAULT_CAPACITY << 1)
        return; //不至于收缩到DEFAULT_CAPACITY一下
    if (size_ << 2 > capacity_)
        return; //以25%为界
    T *oldElem = elem_;
    elem_ = new T[capacity_ >>= 1]; //容量减半
    for (int i = 0; i < size_; i++) {
        elem_[i] = oldElem[i]; //复制原有内容,T为基本类型或已重载'=”运算符
    }
    delete[] oldElem;
}

template <typename T> T &Vector<T>::operator[](Rank r) const {
    assert(0 <= r && r <= size_);
    return elem_[r];
}

template <typename T> void permute(Vector<T> &V) { //随机置乱算法
    for (int i = V.size(); i > 0;
         i--) {                           //自后向前  采用自后向前的原因为容易在[0,i)之间生成随机数
        std::swap(V[i - 1], V[rand() % i]); // v[i-1] 与 V[0,i)中某一元素交换
    }
}

//与permute不同，permute中借助重载操作符[],通过秩访问向量元素
//此处 直接通过下标访问内部数组的元素
template <typename T> void Vector<T>::unsort(Rank lo, Rank hi) { //区间置乱算法
    assert(0 <= lo && lo <= hi && hi <= size_);
    T *V = elem_ + lo; //将子向量elem_[lo,hi)视为另一向量V[0,hi-lo)
    for (Rank i = hi - lo; i > 0; i--) {
        std::swap(V[i - 1], V[rand() % i]); // v[i-1] 与 V[0,i)中某一元素交换
    }
}

//细微之处:
// 1.当同时又多个命中元素时，约定返回其中秩最大者。
//	故采用从后向前查找，一旦命中即可立即返回，省略掉不必要的对比
// 2.查找失败约定统一返回-1
//	不仅简化了查找失败情况的判别，也使此时的返回结果更加易于理解
//	只要假想在秩为-1处植入一个与任何对象都相等的哨兵元素，
//	当且仅当查找失败则返回该元素的秩
// 3.while循环的控制逻辑由两部分组成。
//	首先判断是否已达通配符，再判断当前元素与目标元素是否相等。
//	得益于c/c++语言中逻辑表达式的短路求值特性，不会试图访问已
//	越界的秩(-1)而出错
template <typename T> Rank Vector<T>::find(T const &e, Rank lo, Rank hi) const {
    assert(0 <= lo && lo <= hi && hi <= size_);
    while ((lo < hi--) && e != elem_[hi])
        ; //从后向前，顺序查找
    return hi;
}

// 自后向前的搬迁次序不能颠倒，否则会因为元素被覆盖而造成数据丢失
template <typename T> Rank Vector<T>::insert(Rank r, T const &e) {
    assert(0 <= r && r <= size_);
    expand();
    for (int i = size_; i > r; i--) {
        elem_[i] = elem_[i - 1]; //自后向前，后继元素顺次后移一个单元
    }
    elem_[r] = e;
    size_++;
    return r;
}

template <typename T>
int Vector<T>::remove(Rank lo, Rank hi) { //删除区间[lo,hi)
    assert(0 <= lo && lo <= hi && hi <= size_);
    if (lo == hi)
        return 0; //处于效率考虑，单独处理退化情况，例如remove(0,0)
    while (hi < size_) {
        elem_[lo++] = elem_[hi++]; //[hi,size_)顺次前移hi-lo个单元
    }
    size_ = lo; //更新规模，直接丢弃[lo, size_=hi)区间
    shrink();   //若有必要，则缩容
    return hi - lo;
}

template <typename T> T Vector<T>::remove(Rank r) { //删除向量中秩为r的元素
    assert(0 <= r && r < size_);
    T e = elem_[r];
    remove(r, r + 1);
    return e; //返回被删除的元素
}

template <typename T> int Vector<T>::deduplicate() { //无序向量去重
    int oldSize = size_;                               //记录原始规模
    Rank i = 1;                                        //从elem_[1]开始
    while (i < size_) {            //自前向后逐一考察各元素
        (find(elem_[i], 0, i) < 0) ? //在其前缀中寻找与之雷同者（至多一个）
            i++
            : remove(i); //若无雷同者，则继续考察其后继
    }
    return oldSize - size_; //向量规模的变化量，即被删除元素总数
}

// traverse()遍历的过程，实质上就是自前向后地逐一对各元素实施同一基本操作。
//而具体采用何种操作，可通过两种方式指定。前一种方式借助函数指针*visit()指定某一函数，
//该函数只有一个参数，其类型为对向量元素的引用，故通过该函数即可直接访问或修改向量元素。
//另外，也可以函数对象的形式，指定具体的遍历操作。这类对象的操作符“()”经重载之后，在
//形式上等效于一个函数接口，故此得名。
//相比较而言，后一形式的功能更强，适用范围更广。比如，函数对象的形式支持对向量元素
//的关联修改。也就是说，对各元素的修改不仅可以相互独立地进行，也可以根据某个（些）元素
//的数值相应地修改另一元素。前一形式虽也可实现这类功能，但要繁琐很多。
template <typename T>
void Vector<T>::traverse(void (*visit)(T &)) { //利用函数指针机制遍历
    for (int i = 0; i < size_; i++) {
        visit(elem_[i]);
    }
}

template <typename T>
template <typename VST>                //元素类型、操作器
void Vector<T>::traverse(VST &visit) { //利用函数对象机制遍历
    for (int i = 0; i < size_; i++) {
        visit(elem_[i]);
    }
}

template <typename T>
int Vector<T>::disordered() const { //返回向量中逆序相邻元素对的总数
    int n = 0;
    for (int i = 0; i < size_; i++) { //逐一检查size_ - 1对相邻元素
        if (elem_[i - 1] > elem_[i]) {
            n++;
        }
    }
    return n; //向量有序当且仅当n=0
}

#if 0
template <typename T>
int Vector<T>::uniquify() {						//有序向量元素剔除算法（低效版）
    int oldSize = size_;
    int i = 0;									//当前比对元素的秩，起始于首元素
    while (i < size_ - 1) {						//从前向后逐一比对各对相邻元素
        (elem_[i] == elem_[i + i]) ?
            remove(i+1) : i++;
    }
    return oldSize - size_;
}
#endif

template <typename T>
int Vector<T>::uniquify() { //有序向量元素剔除算法（高效版）
    int i = 0;
    int j = 0; //各对互异“相邻”元素的秩
    while (++j < size_) {
        if (elem_[i] != elem_[j]) { //跳过雷同者
            elem_[++i] = elem_[j]; //发现不同元素时，向前移至紧邻于前者右侧
        }
    }
    size_ = ++i;
    shrink();     //直接截除尾部元素
    return j - i; //向量规模的变化量
}

template <typename T>
Rank Vector<T>::search(T const &e, Rank lo, Rank hi) const {
    //按各50%的概率随机使用 二分查找 或 Fibnoacci 查找
    // Fibnoacci查找算法未实现
    // return (rand() % 2) ?
    //	binSearch(elem_, e, lo, hi) : fibSearch(elem_, e, lo, hi);
    return binSearch(elem_, e, lo, hi);
}

//减而治之
//在有序向量间[lo,hi)内查找元素e
//版本A,算法复杂度O(1.5 logN)
//有多个元素命中时，不能保证返回秩最大者
//查找失败时，简单返回-1，不能指示失败位置
template <typename T>
static Rank binSearch_A(T *A, T const &e, Rank lo, Rank hi) {
    while (lo < hi) { //每步迭代可能要做两次判断比较，有三个分支
        Rank mi = (lo + hi) >> 1; //以中点为轴点
        if (e < A[mi])
            hi = mi; //深入前半段[lo,hi)继续查找
        else if (A[mi] < e)
            lo = mi + 1; //深入后半段(mi, hi)继续查找
        else
            return mi; //在mi处命中
    }
    return -1; //查找失败
}

//版本B
//有多个元素命中时，不能保证返回秩最大者
//查找失败时，简单返回-1，不能指示失败位置
template <typename T>
static Rank binSearch_B(T *A, T const &e, Rank lo, Rank hi) {
    while (1 <
           hi - lo) {                  //每步迭代只要做一次判断比较，有两个分支,成功查找前不能停止
        Rank mi = (lo + hi) >> 1;        //以中点为轴点
        (e < A[mi]) ? hi = mi : lo = mi; //经比较后深入[lo,hi)或[mi,hi)
    } //出口时hi = lo + 1,查找区间仅含一个元素A[lo]
    return (e == A[lo]) ? lo : -1; //查找失败
}

//版本C
//有多个元素命中时，总能保证返回秩最大者
//查找失败时，返回失败位置
//版本C与版本B的不同
// 1.只有有效区间宽度缩短至0(而不是1)
template <typename T>
static Rank binSearch_C(T *A, T const &e, Rank lo, Rank hi) {
    while (lo < hi) {                      //每步迭代只要做一次判断比较，有两个分支,成功查找前不能停止
        Rank mi = (lo + hi) >> 1;            //以中点为轴点
        (e < A[mi]) ? hi = mi : lo = mi + 1; //经比较后深入[lo,hi)或(mi,hi)
    }
    return --lo; //查找失败
}

template <typename T> void Vector<T>::sort(Rank lo, Rank hi) {
    switch (rand() % 5) {
    case 1:
        bubbleSort(lo, hi);
        break;
    case 2:
        selectionSort(lo, hi);
        break;
    case 3:
        mergeSort(lo, hi);
        break;
    case 4:
        heapSort(lo, hi);
        break;
    default:
        quickSort(lo, hi);
        break;
    }
}

template <typename T> bool Vector<T>::bubble(Rank lo, Rank hi) {
    bool Sorted = true;
    while (++lo < hi) {
        if (elem_[lo - 1] > elem_[lo]) {
            Sorted = false;
            std::swap(elem_[lo - 1], elem_[lo]);
        }
    }
    return Sorted;
}

template <typename T> void Vector<T>::bubbleSort(Rank lo, Rank hi) {
    while (!bubble(lo, hi--))
        ;
}

template <typename T> void Vector<T>::mergeSort(Rank lo, Rank hi) {
    if (hi - lo < 2)
        return;
    int mi = (lo + hi) >> 1;

    //分别对前、后半段排序，然后归并
    mergeSort(lo, mi);
    mergeSort(mi, hi);
    merge(lo, mi, hi);
}

template <typename T> void Vector<T>::merge(Rank lo, Rank mi, Rank hi) {
    T *A = elem_ + lo; //合并后的向量A[0, hi-lo) = elem_[lo, hi)
    int lb = mi - lo;
    T *B = new T[lb];
    for (Rank i = 0; i < lb; B[i] = A[i++])
        ; //复制前子向量B[0,lo) = elem_[lo, hi)
    int lc = hi - mi;
    T *C = elem_ + mi;
    //将B[j]和C[k]中小者续至Am末尾
    for (Rank i = 0, j = 0, k = 0; (j < lb) || (k < lc);) {
        if ((j < lb) && (!(k < lc) || (B[j] <= C[k])))
            A[i++] = B[j++];
        if ((k < lc) && (!(j < lb) || (C[k] < B[j])))
            A[i++] = C[k++];
    }
    delete[] B; //释放临时空间B
}
