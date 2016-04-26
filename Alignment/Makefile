CXX?=g++
CC=$(CXX)
CXXSTD?=c++14
CXXFLAGS=-Wall -Werror --pedantic-errors -g -O0
CXXFLAGS+=-std=$(CXXSTD)
CXXFLAGS+=$(CXXOPT)
CXXNOWARN+=-Wno-unused-variable -Wno-unused-but-set-variable
CXXFLAGS+=$(CXXNOWARN)

Boost%: %.cpp
	$(CXX) $(CXXFLAGS) -DWITH_BOOST $^ -o $@

Boost%: Boost%.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

all: Tests GeneralSortTests BoostTests BoostGetTests

dotest: all
	./Tests
	./GeneralSortTests
	./BoostTests
	./BoostGetTests

Tests: Tests.cpp Align.hpp Print.hpp Sort.hpp

BoostTests: Tests.cpp BoostAlign.hpp Print.hpp BoostSort.hpp

BoostGetTests: BoostGetTests.cpp BoostAlign.hpp Print.hpp \
	BoostSort.hpp

GeneralSortTests: GeneralSortTests.cpp Align.hpp Print.hpp Sort.hpp

Compare: Tests BoostTests
	./Tests > Tests.out
	./BoostTests > BoostTests.out
	diff Tests.out BoostTests.out
	rm Tests.out BoostTests.out

clean:
	rm -f *.o *~ Tests GeneralSortTests BoostTests \
	BoostGetTests
