CXX?=g++
CC=$(CXX)
CXXSTD?=c++11
G_BITS?=4
G_VIEW?=DECIMAL
CXXFLAGS?=-Wall -Werror -pedantic-errors -g -O0
CXXFLAGS+=-std=$(CXXSTD) -DG_BITS=$(G_BITS) -DG_VIEW=$(G_VIEW)

all: GrayOld GraySeq

dotest: all
	./GrayOld
	./GraySeq

GrayOld: GrayOld.o GrayDynamic.o

GrayOld.o: GrayOld.cpp GrayDynamic.hpp GrayShared.hpp mStaticAssert.hpp

GrayDynamic.o: GrayDynamic.cpp GrayDynamic.hpp GrayShared.hpp

GraySeq: GraySeq.o GrayDynamic.o

GraySeq.o: GraySeq.cpp GrayDynamic.hpp GrayShared.hpp

clean:
	rm -f GrayOld GraySeq *.o *~ *.s

