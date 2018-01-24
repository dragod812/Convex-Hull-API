# Convex-Hull-API
A flexible API for creating a convex hull for a given points. Return Type is a vector of Points. API supports three algorithms:  Graham's Scan, Jarvis March, Kirkpatrick-Seidel.<br />
Steps to use the API:<br><br>
->include "ConvexHull.h"<br>
  &nbsp;include the header<br><br>
->ConvexHull C(Vector<Point> arr_of_points, ALGORITHM A)<br>
  &nbsp;The constructor requires two parameters:<br>
    &nbsp; &nbsp; Vector of 'Point' objects. Point is a class to represent x and y coordinates in double format.<br>
    &nbsp; &nbsp; ALGORITHM is an enum with following declaration in the CONVEX_HULL_ALGO namespace.<br>
    &nbsp; &nbsp; enum ALGORITHM { GRAHAMS_SCAN, JARVIS_MARCH, KIRKPATRICK_SEIDEL };<br>
