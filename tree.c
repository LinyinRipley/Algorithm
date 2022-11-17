# Algorithm
#include<stdio.h>
#include<stdlib.h>

typedef int Status;
typedef char TElemType;
#define OK 1
#define ERROR 0
#define STACK_INIT_SIZE 100
#define STACKINCREMENT  10
#define SElemType   BiTree  //存储的类型
#define OVERFLOW  -2


//二叉链表存储结构
typedef struct BiTNode{ // 结点结构
    TElemType      data;
    struct BiTNode  *leftchild, *rightchild; 
                                  
} BiTNode, *BiTree;


//栈
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

Status GetTop(SqStack S, SElemType &e){
	if(S.top==S.base) return ERROR;
	e=*(S.top-1);
	return OK;
}


Status StackEmpty(SqStack S)
{
	if(S.top==S.base){ return OK;}
	return ERROR;
}

Status Pop(SqStack &S,SElemType &e){
	if(S.top==S.base) return ERROR;     //列表为空
	e=*--S.top;  
	return OK;
}




Status CreateTree_Preorder(BiTree &T){    //question：&的存在可以让程序忽视指针T未初始化的问题
	TElemType ch;
	scanf("%c",&ch);   //输入根节点
	if (ch=='#') {T=(BiTree)malloc(sizeof(BiTNode));T->data=ch;T->leftchild=NULL;T->rightchild=NULL;return OK;}
	else {
		T=(BiTree)malloc(sizeof(BiTNode));
		if(!T) return ERROR;
		T->data=ch;
		CreateTree_Preorder(T->leftchild);
		CreateTree_Preorder(T->rightchild);
	}
	return OK;
}

//最简单的Visit函数
Status PrintElement( TElemType e ) {  // 输出元素e的值
	if(e=='#') printf(" ");
	else printf("%c", e ); 
    return OK;
}
Status InOrderTraverse_recur(BiTree T, Status (*Visit)(TElemType)) {    
	// 递归中序遍历二叉树T算法，对每个数据元素调用函数Visit。  
	if(T){
	InOrderTraverse_recur(T->leftchild, Visit);  //直到左孩子为空节点停下
	if(T->data!='#') Visit(T->data);
	InOrderTraverse_recur(T->rightchild, Visit);    
	}
	else printf(" ");
	return OK;
}

Status InOrderTraverse2(BiTree T, Status (*Visit)(TElemType)) {  
	SqStack S; InitStack(S); 
	BiTree q=T; //树的指针
	Push(S,T);  //存入根节点的指针
	while(!StackEmpty(S)){
	while(GetTop(S,q)&& q) Push(S,q->leftchild);//根为0或到叶子结点
	Pop(S,q);
	if(!StackEmpty(S)){
		Pop(S,q); Visit(q->data);
		Push(S,q->rightchild);
	}
	}
	return OK;
}

Status Clear(BiTree T){
	if((!T->leftchild)&&(!T->rightchild)) free(T);	
	if(T){
		Clear(T->leftchild); //直至左孩子为空
		Clear(T->rightchild);//直至右孩子为空
		free(T);
	}
	return OK;
}

int main(){
	BiTree Q;
	CreateTree_Preorder(Q);
	printf("中序递归的输出：");
	InOrderTraverse_recur(Q, PrintElement);
	printf("\n");
	printf("非递归的中序输出：");
	InOrderTraverse2(Q, PrintElement);
	Clear(Q); 
return 0;}
