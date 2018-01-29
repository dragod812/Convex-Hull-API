#ifndef CONVEX_HULL_H
#define CONVEX_HULL_H
#include<vector>
#include "Point.h"
#include<iostream>
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
 	Point lowestPoint;
	vector<Point> sortedPoints;
	void LowestIndex(){
		int minIndx = 0;
		for(size_t i = 0;i<points.size();i++){
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
	//form a vector from the given index point to all the points and store it in sorted
	void vectorise(int indx){
		for(size_t i = 0;i<sortedPoints.size();i++){
			if(i != indx){
				sortedPoints[i] = makeVector(sortedPoints[indx], sortedPoints[i]);
			}
		}
	}
	Point makeVector(Point p1, Point p2){
		Point p3(p2.x - p1.x, p2.y - p1.y);
		return p3;
	}
	//get the points back from the vectors given the reference index
	void unvectorise(int indx){
		for(size_t i = 0;i<sortedPoints.size();i++){
			if(i != indx){
				sortedPoints[i].x = sortedPoints[i].x + sortedPoints[indx].x;
				sortedPoints[i].y = sortedPoints[i].y + sortedPoints[indx].y;
			}
		}
	}
	double crossProduct(Point l, Point r){
		return (l.x*r.y - r.x*l.y);
	}
	double magnitude2(Point l){
		return l.x*l.x + l.y*l.y;
	}
	static bool comparePoints(const Point &l, const Point &r) {
		return ((l.x*r.y - r.x*l.y) > 0);
	}
    static bool basisX(const Point &l, const Point &r) {
        return (l.x < r.x);
    }
    static bool basisY(const Point &l, const Point &r) {
        return (l.y < r.y);
    }
	void removeDegeneracies(){
		for(size_t i = 1;i<sortedPoints.size()-1;i++){
			if(crossProduct(sortedPoints[i], sortedPoints[i+1]) == 0){
				if(magnitude2(sortedPoints[i]) < magnitude2(sortedPoints[i+1])){
					sortedPoints.erase(sortedPoints.begin() + i);
				}
				else{
					sortedPoints.erase(sortedPoints.begin() + i + 1);
				}
				i--;
			}
		}
	}
    int medianX(){
        sortedPoints = points;
        sort(sortedPoints.begin(), sortedPoints.end(), basisX);
        int indx = sortedPoints.size() / 2;
        if(sortedPoints.size()%2 == 0){
            return (double)(sortedPoints[indx].x + sortedPoints[indx-1].x)/2;
        }
        return sortedPoints[indx].x;
    }
	void GrahamsScan(){
		LowestIndex();
		sortedPoints = points;
        //for(int i = 0;i<sortedPoints.size();i++){
	    //   	cout << sortedPoints[i].x << " " << sortedPoints[i].y << endl ;
	    // }
        // cout << endl;


		//cout << sortedPoints[0].x << " " << sortedPoints[0].y << endl;
		vectorise(0);
		sort(sortedPoints.begin()+1, sortedPoints.end(), comparePoints);
		removeDegeneracies();
		unvectorise(0);
		convexHull.push_back(sortedPoints[0]);
		convexHull.push_back(sortedPoints[1]);
        convexHull.push_back(sortedPoints[2]);
		for(size_t i = 3;i<sortedPoints.size();i++){
			Point p2 = convexHull.back();
			convexHull.pop_back();
			Point p1 = convexHull.back();
			Point p3 = sortedPoints[i];
			Point v2 = makeVector(p1, p2);
			Point v3 = makeVector(p2, p3);
			if(crossProduct(v2,v3) >= 0){

				convexHull.push_back(p2);
			    convexHull.push_back(p3);

			}
            else
                i--;
		}

		 for(int i = 0;i<convexHull.size();i++){
		   	cout << convexHull[i].x << " " << convexHull[i].y << endl ;
		 }
	}
    Point leftmostPoint;
	//Point leftmostPoint; //Contains the leftmost point

	void leftmostIndx(){  // Function to find the leftmost point.
		int leftmostIndex=0;
		for(size_t i=0;i<points.size();i++){
			if(points[i].x<points[leftmostIndex].x){
				leftmostIndex=i;
			}
		}
		leftmostPoint=points[leftmostIndex];
	}

	void JarvisMarch(){
		leftmostIndx();
		Point pointOnHull=leftmostPoint;
		int i=0;
		Point endpoint;
		while(1){
			convexHull.push_back(pointOnHull);
			endpoint=points[0];
			for(size_t j=1;j<points.size();j++){
				Point candidateEdge=makeVector(pointOnHull,endpoint);
				Point temp=makeVector(pointOnHull,points[j]);
				if((crossProduct(candidateEdge,temp)<0)||(pointOnHull.x==endpoint.x&&pointOnHull.y==endpoint.y)){
					endpoint=points[j];
				}
				else if(crossProduct(candidateEdge,temp)==0){
					if(magnitude2(candidateEdge)>magnitude2(temp)){
						continue;
					}
					else{
						endpoint=points[j];
					}
				}
				if(pointOnHull.x==points[j].x&&pointOnHull.y==points[j].y){
					continue;
				}
			}
			pointOnHull=endpoint;
			if(endpoint.x==convexHull[0].x&&endpoint.y==convexHull[0].y){
				break;
			}
		}
		//while(endpoint.x!=convexHull[0].x&&endpoint.y!=convexHull[0].y);
	}
	void KirkpatrickSeidel(){

	}
};
#endif
