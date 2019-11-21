all: main.o curve.o
	g++ main.o curve.o -lopenGL32 -lfreeGLUT -o test
main.o: main.cpp
	g++ main.cpp -c -o main.o -lopenGL32 -lfreeGLUT 
curve.o: curve.cpp
	g++ curve.cpp -lopenGL32 -lfreeGLUT -c -o curve.o
c:
	g++ curve.cpp -o curve.exe -lfreeGLUT -lopenGL32
