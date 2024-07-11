#include <stdio.h>
#include <time.h>

double Directmultiply(double x,int n);//function of Algorithm 1
double Iterative(double x,int n);//function of Algorithm 2 in iterative form
double Recursive(double x,int n);//function of Algorithm 2 in recursive form

int main(){
	clock_t start,stop;
	double total,duration;
	int i,j,K=1;//i and j are the variables used in the loop, and K is the iteration number 
	double x=1.0001,result;//result is the return value of the function
	int n[8]={1000,5000,10000,20000,40000,60000,80000,100000};//store the index N into an array for easy traversal
//  Check the correctness of the three functions
//	double a=Directmultiply(2.3,3);
//	double b=Recursive(3.1,2);
//	double c=Iterative(2.5,2);
//	printf("%f %f %f",a,b,c);
	printf("Algorithm 1\n"); 
	for(i=0;i<8;i++){
		K=1;//set the initial value of K to 1 
		do{//enter the loop,record the time required for K calls
			K*=10;
			start=clock();//record start time
			for(j=0;j<K;j++){
				result=Directmultiply(x,n[i]);//call function 
			}
			stop=clock();//record end time
		}while(stop-start<10);//end the loop when tick is greater than 10
		total=((double)(stop-start))/CLK_TCK;//calculate the total time
		duration=total/K;//calculate single time
		printf("N=%d,K=%d,Ticks=%d,total time=%.1e,duration=%.1e\n",n[i],K,stop-start,total,duration);
	}
	printf("\n");
	printf("Algorithm 2-iterative version\n"); 
	for(i=0;i<8;i++){
		K=1;//set the initial value of K to 1 
		do{//enter the loop,record the time required for K calls
			K*=10;
			start=clock();//record start time
			for(j=0;j<K;j++){
				result=Iterative(x,n[i]);//call function 			
			}
			stop=clock();//record end time
		}while(stop-start<10);//end the loop when tick is greater than 10
		total=((double)(stop-start))/CLK_TCK;//calculate the total time
		duration=total/K;//calculate single time
		printf("N=%d,K=%d,Ticks=%d,total time=%.1e,duration=%.1e\n",n[i],K,stop-start,total,duration);
	}
	printf("\n");
	printf("Algorithm 2-recursive version\n"); 
	for(i=0;i<8;i++){
		K=1;//set the initial value of K to 1 
		do{//enter the loop,record the time required for K calls
			K*=10;
			start=clock();//record start time
			for(j=0;j<K;j++){
				result=Recursive(x,n[i]);//call function 			
			}
			stop=clock();//record end time
		}while(stop-start<10);//end the loop when tick is greater than 10
		total=((double)(stop-start))/CLK_TCK;//calculate the total time
		duration=total/K;//calculate single time
		printf("N=%d,K=%d,Ticks=%d,total time=%.1e,duration=%.1e\n",n[i],K,stop-start,total,duration);
	}
} 

double Directmultiply(double x,int n){
	int i;
	double result=1;//define variables for output 
	if(n==0){
		return 1;//if the index is 0, return 1 directly
	}
	else{
		for(i=0;i<n;i++){//enter the loop
			result*=x;//multiply x each time
		}
	}
	return result;
}

double Iterative(double x,int n){
	double result=1;//define variables for output 
	if(n==0){
		return 1;//if the index is 0, return 1 directly
	}
	while(n>0){//when n>0, continue the while loop
		if(n%2==1){//if n is odd, multiply result by x
			result*=x;
		}
		x*=x;//square x 
		n/=2;//divide n by 2, automatically round
	}
	return result;//return calculation result
}

double Recursive(double x,int n){
	if(n==0){
		return 1;//if the index is 0, return 1 directly
	}
	if(n==1){
		return x;//if the index is 0, return x directly
	}
	//if n is not trivial, divide the problem in half and call the recursive function
	if(n%2==0){
		return Recursive(x*x,n/2);//if n is an even number, split x^n into x^(n/2)*x^(n/2)
	}
	else{
		return Recursive(x*x,(n-1)/2)*x;//if n is odd, split in the same way
	}
}


