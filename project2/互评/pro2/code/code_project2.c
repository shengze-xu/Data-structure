#include <stdio.h>
#include <stdlib.h>
#define maxn 101
 

typedef struct TNode{ //creates struct tree
    int data;
    struct TNode *lchild,*rchild;
}TNode,*BinTree;
 
BinTree CreateTree(int A[],int B[],int n){ //creates binary tree 
    BinTree BT = (BinTree)malloc(sizeof(struct TNode)); //malloc the memory
    if(n<=0) return NULL; // if tree is empty,creating fail
    else{ //if tree is not empty
        int temp = A[n-1];
        int i;
        for(i=0;i<n;i++){   //find the index of root node in inorder
            if(temp== B[i]){
                break;
            }
        }
        BT->data = temp;  //creates the tree node
        BT->lchild = CreateTree(A,B,i);//travels left son_tree 
        BT->rchild = CreateTree(A+i,B+i+1,n-i-1);//travels right son_tree
        return BT;
    }
}

void LevelTraversal(BinTree BT){ //level_travelsal
    BinTree a[101];  //create an array to memory tree nodes
    int i=0,j=0;     //define variables这个数组作为队列来用
    a[0] = BT;       //memory tree nodes into array a[0]
    while(BT){
        if(BT->lchild!=NULL){
            a[++i] = BT->lchild;
        }            //every time when you visit root node,and put l_child_node into array
        if(BT->rchild!=NULL){
            a[++i] = BT->rchild;
        }            //every time when you visit root node,and put l_child_node into array
        BinTree temp = a[j];
        printf("%d",temp->data);
        if(i==j) break;//this level completes, don't need to add spacing
        else printf(" "); //add spacing
        j++;
        BT = a[j];   //travelsal all the tree
    }
    printf("\n");
}

int inorder[maxn], preorder[maxn], postorder[maxn], appear_time[maxn]={0}; //record initial data, appear_time records appear times
int reinorder[maxn], repreorder[maxn], repostorder[maxn]; //record the complete array 
int miss_cnt , miss_number; //miss_cent records the number of missing_umber, miss_number records missing data
int n,flag; //n is the number of nodes, flag is judging variable
int check(int h1, int h2, int h3, int l); //check if the section can create the only BinTree

int get(void);//change "-" into "0" and transfer data into int 
int get(void) {
	int tmp, i;
	char str[10]; //define array of char 
	scanf("%s", str);
	if (str[0] == '-') {
		return 0; //change "-" into "0" 
	}
	else {
		tmp = 0;
		for (i = 0; str[i]; i++) {
			tmp = tmp * 10 + str[i] - '0'; //in case that input double-digit 
		}
		return tmp; //return the final int 
	}
}

