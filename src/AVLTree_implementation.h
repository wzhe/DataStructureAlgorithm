/***************************************************
 * Data Structure & Algorithm
 * wzhe ahuwang@163.com
 ***************************************************/

//将关键码e插入AVL树中
template<typename T> BinNodePosi(T) AVL<T>::insert(const T& e) {
    BinNodePosi(T) & x = this->search(e); if (x) return x;    //确人目标节点不存在(留意对hot_的设置)
    x = new BinNode<T>(e, this->hot_); this->size_++;               //创建节点x，(此后，其父hot_可能增高，祖父可能失衡)
    for (BinNodePosi(T) g = this->hot_; g; g = g->parent) {   //从x之父向上出发，逐层检查各代祖先g
        if (!AvlBalanced(*g)) { //一旦发现失衡，则采用“3+4”算法使之复衡
            FromParentTo(*g) = this->rotateAt(tallerChild(tallerChild(g)));
            break;
        } else {        //否则（g依然平衡），只需简单地更新其高度
            this->updateHeight(g);
        }
    }   //至多只需要一次调整；若果真做过调整，则全树高度必然复原
    return x;
}

//从AVL树中删除关键码e
template<typename T> bool AVL<T>::remove(const T& e) {
    BinNodePosi(T) & x = this->search(e); if (!x) return false;    //确人目标节点不存在(留意对hot_的设置)
    removeAt(x, this->hot_); this->size_--;     //先按BST的规则删除(此后，原节点之父hot_及其祖先均可能失衡)
    for (BinNodePosi(T) g = this->hot_; g; g = g->parent) {   //从x之父向上出发，逐层检查各代祖先g
        if (!AvlBalanced(*g)) { //一旦发现失衡，则采用“3+4”算法使之复衡
            FromParentTo(*g) = this->rotateAt(tallerChild(tallerChild(g)));
        } 
        this->updateHeight(g);
    }   //可能需要做Omega(longn)调整--无论是否做过调整,全树高度均可能降低
    return true;
}