//Dev-C++ 5.11
#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<cstring>
using namespace std;

//赫夫曼数与赫夫曼的编码存储 

typedef struct{
	double weight;
	unsigned int parent,lchild,rchild;
}HTNode, *HuffmanTree;   //动态分配存储赫夫曼树 *Tree 
typedef char**  HuffmanCode;  //动态分配数组存储赫夫曼编码表 


void Select(HuffmanTree HT,int end,int *s1,int *s2){ //end为每次新增的结尾 
int i;  
for(i=1;i<=end;i++){
	if(HT[i].parent==0) {*s2=i,*s1=i;break;}   //s1,s2的初始化 
}
for(i=1;i<=end;i++){
    if((HT[i].parent==0)&&(HT[i].weight<HT[*s1].weight)) *s1=i;
}
for(i=1;i<=end;i++){
    if((i!=*s1)&&(HT[i].parent==0)) {*s2=i;break;}  //不能与下面的if放在同一个循环中的if条件中 
}
for(;i<=end;i++){
    if((i!=*s1)&&(HT[i].parent==0)&&(HT[i].weight<HT[*s2].weight)) *s2=i;
}
}	




void HuffmanCoding(HuffmanTree &HT, HuffmanCode &HC, double *w, int n){ //w存放n个字符的权值，构造赫尔曼树HT,并求出n个字符的赫夫曼编码HC 
	if(n<=1)  return ;
	int m=2*n-1;   //因为有n个叶子结点，所以共有m个结点 
	HT=(HuffmanTree)malloc((m+1)*sizeof(HTNode)); //0号未用，多分配一个结点存储地址,动态顺序分配地址（类数组） 
	int i; 
    int s1=1,s2=2; 
	for(i=1;i<=n;++i) {
	HT[i].weight=w[i-1];HT[i].lchild=0;HT[i].parent=0;HT[i].rchild=0;
	} // *w为第一个字符的权值，w里面顺序存放对应叶子结点的权值，共n个 
	for(i=n+1;i<=m;++i) {HT[i].weight=0;HT[i].lchild=0;HT[i].parent=0;HT[i].rchild=0;}     //初始化n-1个两度结点 
	for(i=n+1;i<=m;++i){ //后又n个二度，所以从n+1开始建赫夫曼树，循环n-1遍，建立完所有的叶子结点 
	Select(HT,i-1,&s1,&s2);	//在HT[1..i-1]选择parent为0（即还没有被使用过）且weight最小的俩
	//画出树的一个结点
	
	HT[s1].parent=i; HT[s2].parent=i; 
	HT[i].lchild=s1; HT[i].rchild=s2;
	HT[i].weight=HT[s1].weight+HT[s2].weight; 
	//printf("s1:%f--parent:%f,s2:%f--parent:%f\n",HT[s1].weight,HT[HT[s1].parent].weight,HT[s2].weight,HT[HT[s2].parent].weight);
	}
	//从叶子到根逆向求每个字符的赫夫曼编码，编码逆序，译码正序 
	HC=(HuffmanCode)malloc((n+1)*sizeof(char *));
	char *cd; 
	cd=(char *)malloc(n*sizeof(char *)); 
	cd[n-1]='\0';	int start,f,c; 
	for(i=1;i<=n;++i){  
		start=n-1;           //倒着编号 
		for(c=i, f=HT[i].parent; f!=0; c=f,f=HT[f].parent){ //沿着父亲结点找回去 
			if(HT[f].lchild==c) cd[--start]='0';                  //从父母去判断自己是左孩子还是右孩子 
			else cd[--start]='1';          
			HC[i]=(char *)malloc((n-start)*sizeof(char));
			strcpy(HC[i],&cd[start]);     //即HC中存储cd字符串 
		}
free(cd);	
} 
}

void HuffmanDecoding(string in){
	int i=0;
	while(in[i]){
	if(in[i]=='0'&&in[i+1]=='1'){printf("F");i=i+2;}
	else if(in[i]=='0'&&in[i+1]=='0'){
		if(in[i+2]=='1'){printf("H");i=i+3;}
		else{
			if(in[i+3]=='1'){printf("A");i=i+4;}
			else{printf("G");i=i+4;}
		}
	}
	else { i++;
		if(in[i]=='0'){printf("B");i++;}
		else{i++;
			if(in[i]=='0'){printf("E");i++;}
			else{i++;
				if(in[i]=='0'){printf("C");i++;}
				else {printf("D");i++;}
			}
		}
	}	}	
}
int main() {
	HuffmanTree HT; HuffmanCode HC; int i; string ch;
	double w[8]={0.05, 0.29, 0.07, 0.08, 0.14, 0.23, 0.03, 0.11}; int n=8;
	HuffmanCoding(HT, HC, w, n);
	for(int k=0;k<8;k++){
	printf("%lf的赫夫曼编码为%s\n",w[k],HC[k+1]);}	printf("\n");
	printf("请输入您要查找的编码："); cin>>ch; 
	HuffmanDecoding(ch);
	return 0;
}
