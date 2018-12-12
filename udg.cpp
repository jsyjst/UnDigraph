#include "udg.h"


/*初始化含n个顶点且无边的无向图G*/
Status Init(UDG &G, VexType *vexs, int n) {
    int i, j;
    if(n < 0 || (n > 0 && vexs == null)) return ERROR;
    G.n = n;
    G.e = 0;
    if(n == 0) return OK; //空图
    if((G.vexs = (VexType *)malloc(n * sizeof(VexType))) == null) return OVERFLOW;
    for(i = 0; i < n; i++) G.vexs[i] = vexs[i]; //建立顶点数组
    if((G.arcs = (int **)malloc(n * sizeof(int*))) == null) return OVERFLOW; //分配指针数组
    for(i = 0; i < n; i++) //分配每个指针所指向的数组
        if((G.arcs[i] = (int *)malloc(n * sizeof(int))) == null) //分配n*n个地址
            return OVERFLOW;
    if((G.tags = (int *)malloc(n * sizeof(int))) == null) return OVERFLOW;
    for(i = 0; i < n; i++) {
        G.tags[i] = UNVISITED;
        for(j = 0; j < n; j++) G.arcs[i][j] = 0;
    }
    return OK;
}

/*创建含n个顶点和e条边的无向图G, vexs为顶点信息，arcs为边的信息*/
Status Create(UDG &G, VexType *vexs, int n, ArcInfo *arcs, int e) {
    int i, j, k;
    VexType v, w;
    if(Init(G, vexs, n) != OK) return ERROR; //初始化

    G.e = e;
    for(k = 0; k < G.e; k++) {
        v = arcs[k].v;
        w = arcs[k].w;
        i = LocateVex(G, v);
        j = LocateVex(G, w); //确定v和w在顶点数组的位置
        if(i < 0 || j < 0) return ERROR;
        G.arcs[i][j] = G.arcs[j][i] = 1; //对应行列的元素赋值1
    }
    return OK;
}

/*销毁无向图*/
Status Destroy(UDG &G) {
    int i, j;
    for(i = 0; i < G.n; i++) {
        free(&(G.vexs[i]));
        for(j = 0; j < G.e; j++) {
            free(&(G.arcs[i][j]));
        }
    }
    return OK;
}

/*查找顶点*/
int LocateVex(UDG G, VexType v) {
    int i;
    for(i = 0; i < G.n; i++) {
        if(v == G.vexs[i]) return i;
    }
    return -1;
}

/*取图的k顶点的值到w*/
Status GetVex(UDG G, int k, VexType &w) {
    if(k < 0 || k >= G.n) return ERROR;
    w = G.vexs[k];
    return OK;
}

/*对图的k顶点赋值w*/
Status PutVex(UDG G, int k, VexType w) {
    if(k < 0 || k >= G.n) return ERROR;
    G.vexs[k] = w;
    return OK;
}

/*求图G中k顶点的第一个邻接顶点的位序*/
int FirstAdjVex(UDG G, int k) {
    int i;
    if(k < 0 || k >= G.n) return -1; //k顶点不存在
    for(i = 0; i < G.n; i++) {
        if(G.arcs[k][i] == 1) return i;
    }
    return -2; //没有邻接顶点；
}

/* m顶点为k顶点的邻接顶点，求k顶点相对于m顶点的下一个邻接顶点的位序*/
int NextAdjVex(UDG G, int k, int m) {
    if(k < 0 || k >= G.n )  return -1; //k顶点不存在
    if(G.arcs[k][m] == 0 || m < 0 || m >= G.n || k == m) return -3; //m顶点不符合要求
    for(int i = m+1; i < G.n; i++) {
        if(G.arcs[k][i]) return i;
    }
    return -2; //该邻接顶点不存在
}

/*在图中增加k顶点到m顶点的边*/
Status AddArc(UDG &G, int k, int m) {
    if(k < 0 || k >= G.n || m < 0 || m >= G.n || k == m)  return ERROR; //k顶点不存在,m顶点不存在
    G.arcs[k][m] = G.arcs[m][k] = 1;
    G.e++;
    return OK;
}

/*在图G中删除k顶点到m顶点的边*/
Status RemoveArc(UDG &G, int k, int m) {
    if(k < 0 || k >= G.n || m < 0 || m >= G.n || k == m)  return -1; //k顶点不存在,m顶点不存在G
    G.arcs[k][m] = G.arcs[m][k] = 0;
    G.e--;
    return OK;
}

