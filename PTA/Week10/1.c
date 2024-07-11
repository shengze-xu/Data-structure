#include<stdio.h>
#include<stdlib.h>

int arr[1005];
int capacity[1005][1005]={0};
int nNode=0;
int flag[1005][1005]={0};
int min;
int cannotToT[1005]={0};

int isRead(int s){
	int i;
    for(i=0;i<nNode;i++){
        if(arr[i]==s)return i;
    }
    return -1;
}

int findPath(const int S,const int T){
	int i;
	if(S==T) return 1;
	int m=min;
	for(i=0;i<nNode;i++){
		if(i!=S&&capacity[S][i]&&!flag[S][i]){
			flag[S][i]=1;
			if(!cannotToT[i]&&findPath(i,T)){
				if(capacity[S][i]<min)min=capacity[S][i];
				return 1;
			}else{
				cannotToT[i]=1;
				flag[S][i]=0;
				min=m;
			}
			
		}
	}
	return 0;
}

int main(){
    //read
    int i,j,k;
    char s1[4],s2[4];
    int n,w,S,T,tmpS,tmpD;
    int s,t,sum=0;
    scanf("%s%s%d",s1,s2,&n);
    s=((s1[0]-'A')*26+s1[1]-'A')*26+s1[2]-'A';
	t=((s2[0]-'A')*26+s2[1]-'A')*26+s2[2]-'A';
    for(i=0;i<n;i++){
        getchar();
        scanf("%s%s%d",s1,s2,&w);
        tmpS=((s1[0]-'A')*26+s1[1]-'A')*26+s1[2]-'A';
		tmpD=((s2[0]-'A')*26+s2[1]-'A')*26+s2[2]-'A';
        int ts=isRead(tmpS);//�±� 
        if(ts==-1){
        	arr[nNode]=tmpS;
            if(tmpS==s)S=nNode;
            ts=nNode;
            nNode++;
        }
        int td=isRead(tmpD);
        if(td==-1){
        	arr[nNode]=tmpD;
            if(tmpD==t)T=nNode;
            td=nNode;
            nNode++;
        }
        capacity[ts][td]=w;
        //printf("capacity[%d][%d]=%d\n",ts,td,capacity[ts][td]);
    }
    	
    for(;;){
        min=1000000;
        for(i=0;i<nNode;i++)cannotToT[i]=0;
        if(findPath(S,T)){
            for(j=0;j<nNode;j++){
                for(k=0;k<nNode;k++){
                    if(flag[j][k]){
                        capacity[j][k]-=min;
                        capacity[k][j]+=min;
                        flag[j][k]=0;
                    }
                }
        	}
         	sum+=min;   
        }else break;
    }
    
    printf("%d",sum);
    return 0;
}

