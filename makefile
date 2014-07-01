EXECUTABLE := timeTest

CFLAGS := -Wall -O3
CXXFLAGS := $(CFLAGS)
CC := g++

SOURCE := $(wildcard *.c) $(wildcard *.cc) $(wildcard *.cpp) $(wildcard *.cxx)
OBJS := $(patsubst %.c,%.o,$(patsubst %.cc,%.o,$(patsubst %.cpp,%.o,$(patsubst %.cxx,%.o,$(SOURCE)))))

.PHONY : all clean

all:
	$(CC) -o $(EXECUTABLE) $(SOURCE)

clean :
	rm -f *.o $(EXECUTABLE)

$(EXECUTABLE) : $(OBJS)
	$(CC) -o $(EXECUTABLE) $(OBJS)
