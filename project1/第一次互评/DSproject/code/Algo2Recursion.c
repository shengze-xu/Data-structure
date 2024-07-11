#include <stdio.h>
#include <time.h>
clock_t start,stop;
double duration;
//the recursive version of algorithm 2.
double Pow(double x, int N)
{
    if(N==0)
        return 1;//ending part for recursion if N is even finally.
    if (N==1)
        return x;//ending part for recursion if N is odd finally.
    if (N%2==0)
        return Pow(x*x,N/2);//if N is even
    else
        return Pow(x*x, N/2)*x;//if N is odd
    }


int main(){
    int N,i,s;
    int K=10000;//repeat 10000 times
    scanf("%d",&N);
    start = clock();
    for (i=0; i<K; i++)
        s=Pow(1.0001,N);//function operating.
    stop = clock();
    duration = ((double)(stop-start))/CLOCKS_PER_SEC;//another version of CLK_TCK.
    printf("%ld\n%f\n",stop-start,duration);
    return 0;
}


