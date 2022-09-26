#include<stdio.h>
#include<process.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>

#define N 4
#define M 7

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef int Status;  
typedef int ElemType;		

typedef struct LNode{
	ElemType  data;		
	struct LNode *next;				
}LNode, *LinkList;

Status InitList_L(LinkList &L){
	L=(LinkList)malloc(sizeof(LNode));
	if(!L) exit(OVERFLOW);
	L->next=NULL;
	return OK;
}

Status CreateList_L(LinkList &L,int n){
	int i=0;
	LinkList s,q=L;
	
	for(i=1;i<n;i++)
	{
		s=(LinkList)malloc(sizeof(LNode));
		q->next=s;q=s;
	}
	q->next=NULL;
	return OK;
}

void MerageList(LinkList La, LinkList Lb, LinkList &Lc)
{   
	LinkList p=La;
	LinkList q=Lb;
	LinkList r=Lc;

	while(p && q) 
	{   
		if((p->data)<(q->data))
		{r->data=p->data; r=r->next; p=p->next;} 
	   else 
	   {r->data=q->data;r=r->next;q=q->next;}
	   }

	while(p) { r->data=p->data;r=r->next;p=p->next;}
	while(q) { r->data=q->data;r=r->next;q=q->next;}
}

Status Destory_L(LinkList &L)
{LinkList p;
while(L)
{ p=L->next;
free(L); L=p;}
return OK;
}

int main()
{   ElemType mem1[N]={3,5,8,11};
    ElemType mem2[M]={2,6,8,9,11,15,20};
	int i=0;
	LinkList LA,LB,LC;
	LinkList p,s;

	InitList_L(LA);
	CreateList_L(LA,N);
	for(i=0,p=LA;i<N;i++)
	{p->data=mem1[i];p=p->next;}
	
	InitList_L(LB);
	CreateList_L(LB,M);
	for(i=0,p=LB;i<M;i++)
	{p->data=mem2[i];p=p->next;}

	InitList_L(LC);
	CreateList_L(LC,(M+N));
	MerageList(LA, LB, LC);

	s=LA;
	while(s)
	{printf("%d\t",s->data);s=s->next;}
	printf("\n");
	
	s=LB;
	while(s)
	{printf("%d\t",s->data);s=s->next;}
	printf("\n");
    
	s=LC;
	while(s)
	 {printf("%d\t",s->data);s=s->next;}
	
    Destory_L(LA);
	Destory_L(LB);
	Destory_L(LC);
 return 0; 
}
