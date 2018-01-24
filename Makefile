LIBS = -lglfw -lGL -ldl -lX11 -lpthread -lXrandr -std=c++11 -lGLU
CFLAGS = -Wall -Iinclude
GLADH = include/glad.h
GLADC = include/glad.c
GLAD = glad.o $(GLADH)
shader = include/shader.h
convexhull = include/ConvexHull.h
point = include/Point.h
main: main.cpp $(convexhull) $(point) $(GLAD) $(shader)
	g++ main.cpp $(GLAD) $(LIBS) $(CFLAGS)
glad.o: $(GLADH)
	g++ -c $(GLADC)
ConvexHull: ConvexHull.cpp Point.h
	g++ ConvexHull.cpp
