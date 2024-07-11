#include <stdio.h>
#include <time.h>
clock_t start,stop;
double duration;
// the iterative version of algorithm 2.
typedef long long ll;
ll Pow(double x,int N){
    ll s=1;
    while(N>0){
        if(N%2==1){
            s*=x;
        }
        x*=x;//x self-multiplying.
        N=N/2;//N decreases by half
    }
    return s;
}
int main(){
    int N,K=1000,i;
    double s=1;
    
    scanf("%d",&N);
    start = clock();
    for(i=0;i<K;i++)//repeat K times.
        s=Pow(1.0001,N);
    stop = clock();
    duration = ((double)(stop-start))/CLOCKS_PER_SEC;//another version of CLK_TCK.
    printf("%ld\n%e",stop-start,duration);//output.
    return 0;
}


