CXX?=g++
CC=$(CXX)
CXXSTD?=c++11
CXXFLAGS?=-std=$(CXXSTD) -Wall -Werror -pedantic-errors -O0

all: Gray_old

dotest: all
	./Gray_old

Gray_old: Gray_old.o GrayDynamic.o

Gray_old.o: Gray_old.cpp GrayDynamic.hpp GrayShared.hpp

GrayDynamic.o: GrayDynamic.cpp GrayDynamic.hpp GrayShared.hpp

clean:
	rm -f Gray_old *.o *~ *.s

