#include <stdio.h>
#include <string.h>
#define max  10000

int n, a[max], b[max], c[max], num[max], guess[max];
//n is a given positive number, a[], b[], c[] store the input traversal sequence in middle, pre-, and post-order respectively
int tree[max][2], root;
//root is used to store the root node, tree[][] stores left and right subtrees
int aa[max],bb[max],cc[max];
//these three arrays are used to store the subscript when a certain value appears 
int in[max],pre[max],post[max]; 
//Complete mid-order, pre-order and post-order sequence 
char s[max];
//for input string 

int flag,temp;
int height[max][max]={0};
//use a two-dimensional array to store the value of a node in a certain layer of the tree, which is convenient for output when traversing the layer sequence 
int length[max]={0};
//use an array to store the number of nodes at a certain level of the tree

void CreateList(int inleft,int inright,int postleft,int postright,int level){
	int temp=inleft;
	if(inleft>inright)return;//the situation at the end of the function
	if(postleft>postright)return;//the situation at the end of the function
	height[level][length[level]]=post[postright];//find the root node and store the value 
	length[level]++;//the number of nodes in this layer plus one
	while(in[temp]!=post[postright]){
		temp++;//find the position of the root node in the middle-order traversal sequence
	}
	int len=temp-inleft;//calculate relative position
	CreateList(inleft,temp-1,postleft,postleft+len-1,level+1);//operate on the left subtree
	CreateList(temp+1,inright,postleft+len,postright-1,level+1);//operate on the right subtree
}

void PrintBFS(int **height,int length[],int n,int level){
	int i,cnt=0;
	while(cnt<level){//Enter the loop body, traverse each layer
		if(cnt==0){
				printf("%d",height[0][0]);//Output root node
		}
		else{
			for(i=0;i<=length[cnt]-1;i++){//Output the nodes of each layer
				printf(" %d",height[cnt][i]);
			}
		}
		cnt+=1;
	}
}

int Findroot(int *x, int inleft, int inright, int preleft, int preright, int postleft, int postright) {
	if(inleft<=inright){//Conditions for entering operation
		int i; 
		if (b[preleft] && c[postright] && b[preleft] != c[postright]) return 0;
		for (i=inleft;i<=inright;i++){
			if(a[i]){//If the root node is not found, enter the next cycle
				if(b[preleft] && a[i] != b[preleft]) continue;
				if(c[postright] && a[i] != c[postright]) continue;
			}
			/*If the root node is found, assign a value to the array defined by ourselves*/ 
			if(a[i]>b[preleft]&&a[i]>c[postright]){
				guess[i]=a[i]; 
			}
			else{
				if(b[preleft]>c[postright]) guess[i]=b[preleft];
				else guess[i]=c[postright];
			}
			/*Verify that the value found is indeed correct*/
			if (aa[guess[i]] && aa[guess[i]] != i) continue;
			if (bb[guess[i]] && bb[guess[i]] != preleft) continue;
			if (cc[guess[i]] && cc[guess[i]] != postright) continue;
			*x = i;
			/*Check whether the left and right subtrees are reasonable*/
			if (!Findroot(&tree[*x][0], inleft, i - 1, preleft + 1, preleft + i - inleft, postleft, postleft + i - inleft - 1)) continue;//operate on the left subtree
			if (!Findroot(&tree[*x][1], i + 1, inright, preleft + 1 + i - inleft, preright, postleft + i - inleft, postright - 1)) continue;//operate on the right subtree
	 
			return 1;
		}
		return 0;
		//If no reasonable root node is found at the end of the loop, return 0 
	}
	else{
		*x = 0; 
		return 1; 
	}
} 

void restorein(int x) {
	if (!x) return;//Conditions for ending the call
	//Call the function to operate in the order of left, root, and right
	restorein(tree[x][0]);
	in[temp++]=guess[x];
	restorein(tree[x][1]);
}

void restorepre(int x) {
	if (!x) return;
	//Call the function in the order of root, left, and right to operate 
	pre[temp++]=guess[x];
	restorepre(tree[x][0]);
	restorepre(tree[x][1]);
}

void restorepost(int x) {
	if (!x) return;
	//Call the function to operate in the order of left, right, and root
	restorepost(tree[x][0]);
	restorepost(tree[x][1]);
	post[temp++]=guess[x];
}

