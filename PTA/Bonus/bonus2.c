#include <stdio.h>
#include <stdlib.h>
#define maxn 10050

void Bubble(int a[],int len){
	int i, j, temp;
	for (i = 0; i < len - 1; i++){
		for (j = 0; j < len - 1 - i; j++)
		if (a[j] > a[j + 1]){
			temp = a[j];
			a[j] = a[j + 1];
			a[j + 1] = temp;
		}
	}
}
int  findorder(int x,int a[],int N);

int main(){
    int N;
    scanf("%d",&N);
    int hat[maxn];
    int weight[maxn];
    int hat1[maxn];
    int weight1[maxn];

    int i,j;
    for(i=0;i<N;i++){
        scanf("%d",&hat[i]);
        hat1[i]=hat[i];
    }
    for(i=0;i<N;i++){
        scanf("%d",&weight[i]);
        weight1[i]=weight[i];
    }
    Bubble(hat1,N);
    Bubble(weight1,N);
    // for(i=0;i<N;i++){
    //     printf("%d ",hat1[i]);
    // }
    // printf("\n");
    // for(i=0;i<N;i++){
    //     printf("%d ",weight1[i]);
    // }

    //printf("%d",findorder(16,hat1,N));
    for(i=N-1;i>=0;i--){
        int order1;
        order1=findorder(hat[i],hat1,N);
        //printf("%d ",order);
        int order2;
        order2=findorder(weight1[order1],weight,N);
        if(i!=0){
            printf("%d ",order2+1);
        }
        else{
            printf("%d",order2+1);
        }
    }

}

int  findorder(int x,int a[],int N){
    int i;
    for(i=0;i<N;i++){
        if(x==a[i]){
            return i;
        }
    }
}