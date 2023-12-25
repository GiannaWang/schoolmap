#include<string.h>
#define INFINIFY 65535   //定义无穷大
#define MaxVertexNum 100    //定义最大定点数
int visited[MaxVertexNum];
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
		{INFINIFY,INFINIFY,INFINIFY,INFINIFY,INFINIFY,INFINIFY,INFINIFY,INFINIFY,INFINIFY,INFINIFY,INFINIFY,INFINIFY,312,96,0},//14
		//{800,INFINIFY,INFINIFY,INFINIFY,INFINIFY,INFINIFY,INFINIFY,INFINIFY,INFINIFY,INFINIFY,INFINIFY,INFINIFY,INFINIFY,INFINIFY,300,INFINIFY,INFINIFY,0},
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
	printf(" \n\t**      1、学校地图查看 (先bang掉）     2、查看浏览路线               **");
	printf(" \n\t**                                                                    **");
	printf(" \n\t**      3 查看各地点间最短路径          4、景点信息查询               **");
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
				printf("%4s", "∞");
		printf("\n");
	}
}
void PutShortlu(MGraph g, int dist[], int path[], int S[], int z, int& Nv, int B[MaxVertexNum], char R[MaxVertexNum][MaxVertexNum])   //输出从顶点v出发的所有最短路径
{
	int i, j, k;
	int apath[MaxVertexNum], d;					                           //存放一条最短路径(逆向)及其顶点个数
	printf("输入你要到达的地点：");
	i = input2(Nv, B);                                                 //循环输出从顶点v到i的路径
	i = i - 1;
	if (S[i] == 1 && i != z)
	{
		printf("  从地点%s到地点%s的最短路径长度为:%d\n 路径为:", R[z], R[i], dist[i]);
		d = 0;
		apath[d] = i;			                                       //添加路径上的终点
		k = path[i];
		if (k == -1)				                                   //没有路径的情况
			printf("无路径\n");
		else						                               //存在路径时输出该路径
		{
			while (k != z)
			{
				d++;
				apath[d] = k;
				k = path[k];
			}
			d++;
			apath[d] = z;		                                       //添加路径上的起点
			printf("%s", R[apath[d]]);	                           //先输出起点
			for (j = d - 1; j >= 0; j--)                               	   //再输出其他顶点
				printf("->%s", R[apath[j]]);
			printf("\n");
		}
	}
}
void Shortlu(MGraph g, int z, int& Nv, int B[MaxVertexNum], char R[MaxVertexNum][MaxVertexNum])//找寻最短路径函数
{
	int dist[MaxVertexNum], path[MaxVertexNum];
	int S[MaxVertexNum];			        //S[i]=1表示顶点i在S中, S[i]=0表示顶点i在U中
	int Mindis, i, j, u;
	for (i = 0; i < g.Ne; i++)
	{
		dist[i] = g.G[z][i];	//距离初始化
		S[i] = 0;					//S[]置空
		if (g.G[z][i] < INFINIFY)	//路径初始化
			path[i] = z;			//顶点z到顶点i有边时，置顶点i的前一个顶点为z
		else
			path[i] = -1;			//顶点z到顶点i没边时，置顶点i的前一个顶点为-1
	}
	S[z] = 1; path[z] = 0;			//源点编号v放入S中
	for (i = 0; i < g.Nv - 1; i++)			//循环直到所有顶点的最短路径都求出
	{
		Mindis = INFINIFY;				//Mindis置最大长度初值
		for (j = 0; j < g.Nv; j++)		//选取不在S中（即U中）且具有最小最短路径长度的顶点u
			if (S[j] == 0 && dist[j] < Mindis)
			{
				u = j;
				Mindis = dist[j];
			}
		S[u] = 1;					//顶点u加入S中
		for (j = 0; j < g.Nv; j++)		//修改不在S中（即U中）的顶点的最短路径
			if (S[j] == 0)
				if (g.G[u][j] < INFINIFY && dist[u] + g.G[u][j] < dist[j])
				{
					dist[j] = dist[u] + g.G[u][j];
					path[j] = u;
				}
	}
	PutShortlu(g, dist, path, S, z, Nv, B, R);	//输出最短路径
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

	printf("输入你所需要查询的地点坐标，返回菜单请输入(88):");
	ENode* p;
	int i, j;
	i = input2(Nv, B);                                                               ///输入需要查询地标的编号
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
void modify(int A[MaxVertexNum][MaxVertexNum], int& Nv, int& Ne, char R[MaxVertexNum][MaxVertexNum])        //图的修改函数
{
	MGraph g;
	int a,b,c,d,t,i=0,j;
	char x[100];
	int w = 0;
	printf("\n");
	printf("\n");
	printf("\t**************修改菜单***************");
	printf("\n\t**       (1)增加地标节点           **");
	printf("\n\t**       (2)删除地标节点           **");
	printf("\n\t*************************************\n");
	printf("输入你需要查询的菜单选项编号:");
	a = input3();                                      ///调用input3函数获取值
	switch (a)                                        ///对数值a进行判断
	{
	case 1:
		printf("输入需要添加的地点名称:");
		scanf("%s", &x);
		while (i != Nv)                                  ///判断是否添加的地标节点已存在
		{
			if (R != NULL)
			{
				for (i = 0; i < Nv; i++)
					if (strcmp(R[i],x) == 0 )
					{
						printf("该地标节点已存在请重新输入:");
						scanf("%s", &x);
						break;
					}
			}
			else
				break;
		}
		//B[b - 1] = b;                                     ///将新增的结点添加进B数组
		R[Nv] = x;   //将新的结点输入R

		for(int i = 0; i <= Nv; i++){
            A[i][Nv] = INFINIFY;
            A[Nv][i] = INFINIFY;
		}
		A[Nv][Nv] = 0;   //更新距离数组
		/*printf("输入地标节点的编号和名称[(编号)名称]:");
		//scanf("%s", &Q[Nv]);
		printf("输入增加的地标节点与其余地标节点直接连接的路径数目:");
		scanf("%d", &c);
		if (b >= Nv)                                      ///如果添加的地标节点编号超过现有的便将该数组进行扩建并将新的行与列进行初始化
		{
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
			Nv = Nv + 1; Ne = Ne + c;                              ///将该二维数组的信息进行更新
		}

		while (w < c)
		{

			printf("依次输入该地点能直接到达的地点编号和两地标之间的距离\n");
			printf("输入格式:编号、距离之间用英文逗号隔开(x,y):");
			scanf("%d,%d", &d, &t);               ///输入新增地标节点的编号、距离和终止值
			for (i = 0; i < MaxVertexNum; i++)                       ///将该节点对应的边进行添加
				for (j = 0; j < MaxVertexNum; j++)
				{
					if (i == (d - 1) && j == (b - 1))
					{
						A[i][j] = t;
						A[j][i] = t;
						w++;
					}
				}
		}
		*/
		printf("已结束输入，输出新生成的图:\n");
		CreateGraph(g, A, Nv, Ne);
		PutMGraph(g);
		break;
	case 2:
	    /*
		printf("请输入需要删除的地标节点：");
		b = input2(Nv, B) - 1;                              ///通过调用函数input2获取值
		for (i = 0; i < MaxVertexNum; i++)                           ///将想要删除的节点进行初始化删除
			for (j = 0; j < MaxVertexNum; j++)
			{
				if (i == b)
					A[i][j] = INFINIFY;
				if (j == b)
					A[i][j] = INFINIFY;
			}
		for (i = 0; i < Nv; i++)                              ///将存放节点信息和节点编号的数组Q、b进行更新
			if (i == b || i > b)
			{
				strcpy(Q[i], Q[i + 1]);                  ///因为维数组存放的为字符元素所以调用函数strcpy将以删除节点后的结点信息向前覆盖
				B[i] = B[i + 1];
			}
		CreateGraph(g, A, Nv, Ne);
		PutMGraph(g);
		*/
		break;
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
			printf("\n学校地图查看:");
			//map();
			printf("\n已返回主菜单，请输入需要查询的菜单栏选项:\n");
			printf("\n");
			Caidan();
			x = input1();
			break;
		case 2:
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
			break;
		case 3:
			printf("输入你所在的位置，为你规划最短路径：");
			CreateGraph(g, A, Nv, Ne);
			z = input2(Nv, B) - 1;
			Shortlu(g, z, Nv, B, R);
			printf("\n已返回主菜单，请输入需要查询的菜单栏选项:\n");
			printf("\n");
			Caidan();
			x = input1();
			break;

		case 4:
			printf("\n地点信息查看:");
			printf("\n");
			place(A, Nv);
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
		case 7:
			modify(A, Nv, Ne, R);修改
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
