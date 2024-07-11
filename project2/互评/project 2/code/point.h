#ifndef _POINT_H_
#define _POINT_H_
	
void REAMP(point* X, int N); //scan the input of a point list and record it in point *X 

double distance(point A, point B); // RETURN the distance between point A and B

double angle(point A, point B, point C); //RETURN the Angle angle BAC of three points A, B, C

#endif // !_POINT_H_
