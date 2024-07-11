#include<stdio.h>
#define Maxsize 10001

int Find( int X , int S[] );
void Union( int S[] , int root1 , int root2 );
void Check( int num1 , int num2 , int S[] );
void Connect( int num1 , int num2 , int S[] );


int main()
{
	int n, S[Maxsize]={0};
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
		//printf("op = %c num1 = %d num2 = %d\n", op, num1, num2);
		if(op=='C') Check(num1, num2, S);
		if(op=='I') Connect(num1, num2, S);
	}
	int cnt = 0;
	for(i=1; i<=n; i++){
		if(S[i]==i) cnt++;
	}
	if(cnt==1) printf("The network is connected.");
	else printf("There are %d components.", cnt);
	
	return 0;
}

int Find( int X , int S[] )
{
	int root, trail, temp;
	if(X==S[X]) return X;
	for(root=X; S[root]!=root; root=S[root]) ;
	for(trail=X; trail!=root; trail=temp){
		temp = S[trail];
		S[trail] = root;
	}
	
	return root;
}

void Union( int S[] , int root1 , int root2 )
{
	S[root2] = root1;
}

void Check( int num1 , int num2 , int S[] )
{
	if(Find(num1, S)==Find(num2, S)) printf("yes\n");
	else printf("no\n");
}

void Connect( int num1 , int num2 , int S[] )
{
	int root1=Find(num1, S), root2=Find(num2, S);
	if(root1!=root2) Union(S, root1, root2);
}

