# Makefile for data structures tester
#
# Can be built by typing
#
#   make
#

# ----- Make Macros ------

CXXFLAGS = -g -Wall -Wextra -pedantic
CXX = clang++ -std=c++11

TARGETS = linkedlist-int-test linkedlist-string-test linkedlist-otter-test
GTEST_LIB =	-lgtest -lgtest_main



# ----- Make Rules -----

all: $(TARGETS)

clean:
	rm *.o $(TARGETS)

test: linkedlist-int-test linkedlist-string-test linkedlist-otter-test
	./linkedlist-int-test
	./linkedlist-string-test
	./linkedlist-otter-test

linkedlist-int-test: linkedlist-int-test.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(GTEST_LIB)

linkedlist-string-test: linkedlist-string-test.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(GTEST_LIB)

linkedlist-otter-test: linkedlist-otter-test.o otter.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(GTEST_LIB)

# ----- Dependencies -----
otter.o: otter.cpp otter.hpp
linkedlist-otter-test.o: linkedlist-otter-test.cpp
linkedlist-string-test.o: linkedlist-string-test.cpp
linkedlist-int-test.o: linkedlist-int-test.cpp