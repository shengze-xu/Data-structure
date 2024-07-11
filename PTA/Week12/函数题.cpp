#include <stdio.h>

#define ElementType int
#define MAXN 100

void merge_pass( ElementType list[], ElementType sorted[], int N, int length );

void output( ElementType list[], int N )
{
    int i;
    for (i=0; i<N; i++) printf("%d ", list[i]);
    printf("\n");
}

void  merge_sort( ElementType list[],  int N )
{
    ElementType extra[MAXN];  /* the extra space required */
    int  length = 1;  /* current length of sublist being merged */
    while( length < N ) { 
        merge_pass( list, extra, N, length ); /* merge list into extra */
        output( extra, N );
        length *= 2;
        merge_pass( extra, list, N, length ); /* merge extra back to list */
        output( list, N );
        length *= 2;
    }
} 


int main()
{
    int N, i;
    ElementType A[MAXN];

    scanf("%d", &N);
    for (i=0; i<N; i++) scanf("%d", &A[i]);
    merge_sort(A, N);
    output(A, N);

    return 0;
}

void merge_pass( ElementType list[], ElementType sorted[], int N, int length ){
	int i; 
	for(i=0;i<N;i+=length*2){
		int a=i,b=i+length;
		int end1;
		if(i+length<=N){
			end1=i+length;
		}
		else{
			end1=N;
		}
		int end2;
		if(i+2*length<=N){
			end2=i+2*length;
		}
		else{
			end2=N;
		}
		
		int num=i;
		while(a<end1&&b<end2){	
			if(list[a]<list[b]){
				sorted[num]=list[a];
				a+=1;
			}
			else{
				sorted[num]=list[b];
				b+=1;
			}
			num+=1;
		}
		while(a<end1){
			sorted[num]=list[a];
			num+=1;
			a+=1;
		}
      	while(b<end2){
      		sorted[num] = list[b];
      		num+=1;
      		b+=1;
		}
	}
}







