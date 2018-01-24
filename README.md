# Convex-Hull-API
A flexible API for creating a convex hull for a given points. Return Type is a vector of Points. API supports three algorithms: Graham's Scan, Jarvis March, Kirkpatrick-Seidel.
Steps to use the API:
->include "ConvexHull.h"
  include the header
->ConvexHull C(Vector<Point> arr_of_points, ALGORITHM A)
  The constructor requires two parameters:
    Vector of 'Point' objects. Point is a class to represent x and y coordinates in double format.
    ALGORITHM is an enum with following declaration in the CONVEX_HULL_ALGO namespace.
    enum ALGORITHM { GRAHAMS_SCAN, JARVIS_MARCH, KIRKPATRICK_SEIDEL };
