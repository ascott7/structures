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
#GTEST_LIB =	-lgtest -lgtest_main



# ----- Make Rules -----

all: $(TARGETS)

clean:
	rm *.o $(TARGETS)

test: linkedlist-test
	./linkedlist-test

linkedlist-test: linkedlist-test.o
	$(CXX) $(CXXFLAGS) $^ -o $@

# ----- Dependencies -----

hashtest.o: hashtest.cpp hashtable.hpp
hashtable.o: hashtable.hpp hashtable.cpp
linkedlist-test.o: linkedlist.hpp linkedlist-test.cpp
linkedlist.o: linkedlist.hpp linkedlist-private.hpp