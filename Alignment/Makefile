CXX?=g++
CC=$(CXX)
CXXSTD=c++14
CXXFLAGS=-Wall -Werror --pedantic-errors -g -O0
CXXFLAGS+=-std=$(CXXSTD)
CXXFLAGS+=$(CXXOPT)

all: Tests

dotest: Tests
	./Tests

Tests: Tests.cpp Align.hpp

clean:
	rm -f *.o *~ Tests
