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
	
test2: y
        g++ -o Test2 main_test2.o Threes_test.o
y:
        g++ -o main_test2.o -c main_test2.cpp
        g++ -o Threes_test.o -c Threes_test.cpp

clear:
	rm Test1 main.o

