all:  object
	g++ -o Shift_LEFT_test Grid_shift.o Threes.o
object: Threes.o
	g++ -c Grid_shift.cpp
Threes.o:
	g++ -c ../Threes.cpp
clean:
	rm Grid_shift.o Threes.o Shift_LEFT_test
