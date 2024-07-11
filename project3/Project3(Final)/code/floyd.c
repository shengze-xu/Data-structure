#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define inf 1000000000
#define maxn 1050

typedef struct _Node{//First we write a linked list ourselves
	int value;
	struct _Node *next;
}Node;//The value of the head node stores the length of the linked list 

int ambulance[15]={0};//Number of ambulances in rescue centers
int G[maxn][maxn];//Distance between nodes
int d[maxn][maxn];//The distance between the nodes in the question
int path[maxn][maxn];//The midpoint of the shortest path between any two points
int Ns,Na,M,K;//Variables given in the title
Node *ans;//Head node

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
	ans = (Node*)malloc(sizeof(Node));
	ans->value=0;//The length of the linked list is 0
	ans->next=NULL;//The head node points to NULL
}
int StrToInt(char *s){//Convert a string into an integer variable
	int result = 0,i;
	for(i=0; i<strlen(s); i++){
		result = result*10+s[i]-'0';
	}//To transform one by one
	return result;
}

void Floyd(int Ns,int Na){
	int i,j,k;
	int n=Ns+Na;
	for(k=1; k<=n; k++){//Enter the loop to find the shortest path
		for(i=1; i<=n; i++){
			for(j=1; j<=n; j++){
				if(d[i][k]+d[k][j]<d[i][j]){//Update if shorter than current
					d[i][j] = d[i][k]+d[k][j];
					path[i][j] = k;//Update midpoint
				}
			}
		}
	}
}
int Number(int i, int j){
	if(path[i][j]==-1) return 0;
	else return 1+Number(i,path[i][j])+Number(path[i][j],j);//Return the value of the number of streets
}
void Path(int i, int j){
	if(path[i][j]==-1) return;
	Path(i,path[i][j]);//The path from the first point to the middle point
	append(ans,path[i][j]);//Update the shortest path by operating on the linked list
	Path(path[i][j],j);//The path from the middle point to the second point
}

int main(){
	initialize();//Initialize the linked list
	int i,j;
	for(i=0;i<maxn;i++){//Initialize two-dimensional arrays
		for(j=0;j<maxn;j++){
			path[i][j]=-1;
			G[i][j]=inf;
		}
	}
	for(i=0; i<maxn; i++){
		G[i][i] = 0;//The distance from the point to itself is 0
	}
	scanf("%d%d",&Ns,&Na);
	for(i=1; i<=Na; i++){
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
	for(i=0; i<maxn; i++){
		for(j=0; j<maxn; j++){
			d[i][j] = G[i][j];//Two-dimensional array is symmetric
		}
	}
	Floyd(Ns,Na);//Use the floyd algorithm to traverse all nodes to get the shortest distance between any two points
	int spot;
	scanf("%d",&K);
	for(i=0; i<K; i++){
		scanf("%d",&spot);
	/*	printf("spot=%d\n",spot);*/
		int minTime=inf,maxAmbulance=-1,minNumber=inf,index=-1;
		for(j=1; j<=Na; j++){
			if(ambulance[j]>0){//Is the number of ambulances greater than 0
				if(d[j+Ns][spot]<minTime){//If the current time is less than the shortest time available
					minTime = d[j+Ns][spot];//Update the shortest time
					maxAmbulance = ambulance[j];//Update the maximum quantity
					minNumber = Number(j+Ns,spot);//Minimum number of streets
					index =  j;
				}
				else if(d[j+Ns][spot]==minTime&&ambulance[j]>maxAmbulance){//If the quantity is greater than the current maximum quantity
					maxAmbulance = ambulance[j];//Update the maximum quantity
					minNumber = Number(j+Ns,spot);//Minimum number of streets
					index =  j;
				}
				else if(d[j+Ns][spot]==minTime&&ambulance[j]==maxAmbulance&&Number(j+Ns,spot)<minNumber){//If the number of streets is less than the current minimum number of streets
					minNumber = Number(j+Ns,spot);//Update the minimum number of streets
					index =  j;
				}
			}
		}
		if(index==-1) printf("All Busy\n");//If no ambulance is available
		else{
			clear(ans);			
			Path(index+Ns,spot);//Get the most suitable path for a certain point 
			printf("A-%d",index);
			for(j=0; j<size(ans); j++){//Output points passed by the path
				if(at(ans,j)>Ns) printf(" A-%d",at(ans,j)-Ns);
				else printf(" %d",at(ans,j));
			}
			printf(" %d\n",spot);
			printf("%d\n",minTime);//Output shortest time
			ambulance[index]--;//Number of ambulances minus one
		}
	}
	return 0;
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
 
 
 
 
 
 

