#include <stdio.h>
#define maxn 10000000

struct Edge{
	int v1;
	int v2;
	int weight;
	int vis;
}edge[maxn];	
struct Edge temp;
int S[maxn];
int isUnique=1;

int Find(int t);
void swap(struct Edge *a,struct Edge *b);
int partition(struct Edge A[], int left, int right );
void sort (struct Edge A[], int left, int right ){
    if ( left < right ) {
        int p = partition(A, left, right);
        sort(A, left, p);
        sort(A, p+1, right);
    }
}
int partition(struct Edge A[], int left, int right ){
    int i=left,j=right;
    int p=A[(left+right)/2].weight;
    while(i<=j){
        while(A[i].weight<p){
            i++;
        }
        while(A[j].weight>p){
            j--;
        }
        if(i<=j){
            swap(&edge[i],&edge[j]);
            i++;
            j--;
        }
    }
    return i-1;
}
int main(){
	int N,M;
    int i,j;
    int num=0;
	scanf("%d %d",&N,&M);
	for(i=1;i<=N;i++){
		S[i]=-1;
	}
	for(i=1;i<=M;i++){
		scanf("%d %d %d",&(edge[i].v1),&(edge[i].v2),&(edge[i].weight));
	}

    /*Bubble Sort*/
    // for(i=1;i<=M;i++){
    //     for(j=1;j<=M-i;j++){
    //         if(edge[j].weight>edge[j+1].weight){
    //             swap(&edge[j],&edge[j+1]);
    //         }
    //     }
    // }

    /*Shell's Sort*/
    // int gas=M/2;
    // while(gas>0){
    //     for(i=gas+1;i<=M;i++){
    //         for(j=i-gas;j>=1&&edge[j].weight>edge[j+gas].weight;j-=gas){
    //             swap(&edge[j],&edge[j+gas]);
    //         }
    //     }
    //     gas/=2;
    // }

    sort(edge,1,M);

    int length=0;
	for(i=1;i<=M;i++){
		if(Find(edge[i].v1)!=Find(edge[i].v2)){
			if(i!=M){
				if(edge[i].weight==edge[i+1].weight){
					if(Find(edge[i+1].v1)!=Find(edge[i+1].v2))
					edge[i+1].vis=1;
				}
			}
            S[Find(edge[i].v2)]=Find(edge[i].v1);
			length+=edge[i].weight;
		}
		else if(edge[i].vis==1){
			isUnique=0;
		}
	}
	for(i=1;i<=N;i++){
		if(S[i]<0) num++;
	}
	if(num==1){
		printf("%d\n",length);
		if(isUnique)printf("Yes\n");
		else printf("No\n");
	}
	else{
		printf("No MST\n");
		printf("%d\n",num);
	}
	return 0;
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

void swap(struct Edge *a,struct Edge *b){
    struct Edge t=*a;
    *a=*b;
    *b=t;
}

// 5 7
// 1 2 6
// 5 1 1
// 2 3 4
// 3 4 3
// 4 1 7
// 2 4 2
// 4 5 5