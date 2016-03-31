CXX?=g++
CC=$(CXX)
CXXSTD?=c++11
B_SIZE?=3
CXXFLAGS?=-Wall -Werror -pedantic-errors -g -O2
CXXFLAGS+=-std=$(CXXSTD) -DB_SIZE=$(B_SIZE)

all: BernoulliOld

dotest: all
	./BernoulliOld

BernoulliOld: BernoulliOld.o DynamicRatio.o BernoulliDynamic.o

BernoulliOld.o: BernoulliOld.cpp DynamicRatio.hpp BernoulliDynamic.hpp

DynamicRatio.o: DynamicRatio.cpp DynamicRatio.hpp

BernoulliDynamic.o: BernoulliDynamic.cpp BernoulliDynamic.hpp

clean:
	rm -f BernoulliOld *.o *~ *.s

