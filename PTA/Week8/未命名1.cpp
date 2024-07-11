#include <stdio.h>
#define max 300
int hamilton(int seq[],int N);
int degree[max][max];
int seq[max];
int main(){
    int N,M;
    scanf("%d %d",&N,&M);
    int i,j;
    for(i=1;i<=N;i++){
        for(j=1;j<=N;j++){
            degree[i][j]=0;
        }
    }
    for(i=1;i<=M;i++){
        int x,y;
        scanf("%d %d",&x,&y);
        degree[x][y]=1;
        degree[y][x]=1;
    }
    int K,num;
    scanf("%d",&K);
    for(i=1;i<=K;i++){
        scanf("%d",&num);
        for(j=1;j<=num;j++){
            scanf("%d",&seq[j]);
        }
        if(num!=N+1){
            printf("NO\n");
            continue;
        }
        if(hamilton(seq,N)==1){
            printf("YES\n");
        }
        else{
            printf("NO\n");
        }
    }
}

int hamilton(int seq[],int N){
    int i;
    int temp[max];
    for(i=1;i<=N;i++){
        temp[i]=0;
    }
    if(seq[1]!=seq[N+1])return 0;
    for(i=1;i<=N;i++){
        int x=seq[i];
        int y=seq[i+1];
        if(degree[x][y]==0) return 0;
        temp[x]++;
        if(temp[x]>1) return 0;
    }
    return 1;
}
