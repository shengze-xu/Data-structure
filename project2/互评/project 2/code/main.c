#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "main.h"
#include "point.h"
#include "way.h"
//the max acceptable distance between child and parent
#define DISCOE 3
//the max acceptable angle between child and parent
#define ANGLECOE 0.2
//In mode one, assuming that the incomplete path can get 1 vote, the complete path can get PASS votes. 
#define PASS 3
//The coefficient to judge the pruning and to calculate the grading of one path
#define DIFFCOE DISCOE/ANGLECOE
#define SUMCOE 5
#define VOTE(x, y)  x / (y+SUMCOE)
#define SUMDIS(x) sqrt(x + 1) * DISCOE * SUMCOE

int N, M; //the number of points in A and B
point *A, *B; // The points array
point c; 
double **score1, **score2; //The two-dimensional array to record the votes or grades of certain pair
int LEVEL; //The max level of the tree

void expend(Tree Origin, double** score, int mode)
{
	//PART1: Parameter definition
	int i;
	double disadd = Origin->sumdis; //record the sum delta distance and delta angle (plus DIFFCOE) until this node
	double deldis = 0, delang = 0; //initialize limit factor
	int min, max;
	int p = Origin->level + 1;
	min = Origin->q + 1; // determine the possible range of child
	max = M - N + Origin->level + 1;
	//PART2: calculate the limit factor and judge expending or pruning
	Origin->k = (Tree*)malloc(sizeof(Tree) * (max-min+1));
	int j = 0;
	if (Origin->level < N - 1) //if the node is in the last level, it don't need expend
	{
		for (i = min; i <= max; i++) //calculate the limit factor
		{
		deldis = fabs(distance(A[Origin->p], A[p]) - distance(B[Origin->q], B[i]));
		if (Origin->level >= 1)
		{
			delang = fabs(angle(A[Origin->p], A[p], A[Origin->parent->p]) - angle(B[Origin->q], B[i], B[Origin->parent->q]));
		}
		disadd = deldis + delang*DIFFCOE + Origin->sumdis; //the definition of disadd
		//judge expending or pruning and initialize the new node
		if (deldis <= DISCOE && delang <= ANGLECOE && disadd <= SUMDIS(Origin->level)) 
		{
			Origin->flag++;
			Origin->k[j] = (Tree)malloc(sizeof(struct TreeNode));
			Origin->k[j]->flag = -1;
			Origin->k[j]->level = Origin->level + 1;
			Origin->k[j]->p = Origin->p + 1;
			Origin->k[j]->q = i;
			Origin->k[j]->parent = Origin;
			Origin->k[j]->sumdis = disadd;
			j++;
		}
		}
	}

	//PART3: Voting or Grading
	Tree ptr = Origin;
	if (mode == 1) //MODE 1
	{
		if (Origin->flag == -1)
		{
			Tree ptr = Origin;
			if (Origin->level != LEVEL) //to judge if the path is completed or not
			{
				while (ptr->level != -1) //incomplete path -- 1 vote
				{
					score[ptr->p][ptr->q]++;
					ptr = ptr->parent;
				}
			}
			else
			{
				while (ptr->level != -1) //complete path -- PASS votes
				{
					score[ptr->p][ptr->q] += PASS;
					ptr = ptr->parent;
				}
			}
		}
	}
	if (mode == 2) //MODE 2
	{
		if (Origin->flag == -1)
			while (ptr->level != -1) // Add up the grades every pair gets
			{
				score[ptr->p][ptr->q] += VOTE(ptr->level + 1, ptr->sumdis);
				ptr = ptr->parent;
			}
	}


	//PART4: expending
	for (i = 0; i < j; i++) // expende the node
	{
		expend(Origin->k[i], score, mode);
	}
}

int main()
{
	int mode;
	//get input
	printf("Please Input Mode NUM (MODE1-Voting Mode MODE2-Grading Mode):");
	scanf("%d", &mode); // mode input
	printf("Please Input BELOW:\n");
	scanf("%d %d", &N, &M); //get number of point in A and B
	if (M > N)//judge A and B which one is the paired one
	{
		LEVEL = N - 1;
		A = (point*)malloc(sizeof(point) * N); //malloc space for A and B
		B = (point*)malloc(sizeof(point) * M);
		REAMP(A, N); //input A and B
		REAMP(B, M);
	}
	else
	{
		int change; //B is to be paired one, thus to change the reading order
		change = N; N = M; M = change;
		LEVEL = N - 1;
		A = (point*)malloc(sizeof(point) * M); //malloc space for A and B
		B = (point*)malloc(sizeof(point) * N);
		REAMP(A, M); //input A and B
		REAMP(B, N);
	}

	int i, j; // malloc the two-dimensional array score1 and score2 and initialize them
	score1 = (double **)malloc(sizeof(double *) * N); //malloc int **score 
	for (i = 0; i < N; ++i)
	{
		score1[i] = (double *)malloc(sizeof(double) * M); //malloc int *score[i]
		for (j = 0; j < M; j++)
		{
			score1[i][j] = 0;
		}
	}
	score2 = (double **)malloc(sizeof(double *) * N);
	for (i = 0; i < N; ++i)
	{
		score2[i] = (double *)malloc(sizeof(double) * M);
		for (j = 0; j < M; j++)
		{
			score2[i][j] = 0;
		}
	}

	Tree root; 
	root = (Tree)malloc(sizeof(struct TreeNode)); //malloc the tree root
	root->flag = M - N - 1; //initialize the tree root
	root->p = -1; root->q = -1;
	root->level = -1;
	root->parent = NULL;
	root->k = (Tree*)malloc(sizeof(Tree) * (M - N)); //the number of children the root has and malloc the Tree point
	for (i = 0; i <= M - N; i++) //initialize each child and start to expend from each child
	{
		root->k[i] = (Tree)malloc(sizeof(struct TreeNode)); //malloc child node
		root->k[i]->parent = root; //initialize the child node
		root->k[i]->p = 0; root->k[i]->q = i;
		root->k[i]->flag = -1;
		root->k[i]->level = 0;
		root->k[i]->sumdis = 0;
		//printf("%d", root->k[i]->parent->p);
		expend(root->k[i], score1, mode); //start to expend the tree
	}
	for (j = 0; j < M / 2; j++)  //to reverse the array B and do the same things again to get another tree and the score1
	{
		c = B[M - j - 1];
		B[M - j - 1] = B[j];
		B[j] = c;
	}
	for (i = 0; i <= M - N; i++)
	{
		root->k[i]->parent = root;
		root->k[i]->p = 0;
		root->k[i]->q = i;
		root->k[i]->flag = -1;
		root->k[i]->level = 0;
		root->k[i]->sumdis = 0;
		//printf("%d", root->k[i]->parent->p);
		expend(root->k[i], score2, mode);
	}

	arrayprint(score1, N, M, 0); //print the score array of score1 (B is in order)
	printf("\n");
	arrayprint(score2, N, M, 1); //print the score array of score2 (B is in reversed order)

	double scoref1, scoref2;
	scoref1 = wayfind(score1, N, M, 1);
	scoref2 = wayfind(score2, N, M, 2);
	if (scoref1 == 0 && scoref2 == 0) //both the two ways can't get a complete node (the COEFFICIENT maybe too small) 
	{
		printf("NO RESULT IN THIS COE!");
	}
	else if (scoref1 > scoref2) //the in order way is better
	{
		printfpoints(score1, N, M, 1); //print the best way 
	}
	else //the reversed order way is better
	{
		printfpoints(score2, N, M, 2); //print the best way 
	}
	return 0;
}