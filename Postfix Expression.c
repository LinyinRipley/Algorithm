# Algorithm
//后缀表达式的转换也可以通过树的不同遍历方式进行转换，此处则是通过栈来实现
#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
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

Status PrintTop(SqStack S){ //打印栈顶元素
	char e;
  if(S.top==S.base) return NULL;     //列表为空
	e=*(S.top-1);  //top指向栈顶上的空位
	return e;
}

Status StackEmpty(SqStack S)
{
	if(S.top==S.base){ return TRUE;}  //为空的时候返回1
	return ERROR;
}

Status Pop(SqStack &S,SElemType &e){
	if(S.top==S.base) return ERROR;     //列表为空
	e=*--S.top;  
	return OK;
}

void Print(SqStack t){
	SElemType *tem=t.base;
	printf("栈：");
	while(t.base!=t.top){
	    printf("%c",*t.base);
		t.base++;
	}t.base=tem;
	printf("\n");
}


void Out_All(char *O,int &num,char i){
	if(i!='(')
	O[num++]=i;
	else return;
}

int Compare(char s1,char s2){ //比较前一个操作符与现在操作符的优先级：原优先--1，后一个优先--0，右括号---2连输出两个（符号+‘（’）
	if(s2==')')  return 2; //右括号优先级最高直接输出前面且删前一个（
	if(s2=='(')  return 0; //左括号优先级最低,不出栈，后一个入栈
	switch(s1){             //1--输出s1且s2入栈， 0--后一个入栈
		case '+': 
			if(s2=='+'||s2=='-') return 1; 
			else return 0;
		case '-':
			if(s2=='+'||s2=='-') return 1; 
			else return 0;
		case '*':
			return 1;
		case '/':
			return 1;
		case '(':
			return 0;
	}
}



int main(){
	SqStack S;
	InitStack(S);//初始化栈
	char Input[20]; 
	while(~scanf("%s",Input))
{	char e;char Output[20];int num=0;
	char *p=Input;
	while(*p!='#')   //printf("e:%c---p:%c\n",e,*p);a+b*(c+d*e)+k#
	{   e=PrintTop(S);
		if(isalpha(*p)){printf("%c\n",*p);Out_All(Output,num,*p);p++;} //字母直接输出
		else if(StackEmpty(S)){Push(S,*p);e=PrintTop(S);Print(S);p++;} //第一个操作符直接存入，并将其放入e，e保存上一个
		else {  //p为操作符且栈不为空

			
				int choice=Compare(e,*p); //0--不出栈，p入栈；1--top出栈，再入栈；2--清空（...）括号及里面
				switch(choice){
				case 0: Push(S,*p);Print(S);
					p++;	
					break;
				case 1:
					Pop(S,e);printf("%c\n",e);Out_All(Output,num,e);Print(S);
					e=PrintTop(S);
					while(Compare(e,*p))  //直到p的优先级高入栈停止循环，否则将栈顶元素输出
					{
						Pop(S,e);printf("%c\n",e);Out_All(Output,num,e);Print(S);
						e=PrintTop(S);
					}
					Push(S,*p);e=PrintTop(S);Print(S);   //e始终为栈顶元素
					p++;

					break;
				case 2:
					Pop(S,e);printf("%c\n",e);Out_All(Output,num,e);Print(S);
				 while(e!='(')
					{Pop(S,e);printf("%c\n",e);Out_All(Output,num,e);Print(S);e=PrintTop(S);} //直至（出栈，不进行输出
				 Pop(S,e);Print(S);e=PrintTop(S); //此时e=（
					p++;
					break;
				
				}
			}
		}
	while(!StackEmpty(S)) {Pop(S,e);printf("%c\n",e);Output[num++]=e;}
	Output[num++]='\0';
	printf("后缀表达式为：%s\n",Output);
}
	return 0;}
