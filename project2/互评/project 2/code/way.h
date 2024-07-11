#ifndef _WAY_H_
#define _WAY_H_
//print the two dimensional arrary with X and Y serial number
void arrayprint(double** score, int N, int M, int flag); 

//find the best way with highest votes or grades and return the votes or grades
double wayfind(double **score, int N, int M, int fl);

//print the points which makes the best way
void printfpoints(double **score, int N, int M, int flag);

#endif // !_WAY_H_
