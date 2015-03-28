# Makefile for data structures tester
#
# Can be built by typing
#
#   make
#

# ----- Make Macros ------

CXXFLAGS = -g -Wall -Wextra -pedantic
CXX = clang++ -std=c++11

TARGETS = linkedlist-test randomtree-test
# good instructions for installing gtest on mac here
# http://stackoverflow.com/questions/20746232/how-to-properly-setup-googletest
# -on-os-x-aside-from-xcode
GTEST_LIB =	-lgtest -lgtest_main



# ----- Make Rules -----

all: $(TARGETS)

clean:
	rm *.o $(TARGETS)

test: linkedlist-test randomtree-test
	./linkedlist-test
	./randomtree-test

linkedlist-test: linkedlist-test.o otter.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(GTEST_LIB)

randomtree-test: randomtree-test.o otter.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(GTEST_LIB)

#linkedlist-int-test: linkedlist-int-test.o
#	$(CXX) $(CXXFLAGS) -o $@ $^ $(GTEST_LIB)

#linkedlist-string-test: linkedlist-string-test.o
#	$(CXX) $(CXXFLAGS) -o $@ $^ $(GTEST_LIB)

#linkedlist-otter-test: linkedlist-otter-test.o otter.o
#	$(CXX) $(CXXFLAGS) -o $@ $^ $(GTEST_LIB)

# ----- Dependencies -----
otter.o: otter.cpp otter.hpp
linkedlist-test.o: linkedlist-test.cpp
randomtree-test.o: randomtree-test.cpp
#linkedlist-otter-test.o: linkedlist-otter-test.cpp
#linkedlist-string-test.o: linkedlist-string-test.cpp
#linkedlist-int-test.o: linkedlist-int-test.cpp