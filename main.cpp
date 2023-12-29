#include<string.h>
#define INFINIFY 65535   //���������
#define MaxVertexNum 100    //������󶨵���
using namespace std;
#include <stdio.h>
#include <limits.h>
#include <string.h>

//int visited[MaxVertexNum];
/*
char Q[MaxVertexNum][MaxVertexNum] = {
 */

char R[MaxVertexNum][MaxVertexNum] = {
	{" ����    "},
	{" ��Ӿ��  "},
	{" �Ӷ�ʳ��"},
	{" ��ʷ¥  "},
	{" ����    "},
	{" ������  "},
	{" �ĸ�¥  "},
	{" �Ŀƴ�¥"},
	{" ����  "},
	{" ͼ���  "},
	{" ë��ϯ��"},
	{" ��ƴ�¥"},
	{" ����ʳ��"},
	{" ������  "},

};//�ص���Ϣ

int A[MaxVertexNum][MaxVertexNum] = {
		{0,152,INFINIFY,INFINIFY,INFINIFY,INFINIFY,INFINIFY,INFINIFY,INFINIFY,INFINIFY,INFINIFY,INFINIFY,INFINIFY,INFINIFY},//1
		{152,0,251,INFINIFY,INFINIFY,INFINIFY,INFINIFY,INFINIFY,143,98,INFINIFY,INFINIFY,532,INFINIFY},//2
		{INFINIFY,251,0,85,INFINIFY,INFINIFY,INFINIFY,INFINIFY,INFINIFY,INFINIFY,INFINIFY,INFINIFY,INFINIFY,INFINIFY},//3
		{INFINIFY,INFINIFY,85,0,261,348,INFINIFY,INFINIFY,96,INFINIFY,INFINIFY,INFINIFY,INFINIFY,INFINIFY},//4
		{INFINIFY,INFINIFY,INFINIFY,261,0,187,INFINIFY,INFINIFY,INFINIFY,INFINIFY,INFINIFY,INFINIFY,INFINIFY,INFINIFY},//5
		{INFINIFY,INFINIFY,INFINIFY,348,187,0,198,162,412,INFINIFY,INFINIFY,INFINIFY,INFINIFY,INFINIFY},//6
		{INFINIFY,INFINIFY,INFINIFY,INFINIFY,INFINIFY,198,0,47,INFINIFY,INFINIFY,INFINIFY,INFINIFY,INFINIFY,INFINIFY},//7
		{INFINIFY,INFINIFY,INFINIFY,INFINIFY,INFINIFY,162,47,0,346,437,INFINIFY,541,INFINIFY,INFINIFY},//8
		{INFINIFY,143,INFINIFY,96,INFINIFY,412,INFINIFY,346,0,112,INFINIFY,INFINIFY,INFINIFY,INFINIFY},//9
		{INFINIFY,98,INFINIFY,INFINIFY,INFINIFY,INFINIFY,INFINIFY,437,112,0,226,442,323,INFINIFY},//10
		{INFINIFY,INFINIFY,INFINIFY,INFINIFY,INFINIFY,INFINIFY,INFINIFY,INFINIFY,INFINIFY,226,0,145,318,INFINIFY},//11
		{INFINIFY,INFINIFY,INFINIFY,INFINIFY,INFINIFY,INFINIFY,INFINIFY,541,INFINIFY,442,145,0,281,312},//12
		{INFINIFY,532,INFINIFY,INFINIFY,INFINIFY,INFINIFY,INFINIFY,INFINIFY,INFINIFY,323,318,281,0,96},//13
		{INFINIFY,INFINIFY,INFINIFY,INFINIFY,INFINIFY,INFINIFY,INFINIFY,INFINIFY,INFINIFY,INFINIFY,INFINIFY,INFINIFY,312,96,0},//14
		//{800,INFINIFY,INFINIFY,INFINIFY,INFINIFY,INFINIFY,INFINIFY,INFINIFY,INFINIFY,INFINIFY,INFINIFY,INFINIFY,INFINIFY,INFINIFY,300,INFINIFY,INFINIFY,0},
};//��·��Ϣ

