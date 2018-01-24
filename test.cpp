#include "include/ConvexHull.h"
#include <iostream>
using namespace std;

int main(){
	int N;
	cin >> N;
	vector< Point > Points;
	for(int i = 0;i<N;i++){
		double x, y;
		cin >> x >> y;
		Points.push_back(Point(x, y));
	}
	ConvexHull C(Points, CONVEX_HULL_ALGO::GRAHAMS_SCAN);
	for(int i = 0;i<C.convexHull.size();i++){
		cout << C.convexHull[i].x << " ," << C.convexHull[i].y << endl;
	}
	return 0;
}
