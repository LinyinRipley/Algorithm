# Algorithm
#include<iostream>
#include<cstring>
#include<string.h>
#include<stdlib.h>
using namespace std;
#define OVERFLOW -1
#define QElemType int
#define MAX_VERTEX_NUM 100
#define InfoType double   //弧信息的类型
#define VertexType char //顶点信息，数组中存储的图的本身结点所对应的信息 
#define Status int
#define True 1
#define False 0

//表中的节点 
typedef struct ArcNode{
	int adjvex;//该弧指向的顶点数组位置
	struct ArcNode *nextarc;//指向下一条弧的指针
	InfoType info;//改弧的相关信息 
}ArcNode;

//数组中的顶点 
typedef struct VNode{
	char  data;
	ArcNode *firstarc;
}VNode; 

//图的大定义 
typedef struct{
	VNode vertices[MAX_VERTEX_NUM];    //数组 
	int vexnum;
	int arcnum;  //图的当前顶点数和弧数 
	int kind;       //图的种类标志 
}ALGraph;

//正邻接表的创建 
Status Creategra(ALGraph &G){
	int head=0;int num=0;
	printf("请输入图的顶点数:");
	scanf("%d",&G.vexnum); 
	printf("请输入图的边数:");
	scanf("%d",&G.arcnum); 
	printf("请输入图的种类标志:");
	scanf("%d",&G.kind); 
	int i;int d;
	for(i=0;i<G.vexnum;i++){
		printf("请输入第%d的顶点值:",i);  
		cin>>(G.vertices[i]).data;//VertexType类型 ABC等 
	    G.vertices[i].firstarc=NULL;
	}
	for(i=0,d=0;i<G.arcnum&&d<G.vexnum;i=i+num,d++){
		ArcNode *p;
		printf("请分别输入弧尾为%d的弧数:",d);
		scanf("%d",&num);	
		p=(ArcNode *)malloc(num*sizeof(ArcNode)); //链表一个一个来赋值空间，或者记录各弧相同头/尾的个数
		if(!p) return False;
		//将链表初始化
		G.vertices[d].firstarc=p;
		ArcNode *q=p;
		if(num!=0) printf("请输入其所有弧头\n");
		for(int k=0;k<num-1;k++){
			printf("%d:",k+1); scanf("%d",&head);
			//printf("请输入这个弧的权值"); 
			//scanf("%lf",q->info); //输入权值等信息 
		q->adjvex=head; q->nextarc=q+1;q++;
		} 	if(num!=0){
		printf("%d:",num);scanf("%d",&head);q->adjvex=head;q->nextarc=NULL;//最后一个无连接 	
		}
	}
	return True;	
}

//visitfunc
void Visit(ALGraph G,int v){
	cout<<G.vertices[v].data;//printf("顶点信息：%s\n",G.vertices[v].data);
}


//单链队列
typedef struct QNode{
QElemType     data;
struct QNode  *next;
}QNode,*QueuePtr;
typedef struct{
QueuePtr front;
QueuePtr rear;
}LinkQueue;

Status InitQueue(LinkQueue &Q){
	Q.front=Q.rear=(QueuePtr)malloc(sizeof(QNode));
	if(!Q.front) exit(OVERFLOW);
	Q.front->next=NULL;
	return True;
}
//插入e为队尾新地元素
Status EnQueue(LinkQueue &Q,QElemType e){
	QueuePtr p;
	p=(QueuePtr)malloc(sizeof(QNode));
	if(!p) exit(OVERFLOW);
	p->data=e; p->next=NULL;
	Q.rear->next=p;
	Q.rear=p;
	return True;
}

Status DeQueue(LinkQueue &Q,QElemType &e){
	if(Q.front==Q.rear)return False;
    QueuePtr p=Q.front->next;//front为头，数据的前一个，将p指向第一个
	e=p->data;
	Q.front->next=p->next;
	if(Q.rear==p) 
	{Q.rear=Q.front; }//即原本就只有一个元素,这时候后队尾指针也需要重新更改
		free(p);
	return True;
}

Status QueueEmpty(LinkQueue Q){
	if(Q.front==Q.rear) return True;
	return False;

}

int FirstAdjVex(ALGraph G,int v){ //从弧尾寻找下一个弧头 
	int v_fir;
	v_fir=G.vertices[v].firstarc->adjvex;
	return v_fir; 
}

int NextAdjVex(ALGraph G,int v,int w){ //访问以v为弧尾的链中w弧头的下一个结点 
	int v_nex=0;
	ArcNode *p;
	for(p=G.vertices[v].firstarc;p!=NULL;p=p->nextarc) //p不为空，即p不是链的最后一个 
		{if(p->adjvex==w)
	{  if(p->nextarc==NULL){return -1;}
	else {v_nex=(p->nextarc)->adjvex;return v_nex;}
		}
		}
	return -1;
}

////深度优先遍历
//void DFS(ALGraph G,int v,int *visited){//v为起始点 
//	visited[v]=True; 
//	Visit(G,v);
//	int w;
//	for(w=FirstAdjVex(G,v);w>=0;w=NextAdjVex(G,v,w))
//	if(!visited[w]) DFS(G,w,visited);
// } 
//
//
//void DFSTraverse(ALGraph G,int *visited){  //traverse--横穿，横渡 
//	int i;
//	printf("请输入深度遍历的起始结点");
//	scanf("%d",&i); 
//	cout<<"遍历的顶点信息:";
//	for(;i<G.vexnum;i++) if(!visited[i])DFS(G,i,visited);  //最后防止图的不连通 
//	cout<<endl;
//} 


void BFSTraverse(ALGraph G,bool *visited)  //队列存储实现
{	int w,u,v;
	LinkQueue Q;
	InitQueue(Q);
	for(v=0;v<G.vexnum;v++) visited[v]=False;//初始化辅助数组
	for(v=0;v<G.vexnum;v++)   //不连通时的保证
	{if(!visited[v]){
		visited[v]=True;Visit(G,v);
		EnQueue(Q,v); //将访问的元素放入队列中
		while(!QueueEmpty(Q)){  
			DeQueue(Q,u);    //不为空就循环，取出存入u
			for(w=FirstAdjVex(G,v);w>=0;w=NextAdjVex(G,v,w)) //下一轮循环w变为以v为尾的下一个邻接
				{
				  if(!visited[w]){//第一次的时候w=u，visited为真直接跳过
					visited[w]=True;Visit(G,w);
					EnQueue(Q,w);}
			}
		}
	}
	}
}

int main(){
	ALGraph G;
	int v; bool visited[MAX_VERTEX_NUM];
	G.arcnum=0;G.vexnum=0;G.kind=0; //未初始化G会错
	Creategra(G);
	//深度优先
    //int visited[MAX_VERTEX_NUM];
    //for(int i=0;i<G.vexnum;i++)visited[i]=False; //标志数组的初始化
    //DFSTraverse(G,visited);
	
	//广度优先
	BFSTraverse(G,visited);//默认从0开始


	return 0; 
}
