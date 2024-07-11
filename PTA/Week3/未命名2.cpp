#include <stdio.h>

int Pop(int a[],int N,int M);

int main(){
	int M,N,K,i,j;
	scanf("%d %d %d",&M,&N,&K);
	for(i=0;i<K;i++){
		int num[N];
		for(j=0;j<N;j++){
			scanf("%d",&num[j]);
		}
		int flag=Pop(num,N,M);
		if(flag==1){
			printf("YES\n");
		}
		else{
			printf("NO\n");
		}
	}
}

int Pop(int a[],int N,int M){
	int result,stack[N],ptsa=0,ptsb=0,num=1;
	while(1){
		if(num==a[ptsa]&&ptsb<M) {
            ptsa+=1;
            num+=1;
            ptsb+=0;
        }
        else if(stack[ptsb]==a[ptsa]){
            ptsb-=1;
            ptsa+=1;
        }
        else if(ptsb<M&&ptsa<N){
    		ptsb+=1;
            stack[ptsb]=num;
            num+=1;
        }
        else{
        	if(ptsa==N){
        		result=1;
			}
			else{
				result=0;
			}
			break;
		}
	}			
	return result;
}
