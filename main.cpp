#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#define INFINIFY 65535   //定义无穷大
#define MaxVertexNum 100    //定义最大定点数
int visited[MaxVertexNum];
/*
char Q[MaxVertexNum][MaxVertexNum] = {
 */

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
void map();//地图绘制
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
	printf(" \n\t**                      欢迎来到广东东软学院                          **");
	printf(" \n\t**                         菜单选择                                   **");
	printf(" \n\t**                                                                    **");
	printf(" \n\t**      1、地点信息查看                 2、查看浏览路线 ！            **");
	printf(" \n\t**                                                                    **");
	printf(" \n\t**      3、修改路径信息                 4、查看各地点间最短路径       **");
	printf(" \n\t**                                                                    **");
	printf(" \n\t**      5、查询各地点间可行路径         6、打印邻接矩阵               **");
	printf(" \n\t**                                                                    **");
	printf(" \n\t**      7、修改地图信息                 8、退出                       **");
	printf(" \n\t**                                                                    **");
	printf(" \n\t************************************************************************");
	printf("\n");
	printf("请输入你的选择:");
}
/*
void  map()//地图查看
{
	printf("\n");
	printf("\n");
	printf("***********************************************************************************************************************\t\t\t\t\t");
	printf("\n");
	printf("**----------------------------------------------------------(10)a栋教学楼--------------------------------------------**\t\t\t\t\t");
	printf("\n");
	printf("**----------------------------------------------------------(9)b栋教学楼---------------------------------------------**\t\t\t\t\t");
	printf("\n");
	printf("**---(8)运动场-----------------------(6)c栋教学楼------------------------------(11)行政楼----------------------------**\t\t\t\t\t");
	printf("\n");
	printf("**-----------------------------------(5)图书馆---------------------------------(12)继教学院-----(13)雨湖-------------**\t\t\t\t\t");
	printf("\n");
	printf("**---(4)e栋教学楼-----------------------------------------------(14)足球场-------------------------------------------**\t\t\t\t\t");
	printf("\n");
	printf("**---(3)f栋教学楼----------------(7)报告厅---------------------------------------------------------------------------**\t\t\t\t\t");
	printf("\n");
	printf("**-- (1)新生公寓------------------(2)学二食堂------------------------------------------------------------------------**\t\t\t\t\t");
	printf("\n");
	printf("**------------------------ (18)国际交流中心--------(15)d栋教学楼-----------------(16)龙翔食堂-----(17)继续教育学院---**\t\t\t\t\t");
	printf("\n");
	printf("***********************************************************************************************************************\t\t\t\t\t");
	printf("\n");
	printf("\n");
}
*/
int input1() {     //判断菜单输入的数 是否合理，不合理则再次输入
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
				printf(" %4s ", "∞");
		printf("\n");
	}
}
void printShortestPath(int src, int dest, int dist[], int path[], char R[MaxVertexNum][MaxVertexNum]) {
    //cout << "1" << endl;
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
}

