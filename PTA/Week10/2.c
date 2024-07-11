#include <stdio.h>

int S[200000];
int MST(int n);
int Find(int t);
void Union(int a,int b);

int isUnique=1;
struct edge{
	int n1;
	int n2;
	int w;
	int vis;
}e[200000];	
struct edge temp;
    // int gas=M/2;
    // while(gas>0){
    //     for(i=gas+1;i<=M;i++){
    //         for(j=i-gas;j>=1&&edge[j].weight>edge[j+gas].weight;j-=gas){
    //             swap(&edge[j],&edge[j+gas]);
    //         }
    //     }
    //     gas/=2;
    // }
void Median( struct edge A[], int N );
int main(){
	int n,m,a,b,w,i,j,cnt=0,minnum,result;
	scanf("%d %d",&n,&m);
	for(i=0;i<=n;i++){
		S[i]=-1;
	}
	for(i=1;i<=m;i++){
		scanf("%d %d %d",&(e[i].n1),&(e[i].n2),&(e[i].w));
	}
	Median(e,m);
	result=MST(m);
	for(i=1;i<=n;i++){
		if(S[i]<0)cnt++;
	}
	if(cnt==1){
		printf("%d\n",result);
		if(isUnique)printf("Yes\n");
		else printf("No\n");
	}
	else {
		printf("No MST\n");
		
		printf("%d\n",cnt);
	}
	return 0;
}
void Median( struct edge A[], int N )//希尔排序 
{
    int gas = N / 2;
    int i,j;
    struct edge tmp;
    while(gas > 0)
    {
        for(i = gas+1;i <=N; i ++)
        {
            for(j = i-gas;j >= 1 && A[j].w > A[j+gas].w; j -= gas)
            {
                     tmp = A[j];
                    A[j] = A[j+gas];
                    A[j+gas] = tmp;
            }
        }
        gas /= 2;
    }
}
int Find(int t){
	int root,trail,lead;
	for(root=t;S[root]>0;root=S[root]);
	for(trail=t;trail!=root;trail=lead){
		lead=S[trail];
		S[trail]=root;
	}
	return root;	
}
void Union(int a,int b){
	int r1=Find(a),r2=Find(b);
	S[r2]=r1;
}
int MST(int m){
	int i;
	long long length=0;
	for(i=1;i<=m;i++){
		if(Find(e[i].n1)!=Find(e[i].n2)){//没合并过 
			
			if(i!=m){
				if(e[i].w==e[i+1].w){
					if(Find(e[i+1].n1)!=Find(e[i+1].n2))
					e[i+1].vis=1;
				}
			}
			Union(e[i].n1,e[i].n2);
			length+=e[i].w;
		}
		else if(e[i].vis==1){ //都被包含，并且可替代 
			isUnique=0;
		}
	}
	return length;
}