#include "udg.h"

int main() {
    int i, j, t, n, e;
    int current; //位序
    int k, m; //测试的顶点k
    char w;//测试的顶点w
    int select;//选择
    UDG G;
    srand(time(NULL));  //以时间为种子，从而产生不一样的随机数
    n = random(5); //随机产生顶点个数
    if(n==1) e=0;
    else e = n; //边数与顶点数相同
    char *vexs = (char *)malloc(n * sizeof(char));
    ArcInfo *arcs = (ArcInfo *)malloc(e * sizeof(ArcInfo));
    printf("随机产生顶点个数：%d\n", n);
    printf("图的默认边数为：%d\n", e);
    printf("顶点名称为：");
    for(i = 0; i < n; i++) {
        vexs[i] = 'A' + random(26);   //随机生成顶点名称
        printf("%c ", vexs[i]);
    }
    //边数以从第一个顶点开始依次连接
    for(j = 0; j < e; j++) {
        arcs[j].v = vexs[j];
        if(j + 1 == e) arcs[j].w = vexs[0];
        else arcs[j].w = vexs[j + 1];
    }
    Create(G, vexs, n, arcs, e);  //创建无向图
    printf("\n");
    do {
        showUDG(G);
        printf("请选择对无向图G的操作：键盘输入对应数字\n");
        printf("1 查找顶点\n");
        printf("2 取图G的k顶点的值到w\n");
        printf("3 对图G的k顶点赋值w\n");
        printf("4 求图G中k顶点的第一个邻接顶点的位序\n");
        printf("5 求k顶点相对于m顶点的下一个邻接顶点的位序,其中m顶点为k顶点的邻接顶点\n");
        printf("6 在图G中增加k顶点到m顶点的边\n");
        printf("7 在图G中删除k顶点到m顶点的边\n");
        printf("8 深度优先遍历图\n");
        printf("9 广度优先遍历图\n");
        printf("0 退出程序\n");
        printf("请输入你的选择：\n");
        scanf("%d", &select);
        switch(select) {
        case 1:
            printf("请输入你要查找的顶点字母：");
            w = put();
            if(LocateVex(G, w) == -1) printf("查找失败，请检查查找的顶点是否存在\n");
            else printf("该字母的位序为：%d\n", LocateVex(G, w));
            break;
        case 2:
            printf("请输入k顶点位序:");
            scanf("%d", &k);
            if(GetVex(G, k, w)) printf("w的值为：%c\n", w);
            else printf("赋值失败，请检查k顶点的位序是否正确\n");
            break;
        case 3:
            printf("请输入k顶点位序:");
            scanf("%d", &k);
            printf("请输入w的值:");
            w = put();
            if(PutVex(G, k, w)) printf("赋值成功，");
            else printf("赋值失败，请检查k顶点的位序是否正确\n");
            break;
        case 4:
            printf("请输入k顶点位序:");
            scanf("%d", &k);
            current = FirstAdjVex(G, k);
            if(current == -2) printf("所求邻接顶点不存在\n");
            else if(current == -1) printf("k顶点不存在\n");
            else printf("所求邻接顶点的位序为：%d\n", current);
            break;
        case 5:
            printf("请输入k顶点位序:");
            scanf("%d", &k);
            printf("请输入m顶点的位序:");
            scanf("%d", &m);
            current = NextAdjVex(G, k, m);
            if(current == -2) printf("所求邻接顶点不存在\n");
            else if(current == -1) printf("k顶点不存在\n");
            else if(current == -3) printf("m顶点不符合要求\n");
            else printf("所求邻接顶点的位序为：%d\n", current);
            break;
        case 6:
            printf("请输入k顶点位序:");
            scanf("%d", &k);
            printf("请输入m顶点的位序:");
            scanf("%d", &m);
            if(AddArc(G, k, m) == OK) printf("增加成功，");
            else printf("增加失败，请检查输入的k与m顶点是否符合要求\n");
            break;
        case 7:
            printf("请输入k顶点位序:");
            scanf("%d", &k);
            printf("请输入m顶点的位序:");
            scanf("%d", &m);
            if(RemoveArc(G, k, m) == OK) printf("删除成功，");
            else printf("删除失败，请检查输入的k与m顶点是否符合要求\n");
            break;
        case 8:
            printf("深度优先遍历的顶点顺序为：");
            DFSTraverse(G,visit);
            printf("\n");
            break;
        case 9:
            printf("广度优先遍历的顶点顺序为：");
            BFSTraverse(G,visit);
            printf("\n");
            break;
        case 0:
            break;
        default :
            printf("输入错误，没有该选项\n");
            break;
        }
    } while(select != 0);
    /*操作完释放空间*/
    Destroy(G);
    if(n != 0) {
        free(vexs);
        free(arcs);
    }
    return 0;
}
