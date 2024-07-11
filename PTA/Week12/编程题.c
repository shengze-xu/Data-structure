#include<stdio.h>
#define maxn 1000

int a[maxn];
int b[maxn];
int c[maxn];
int IfInsert(int N){
    int i=0;
    for(i=0; i<N;i++){
        if(b[i]>b[i+1]) break;
    }
    for(i++;i<N;i++){
        if(b[i]!=a[i])break;
    }
    if(i==N) return 1;
    else return 0;
}

void PercolateDown(int start, int end){
	int parent=start;
    int child;
	int temp=c[start];

	for(;parent*2+1<end;parent=child){
		child=parent*2+1;
		if(child+1<end&&c[child+1]>c[child]){
			child++;
		}
		if(c[child]<temp)break;
		c[parent]=c[child];
	}
	c[parent]=temp;

}
void swap(int *a, int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
}
void HeapSort(int n){
    int i;
	for(i=n/2-1;i>-1;i--){
		PercolateDown(i,n);
	}
    swap(&c[n-1],&c[0]);
	PercolateDown(0,n-1);
}

int main(){
    int N;
    scanf("%d",&N);
    int i;
    for(i=0;i<N;i++){
        scanf("%d",&a[i]);
    }
    for(i=0;i<N;i++){
        scanf("%d",&b[i]);
    }
    int flag=IfInsert(N);
    if(flag){
        printf("Insertion Sort\n");
        for(i=0; i<N;i++){
            if(b[i]>b[i+1]) break;
        }
        int temp=b[i+1];
        while(i>=0){
            if(temp>b[i])break;
            b[i+1]=b[i];
            i--;
        }
        b[i+1]=temp;
        for(i=0;i<N;i++){
		    if(i==0)printf("%d",b[i]);
		    else printf(" %d",b[i]);
	    }
    }
    else{
        printf("Heap Sort\n");
        for(i=0;i<N;i++){
            c[i]=a[i];
        }
        int n=N;
        while(1){
			HeapSort(n);
			for(i=0;i<N;i++){
				if(c[i]!=b[i]) {
					n--;
					break;
				}
			}
			if(i==N) break;
		}
		HeapSort(n-1);
        for(i=0;i<N;i++){
		    if(i==0)printf("%d",c[i]);
		    else printf(" %d",c[i]);
	    }
    }
    return 0;
}


// 10
// 3 1 2 8 7 5 9 4 6 0
// 1 2 3 7 8 5 9 4 6 0

// 10
// 3 1 2 8 7 5 9 4 6 0
// 6 4 5 1 0 3 2 7 8 9