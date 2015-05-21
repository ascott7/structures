# Makefile for data structures tester
#
# Can be built by typing
#
#   make
#

# ----- Make Macros ------

CXXFLAGS = -g -Wall -Wextra -pedantic -O2
CXX = clang++ -std=c++11

TARGETS = linkedlist-test randomtree-test splaytree-test avltree-test \
	rbtree-test
# good instructions for installing gtest on mac here
# http://stackoverflow.com/questions/20746232/how-to-properly-setup-googletest
# -on-os-x-aside-from-xcode
GTEST_LIB =	-lgtest -lgtest_main
export MAKEFLAGS="-j 8



# ----- Make Rules -----

all: $(TARGETS)

clean:
	rm -f *.o $(TARGETS)

test: $(TARGETS) bench
	./linkedlist-test
	./randomtree-test
	./splaytree-test
	./avltree-test
#	./rbtree-test
	./bench

bench: bench.cpp $(TARGETS)
	$(CXX) $(CXXFLAGS) -o $@ bench.cpp

linkedlist: linkedlist-test
	./linkedlist-test

randtree: randomtree-test
	./randomtree-test

splaytree: splaytree-test
	./splaytree-test

avltree: avltree-test
	./avltree-test

rbtree: rbtree-test
	./rbtree-test

linkedlist-test: linkedlist-test.o otter.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(GTEST_LIB)

randomtree-test: randomtree-test.o otter.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(GTEST_LIB)

splaytree-test: splaytree-test.o otter.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(GTEST_LIB)

avltree-test: avltree-test.o otter.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(GTEST_LIB)

rbtree-test: rbtree-test.o otter.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(GTEST_LIB)

# ----- Dependencies -----
otter.o: otter.cpp otter.hpp
linkedlist-test.o: linkedlist-test.cpp linkedlist.hpp linkedlist-private.hpp
randomtree-test.o: randomtree-test.cpp randomtree.hpp randomtree-private.hpp
splaytree-test.o: splaytree-test.cpp splaytree.hpp splaytree-private.hpp
avltree-test.o: avltree-test.cpp avltree.hpp avltree-private.hpp
rbtree-test.o: rbtree-test.cpp rbtree.hpp rbtree-private.hpp
