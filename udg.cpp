#include "udg.h"


/*��ʼ����n���������ޱߵ�����ͼG*/
Status Init(UDG &G, VexType *vexs, int n) {
    int i, j;
    if(n < 0 || (n > 0 && vexs == null)) return ERROR;
    G.n = n;
    G.e = 0;
    if(n == 0) return OK; //��ͼ
    if((G.vexs = (VexType *)malloc(n * sizeof(VexType))) == null) return OVERFLOW;
    for(i = 0; i < n; i++) G.vexs[i] = vexs[i]; //������������
    if((G.arcs = (int **)malloc(n * sizeof(int*))) == null) return OVERFLOW; //����ָ������
    for(i = 0; i < n; i++) //����ÿ��ָ����ָ�������
        if((G.arcs[i] = (int *)malloc(n * sizeof(int))) == null) //����n*n����ַ
            return OVERFLOW;
    if((G.tags = (int *)malloc(n * sizeof(int))) == null) return OVERFLOW;
    for(i = 0; i < n; i++) {
        G.tags[i] = UNVISITED;
        for(j = 0; j < n; j++) G.arcs[i][j] = 0;
    }
    return OK;
}

/*������n�������e���ߵ�����ͼG, vexsΪ������Ϣ��arcsΪ�ߵ���Ϣ*/
Status Create(UDG &G, VexType *vexs, int n, ArcInfo *arcs, int e) {
    int i, j, k;
    VexType v, w;
    if(Init(G, vexs, n) != OK) return ERROR; //��ʼ��

    G.e = e;
    for(k = 0; k < G.e; k++) {
        v = arcs[k].v;
        w = arcs[k].w;
        i = LocateVex(G, v);
        j = LocateVex(G, w); //ȷ��v��w�ڶ��������λ��
        if(i < 0 || j < 0) return ERROR;
        G.arcs[i][j] = G.arcs[j][i] = 1; //��Ӧ���е�Ԫ�ظ�ֵ1
    }
    return OK;
}

/*��������ͼ*/
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

/*���Ҷ���*/
int LocateVex(UDG G, VexType v) {
    int i;
    for(i = 0; i < G.n; i++) {
        if(v == G.vexs[i]) return i;
    }
    return -1;
}

/*ȡͼ��k�����ֵ��w*/
Status GetVex(UDG G, int k, VexType &w) {
    if(k < 0 || k >= G.n) return ERROR;
    w = G.vexs[k];
    return OK;
}

/*��ͼ��k���㸳ֵw*/
Status PutVex(UDG G, int k, VexType w) {
    if(k < 0 || k >= G.n) return ERROR;
    G.vexs[k] = w;
    return OK;
}

/*��ͼG��k����ĵ�һ���ڽӶ����λ��*/
int FirstAdjVex(UDG G, int k) {
    int i;
    if(k < 0 || k >= G.n) return -1; //k���㲻����
    for(i = 0; i < G.n; i++) {
        if(G.arcs[k][i] == 1) return i;
    }
    return -2; //û���ڽӶ��㣻
}

/* m����Ϊk������ڽӶ��㣬��k���������m�������һ���ڽӶ����λ��*/
int NextAdjVex(UDG G, int k, int m) {
    if(k < 0 || k >= G.n )  return -1; //k���㲻����
    if(G.arcs[k][m] == 0 || m < 0 || m >= G.n || k == m) return -3; //m���㲻����Ҫ��
    for(int i = m+1; i < G.n; i++) {
        if(G.arcs[k][i]) return i;
    }
    return -2; //���ڽӶ��㲻����
}

/*��ͼ������k���㵽m����ı�*/
Status AddArc(UDG &G, int k, int m) {
    if(k < 0 || k >= G.n || m < 0 || m >= G.n || k == m)  return ERROR; //k���㲻����,m���㲻����
    G.arcs[k][m] = G.arcs[m][k] = 1;
    G.e++;
    return OK;
}

/*��ͼG��ɾ��k���㵽m����ı�*/
Status RemoveArc(UDG &G, int k, int m) {
    if(k < 0 || k >= G.n || m < 0 || m >= G.n || k == m)  return -1; //k���㲻����,m���㲻����G
    G.arcs[k][m] = G.arcs[m][k] = 0;
    G.e--;
    return OK;
}

/*���ʺ���*/
Status visit(int k) {
    if(k < 0) return ERROR;
    return OK;
}

/*����ͨͼG��k�����������������ȱ���*/
Status DFS(UDG G, int k, Status(* visit)(int)) {
    int i;
    if(visit(k) == ERROR) return ERROR; //����k����
    G.tags[k] = VISITED;
    printf("%c", G.vexs[k]);
    for(i = FirstAdjVex(G, k); i >= 0; i = NextAdjVex(G, k, i)) {
        if(G.tags[i] == UNVISITED)  //λ��Ϊi�Ķ���δ�����ʹ�
            if(DFS(G, i, visit) == ERROR)
                return ERROR;    //��i����ݹ���ȱ���
    }
    return OK;

}

/*������ȱ���ͼ*/
Status DFSTraverse(UDG G, Status(*vistit)(int)) {
    int i;
    for(i = 0; i < G.n ; i++) G.tags[i] = UNVISITED; //��ʼ����־����
    for(i = 0; i < G.n ; i++) {
        if(G.tags[i] == UNVISITED)
            if(DFS(G, i, visit) == ERROR)
                return ERROR;
        return OK;
    }
}

/*����һ���ն���*/
void InitQueue(LQueue &Q) {
    Q.head = Q.rear = (QueuePtr)malloc(sizeof(LQNode)); //���ٿռ�
    if(!Q.head) exit(OVERFLOW);//����ʧ�����˳�
    Q.head ->next = NULL;
}
/*��Ӳ���*/
Status EnQueue(LQueue &Q, ElemType e) {
    LQNode *p;
    p = (LQNode *)malloc(sizeof(LQNode));
    if(p == null) return OVERFLOW;
    p->data = e;
    p->next = NULL;
    if(Q.head == NULL) Q.head = p; //����ն���
    else Q.rear->next = p;  //e����ǿն���
    Q.rear = p;  //��βָ��ָ���µĶ�β
    return OK;
}

/*���Ӳ���*/
Status DeQueue(LQueue &Q, ElemType &e) {
    LQNode *p;
    if(Q.head == null) return ERROR;
    p = Q.head;  //ָ���ͷ���
    e = p->data; //�����ͷ�ڵ�����
    Q.head = p->next;
    if(Q.rear == p) Q.rear = null;
    free(p);
    return OK;
}

/*������ȱ���ͼ*/
Status BFSTraverse(UDG G, Status(*vistit)(int)) {
    int i, j, k;
    for(i = 0; i < G.n ; i++) G.tags[i] = UNVISITED; //��ʼ����־����
    LQueue Q;
    InitQueue(Q);  //��ʼ��������
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

/*��ʾ����ͼ���ڽ�����*/
void showUDG(UDG G) {
    if(G.n == 0) printf("��ǰ������ͼΪ��ͼ\n");
    else {
        printf("ͼG��ǰ���ڽ�����Ϊ��\n");
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
/*���������*/
int random(int num) {
    return (rand() % num);
}
/*�����ַ�*/
char put() {
    char c;
    getchar(); //�Ե��������Ŀո�
    gets(&c);
    return c;
}
