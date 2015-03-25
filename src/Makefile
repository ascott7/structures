# Makefile for data structures tester
#
# Can be built by typing
#
#   make
#

# ----- Make Macros ------

CXXFLAGS = -g -Wall -Wextra -pedantic
CXX = clang++ -std=c++11

TARGETS = linkedlist-test
GTEST_LIB =	-lgtest -lgtest_main



# ----- Make Rules -----

all: $(TARGETS)

clean:
	rm *.o $(TARGETS)

test: linkedlist-test
	./linkedlist-test

linkedlist-test: linkedlist-test.o otter.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(GTEST_LIB)

# ----- Dependencies -----
otter.o: otter.cpp otter.hpp
linkedlist-test.o: linkedlist-test.cpp