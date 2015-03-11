/**
* \file linkedlist-test.cpp
* \author Andrew Scott
*
* \brief Tests a LinkedList for correctness using multiple types
*
* \details
*   Configured to use the templated linkedlist found in linkedlist.hpp as
*   linked lists of different types
*/

#include "linkedlist.hpp"
#include <iostream>
#include <cstddef>
#include <cassert>

using std::string;

/**
 * \brief Converts any type that operator << can write out into a string.
 *  
 * \param thing         thing to convert
 * \returns             string representation of thing
 * \note taken from CS70 hw8 stringtest.cpp
 * \throws std::invalid_argument  if conversion fails
 */
/*template <typename T>
std::string stringFrom (const T& thing)
{
    std::stringstream stream;
    stream << thing;

    if (!stream.fail())
        return stream.str();
    else
        throw std::invalid_argument("Conversion to string failed");
}*/

void basicStringTests()
{
    std::cout << "running basic string tests" << std::endl;
    LinkedList<string> stringList;
    std::string test = "hello world";
    assert(!stringList.contains(test));
    stringList.insertFront(test);
    assert(stringList.contains(test));
    assert(stringList.size() == 1);
}

int main(int, const char**)
{
    basicStringTests();

    // Unix "success" value
    return 0;
}