int B[MaxVertexNum] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14};

typedef struct {
    int G[MaxVertexNum][MaxVertexNum]; // ͼ���ڽӾ���
    int Nv; // ������
    int Ne; // ����
} MGraph;

void CreateGraph(MGraph& g, int A[MaxVertexNum][MaxVertexNum], int Nv, int Ne)      //����ͼ���ڽӾ���
{
	int i, j;
	g.Nv = Nv;
	g.Ne = Ne;
	for (i = 0; i < g.Nv; i++)
		for (j = 0; j < g.Ne; j++)
			g.G[i][j] = A[i][j];
}
void printShortestPath(int src, int dest, int dist[], int path[], char R[MaxVertexNum][MaxVertexNum]) {
    int stack[MaxVertexNum];
    int top = 0;
    int p = dest;

    while (p != -1) {
        stack[top++] = p;
        p = path[p];
    }

    printf("���·��Ϊ��");
    for (int i = top - 1; i >= 0; --i) {
        printf("%s", R[stack[i]]);
        if (i > 0) printf(" -> ");
    }

    printf("\n·������Ϊ��%d\n", dist[dest]);
}
void Dijkstra(MGraph g, int src, int dest, int dist[], int path[]) {
    int visited[MaxVertexNum] = {0}; // ��Ƕ����Ƿ񱻷���
    int i, j, k, min;

    for (i = 0; i < g.Nv; ++i) {
        dist[i] = g.G[src][i]; // ��ʼ������
        path[i] = (dist[i] < INFINIFY) ? src : -1; // ��ʼ��·��
    }

    visited[src] = 1; // ���Դ�����ѷ���

    for (i = 0; i < g.Nv - 1; ++i) {
        min = INFINIFY;
        k = -1;

        // ѡ��һ������Դ�������δ���ʶ���
        for (j = 0; j < g.Nv; ++j) {
            if (!visited[j] && dist[j] < min) {
                min = dist[j];
                k = j;
            }
        }

        if (k == -1) // ����Ҳ���δ���ʵĶ��㣬�˳�ѭ��
            break;

        visited[k] = 1; // ��Ƕ��� k �ѷ���

        // ���¾����·��
        for (j = 0; j < g.Nv; ++j) {
            if (!visited[j] && g.G[k][j] < INFINIFY) {
                if (dist[k] + g.G[k][j] < dist[j]) {
                    dist[j] = dist[k] + g.G[k][j];
                    path[j] = k;
                }
            }
        }
    }
}
void change()
{

}

int main()
{
    //Caidan();
	MGraph g;
	//LGraph* G;
    int dist[MaxVertexNum];int path[MaxVertexNum];
    int src,dest;
	int Nv = 14, Ne = 24;
	int x, z;
	//x = input1();//�ж�����������Ƿ��ڹ�������
    printf("���������ڵ�λ�ã�Ϊ��滮���·����");

    //z = input2(Nv, B) - 1;//�ж�����ĵص���ͼ������
    char place1[MaxVertexNum], place2[MaxVertexNum];

    printf("���������ص㣬�ÿո�ָ���\n");
    scanf("%s %s", place1, place2);
    for (int i = 0; i < Nv; ++i) {
        if (strcmp(R[i], place1) == 0) {
            src = i;
        }
        if (strcmp(R[i], place2) == 0) {
            dest = i;
        }
    }
    CreateGraph(g, A, Nv, Ne);
    Dijkstra(g, src, dest, dist, path);

    // ������·����·������
    printShortestPath(src, dest,dist, path, R);
    printf("\n�ѷ������˵�����������Ҫ��ѯ�Ĳ˵���ѡ��:\n");
    printf("\n");
    //Caidan();
    return 0;
}
