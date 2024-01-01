#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#define INFINIFY 65535   //定义无穷大
#define MaxVertexNum 100    //定义最大定点数
#include<vector>
#include<iostream>
#include<map>
using namespace std;
int visited[MaxVertexNum];
int minDistance=INFINIFY;
char R[MaxVertexNum][MaxVertexNum] = {
	{"北门"},
	{"游泳池"},
	{"河东食堂"},
	{"文史楼"},
	{"东门"},
	{"体育馆"},
	{"文附楼"},
	{"文科大楼"},
	{"篮球场"},
	{"图书馆"},
	{"毛主席像"},
	{"理科大楼"},
	{"河西食堂"},
	{"西北门"},

};
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
		{INFINIFY,INFINIFY,INFINIFY,INFINIFY,INFINIFY,INFINIFY,INFINIFY,INFINIFY,INFINIFY,INFINIFY,INFINIFY,312,96,0},//14
};
int B[MaxVertexNum] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14};
typedef char DataType;
typedef int  WeightType;
typedef struct          //以下定义邻接矩阵类型
{
	int number;             //顶点编号
	DataType xinxi;      //顶点其他信息
}VertexType;           //顶点类型
typedef struct
{
	WeightType G[MaxVertexNum][MaxVertexNum];    //邻接矩阵数组
	int Nv;                   //顶点数
	int Ne;                  //边数
	VertexType Data[MaxVertexNum];     //存放顶点信息
}MGraph;                    //完整的图邻接矩阵类型
typedef struct ANode          //定义邻接表类型
{
	int Adjv;              //该边的邻接点编号
	struct ANode* Next;   //指向下一条边的指针
	WeightType weight;              //该边的相关信息如权值（用整形表示）
}ENode;                    //边结点类型
typedef struct Vnode
{
	DataType xinxi;           //顶点其他信息
	ENode* FirstEdge;       //指向第一条边
}VNode;                      //邻接表头结点类型
typedef struct
{
	VNode Adjlist[MaxVertexNum];       //邻接表头结点数组
	int Nv, Ne;                   //图中顶点数n和边数e
}LGraph;
void Caidan();       //菜单函数

int input1();            //输入函数1
int input2(int& Nv, int B[MaxVertexNum]);             //输入函数2
int input3();              //输入函数3
void place(char Q[MaxVertexNum][MaxVertexNum], int& Nv);              ///景点信息查询函数
void CreateGraph(MGraph& g, int A[MaxVertexNum][MaxVertexNum], int Nv, int Ne);      //创建图的邻接矩阵
void PutMGraph(MGraph g);                  //输出邻接矩阵g
void CreateLGraph(LGraph*& G, int A[MaxVertexNum][MaxVertexNum], int Nv, int Ne);    //创建地图的邻接表
void AvabilePath(LGraph* G, int Nv, char Q[MaxVertexNum][MaxVertexNum], int B[MaxVertexNum]);                    ///输出各地点间可行路径函数
void DestroyLGraph(LGraph* G);                  ///销毁图的邻接表
void Bestlu(LGraph* G, int z, char A[MaxVertexNum][MaxVertexNum]);      ///找寻最佳浏览路线函数
void PutShortlu(MGraph g, int dist[], int path[], int S[], int z, int& Nv, int B[MaxVertexNum], char R[MaxVertexNum][MaxVertexNum]);   //输出从顶点v出发的所有最短路径
void Shortlu(MGraph g, int z, int& Nv, int B[MaxVertexNum], char R[MaxVertexNum][MaxVertexNum]);	//找寻最短路径函数
void modify(int A[MaxVertexNum][MaxVertexNum], int& Nv, int& Ne, char Q[MaxVertexNum][MaxVertexNum], int B[MaxVertexNum]);        //图的修改函数
void  Caidan()//菜单函数
{
	printf(" \t************************欢迎使用校园导航系统****************************");
	printf(" \n\t**                    欢迎来到华东师范大学                            **");
	printf(" \n\t**                          菜单选择                                  **");
	printf(" \n\t**                                                                    **");
	printf(" \n\t**      1、地点信息查看                 2、增加、删除地点信息         **");
	printf(" \n\t**                                                                    **");
	printf(" \n\t**      3、增加、删除道路信息           4、查看各地点间最短路径       **");
	printf(" \n\t**                                                                    **");
	printf(" \n\t**      5、查询各地点间可行路径         6、最小生成树求解最短路径     **");
	printf(" \n\t**                                                                    **");
	printf(" \n\t**      7、求解拓扑受限的最短路径       8、退出                       **");
	printf(" \n\t**                                                                    **");
	printf(" \n\t************************************************************************");
	printf("\n");
	printf("请输入你的选择:");
}

