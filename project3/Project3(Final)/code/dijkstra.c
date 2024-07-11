#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define inf 100000000
#define maxn 1050

typedef struct _Node{//First we write a linked list ourselves
	int value;
	struct _Node *next;
}Node;//The value of the head node stores the length of the linked list 

int ambulance[15];//Number of ambulances in rescue centers
int G[maxn][maxn];//Distance between nodes
int d[15][maxn];//The distance between the nodes in the question
int flag[maxn];//The value is only 0 or 1
int Ns,Na,M,K;//Variables given in the title
Node *temp;
Node *path;
Node *pre[15][maxn];

int size(Node *Head){//Returns the length of the linked list
	return Head->value;
}
Node* copy(Node *Head){//Copy a linked list
	Node *pNode=Head;//Define a new node
	Node *Thead,*Tnode;//Define new nodes
	if(pNode!=NULL){//
		Thead=(Node*)malloc(sizeof(Node));
		Thead->value=pNode->value;
		Thead->next=NULL;
		Tnode=Thead;
		pNode=pNode->next;
	}//The case where the head node is not empty
	while(pNode!=NULL){//Enter the loop to traverse one by one and assign values
		Node *tempNode=(Node*)malloc(sizeof(Node));
		tempNode->value=pNode->value;
		tempNode->next=NULL;
		Tnode->next=tempNode;
		Tnode=Tnode->next;
		pNode=pNode->next;
	}
	return Thead;//Return the head node of the new linked list
}
void append(Node *Head,int x){//Add elements to the end of the linked list
	Node *T = (Node*)malloc(sizeof(Node));
	T->value = x;
	Node *p = Head;
	while(p->next!=NULL) p = p->next;//Traverse to reach the target node
	T->next = p->next;
	p->next = T;
	Head->value++;//the length of the linked list increases by 1
}
void remove_back(Node *Head){//remove an element in the linked list
	Node *p = Head, *t;
	while(p->next!=NULL){//Traverse to reach the target node
		t=p;
		p=p->next;
	}
	t->next=t->next->next;
	free(p);//Free up space
	Head->value--;//the length of the linked list decreases by 1
}
void clear(Node *Head){//Empty the linked list
	Node *p = Head->next, *t;
	while(p!=NULL){//Free up space
		t = p;
		p = p->next;
		free(t);
	}
	Head->next=NULL;
	Head->value=0;//Then the length of the linked list is reset to zero
}
int at(Node *Head,int index){//Returns the value of the index node
	if(index >= size(Head))return -1;//If it is greater than the length of the linked list
	int i=0;
	Node *p = Head->next;
	while(i<index){
		p = p->next;
		i++;
	}//Traverse to reach the target node
	return p->value;
}
void initialize(){//Initialize the linked list when the program starts, the first line of the main program
	temp = (Node*)malloc(sizeof(Node));
	temp->value=0;//The length of the linked list is 0
	temp->next=NULL;//The head node points to NULL

	path = (Node*)malloc(sizeof(Node));
	path->value=0;
	path->next=NULL;

	int i,j;
	for(i=0;i<15;i++){
		for(j=0;j<maxn;j++){
			pre[i][j] = (Node*)malloc(sizeof(Node));
			pre[i][j]->value=0;
			pre[i][j]->next=NULL;
		}
	}//The same is true for the linked list of a two-dimensional array, which is defined one by one
}
int StrToInt(char *s){//Convert a string into an integer variable
	int result = 0,i;
	for(i=0; i<strlen(s); i++){
		result = result*10+s[i]-'0';
	}//To transform one by one
	return result;
}

