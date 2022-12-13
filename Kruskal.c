#include<iostream>
#include<cstring>
#include<string.h>
#include<stdlib.h>
using namespace std;
#define MAX_LEN 25
#define VT char  //顶点信息的类型
#define WT int   //权值的类型（int/type）
//Kruskal算法+邻接矩阵存储

int T[MAX_LEN];//用于判断回路的存储数组，实际存储数为顶点数

void Init(int n) { //n为总共的顶点数+1,用T[0]存储
  //初始化时每个点都在单独的一个集合中，每个点的数值先设置为自己的顶点值，若是顶点间有连通边就用相同数值存入代表再同一个集合里面
	T[0]=n;
	for (int i = 1; i <= n; i++) {  //从1开始(与顶点值对应关系：集合标志值=顶点值+1)，    条件n>=1即必存在顶点
		T[i] = i;                   //设置都为负数为已经合并的集合
	}
}

//结构体弧的定义
typedef struct edge {
	int u, v;//u--弧尾，v---弧头
	WT weight;//权值
}Edge;

Edge eg[MAX_LEN]; //存储弧的数组eg，实际存储数为弧数

bool merge(int u, int v) { //存入弧时将两个顶点合并
	int flag=1;
	if(T[v]==T[u]){return false;}
	else{T[v]=T[u];
		for(int i=1;i<=T[0];i++){//跟着弧尾设的顶点设值
			if(T[i]==T[v]){ //合并v，u所在的集合
				T[i]=T[u];
			}
		}
	}
	for(int i=2;i<=T[0];i++){//检验是否全部在同一个集合中
		if(T[i]!=T[1]){flag=0;}
	}
	if(flag) return false;
	
	return true;  //用于判断是否再同一个集合中
}


typedef struct
{	int no;						//顶点序号
	VT data[25];			        //顶点其他信息,这里顶点信息为A，B，C等字母
} VertexType;					//顶点类型

typedef struct
{	WT edges[MAX_LEN][MAX_LEN];	//邻接矩阵存储边的权值，对角线用0代替其他的用-1
	int NUM_Vertex,NUM_Edge;					    //顶点数，边数
	VertexType vexs[MAX_LEN];		//存储顶点
} MGraph;						    //完整的图邻接矩阵类型


void CreateG(MGraph &g, WT A[][MAX_LEN])	//建立图的邻接矩阵
{	int i,j;
	printf("请分别输入图的顶点数与边数：");
	cin>>g.NUM_Vertex>>g.NUM_Edge;
	printf("请分别填入每个顶点的相应信息\n");
	for(i=0;i<g.NUM_Vertex;i++){
		g.vexs[i].no=i;
	    printf("no%d:",i);
		scanf("%s",g.vexs[i].data); //此处的顶点信息用A，B，C等字母来表示
	}
	for (i=0;i<g.NUM_Vertex;i++)
		for (j=0;j<g.NUM_Vertex;j++)
			g.edges[i][j]=A[i][j];
}

void ShowG(MGraph &g){
	for(int i=0;i<g.NUM_Vertex;i++){
		printf("%s  ",g.vexs[i].data);} //为首行对齐信息
	printf("\n");
	for(int i=0;i<g.NUM_Vertex;i++){
		for(int j=0;j<g.NUM_Vertex;j++){
			printf("%d  ",g.edges[i][j]);
		}printf("\n");
	}
}

int Kruskal(MGraph g,Edge eg[MAX_LEN]){//用edge来接受返回的最小生成树
	int num=0;//来记录选择的边数，便于检验
	MGraph tem=g; 
//寻找最小的边，存入eg
	while(num<g.NUM_Vertex-1){ //最小生成树的边定为顶点数-1
		int i,j; eg[num].weight=1000;
		//int flag=0;
	//for(i=0;i<tem.NUM_Vertex;i++){ //初始化eg[num]存入矩阵中第一个弧
	//	for(j=0;j<tem.NUM_Vertex;j++){
	//	if(eg[num].weight>tem.edges[i][j]&&tem.edges[i][j]>0)
	//		 { eg[num].weight=tem.edges[i][j];
	//	eg[num].u=i;eg[num].v=j;flag=1;break;}
	//		}if(flag) break;
	//}
	for(i=0;i<tem.NUM_Vertex;i++){
		for(j=0;j<tem.NUM_Vertex;j++){
			if(eg[num].weight>tem.edges[i][j]&&tem.edges[i][j]>0){ //找到最小的边存入
				eg[num].weight=tem.edges[i][j];
				eg[num].u=i;eg[num].v=j;
			}
		}
	}         
	if(merge(eg[num].u+1,eg[num].v+1)){num++;} //不在同一个集合中 
	tem.edges[eg[num].u][eg[num].v]=-1;}//将已经选择的或是在同一个集合中的边设为-1
	return num;
}


int main(){
	MGraph G; int num,sum=0;
	        /*  例子：
	                {0,4,6,6,-1,-1,-1},
					{4,0,1,-1,7,-1,-1},
					{6,1,0,2,6,4,-1},
					{6,-1,2,0,-1,1,6},
					{-1,7,6,-1,0,1,6},
					{-1,-1,4,5,1,0,8},
					{-1,-1,-1,-1,6,8,0}*/
	WT A[][MAX_LEN]={   //行数不填减少内存浪费，测试例n=5,e=8
	  {0,1,6,6,-1},         
      {4,0,1,-1,7},				
	  {8,1,0,3,6},
	  {3,-1,2,0,6},
	  {-1,-1,6,8,0}
	};

	CreateG(G,A);      //创建图
	ShowG(G);//检验图的创建
	printf("\n");
	Init(G.NUM_Vertex); //初始化集合数组，即辅助数组
	num=Kruskal(G,eg);
	for(int i=0;i<num;i++){sum+=eg[i].weight;
		cout<<'<'<<eg[i].u<<','<<eg[i].v<<'>'<<"weight:"<<eg[i].weight<<'\n';}
	printf("最小的权值和为:%d",sum);
	return 0;}
