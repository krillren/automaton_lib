GTEST_ROOT = ../googletest/googletest
CXXFLAGS_GTEST = -Wall -Wextra -pedantic -g -c -O2 -std=c++17 -I$(GTEST_ROOT)/include -I$(GTEST_ROOT)
CXXFLAGS_AUTO = -Wall -Wextra -pedantic -g -c -O0 -std=c++17 -I$(GTEST_ROOT)/include -I$(GTEST_ROOT)
LDLIBS = -lpthread

CXX = g++
GCOVR = gcovr     #<-- change this to something like "GCOVR = home/AD/mguille/.local/bin/gcovr" if you are on the college computers

RENDU = --html=coverage/coverage.html --html-details
NOT_BRANCHE = --exclude-unreachable-branches --exclude-throw-branches


coverage: execute
	$(GCOVR) -s --decisions --root .. --txt $(RENDU) $(NOT_BRANCHE)

all: execute
	$(GCOVR) -s --decisions --root .. --txt $(RENDU)


# Don't touch this
execute: ./build/coverage
	{ ./build/coverage; exit 0;}

./build/coverage: ./build/gtest-all.o ./build/Automaton.o ./build/testfa.o
	$(CXX) --coverage -o ./build/coverage ./build/Automaton.o ./build/testfa.o ./build/gtest-all.o 

./build/gtest-all.o: $(GTEST_ROOT)/src/gtest-all.cc
	$(CXX) $(CXXFLAGS_GTEST) -o ./build/gtest-all.o ../googletest/googletest/src/gtest-all.cc -lpthread

./build/Automaton.o: ../Automaton.cc ../Automaton.h 
	$(CXX) $(CXXFLAGS_AUTO) -o ./build/Automaton.o ../Automaton.cc --coverage

./build/testfa.o: ../testfa.cc ../Automaton.h
	$(CXX) $(CXXFLAGS_AUTO) -o ./build/testfa.o ../testfa.cc


preparemasstest: ./build/gtest_for_test.o ./build/Automaton_for_test.o

./build/gtest_for_test.o: $(GTEST_ROOT)/src/gtest-all.cc
	$(CXX) $(CXXFLAGS_GTEST) -fPIE -o ./build/gtest_for_test.o ../googletest/googletest/src/gtest-all.cc -lpthread

./build/Automaton_for_test.o: ../Automaton.cc ../Automaton.h 
	$(CXX) $(CXXFLAGS_AUTO) -fPIE -o ./build/Automaton_for_test.o ../Automaton.cc


clean:
	rm -f ./build/*.o ./build/coverage ./build/*.gcda ./build/*.gcno ./build/*.gcov ./build/*.out
	rm -f ./coverage/*.html ./coverage/*.css

cleantest:
	rm -f ./test/*.o