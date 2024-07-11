#include <stdio.h>
#define max 100

int inorder[max],postorder[max];
int height[max][max]={0};
int length[max]={0};

void CreateList(int inleft,int inright,int postleft,int postright,int level){
	int temp=inleft;
	if(inleft>inright)return;
	if(postleft>postright)return;
	height[level][length[level]]=postorder[postright];	
	length[level]++;
	while(inorder[temp]!=postorder[postright]){
		temp++;
	}
	int len=temp-inleft;
	CreateList(inleft,temp-1,postleft,postleft+len-1,level+1);
	CreateList(temp+1,inright,postleft+len,postright-1,level+1);	 		
}

void PrintZigZagTree(int **height,int length[],int n,int level){
	int i,cnt=0;
	while(cnt<level){
		if(cnt%2==0){
			if(cnt==0){
				printf("%d",height[0][0]);
			}
			else{
				for(i=length[cnt]-1;i>=0;i--){
					printf(" %d",height[cnt][i]);
				}
			}
		}
		else{
			for(i=0;i<=length[cnt]-1;i++){
				printf(" %d",height[cnt][i]);
			}		
		}
		cnt+=1;
	}
}

int main(){
	int i,k,n;
	scanf("%d",&n);
	for(i=0;i<n;i++){
		scanf("%d",&inorder[i]);
	}
	for(i=0;i<n;i++){
		scanf("%d",&postorder[i]);
	}
	CreateList(0,n-1,0,n-1,0);
	int level=0;
	int num=0;
	for(i=0;num<n;i++){
		num+=length[i];
		level+=1;
	}
	//printf("level=%d\n",level);
	int *p[max];
	for(i=0;i<level;i++){
		p[i]=height[i];
	}
	PrintZigZagTree(p,length,n,level);
	return 0;	
} 

