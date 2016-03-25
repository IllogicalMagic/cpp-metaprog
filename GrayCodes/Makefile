CXX?=g++
CC=$(CXX)
CXXSTD?=-std=c++1y
CXXFLAGS?=$(CXXSTD) -Wall -Werror -pedantic-errors -O0

all: Gray_new Gray_old

dotest: all
	./Gray_new
	./Gray_old

Gray_new: Gray_new.o GrayDynamic.o

Gray_new.o: Gray_new.cpp GrayDynamic.hpp utils.h

Gray_old: Gray_old.o GrayDynamic.o

Gray_old.o: Gray_old.cpp GrayDynamic.hpp utils.h

GrayDynamic.o: GrayDynamic.cpp GrayDynamic.hpp

clean:
	rm -f Gray_new Gray_old *.o *~ *.s

