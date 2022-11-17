#include<stdio.h>
#include<stdlib.h>
#define STACK_INIT_SIZE 100
#define STACKINCREMENT  10
#define SElemType   int   //存储的类型
#define Status      int   //状态
#define OK        1
#define TRUE      1
#define ERROR     0
#define OVERFLOW  -2

typedef struct{           //一个栈的类型
	SElemType *base;
	SElemType *top;
	int stacksize;
}SqStack;        

Status InitStack(SqStack &S){
       S.base=(SElemType *)malloc(STACK_INIT_SIZE*sizeof(SElemType));
	   if(!S.base) exit(OVERFLOW);
	   S.top=S.base;
	   S.stacksize=STACK_INIT_SIZE;
	   return OK;
}

Status Push(SqStack &S, SElemType e){
	if(S.top-S.base>=S.stacksize){
		S.base=(SElemType *)realloc(S.base,(S.stacksize+STACKINCREMENT)*sizeof(SElemType));
		if(!S.base) exit(OVERFLOW);     //创建失败
		S.top=S.base+S.stacksize;
		S.stacksize+=STACKINCREMENT;}
	*S.top++=e;
	return OK;
}

Status StackEmpty(SqStack S)
{
	if(S.top==S.base){ return TRUE;}
	return ERROR;
}

Status Pop(SqStack &S,SElemType &e){
	if(S.top==S.base) return ERROR;     //列表为空
	e=*--S.top;  
	return OK;
}


void conversion (int num,  char *result, int system=2){
	SqStack S;
	int e,i=0;
	InitStack(S);
	while(num){
		Push(S,num%system);
		num/=system;
	}

	while(!StackEmpty(S))
	{
		Pop(S,e);
		if(e>9){
			e=e+'A'-10;
			result[i++]=e;	
		}
		else result[i++]=e+'0';
	}
	result[i]='\0';
}


int main(){
	char result[50];
	int N,Syst;
	while(~scanf("%d%d",&N,&Syst))
	{
	conversion(N, result,Syst);
	printf("%s\n",result);}
	return 0;}
