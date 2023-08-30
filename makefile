Snake:main.o
	mingw32-g++  -o  Snake.exe main.o -lgomp -lpthread
main.o:main.cpp
	mingw32-g++  -c -fopenmp main.cpp