int main()
{
	scanf("%d", &n);
	int number = 0;//Numbers that did not appear
	int res;
	
	int i,j;

	for (i=1;i<=n;i++){
	    scanf("%s",&s);
	    a[i]=0;
	    if(strcmp(s,"-")==0) a[i]=0;
	    //If the input is -, the integer 0 is stored in the array, and the unknown number is replaced by 0
	    else {
	    	/*Convert the input string into an integer, whether it is a single digit, a tens digit, a hundred digit, etc.*/
		    for(j=0;s[j]!='\0';j++){
		        a[i]=a[i]*10+s[j]-'0';
		    }
		}
		aa[a[i]]=i;//Storage subscript
		num[a[i]]++;//The number of times a certain number has appeared
	}
	for (i=1;i<=n;i++){
	    scanf("%s",&s);
	    b[i]=0;
	    if(strcmp(s,"-")==0) b[i]=0;
	    //If the input is -, the integer 0 is stored in the array, and the unknown number is replaced by 0
	    else {
	    	/*Convert the input string into an integer, whether it is a single digit, a tens digit, a hundred digit, etc.*/
		    for(j=0;s[j]!='\0';j++){
		        b[i]=b[i]*10+s[j]-'0';
		    }
		}
		bb[b[i]]=i;//Storage subscript
		num[b[i]]++;//The number of times a certain number has appeared
	}
	for (i=1;i<=n;i++){
	    scanf("%s",&s);
	    c[i]=0;
	    if(strcmp(s,"-")==0) c[i]=0;
	    //If the input is -, the integer 0 is stored in the array, and the unknown number is replaced by 0
	    else {
	    	/*Convert the input string into an integer, whether it is a single digit, a tens digit, a hundred digit, etc.*/
		    for(j=0;s[j]!='\0';j++){
		        c[i]=c[i]*10+s[j]-'0';
		    }
		}
		cc[c[i]]=i;//Storage subscript
		num[c[i]]++;//The number of times a certain number has appeared
	}

	for (i = 1; i <= n; i++) {if (!num[i]) number++; res = i; }
	//printf("cnt=%d,res=%d\n",cnt,res);

	if (number > 1 || !Findroot(&root, 1, n, 1, n, 1, n)) printf("Impossible\n");
	else {
		//printf("root=%d\n",v[root]);
		for (i = 1; i <= n; i++) if (!guess[i]) guess[i] = res;
			//printf("v[%d]=%d\n",i,guess[i]);
			
 		/*Output the result of in-order traversal*/
		temp=1;
		restorein(root);
		for(i=1;i<=n;i++){
			if(i==1) printf("%d",in[i]);
			else{
				printf(" %d",in[i]);
			}
		}
		printf("\n");
		/*Output the result of preorder traversal*/
		temp=1;
		restorepre(root);
		for(i=1;i<=n;i++){
			if(i==1) printf("%d",pre[i]);
			else{
				printf(" %d",pre[i]);
			}		
		}
		printf("\n");
		/*Output the result of post-order traversal*/
		temp=1;
		restorepost(root);
		for(i=1;i<=n;i++){
			if(i==1) printf("%d",post[i]);
			else{
				printf(" %d",post[i]);
			}
		}
		printf("\n");
		/*Call the function to store all the values in the sequence into a two-dimensional array*/
		CreateList(1,n,1,n,0);//
		int level=0;
		int num=0;
		for(i=0;num<n;i++){//Calculate the total number of layers
			num+=length[i];
			level+=1;
		}
		//printf("level=%d\n",level);
		int *p[max];
		for(i=0;i<level;i++){
			p[i]=height[i];//Store the address of a two-dimensional array
		}
		PrintBFS(p,length,n,level);//Output the result of layer sequence traversal
	}
	return 0;
}


//9
//3 - 2 1 7 9 - 4 6
//9 - 5 3 2 1 - 6 4
//3 1 - - 7 - 6 8 -

//10
//2 - 3 7 1 5 8 10 9 -
//- 4 2 3 1 - 6 8 9 -
//2 7 1 3 - - 9 8 6 -

//10
//2 4 6 8 10 - - - - -
//1 - 3 - 5 - 7 - 9 -
//- - - - - - - - - -

//10
//2 4 6 8 10 - - - - -
//- 2 3 - 5 - 7 - 9 -
//- - - - - - - - - -

//9
//3 - 2 1 - 9 - 4 6
//- - 5 - 2 1 - 6 4
//3 1 - - - - 6 8 -


