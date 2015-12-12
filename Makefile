# Makefile for data structures tester
#
# Can be built by typing
#
#   make
#
# All tests can be run by typing
#
#   make test

# ----- Make Macros ------

CXXFLAGS = -g -Wall -Wextra -pedantic -O2 -Isrc/binary_trees
CXX = clang++ -std=c++11

# SOURCE_DIR = src/
# BINARY_DIR = binary_trees

VPATH=src/binary_trees:src/other_structures:testing/correctness:\
	testing/performance

TARGETS = linked_list_test random_tree_test splay_tree_test avl_tree_test \
	red_black_tree_test two_three_four_tree_test
# good instructions for installing gtest on mac here
# http://stackoverflow.com/questions/20746232/how-to-properly-setup-googletest
# -on-os-x-aside-from-xcode
GTEST_LIB =	-lgtest -lgtest_main
export MAKEFLAGS="-j 8"



# ----- Make Rules -----

all: $(TARGETS)

clean:
	rm -f *.o $(TARGETS)

test: $(TARGETS) bench
	./linked_list_test
	./random_tree_test
	./splay_tree_test
	./avl_tree_test
#	./red_black_tree_test
#	./two_three_four_tree_test
	./bench

bench: bench.cpp $(TARGETS)
	$(CXX) $(CXXFLAGS) -o $@ bench.cpp

linked_list: linked_list_test
	./linked_list_test

randtree: random_tree_test
	./random_tree_test

splay_tree: splay_tree_test
	./splay_tree_test

avl_tree: avl_tree_test
	./avl_tree_test

red_black_tree: red_black_tree_test
	./red_black_tree_test

two_three_four_tree: two_three_four_tree_test
	./two_three_four_tree_test

linked_list_test: linked_list_test.o otter.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(GTEST_LIB)

random_tree_test: random_tree_test.o otter.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(GTEST_LIB)

splay_tree_test: splay_tree_test.o otter.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(GTEST_LIB)

avl_tree_test: avl_tree_test.o otter.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(GTEST_LIB)

red_black_tree_test: red_black_tree_test.o otter.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(GTEST_LIB)

two_three_four_tree_test: two_three_four_tree_test.o otter.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(GTEST_LIB)

# ----- Dependencies -----
otter.o: otter.cpp otter.hpp
linked_list_test.o: linked_list_test.cpp linked_list.hpp linked_list_private.hpp
random_tree_test.o: random_tree_test.cpp random_tree.hpp random_tree_private.hpp
splay_tree_test.o: splay_tree_test.cpp splay_tree.hpp splay_tree_private.hpp
avl_tree_test.o: avl_tree_test.cpp avl_tree.hpp avl_tree_private.hpp
red_black_tree_test.o: red_black_tree_test.cpp red_black_tree.hpp red_black_tree_private.hpp
two_three_four_tree_test.o: two_three_four_tree_test.cpp two_three_four_tree.hpp two_three_four_tree_private.hpp