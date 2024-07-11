#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxn 1005

int a[maxn];
int capacity[maxn][maxn]={0};
int flag[maxn][maxn]={0};
int min;
int node=0;
int temp[maxn]={0};
int sum=0;
int Path(const int S,const int D){
	if(S!=D){
        int i;
        for(i=0;i<node;i++){
            if(i!=S&&capacity[S][i]&&!flag[S][i]){
                flag[S][i]=1;
                if(!temp[i]&&Path(i,D)){
                    if(capacity[S][i]<min){
                        min=capacity[S][i];
                    }
                    return 1;
                }else{
                    temp[i]=1;
                    flag[S][i]=0;
                }
            }
        }
        return 0;
    }
    else{
        return 1;
    }
}
int mypow(int x,int n){
    if(n==0) return 1;
    int result=1,i;
    for(i=0;i<n;i++){
        result*=x;
    }
    return result;
}
int StrToInt(char *s){
	int result = 0,i;
	for(i=0; i<strlen(s); i++){
		result+=(s[i]-'A')*mypow(26,strlen(s)-i-1);
	}
	return result;
}
int mysum(int sum,int min){
    int i,j;
    for(i=0;i<node;i++){
        for(j=0;j<node;j++){
            if(flag[i][j]){
                capacity[i][j]-=min;
                capacity[j][i]+=min;
                flag[i][j]=0;
            }
        }
    }
    sum+=min;
    return sum;
}

int main(){
    int source,destination;
    int N;
    int i,j;
    char s1[4],s2[4];
    scanf("%s%s%d",s1,s2,&N);
    source=StrToInt(s1);
	destination=StrToInt(s2); 
    int s,d,c; 
    int S,D; 
    for(i=0;i<N;i++){
        getchar();
        scanf("%s%s%d",s1,s2,&c);
        s=StrToInt(s1);
		d=StrToInt(s2);
        int flags=-1,flagd=-1;
        for(j=0;j<node;j++){
            if(a[j]==s){
                flags=j;
            }
        }
        if(flags==-1){
            a[node]=s;
            if(s==source){
                S=node;
            }
            flags=node;
            node++;
        }
        for(j=0;j<node;j++){
            if(a[j]==d){
                flagd=j;
            }
        }
        if(flagd==-1){
            a[node]=d;
            if(d==destination){
                D=node;
            }
            flagd=node;
            node++;
        }
        capacity[flags][flagd]=c;
    }
    while(1){
        min=100000;
        for(i=0;i<node;i++){
            temp[i]=0;
        }
        if(Path(S,D)==0){
            break;
        }
        else{
            sum=mysum(sum,min);
        }
    }
    printf("%d",sum);
    return 0;
}