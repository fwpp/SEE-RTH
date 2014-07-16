all:  before
	g++ -o game Threes.o example_main.o

before:
	g++ -c Threes.cpp
	g++ -c example_main.cpp


clean:
	rm Threes.o example_main.o game

test1: x
	g++ -o Test1 main.o Threes.o
x:
	g++ -c -g -Wall -O2 main.cpp

clear:
	rm Test1 main.o

