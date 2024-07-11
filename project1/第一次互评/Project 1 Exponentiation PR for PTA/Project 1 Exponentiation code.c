#include<stdio.h>
#include<time.h>

clock_t start,stop;
//�����ʱ�� 
double duration,ticks,total;
//duration-�㷨������������ʱ��; ticks-�㷨K�����м�ʱ���������� total-�㷨K������������ʱ�� 
double X,result;
//X-����; result-���ݵĽ�� 
long int N;
//N-ָ�� 

int IsEven(long int N);
/*
�����ж������Ƿ�Ϊż����
����long int N����NΪż�����򷵻� 1�����򷵻�0 
*/
double Pow1(double X, long int N);
/*
Algorithm 1�ڳ����еĺ���ʵ�֡�
����double X ��long int N,�ñ�����˵ķ�����ò�����X^N 
��N=0���򷵻�1�������㷨���Ƚ�X��ֵ������double out����ͨ��һ��forѭ������out��X���N-1�Σ�����out���Ӷ��ó�X^N;
*/ 
double Pow2I(double X, long int N);
/*
Algorithm 2 (iterative version) �ڳ����еĺ���ʵ�� 
���� double X �� long int N�� ���� X^N 
*/ 
double Pow2R(double X, long int N);
/*
Algorithm 2 (iterative version) �ڳ����еĺ���ʵ��
���� double X �� long int N ,���� X^N 
*/

int main()
{
	int type;
	//�ж�ѡ���㷨���͵ı�Ǳ���,1,2,3����ͬ�㷨 
	//1-Algorithm 1; 2-Algorithm 2 (iterative version); 3-Algorithm 2 (recursive version) 
	double i;
	long int K=1000000;
	//�㷨�ظ��Ĵ��� 
	printf("����һ������X��N\n");
	scanf("%lf %ld",&X,&N); 
	//printf("%lf %ld\n",X,N);
	printf("�����뽫ʹ�õ��㷨���:\n1-Algorithm1\n2-Algorithm2(iterative)\n3-Algorithm2(recursive)\n");
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
	//duration  ����̫С��������ʾ��ת���ں������ݴ���չ�� 
	printf("���Ϊ%lf\n",result);
	printf("����%ld�δ����Ϊ%lf   ��ʱΪ %lfsec\n",K,ticks,total);
	//printf("����������ʱΪ%lfsec\n",duration);
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
��������POW2I
��N=0���򷵻�1��
����
��ѭ��ʵ�֣�double out��ʼֵΪ1�����ڴ����ۻ��Ľ����
whileѭ����Ϊʮ����ת��Ϊ������"��2ȡ��"�����Ĵ���ʵ�֡�
Nÿ������2��Xÿ���Գˣ��൱��X^2k��kÿ����һ����
��������Ϊ1ʱ����ΪN�Ķ��������ϸ�λΪ1����X^2k����out��
���������out�� 
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
��������POW2R
X����log2(N)����log2(N)+1�Σ�NΪ������ƽ����õ�X^N���������õ�
��׵㣬��N=1ʱ��������X����ʣ������£���"��"δ����������ֵ��Ϊ
POW2R(X*X, N/2)���൱�ڶ�X����һ��ƽ���Լ���N����2����������Ϊ��
N=1ʱ�ͻ������������N��ż���Ĳ�ȷ����ʹ�� if�ṹ��IsEven��������
������N��Ϊ�����ѡ��POW2R(X*X, N/2)*X��
*/