int main(void) {
	int i;
	scanf("%d", &n);  
	                     
	for (i = 0; i < n; i++) {inorder[i] = get(); appear_time[inorder[i]]++; //put the input data into array inorder[]
	if(inorder[i] != 0) reinorder[i] = inorder[i];}//if the input is not 0,then put it into complete array
	for (i = 0; i < n; i++) {preorder[i] = get(); appear_time[preorder[i]]++; //put the input data into array preorder[]
	if(preorder[i] != 0) repreorder[i] = preorder[i];}//if the input is not 0,then put it into complete array
	for (i = 0; i < n; i++) {postorder[i] = get(); appear_time[postorder[i]]++; //put the input data into array postorder[]
	if(postorder[i] != 0) repostorder[i] = postorder[i];}//if the input is not 0,then put it into complete array 

	miss_cnt = 0;
	for (i = 1; i <= n; i++) {
	  if (appear_time[i]==0){
          miss_number = i;
	      miss_cnt++;} //if i never appear, the add the miss_cnt
	  } 
	
	if(n==1&&inorder[0]==0&&preorder[0]==0&&postorder[0]==0){
		for(i=0;i<4;i++){
            printf("1\n"); //if the tree has only one node, we can create the tree
        }
	    return 0;
	} //even if there is no element, still can create the only Bin_Tree
	if(miss_cnt > 1 ) {
	    printf("Impossible");
	    return 0;
	} //if the number of missing is more than one, then fail
    
	flag = check(0, 0, 0, n); //input flag

	if(n==1&&flag==1){
		int a=reinorder[0];
		for(i=0;i<4;i++)
		printf("%d\n",a);
	}
	if(flag == 1&&n>1){ //output the complete inorder queue
		for(i=0;i<n;i++){
			if(i==0)    
			printf("%d",reinorder[0]); //output the first data
			if(i>0&&i<n-1)
			printf(" %d",reinorder[i]); //output the other data 
			if(i>0&&i==n-1)
			printf(" %d\n",reinorder[i]); //when finish, newline
		}
		for(i=0;i<n;i++){ //output the complete inorder queue
			if(i==0)
			printf("%d",repreorder[0]); //output the first data
			if(i>0&&i<n-1)
			printf(" %d",repreorder[i]);  //output the other data
			if(i>0&&i==n-1)
			printf(" %d\n",repreorder[i]); //when finish, newline 
		}
		for(i=0;i<n;i++){ //output the complete inorder queue
			if(i==0)
			printf("%d",repostorder[0]); //output the first data
			if(i>0&&i<n-1)
			printf(" %d",repostorder[i]); //output the other data
			if(i>0&&i==n-1)
			printf(" %d\n",repostorder[i]); //when finish, newline 
		}
	    BinTree BT = CreateTree(repostorder,reinorder,n); //creat the BinTree according the repostorder and reinorder
        LevelTraversal(BT); //level traversal the tree
	}    
    if(flag ==0){
        printf("Impossible");
	    return 0;
    }
	return 0;
}

int check(int h1, int h2, int h3, int l){//h1 is the head inorder,h2 is head of preorder,h3 is head of postorder,l is length 
    if(l == 0) return 1;//l=0,then finish the traversal,can create correct tree 
	int l1,k=0;
	for(l1 =0; l1<l; l1++){
		int l2 = l-l1-1;
		int size = 0; //record the number of possible root
		int cnt = 0; //record the appear times of possible root
		int root_number;
        if(preorder[h2] > 0 && postorder[h3+l-1] > 0 && preorder[h2] != postorder[h3+l-1]){  
            return 0;  //if the head of preorder!=the tail of postorder,it is impossible to create the tree
        }
		if(inorder[h1+l1] > 0) {
			size++;      //traversal the inorder to find the possible root
			cnt++;
			root_number=inorder[h1+l1];
		}
		if(preorder[h2] > 0){
			cnt++;       //traversal the preorder to find the possible root
			if(inorder[h1+l1] > 0&&preorder[h2] != inorder[h1+l1])
			size++;
		    if(inorder[h1+l1] == 0)
			root_number = preorder[h2];
		}
		if(postorder[h3+l-1] > 0){
			cnt++;       //traversal the postorder to find the possible root
			if((inorder[h1+l1]>0&&postorder[h3+l-1]!=inorder[h1+l1])||(preorder[h2] > 0&&postorder[h3+l-1]!=preorder[h2]))
			size++;
			if(inorder[h1+l1] == 0&&preorder[h2]==0)
			root_number = postorder[h3+l-1];
		}
		if(size > 1) //if size>1, then appear more than one possible root,then fail
		continue;
		if(cnt == 0){ //if size = 0,then three order missing
			if(miss_cnt == 0) continue; //if there is no missing,then fail  
			reinorder[h1+l1] = miss_number; //complete the order
		    repreorder[h2] = miss_number; //complete the order
		    repostorder[h3+l-1] = miss_number; //complete the order
			miss_cnt--; //if complete,then miss_cnt decline
		}
		else{ //if size=1,this level is correct
		
			if(cnt != appear_time[root_number]) continue; //check if the number equal with appear_time
			reinorder[h1+l1] = root_number; //complete missing number
			repreorder[h2] = root_number; //complete missing number
			repostorder[h3+l-1] = root_number; //complete missing number
		}
		int b1 = check(h1,h2+1,h3,l1); //check the l_child tree 
		int b2 = check(h1+l1+1,h2+1+l1,h3+l1,l2); //check the r_child tree 
		if(!cnt)
			miss_cnt = 1;
		if(b1==1&&b2==1) return 1;
	}
	return 0;
}
