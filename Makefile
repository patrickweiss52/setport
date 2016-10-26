all: setport.cpp test.cpp

setport:
	g++ -std=c++11 -o setport setport.cpp

test:
	g++ -std=c++11 -o test test.cpp