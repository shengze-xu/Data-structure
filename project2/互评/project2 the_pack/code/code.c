#include<stdio.h>
#include<stdlib.h>

typedef struct tree *node;
struct tree{
    int value;
	int flag;
	//to remove bug from building a tree, it will be made clearer in the following code
    node left;
    node right;
};
 
typedef struct queue{
    node numQ[100];//the max size of queue
    int front;
    int rear;
}Queue;
 
Queue Q;//designed for level-output
int in[200], pre[200], post[200],level[200];
//firstly, it can record input data; secondly it will be reused for standard output
int check[200];
//to check whether sufficient data is provided
int n;//record the limit of the data
char ch;
node root ;//it's the root of our tree
int out;//its usage is the same as level[200], aiming at standard output

void initilize();
void Push(node rt);
node Pop();
int empty();
//queue library, used for levelorder output
int get();
//deal with '-' and unsingle digit integer, get data
int max(int a,int b);//to get non-zero number
int dfs(node rt, int inl, int inr, int prel, int prer, int postl, int postr);
//most important function, to build the tree and determine whether a tree can be built
void out_pre(node rt);//pre-order out put 
void out_in(node rt);//in-order output
void out_post(node rt);//post-order output
void out_level(node rt);  //level-order output

int main() 
{
	int j,i;
	root= (node)malloc(sizeof(node));//set a root to start a tree
	root->flag=0;//as long as the value of the code hasn't been changed, the flag is 0
	node rt=root;//convey the variable
	root->left==NULL;
	root->right==NULL;
	scanf("%d",&n);
	for (j = 1; j <= n; j++) {
			in[j] = get();
			check[in[j]] = 1;
	}
	for (j = 1; j <= n; j++) {
			pre[j] = get();
			check[pre[j]] = 1;
	}
	for (j = 1; j <= n; j++) {
			post[j] = get();
			check[post[j]] = 1;
	}
	//get data, explained clearly in get() function
	for (i = 1; i <= n; i++) {
		if (check[i] == 0) {
			printf("Impossible");
			return 0;
		}
	}
	//whether suffcient data is given
	if (!dfs(root, 1, n, 1, n, 1, n)) {
		printf("Impossible");
		return 0;
	}
	//whether a tree can be built
	out_in(root); 
	for(i=1;i<out;i++){
		printf("%d ",in[i]);
	}
	printf("%d\n",in[i]);
	out=0;
	//standard output to pass the test point, the following are the same 
	out_pre(root); 
	for(i=1;i<out;i++){
		printf("%d ",pre[i]);
	}
	printf("%d\n",pre[i]);
	out=0;
	out_post(root);
	for(i=1;i<out;i++){
		printf("%d ",post[i]);
	}
	printf("%d\n",post[i]);
	out=0;
	out_level(root); 
	for(i=1;i<out;i++){
		printf("%d ",level[i]);
	}
	printf("%d\n",level[i]);
	return 0;
}

int max(int a,int b)
{
	if(a>b){
		return a;
	}else{
		return b;
	}
}
//get the max value, get the non-zore data quicker
int dfs(node rt, int inl, int inr, int prel, int prer, int postl, int postr) 
{
	if (inl > inr) {
		rt->flag=0;
		return 1;
	}
	//the end of the iteration, the leaves' flag are set 0, so we can determine whether a tree is already built
    int i;
	rt->left=(node)malloc(sizeof(node));
	rt->right=(node)malloc(sizeof(node));
	//creat left child and right child, transfer variable to next iteration
	for (i = inl; i <= inr; i++) {//"violently" enumeration, try every element to check if in[i] can be the root
		if (in[i] * pre[prel] && in[i] != pre[prel]) continue;
		if (in[i] * post[postr] && in[i] != post[postr]) continue;
		if (post[postr] * pre[prel] && post[postr] != pre[prel])continue;
		rt->value = max(in[i],max(pre[prel],post[postr]));
		//get the value of the root, if any two of them are not equal, in[i] can't be the root
		rt->flag=1;//already been changed, set flag 1
		if (rt->value == 0) return 0;
		//all three are unknown, in[i] can't be the root, try next
		if (!dfs(rt->left, inl, i - 1, prel + 1, prel + i - inl, postl, postl + i - inl - 1))continue;
		if (!dfs(rt->right, i + 1, inr, prer - (inr - i) + 1, prer, postr - (inr - i), postr - 1))continue;
		//iteration for root's left child and right child
		return 1;
		//in[i] can be the root, return true
	}
	return 0;
	//in[i] can't be the root, return false
}

int get()
{
	int tmp, i;
	char str[10];
	scanf("%s", str);
	if (str[0] == '-') {
		return 0;
	}
	else {
		tmp = 0;
		for (i = 0; str[i]; i++) {
			tmp = tmp * 10 + str[i] - '0';
		}
		return tmp;
	}
}
//to get data. as the data can't be read due to the existence of '-', we need to read them as char and get over one digit data
void out_in(node rt) 
{
	if (rt==NULL) return;
	if (!rt->left->flag) rt->left =NULL; 
	if (!rt->right->flag) rt->right =NULL;
	out_in(rt->left);
	in[++out]=rt->value;
	out_in(rt->right);
}
//in-order output
void out_pre(node rt)
{
	if(rt==NULL) return;
	pre[++out]=rt->value;
	out_pre(rt->left);
	out_pre(rt->right);
}
//pre-order output
void out_post(node rt)
{
	if (rt==NULL) return;
	out_post(rt->left);
	out_post(rt->right);
	post[++out]=rt->value;
}
//post order output
void initilize() 
{ //initialize a queue
    Q.front = 0;
    Q.rear = 0;
}
 
void Push(node rt) 
{ //push a node into the queue
    Q.numQ[++Q.rear] = rt;
}
 
node Pop() 
{ //pop a node out of the queue
    return Q.numQ[++Q.front];
}
 
int empty() 
{ //check whether a queue is empty
    return Q.rear == Q.front;
}
 
void out_level(node rt) 
{ //traversal of a tree in level-order
    node temp;
    Push(rt);
    while (!empty()) {
        temp = Pop();
        level[++out]=temp->value;;  //输出队首结点
        if (temp->left)     //把Pop掉的结点的左子结点加入队列
            Push(temp->left);
        if (temp->right)    //把Pop掉的结点的右子结点加入队列
            Push(temp->right);
    }
}