int input1() {     //输入检测1，判断菜单输入的数是否合理，不合理则再次输入
	int m;
	char n = 1;
	scanf("%d", &m);
	while (n)
	{
		if (m < 1 || m>8)
		{
			printf("输入错误,请再次输入:");
			scanf("%d", &m);
		}
		else
			n = 0;
	}
	return m;
}
void CreateLGraph(LGraph*& G, int A[MaxVertexNum][MaxVertexNum], int Nv, int Ne)    //创建地图的邻接表
{
	int i, j;
	ENode* p;
	G = (LGraph*)malloc(sizeof(LGraph));
	for (i = 0; i < Nv; i++)
		G->Adjlist[i].FirstEdge = NULL;                            //给邻接表所有头结点的指针域置初值
	for (i = 0; i < Nv; i++)                                            //检查邻接矩阵中的每一个元素
		for (j = Nv - 1; j >= 0; j--)
			if (A[i][j] != 0 && A[i][j] != INFINIFY)                         //存在一条边
			{
				p = (ENode*)malloc(sizeof(ENode));            //创建一个结点p
				p->Adjv = j;
				p->weight = A[i][j];
				p->Next = G->Adjlist[i].FirstEdge;               //采用头插入法插入节点p
				G->Adjlist[i].FirstEdge = p;
			}
	G->Nv = Nv;
	G->Ne = Nv;
}
void CreateGraph(MGraph& g, int A[MaxVertexNum][MaxVertexNum], int Nv, int Ne)      //创建图的邻接矩阵
{
	int i, j;
	g.Nv = Nv;
	g.Ne = Ne;
	for (i = 0; i < g.Nv; i++)
		for (j = 0; j < g.Ne; j++)
			g.G[i][j] = A[i][j];
}
void PutMGraph(MGraph g)                 //输出邻接矩阵g
{
	int i, j;
	for (i = 0; i < g.Nv; i++)
	{
		for (j = 0; j < g.Nv; j++)
			if (g.G[i][j] != INFINIFY)
				printf("%4d", g.G[i][j]);
			else
				printf(" %4s", "∞");
		printf("\n");
	}
}
void Bestlu(LGraph* G, int z, char R[MaxVertexNum][MaxVertexNum])    ///找寻最佳浏览路线函数
{
	ENode* p;
	int t[MaxVertexNum];
	int top = -1, y, x, i;
	for (i = 0; i < G->Nv; i++)
		visited[i] = 0;                  ///将访问标志均置为0,代表未访问过
	printf("%s", R[z]);                   ///访问顶点v
	visited[z] = 1;                      ///表示顶点v已被访问
	top++;
	t[top] = z;                          ///将顶点v进栈
	while (top > -1)                      ///判断栈是否为空，为空则不进入循环
	{
		x = t[top];                      ///取栈顶顶点x作为当前顶点
		p = G->Adjlist[x].FirstEdge;      ///找顶点x的第一个相邻点
		while (p != NULL)                 ///判断节点是否为空
		{
			y = p->Adjv;               ///x的相邻点为y
			if (visited[y] == 0)          ///判断顶点y是否已访问
			{
				printf(" -> %s", R[y]);    ///访问顶点y
				visited[y] = 1;          ///重置顶点y已被访问
				top++;
				t[top] = y;              ///将顶点y进栈
				break;                 ///退出循环，即再处理栈顶点的顶点（体现先进后出）
			}
			p = p->Next;              ///找顶点x的下一个相邻点
		}
		if (p == NULL)
			top--;                     ///若顶点x在没有相邻点，将其退栈
	}
	printf("\n");
}

