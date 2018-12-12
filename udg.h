#ifndef UDG_H_INCLUDED
#define UDG_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include<time.h>  //随机数使用
#define UNVISITED 0
#define VISITED 1
#define OK 1
#define ERROR 0
#define OVERFLOW -1
#define null NULL
typedef int Status;
typedef char VexType;  //char类型
typedef int ElemType;  //链队列存储类型为int 类型

/*无向图定义*/
typedef struct {
    VexType *vexs;   //顶点数组，VexType为char类型
    int **arcs;     //关系数组，0表示不相邻，1表示相邻
    int n,e;       //顶点数和边数
    int *tags;    //标志数组，可用于图遍历中标记顶点访问与否
}UDG;            //邻接数组类型
typedef struct {
   VexType v,w;//边的端点
} ArcInfo;//边的信息

/*链队列定义*/
typedef struct LQNode{
    ElemType data;
    struct LQNode *next;
} LQNode,*QueuePtr; //结点及其指针类型
typedef struct {
    QueuePtr head; //队头指针
    QueuePtr rear;  //队尾指针
}LQueue; //链队列

/* 测试需要的接口*/
int random(int num); //产生随机数
char put();//输入字符
void showUDG(UDG G); //显示无向图的邻接数组

/*图操作的接口*/
int LocateVex(UDG G, VexType v); //查找顶点
Status Init(UDG &G,VexType *vexs,int n); //初始化含n个顶点的且无边的无向图
Status Create(UDG &G, VexType *vexs, int n, ArcInfo *arcs, int e);//创建含n个顶点和e条边的无向图G, vexs为顶点信息，arcs为边的信息
Status Destroy(UDG &G); //销毁无向图
Status GetVex(UDG G,int k,VexType &w); //取图的k顶点的值到w
Status PutVex(UDG G,int k,VexType w); //对图的k顶点赋值w
int FirstAdjVex(UDG G,int k); //求图G中k顶点的第一个邻接顶点的位序
int NextAdjVex(UDG G,int k,int m); // m顶点为k顶点的邻接顶点，求k顶点相对于m顶点的下一个邻接顶点的位序
Status AddArc(UDG &G,int k ,int m ); //在图中增加k顶点到m顶点的边
Status RemoveArc(UDG &G,int k ,int m); //在图G中删除k顶点到m顶点的边
Status DFSTraverse(UDG G,Status(*vistit)(int));//深度优先遍历图
Status BFSTraverse(UDG G,Status(*vistit)(int));//广度优先遍历图
Status visit(int k);//访问函数
#endif // UDG_H_INCLUDED
