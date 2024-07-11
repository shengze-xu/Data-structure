#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "main.h"
#include "point.h"

void REAMP(point* X, int N) //get the input of a point list
{
	int i;
	double x, y;
	for (i = 0; i < N; i++)
	{
		scanf("\n%lf %lf", &x, &y); //scan the list
		X[i].x = x; X[i].y = y; //record the list to the points array
	}
}

double distance(point A, point B) // calculate the distance between point A and B
{
	double dis;
	dis = sqrt(pow(A.x - B.x, 2) + pow(A.y - B.y, 2));
	return dis;
}

double angle(point A, point B, point C) //The Angle angle BAC of three points A, B, C
{
	double ab, bc, ca;
	double theta;
	ab = distance(A, B);
	bc = distance(B, C);
	ca = distance(C, A);
	theta = (ab*ab + ca * ca - bc * bc) / (2 * ab*ca); //Law of cosines to calculate the angle
	return theta;
}