int input2(int& Nv, int B[MaxVertexNum])              //输入函数2
{
	int m, y = 0;
	char n = 1;
	scanf("%d", &m);
	while (m != 88)                       ///判断输入是否进行循环
	{
		while (n)                         ///判断输入是否进行循环
		{
			if (m<1 || m>Nv)                   ///判断输入值的是否正确
			{
				printf("该地标节点不存在请重新输入:");
				scanf("%d", &m);             ///判断输入错误重新输入
			}
			if (B != NULL)                    ///判断一位数组B是否为空
			{
				for (int i = 0; i < MaxVertexNum; i++)    ///判断该数值是否存在于数组B
					if (B[i] == m)
						y++;               ///存在则y++
				if (y <= 0)                   ///判断该输入节点是否存在
				{
					printf("该地标节点不存在请重新输入:");
					scanf("%d", &m);        ///不存在则重新输入
				}
				else
					n = 0;               ///如果属于上面两种情况则退出该循环
			}
			else
				n = 0;
		}
		break;
	}
	return m;                           ///返回输入值
}
void DestroyLGraph(LGraph* G)//销毁邻接表
{
	ENode* pre, * p;
	for (int i = 0; i < G->Nv; i++)
	{
		pre = G->Adjlist[i].FirstEdge;
		if (pre != NULL)
		{
			p = pre->Next;
			while (p != NULL)
			{
				free(pre);
				pre = p;
				p = p->Next;
			}
			free(pre);
		}
	}
	free(G);
}

///问题1，输出基本信息
void place(int A[MaxVertexNum][MaxVertexNum], char R[MaxVertexNum][MaxVertexNum], int Nv)   ///需要增添输出地点信息
{
	int k = 0;
	for (int i = 0; i < Nv; i++)
    {
        printf("%s ", &R[i]);
    }
    printf("\n");
	for (int i = 0; i < Nv; i++)
	{
		for(int j = i; j < Nv; j++)
		{
			if(A[i][j] != INFINIFY && i != j){
                k++;
                printf("%d %s %s %d\n", k, &R[i], &R[j], A[i][j]);
			}
		}

	}
}

///问题2
int isExist(int& Nv,char R[MaxVertexNum][MaxVertexNum],char x[100])  ///判断输入的地点是否已存在
{
    int i = 0;
    while (i != Nv)
    {
        if (R != NULL) {
            for (i = 0; i < Nv; i++)
                if (strcmp(R[i], x) == 0) {
                    return i;       ///返回字符串x所在的位置
                }
        } else
            return -1;
    }
    return -1;          ///出界或数组为空，都返回-1
}

 void modify(int A[MaxVertexNum][MaxVertexNum], int& Nv, int& Ne, char R[MaxVertexNum][MaxVertexNum]) {
    MGraph g;
    int c, d, t, i = 0, j;
    int w = 0;
    char x[100];
    printf("\n");
    printf("\n");
    printf("\t**************修改菜单***************");
    printf("\n\t**       (1)增加地标节点           **");
    printf("\n\t**       (2)删除地标节点           **");
    printf("\n\t*************************************\n");
    printf("输入你需要查询的菜单选项编号:");
    int a = input3();  ///调用input3函数获取值

    switch (a)          ///对数值a进行判断
    {
    case 1:
        printf("输入需要添加的地点名称:");
        scanf("%s", &x);

        if(isExist(Nv, R, x) != -1)       ///判断输入的地点是否已经存在
        {
            printf("该地标节点已存在!");
            return;
        }

        strcpy(R[Nv], x);  ///将新增的结点添加进R数组
        for (i = 0; i < MaxVertexNum; i++)
				for (j = 0; j < MaxVertexNum; j++)
				{
					if (i == Nv)
						A[i][j] = INFINIFY;
					if (j == Nv)
						A[i][j] = INFINIFY;
					if (i == Nv && j == Nv)
						A[i][j] = 0;
				}
			B[Nv] = Nv + 1;
			Nv = Nv + 1;

        printf("已结束输入，输出新生成的图:\n");
        CreateGraph(g, A, Nv, Ne);
        place(A, R, Nv);
        break;

	case 2:
        printf("请输入需要删除的地标节点：");
        scanf("%s", &x);
        int k = isExist(Nv, R, x);
        while (k == -1) /// 地点不存在则重新输入
        {
            printf("该地点不存在，请重新输入：");
            scanf("%s", &x);
            k = isExist(Nv, R, x);
        }

        for (int i = k; i < Nv - 1; i++) /// 从R数组中删除结点
        {
            strcpy(R[i], R[i + 1]);
        }

        for (int i = 0; i < Nv; i++)
        {
            for (int j = k; j < Nv - 1; j++) /// 从A数组中删除结点对应的行和列
            {
                A[i][j] = A[i][j + 1];
            }
            A[i][Nv - 1] = INFINIFY; /// 将结点对应的列初始化为无穷大
        }

        for (int i = k; i < Nv - 1; i++)
        {
            for (int j = 0; j < Nv; j++) /// 从A数组中删除结点对应的行
            {
                A[i][j] = A[i + 1][j];
            }
        }

        Nv--; /// 更新顶点数
        Ne -=  Nv - k; /// 更新边数，每删除一个节点，相关边数减2

        CreateGraph(g, A, Nv, Ne);
        //PutMGraph(g);
        place(A, R, Nv);
        break;
	}
}

