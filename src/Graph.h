/***************************************************
 * Data Structure & Algorithm
 * wzhe ahuwang@163.com
 ***************************************************/

#pragma once

#include "Stack.h"

typedef enum { UNDISCOVERED, DISCOVERED, VISITED } VStatus; //顶点状态
typedef enum { UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD } EStatus; //边状态

template <typename Tv, typename Te> class Graph {
private:
    void reset() {
        for (int i = 0; i < n; i++) {
            status(i) = UNDISCOVERED;
            dTime(i) = fTime(i) = -1;
            parent(i) = -1;
            priority(I) = INT_MAX;
            for (int j = 0; j < n; j++) {
                if (exists(i, j)) {
                    status(i, j) = UNDETERMINED;
                }
            }
        }
    }

    void BFS(int, int &);               //（连通域）广度优先搜素算法
    void DFS(int, int &);               //（连通域）深度优先搜素算法
    void BCC(int, int &, Stack<int> &); //（连通域）基于DFS的双连通分量分解算法
    bool TSort(int, int &, STack<Tv> *); //（连通域）基于DFS的拓扑排序算法

    template <typename PU> void PFS(int, PU); //（连通域）优先级搜索框架

public:
    //顶点
    int n;                              //顶点总数
    virtual int insert(Tv const &) = 0; //插入顶点，返回编号
    virtual Tv remove(int) = 0; //删除顶点及其关联边，返回该顶点信息
    virtual Tv &vertex(int) = 0;   //顶点v的数据（该顶点的确存在)
    virtual int inDegree(int) = 0; //顶点v的入度
    virtual int outDegree(int) = 0;
    virtual int firstNbr(int) = 0;    //顶点v的首个邻接顶点
    virtual int nextNbr(int) = 0;     //顶点v的下一个邻接顶点
    virtual VStatus &status(int) = 0; //顶点的状态
    virtual int &dTime(int) = 0;      //顶点的时间标签dTime
    virtual int &fTime(int) = 0;      //顶点的时间标签fTime
    virtual int &parent(int) = 0;     //顶点v在遍历树中的父亲
    virtual int &priority(int) = 0;   //顶点v在遍历树中的优先级

    //边
    int e;                             //边的总数
    virtual bool exists(int, int) = 0; //边（v，u）是否存在
    virtual void insert(Te const &, int, int,
                        int) = 0; //在顶点v和u之间插入权重为w的边e
    virtual Te remove(int, int) = 0; //移除顶点v和u之间的边e，返回该边胡信息
    virtual EStatus &status(int, int) = 0; //边（v，u）的状态
    virtual Te &edge(int, int) = 0;        //边(v,u)的数据
    virtual int &weight(int, int) = 0;     //边(v,u)的权重

<<<<<<< HEAD
  //算法
  void bfs(int);
  void dfs(int);
  void bcc(int);
  Stack<Tv> *tSort(int);
  void prim(int);                           //最小支撑树Prim算法
  void dijkstra(int);                       //最短路径Dijkstra算法
  template <typename PU> void pfs(int, PU); //优先搜索框架
};

template <typename Tv, typename Te>
void Graph<Tv, Te>::bfs(int s) {
	reset();
	int clock = 0;
	int v = s;
	do {
		if (UNDETERMINED == status(v)) {
			BFS(v, clock);
		}
	}while (s != (v = (++v%n)));
}
template <typename Tv, typename Te>
void Graph<Tv, Te>::BFS(int v, int& clock) {
	Queue<int> Q;
	status(v) = DISCOVERED;
	Q.enqueue(v);
	while (!Q.empty()) {
		int v = Q.dequeue();
		dTime(v) = ++clock;
		for (int u = firstNbr(v); -1 < u; u = nextNbr(v)) {
			if (UNDETERMINED = status(u)) {
				status(u) = DISCOVERED;
				Q.enqueue(u);
				status(v,u) = TREE;
				parent(u) = v;
			} else {
				status(v,u) = CROSS;
			}
		}
		status(v) = VISITED;
	}
    //算法
    void bfs(int);
    void dfs(int);
    void bcc(int);
    Stack<Tv> *tSort(int);
    void prim(int);                           //最小支撑树Prim算法
    void dijkstra(int);                       //最短路径Dijkstra算法
    template <typename PU> void pfs(int, PU); //优先搜索框架
}
