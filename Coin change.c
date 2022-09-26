#include<stdio.h>
#define SUM 10000
int main(){
	int i,j,k,m,p=0,n=0;//100角,50角,10角,5角,1角
	int I,J,K,M,left;
	int count_i,count_j,count_k,count_m;
	for(i=0;i<=(SUM/100);i++){
		count_i=SUM-i*100;
		for(j=0;j<=(count_i/50);j++){
			count_j=count_i-j*50;
			for(k=0;k<=(count_j/10);k++){
				count_k=count_j-k*10;
				for(m=0;m<=(count_k/5);m++){
			    	count_m=count_k-m*5;
				    if((100*i+50*j+10*k+5*m+count_m)==SUM){
						n++;I=i;J=j;K=k;M=m;left=count_m;
					   }
			        
				}
			    
			}
		}  
	}
printf("最后一种为%d张10元，%d张5元，%d枚1元，%d个5角，%d个1角",I,J,K,M,left);
printf("一共%d种方案\n",n);

return 0;

}
