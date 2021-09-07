all: main.o curve.o
	g++ main.o curve.o `pkg-config --cflags --libs glut`
main.o: main.cpp
	g++ main.cpp -c -o main.o `pkg-config --cflags --libs glut`
curve.o: curve.cpp
	g++ curve.cpp -lopenGL32 `pkg-config --cflags --libs glut`
c:
	g++ curve.cpp -o curve.exe `pkg-config --cflags --libs glut`
test: all
	test.exe
