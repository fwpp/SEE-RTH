all:  before
	g++ -o game Threes.o example_main.o

before:
	g++ -c Threes.cpp
	g++ -c example_main.cpp


clean:
	rm Threes.o example_main.o game



