#ifndef _MAIN_H_
#define _MAIN_H_

typedef struct pointxy point;
typedef struct TreeNode* Tree;
#define NUM 100

struct pointxy { //define the struct to record the point in x-y coordinate 
	double x, y;
};

struct TreeNode { //define the struct of tree node 
	int p;
	int q;
	int flag;
	int level;
	double sumdis;
	Tree *k;
	Tree parent;
};

#endif // !_POINT_H_