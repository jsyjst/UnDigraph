#include "udg.h"

int main() {
    int i, j, t, n, e;
    int current; //λ��
    int k, m; //���ԵĶ���k
    char w;//���ԵĶ���w
    int select;//ѡ��
    UDG G;
    srand(time(NULL));  //��ʱ��Ϊ���ӣ��Ӷ�������һ���������
    n = random(5); //��������������
    if(n==1) e=0;
    else e = n; //�����붥������ͬ
    char *vexs = (char *)malloc(n * sizeof(char));
    ArcInfo *arcs = (ArcInfo *)malloc(e * sizeof(ArcInfo));
    printf("����������������%d\n", n);
    printf("ͼ��Ĭ�ϱ���Ϊ��%d\n", e);
    printf("��������Ϊ��");
    for(i = 0; i < n; i++) {
        vexs[i] = 'A' + random(26);   //������ɶ�������
        printf("%c ", vexs[i]);
    }
    //�����Դӵ�һ�����㿪ʼ��������
    for(j = 0; j < e; j++) {
        arcs[j].v = vexs[j];
        if(j + 1 == e) arcs[j].w = vexs[0];
        else arcs[j].w = vexs[j + 1];
    }
    Create(G, vexs, n, arcs, e);  //��������ͼ
    printf("\n");
    do {
        showUDG(G);
        printf("��ѡ�������ͼG�Ĳ��������������Ӧ����\n");
        printf("1 ���Ҷ���\n");
        printf("2 ȡͼG��k�����ֵ��w\n");
        printf("3 ��ͼG��k���㸳ֵw\n");
        printf("4 ��ͼG��k����ĵ�һ���ڽӶ����λ��\n");
        printf("5 ��k���������m�������һ���ڽӶ����λ��,����m����Ϊk������ڽӶ���\n");
        printf("6 ��ͼG������k���㵽m����ı�\n");
        printf("7 ��ͼG��ɾ��k���㵽m����ı�\n");
        printf("8 ������ȱ���ͼ\n");
        printf("9 ������ȱ���ͼ\n");
        printf("0 �˳�����\n");
        printf("���������ѡ��\n");
        scanf("%d", &select);
        switch(select) {
        case 1:
            printf("��������Ҫ���ҵĶ�����ĸ��");
            w = put();
            if(LocateVex(G, w) == -1) printf("����ʧ�ܣ�������ҵĶ����Ƿ����\n");
            else printf("����ĸ��λ��Ϊ��%d\n", LocateVex(G, w));
            break;
        case 2:
            printf("������k����λ��:");
            scanf("%d", &k);
            if(GetVex(G, k, w)) printf("w��ֵΪ��%c\n", w);
            else printf("��ֵʧ�ܣ�����k�����λ���Ƿ���ȷ\n");
            break;
        case 3:
            printf("������k����λ��:");
            scanf("%d", &k);
            printf("������w��ֵ:");
            w = put();
            if(PutVex(G, k, w)) printf("��ֵ�ɹ���");
            else printf("��ֵʧ�ܣ�����k�����λ���Ƿ���ȷ\n");
            break;
        case 4:
            printf("������k����λ��:");
            scanf("%d", &k);
            current = FirstAdjVex(G, k);
            if(current == -2) printf("�����ڽӶ��㲻����\n");
            else if(current == -1) printf("k���㲻����\n");
            else printf("�����ڽӶ����λ��Ϊ��%d\n", current);
            break;
        case 5:
            printf("������k����λ��:");
            scanf("%d", &k);
            printf("������m�����λ��:");
            scanf("%d", &m);
            current = NextAdjVex(G, k, m);
            if(current == -2) printf("�����ڽӶ��㲻����\n");
            else if(current == -1) printf("k���㲻����\n");
            else if(current == -3) printf("m���㲻����Ҫ��\n");
            else printf("�����ڽӶ����λ��Ϊ��%d\n", current);
            break;
        case 6:
            printf("������k����λ��:");
            scanf("%d", &k);
            printf("������m�����λ��:");
            scanf("%d", &m);
            if(AddArc(G, k, m) == OK) printf("���ӳɹ���");
            else printf("����ʧ�ܣ����������k��m�����Ƿ����Ҫ��\n");
            break;
        case 7:
            printf("������k����λ��:");
            scanf("%d", &k);
            printf("������m�����λ��:");
            scanf("%d", &m);
            if(RemoveArc(G, k, m) == OK) printf("ɾ���ɹ���");
            else printf("ɾ��ʧ�ܣ����������k��m�����Ƿ����Ҫ��\n");
            break;
        case 8:
            printf("������ȱ����Ķ���˳��Ϊ��");
            DFSTraverse(G,visit);
            printf("\n");
            break;
        case 9:
            printf("������ȱ����Ķ���˳��Ϊ��");
            BFSTraverse(G,visit);
            printf("\n");
            break;
        case 0:
            break;
        default :
            printf("�������û�и�ѡ��\n");
            break;
        }
    } while(select != 0);
    /*�������ͷſռ�*/
    Destroy(G);
    if(n != 0) {
        free(vexs);
        free(arcs);
    }
    return 0;
}
