all: main.cpp main.o
	g++ -c main.cpp
	g++ main.o -Wall -Werror
	./main
