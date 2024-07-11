#include <stdio.h>
#define max 100000

int Find( int X , int S[] );
int Flag(int S[],int n);

int main()
{
	int n, S[max]={0};
	scanf("%d", &n);
	int i;
	for(i=1; i<=n; i++){
		S[i] = i;
	}
	char op;
	int num1, num2;
	getchar();
	while(1){
	    scanf("%c", &op);
		if(op=='S') break;
		scanf("%d %d", &num1, &num2);
		if(op=='C'){
			if(Find(num1, S)==Find(num2, S)){
				printf("yes\n");
			}
			else{
				printf("no\n");
			} 
		}
		if(op=='I'){
			if(Find(num1, S)!=Find(num2, S)){
				S[Find(num2, S)]=Find(num1, S);
			}
		}
	}
	int flag=Flag(S,n);
	if(flag==1){
		printf("The network is connected.");
	}
	else{
		printf("There are %d components.", flag);
	} 
	return 0;
}

int Find( int X , int S[] )
{
	int root, i, temp;
	if(X==S[X]) return X;
	for(root=X; S[root]!=root; root=S[root]);
	for(i=X; i!=root; i=temp){
		temp = S[i];
		S[i] = root;
	}	
	return root;
}

int Flag(int S[],int n){
	int i,num=0;
	for(i=1;i<=n;i++){
		if(S[i]==i) num++; 
	}
	return num;
}
