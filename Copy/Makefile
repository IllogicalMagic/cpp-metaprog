CXX?=g++
CC=$(CXX)
CXXSTD?=c++14
CXXFLAGS?=-Wall -Werror --pedantic-errors -g -O0
CXXFLAGS+=-std=$(CXXSTD)

all: TypeTests Copy

dotest: all
	./TypeTests
	./Copy

Copy: Copy.o

Copy.o: Copy.cpp mTypeTraits.hpp

TypeTests: TypeTests.o

TypeTests.o: TypeTests.cpp mTypeTraits.hpp

clean:
	rm -f *.o *~ TypeTests Copy
