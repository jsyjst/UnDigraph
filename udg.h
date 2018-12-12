#ifndef UDG_H_INCLUDED
#define UDG_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include<time.h>  //�����ʹ��
#define UNVISITED 0
#define VISITED 1
#define OK 1
#define ERROR 0
#define OVERFLOW -1
#define null NULL
typedef int Status;
typedef char VexType;  //char����
typedef int ElemType;  //�����д洢����Ϊint ����

/*����ͼ����*/
typedef struct {
    VexType *vexs;   //�������飬VexTypeΪchar����
    int **arcs;     //��ϵ���飬0��ʾ�����ڣ�1��ʾ����
    int n,e;       //�������ͱ���
    int *tags;    //��־���飬������ͼ�����б�Ƕ���������
}UDG;            //�ڽ���������
typedef struct {
   VexType v,w;//�ߵĶ˵�
} ArcInfo;//�ߵ���Ϣ

/*�����ж���*/
typedef struct LQNode{
    ElemType data;
    struct LQNode *next;
} LQNode,*QueuePtr; //��㼰��ָ������
typedef struct {
    QueuePtr head; //��ͷָ��
    QueuePtr rear;  //��βָ��
}LQueue; //������

/* ������Ҫ�Ľӿ�*/
int random(int num); //���������
char put();//�����ַ�
void showUDG(UDG G); //��ʾ����ͼ���ڽ�����

/*ͼ�����Ľӿ�*/
int LocateVex(UDG G, VexType v); //���Ҷ���
Status Init(UDG &G,VexType *vexs,int n); //��ʼ����n����������ޱߵ�����ͼ
Status Create(UDG &G, VexType *vexs, int n, ArcInfo *arcs, int e);//������n�������e���ߵ�����ͼG, vexsΪ������Ϣ��arcsΪ�ߵ���Ϣ
Status Destroy(UDG &G); //��������ͼ
Status GetVex(UDG G,int k,VexType &w); //ȡͼ��k�����ֵ��w
Status PutVex(UDG G,int k,VexType w); //��ͼ��k���㸳ֵw
int FirstAdjVex(UDG G,int k); //��ͼG��k����ĵ�һ���ڽӶ����λ��
int NextAdjVex(UDG G,int k,int m); // m����Ϊk������ڽӶ��㣬��k���������m�������һ���ڽӶ����λ��
Status AddArc(UDG &G,int k ,int m ); //��ͼ������k���㵽m����ı�
Status RemoveArc(UDG &G,int k ,int m); //��ͼG��ɾ��k���㵽m����ı�
Status DFSTraverse(UDG G,Status(*vistit)(int));//������ȱ���ͼ
Status BFSTraverse(UDG G,Status(*vistit)(int));//������ȱ���ͼ
Status visit(int k);//���ʺ���
#endif // UDG_H_INCLUDED
