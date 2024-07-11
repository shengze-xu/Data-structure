#include<stdio.h> 
#include<stdlib.h>

/*build the tree*/
typedef struct TreeNode *Tree;
struct TreeNode {
    int  element;
    int  level;
    Tree  Left;
    Tree  Right;
}; 
/*build the queue*/
typedef struct QueueNode *Node;
struct QueueNode{
	Tree Element;
	Node Next;
};
typedef struct Queueall *Queue;
struct Queueall{
	Node Front;
	Node Rear;
};

static int N;
static int a[50],b[50]; /*a is the inorder sequence£¬b is the postorder sequence */

void BuildTree(int start, int end, int level, Tree root);
void levelorder(Tree root);
Queue CreateQueue();
void Enqueue(Tree root, Queue q);
int isempty(Queue q);
Tree Output(Queue q);
void Dequeue(Queue q);

int main(void)
{
	int i;
	int size=sizeof(struct TreeNode);
	Tree root;

	
	scanf("%d",&N);
	
	for (i=1;i<=N;i++){
		scanf("%d",&a[i]);
	}
	for (i=1;i<=N;i++){
		scanf("%d",&b[i]);
	}
	
	root=(Tree)malloc(size);
	root->element=b[N];
	root->level=1;
	root->Left=NULL;
	root->Right=NULL;
	BuildTree(1,N,1,root);
	levelorder(root);/*print the order*/
	
	return 0;
}

/* build the tree*/
void BuildTree(int start, int end, int level, Tree root)
{
	int start1,end1,i,leftlength,rightlength,j;
	Tree rootl,rootr; /*create left and right nodes*/
	int size=sizeof(struct TreeNode);
	start1=N;
	
	for(j=start;j<=end;j++){
		for(i=1;i<=N;i++){
		if(a[i]==b[j]) {
			if(i<start1) start1=i;
			break;
		}
		} 
	}
	for(i=1;i<=N;i++){
		if(a[i]==b[end]) {
			end1=i;
			break;
		}
	}
	leftlength=end1-start1;
	rightlength=end-start-end1+start1;
	
	
	if(leftlength>0)
	{
		rootl=(Tree)malloc(size);
		rootl->element=b[start+end1-start1-1];
	    rootl->level=level+1;
	    rootl->Left=NULL;
	    rootl->Right=NULL;
	    root->Left=rootl;
	    BuildTree(start,start+end1-start1-1,level+1,rootl);
	}
	if(rightlength>0)
	{
		rootr=(Tree)malloc(size);
		rootr->element=b[end-1];
	    rootr->level=level+1;
	    rootr->Left=NULL;
	    rootr->Right=NULL;
	    root->Right=rootr;
	    BuildTree(start+end1-start1,end-1,level+1,rootr);
	}
	
}


void levelorder(Tree root)
{
	Queue q;
	int c[32];
	int tmplevel,tmpcount;/*to record the level and the count of each level*/
	int i;
	tmplevel=1;
	tmpcount=0;
	Tree t;
		
	q=CreateQueue();
	Enqueue(root,q);
	
	while(!isempty(q)){
		t=Output(q);
		Dequeue(q);
		if(t->Left!=NULL) Enqueue(t->Left,q);
		if(t->Right!=NULL) Enqueue(t->Right,q);
		if(t->level==tmplevel) {
			tmpcount=tmpcount+1;
			c[tmpcount]=t->element; /*record the elements of the level in the array*/
		}
		else{
			if(tmplevel==1) printf("%d",c[1]);
			else if(tmplevel%2==0){
				for(i=1;i<=tmpcount;i++) printf(" %d",c[i]);
			}
			else{
				for(i=tmpcount;i>=1;i--) printf(" %d",c[i]);
			}
			tmplevel=tmplevel+1;
			tmpcount=1;	
			c[1]=t->element;
		}
	}
	
	if(tmplevel==1) printf("%d",c[1]);
	else if(tmplevel%2==0){
			for(i=1;i<=tmpcount;i++) printf(" %d",c[i]);
		}
	else{
		for(i=tmpcount;i>=1;i--) printf(" %d",c[i]);
	}
	
}
/*build new queue*/
Queue CreateQueue()
{
	int size1=sizeof(struct Queueall);
	int size2=sizeof(struct QueueNode);
	Queue q;
	
	q=(Queue)malloc(size1);
	q->Front=(Node)malloc(size2);
	q->Front->Next=NULL;
	q->Front->Element=NULL;
	q->Rear=q->Front;
	
	return q;
}
/*put tree into queue*/
void Enqueue(Tree root, Queue q)
{
	Node p;
	int size=sizeof(struct QueueNode);
	
	p=(Node)malloc(size);
	p->Element=root;
	p->Next=NULL;
	q->Rear->Next=p;
	q->Rear=q->Rear->Next;
}
/*judge if the queue is empty*/
int isempty(Queue q)
{
	if(q->Front==q->Rear) return 1;
	else return 0;
}
/*dequeue and output the tree*/
Tree Output(Queue q)
{
	return q->Front->Next->Element	;
}
void Dequeue(Queue q)
{
	Node tmp;
	tmp=q->Front->Next;
	if(tmp->Next==NULL) q->Rear=q->Front;
	q->Front->Next=tmp->Next;
	free(tmp);
}

