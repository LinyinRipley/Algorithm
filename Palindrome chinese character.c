#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define STACK_INIT_SIZE 100
#define STACKINCREMENT  10
#define SElemType   char   //存储的类型
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

Status StatckEmpty(SqStack S)
{
	if(S.top==S.base){ return TRUE;}
	return ERROR;
}

Status Pop(SqStack &S,SElemType &e){
	if(S.top==S.base) return ERROR;     //列表为空
	e=*--S.top;  
	return OK;
}

void Judge(char *init,int &res)
{   int num=0; char out[3];
	SqStack S;
    SElemType e;
	InitStack(S);
	int len=strlen(init),i=0; //不包括0的字节数,一个汉字俩字节
    res=1;  out[2]=0;
	while(init[i]) Push(S,init[i++]); //存入每一个字节，但不包括结尾的0
	

	i=1;
    while(!StatckEmpty(S))   //取出字符串 
	{	
		Pop(S,e);
		if(i%2) {out[1]=e;}
		else {out[0]=e;num++;}
		if(!(i%2)){
			printf("%s",out); //输出一个汉字
			if((out[0]!=init[2*num-2])||(out[1]!=init[2*num-1])) res=0;
			      }i++;
	}
}




int main(){
	char init[100];
	int res;
	
	         
	   while( ~scanf("%s",init)){  //输入判断的字符串
		
		printf("%s",init);  //输出输入的内容
	    printf("\n");

	    Judge(init,res);
		if(res) printf("是回文字符串\n");
		else printf("不是回文字符串\n");}
		
	
	return 0;}
