#include <stdio.h>
#include <math.h>
#define max 10000

int a[max],b[max];

void Reorder(int N);
void BuildTree(int al,int ar,int root);
void PrintTree(int N);

int main(){
    int N;
    scanf("%d",&N);
    int i;
    for(i=0;i<N;i++){
        scanf("%d",&a[i]);
    }
    Reorder(N);
//    for(i=0;i<N;i++){
//        printf("%d", a[i]);
//    }
	BuildTree(0,N-1,0);
	PrintTree(N);
}

void Reorder(int N){
    int i,j;
    for(i=1;i<N;i++){
        for(j=0;j<N-i;j++){
            if(a[j]>a[j+1]){
                int temp=a[j];
                a[j]=a[j+1];
                a[j+1]=temp;
            }
        }
    }
}

void BuildTree(int al,int ar,int root){
	int n=ar-al+1;
	if(n==0) return;
	int height,number,Lnumber;
	height=(int)(log(n+1)/log(2));
	number=n-pow(2,height)+1;
	if(number>=pow(2,height-1)){
		number=pow(2,height-1);
	}
	Lnumber=pow(2,height-1)-1+number;
	b[root]=a[al+Lnumber];
	BuildTree(al,al+Lnumber-1,root*2+1);
	BuildTree(al+Lnumber+1,ar,root*2+2);
}

void PrintTree(int N){
	int i;
	for(i=0;i<N;i++){
		if(i==0){
			printf("%d",b[i]);
		}
		else{
			printf(" %d",b[i]);
		}
	}
}


