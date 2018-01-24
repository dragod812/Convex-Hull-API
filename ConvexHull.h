#ifndef SHADER_H
#define SHADER_H
#include<vector>
#include "Point.h"
#include<utility>
#include<algorithm>
using namespace std;

namespace CONVEX_HULL_ALGO{
	enum ALGORITHM { GRAHAMS_SCAN, JARVIS_MARCH, KIRKPATRICK_SEIDEL };
}
class ConvexHull{
public:
	vector<Point> convexHull;
	vector<Point> points;
	ConvexHull(vector<Point> points, CONVEX_HULL_ALGO::ALGORITHM A){
		this->points = points;
		switch(A){
			case CONVEX_HULL_ALGO::GRAHAMS_SCAN:
				GrahamsScan();
				break;

			case CONVEX_HULL_ALGO::JARVIS_MARCH:
				JarvisMarch();
				break;
			case CONVEX_HULL_ALGO::KIRKPATRICK_SEIDEL:
				KirkpatrickSeidel();
				break;
		}
	}
	~ConvexHull(){

	}
private:
	static Point lowestPoint;
	vector<Point> sortedPoints;
	void LowestIndex(){
		int minIndx = 0;
		for(int i = 1;i<points.size();i++){
			if(points[i].y < points[minIndx].y){
				minIndx = i;
			}
			else if(points[i].y == points[minIndx].y){
				minIndx = (points[i].x < points[minIndx].x)?(i):(minIndx);
			}
		}
		// lowest point is swapped with the 0th index
		lowestPoint = points[minIndx];
		points[minIndx] = points[0];
		points[0] = lowestPoint;
	}
	double crossProduct(pair<double, double> vl, pair<double, double> vr){
		return (vl.first*vr.second - vl.second*vr.first );
	}
	double magnitude2(pair<double, double> v){
		return v.first*v.first + v.second*v.second;
	}
	pair<double, double> makeVector(Point p1, Point p2){
		return make_pair(p2.x - p1.x, p2.y - p1.y);
	}
	static bool comparePoints(const Point &l, const Point &r) {
		pair<double, double> vl, vr;
		vl = make_pair(l.x - lowestPoint.x, l.y - lowestPoint.y);
		vr = make_pair(r.x - lowestPoint.x, r.y - lowestPoint.y);
		return ((vl.first*vr.second - vl.second*vr.first) > 0);
	}
	void removeDegeneracies(){
		for(int i = 1;i<sortedPoints.size()-1;i++){
			pair<double, double> v1, v2;
			v1 = make_pair(sortedPoints[i].x - lowestPoint.x, sortedPoints[i].y - lowestPoint.y);
			v2 = make_pair(sortedPoints[i+1].x - lowestPoint.x, sortedPoints[i+1].y - lowestPoint.y);
			if(crossProduct(v1, v2) == 0){
				if(magnitude2(v1) < magnitude2(v2)){
					sortedPoints.erase(sortedPoints.begin() + i);
				}
				else{
					sortedPoints.erase(sortedPoints.begin() + i + 1);
				}
			}
		}
	}
	void GrahamsScan(){
		LowestIndex();
		sortedPoints = points;
		sort(sortedPoints.begin()+1, sortedPoints.end(), comparePoints);
		//removeDegeneracies();
		convexHull.push_back(sortedPoints[0]);
		convexHull.push_back(sortedPoints[1]);
		convexHull.push_back(sortedPoints[2]);
		for(int i = 3;i<sortedPoints.size();i++){
			Point p2 = convexHull.back();
			convexHull.pop_back();
			Point p1 = convexHull.back();
			Point p3 = sortedPoints[i];
			pair<double, double> v2 = makeVector(p1, p2);
			pair<double, double> v3 = makeVector(p2, p3);
			double cp = crossProduct(v2, v3);
			if(cp >= 0){
				convexHull.push_back(p2);
			}
			convexHull.push_back(p3);
		}
	}
	void JarvisMarch(){

	}
	void KirkpatrickSeidel(){

	}
};
#endif
