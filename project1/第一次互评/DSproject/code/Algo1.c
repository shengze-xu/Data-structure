#include <stdio.h>
#include <time.h>

clock_t start,stop;
double duration;
 
int main(){
    int N,i,j;
    int K=100;//repeat
    double s=1;//variation
    scanf("%d",&N);//input N.
    start = clock();
    for(j=0;j<K;j++)//control the repeating times
        for(i=0;i<N;i++)
            s=s*1.0001;//doing exponentiation for N-1 times.
    stop = clock();//time record for the function
    duration = ((double)(stop-start))/CLOCKS_PER_SEC;//another version of CLK_TCK
    printf("%ld\n%f",stop-start,duration);
    return 0;

}



