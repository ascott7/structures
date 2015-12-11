/**
 * \file bench.cpp
 * \author Andrew Scott
 * \brief The program benchmarks insertions and erases in
 * std::orderedset, RandomTree, SplayTree, AvlTree and RBTree
 */

#include "linkedlist.hpp"
#include "randomtree.hpp"
#include "splaytree.hpp"
#include "avltree.hpp"
#include "rbtree.hpp"
#include "stdset.hpp"
#include "pcg-cpp-0.98/include/pcg_random.hpp"

#include <iostream>
#include <cstdlib>
#include <list>
#include <vector>
#include <iterator>
#include <random>
#include <chrono>
#include <set>
#include <list>


enum class Container {
    LINKED_LIST,
    STD_SET,
    RANDOM_TREE,
    SPLAY_TREE,
    AVL_TREE,
    RB_TREE
};


enum class Test {
  INSERT_INORDER,
  INSERT_RANDOM,
  ERASE_INORDER,
  ERASE_RANDOM
};

static int testSizes[] = {100, 1000, 10000, 100000};
size_t numTestSizes = 4;
static int randomNums[100000];
pcg32 rng(pcg_extras::seed_seq_from<std::random_device>{});


/*struct TestInfo {
    //Test testType_;
    //Container containerType_;
    //size_t testSize_;
    float runtime_;
    TestInfo(Test testType, Container containerType, size_t testSize, float runtime)
        : testType_{testType}, containerType_{containerType}, testSize_{testSize}, 
          runtime_{runtime}
    {}
    TestInfo(float runtime)
        : runtime_{runtime}
    {}
};*/

/*void linkedListTest(Test testType, size_t testSize)
{
    LinkedList<int> testList;
    if (testType == Test::INSERT_INORDER) {
        for (size_t i = 0; i < testSize; ++i) {
            testList.insert(i);
            if (!testList.contains(i)) {
                std::cerr << "Correctness error: list should contain " << i << std::endl;
            }
        }
    } else if (testType == INSERT_RANDOM) {
        for (size_t i = 0; i < testSize; ++i) {
            int randInsert = rand();
            testList.insert(i);
            if (!testList.contains(i)) {
                std::cerr << "Correctness error: list should contain " << i << std::endl;
            }
        }
    }
}*/

void makeRandomArray()
{
    for (int i = 0; i < testSizes[numTestSizes - 1]; ++i) {
        randomNums[i] = rng(testSizes[numTestSizes - 1]);
    }
}

size_t singleTreeTest(Test testType, Container treeType, int testSize)
{
    using clock = std::chrono::high_resolution_clock;
    clock::time_point startTime = clock::now();
    clock::time_point stopTime = clock::now();
    std::string testName;
    AbstractTree<int>* testTree;
    if (treeType == Container::RANDOM_TREE) {
        testTree = new RandomTree<int>;
    } else if (treeType == Container::SPLAY_TREE) {
        testTree = new SplayTree<int>;
    } else if (treeType == Container::AVL_TREE) {
        testTree = new AvlTree<int>;
    } else if (treeType == Container::RB_TREE) {
        testTree = new RBTree<int>;
    } else if (treeType == Container::STD_SET) {
        testTree = new StdSet<int>;
    }
    if (testType == Test::INSERT_INORDER) {
        startTime = clock::now();
        for (int i = 0; i < testSize; ++i) {
            testTree->insert(i);
            assert(testTree->contains(i));
        }
        stopTime = clock::now();
    } 

    else if (testType == Test::INSERT_RANDOM) {
        startTime = clock::now();
        for (int i = 0; i < testSize; ++i) {
            int numToInsert = randomNums[i];
            testTree->insert(numToInsert);
            assert(testTree->contains(numToInsert));
        }
        stopTime = clock::now();
    } 

    else if (testType == Test::ERASE_INORDER) {
        for (int i = 0; i < testSize; ++i) {
            testTree->insert(i);
        }
    } 

    else if (testType == Test::ERASE_RANDOM) {
        for (int i = 0; i < testSize; ++i) {
            int numToInsert = rand() % testSize;
            testTree->insert(numToInsert);
        }
    }
    clock::duration elapsed = stopTime - startTime;
    return std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
}

void runTest(Test testType, Container treeType)
{
    // using clock = std::chrono::high_resolution_clock;

    std::vector<size_t> testStatistics;
    std::string testName;

    if (testType == Test::INSERT_INORDER) {
        testName = "insert inorder";
    } else if (testType == Test::INSERT_RANDOM) {
        testName = "insert random";
    } else if (testType == Test::ERASE_INORDER) {
        testName = "erase inorder";
    } else if (testType == Test::ERASE_RANDOM) {
        testName = "erase random";
    }

    for (size_t i = 0; i < numTestSizes; ++i) {
        
        testStatistics.push_back(singleTreeTest(testType, treeType, testSizes[i]));
        //testStatistics.push_back(ticks);
    }

    std::cout << testName << "\t";
    for (size_t i = 0; i < testStatistics.size(); ++i) {
        printf("\t%d", testStatistics[i]);
    }
    std::cout << std::endl;
}

