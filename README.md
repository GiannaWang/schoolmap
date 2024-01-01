#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<vector>
#include <map>
#include <set>
#include<iostream>
using namespace std;
#define INFINITY 65535   //定义无穷大
#define MAX_VERTEX_NUM 100    //定义最大定点数

typedef struct {
    int number;             //顶点编号
    char xinxi[50];      //顶点其他信息
} VertexType;           //顶点类型

typedef struct {
    int G[MAX_VERTEX_NUM][MAX_VERTEX_NUM];    //邻接矩阵数组
    int Nv;                   //顶点数
    int Ne;                  //边数
    VertexType Data[MAX_VERTEX_NUM];     //存放顶点信息
} MGraph;                    //完整的图邻接矩阵类型
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
            mgraph.G[i][j] = INFINITY;
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
            if (weight !=  INFINITY) {
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

int locate(MGraph& g,string s)
{
    for(int i=0;i<g.Nv;i++){if(s==g.Data[i].xinxi)return i;}
    return -1;
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
    int minLength = INFINITY;
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

int main(){
    InitGraph(mgraph);
    tp_shortest(mgraph);
}