void Dijkstra(MGraph g, int src, int dest, int dist[], int path[]) {
    int visited[MaxVertexNum] = {0}; // 标记顶点是否被访问
    int i, j, k, min;

    for (i = 0; i < g.Nv; ++i) {
        dist[i] = g.G[src][i]; // 初始化距离
        //cout << dist[i] << endl;
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
    for (j = 0; j < g.Nv; ++j)
    {
        //cout << path[j] << endl;
    }

}

void place(int A[MaxVertexNum][MaxVertexNum], int Nv)   //问题1，输出基本信息
{
	int k = 0;
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
void AvabilePath(LGraph* G, int Nv, char R[MaxVertexNum][MaxVertexNum], int B[MaxVertexNum])                    ///输出各地点间可行路径函数
{

	printf("输入你所需要查询的地点名称:");
	ENode* p;
	//char x[100], y[100];
	int i = input2(Nv, B);
	int j;
                                                            ///输入需要查询地标的编号
	while (i != 88)                                                                ///判断输入值是否为88，是则返回主菜单
	{
		p = G->Adjlist[i - 1].FirstEdge;                                                ///指向需要查询地点的第一条边
		printf("地点%s的可行路径:\n", R[i - 1]);
		if (p == NULL)                                                                ///判断该地点是否存在边
			printf("不存在该地点,无可行路径");
		while (p != NULL)
		{
			j = p->Adjv;
			printf("  可以到达%3s路程长为%d米\n", R[j], p->weight);
			p = p->Next;                                                            ///指向下一条边
		}
		printf("\n");
		printf("继续查询请输入地点坐标，返回菜单请输入(88):");
		i = input2(Nv, B);
	}
}
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
            printf("该地标节点已存在请重新输入:");
            scanf("%s", &x);
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
        PutMGraph(g);
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
        PutMGraph(g);

        break;
	}
}

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



            if (R != NULL) {
                for (i = 0; i < Nv; i++)
                    if (strcmp(R[i], x) == 0) {
                        m = i;
                        printf("第一个地点编号为%d:",m);
                        //continue;
                    }

            } else
                break;
        if (R != NULL) {
                for (i = 0; i < Nv; i++)
                    if (strcmp(R[i], y) == 0) {
                        n = i;
                        printf("第二个地点编号为%d:",n);
                        //continue;
                    }

            } else
                break;

        if(m == Nv || n == Nv) printf("抱歉，您输入的地址有误！");
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
        PutMGraph(g);
        break;
	case 2:
	    printf("请输入需要删除路径的两个地点：");
	    scanf("%s %s", &x, &y);
        for (i = 0; i < Nv; i++)
        {
            if (strcmp(R[i], x) == 0)    ///判断是否添加的地标节点已存在
                m= i;
        }
        for (i = 0; i < Nv; i++)
        {
            if (strcmp(R[i], y) == 0)
                n = i;
        }
        if(m == Nv || n == Nv){
                printf("该地标节点不存在");
        } else {

            printf("该节点编号是%d, %d", m, n);
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
        PutMGraph(g);

		break;

        }

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
			printf("\n地点信息查看:");
			printf("\n");
			place(A, Nv);
			printf("\n已返回主菜单，请输入需要查询的菜单栏选项:\n");
			printf("\n");
			Caidan();
			x = input1();
			break;
		case 2:
		    /*
			printf("输入你所在的位置，为你规划浏览路线：");
			CreateLGraph(G, A, Nv, Ne);
			z = input2(Nv, B) - 1;
			Bestlu(G, z, R);
			printf("\n");
			DestroyLGraph(G);
			printf("\n已返回主菜单，请输入需要查询的菜单栏选项:\n");
			printf("\n");
			Caidan();
			x = input1();
			*/
			break;
		case 3://修改路径
			path(A, Nv, Ne, R);
			printf("\n已返回主菜单，请输入需要查询的菜单栏选项:\n");
			printf("\n");
			Caidan();
			x = input1();
			break;

		case 4:
		    /*
			printf("输入你所在的位置，为你规划最短路径：");
			CreateGraph(g, A, Nv, Ne);
			z = input2(Nv, B) - 1;
			Shortlu(g, z, Nv, B, R);
			printf("\n已返回主菜单，请输入需要查询的菜单栏选项:\n");
			printf("\n");
			Caidan();
			x = input1();
			break;
			*/
			printf("输入两个地点，为您规划最短路径");
			CreateGraph(g, A, Nv, Ne);
			//z = input2(Nv, B) - 1;
			int dist[MaxVertexNum];
			int path[MaxVertexNum];
            int src,dest;
            char place1[MaxVertexNum], place2[MaxVertexNum];
            scanf("%s %s", place1, place2);
            for (int i = 0; i < Nv; ++i) {
                if (strcmp(R[i], place1) == 0) {
                    src = i;
                }
                if (strcmp(R[i], place2) == 0) {
                    dest = i;
                }
            }

			Dijkstra(g, src, dest, dist, path);

            printShortestPath(src, dest,dist, path, R);
            //cout << "1" << endl;
			printf("\n已返回主菜单，请输入需要查询的菜单栏选项:\n");
			printf("\n");
			Caidan();
			x = input1();
			break;
		case 5:
			printf("\n各地点间可行路径查看:\n");
			CreateLGraph(G, A, Nv, Ne);
			AvabilePath(G, Nv, R, B);
			DestroyLGraph(G);
			printf("\n已返回主菜单，请输入需要查询的菜单栏选项:\n");
			printf("\n");
			Caidan();
			x = input1();
			break;
		case 6:
			printf("\n打印邻接矩阵:\n");
			CreateGraph(g, A, Nv, Ne);
			PutMGraph(g);
			printf("\n已返回主菜单，请输入需要查询的菜单栏选项:\n");
			printf("\n");
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