void Dijsktra(int index){
	int i,j;
	for(i=0;i<maxn;i++){//Initialize variables
		flag[i]=0;
		d[index][i]=inf;
	}
	d[index][index+Ns]=0;
	for(i=1;i<=Ns+Na;i++){
		int u=-1;
		int min=inf;
		for(j=1;j<=Ns+Na;j++){//Initialize variables
			if(flag[j]==0&&d[index][j]<min){
				min=d[index][j];
				u=j;
			}
		}
		if(u==-1) return;
		flag[u]=1;//Initialize variables
		int v;
		for(v=1;v<=Ns+Na;v++){//Enter the loop to find the shortest path
			if(flag[v]==0&&G[u][v]!=inf){
				if(d[index][u]+G[u][v]<d[index][v]){//Update if the path is shorter than the current path
					clear(pre[index][v]);//clear the linked list
					append(pre[index][v],u);
					d[index][v]=d[index][u]+G[u][v];
				}else if(d[index][u]+G[u][v]==d[index][v]) append(pre[index][v],u);
			}
		}
	}
}
void DFS(int spot, int center){
	append(temp,spot);
	if(spot==center+Ns){
		if(size(path)==0) path=copy(temp);//copy the linked list
		else{
			if(size(temp)<=size(path)) path=copy(temp);//copy the linked list
		}
		remove_back(temp);//remove the element
		return;
	}
	int i;
	for(i=0;i<size(pre[center][spot]);i++){//Enter the loop and recurse continuously
		DFS(at(pre[center][spot],i),center);
	}
	remove_back(temp);//remove the element
}

int main(){
	initialize();//Initialize the linked list
	int i,j;
	for(i=0;i<maxn;i++){//Initialize two-dimensional arrays
		for(j=0;j<maxn;j++){
			G[i][j]=inf;
		}
	}
	scanf("%d%d",&Ns,&Na);
	for(i=1;i<=Na;i++){
		scanf("%d",&ambulance[i]);//Input variable
	}
	scanf("%d",&M);
	int u,v;
	char s1[10],s2[10];
	int time;
	for(i=0; i<M; i++){
		scanf("%s%s%d",s1,s2,&time);//Input variable
		//Convert string to integer
		if(s1[0]=='A') u = Ns+StrToInt(s1+2);
		else u = StrToInt(s1);
		if(s2[0]=='A') v = Ns+StrToInt(s2+2);
		else v = StrToInt(s2);
		G[u][v] = G[v][u] = time;//Get the distance between the two coordinates entered
	}
	for(i=1;i<=Na;i++){
		Dijsktra(i);
	}
	scanf("%d",&K);
	for(i=0;i<K;i++){
		int spot;
		int minTime=inf,maxAmbulance=-1,index=-1;
		Node *res;
		res = (Node*)malloc(sizeof(Node));
		res->value=0;
		res->next=NULL;
		scanf("%d",&spot);
		for(j=1;j<=Na;j++){
			if(ambulance[j]>0){//Is the number of ambulances greater than 0
				if(d[j][spot]<minTime){//If the current time is less than the shortest time available
					DFS(spot,j);
					minTime=d[j][spot];//Update the shortest time
					maxAmbulance=ambulance[j];//Update the maximum quantity
					res=copy(path);
					clear(path);
					index=j;
				}
				else if(d[j][spot]==minTime&&ambulance[j]>maxAmbulance){//If the quantity is greater than the current maximum quantity
					DFS(spot,j);
					maxAmbulance=ambulance[j];//Update the maximum quantity
					res=copy(path);
					clear(path);
					index=j;
				}
				else if(d[j][spot]==minTime&&ambulance[j]==maxAmbulance){
					DFS(spot,j);
					if(size(path)<size(res)){//If the number of streets is less than the current minimum number of streets
						res=copy(path);
						index=j;
					} 
					clear(path);
				}
			}	
		}	
		if(maxAmbulance==-1) printf("All Busy\n");//If no ambulance is available
		else{
			for(j=size(res)-1;j>=0;j--){//Output points passed by the path
				if(at(res,j)>Ns) printf("A-%d",at(res,j)-Ns);
				else printf("%d",at(res,j));
				if(j==0) printf("\n");//Wrap
				else printf(" ");//Output space
			}
			printf("%d\n",d[index][spot]);
			ambulance[index]--;//Number of ambulances minus one
		}
	}	
}

// 7 3
// 3 2 2
// 16
// A-1 2 4
// A-1 3 2
// 3 A-2 1
// 4 A-3 1
// A-1 4 3
// 6 7 1
// 1 7 3
// 1 3 3
// 3 4 1
// 6 A-3 5
// 6 5 2
// 5 7 1
// A-2 7 5
// A-2 1 1
// 3 5 1
// 5 A-3 2
// 8
// 6 7 5 4 6 4 3 2



 
