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

Status Printtop(SqStack &S, SElemType &e){
  if(S.top==S.base) return ERROR;     //列表为空
	e=*S.top;  
	return OK;
}

Status StatckEmpty(SqStack S)
{
	if(S.top==S.base){ return TRUE;}  //为空的时候返回1
	return ERROR;
}

Status Pop(SqStack &S,SElemType &e){
	if(S.top==S.base) return ERROR;     //列表为空
	e=*--S.top;  
	return OK;
}

void Printlast(SqStack &OPND){//倒叙存储到res中
  char e; char res[20]; 
  char *p=res;  int n=0;             
	while(!StatckEmpty(OPND))   //取出字符串 
	{	
		Pop(OPND,e);
		if(e=='('||e==')'){continue;}
		*p=e;p++;n++;
	}  
	for(int i=n-1;i>=0;i--){printf("%c",res[i]);}
}

//s2为原先的
Status Judge(char s1,char s2){   //s1--新，s2--原来
//比较符号的优先级: 1--现在入的级别更高，0--原优先级高取出放入数字栈中
	if(s1==')'||s1=='(') return -1;  ///special
	switch (s2){
	case '+':
		if(s1!='+'||s1!='-') return 1;
		else return 0;
	case '-': 
		if(s1!='+'||s1!='-') return 1;
		else return 0;
	case '*':
		return 0;
	case '/':
		return 0;
	case'(':
		return 1;
//（）放到外面去实现 ，直接跳过但（）里面的优先级另外在排
	
	} 
}


void Change(char *str,SqStack &OPND,SqStack &OPRT){
 //以不同的ASCll码来判断字符
//决定运算顺序的只有符号，数字都是一样的放入其中
 //按照不同符号的优先级表来进行入栈出栈的比较，+-*/（）%---switchcase，if(优先级后)：交换栈中位置
	char *p=str;  char opr='0',opd;  
	while(*p!='#'){
		if(isalpha(*p)||isdigit(*p)){    //如果是数字或者是字母就放进栈中
			Push(OPND,*p);opd=*p;p++;
		}
		else {
			if(StatckEmpty(OPRT)){  //为空就直接放入
				Push(OPRT,*p);opr=*p++; //opr指代原先p后移
			} 
			else if(Judge(*p,opr)==1&&Judge(*p,opr)!=-1){ //如果放入的优先级大
				if(opr=='('){Push(OPRT,*p);opr=*p;p++;continue;}//原来为（就直接存入现在的p
				opr=*p;++p;//查看后方符号
				if(*p=='('){Push(OPRT,opr);Push(OPRT,*p);opr='(';}//后面为（将符号与左括号压入栈
				else {Push(OPND,*p);Push(OPND,opr);Printtop(OPRT,opr);} //放入后面的一个数字 *p!='('||*p!=')'
				p++;                      //此处opr为字母
			}
			else if(Judge(*p,opr)==0){Push(OPND,opr);Pop(OPRT,opr);Push(OPRT,*p);opr=*p;p++;}   //原先符号元素优先级高
			else if(Judge(*p,opr)==-1){  //-1
				if(*p==')') 
				{Pop(OPRT,opr);Push(OPND,opr);Printtop(OPRT,opr);p++;}//两次删除
				else if(*p=='('){Push(OPRT,*p);opr=*p;p++;}//如果为（，直接存入（
			}//Judge==-1
		}
	}
	while(!StatckEmpty(OPRT)){Pop(OPRT,opd);Push(OPND,opd);}
}



int main(){
	SqStack OPND,OPRT;//OPND--操作数，OPRT--操作符
	InitStack(OPND);InitStack(OPRT);
	char Input[20];
	while(~scanf("%s",Input))
	{
	printf("后缀表达式为：");
	Change(Input,OPND,OPRT);
	Printlast(OPND);printf("\n");
	}
	return 0;}
