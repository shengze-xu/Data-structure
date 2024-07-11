#include<stdio.h>
#include<time.h>

clock_t start,stop;
//定义计时器 
double duration,ticks,total;
//duration-算法单次运行所用时长; ticks-算法K次运行计时器打点次数； total-算法K次运行所用总时长 
double X,result;
//X-底数; result-求幂的结果 
long int N;
//N-指数 

int IsEven(long int N);
/*
用于判断输入是否为偶数。
输入long int N，若N为偶数，则返回 1，否则返回0 
*/
double Pow1(double X, long int N);
/*
Algorithm 1在程序中的函数实现。
输入double X 与long int N,用遍历相乘的方法求得并返回X^N 
若N=0，则返回1，否则算法首先将X赋值给变量double out，再通过一个for循环，将out与X相乘N-1次，返回out，从而得出X^N;
*/ 
double Pow2I(double X, long int N);
/*
Algorithm 2 (iterative version) 在程序中的函数实现 
输入 double X 与 long int N， 返回 X^N 
*/ 
double Pow2R(double X, long int N);
/*
Algorithm 2 (iterative version) 在程序中的函数实现
输入 double X 与 long int N ,返回 X^N 
*/

int main()
{
	int type;
	//判断选用算法类型的标记变量,1,2,3代表不同算法 
	//1-Algorithm 1; 2-Algorithm 2 (iterative version); 3-Algorithm 2 (recursive version) 
	double i;
	long int K=1000000;
	//算法重复的次数 
	printf("请间隔一空输入X和N\n");
	scanf("%lf %ld",&X,&N); 
	//printf("%lf %ld\n",X,N);
	printf("请输入将使用的算法编号:\n1-Algorithm1\n2-Algorithm2(iterative)\n3-Algorithm2(recursive)\n");
	scanf("%d",&type);
	start=clock();
	if(type==1){
		for(i=1;i<=K;i++) result=Pow1(X,N);
	}
	else if(type==2){
		for(i=1;i<=K;i++) result=Pow2I(X,N);
	}
	else if(type==3){
		for(i=1;i<=K;i++) result=Pow2R(X,N);
	}
	stop=clock();
	ticks=((double)(stop-start));
	total=((double)(stop-start))/CLK_TCK;
	//duration=((double)(stop-start))/(CLK_TCK*K);
	//duration  由于太小，不予显示，转而在后期数据处理展现 
	printf("结果为%lf\n",result);
	printf("运行%ld次打点数为%lf   用时为 %lfsec\n",K,ticks,total);
	//printf("单次运行用时为%lfsec\n",duration);
	system("pause"); 
	return 0;
}

int IsEven(long int N){
	if(N%2==0) return 1;
	return 0; 
}

double Pow1(double X, long int N){
	if(N==0) return 1;
	long int i;
	double out=X;
	for(i=1;i<N;i++) out=out*X;
	return out;
}

double Pow2I(double X, long int N){
	if(N==0) return 1; 
	double out=1;
	while(N>0){
		if(!IsEven(N)) out*=X;
		X*=X;N/=2;
	}
	return out;
}
/*
函数名：POW2I
若N=0，则返回1。
否则
用循环实现：double out初始值为1，用于储存累积的结果。
while循环即为十进制转换为二进制"除2取余"方法的代码实现。
N每步整除2，X每步自乘（相当于X^2k，k每步加一），
当有余数为1时，即为N的二进制码上该位为1，将X^2k乘入out。
最后函数返回out。 
*/ 

double Pow2R(double X, long int N){
	if(N==0)
	return 1;
	if(N==1)
	return X;
	if(IsEven(N)){
	return Pow2R(X*X,N/2);
	}
	else
	{
	return Pow2R(X*X,N/2)*X;
}
}
/*
函数名：POW2R
X进行log2(N)或者log2(N)+1次（N为奇数）平方后得到X^N。首先设置递
归底点，当N=1时函数返回X。在剩余情况下（即"递"未结束）返回值改为
POW2R(X*X, N/2)，相当于对X进行一次平方以及将N整除2来计数（因为当
N=1时就会结束）。由于N奇偶数的不确定，使用 if结构和IsEven函数来针
对输入N的为奇与否选择POW2R(X*X, N/2)*X。
*/
