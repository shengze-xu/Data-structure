#define _CRT_SECURE_NO_WARNINGS                         //only used in visual studio to avoid warnings of using "scanf" function.
#include<stdio.h>
#include<time.h>
#include"algorithm.h"

clock_t start, stop;                                    //record the starting ticks and stopping ticks of the algorithm
double duration,                                        //record the running time of the algorithm
	   total_time,                                      //record the total running time of the algorithm 
	   result;                                          //record the result of the calculation
int k,                                                  //record the iteration times of algorithm
    ticks;                                              //record total ticks when the algorithm works

//print the result to the window
void output()                
{
	ticks = (stop - start);                                //calculate the ticks by start tick minus end tick
	total_time = ((double)(stop - start)) / CLK_TCK;       //divide ticks with CLK_TCK to get total time
	duration = (((double)(stop - start)) / k) / CLK_TCK;   //divide total time with k to get duration
	printf("Compute completed.\n\n");
	printf("The result is %lf\n", result);
	printf("The ticks are %d.\n", ticks);
	printf("The total time is %lf\n", total_time);
	printf("The duration is %lf\n", duration);
}

int main()
{
	double x;
	int n;
	int algo_selector;                                      //indicates the algorithm selected
	int i;                                                  //flag for the loop


	printf("Please input double x , positive interger n and iteration times (positive intergers)k.\n");
	scanf("%lf %d %d", &x, &n, &k);                         //taking in the value of x,n,k


	if (n <= 0||k<=0)                                             //check if the input is valid
	{
		printf("Range Error,program ended.");
		return 1;
	}
	
	

	printf("Please enter a number to choose an algorithm\n");     //choose the algorithm
	printf("1. algorithm1    2.algorithm2_iterative    3.algorithm2_recursive\n");
	scanf_s("%d", &algo_selector);

	if (algo_selector <= 0 || algo_selector > 3)                   //check if the selection is valid
	{
		printf("Invalid selection, program ended!\n");
	}
	printf("Computing,please wait...\n");

		
	switch (algo_selector)                                         //use different algorithms to calculate according to the selector
	{
	case 1:
		start = clock();                                          //start timing
		for (i = 0; i < k; i++)                                   //do for k times
		{
			result = algorithm1(x, n);
		}
		stop = clock();                                           //end timing
		output();                                                 //print the result
		break;

	case 2:
		start = clock();
		for (i = 0; i < k; i++)
		{
			result = algorithm2_iterative(x, n);
		}
		stop = clock();
		output();
		break;
	case 3:
		start = clock();
		for (i = 0; i < k; i++)
		{
			result = algorithm2_recursive(x, n);
		}
		stop = clock();
		output();
		break;
	default:
		break;
	}
	

}