#include<stdio.h>
#include<process.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>

#define N 4
#define M 7

#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef int Status;  
typedef int ElemType;		

typedef struct{
	ElemType * elem;		
	int listlength;	
	int listsize;			
}SqList;

Status InitList_Sq(SqList &L){
	L.elem=(ElemType *)malloc(LIST_INIT_SIZE*sizeof(ElemType));
	if(!L.elem) exit(OVERFLOW);
	L.listlength=0;
	L.listsize=LIST_INIT_SIZE;
	return OK;
}

void MerageList(SqList La, SqList Lb, SqList &Lc)
{   
	ElemType *p=La.elem;
	ElemType *q=Lb.elem;
	ElemType *r=Lc.elem;

	while(p<La.elem+La.listlength && q<Lb.elem+Lb.listlength) 
   {   if(*p<*q)
		   *r++=*p++; 
	   else 
		  *r++=*q++;
	   Lc.listlength++; }

	while(p<La.elem+La.listlength) { *r++=*p++;Lc.listlength++;}
	while(q<Lb.elem+La.listlength) {  *r++=*q++;Lc.listlength++;}
}



int main()
{   ElemType mem1[N]={3,5,8,11};
    ElemType mem2[M]={2,6,8,9,11,15,20};
	int i=0;
	SqList LA,LB,LC;
	
	InitList_Sq(LA);
	memcpy(LA.elem,mem1,N*sizeof(ElemType));
	LA.listlength=N;
	InitList_Sq(LB);
	memcpy(LB.elem,mem2,M*sizeof(ElemType));
	LB.listlength=M;

	InitList_Sq(LC);
	MerageList(LA, LB, LC);

	for(i=0;i<LA.listlength;i++)
	printf("%d\t",LA.elem[i]);
	printf("\n");
	for(i=0;i<LB.listlength;i++)
	printf("%d\t",LB.elem[i]);
	printf("\n");
	for(i=0;i<LC.listlength;i++)
	printf("%d\t",LC.elem[i]);
    free(LA.elem);
	free(LB.elem);
	free(LC.elem);
 return 0; 
}