void runTreeTests(Container treeType)
{
    printf("test size:\t");
    for (size_t i = 0; i < numTestSizes; ++i) {
        printf("\t%d", testSizes[i]);
    }
    printf("\n");
    runTest(Test::INSERT_INORDER, treeType);
    runTest(Test::INSERT_RANDOM, treeType);
    runTest(Test::ERASE_INORDER, treeType);
    runTest(Test::ERASE_RANDOM, treeType);
    std::cout << std::endl;
}

/**
 * \brief Option Processing
 * \details
 *   Sets various configuration variables by modifying variables passed
 *   by reference.
 *
 *   Will return with an exit error of 2 if receives a usage problem.
 *
 * \param options       Input of options from command line.
 * \param testType      Which kind of container to test
 * \param testType      Which test to run
 * \param insertions    How many insertions to perform.
 */
/*
void processOptions(std::list<std::string> options,
                    Container&             containerType,
                    Test&                  testType,
                    size_t&                insertions)
{

    // Set the defaults
    testType = Test::INSERT_FRONT;
    containerType = Container::VECTOR;
    insertions = 100000;

    // Loop through the options. If they start with a dash
    // try to interpret them as a flag; if not, assume it's
    // the number of insertions.
    while (!options.empty()) {
        std::string option = options.front();
        options.pop_front();

        if (option.empty()) {
            std::cerr << "Empty argument" << std::endl;
            exit(2);
        };

        // If we've gotten this far, the argument has at least one
        // character, so it's safe to ask whether that character is
        // a dash or not.
        if (option[0] >= '0' && option[0] <= '9') {
            // Starts with a digit, so try to interpret it as a number of
            // insertions, using the C++11 string-to-unsigned-long converter
            insertions = std::stoul(option);

        } else if (option == "-v" || option == "--vector") {
            containerType = Container::VECTOR;            

        } else if (option == "-l" || option == "--intlist") {
            containerType = Container::INTLIST;            

        } else if (option == "-f" || option == "--front") {
            testType = Test::INSERT_FRONT;

        } else if (option == "-b" || option == "--back") {
            testType = Test::INSERT_BACK;

        } else if (option == "-m" || option == "--middle") {
            testType = Test::INSERT_MIDDLE;

        } else {
            std::cerr << "Unrecognized option: " << option << std::endl;
            std::cerr << "Usage: ./bench [-v|-l|-f|-b|-m] [num]" << std::endl;
            exit(2);
        }
    }
}*/

int main(int argc, const char* argv[])
{
    // These three variables will be set by processOptions.
    Container containerType;
    Test testType;
    size_t insertions;
    //srand(time(NULL));
    makeRandomArray();

    // Turn the command line (an array of C-style strings)
    // into a nice C++ list of C++ strings, and pass them to
    // processOptions. (Note that the arguments to the
    // list constructor are pointers into the array, being
    // used as start and end iterators.)

    //std::list<std::string> options(argv + 1, argv + argc);
    //processOptions(options, containerType, testType, insertions);


    // linked list benchmarks

    // for reference: std::list
    std::cout << "std::set benchmarks" << std::endl;
    runTreeTests(Container::STD_SET);

    // random tree benchmarks
    std::cout << "random tree benchmarks" << std::endl;
    runTreeTests(Container::RANDOM_TREE);

    // splay tree benchmarks
    std::cout << "splay tree benchmarks" << std::endl;
    runTreeTests(Container::SPLAY_TREE);

    // avl tree benchmarks
    std::cout << "avl tree benchmarks" << std::endl;
    runTreeTests(Container::AVL_TREE);

    // red black tree benchmarks
    std::cout << "red-black tree benchmarks" << std::endl;
    runTreeTests(Container::RB_TREE);

    // for reference: std::set


    /*clock::time_point startTime = clock::now();

    if (containerType == Container::LINKED_LIST) {
      vectorTest(testType, insertions);
    } else if (containerType == Container::INTLIST) {
      intlistTest(testType, insertions);
    } else {
      std::cerr << "Unknown container type!" << std::endl;
      exit(4);
    }

    clock::time_point stopTime = clock::now();

    // Compute the elapsed duration, convert that to microseconds, and display

    clock::duration elapsed = stopTime - startTime;
    size_t ticks = 
      std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    const std::string micro = "\u00B5";  // unicode micro symbol
    std::cout << ticks << " " << micro << "s total" << std::endl;
    std::cout << float(ticks) / insertions << " "
              << micro << "s per insertion" << std::endl;
    */
    // Unix "success" value
    return 0;
}
