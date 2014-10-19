all:
	g++ -march=native -Ofast -o ulam ulam.cpp
	g++ -march=native -Ofast -fopenmp -o ompulam ompulam.cpp
