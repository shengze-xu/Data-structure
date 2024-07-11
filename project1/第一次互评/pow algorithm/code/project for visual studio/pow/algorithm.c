#include"algorithm.h"

//Algorithm1 consider x^n as x multiply itself for n-1 times.
double algorithm1(double x, int n)
{
	double ans = x;                 //record the result of the multiplications
	int i;                          //record the number of the multiplications
	for (i = 1; i < n; i++)         //if the number of multiplications is less than n-1,continue the loop.When the number is equal to n-1,end the loop.
	{
		ans = ans * x;        
	}
	return ans;
}


//Algorithm 2 works in the following way:
//    if n is even and n>1,x^n=(x^(n/2))*(x^(n/2)).Else,x^n=(x^(n/2))*(x^(n/2))*x.
//The following two algorithms is the iterative and recursive version of algorithm 2.

//The iterative version 
double algorithm2_iterative(double x, int n)
{
	double ans = x;                 //record the result of the calculaion
	if (n == 1)                     //if n==1, then x^1==x.
	{
		return ans;
	}
	for (; n > 0;)                  //while n>0, continue the loop, else, end the loop.
	{
		if (n % 2 != 0)             //if n is odd, ans shall be multiplied by x.
		{
			ans = ans * x;
		}
		x = x * x;                  //change x to x*x, and change n to n/2 in the next loop.
		n = n / 2;
	}
	return ans;
}

//The recursive version
double algorithm2_recursive(double x, int n)
{
	if (n == 1)                     //if n==1,the recursion ends.
	{
		return x;
	}
	if (n % 2 == 0)
	{
		return algorithm2_recursive(x*x, n / 2);        //if n is even,call the function again with x replaced by x*x and n replaced by n/2 to do it recursively.
	}
	else
	{
		return algorithm2_recursive(x*x, n / 2)*x;      //if n is odd, a x should be multiplied.
	}
}