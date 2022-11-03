#include<iostream>
#include<cstring>
#include<cstdlib>
using namespace std;
#define STACK_INIT_SIZE 100
#define STACKINCREMENT  10
#define SElemType char
#define Status int
#define OK 1
#define ERROR -1
#define OVERFLOW -2

typedef struct {
	SElemType *top;
	SElemType *base;
	int stacksize;
}SqStack; 

Status InitStack(SqStack &S){
	S.base=(SElemType *)malloc(STACK_INIT_SIZE*sizeof(SElemType));
	if(!S.base) exit(OVERFLOW);
	S.top=S.base;
	S.stacksize=STACK_INIT_SIZE;
	return OK;
}

Status Push(SqStack &S, SElemType &e){
	if(S.top-S.base>S.stacksize){
		S.base=(SElemType *)realloc(S.base,(STACK_INIT_SIZE+STACKINCREMENT)*sizeof(SElemType));
		if(!S.base) exit(OVERFLOW);	
		S.top=S.base+S.stacksize;
	    S.stacksize+=STACKINCREMENT;
	}
    *S.top++=e; 
    return OK;
}

Status Pop(SqStack &S, SElemType &e){
	if(S.base==S.top) return ERROR;
	e=*--S.top;
	return OK;
}

Status StackEmpty(SqStack &S){
	if(S.top==S.base) return true;
	else return false;
}

Status GetTop(SqStack &S){
	SElemType e;
	if(S.base==S.top)return ERROR;
	e=*(S.top-1);
	return e;
}

bool Judge(char exp[],int &num,int n,char a,char b){
 int i=0;bool mat=true;
 SqStack S; 	SElemType e;   InitStack(S);

 while (i<n){ 
	
        if(exp[i]==a) 
		{ Push(S,exp[i]); num=i++; mat=false; } //存入｛
        else if(exp[i]==b) 
		{
            if (!StackEmpty(S) &&GetTop(S) == a )   //补位空栈且找到{
              {  Pop(S, e);  mat=true;	}
            else {mat = false;num=i;}
            i++;  
			}
	    if(exp[i]!=a&&exp[i]!=b) {i++;}	
 }if(!StackEmpty(S)){mat=false;}	
 return mat;}



int main(){
	char exp[100];int num1=0,num2=0,num3=0;
	while(cin>>exp){
	int n=strlen(exp);bool jud1=true,jud2=true,jud3=true;
	jud1=Judge(exp,num1,n,'{','}');
	jud2=Judge(exp,num2,n,'(',')');
	jud3=Judge(exp,num3,n,'[',']');
	if(!jud1){cout<<"{}在"<<num1<<"处不匹配"<<endl;}
    if(!jud2){cout<<"()在"<<num2<<"处不匹配"<<endl;}
    if(!jud3){cout<<"[]在"<<num3<<"处不匹配"<<endl;}
	if(jud1&&jud2&&jud3) cout<<"匹配"<<endl;
	}	
	return 0;
}

