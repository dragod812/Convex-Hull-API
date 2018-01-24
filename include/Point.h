#ifndef POINT_H
#define POINT_H

class Point{
public:
	double x, y;
	Point(){
		x = 0; y = 0;
	}
	Point(double x, double y){
		this->x = x;
		this->y = y;
	}
};
#endif
