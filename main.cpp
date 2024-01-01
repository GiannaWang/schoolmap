#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#define INFINIFY 65535   //定义无穷大
#define MaxVertexNum 100    //定义最大定点数
#include<vector>
#include<iostream>
#include<map>
#include<set>
#include<queue>
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
	char xinxi[50];      //顶点其他信息
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
void PutShortlu(MGraph g, int dist[], int path[], int S[], int z, int& Nv, int B[MaxVertexNum], char R[MaxVertexNum][MaxVertexNum]);   //输出从顶点v出发的所有最短路径
void Shortlu(MGraph g, int z, int& Nv, int B[MaxVertexNum], char R[MaxVertexNum][MaxVertexNum]);	//找寻最短路径函数
 void modify(int A[MaxVertexNum][MaxVertexNum], int& Nv, int& Ne, char R[MaxVertexNum][MaxVertexNum]);        //图的修改函数
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

void CreateGraph(MGraph& g, int A[MaxVertexNum][MaxVertexNum], int Nv, int Ne)      //创建图的邻接矩阵
{
	int i, j;
	g.Nv = Nv;
	g.Ne = Ne;
	for (i = 0; i < g.Nv; i++)
		for (j = 0; j < g.Ne; j++)
			g.G[i][j] = A[i][j];
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
MGraph mgraph;
void InitGraph(MGraph& mgraph) {
    int i, j;

    mgraph.Nv = 14; //无向图顶点个数
    mgraph.Ne = 26; //边数

    strcpy(mgraph.Data[0].xinxi, "北门");
    strcpy(mgraph.Data[1].xinxi, "西北门");
    strcpy(mgraph.Data[2].xinxi, "河西食堂");
    strcpy(mgraph.Data[3].xinxi, "游泳池");
    strcpy(mgraph.Data[4].xinxi, "河东食堂");
    strcpy(mgraph.Data[5].xinxi, "理科大楼");
    strcpy(mgraph.Data[6].xinxi, "毛主席像");
    strcpy(mgraph.Data[7].xinxi, "图书馆");
    strcpy(mgraph.Data[8].xinxi, "篮球馆");
    strcpy(mgraph.Data[9].xinxi, "文史楼");
    strcpy(mgraph.Data[10].xinxi, "文科大楼");
    strcpy(mgraph.Data[11].xinxi, "体育馆");
    strcpy(mgraph.Data[12].xinxi, "东门");
    strcpy(mgraph.Data[13].xinxi, "文附楼");

    for (i = 0; i < mgraph.Nv; i++) {
        for (j = 0; j < mgraph.Nv; j++) {
            mgraph.G[i][j] = INFINIFY;
        }
    }
    for (i = 0; i < mgraph.Nv; i++) {

            mgraph.G[i][i] = 0;

    }
    mgraph.G[0][3] = mgraph.G[3][0] = 152;
    mgraph.G[1][5] = mgraph.G[5][1] = 312;
    mgraph.G[1][2] = mgraph.G[2][1] = 96;
    mgraph.G[2][5] = mgraph.G[5][2] = 281;
    mgraph.G[2][6] = mgraph.G[6][2] = 318;
    mgraph.G[2][7] = mgraph.G[7][2] = 323;
    mgraph.G[2][3] = mgraph.G[3][2] = 532;
    mgraph.G[3][7] = mgraph.G[7][3] = 98;
    mgraph.G[3][8] = mgraph.G[8][3] = 143;
    mgraph.G[3][4] = mgraph.G[4][3] = 251;
    mgraph.G[4][9] = mgraph.G[9][4] = 85;
    mgraph.G[5][6] = mgraph.G[6][5] = 145;
    mgraph.G[5][7] = mgraph.G[7][5] = 442;
    mgraph.G[5][10] = mgraph.G[10][5] = 541;
    mgraph.G[6][7] = mgraph.G[7][6] = 226;
    mgraph.G[7][8] = mgraph.G[8][7] = 112;
    mgraph.G[7][10] = mgraph.G[10][7] = 437;
    mgraph.G[8][10] = mgraph.G[10][8] = 346;
    mgraph.G[8][9] = mgraph.G[9][8] = 96;
    mgraph.G[8][11] = mgraph.G[11][8] = 412;
    mgraph.G[9][11] = mgraph.G[11][9] = 348;
    mgraph.G[9][12] = mgraph.G[12][9] = 261;
    mgraph.G[10][11] = mgraph.G[11][10] = 162;
    mgraph.G[10][13] = mgraph.G[13][10] = 47;
    mgraph.G[11][13] = mgraph.G[13][11] = 198;
    mgraph.G[11][12] = mgraph.G[12][11] = 187;

}
int locate(MGraph& g,string s)
{
    for(int i=0;i<g.Nv;i++){if(s==g.Data[i].xinxi)return i;}
    return -1;
}
vector<pair<int, int>> prim(MGraph& g,vector<int>&keyLocations) {
    vector<pair<int, int>> minSpanningTree;
    vector<bool> visited(g.Nv, false);
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;
    int startVertex = keyLocations[0];
    visited[startVertex] = true;

    // 将起始点的边加入优先队列
    for (int neighbor = 0; neighbor < g.Nv; ++neighbor) {
        if (g.G[startVertex][neighbor] !=INFINIFY) {
            pq.push({g.G[startVertex][neighbor], {startVertex, neighbor}});
        }
    }

    while (!pq.empty()) {
        int u = pq.top().second.first;
        int v = pq.top().second.second;
        pq.pop();

        if (visited[u] && visited[v]) {
            continue;  // 避免形成环
        }

        // 将当前边加入最小生成树
        minSpanningTree.push_back({u, v});

        // 标记已访问的节点
        visited[u] = true;
        visited[v] = true;

        // 将新加入的节点的边加入优先队列
        for (int neighbor = 0; neighbor <g.Nv; ++neighbor) {
            if (!visited[neighbor] && g.G[v][neighbor] != INFINIFY) {
                pq.push({g.G[v][neighbor], {v, neighbor}});
            }
        }
    }

    return minSpanningTree;
}

void backtrack(map<pair<int,int>,bool>&visit,vector<pair<int, int>>&position,MGraph& g,vector<int>& currentPath, vector<int>& bestPath, vector<bool>& visited, int currentLength, int& minLength, const vector<int>& keyLocations) {
    int lastVisited = currentPath.back();
    int s=1;
    for(auto i:keyLocations){
        if(visited[i]==false){s=0;break;}
    }
    if (s) {
        if (currentLength < minLength) {
            minLength = currentLength;
            bestPath = currentPath;

        }
        return;
    }
    set<int>pos;
    for(auto e:position){
        if(e.first==lastVisited)pos.insert(e.second);
        if(e.second==lastVisited)pos.insert(e.first);
    }

    for (auto next:pos) {
        if(!visit[{lastVisited,next}]){
        for(auto e:position){
        if(e.first==lastVisited)pos.insert(e.second);
        if(e.second==lastVisited)pos.insert(e.first);
    }

    for (auto next:pos) {
            if(!visit[{lastVisited,next}]){
            int weight = g.G[lastVisited][next];
            if (weight != INFINIFY) {
                currentPath.push_back(next);
                int flag=0;
                visit[{lastVisited,next}]=true;
                if(visited[next]==true)flag=1;
                else visited[next]=true;
                backtrack(visit,position,g,currentPath, bestPath, visited, currentLength + weight, minLength, keyLocations);
                currentPath.pop_back();
                visit[{lastVisited,next}]=false;
                if(!flag)visited[next]=false;
            }}

    }
}
    }
}

void prim_shortest(MGraph& g)
{
    int n;
     cout<<"请输入您想参观的地点数目，如果想退出函数请输入-1"<<endl;
    while(cin>>n&&n!=-1){
    vector<int>keyLocations;
    int flag=1;
    string s;
    cout<<"请输入您想参观的地点:"<<endl;
    for(int i=0;i<n;i++){
        cin>>s;
        int temp=locate(g,s);
        if(temp==-1){cout<<"不合理，重新输入！"<<endl;flag=0;break;}
        else keyLocations.push_back(temp);
    }
    if(flag){
    vector<pair<int, int>>position=prim(g,keyLocations);
    map<pair<int,int>,bool>v;
    for(auto e :position){v[e]=false;
    v[{e.second,e.first}]=false;}
    vector<int> currentPath = {keyLocations[0]};
    vector<int> bestPath;
    vector<bool> visited(g.Nv, false);
    visited[keyLocations[0]] =true;
    int minLength = INFINIFY;
    backtrack(v,position,g,currentPath, bestPath, visited, 0, minLength, keyLocations);

    set<int>poss;
    for(auto e:position){
    poss.insert(e.first);
    poss.insert(e.second);}
    cout<<"最小生成树："<<endl;
    cout<<"地点信息："<<endl;
    for(auto e:poss){
        cout<<g.Data[e].xinxi<<' ';
    }
    cout<<endl<<"道路信息："<<endl;
    for(auto e:position){
        cout<<g.Data[e.first].xinxi<<' '<<g.Data[e.second].xinxi<<' '<<g.G[e.first][e.second]<<endl;
    }
    if(bestPath.size()!=0){
    cout << "最短路径：";
    for (int vertex : bestPath) {
        cout << g.Data[vertex].xinxi << " ";
    }
    cout << endl<< "路径长度：" << minLength << endl;}
    else cout<<"该限制条件下无路径可达"<<endl;
    }

     if(flag)cout<<"请输入您想参观的地点数目，如果想退出函数请输入-1"<<endl;
     else cout<<"输入地点有误，请重新输入您想参观的地点数目，如果想退出函数请输入-1"<<endl;

    }
}


///问题7

void backt(vector<map<int,int>>&pos,MGraph& g,vector<int>& currentPath,
            vector<int>& bestPath, vector<bool>& visited, int currentLength,
            int& minLength, const vector<int>& keyLocations)
{
    int lastVisited = currentPath.back();
    if (lastVisited==keyLocations.back()){
        int s=1;
        for(auto i:keyLocations){
        if(visited[i]==false){s=0;break;}
        }
        int flag=1;
        for(auto e:pos){int m=0;flag=1;
        for(auto cur:currentPath){
                if(e[cur]){
                    if(e[cur]>=m){m=e[cur];}
                    else {flag=0;break;}
                }
            }
            if(flag==1)break;
            }
        if (s&&flag&&currentLength < minLength) {
            minLength = currentLength;
            bestPath = currentPath;

        }

        return;
    }


    for (int next=0;next<g.Nv;next++){
            if(!visited[next]){
            int weight = g.G[lastVisited][next];
            if (weight !=  INFINIFY) {
                currentPath.push_back(next);
                visited[next]=true;
                backt(pos,g,currentPath, bestPath, visited, currentLength + weight, minLength, keyLocations);
                currentPath.pop_back();
                visited[next]=false;
            }
            }

    }
}

void allTopologicalSortUtil(set<int>&poss,vector<int>*adj,vector<bool>&visited, vector<int>&indegree, vector<int> &ans,vector<vector<int>>& pos)
{
	if( ans.size() ==poss.size())
	{
		pos.push_back(ans);
		return ;
	}

	for(auto i: poss)
	{
		if(indegree[i]==0 && !visited[i])
		{
			for(auto j:adj[i])
			{
				indegree[j]--;
			}

			visited[i] = true;
			ans.push_back(i);

			allTopologicalSortUtil(poss,adj,visited, indegree, ans,pos);

			for(auto j:adj[i])
			{
				indegree[j]++;
			}

			visited[i] = false;
			ans.pop_back();
		}
	}
}



void tp_shortest(MGraph& g)
{
    cout<<"请输入您想参观的地点数目，如果想退出函数请输入-1"<<endl;
    int n;
    int flag;
    while(cin>>n&&n!=-1){
    vector<int>keyLocations;
    string s;
    flag=1;
    cout<<"请输入您想参观的地点:"<<endl;
    for(int i=0;i<n;i++){
        cin>>s;
        int temp=locate(g,s);
        //cout<<temp<<endl;
        if(temp==-1){flag=0;break;}
        else keyLocations.push_back(temp);
    }
    if(flag){
    vector<bool>visi(g.Nv,false);
    vector<int>indegree(g.Nv,0);
    vector<int>adj[g.Nv];
    vector<vector<int>>pos;
    vector<map<int,int>>poss;
     vector<int> ans;
    map<int,int>fd;
    cout<<"请输入您限制的地点参观顺序条目数："<<endl;
    int cnt;
    cin>>cnt;
    string s1,s2;
    set<int>s_set;
    cout<<"请输入您限制的地点数："<<endl;
    for(int i=0;i<cnt;i++){
        cin>>s1>>s2;
        int t1=locate(g,s1);
        int t2=locate(g,s2);
        //cout<<t1<<" "<<t2<<endl;
        s_set.insert(t1);
        s_set.insert(t2);
        indegree[t2]++;
        adj[t1].push_back(t2);
    }
    allTopologicalSortUtil(s_set,adj,visi, indegree, ans,pos);
    vector<int> currentPath = {keyLocations[0]};
    vector<int> bestPath;
    vector<bool> visited(g.Nv, false);
    visited[keyLocations[0]] =true;
    int minLength = INFINIFY;
    for(auto vec:pos){
        int k=1;
        for(auto t:vec){
            fd[t]=k;k++;
        }
        poss.push_back(fd);
        fd.clear();
    }
    if(poss.size()!=0){
    backt(poss,g,currentPath, bestPath, visited, 0, minLength, keyLocations);
    if(bestPath.size()!=0){
    cout << "最短参观路径：";
    for (int vertex : bestPath) {
        cout << g.Data[vertex].xinxi << " ";
    }
    cout<< endl << "路径长度：" << minLength << endl;}
    else cout<<"在该限制条件下无可达路径！"<<endl;
    }
    else flag=-1;
    }
    if(flag==1)cout<<"请输入您想参观的地点数目，如果想退出函数请输入-1"<<endl;
    else if(flag==0)cout<<"输入地点有误，请重新输入您想参观的地点数目，如果想退出函数请输入-1"<<endl;
    else cout<<"您输入的限制地点顺序成环，请重新输入"<<endl;
    }
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
			//GreateMST(Nv, R, A);
			prim_shortest(mgraph);
			Caidan();
			x = input1();
			break;
		case 7://修改地图信息

            InitGraph(mgraph);
            tp_shortest(mgraph);
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
