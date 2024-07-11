#include <stdio.h>
#define max 1010

int s[max];
int a[max];
int b[max];
int c[max];
void assign(int N){
    int i;
    for(i=0;i<N;i++){
        if(s[i]<0){
            b[i]=-1;
        }
        else{
            b[i]=(i-s[i]%N+N)%N;
        }
    }
    for(i=0;i<N;i++){
        c[i]=b[i];
    }
}

void modify(int N){
    int i,j;
    for(i=0;i<N;i++){
        int min=-1;
        int index;
        for(j=0;j<N;j++){
            if(b[j]==0&&(min==-1||s[j]<min)){
                index=j;
            }
        }
        for(j=0;j<N;j++){
            if(b[j]>=0){
                if(((j-index+N)%N)<=c[j]){
                    b[j]--;
                }
            }
        }
        a[i]=min;
    }
}

int main(){
    int N;
    scanf("%d",&N);
    int i;
    for(i=0;i<N;i++){
        scanf("%d",&s[i]);
    }
    assign(N);
    modify(N);
    i=0;
    while(i<N){ 
        if (a[i]==-1){
            break;
        } 
        if(i==0){
            printf("%d",a[i]);
        }
        else{
            printf(" %d",a[i]);
        }
        i++;
    }
    return 0;
}