#include<string.h>
#define INFINIFY 65535   //定义无穷大
#define MaxVertexNum 100    //定义最大定点数
using namespace std;
#include <stdio.h>
#include <limits.h>
#include <string.h>

//int visited[MaxVertexNum];
/*
char Q[MaxVertexNum][MaxVertexNum] = {
 */

char R[MaxVertexNum][MaxVertexNum] = {
	{" 北门    "},
	{" 游泳池  "},
	{" 河东食堂"},
	{" 文史楼  "},
	{" 东门    "},
	{" 体育馆  "},
	{" 文附楼  "},
	{" 文科大楼"},
	{" 篮球场  "},
	{" 图书馆  "},
	{" 毛主席像"},
	{" 理科大楼"},
	{" 河西食堂"},
	{" 西北门  "},

};//地点信息

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
};//道路信息

int B[MaxVertexNum] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14};

typedef struct {
    int G[MaxVertexNum][MaxVertexNum]; // 图的邻接矩阵
    int Nv; // 顶点数
    int Ne; // 边数
} MGraph;

void CreateGraph(MGraph& g, int A[MaxVertexNum][MaxVertexNum], int Nv, int Ne)      //创建图的邻接矩阵
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

    printf("最短路径为：");
    for (int i = top - 1; i >= 0; --i) {
        printf("%s", R[stack[i]]);
        if (i > 0) printf(" -> ");
    }

    printf("\n路径长度为：%d\n", dist[dest]);
}
void Dijkstra(MGraph g, int src, int dest, int dist[], int path[]) {
    int visited[MaxVertexNum] = {0}; // 标记顶点是否被访问
    int i, j, k, min;

    for (i = 0; i < g.Nv; ++i) {
        dist[i] = g.G[src][i]; // 初始化距离
        path[i] = (dist[i] < INFINIFY) ? src : -1; // 初始化路径
    }

    visited[src] = 1; // 标记源顶点已访问

    for (i = 0; i < g.Nv - 1; ++i) {
        min = INFINIFY;
        k = -1;

        // 选择一个距离源点最近的未访问顶点
        for (j = 0; j < g.Nv; ++j) {
            if (!visited[j] && dist[j] < min) {
                min = dist[j];
                k = j;
            }
        }

        if (k == -1) // 如果找不到未访问的顶点，退出循环
            break;

        visited[k] = 1; // 标记顶点 k 已访问

        // 更新距离和路径
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
	//x = input1();//判断输入的数字是否在功能里面
    printf("输入你所在的位置，为你规划最短路径：");

    //z = input2(Nv, B) - 1;//判断输入的地点在图里面吗
    char place1[MaxVertexNum], place2[MaxVertexNum];

    printf("输入两个地点，用空格分隔：\n");
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

    // 输出最短路径和路径长度
    printShortestPath(src, dest,dist, path, R);
    printf("\n已返回主菜单，请输入需要查询的菜单栏选项:\n");
    printf("\n");
    //Caidan();
    return 0;
}
