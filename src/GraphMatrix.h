/***************************************************
 * Data Structure & Algorithm
 * wzhe ahuwang@163.com
 ***************************************************/

#pragma once

#include "Graph.h"
#include "Vector.h"

template <typename Tv>
struct Vertex {
    Tv data;
    int inDegree, outDegree;
    VStatus status;
    int dTime, fTime;
    int parent;
    int priority;
    Vertex(Tv const& d = (Tv)0)
        : data(d),
          inDegree(0),
          outDegree(0),
          status(UNDISCOVERED),
          dTime(-1),
          fTime(-1),
          parent(-1),
          priority(INT_MAX) {}
};

template <typename Te>
struct Edge {
    Te data;
    int weight;
    EStatus status;
    Edge(Te const& d, int w) : data(d), weight(w), status(UNDETERMINED) {}
};

template <typename Tv, typename Te>
class GraphMatrix : public Graph<Tv, Te> {
private:
    Vector<Vertex<Tv>> V;	 //顶点集
    Vector<Vector<Edge<Te>*>> E;  //边集（邻接矩阵）

public:
    GraphMatrix() { n = e = 0; }  //构造
    ~GraphMatrix() {
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++) delete E[j][k];
    }

    //顶点的基本操作：查询第i个顶点(0 <= i < n)
    virtual Tv& vertex(int i) { return V[i].data; }
    virtual int inDegree(int i) { return V[i].inDegree; }
    virtual int outDegree(int i) { return V[i].outDegree; }
    virtual int firstNbr(int i) { return nextNbr(i, n); }
    virtual int nextNbr(int i, int j)  //相对于顶点j的下一邻接顶点
    {
        while ((-1 < j) && (!exists(i, --j)))
            ;
        return j;
    }  //逆向线性试探
    virtual VStatus& status(int i) { return V[i].status; }
    virtual int& dTime(int i) { return V[i].dTime; }
    virtual int& fTime(int i) { return V[i].fTime; }
    virtual int& parent(int i) { return V[i].parent; }
    virtual int& priority(int i) { return V[i].priority; }
};
