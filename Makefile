all: main matrix
	g++ -o Wagner WagnerISD.o matrix.o

main: WagnerISD.cpp
	g++ -c WagnerISD.cpp

matrix: matrix.cpp
	g++ -c matrix.cpp

clear:
	rm *.o

