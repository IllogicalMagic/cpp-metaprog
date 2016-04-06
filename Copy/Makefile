CXX?=g++
CC=$(CXX)
CXXSTD?=c++14
CXXFLAGS?=-Wall -Werror --pedantic-errors -g -O0
CXXFLAGS+=-std=$(CXXSTD)

all: CopyTest

dotest: all
	./CopyTest

CopyTest: CopyTest.o

CopyTest.o: CopyTest.cpp Copy.hpp mTypeTraits.hpp

clean:
	rm -f *.o *~ CopyTest