///问题3
void path(int A[MaxVertexNum][MaxVertexNum], int& Nv, int& Ne, char R[MaxVertexNum][MaxVertexNum]) {
    MGraph g;
    int d, m,n, i = 0, j;
    int w = 0;
    char x[100],y[100];
    printf("\n");
    printf("\n");
    printf("\t**************修改菜单***************");
    printf("\n\t**       (1)增加路径           **");
    printf("\n\t**       (2)删除路径           **");
    printf("\n\t*************************************\n");
    printf("输入你需要查询的菜单选项编号:");
    int a = input3();  ///调用input3函数获取值


    switch (a)          ///对数值a进行判断
    {
    case 1:
        printf("输入需要添加路径的两个地点名称以及路径长度:");
        scanf("%s %s %d", &x,&y,&d);
        m=isExist(Nv,R,x);
        n=isExist(Nv,R,y);

        if(m == -1 || n == -1){
           printf("抱歉，您输入的地址有误！");
           break;
        }
        else Ne = Ne + 1;

        while(w<1)
        {
           for (i = 0; i < MaxVertexNum; i++)                       ///将该节点对应的边进行添加
				for (j = 0; j < MaxVertexNum; j++)
				{
					if (i == m && j == n)
					{
						A[i][j] = d;
						A[j][i] = d;
						w++;
					}
				}


        }
        printf("已结束输入，输出新生成的图:\n");
        CreateGraph(g, A, Nv, Ne);
        //PutMGraph(g);
        place(A, R, Nv);
        break;
	case 2:
	    printf("请输入需要删除路径的两个地点：");
	    scanf("%s %s", &x, &y);
        m=isExist(Nv,R,x);  ///判断是否添加的地标节点已存在
        n=isExist(Nv,R,y);
        if(m == -1 || n == -1){
                printf("抱歉，您输入的地址有误!");
                return;
        } else {
            for (int i = 0; i < Nv; i++)                           ///将想要删除的节点进行初始化删除
            for (int j = 0; j < Nv; j++)
            {
                if (i == m && j == n){
                    A[i][j] = INFINIFY;
                    A[j][i] = INFINIFY;
                    Ne--;
                    break;
                }
            }
        CreateGraph(g, A, Nv, Ne);
        //PutMGraph(g);
        place(A,R,Nv);
		break;
        }
	}
}
///问题4

