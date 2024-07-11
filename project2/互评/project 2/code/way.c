#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//print the two dimensional arrary with X and Y serial number
void arrayprint(double** score, int N, int M, int flag)
{
	int i, j;
	printf("       ");
	for (i = 1; i <= M; i++) //print the X serial number
	{
		printf("%5d ", i);
	}
	printf("\n");

	if (flag == 0) // flag is to judge whether the B is in order or not , flag = 0 -- inorder
	{
		for (i = 0; i < N; i++)
		{
			printf("%5d |", i + 1); //print the Y serial number
			for (j = 0; j < M; j++)
			{
				if (score[i][j] != 0)
					printf("%5.1lf ", score[i][j]); //print the score the pair gets
				else
					printf("XXXXXX"); //the impossible path
			}
			printf("\n");
		}
	}

	if (flag == 1) //flag = 1 B--reversed order
	{
		for (i = N - 1; i >= 0; i--)
		{
			printf("%5d |", N - i);
			for (j = 0; j < M; j++)
			{
				if (score[i][j] != 0)
					printf("%5.1lf ", score[i][j]);
				else
					printf("XXXXXX");
			}
			printf("\n");
		}
	}
}

//find the best way with highest votes or grades and return the votes or grades
double wayfind(double **score, int N, int M, int fl)
{
	double scoref = 0;// initialize the score of the way
	int i, j, k, flag = 0;
	double max = 0; //the max scores untill now

	
	for (j = 0; j < M; j++)
	{
		if (score[N - 1][j] != 0)
			flag = 1;
	}
	if (flag == 0) return 0; // If there is no possible path, return 0
	/*To find the best way, 
	add the largest element on the left side of the element in the next line to the element, 
	and repeat it repeatedly to get the best path and the number of votes or scores.*/
	for (i = N - 2; i >= 0; i--)
	{
		for (j = 0; j < M; j++)
		{
			if (score[i][j] != 0)
			{
				for (k = j + 1; k < M; k++)
				{
					if (score[i + 1][k] > max)
					{
						max = score[i + 1][k];
					}
				}
				score[i][j] += max;
			}
		}
	}
	scoref = score[0][0];//the max scores will finally converges to the first point.
	return scoref;
}
void printfpoints(double **score, int N, int M, int flag)
{
	int i, j;
	int maxx, maxy, lasty = -1;
	double max = 0;

	for (i = 0; i < N; i++)
	{
		max = score[i][0]; // initialize the pair
		maxx = i + 1;
		maxy = 1;
		for (j = 0; j < M; j++)
		{
			if (score[i][j] > max + 1) //To find the pair with the lagest scores
			{
				max = score[i][j];
				maxy = j + 1;
			}
		}
		if (maxy <= lasty)
		{
			maxy = lasty+1;
		}
		if(flag == 1) // flag is to judge whether the B is in order or not , flag = 1 -- inorder
			printf("(%d, %d)\n", maxx, maxy);
		if(flag == 2) // B -- conversed order
			printf("(%d, %d)\n", maxx, M - maxy + 1);
		lasty = maxy;
	}
}
