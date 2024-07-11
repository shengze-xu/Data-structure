#include <stdio.h>
//用数组 
int in[50],post[50],ans[40][20],size[40];
void Create(int il,int ir,int pl,int pr,int level);
int main(){
	int n,i,cnt=0,k;
	int sum=1;
	scanf("%d",&n);
	for(i=1;i<=n;i++){
		scanf("%d",&in[i]);
	}
	for(i=1;i<=n;i++){
		scanf("%d",&post[i]);
	}
	for(i=0;i<40;i++){
		size[i]=0;//初始化 
	}
	for(i=0;i<40;i++){
		for(k=0;k<20;k++){
			ans[i][k]=0;
		}
	}
	Create(1,n,1,n,1);//创建前序 
	//printf
	printf("%d",ans[1][1]);
	for(i=2;sum<n;i++){
		sum+=size[i];
		if(i%2==0){
			for(k=1;k<=size[i];k++){
				printf(" %d",ans[i][k]);
			}
		}else{
			for(k=size[i];k>=1;k--){
				printf(" %d",ans[i][k]);
			}
		}
		
	} 
	
	return 0;
} 
void Create(int il,int ir,int pl,int pr,int level){
	int width;
	int j=1;
	if(il>ir||pl>pr)return;
	else{
	//	if(size[level]==0)width=1;
	//	else width++;
		size[level]++;
		ans[level][size[level]]=post[pr];
		
	
		while(in[j]!=post[pr])j++;//找到在中序中的位置 
		j=j-il;//相对位置 
	
	//	12 11 20 17 1 15 8 5
	//	12 20 17 11 15 8 5 1
		Create(il,il+j-1,pl,pl+j-1,level+1);//左子树 
		Create(il+j+1,ir,pl+j,pr-1,level+1);//右子树 
		
	}
	
}