/*访问函数*/
Status visit(int k) {
    if(k < 0) return ERROR;
    return OK;
}

/*从连通图G的k顶点出发进行深度优先遍历*/
Status DFS(UDG G, int k, Status(* visit)(int)) {
    int i;
    if(visit(k) == ERROR) return ERROR; //访问k顶点
    G.tags[k] = VISITED;
    printf("%c", G.vexs[k]);
    for(i = FirstAdjVex(G, k); i >= 0; i = NextAdjVex(G, k, i)) {
        if(G.tags[i] == UNVISITED)  //位序为i的顶点未被访问过
            if(DFS(G, i, visit) == ERROR)
                return ERROR;    //对i顶点递归深度遍历
    }
    return OK;

}

/*深度优先遍历图*/
Status DFSTraverse(UDG G, Status(*vistit)(int)) {
    int i;
    for(i = 0; i < G.n ; i++) G.tags[i] = UNVISITED; //初始化标志数组
    for(i = 0; i < G.n ; i++) {
        if(G.tags[i] == UNVISITED)
            if(DFS(G, i, visit) == ERROR)
                return ERROR;
        return OK;
    }
}

/*构造一个空队列*/
void InitQueue(LQueue &Q) {
    Q.head = Q.rear = (QueuePtr)malloc(sizeof(LQNode)); //开辟空间
    if(!Q.head) exit(OVERFLOW);//开辟失败则退出
    Q.head ->next = NULL;
}
/*入队操作*/
Status EnQueue(LQueue &Q, ElemType e) {
    LQNode *p;
    p = (LQNode *)malloc(sizeof(LQNode));
    if(p == null) return OVERFLOW;
    p->data = e;
    p->next = NULL;
    if(Q.head == NULL) Q.head = p; //插入空队列
    else Q.rear->next = p;  //e插入非空队列
    Q.rear = p;  //队尾指针指向新的队尾
    return OK;
}

/*出队操作*/
Status DeQueue(LQueue &Q, ElemType &e) {
    LQNode *p;
    if(Q.head == null) return ERROR;
    p = Q.head;  //指向队头结点
    e = p->data; //保存队头节点数据
    Q.head = p->next;
    if(Q.rear == p) Q.rear = null;
    free(p);
    return OK;
}

/*广度优先遍历图*/
Status BFSTraverse(UDG G, Status(*vistit)(int)) {
    int i, j, k;
    for(i = 0; i < G.n ; i++) G.tags[i] = UNVISITED; //初始化标志数组
    LQueue Q;
    InitQueue(Q);  //初始化链队列
    for(i = 0; i < G.n; i++) {
        if(G.tags[i] == UNVISITED) {
            if(vistit(i) == ERROR) return ERROR;
            printf("%c", G.vexs[i]);
            G.tags[i] = VISITED;
            EnQueue(Q, i);
            while(OK == DeQueue(Q, k)) {
                for(j = FirstAdjVex(G, k); j >= 0; j = NextAdjVex(G, k, j))
                    if(UNVISITED == G.tags[j]) {
                        if(vistit(j) == ERROR) return ERROR;
                        G.tags[j] = VISITED;
                        EnQueue(Q, j);
                        printf("%c", G.vexs[j]);
                    }
            }
        }
    }
}

/*显示无向图的邻接数组*/
void showUDG(UDG G) {
    if(G.n == 0) printf("当前的无向图为空图\n");
    else {
        printf("图G当前的邻接数组为：\n");
        for(int i = 0; i < G.n + 1; i++) {
            for(int j = 0; j < G.n + 1; j++) {
                if(i == 0 && j == 0) printf("    ");
                else if(i == 0) printf("%4c", G.vexs[j - 1]);
                else if(j == 0) printf("%4c", G.vexs[i - 1]);
                else printf("%4d", G.arcs[i - 1][j - 1]);
                if(j == G.n) printf("\n\n");
            }
        }
    }
}
/*产生随机数*/
int random(int num) {
    return (rand() % num);
}
/*输入字符*/
char put() {
    char c;
    getchar(); //吃掉缓冲区的空格
    gets(&c);
    return c;
}
