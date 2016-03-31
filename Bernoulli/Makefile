CXX?=g++
CC=$(CXX)
CXXSTD?=c++11
B_SIZE?=3
CXXFLAGS?=-Wall -Werror -pedantic-errors -g -O0
CXXFLAGS+=-std=$(CXXSTD) -DB_SIZE=$(B_SIZE)

all: BernoulliOld

dotest: all
	./BernoulliOld

BernoulliOld: BernoulliOld.o DynamicRatio.o

BernoulliOld.o: BernoulliOld.cpp DynamicRatio.hpp

DynamicRatio.o: DynamicRatio.cpp DynamicRatio.hpp

clean:
	rm -f BernoulliOld *.o *~ *.s

