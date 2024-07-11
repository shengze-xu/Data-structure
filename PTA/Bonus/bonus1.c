#include <stdio.h>
#define maxn 100000

int a[maxn];
int b[maxn];

int possibility(int N,int array[]){
    int now = 0;
    int front = 1;
    int rear = front-1;
    int i=0;
    while(i<N){
        while(now<N){
            b[++rear] = a[now];
            if(a[now] == array[i]){
                now++; 
                break;
            } 
            now++;
        }
        if(array[i]!=b[rear]&&array[i]!=b[front]){
            return 0;//impossible
        }
        else{
            if(array[i] == b[rear]) rear--;
            else front++;
        }
        i++;
    }
    return 1;//possible
}
int main(){
    int N, K;
    scanf("%d %d", &N, &K);
    int i,j;
    for(i=0; i<N; i++){
        scanf("%d", &a[i]);
    }
    for(i=0;i<K;i++){
        int array[maxn];
        for(j=0; j<N; j++){
            b[j]=0;
        }
        for(j=0; j<N; j++){
            scanf("%d",&array[j]);
        }
        int flag=possibility(N,array);
        if(i!=K-1){
            if(flag) printf("yes\n");
            else printf("no\n");
        }
        else{
            if(flag) printf("yes");
            else printf("no");
        }
    }
    return 0;
}
// 5 4
// 10 2 3 4 5
// 10 3 2 5 4
// 5 10 3 2 4
// 2 3 10 4 5
// 3 5 10 4 2