int printShortestPath(int src, int dest, int dist[], int path[], char R[MaxVertexNum][MaxVertexNum]) {
    int stack[MaxVertexNum];
    int top = 0;
    int p = dest;
    while (p != src) {
        //cout << p << endl;
        stack[top++] = p;
        p = path[p];
    }
    printf("最短路径为：");
    for (int i = top - 1; i >= 0; --i) {
        printf("%s", R[stack[i]]);
        if (i > 0) printf(" -> ");
    }
    printf("\n路径长度为：%d\n", dist[dest]);
    int length=dist[dest];
    return length;
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

void ShortestPath(MGraph g, int A[MaxVertexNum][MaxVertexNum], int& Nv, int& Ne)
{
    char src[MaxVertexNum], dest[MaxVertexNum];
    printf("请输入出发点和目的地，为您规划最短路径：\n");
    scanf("%s %s",&src,&dest);
    CreateGraph(g, A, Nv, Ne);

    int dist[MaxVertexNum];
    int path[MaxVertexNum];
    int s,d;
    s = isExist(Nv, R, src);
    d = isExist(Nv, R, dest);
    if(s==-1 || d==-1){
        printf("抱歉，您输入的地址有错！");
        return;
    }
    Dijkstra(g, s, d, dist, path);

    printShortestPath(s, d, dist, path, R);
}
///问题5

void DFS(int src, int dest, int numVertices, int count, int distance, vector<int>& path, int visited[]) {
    visited[src] = 1;
    path.push_back(src);
    cout << "cnt= " << count << " " << src << " " << dest << endl;
    for (int i = 0; i < path.size(); i++)
    {
       cout << path[i] << " ";
    }
    cout << endl;
    if (count == numVertices && src == dest) {
        if (distance < minDistance) {
            minDistance = distance;
            cout << "最短路径长度为：" << minDistance << endl;
            cout << "最短路径为：";
            for (int i = 0; i < path.size(); ++i) {
                cout << R[path[i]]<< " ";
            }
            cout << endl;
            return;
        }
    }
    else {
        if (count > numVertices) {
            return; // 已经经过的顶点数（包括起点和终点）超过了指定的数量，直接返回
        }
        for (int i = 0; i < 14; ++i) {
            if (A[src][i] != INFINIFY && !visited[i]) {
                DFS(i, dest, numVertices, count + 1, distance + A[src][i], path, visited);
                path.pop_back();
                //std::cout << "chuzhan" << std::endl;
                distance -= A[src][i];
            }
        }
    }

    // Backtrack
    visited[src] = 0;
}

vector<string> shortest_path;
int shortest_length = INT_MAX;
typedef pair<int,int> spot_pair;
void dfs(int cur, int end, int n, int len, vector<string> route, map<int,bool> visit)
{
    //for (auto it : route)
    //{
        //cout << it << " ";
    //}
    //cout << endl;
    if (cur == end)
    {
        if (route.size() == n && len < shortest_length)
        {
            shortest_length = len;
            shortest_path = route;
        }
    }
    if (route.size() == n)
    {
        return;
    }
    visit[cur] = true;
    for (int i = 0; i < 14; i++)
    {
        if (visit[i] || A[cur][i] == INFINIFY)
        {
            continue;
        }
        route.push_back(R[i]);
        len += A[cur][i];
        dfs(i,end,n,len,route,visit);
        route.pop_back();
        len -= A[cur][i];
    }
    visit[cur] = false;
}

void findShortestPath(int src, int dest, int numVertices) {
    //int visited[MaxVertexNum] = {0};
    //vector<int> path;
    //DFS(src, dest, numVertices, 0, 0, path, visited);
    map<int,bool> visit;
    vector<string> route;
    int len = 0;
    route.push_back(R[src]);
    dfs(src,dest,numVertices,len,route,visit);
    if (shortest_length != INT_MAX)
    {
        for (int i = 0; i < shortest_path.size(); i++)
        {
            cout << shortest_path[i] << " ";
        }
        cout << "该最短路径长度为" << shortest_length << endl;
    }
    else
    {
        cout << "无法找到路径" << endl;
    }
}


///问题6

// 查找具有最小键值的顶点
int minKey(int key[], int mstSet[], int Nv) {
    int min = INFINIFY, min_index;

    for (int v = 0; v < Nv; v++) {
        if (mstSet[v] == 0 && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }

    return min_index;
}
void GreateMST(int& Nv, char R[MaxVertexNum][MaxVertexNum],int A[MaxVertexNum][MaxVertexNum]) {
    int n;
    printf("输入：\n");
    scanf("%d\n",&n);
    int nv = n;

    char Tr[MaxVertexNum][MaxVertexNum];
    int Tb[MaxVertexNum];
    int Ta[MaxVertexNum][MaxVertexNum];
    for(int i = 0; i < n; i++)
    {
        scanf("%s",&Tr[i]);
        Tb[i]=isExist(Nv,R,Tr[i]);
    }
    int k = 0;
    for(int i = 0; i < MaxVertexNum; i++)///把对应的路径长度储存到Ta中
    {
        if(i == Tb[k])
        {
            int m = 0;
            for(int j = 0; j < MaxVertexNum; j++)
            {
                if(j == Tb[m])
                {
                    Ta[k][m] = A[i][j];
                    m++;
                }
            }
            k++;
        }
    }

    // 创建最小生成树
    int parent[MaxVertexNum];
    int key[MaxVertexNum];     // 用于选择切割中最小权重边的关键值
    int mstSet[MaxVertexNum]; // 表示包含在MST中的一组顶点

    // 初始化
    for (int i = 0; i < Nv; i++) {
        key[i] = INFINIFY;
        mstSet[i] = 0;
    }
    key[0] = 0;
    parent[0] = -1;

    for (int i = 0; i < Nv - 1; i++) {
        // 从尚未包含在MST中的顶点集合中选择最小键顶点
        int j = minKey(key, mstSet, Nv);

        // 将选中的顶点添加到MST集合中
        mstSet[j] = 1;

        // 更新所选顶点的相邻顶点的键值和父索引
        for (int k = 0; k < Nv; k++) {
            // Ta[j][k]仅对m的相邻顶点不为零
            //对于尚未包含在MST中的顶点，mstSet[k]为false
            //只有当Ta[j][k]小于key[k]时才更新键
            if (Ta[j][k] && mstSet[k] == 0 && Ta[j][k] < key[k]) {
                parent[k] = j;
                key[k] = A[j][k];
            }
        }
    }

    printf("Minimum Spanning Tree:\n");
    for (int i = 1; i < Nv; i++)
        printf("%d - %d\n", parent[i], i);

}


int input3()              //输入函数3
{
	int x;
	char m = 1;
	scanf("%d", &x);
	while (m)
	{
		if (x > 2 || x < 1)          ///判断数值是否输入正确
		{
			printf("输入错误，请重新输入:");
			scanf("%d", &x);
		}
		else
			m = 0;            ///输入正确则退出循环
	}
	return x;               ///返回该输入值
}
int main() {
	Caidan();
	MGraph g;
	LGraph* G;

	int Nv = 14, Ne = 24;
	int x, z;
	x = input1();
	while (1)
	{
		switch (x)
		{
		case 1:
			printf("\n输出该图的地点信息和道路信息:\n");
			place(A, R, Nv);
			printf("\n已返回主菜单，请输入需要查询的菜单栏选项:\n");
			printf("\n");
			Caidan();
			x = input1();
			break;
		case 2:
			printf("\n根据提示选择增删地点信息\n");
			modify(A, Nv, Ne, R);
			printf("\n已返回主菜单，请输入需要查询的菜单栏选项:\n");
			printf("\n");
			Caidan();
			x = input1();
			break;
		case 3://修改路径
		    printf("\n根据提示修改路径信息\n");
			path(A, Nv, Ne, R);
			printf("\n已返回主菜单，请输入需要查询的菜单栏选项:\n");
			printf("\n");
			Caidan();
			x = input1();
			break;

		case 4:
			printf("输入两个地点，为您规划最短路径");
			ShortestPath(g, A, Nv, Ne);
			printf("\n已返回主菜单，请输入需要查询的菜单栏选项:\n");
			printf("\n");
			Caidan();
			x = input1();
			break;
		case 5:
		    {
			int src, dest, numVertices;
            cout << "请输入起始地点、目标地点和经过的顶点数量：" << endl;
            cin >> src >> dest >> numVertices;

            findShortestPath(src, dest, numVertices);

			printf("\n已返回主菜单，请输入需要查询的菜单栏选项:\n");
			printf("\n");
			Caidan();
			x = input1();
			break;
		    }
		case 6:
			printf("从最小生成树中求解途径地点受限的最短路径");
			printf("请输入正整数n，以及n个地点名称。");
			GreateMST(Nv, R, A);
			Caidan();
			x = input1();
			break;
		case 7://修改地图信息
			modify(A, Nv, Ne, R);
			printf("\n已返回主菜单，请输入需要查询的菜单栏选项:\n");
			printf("\n");
			Caidan();
			x = input1();
		}

		if (x == 8)
			break;
	}
	printf("\n已退出系统，想要继续操作请重新进入！\n");
	return 1;
}
