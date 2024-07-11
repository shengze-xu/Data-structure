#include <stdio.h>
int arr[110];
int test[110];
int next[110];
void InsertionSort(int s,int N);
void BuildMaxHeap(int t);
void PercolateDown(int s,int e);
void HeapSort(int size);
int main()
{
    int N,i,tmp,flag=0;
    scanf("%d",&N);
    int t=N;
    for(i=0;i<N;i++){
    	scanf("%d",&arr[i]);
	}
	for(i=0;i<N;i++){
    	scanf("%d",&test[i]);
	}
	for(i=0;i<N;i++){
		if(test[i]>test[i+1])break;
	}
	i++;
	tmp=i;
	while(i<N){
		if(test[i]!=arr[i])break;
		i++;
	} 
	if(i==N){
		printf("Insertion Sort\n");
		InsertionSort(tmp,N); 
	}else{
		printf("Heap Sort\n");
		while(!flag){
			HeapSort(t);
			for(i=0;i<N;i++){
				if(arr[i]!=test[i]) {
					t--;
					break;
				}
			}
			if(i==N)flag=1;
		}
		HeapSort(t-1);
		for(i=0;i<N;i++){
			test[i]=arr[i];
		}
	}
	for(i=0;i<N;i++){
		if(i==0)printf("%d",test[i]);
		else printf(" %d",test[i]);
	}
    return 0;
}
void InsertionSort(int s,int N){
	int j=s-1,tmp;
	tmp=test[s];
	while(j>=0){
		if(tmp>test[j])break;
		test[j+1]=test[j];
		j--;
	}
	test[j+1]=tmp;
}
void PercolateDown(int s,int e){
	int parent=s,child;//��0��e(size-1) 
	int t=arr[s];

	for(;parent*2+1<e;parent=child){
		child=parent*2+1;
		if(child+1<e&&arr[child+1]>arr[child]){
			child++;
		}
		if(arr[child]<t)break;
		arr[parent]=arr[child];
	}
	arr[parent]=t;

}
void BuildMaxHeap(int t){
	int i;
	for(i=t/2-1;i>-1;i--){
		PercolateDown(i,t);
	}
}
void HeapSort(int size){
	int temp;
	BuildMaxHeap(size);
	
	temp=arr[size-1];
	arr[size-1]=arr[0];
	arr[0]=temp;
	PercolateDown(0,size-1);
}

