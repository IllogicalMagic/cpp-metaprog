CXX?=g++
CC=$(CXX)
CXXSTD=c++14
CXXFLAGS=-Wall -Werror --pedantic-errors -g -O0
CXXFLAGS+=-std=$(CXXSTD)
CXXFLAGS+=$(CXXOPT)

all: Tests GeneralSortTests

dotest: Tests
	./Tests
	./GeneralSortTests

Tests: Tests.cpp Align.hpp Print.hpp

GeneralSortTests: GeneralSortTests.cpp Align.hpp Print.hpp

clean:
	rm -f *.o *~ Tests GeneralSortTests
