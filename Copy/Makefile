CXX?=g++
CC=$(CXX)
CXXSTD?=c++14
CXXFLAGS?=-Wall -Werror --pedantic-errors -g -O0
CXXFLAGS+=-std=$(CXXSTD)

all: TypeTests

dotest: all
	./TypeTests

TypeTests: TypeTests.o

TypeTests.o: TypeTests.cpp mTypeTraits.hpp

clean:
	rm -f *.o *~ TypeTests
