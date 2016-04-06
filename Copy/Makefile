CXX?=g++
CC=$(CXX)
CXXSTD?=c++14
CXXFLAGS?=-Wall -Werror --pedantic-errors -g -O0
CXXFLAGS+=-std=$(CXXSTD)

all: TypeTests CopyTest

dotest: all
	./TypeTests
	./CopyTest

CopyTest: CopyTest.o

CopyTest.o: CopyTest.cpp Copy.hpp mTypeTraits.hpp

TypeTests: TypeTests.o

TypeTests.o: TypeTests.cpp mTypeTraits.hpp

clean:
	rm -f *.o *~ TypeTests CopyTest
